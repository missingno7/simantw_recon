"""Generate and search perturbed admitted controls for the MSC permuter."""
import json
import copy
import hashlib
import random
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import permuter_mutations as M
from permuter import source_function
from common import relative

CONTROLS = [('_ms_Delay', 32102), ('_FloorTiles', 32103)]
GOOD = {'CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'}


def main():
    ledger = json.loads((ROOT / 'src/recovery.json').read_text(encoding='utf-8'))['targets']
    out_root = ROOT / 'build' / 'permuter' / 'controls_meaningful'
    out_root.mkdir(parents=True, exist_ok=True)
    process_rows = []
    for symbol, seed in CONTROLS:
        recipe = ledger[symbol]
        source_path = ROOT / recipe['source']
        source = source_path.read_text(encoding='ascii')
        function = source_function(source, symbol)
        codec = M.BodyCodec(source, function)
        rng = random.Random(seed)
        variants = []
        seen = set()
        for variant_id in range(64):
            body = copy.deepcopy(codec.body)
            wanted = rng.randint(2, 4)
            chain = []
            attempts = 0
            while len(chain) < wanted and attempts < 100:
                attempts += 1
                description = M.mutate(body, rng, allow_risky=False, tries=25)
                if description:
                    chain.append(description)
            if len(chain) != wanted or set(M.local_hygiene(body)) - set(M.local_hygiene(codec.body)):
                continue
            perturbed = codec.splice(codec.render(body))
            key = hashlib.sha256(perturbed.encode('ascii')).hexdigest()
            if perturbed != source and key not in seen:
                seen.add(key)
                variants.append({'source': perturbed, 'body': body, 'chain': chain,
                                 'wanted': wanted, 'variant_id': variant_id})
        if not variants:
            raise RuntimeError(f'{symbol}: no valid randomized perturbations')
        from codegen_grinder import run
        from promote import function_flags
        profile, flags = function_flags(symbol)
        probe_dir = out_root / 'perturb_probes' / symbol
        probe = run({'symbol': symbol, 'compiler': 'msc700', 'flags': flags,
                     'sources': [x['source'] for x in variants], 'max_candidates': len(variants)},
                    relative(probe_dir), cache=True)
        outcomes = {r['candidate']: r['comparison']['result'] for r in probe['results']}
        chosen = next((index for index in range(len(variants))
                       if outcomes.get(index) not in GOOD and
                       outcomes.get(index) not in {'COMPILE_FAILED', 'UNSUPPORTED_COMPARISON'}), None)
        if chosen is None:
            raise RuntimeError(f'{symbol}: 64 random mutation chains all kept the exact member')
        perturb = variants[chosen]
        wanted = perturb['wanted']
        chain = perturb['chain']
        perturbed = perturb['source']
        control_dir = out_root / symbol
        control_dir.mkdir(parents=True, exist_ok=True)
        perturbed_path = control_dir / 'perturbed.c'
        perturbed_path.write_text(perturbed, encoding='ascii')
        run_dir = ROOT / 'build' / 'permuter' / f'{symbol}_control_{datetime.now():%Y%m%d_%H%M%S}'
        log = control_dir / 'search.log'
        command = [sys.executable, 'tools/permuter.py', str(perturbed_path), '--function', symbol,
                   '--time-limit', '300', '--iterations', '20000', '--batch-size', '48',
                   '--beam', '8', '--seed', str(seed + 100), '--out', str(run_dir)]
        stream = log.open('w', encoding='utf-8')
        process = subprocess.Popen(command, cwd=ROOT, stdout=stream, stderr=subprocess.STDOUT)
        process_rows.append({'symbol': symbol, 'profile': recipe.get('profile'), 'seed': seed,
                             'perturbations': wanted, 'mutation_chain': chain,
                             'perturb_member_result': outcomes.get(chosen),
                             'perturb_probe_candidates': len(variants),
                             'perturb_probe_cache': probe.get('cache'),
                             'source': str(perturbed_path), 'run_dir': str(run_dir),
                             'log_path': str(log), 'started': time.time(),
                             'process': process, 'stream': stream})
        print(f"started {symbol}: profile={recipe.get('profile')} mutations={wanted}", flush=True)

    while any(row['process'].poll() is None for row in process_rows):
        time.sleep(5)

    results = []
    for row in process_rows:
        row['stream'].close()
        summary_path = Path(row['run_dir']) / 'summary.json'
        summary = json.loads(summary_path.read_text(encoding='utf-8')) if summary_path.exists() else {}
        results.append({k: v for k, v in row.items() if k not in ('process', 'stream')} | {
            'return_code': row['process'].returncode,
            'seconds': round(time.time() - row['started'], 2),
            'recovered_exact': bool(summary.get('best', {}).get('strict_exact')),
            'exact_source': summary.get('exact_source'),
            'profile_used': summary.get('profile'),
            'evaluations': (summary.get('counts') or {}).get('evaluations'),
            'candidate_evaluations_per_second': summary.get('candidate_evaluations_per_second'),
            'best': summary.get('best'),
            'search_chain': summary.get('best_chain'),
            'source_class': summary.get('best_source_class'),
        })
    report = {'controls': results,
              'recoveries': sum(bool(row['recovered_exact']) for row in results),
              'count': len(results),
              'recovery_rate': sum(bool(row['recovered_exact']) for row in results) / max(len(results), 1),
              'elapsed_seconds': max((row['seconds'] for row in results), default=0),
              'scope': 'Strict complete-member result; no promotion.'}
    (out_root / 'summary.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
    print(f"controls recovered {report['recoveries']}/{report['count']} "
          f"({report['recovery_rate']:.0%}) in {report['elapsed_seconds']:.1f}s", flush=True)
    return 0 if all(row['return_code'] == 0 for row in results) else 1


if __name__ == '__main__':
    raise SystemExit(main())
