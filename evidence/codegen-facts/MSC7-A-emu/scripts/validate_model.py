"""Validate tools/regalloc_model.py against C2's own colouring on every admitted msc700 source."""
import sys, json, time
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools'))


def job(item):
    src, flags = item
    import regalloc_model as RM
    try:
        _r, fns = RM.capture((ROOT / src).read_bytes(), list(flags))
        rows = RM.compare(fns)
        return src, flags, [dict(function=r['function'], cls=r['cls'], n=r['candidates'],
                                 mismatches=r['mismatches'],
                                 si_di=sum(1 for v in r['actual'].values() if v in (6, 7))) for r in rows], None
    except Exception as e:
        return src, flags, [], repr(e)[:300]


if __name__ == '__main__':
    targets = json.load(open(ROOT / 'src/recovery.json'))['targets']
    jobs = sorted({(v['source'], tuple(v['flags'])) for v in targets.values()
                   if v.get('compiler') == 'msc700' and v.get('proof') == 'BYTE_MATCHED_RECONSTRUCTION'})
    t = time.time()
    out = []
    with Pool(12) as p:
        for r in p.imap_unordered(job, jobs):
            out.append(r)
    funcs = [row for _s, _f, rows, _e in out for row in rows]
    ok = [r for r in funcs if not r['mismatches']]
    prof = {}
    for s, f, rows, e in out:
        key = ' '.join(f[3:-1])
        for r in rows:
            d = prof.setdefault(key, [0, 0])
            d[0] += 1
            d[1] += not r['mismatches']
    errors = [(s, e) for s, f, rows, e in out if e]
    si = [r for r in funcs if r['si_di']]
    si_ok = [r for r in si if not r['mismatches']]
    cands = sum(r['n'] for r in funcs)
    cmis = sum(len(r['mismatches']) for r in funcs)
    summary = dict(sources=len(jobs), function_classes=len(funcs), exact_function_classes=len(ok),
                   with_si_di=len(si), with_si_di_exact=len(si_ok), candidates=cands, candidate_mismatches=cmis,
                   by_profile=prof, errors=errors, seconds=round(time.time() - t, 1))
    print(json.dumps(summary, indent=1))
    json.dump(dict(summary=summary, rows=out), open(ROOT / 'build/workers/f-alloc-emu/model_validation.json', 'w'),
              indent=1)
    for s, f, rows, e in out:
        for r in rows:
            if r['mismatches']:
                print('MISMATCH', s, r['function'], r['cls'], r['mismatches'])
