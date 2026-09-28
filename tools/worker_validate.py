"""Canonical raw-OMF and strict-match oracle for persistent C7 workers."""
import argparse
import statistics
import time

from common import ROOT, read_json, write_json, FormatError, fixture, identity
from compiler import verify_lock
from compiler_service import (SUPPORTED_WORKERS, current_proof_inputs,
                              require_worker_proof)
from compiler_worker import Win31Worker
from library_match import import_symbols, compare_member
from matcher import compare
import omf
import ne
import mapsym


def percentile(values, percent):
    if not values:
        return None
    values = sorted(values)
    return values[min(len(values) - 1, max(0, int((len(values) - 1) * percent + .5)))]


def resource_summary(rows, workers, elapsed):
    result = []
    for worker_id in range(workers):
        selected = [row['receipt'] for row in rows if row['receipt'].get('worker_id') == worker_id]
        metrics = [receipt.get('resource_delta') for receipt in selected]
        metrics = [item for item in metrics if item]
        result.append(dict(
            worker_id=worker_id,
            jobs=len(selected),
            sessions=len({receipt.get('worker_session') for receipt in selected}),
            environment_launches=sum(receipt.get('timing', {}).get('environment_launches', 0) for receipt in selected),
            cpu_seconds=round(sum(item['cpu_seconds'] for item in metrics), 4),
            cpu_percent_of_one_core=round(100 * sum(item['cpu_seconds'] for item in metrics) / elapsed, 2) if elapsed else None,
            peak_working_set_bytes=max((item['peak_working_set_bytes'] for item in metrics), default=None),
            read_transfer_bytes=sum(item['read_transfer_bytes'] for item in metrics),
            write_transfer_bytes=sum(item['write_transfer_bytes'] for item in metrics),
            read_operations=sum(item['read_operations'] for item in metrics),
            write_operations=sum(item['write_operations'] for item in metrics),
            io_measurement='Windows process I/O transfer counters; logical bytes, not physical-device bytes',
            samples=len(metrics)))
    return result


def canonical_compare(obj, probe, target, raw, image, symbols, imports):
    module = omf.parse(obj.read_bytes())
    if probe in ('CreateMonoSolidBrush', 'RandTurn', 'win_SetWinDrawHook'):
        return compare_member(module, raw, image, symbols, imports)
    return compare(module, raw, image, symbols, target)


def load_canonical():
    oracle_path = ROOT / 'evidence/experiments/toolchain/msc700-baseline-Oelw.json'
    if not oracle_path.exists():
        raise FormatError('canonical worker oracle is missing: ' + oracle_path.relative_to(ROOT).as_posix())
    oracle = read_json(oracle_path)
    for row in oracle.get('results', []):
        receipt = row.get('receipt', {})
        source = receipt.get('source')
        expected_source = ROOT / source if source else None
        if expected_source is None or not expected_source.is_file():
            raise FormatError('canonical worker source is missing: %s' % source)
        if identity(expected_source) != receipt.get('source_identity'):
            raise FormatError('canonical worker source identity disagrees with oracle: %s' % source)
        object_path = receipt.get('object')
        expected_object = receipt.get('object_identity')
        if (not object_path or not isinstance(expected_object, dict) or
                not isinstance(expected_object.get('size'), int) or expected_object['size'] < 0 or
                not isinstance(expected_object.get('sha256'), str) or len(expected_object['sha256']) != 64):
            raise FormatError('canonical worker oracle has no valid object identity: %s' % object_path)
        if any(char not in '0123456789abcdef' for char in expected_object['sha256'].lower()):
            raise FormatError('canonical worker oracle has invalid object digest: %s' % object_path)
        canonical_object = ROOT / object_path
        if canonical_object.is_file() and identity(canonical_object) != expected_object:
            raise FormatError('canonical worker OMF identity disagrees with oracle: %s' % object_path)
    raw = fixture('SIMANTW.EXE')
    image = ne.parse(raw)
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    targets = {'_' + row.get('probe', row['symbol'].lstrip('_')): row for row in oracle['probes']}
    return oracle, raw, image, symbols, imports, targets


def canonical_object_equal(obj, row):
    """Compare the complete OMF with the oracle's recorded byte identity."""
    expected = row.get('receipt', {}).get('object_identity')
    return bool(obj) and isinstance(expected, dict) and identity(obj) == expected


