"""Sweep declaration orders (locals, file-scope externs) over the whole near-exact wall with the emulator.

Rationale (RE of C23216): commutative operands are ordered by 0x432a74 keys built
from symbol sequence numbers (declaration order), and the global allocator's
candidate creation order (its tie-break) follows the resulting tree walk.
"""
import sys, json, random, itertools, time, re
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'build/workers/f-alloc-emu'))
import declperm

OUT = ROOT / 'build/workers/f-alloc-emu/declsweep'


def variants(src, fname, budget=400, seed=1):
    rnd = random.Random(seed)
    out = []
    try:
        bs, end, decls = declperm.function_decls(src, fname)
        single = [d for s in decls for d in declperm.split_declarators(s)]
    except SystemExit:
        bs = end = None
        single = []
    local_texts = [src]
    if single and len(single) > 1:
        perms = list(itertools.permutations(range(len(single)))) if len(single) <= 6 else None
        if perms is None:
            seen = set()
            base = list(range(len(single)))
            while len(seen) < min(budget // 2, 2000):
                rnd.shuffle(base)
                seen.add(tuple(base))
            perms = list(seen)
        rnd.shuffle(perms)
        for p in perms[:budget // 2]:
            local_texts.append(declperm.render(src, bs, end, [single[i] for i in p]))
    out += local_texts
    lines, idx = declperm.extern_block(src)
    if len(idx) > 1:
        ext = [lines[i] for i in idx]
        for _ in range(budget // 2):
            base = rnd.choice(local_texts)
            bl, bidx = declperm.extern_block(base)
            order = list(range(len(ext)))
            rnd.shuffle(order)
            t2 = list(bl)
            for k, i in enumerate(bidx):
                t2[i] = ext[order[k]]
            out.append('\n'.join(t2))
    return list(dict.fromkeys(out))


def job(args):
    sym, text = args
    import esearch
    try:
        r = esearch.evaluate(text.encode('latin1'), sym)
    except Exception as e:
        r = dict(result='ERROR', err=str(e)[:100])
    return sym, text, r


def main():
    wall = json.load(open(ROOT / 'build/workers/f-alloc-emu/wall.json'))
    budget = int(sys.argv[1]) if len(sys.argv) > 1 else 300
    only = set(sys.argv[2:])
    OUT.mkdir(parents=True, exist_ok=True)
    tasks = []
    base = {}
    for sym, ops, byt, reg, stack, mem, path in wall:
        if only and sym not in only:
            continue
        src = (ROOT / path).read_text(encoding='latin1')
        fname = sym.lstrip('_')
        vs = variants(src, fname, budget)
        base[sym] = (ops, reg, stack)
        tasks += [(sym, v) for v in vs]
    print('tasks', len(tasks), flush=True)
    best = {}
    t0 = time.time()
    with Pool(12) as p:
        for sym, text, r in p.imap_unordered(job, tasks, chunksize=4):
            rk = declperm.rank(r)
            if sym not in best or rk > best[sym][0]:
                best[sym] = (rk, r, text)
                if rk[0] >= 2:
                    (OUT / (sym.lstrip('_') + '_exact.c')).write_text(text, encoding='latin1')
                    print('EXACT', sym, json.dumps(r)[:200], flush=True)
    rows = []
    for sym, (rk, r, text) in sorted(best.items()):
        (OUT / (sym.lstrip('_') + '_best.c')).write_text(text, encoding='latin1')
        rows.append(dict(symbol=sym, base=base[sym], best_rank=rk, best=r))
    json.dump(rows, open(OUT / 'summary.json', 'w'), indent=1)
    print('done in', round(time.time() - t0), 's')
    for row in rows:
        b = row['base']
        r = row['best']
        print(row['symbol'], 'base', b, '->', r.get('opcodes'), 'reg', r.get('reg'), 'stack', r.get('stack'), row['best_rank'])


if __name__ == '__main__':
    main()
