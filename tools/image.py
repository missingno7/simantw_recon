"""Whole-executable hybrid image: every byte of SIMANTW.EXE has exactly one owner.

    python tools/image.py              # rebuild, check HYBRID_EXACT, print totals by owner/lane
    python tools/image.py --debt       # also list every raw interval (the remaining work)

Owners:
  C              bytes regenerated from admitted game objects (build/recovered/*.obj)
  RUNTIME        bytes regenerated from complete historical library members
  NE_CHAIN       NE relocation-chain words at loader sites (linker metadata, lane LINK)
  RAW:<lane>     explicit reconstruction debt copied from the oracle, classified by lane

Object bytes are produced by a small binder: the object's initialized data, the
LINK far-call translation, and every fixup resolved to its independently
grounded target (the same rules the strict matcher validates). Chain words come
from the NE relocation metadata, never from an object. The hybrid image is
HYBRID_EXACT only when it equals the oracle byte for byte; raw debt is explicit
and is never recovery credit.
"""
import argparse
import json
import sys
from array import array
from collections import Counter, defaultdict
from common import ROOT, FormatError, cards, fixture, identity, read_json, sha256, write_json
from library_match import compare_member, import_symbols
import mapsym
import ne
import omf

LANES = {
    'GAME_CODE': 'unrecovered game function (search/promote)',
    'CODE_GAP': 'code bytes outside every known function extent (alignment, tails, unknown entries)',
    'RUNTIME_CODE': 'library/runtime code not yet matched to a complete historical member',
    'DATA': 'initialized data not yet owned by an admitted object',
    'LINK': 'NE header, tables, relocation tables and file padding (authentic LINK + DEF)',
    'RESOURCES': 'resource table and resource data (authentic RC)',
    'MERGE': 'bytes claimed by two admitted objects; combine them in one unit (not raw, but blocks a real link)',
}


def regenerate(module, raw, image, symbols, imports):
    """Bytes an admitted object contributes, keyed by (segment number, offset)."""
    comparison = compare_member(module, raw, image, symbols, imports, allow_data=True)
    if not comparison or comparison['result'] not in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
        raise FormatError('object is not a complete member: %s' % ((comparison or {}).get('issues') or 'unplaced'))
    placed = {}
    by_name = {s['name']: s for s in module['segments']}
    for contribution in comparison['contributions']:
        segment = contribution['original_segment']; base = contribution['original_offset']
        data = bytearray.fromhex(by_name[contribution['segment']]['data_hex'])
        chain_sites = set()
        for row in contribution['fixups']:
            if not row['equal']:
                raise FormatError('unequal fixup in admitted object')
            p = row['offset']; target = row['target']; reason = row['reason']
            if reason in ('resolved offset and frame', 'MAPSYM absolute symbol', 'far code symbol offset in its own segment frame; selector half required'):
                data[p:p + 2] = (target['offset'] & 0xFFFF).to_bytes(2, 'little')
            elif reason == 'same-segment relative offset':
                data[p:p + 2] = ((target['offset'] - (base + p + 2)) & 0xFFFF).to_bytes(2, 'little')
            elif reason == 'NE selector relocation + offset':
                data[p:p + 2] = (target['offset'] & 0xFFFF).to_bytes(2, 'little'); chain_sites.add(p + 2)
            elif reason in ('NE selector for independently named target', 'NE pointer relocation', 'NE imported offset/absolute value'):
                chain_sites.add(p)
            elif reason.startswith('calibrated '):
                pass  # additive OS fixup: the instruction bytes themselves are the file bytes
            elif reason != 'LINK same-segment far call/jump translation':
                raise FormatError('binder has no rule for fixup reason: ' + reason)
        for t in contribution['transformations']:
            # The record names the opcode byte; the matcher's displacement origin is the next byte.
            p = t['offset']; opcode = data[p]; dest = t['target']['offset']
            if opcode == 0x9A:
                data[p:p + 5] = b'\x90\x0e\xe8' + ((dest - (base + p + 5)) & 0xFFFF).to_bytes(2, 'little')
            elif opcode == 0xEA:
                data[p:p + 5] = b'\xe9' + ((dest - (base + p + 3)) & 0xFFFF).to_bytes(2, 'little') + b'\x90\x90'
            else:
                raise FormatError('unknown far transfer translation')
        for a, b in contribution['initialized_ranges']:
            for i in range(a, b):
                placed[(segment, base + i)] = (data[i], i in chain_sites or (i - 1) in chain_sites)
    return comparison, placed


