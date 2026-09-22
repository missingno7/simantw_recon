"""Rebind `match_position[K]`-style PACK accesses to the MAPSYM object they address.

`match_position` is the first public of the PACK segment; several isolated
recoveries reached other PACK words as `match_position[K]` (K words further).
In isolation that matches byte for byte (the displacement resolves), but the
object truth is one selector-pool word *per symbol*: the original loaded the
word of `ListIndexB`, not a second use of `match_position`'s word. In a unit
that binding allocates the wrong pool words, so the unit proves the isolated
recipe wrong (offset is not identity).

This tool rewrites such accesses in a preserved source to the exact MAPSYM
symbol located at PACK offset 2*K (only when a public symbol sits exactly
there and the access is a scalar word read/write), declares it, re-verifies
the result strictly in isolation, and writes the reviewed source under
evidence/topology/supervisor-unit-sources/. Nothing is admitted here.
"""
import argparse
import re
from common import ROOT, FormatError, read_json, write_json

OUT = ROOT / 'evidence/topology/supervisor-unit-sources'
PATTERN = re.compile(r'\bmatch_position\s*\[\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\]')


def pack_symbols():
    import mapsym
    from common import fixture
    s = mapsym.parse(fixture('SIMANTW.SYM'))
    pack = next(seg for seg in s['segments'] if seg['name'] == 'PACK')
    return {x['offset']: x['name'].lstrip('_') for x in pack['symbols']}


def rebind(text, symbols):
    """Exact symbol at 2K becomes the scalar; a word inside a public object
    (between it and the next public) becomes `Name[(2K-off)/2]`."""
    replaced = {}
    arrays = set()
    offsets = sorted(symbols)
    def swap(m):
        k = int(m.group(1), 16 if m.group(1).lower().startswith('0x') else 10)
        address = 2 * k
        name = symbols.get(address)
        if name and name != 'match_position':
            replaced[m.group(0)] = name
            return name
        below = [o for o in offsets if o < address]
        if not below:
            return m.group(0)
        base = below[-1]
        owner = symbols[base]
        if owner == 'match_position' or (address - base) % 2:
            return m.group(0)
        arrays.add(owner)
        expr = '%s[%d]' % (owner, (address - base) // 2)
        replaced[m.group(0)] = expr
        return expr
    body = PATTERN.sub(swap, text)
    if not replaced:
        return text, replaced
    names = sorted({v.split('[')[0] for v in replaced.values()})
    decls = ''.join(('extern int far %s[];\n' if n in arrays else 'extern int far %s;\n') % n for n in names)
    # declare right after the match_position declaration when present, else before the first definition
    m = re.search(r'extern[^\n]*\bmatch_position\b[^\n]*\n', body)
    if m:
        body = body[:m.end()] + decls + body[m.end():]
    else:
        i = body.find('\nvoid ')
        i = i if i >= 0 else body.find('\nint ')
        body = body[:i + 1] + decls + body[i + 1:]
    body = body.replace('/*\n', '/*\n * Unit review: PACK words reached as match_position[K] are the public\n * symbols %s (one selector word per symbol in the object).\n *\n' % ', '.join('%s -> %s' % kv for kv in sorted(replaced.items())), 1)
    return body, replaced


def main(symbol, out_name=None, verify=True):
    import tu_assembly as tu
    import compiler_profiles as cp
    from codegen_grinder import run
    preserved = tu.preserved_sources()
    if symbol not in preserved:
        raise FormatError('no preserved source for ' + symbol)
    text = (ROOT / preserved[symbol]['source']).read_text(encoding='latin1')
    body, replaced = rebind(text, pack_symbols())
    if not replaced:
        print(symbol, 'no match_position[K] accesses to a public PACK symbol')
        return None
    OUT.mkdir(parents=True, exist_ok=True)
    path = OUT / ((out_name or symbol.lstrip('_')) + '.c')
    path.write_text(body, encoding='latin1')
    result = None
    if verify:
        comp = cp.component_of(symbol) or {}
        flags = cp.profile_flags(cp.resolve(symbol)['name'], comp.get('segment'))
        report = run(dict(symbol=symbol, source=path.relative_to(ROOT).as_posix(), compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[symbol]),
                     'build/experiments/rebind/' + symbol.lstrip('_'), cache=True)
        c = report['results'][0]['comparison']
        result = dict(result=c['result'], exact_body=tu.body_exact(c), issues=c.get('issues', [])[:4])
        tu.record_reviewed_source(symbol, path, note=__doc__.strip().splitlines()[0])
    print(symbol, replaced, result)
    return dict(source=path.relative_to(ROOT).as_posix(), replaced=replaced, verification=result)


if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('symbols', nargs='+')
    p.add_argument('--no-verify', action='store_true')
    args = p.parse_args()
    for s in args.symbols:
        main(s, verify=not args.no_verify)
