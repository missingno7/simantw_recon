"""Run the ten assigned-profile residue pilots from saved context packets."""
import json
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SYMBOLS = ['_XferPatch', '_SimQueenR', '_AnimYellowInsane', '_gr_BitMapSize',
           '_FloodNestB', '_WaitHundredths', '_GetSmellT', '_SubtractFood',
           '_HoleBorder', '_YellowCommand']


def main():
    context_root = ROOT / 'build' / 'permuter' / 'context'
    out_root = ROOT / 'build' / 'permuter' / 'pilots'
    out_root.mkdir(parents=True, exist_ok=True)
    stamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    processes = []
    for i, symbol in enumerate(SYMBOLS):
        context_path = context_root / f'{symbol}.json'
        context = json.loads(context_path.read_text(encoding='utf-8'))
        draft = context.get('best_draft') or {}
        source = ROOT / draft['source']
        if not source.is_file():
            raise FileNotFoundError(f'{symbol}: saved best draft is missing: {source}')
        run_dir = ROOT / 'build' / 'permuter' / f'{symbol}_{stamp}_pilot'
        symbol_dir = out_root / symbol
        symbol_dir.mkdir(parents=True, exist_ok=True)
        log = symbol_dir / 'driver.log'
        command = [sys.executable, 'tools/permuter.py', str(source), '--function', symbol,
                   '--time-limit', '900', '--iterations', '100000', '--batch-size', '48',
                   '--beam', '8', '--seed', str(770900 + i), '--out', str(run_dir)]
        stream = log.open('w', encoding='utf-8')
        process = subprocess.Popen(command, cwd=ROOT, stdout=stream, stderr=subprocess.STDOUT)
        profile_data = context.get('compiler_profile') or {}
        profile_name = ((profile_data.get('profile') or {}).get('name')
                        if isinstance(profile_data.get('profile'), dict) else profile_data.get('profile'))
        processes.append({'symbol': symbol, 'source': str(source), 'draft_key': draft.get('key'),
                          'profile': profile_name,
                          'run_dir': str(run_dir), 'log_path': str(log), 'started': time.time(),
                          'process': process, 'stream': stream})
        print(f"started {symbol}: profile={processes[-1]['profile']} "
              f"draft={draft.get('opcode_matches')}/{draft.get('opcode_total')}", flush=True)

    while any(row['process'].poll() is None for row in processes):
        time.sleep(30)
        live = [row['symbol'] for row in processes if row['process'].poll() is None]
        print(f"pilot progress: {len(live)}/{len(processes)} active: {', '.join(live)}", flush=True)

    results = []
    for row in processes:
        row['stream'].close()
        summary_path = Path(row['run_dir']) / 'summary.json'
        summary = json.loads(summary_path.read_text(encoding='utf-8')) if summary_path.exists() else {}
        results.append({k: v for k, v in row.items() if k not in ('process', 'stream')} | {
            'return_code': row['process'].returncode,
            'elapsed_seconds': round(time.time() - row['started'], 2),
            'time_limit_seconds': 900,
            'baseline': summary.get('baseline'), 'best': summary.get('best'),
            'profile_used': summary.get('profile'), 'flags_used': summary.get('flags'),
            'earliest_movement': summary.get('baseline_to_best_earliest_movement'),
            'evaluations': (summary.get('counts') or {}).get('evaluations'),
            'compiler_misses': (summary.get('counts') or {}).get('compiler_misses'),
            'candidate_evaluations_per_second': summary.get('candidate_evaluations_per_second'),
            'compiler_misses_per_second': summary.get('compiler_misses_per_second'),
            'duplicate_source_rate': summary.get('duplicate_source_rate'),
            'duplicate_output_rate': summary.get('duplicate_output_rate'),
            'exact_source': summary.get('exact_source'),
            'best_chain': summary.get('best_chain'),
            'source_class': summary.get('best_source_class'),
            'steering_mutations': summary.get('steering_mutations'),
        })
    report = {'started': stamp, 'fixed_time_limit_seconds': 900, 'pilots': results,
              'throughput_evaluations_per_second': round(
                  sum(row.get('evaluations') or 0 for row in results) /
                  max(max((row['elapsed_seconds'] for row in results), default=1), 1), 3),
              'scope': 'One assigned-profile search per requested near-exact target; no promotion.'}
    (out_root / 'summary.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
    exact = [row['symbol'] for row in results if row.get('exact_source')]
    print(f"pilots complete: exact={exact or 'none'}; aggregate throughput="
          f"{report['throughput_evaluations_per_second']} evaluations/s", flush=True)
    return 0 if all(row['return_code'] == 0 for row in results) else 1


if __name__ == '__main__':
    raise SystemExit(main())
