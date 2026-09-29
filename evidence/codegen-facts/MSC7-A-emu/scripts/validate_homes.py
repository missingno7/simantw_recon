"""Validate the home (stack-slot) model against C2 on every admitted msc700 source."""
import sys, json, time
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools'))

def job(item):
    src, flags = item
    import regalloc_model as RM
    try:
        _r, fns = RM.capture_homes((ROOT / src).read_bytes(), list(flags))
        return src, flags, [dict(function=r['function'], n=r['n'], mismatches=r['mismatches']) for r in RM.compare_homes(fns)], None
    except Exception as e:
        return src, flags, [], repr(e)[:300]

if __name__ == '__main__':
    targets = json.load(open(ROOT / 'src/recovery.json'))['targets']
    jobs = sorted({(v['source'], tuple(v['flags'])) for v in targets.values()
                   if v.get('compiler') == 'msc700' and v.get('proof') == 'BYTE_MATCHED_RECONSTRUCTION'})
    with Pool(12) as p:
        out = list(p.imap_unordered(job, jobs))
    rows = [r for s, f, rs, e in out for r in rs]
    multi = [r for r in rows if r['n'] >= 2]
    print(json.dumps(dict(functions=len(rows), exact=sum(not r['mismatches'] for r in rows),
                          with_2plus_homes=len(multi), exact_2plus=sum(not r['mismatches'] for r in multi),
                          homes=sum(r['n'] for r in rows), home_mismatches=sum(len(r['mismatches']) for r in rows),
                          errors=[(s, e) for s, f, rs, e in out if e]), indent=1))
    json.dump(out, open(ROOT / 'build/workers/f-alloc-emu/home_validation.json', 'w'), indent=1)
    for s, f, rs, e in out:
        for r in rs:
            if r['mismatches']: print('MISMATCH', s, r['function'], r['mismatches'])
