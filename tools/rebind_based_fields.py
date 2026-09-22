"""Rebind `Dx8[index + <field offset>]` spellings to the named based arrays.

In some objects (simant1:0000 is the established case) the ant-list fields
are not reached through the `Dx8` symbol's selector word: the original loads
one selector word for the SIMANT_DATA_GROUP segment (a `__based(__segname)`
declaration) and addresses the public arrays AlistX/AlistY/AlistM/AlistT/
AlistS by their absolute offsets, while Dx8/Dy8 keep their own symbol words.
Byte for byte both spellings are identical in isolation; in the object only
the based spelling allocates the right pool words (evidence: the pool block
of simant1:0000 has one segment word C318 used with displacements 0x23A4,
0x2B78 and 0x2F62, and separate words C31C/C31E for Dy8/Dx8).

The tool rewrites `Dx8[EXPR + 0xOFF]` (and `AT((EXPR) + 0xOFF)`-style macro
bodies) where 0xOFF is exactly the MAPSYM offset of a segment-8 public into
`Name[EXPR]`, declares the arrays `__based(__segname("SIMANT_DATA_GROUP"))`,
re-verifies strictly in isolation and writes the reviewed source under
evidence/topology/supervisor-unit-sources/. Nothing is admitted here.
"""
import argparse
import re
from common import ROOT, FormatError

OUT = ROOT / 'evidence/topology/supervisor-unit-sources'
SEGMENT = 'SIMANT_DATA_GROUP'


def segment8_publics():
    import mapsym
    from common import fixture
    s = mapsym.parse(fixture('SIMANTW.SYM'))
    seg = s['segments'][7]
    return {x['offset']: x['name'].lstrip('_') for x in seg['symbols'] if x['offset'] >= 0x100}


def rebind(text, fields, element='unsigned char'):
    replaced = {}
    used = set()
    def swap(m):
        expr, lit = m.group(1).strip(), m.group(2)
        off = int(lit, 16 if lit.lower().startswith('0x') else 10)
        name = fields.get(off)
        if not name:
            return m.group(0)
        used.add(name)
        replaced[m.group(0)] = '%s[%s]' % (name, expr)
        return '%s[%s]' % (name, expr)
    pattern = re.compile(r'\bDx8\s*\[\s*([^\[\]]+?)\s*\+\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\]')
    body = pattern.sub(swap, text)
    # direct uses of an AT(off) accessor macro over Dx8: AT(expr + 0xOFF)
    if re.search(r'#define\s+AT\s*\(', body):
        body = re.sub(r'\bAT\s*\(\s*([^()]+?)\s*\+\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\)', swap, body)
    # macro spellings: #define NAME(i) AT((i) + 0xOFF) with #define AT(off) Dx8[off]
    at = re.search(r'#define\s+AT\s*\(\s*(\w+)\s*\)\s*Dx8\s*\[\s*\1\s*\]', body)
    if at:
        def swap_macro(m):
            off = int(m.group(3), 16 if m.group(3).lower().startswith('0x') else 10)
            name = fields.get(off)
            if not name:
                return m.group(0)
            used.add(name)
            replaced[m.group(0)] = '#define %s(%s) %s[%s]' % (m.group(1), m.group(2), name, m.group(2))
            return '#define %s(%s) %s[%s]' % (m.group(1), m.group(2), name, m.group(2))
        body = re.sub(r'#define\s+(\w+)\s*\(\s*(\w+)\s*\)\s*AT\s*\(\s*\(\s*\2\s*\)\s*\+\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\)', swap_macro, body)
    if not replaced:
        return text, replaced
    decls = ''.join('extern %s __based(__segname("%s")) %s[];\n' % (element, SEGMENT, n) for n in sorted(used))
    m = re.search(r'extern[^\n]*\bDx8\b[^\n]*\n', body)
    body = body[:m.end()] + decls + body[m.end():] if m else decls + body
    body = body.replace('/*\n', '/*\n * Unit review: in this object the ant-list fields are the public based\n * arrays %s of %s (one segment selector word), not\n * displacements from Dx8; Dx8/Dy8 keep their own selector words.\n *\n' % (', '.join(sorted(used)), SEGMENT), 1)
    return body, replaced


def main(symbol, verify=True, element='unsigned char'):
    import tu_assembly as tu
    import compiler_profiles as cp
    from codegen_grinder import run
    preserved = tu.preserved_sources()
    if symbol not in preserved:
        raise FormatError('no preserved source for ' + symbol)
    text = (ROOT / preserved[symbol]['source']).read_text(encoding='latin1')
    body, replaced = rebind(text, segment8_publics(), element)
    if not replaced:
        print(symbol, 'no Dx8 field displacements found')
        return None
    OUT.mkdir(parents=True, exist_ok=True)
    path = OUT / (symbol.lstrip('_') + '.c')
    path.write_text(body, encoding='latin1')
    result = None
    if verify:
        comp = cp.component_of(symbol) or {}
        flags = cp.profile_flags(cp.resolve(symbol)['name'], comp.get('segment'))
        report = run(dict(symbol=symbol, source=path.relative_to(ROOT).as_posix(), compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[symbol]),
                     'build/experiments/rebind/' + symbol.lstrip('_'), cache=True)
        c = report['results'][0]['comparison']
        result = dict(result=c['result'], exact_body=tu.body_exact(c), issues=c.get('issues', [])[:4])
    print(symbol, replaced, result)
    return dict(source=path.relative_to(ROOT).as_posix(), replaced=replaced, verification=result)


if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('symbols', nargs='+')
    p.add_argument('--element', default='unsigned char')
    p.add_argument('--no-verify', action='store_true')
    args = p.parse_args()
    for s in args.symbols:
        main(s, verify=not args.no_verify, element=args.element)
