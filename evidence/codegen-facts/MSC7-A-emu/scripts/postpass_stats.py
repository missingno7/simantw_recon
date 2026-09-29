"""How often do the post-colouring passes (0x442040/0x442628/0x442fac/0x445f14) change registers?"""
import sys, json, collections
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools'))


def job(item):
    src, flags = item
    import alloc_trace as AT
    try:
        _r, fns = AT.trace_source((ROOT / src).read_bytes(), list(flags))
    except Exception as e:
        return src, None, repr(e)
    out = []
    for fn in fns:
        picked = {}
        unassigned = set()
        repicked = {}
        dropped = set()
        for ev in fn['events']:
            if ev[0] == 'reg' and ev[1] == 2:
                picked[ev[2]] = ev[3]
            if ev[0] == 'unassign' and ev[1] == 2:
                unassigned.add(ev[2])
            if ev[0] == 'drop':
                dropped.add(ev[2])
        final = {}
        for lst, cands in fn['snapshots'].get('final', {}).items():
            for c in cands:
                final[c['id']] = c['regname']
        changed = {cid: (r, final.get(cid)) for cid, r in picked.items() if final.get(cid) != r}
        sidi_changed = {cid: v for cid, v in changed.items() if v[0] in ('si', 'di') or v[1] in ('si', 'di')}
        out.append(dict(function=fn['function'], picked=len(picked), unassigned=len(unassigned), dropped=len(dropped),
                        changed=changed, sidi_changed=sidi_changed))
    return src, out, None


if __name__ == '__main__':
    targets = json.load(open(ROOT / 'src/recovery.json'))['targets']
    jobs = sorted({(v['source'], tuple(v['flags'])) for v in targets.values()
                   if v.get('compiler') == 'msc700' and v.get('proof') == 'BYTE_MATCHED_RECONSTRUCTION'})
    with Pool(12) as p:
        res = list(p.imap_unordered(job, jobs))
    fns = [f for s, out, e in res if out for f in out]
    n = len(fns)
    ch = sum(1 for f in fns if f['changed'])
    sd = sum(1 for f in fns if f['sidi_changed'])
    kinds = collections.Counter()
    for f in fns:
        for cid, (a, b) in f['sidi_changed'].items():
            kinds[(a, b)] += 1
    print(json.dumps(dict(functions=n, with_any_post_change=ch, with_si_di_post_change=sd,
                          si_di_transitions={'%s->%s' % k: v for k, v in kinds.most_common()}), indent=1))
    json.dump(res, open(ROOT / 'build/workers/f-alloc-emu/postpass_stats.json', 'w'), indent=1, default=str)