def validate_workers(workers):
    if workers not in SUPPORTED_WORKERS:
        raise FormatError('workers must be one of ' + ', '.join(map(str, SUPPORTED_WORKERS)))
    if workers > 1:
        require_worker_proof(1)
    verify_lock(read_json(ROOT / 'layout/toolchain.json'))
    oracle, raw, image, symbols, imports, targets = load_canonical()
    jobs = oracle['results'] * 2
    started = time.perf_counter()

    def run_worker(index):
        results = []
        with Win31Worker(index) as worker:
            for position in range(index, len(jobs), workers):
                probe = jobs[position]
                obj, receipt = worker.compile(probe['receipt']['source'], probe['flags'])
                byte_equal = canonical_object_equal(obj, probe)
                comparison = canonical_compare(obj, probe['probe'], targets['_' + probe['probe']], raw, image, symbols, imports) if obj else None
                match_equal = comparison is not None and comparison['result'] == probe['result']
                results.append(dict(position=position, probe=probe['probe'], canonical_omf_equal=byte_equal,
                                    canonical_match_equal=match_equal,
                                    result=comparison['result'] if comparison else None,
                                    expected_result=probe['result'], receipt=receipt))
                print(index, probe['probe'], byte_equal, match_equal,
                      round(receipt['timing']['total_compile_request_seconds'], 3), flush=True)
        return results

    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor(max_workers=workers) as pool:
        results = [row for group in pool.map(run_worker, range(workers)) for row in group]
    elapsed = time.perf_counter() - started
    latencies = [row['receipt']['timing']['total_compile_request_seconds'] for row in results]
    inputs = current_proof_inputs()
    report = dict(workers=workers, passed=len(results) == len(jobs) and all(
        row['canonical_omf_equal'] and row['canonical_match_equal'] for row in results),
        inputs=inputs, elapsed_seconds=elapsed, throughput_compiles_per_second=len(results) / elapsed,
        per_job_latency_seconds=dict(p50=percentile(latencies, .50), p95=percentile(latencies, .95),
                                     mean=statistics.mean(latencies) if latencies else None),
        environment_launches=sum(row['receipt']['timing']['environment_launches'] for row in results),
        jobs=len(results), resource_per_host=resource_summary(results, workers, elapsed),
        results=sorted(results, key=lambda row: row['position']))
    diagnostic = ROOT / ('build/worker-validation/worker-%d.json' % workers)
    write_json(diagnostic, report)
    proof_path = ROOT / ('evidence/experiments/runner/worker-%d.json' % workers)
    if report['passed']:
        write_json(proof_path, report)
    else:
        proof_path.unlink(missing_ok=True)
        raise FormatError('canonical worker oracle failed; diagnostic: ' + diagnostic.relative_to(ROOT).as_posix())
    print('PASS', workers, 'workers', len(results), 'jobs', round(elapsed, 2), 'seconds',
          round(report['throughput_compiles_per_second'], 2), 'compiles/s', flush=True)
    return report


def service_stress(workers=4, total=400):
    """Run canonical client/server load and strictly rematch every returned object."""
    if workers not in SUPPORTED_WORKERS:
        raise FormatError('workers must be one of ' + ', '.join(map(str, SUPPORTED_WORKERS)))
    require_worker_proof(workers)
    oracle, raw, image, symbols, imports, targets = load_canonical()
    canonical_jobs = oracle['results']
    jobs = [canonical_jobs[index % len(canonical_jobs)] for index in range(total)]
    started = time.perf_counter()
    compiled = []
    error = None
    try:
        from compiler_service import compile_jobs
        compiled = compile_jobs([dict(source=job['receipt']['source'], flags=job['flags']) for job in jobs], workers=workers)
    except Exception as exc:
        error = str(exc)
    rows = []
    for index, ((obj, receipt), job) in enumerate(zip(compiled, jobs)):
        byte_equal = canonical_object_equal(obj, job)
        comparison = canonical_compare(obj, job['probe'], targets['_' + job['probe']], raw, image, symbols, imports) if obj else None
        match_equal = comparison is not None and comparison['result'] == job['result']
        rows.append(dict(position=index, probe=job['probe'], canonical_omf_equal=byte_equal,
                         canonical_match_equal=match_equal,
                         result=comparison['result'] if comparison else None,
                         expected_result=job['result'], receipt=receipt))
    elapsed = time.perf_counter() - started
    latencies = [row['receipt'].get('service_timing', {}).get('end_to_end_seconds') for row in rows]
    latencies = [value for value in latencies if value is not None]
    divergences = sum(not row['canonical_omf_equal'] or not row['canonical_match_equal'] for row in rows)
    lower_error = (error or '').lower()
    timeouts = int('timeout' in lower_error)
    report = dict(workers=workers, expected_jobs=total, completed_jobs=len(rows), passed=error is None and
                  len(rows) == total and divergences == 0,
                  elapsed_seconds=elapsed, throughput_compiles_per_second=len(rows) / elapsed if elapsed else 0,
                  per_job_latency_seconds=dict(p50=percentile(latencies, .50), p95=percentile(latencies, .95),
                                               mean=statistics.mean(latencies) if latencies else None),
                  divergences=divergences, timeouts=timeouts, lost_jobs=max(0, total - len(rows)),
                  error=error, environment_launches=sum(row['receipt'].get('timing', {}).get('environment_launches', 0) for row in rows),
                  worker_sessions=len({row['receipt'].get('worker_session') for row in rows}),
                  resource_per_host=resource_summary(rows, workers, elapsed),
                  mismatches=[row for row in rows if not row['canonical_omf_equal'] or not row['canonical_match_equal']][:20])
    report_path = ROOT / ('build/worker-validation/service-stress-%d.json' % workers)
    write_json(report_path, report)
    if not report['passed']:
        (ROOT / ('evidence/experiments/runner/worker-%d.json' % workers)).unlink(missing_ok=True)
        raise FormatError('service stress failed; diagnostic: ' + report_path.relative_to(ROOT).as_posix())
    # validate.py's gate: the canonical stress record, bound to the service implementation it exercised.
    from compiler_service import IMPLEMENTATION
    write_json(ROOT / 'evidence/experiments/runner/service-stress.json',
               dict(passed=True, jobs=total, workers=workers, elapsed_seconds=elapsed,
                    throughput_compiles_per_second=report['throughput_compiles_per_second'],
                    inputs={p: identity(ROOT / p) for p in IMPLEMENTATION},
                    diagnostic=report_path.relative_to(ROOT).as_posix()))
    print('PASS service stress', workers, 'workers', total, 'jobs', round(elapsed, 2), 'seconds',
          round(report['throughput_compiles_per_second'], 2), 'compiles/s', flush=True)
    return report


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--workers', type=int, default=1)
    parser.add_argument('--service-stress', action='store_true', help='canonical client/server stress run')
    parser.add_argument('--jobs', type=int, default=400, help='service stress job count')
    args = parser.parse_args()
    if args.service_stress:
        service_stress(args.workers, args.jobs)
    else:
        validate_workers(args.workers)


if __name__ == '__main__':
    main()