def build(debt=False, manifest=None, write=True):
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    size = len(raw)
    hybrid = bytearray(size)
    owner = array('i', [-1]) * size
    owners = []

    def add_owner(kind, label, lane=None):
        owners.append(dict(kind=kind, label=label, lane=lane)); return len(owners) - 1

    # Container regions: everything outside segment data is linker/RC output.
    for region in image['file_regions']:
        if region['kind'] == 'SEGMENT':
            continue
        lane = 'RESOURCES' if region['kind'].startswith('RESOURCE') else 'LINK'
        o = add_owner('RAW', region['kind'], lane)
        for i in range(region['start'], region['end']):
            owner[i] = o; hybrid[i] = raw[i]
    # Relocation-chain words at every non-additive loader site.
    chain = add_owner('NE_CHAIN', 'NE relocation chains', 'LINK')
    chain_words = {}
    for seg in image['segments']:
        for r in seg['relocations']:
            if r['additive']:
                continue
            for k, site in enumerate(r['sites']):
                word = r['sites'][k + 1] if k + 1 < len(r['sites']) else 0xFFFF
                chain_words[(seg['number'], site)] = word
                for j, byte in enumerate(word.to_bytes(2, 'little')):
                    at = seg['file_offset'] + site + j
                    owner[at] = chain; hybrid[at] = byte

    manifest = manifest or read_json(ROOT / 'build/recovered/manifest.json')
    symbols_of = defaultdict(list)
    for row in manifest['game_objects']:
        symbols_of[row['object']].append(row['symbol'])
    seen = {}
    objects = [(row['object'], 'C', row['symbol']) for row in manifest['game_objects']] + \
              [(row['object'], 'RUNTIME', row['member']) for row in manifest['runtime_objects']]
    problems = []
    conflicts = Counter()
    for path, kind, label in objects:
        digest = identity(ROOT / path)['sha256']
        if digest in seen:
            continue
        module = omf.parse((ROOT / path).read_bytes())
        o = add_owner(kind, ', '.join(sorted(symbols_of[path])) if kind == 'C' else label)
        seen[digest] = o
        try:
            _, placed = regenerate(module, raw, image, symbols, imports)
        except FormatError as exc:
            problems.append('%s %s: %s' % (kind, owners[o]['label'], exc)); continue
        for (segment, offset), (byte, is_chain) in placed.items():
            at = image['segments'][segment - 1]['file_offset'] + offset
            if is_chain:
                if owner[at] != chain:
                    problems.append('%s claims a loader site the relocation table does not name at seg %d:%04X' % (owners[o]['label'], segment, offset))
                continue
            if owner[at] not in (-1, chain):
                # Two admitted objects prove the same bytes (a private literal
                # declared twice, or an older unit still owning superseded code).
                # The bytes must agree; a real LINK cannot take both objects.
                if hybrid[at] != byte:
                    problems.append('conflicting bytes at seg %d:%04X (%s / %s)' % (segment, offset, owners[owner[at]]['label'], owners[o]['label']))
                conflicts[(owners[owner[at]]['label'], owners[o]['label'])] += 1
                continue
            if owner[at] == chain:
                problems.append('object byte at loader chain site seg %d:%04X (%s)' % (segment, offset, owners[o]['label']))
                continue
            owner[at] = o; hybrid[at] = byte

    # Classify the remaining raw debt.
    code_symbol = {}
    for card in cards():
        seg = image['segments'][card['segment'] - 1]
        end = card['extent']['end'] or card['extent'].get('upper_bound') or card['offset']
        lane = 'GAME_CODE' if card['ownership'] == 'GAME' else 'RUNTIME_CODE'
        for off in range(card['offset'], end):
            code_symbol.setdefault(seg['file_offset'] + off, (lane, card['symbol']))
    data_symbol = {}
    for seg in symbols['segments']:
        if image['segments'][seg['number'] - 1]['kind'] != 'DATA':
            continue
        ns = image['segments'][seg['number'] - 1]
        ordered = sorted(seg['symbols'], key=lambda p: p['offset'])
        for k, p in enumerate(ordered):
            end = ordered[k + 1]['offset'] if k + 1 < len(ordered) else ns['logical_size']
            for off in range(p['offset'], min(end, ns['logical_size'])):
                data_symbol[ns['file_offset'] + off] = p['name']
    raw_owner = {}
    for seg in image['segments']:
        for off in range(seg['logical_size']):
            at = seg['file_offset'] + off
            if owner[at] != -1:
                continue
            if seg['kind'] == 'DATA':
                lane, label = 'DATA', '%s:%s' % (seg['number'], data_symbol.get(at, '<before first symbol>'))
            else:
                lane, label = code_symbol.get(at, ('CODE_GAP', 'seg%d' % seg['number']))
            key = (lane, label)
            if key not in raw_owner:
                raw_owner[key] = add_owner('RAW', label, lane)
            owner[at] = raw_owner[key]; hybrid[at] = raw[at]
    for i in range(size):
        if owner[i] == -1:
            raise FormatError('unowned byte at file offset %06X' % i)

    mismatches = [i for i in range(size) if hybrid[i] != raw[i]]
    for i in mismatches:
        problems.append('byte %06X differs (%s)' % (i, owners[owner[i]]['label']))
    out = ROOT / 'build/image'
    if write:
        out.mkdir(parents=True, exist_ok=True)
        (out / 'SIMANTW.EXE').write_bytes(hybrid)

    merge = [dict(first=a, second=b, bytes=n) for (a, b), n in conflicts.most_common()]
    totals = Counter(); lanes = Counter(); intervals = []
    start = 0
    for i in range(1, size + 1):
        if i == size or owner[i] != owner[start]:
            info = owners[owner[start]]
            totals[info['kind']] += i - start
            if info['kind'] == 'RAW' or info['kind'] == 'NE_CHAIN':
                lanes[info['lane']] += i - start
            if info['kind'] == 'RAW':
                intervals.append(dict(start=start, end=i, lane=info['lane'], label=info['label']))
            start = i
    code_bytes = sum(s['logical_size'] for s in image['segments'] if s['kind'] == 'CODE')
    report = dict(status='HYBRID_EXACT' if not mismatches and not problems else 'NOT_EXACT', image_sha256=sha256(bytes(hybrid)), oracle_sha256=sha256(raw),
                  file_bytes=size, owned=dict(C=totals['C'], RUNTIME=totals['RUNTIME']), debt=dict(sorted(lanes.items())),
                  debt_total=size - totals['C'] - totals['RUNTIME'], code_segment_bytes=code_bytes,
                  objects=len(seen), problems=problems[:50], problem_count=len(problems), mismatched_bytes=len(mismatches),
                  claim_conflicts=dict(bytes=sum(conflicts.values()), pairs=len(conflicts),
                                       note='bytes proved by two admitted objects; merge them into one unit (lane MERGE) before a real LINK'),
                  scope='HYBRID_EXACT means the image rebuilt from admitted objects plus explicit raw debt equals the oracle; raw debt is not recovery')
    if write:
        write_json(out / 'ledger.json', dict(report, lanes=LANES, intervals=intervals, merge=merge, all_problems=problems))
        summary = {k: report[k] for k in ('status', 'file_bytes', 'owned', 'debt', 'debt_total', 'claim_conflicts')}
        write_json(ROOT / 'docs/image.json', dict(summary, lanes=LANES, detail='build/image/ledger.json (python tools/image.py --debt)'))
    result = dict(report)
    if debt:
        grouped = defaultdict(list)
        for row in intervals:
            grouped[row['lane']].append(row)
        result['intervals'] = {lane: sorted(rows, key=lambda r: -(r['end'] - r['start'])) for lane, rows in grouped.items()}
        result['merge'] = merge
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--debt', action='store_true')
    args = ap.parse_args()
    result = build(args.debt)
    print(json.dumps(result, indent=2))
    if result['status'] != 'HYBRID_EXACT':
        raise SystemExit(1)


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
