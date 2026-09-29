"""Declaration-order permuter on the emulated compiler.

MSC 7.00 C2 orders the operands of commutative operators by a key whose low
word is built from symbol sequence numbers (sym+6), i.e. declaration order
(sortnode.c, 0x432a74).  That order also fixes the walk order in which the
global register allocator creates its candidates, and so the tie order among
equal weights.  This tool tries local (and optionally file-scope extern)
declaration orders of one function and scores each with the symbol's profile.
"""
import argparse, itertools, json, random, re, sys, time
from multiprocessing import Pool
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'build/workers/f-alloc-emu'))

DECL_RE = re.compile(r'^\s*(?:register\s+|static\s+|volatile\s+|const\s+|unsigned\s+|signed\s+)*'
                     r'(?:int|char|short|long|unsigned|signed|struct\s+\w+|union\s+\w+|[A-Z][A-Za-z0-9_]*|BYTE|WORD|DWORD|BOOL)\b[^;(]*;')


def split_declarators(stmt):
    """'int a, *b = 0;' -> ['int a;', 'int *b = 0;'] (top-level commas only)."""
    stmt = stmt.strip().rstrip(';')
    m = re.match(r'^((?:(?:register|static|volatile|const|unsigned|signed|near|far|struct\s+\w+|union\s+\w+|'
                 r'int|char|short|long|[A-Z][A-Za-z0-9_]*)\s+)+)(.*)$', stmt)
    if not m:
        return [stmt + ';']
    base, rest = m.group(1), m.group(2)
    parts, depth, cur = [], 0, ''
    for ch in rest:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += ch
    parts.append(cur)
    # modifiers like near/far/* belong to declarators; base keeps type words
    return ['%s%s;' % (base, p.strip()) for p in parts]


def function_decls(src, fname):
    m = re.search(r'\b%s\s*\([^)]*\)\s*\{' % re.escape(fname), src)
    if not m:
        raise SystemExit('function %s not found' % fname)
    body_start = m.end()
    pos = body_start
    decls = []
    while True:
        # skip whitespace/comments
        mm = re.match(r'(\s|/\*.*?\*/)*', src[pos:], re.S)
        p2 = pos + mm.end()
        dm = DECL_RE.match(src[p2:])
        if not dm or '=' in dm.group(0) and '(' in dm.group(0):
            break
        decls.append(dm.group(0))
        pos = p2 + dm.end()
    return body_start, pos, decls


def render(src, body_start, end, decl_list):
    return src[:body_start] + '\n' + '\n'.join('    ' + d for d in decl_list) + '\n' + src[end:]


def extern_block(src):
    lines = src.split('\n')
    idx = [i for i, l in enumerate(lines) if re.match(r'^\s*extern\b', l) and l.rstrip().endswith(';')]
    return lines, idx


_SYM = None


def _init(sym):
    global _SYM
    _SYM = sym


def _eval(text):
    import esearch
    try:
        r = esearch.evaluate(text.encode('latin1'), _SYM)
    except Exception as e:
        r = dict(result='ERROR', err=str(e)[:200])
    return text, r


def rank(r):
    if r.get('strict') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
        return (3, 0, 0)
    if r.get('exact_body'):
        return (2, 0, 0)
    try:
        a, b = r['opcodes'].split('/')
        op = int(a) - abs(int(b) - int(a))
    except Exception:
        op = -1
    reg = r.get('reg') or 0
    stack = r.get('stack') or 0
    return (1, op, -(reg + stack))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('symbol')
    ap.add_argument('draft')
    ap.add_argument('--function', help='C function name (default: symbol without _)')
    ap.add_argument('--externs', action='store_true', help='also permute file-scope extern lines')
    ap.add_argument('--limit', type=int, default=720)
    ap.add_argument('--jobs', type=int, default=12)
    ap.add_argument('--out', default=None)
    a = ap.parse_args()
    fname = a.function or a.symbol.lstrip('_')
    src = Path(a.draft).read_text(encoding='latin1')
    body_start, end, decls = function_decls(src, fname)
    single = [d for s in decls for d in split_declarators(s)]
    variants = []
    perms = list(itertools.permutations(range(len(single)))) if len(single) <= 7 else None
    if perms is None or len(perms) > a.limit:
        rnd = random.Random(1)
        seen = set()
        base = list(range(len(single)))
        while len(seen) < a.limit:
            rnd.shuffle(base)
            seen.add(tuple(base))
        perms = sorted(seen)
    texts = []
    for p in perms:
        texts.append(render(src, body_start, end, [single[i] for i in p]))
    if a.externs:
        lines, idx = extern_block(src)
        ext = [lines[i] for i in idx]
        eperms = list(itertools.permutations(range(len(ext))))
        rnd = random.Random(2)
        rnd.shuffle(eperms)
        more = []
        for t in texts[:max(1, a.limit // max(1, min(len(eperms), 24)))]:
            tl = t.split('\n')
            _l, tidx = extern_block(t)
            for ep in eperms[:24]:
                t2 = list(tl)
                for k, i in enumerate(tidx):
                    t2[i] = ext[ep[k]]
                more.append('\n'.join(t2))
        texts += more
    texts = list(dict.fromkeys(texts))
    print('declarations:', single, 'variants:', len(texts), flush=True)
    t0 = time.time()
    best = None
    results = []
    with Pool(a.jobs, initializer=_init, initargs=(a.symbol,)) as pool:
        for text, r in pool.imap_unordered(_eval, texts):
            results.append((rank(r), r, text))
            if best is None or rank(r) > best[0]:
                best = (rank(r), r, text)
                print(round(time.time() - t0, 1), rank(r), json.dumps(r)[:200], flush=True)
                if rank(r)[0] >= 2 and a.out:
                    Path(a.out).write_text(text, encoding='latin1')
    print('done', len(results), 'in', round(time.time() - t0, 1), 's; best', best[0])
    if a.out and best:
        Path(a.out).write_text(best[2], encoding='latin1')
    hist = {}
    for rk, r, t in results:
        hist[str(rk)] = hist.get(str(rk), 0) + 1
    print('rank histogram', hist)


if __name__ == '__main__':
    main()
