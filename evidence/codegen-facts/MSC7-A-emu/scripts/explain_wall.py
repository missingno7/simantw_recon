"""For every near-exact wall draft: which register substitutions the target needs, and the
allocator facts (weights, ties, creation order) behind the draft's current choice."""
import sys, json, re, collections
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'build/workers/f-alloc-emu'))

REGS = ['ax', 'bx', 'cx', 'dx', 'si', 'di', 'al', 'ah', 'bl', 'bh', 'cl', 'ch', 'dl', 'dh']
RX = re.compile(r'\b(%s)\b' % '|'.join(REGS))


def subst_pairs(rows):
    pairs = collections.Counter()
    for row in rows:
        if 'register_allocation' not in (row.get('differences') or []):
            continue
        t = RX.findall(row.get('target') or '')
        c = RX.findall(row.get('candidate') or '')
        if len(t) == len(c):
            for a, b in zip(c, t):
                if a != b:
                    pairs[(a, b)] += 1
    return pairs


def job(item):
    sym, path = item
    import esearch
    import alloc_trace as AT
    src = (ROOT / path).read_bytes()
    try:
        r = esearch.full(src, sym)
        rows = r['diagnostic']['aligned_asm']
        pairs = subst_pairs(rows)
        _res, fns = AT.trace_source(src, esearch.flags_for(sym))
        fn = next((f for f in fns if f['function'] == sym.lstrip('_')), fns[-1] if fns else None)
        table = AT.candidate_table(fn) if fn else []
        word = [dict(id=c['id'], name=c['name'], final=c['regname'], picked=c.get('picked'), weight=c['weight'],
                     uses=c['uses'], degree=c['degree'], depth=c['depth'], order=c.get('order'),
                     blocks='%s-%s' % (c['first'], c['last']))
                for c in table if c.get('cls') == 2 or (c.get('lists', {}).get('before_colour') in ('work2', 'alloc2'))]
        # ties among ranges that ended in si/di
        sidi = [w for w in word if w['final'] in ('si', 'di')]
        ties = collections.defaultdict(list)
        for w in word:
            ties[w['weight']].append(w)
        tie_groups = [[(x['name'], x['final'], x['order']) for x in g] for wgt, g in ties.items()
                      if len(g) > 1 and any(x['final'] in ('si', 'di', 'bx', 'cx', 'dx') for x in g) and wgt > 0x8000]
        return dict(symbol=sym, draft=path, substitutions={'%s->%s' % k: v for k, v in pairs.items()},
                    sidi=sidi, ties=tie_groups, candidates=word)
    except Exception as e:
        return dict(symbol=sym, draft=path, error=repr(e)[:300])


if __name__ == '__main__':
    wall = json.load(open(ROOT / 'build/workers/f-alloc-emu/wall.json'))
    items = [(w[0], w[6]) for w in wall]
    with Pool(12) as p:
        out = list(p.imap_unordered(job, items))
    out.sort(key=lambda d: d['symbol'])
    json.dump(out, open(ROOT / 'build/workers/f-alloc-emu/wall_explain.json', 'w'), indent=1)
    for d in out:
        if 'error' in d:
            print(d['symbol'], 'ERROR', d['error'][:100])
            continue
        print('%-24s subst %s' % (d['symbol'], d['substitutions']))
        for w in d['sidi']:
            print('    %-14s %-3s w=%5x uses=%-3d deg=%-2d depth=%d order=%s blk=%s' % (
                w['name'], w['final'], w['weight'], w['uses'], w['degree'], w['depth'], w['order'], w['blocks']))
        if d['ties']:
            print('    ties:', d['ties'][:4])
