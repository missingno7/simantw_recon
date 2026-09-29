"""Validate colouring + post-colouring model (to C2's final registers) on every admitted msc700 source."""
import sys, json, collections
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools'))
def job(item):
    src, flags = item
    import regalloc_model as RM
    try:
        _r, fns = RM.capture((ROOT / src).read_bytes(), list(flags))
        return src, flags, RM.compare_full(fns), None
    except Exception as e:
        import traceback
        return src, flags, [], traceback.format_exc()[-600:]
if __name__ == '__main__':
    targets = json.load(open(ROOT / 'src/recovery.json'))['targets']
    jobs = sorted({(v['source'], tuple(v['flags'])) for v in targets.values()
                   if v.get('compiler') == 'msc700' and v.get('proof') == 'BYTE_MATCHED_RECONSTRUCTION'})
    with Pool(12) as p:
        out = list(p.imap_unordered(job, jobs))
    rows = [r for s, f, rs, e in out for r in rs]
    summ = dict(functions=len(rows),
                split_exact=sum(not r['split'] for r in rows), repick_exact=sum(not r['repick'] for r in rows),
                final_exact=sum(not r['final'] for r in rows),
                final_exact_no_rangesplit=sum(not r['final'] for r in rows if not r['split_seen']),
                no_rangesplit=sum(not r['split_seen'] for r in rows),
                with_sidi=sum(1 for r in rows if r['final_sidi']),
                with_sidi_exact=sum(1 for r in rows if r['final_sidi'] and not r['final']),
                candidates=sum(r['n'] for r in rows), final_mismatches=sum(len(r['final']) for r in rows),
                errors=[(s, e) for s, f, rs, e in out if e][:5])
    by = collections.defaultdict(lambda: [0, 0])
    for s, f, rs, e in out:
        for r in rs:
            by[' '.join(f[3:-1])][0] += 1
            by[' '.join(f[3:-1])][1] += not r['final']
    summ['by_profile'] = dict(by)
    print(json.dumps(summ, indent=1))
    json.dump(dict(summary=summ, rows=out), open(ROOT / 'build/workers/f-alloc-emu/full_validation.json', 'w'), indent=1)
    n = 0
    for s, f, rs, e in out:
        for r in rs:
            if r['final'] and n < 40:
                n += 1
                print('MISMATCH', s, r['function'], 'split_seen' if r['split_seen'] else '', 'split', r['split'], 'repick', r['repick'], 'final', r['final'])
