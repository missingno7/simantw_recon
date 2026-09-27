"""Diagnostic for unnamed static helpers (no MAPSYM name, no card).

    python tools/static_probe.py SEG:OFFSET candidate.c FUNCTION --like CALLER [--full]

A static helper of an object has no public name, so search.py cannot target it
and its callers cannot become exact while it is missing. This compiles the
candidate (FUNCTION must be defined non-static here, so its offset is visible)
under the compiler profile of CALLER's object, cuts FUNCTION's code, and
compares it with the original bytes at SEG:OFFSET (extent from the recursive
CFG solver, else up to the next MAPSYM entry). Fixup sites are bound on both sides (original relocation targets versus
OMF targets, so immediate/memory 'differences' at fixups are representation only),
and LINK's same-segment far-call translation is applied to the candidate view.

Diagnostic only: proof and credit come from the unit lane, where the helper is
defined `static` inside its object's unit and every byte is compared.
"""
import argparse
import json
from common import ROOT, FormatError, cards, fixture
from codegen_cache import compile_cached
from codegen_diff import compare_code
from cfg_solver import solve
from search import focused_alignment
import compiler_profiles
import mapsym
import ne
import omf


def original_bytes(segment, offset):
    raw = fixture('SIMANTW.EXE')
    image = ne.parse(raw)
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    ns = image['segments'][segment - 1]
    code = raw[ns['file_offset']:ns['file_offset'] + ns['logical_size']]
    entries = sorted({s['offset'] for s in symbols['segments'][segment - 1]['symbols']})
    if offset in entries:
        raise FormatError('%d:%04X is a named entry; use search.py' % (segment, offset))
    upper = min([e for e in entries if e > offset] + [len(code)])
    graph = solve(code, offset, upper, entries, ns['relocations'], segment)
    end = graph['end'] if graph.get('end') and graph.get('status') == 'PROBABLE' else upper
    bindings = {site - offset: r['target'] for r in ns['relocations'] for site in r['sites'] if offset <= site < end}
    names = {s['name']: (i + 1, s['offset']) for i, seg in enumerate(symbols['segments']) for s in seg['symbols']}
    return code[offset:end], bindings, names, dict(end=end, upper=upper, status=graph.get('status'), reasons=graph.get('reasons'))


def candidate_bytes(obj, function, segment=None, offset=None, names=None):
    """The function's code, its fixup bindings, and LINK's same-segment far-call
    translation applied in a diagnostic view (9A far call -> NOP; PUSH CS; CALL near)."""
    module = omf.parse(obj.read_bytes())
    pubs = [p for p in module['publics'] if p['name'].lstrip('_') == function.lstrip('_') and p['segment']]
    if len(pubs) != 1:
        raise FormatError('define %s non-static (once) in the probe source so its offset is visible' % function)
    pub = pubs[0]
    seg = module['segments'][pub['segment'] - 1]
    code = bytes.fromhex(seg['data_hex'])
    following = [p['offset'] for p in module['publics'] if p['segment'] == pub['segment'] and p['offset'] > pub['offset']]
    begin, stop = pub['offset'], min(following + [len(code)])
    closed = solve(code, begin, stop)
    if closed.get('end') and closed.get('status') == 'PROBABLE':
        stop = closed['end']   # drop the compiler's even-alignment padding
    view = bytearray(code[begin:stop])
    bindings = {}
    for f in module['fixups']:
        if f['segment'] != pub['segment'] or not begin <= f['offset'] < stop:
            continue
        pos = f['offset'] - begin
        bindings[pos] = f['target']
        name = (f['target'] or {}).get('name')
        if names is None or segment is None or f['location_type'] != 3 or pos < 1 or view[pos - 1] != 0x9A or name not in names:
            continue
        dest_segment, dest = names[name]
        if dest_segment != segment:
            continue
        at = pos - 1
        view[at:at + 5] = b'\x90\x0e\xe8' + ((dest - (offset + at + 5)) & 0xFFFF).to_bytes(2, 'little')
        bindings.pop(pos)
    return bytes(view), bindings


def probe(address, source, function, like, full=False):
    segment, offset = (int(x, 16) if i else int(x) for i, x in enumerate(address.split(':')))
    caller = next((c for c in cards() if c['symbol'] == like), None)
    if caller is None:
        raise FormatError('unknown caller ' + like)
    if caller['segment'] != segment:
        raise FormatError('%s is in segment %d, not %d' % (like, caller['segment'], segment))
    flags = compiler_profiles.flags_for(like, caller['segment_name'])
    target, target_bindings, names, extent = original_bytes(segment, offset)
    obj, receipt = compile_cached([dict(source=source, flags=flags)], 'msc700')[0][0]
    if obj is None or receipt.get('exit_code'):
        return dict(result='COMPILE_FAILED', log=receipt['stdout'][-1200:])
    candidate, candidate_bindings = candidate_bytes(obj, function, segment, offset, names)
    diff = compare_code(target, candidate, target_bindings, candidate_bindings)
    rows = diff['aligned_asm'] if full else focused_alignment(diff['aligned_asm'])
    return dict(address=address, function=function, flags=flags, target_extent=extent,
                opcodes='%s/%s' % (diff['opcode_matches'], diff['opcode_total']),
                bytes='%d/%d' % (len(candidate), len(target)), identical_bytes=candidate == target,
                register_differences=diff['register_only_differences'], stack_differences=diff['stack_local_differences'],
                immediate_differences=diff['immediate_differences'], memory_differences=diff['memory_operand_differences'],
                branch_differences=diff['branch_target_differences'], first_structural_difference=diff['first_structural_difference'],
                aligned_asm=rows, scope='DIAGNOSTIC ONLY: bytes without fixups; admit the helper as a static inside its unit')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('address', help='SEG:OFFSET of the original helper, e.g. 3:16D4')
    ap.add_argument('source')
    ap.add_argument('function', help='name of the helper as defined (non-static) in the probe source')
    ap.add_argument('--like', required=True, help='a caller in the same object: its compiler profile is used')
    ap.add_argument('--full', action='store_true')
    args = ap.parse_args()
    print(json.dumps(probe(args.address, args.source, args.function, args.like, args.full), indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
