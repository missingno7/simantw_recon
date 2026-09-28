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


def compare_object(address, obj, function, like):
    """Compare an already compiled helper with its unnamed target."""
    segment, offset = (int(x, 16) if i else int(x) for i, x in enumerate(address.split(':')))
    caller = next((c for c in cards() if c['symbol'] == like), None)
    if caller is None:
        raise FormatError('unknown caller ' + like)
    if caller['segment'] != segment:
        raise FormatError('%s is in segment %d, not %d' % (like, caller['segment'], segment))
    target, target_bindings, names, extent = original_bytes(segment, offset)
    candidate, candidate_bindings = candidate_bytes(obj, function, segment, offset, names)
    diff = compare_code(target, candidate, target_bindings, candidate_bindings)
    ordinary_bytes_equal = _ordinary_bytes_equal(
        segment, offset, target, candidate, obj, function, names)
    diff['ordinary_bytes_equal'] = ordinary_bytes_equal
    diff['exact_match'] = ordinary_bytes_equal and len(candidate) == len(target) and all(
        not row.get('differences') or _fixup_only_difference(row)
        for row in diff.get('aligned_asm', []))
    return dict(address=address, function=function, target_extent=extent,
                opcodes='%s/%s' % (diff['opcode_matches'], diff['opcode_total']),
                bytes='%d/%d' % (len(candidate), len(target)), identical_bytes=candidate == target,
                register_differences=diff['register_only_differences'], stack_differences=diff['stack_local_differences'],
                immediate_differences=diff['immediate_differences'], memory_differences=diff['memory_operand_differences'],
                branch_differences=diff['branch_target_differences'], first_structural_difference=diff['first_structural_difference'],
                aligned_asm=diff['aligned_asm'], diagnostic=diff,
                scope='DIAGNOSTIC ONLY: fixup-bound helper body; admit it as a static inside its unit')


def _fixup_only_difference(row):
    differences = set(row.get('differences') or [])
    allowed = {'memory_operand', 'immediate_or_binding', 'alignment_uncertain'}
    target = (row.get('target') or '').lower()
    candidate = (row.get('candidate') or '').lower()
    rendered = 'resolved fixup' in target or 'resolved fixup' in candidate
    selector = 'es:[' in target or 'es:[' in candidate
    return differences <= allowed and (rendered or selector)


def _ordinary_bytes_equal(segment, offset, target, candidate, obj, function, names):
    """Require identical body bytes after masking only bound relocation fields."""
    if len(target) != len(candidate):
        return False
    image = ne.parse(fixture('SIMANTW.EXE'))
    ns = image['segments'][segment - 1]
    ignored = set()
    for relocation in ns['relocations']:
        width = ne.RELOC_WIDTH[relocation['source_type']]
        for site in relocation['sites']:
            if offset <= site < offset + len(target):
                begin = site - offset
                ignored.update(range(begin, min(begin + width, len(target))))

    module = omf.parse(obj.read_bytes())
    pubs = [p for p in module['publics']
            if p['name'].lstrip('_') == function.lstrip('_') and p['segment']]
    if len(pubs) != 1:
        return False
    pub = pubs[0]
    code = bytes.fromhex(module['segments'][pub['segment'] - 1]['data_hex'])
    following = [p['offset'] for p in module['publics']
                 if p['segment'] == pub['segment'] and p['offset'] > pub['offset']]
    stop = min(following + [len(code)])
    closed = solve(code, pub['offset'], stop)
    if closed.get('end') and closed.get('status') == 'PROBABLE':
        stop = closed['end']
    begin = pub['offset']
    for fixup in module['fixups']:
        if fixup['segment'] != pub['segment'] or not begin <= fixup['offset'] < stop:
            continue
        pos = fixup['offset'] - begin
        name = (fixup['target'] or {}).get('name')
        translated = (fixup['location_type'] == 3 and pos >= 1 and
                      code[fixup['offset'] - 1] == 0x9A and name in names and
                      names[name][0] == segment)
        if not translated:
            ignored.update(range(pos, min(pos + fixup['width'], len(candidate))))
    return all(target[index] == candidate[index]
               for index in range(len(target)) if index not in ignored)


def probe(address, source, function, like, full=False):
    caller = next((c for c in cards() if c['symbol'] == like), None)
    if caller is None:
        raise FormatError('unknown caller ' + like)
    flags = compiler_profiles.flags_for(like, caller['segment_name'])
    obj, receipt = compile_cached([dict(source=source, flags=flags)], 'msc700')[0][0]
    if obj is None or receipt.get('exit_code'):
        return dict(result='COMPILE_FAILED', log=receipt['stdout'][-1200:])
    compared = compare_object(address, obj, function, like)
    rows = compared['aligned_asm'] if full else focused_alignment(compared['aligned_asm'])
    return dict(address=address, function=function, flags=flags, target_extent=compared['target_extent'],
                opcodes=compared['opcodes'], bytes=compared['bytes'], identical_bytes=compared['identical_bytes'],
                register_differences=compared['register_differences'], stack_differences=compared['stack_differences'],
                immediate_differences=compared['immediate_differences'], memory_differences=compared['memory_differences'],
                branch_differences=compared['branch_differences'], first_structural_difference=compared['first_structural_difference'],
                aligned_asm=rows, scope=compared['scope'])


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
