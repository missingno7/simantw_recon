"""DOS SimAnt cross-version reference: byte-exact DOS C (MSC 6.00A) for Win16 functions.

    python tools/xver.py list [--open]          # paired Win16 symbols with an exact DOS C function
    python tools/xver.py show SYMBOL            # the DOS function source and pair evidence

The DOS reconstruction (D:\\Prog\\simant_recon, override with $SIMANT_DOS_ROOT) proves some
functions byte-exact under MSC 6.00A and pairs them with Win16 functions by shared strings,
constants and call order (its evidence/cross_version/simantw_correspondence.json). A byte-exact
DOS function fixes the original SOURCE SHAPE of the shared Maxis code: statement order, loop form,
which expressions are named temporaries and which are repeated (MSC7-R0/A7), array indexing form.

This is supporting evidence only. It never names Windows source text, and the DOS names of
unrecovered callees/globals are address names (f_SSSS_OOOO, fd_SSSS_OOOO) that must be mapped
to the Win16 names the draft already uses. Nothing here is a gate.
"""
import argparse
import json
import os
import sys
from functools import lru_cache
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import FormatError, recipes

DOS_ROOT = Path(os.environ.get('SIMANT_DOS_ROOT', r'D:\Prog\simant_recon'))
CONFIDENCE_ORDER = {'CONFIRMED': 0, 'HIGH': 1, 'MEDIUM': 2, 'LOW': 3}


@lru_cache(maxsize=1)
def exact_dos_functions():
    """{DOS address 'unit:SEG:OFF': claim} for byte-exact DOS C claims."""
    path = DOS_ROOT / 'layout/manifest.json'
    if not path.exists():
        return {}
    manifest = json.loads(path.read_text(encoding='utf-8'))
    out = {}
    for module in manifest.get('modules', {}).values():
        for claim in module.get('claims', []):
            if claim.get('kind') == 'C':
                key = '%s:%04X:%04X' % (claim['unit'], claim['seg'], claim['off'])
                out[key] = dict(claim, source=module['source'], flags=module.get('flags'), profile=module.get('profile'))
    return out


@lru_cache(maxsize=1)
def pairs():
    path = DOS_ROOT / 'evidence/cross_version/simantw_correspondence.json'
    if not path.exists():
        return []
    return json.loads(path.read_text(encoding='utf-8')).get('pairs', [])


def references(symbol=None):
    """Pairs whose DOS side is byte-exact C, best confidence first."""
    exact = exact_dos_functions()
    rows = []
    for p in pairs():
        claim = exact.get(p.get('dos_address'))
        if not claim or (symbol and p.get('win16') != symbol):
            continue
        rows.append(dict(win16=p['win16'], dos=p.get('dos'), dos_function=claim['name'], dos_address=p['dos_address'],
                         confidence=p.get('confidence'), mutual_best=p.get('mutual_best'), evidence=(p.get('evidence') or [])[:4],
                         dos_source=str(DOS_ROOT / claim['source']), dos_size=claim.get('size'), dos_flags=claim.get('flags'),
                         dos_provenance=claim.get('provenance')))
    rows.sort(key=lambda r: (CONFIDENCE_ORDER.get(r['confidence'], 9), r['win16']))
    return rows


def function_text(path, name):
    import c_source
    text = Path(path).read_text(encoding='latin1')
    for f in c_source.top_level_functions(text):
        if f['name'] == name:
            return text[f['header_start']:f['body_end'] + 1]
    return None


def triage_evidence(symbol):
    """Compact reference for triage.py (None when the DOS project has no exact paired function)."""
    rows = references(symbol)
    if not rows:
        return None
    r = rows[0]
    return dict(status='DOS_EXACT_REFERENCE', confidence=r['confidence'], dos_function=r['dos_function'], dos_source=r['dos_source'],
                command='python tools/xver.py show %s' % symbol,
                use=('byte-exact DOS C of the same Maxis function (MSC 6.00A): take its source SHAPE (statement order, loops, '
                     'array indexing, which expressions are named vs repeated) into the Win16 draft, mapping address names '
                     'to the Win16 names; supporting evidence, never Windows source text'))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='command', required=True)
    p = sub.add_parser('list'); p.add_argument('--open', action='store_true', help='only Win16 functions not yet admitted')
    p = sub.add_parser('show'); p.add_argument('symbol')
    args = ap.parse_args()
    if args.command == 'list':
        admitted = recipes()
        rows = [r for r in references() if not args.open or r['win16'] not in admitted]
        for r in rows:
            print('%-10s %-24s %-16s %5s  %s' % (r['confidence'], r['win16'], r['dos_function'], r['dos_size'], r['dos_source']))
        print('%d pairs' % len(rows))
    else:
        rows = references(args.symbol)
        if not rows:
            raise FormatError('no byte-exact DOS function is paired with ' + args.symbol)
        for r in rows:
            print('// %s  <->  DOS %s (%s, %s bytes, %s)\n// evidence: %s' % (r['win16'], r['dos_function'], r['confidence'], r['dos_size'],
                                                                             ' '.join(r['dos_flags'] or []), '; '.join(r['evidence'])))
            print(function_text(r['dos_source'], r['dos_function']) or '(function text not found in %s)' % r['dos_source'])


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
