"""Whole-executable hybrid image: every byte of SIMANTW.EXE has exactly one owner.

    python tools/image.py              # rebuild, check HYBRID_EXACT, print totals by owner/lane
    python tools/image.py --debt       # also list every raw interval (the remaining work)

Owners:
  C              bytes regenerated from admitted game objects (build/recovered/*.obj)
  RUNTIME        bytes regenerated from complete historical library members
  RESOURCES      payload ranges reproduced by the pinned Microsoft RC 3.00
  LINK           complete NE file regions reproduced by the pinned LINK 5.30
  NE_CHAIN       NE relocation-chain words at loader sites (linker metadata, lane LINK)
  RAW:<lane>     explicit reconstruction debt copied from the oracle, classified by lane

Scaffold stand-ins in admitted unit sources (`SCAFFOLD, not recovered source:
... (DGROUP LO-HI)`) keep a unit's data layout for unclaimed members; their
bytes are strictly compared by the unit gate but stay RAW debt here.

Object bytes are produced by a small binder: initialized data, independently
placed file-backed private FAR_DATA zero-fill, LINK far-call translations, and
fixups resolved to their grounded targets (the same rules the strict matcher
validates). Chain words come from NE relocation metadata, never from an object. The hybrid image is
HYBRID_EXACT only when it equals the oracle byte for byte; raw debt is explicit
and is never recovery credit.
"""
import re
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
import resources as resource_lane
import link_lane

LANES = {
    'GAME_CODE': 'unrecovered game function (search/promote)',
    'CODE_GAP': 'code bytes outside every known function extent (alignment, tails, unknown entries)',
    'RUNTIME_CODE': 'library/runtime code not yet matched to a complete historical member',
    'DATA': 'file-backed data not yet owned by an admitted object',
    'LINK': 'NE header, tables, relocation tables and file padding (authentic LINK + DEF)',
    'RESOURCES': 'resource table and resource bytes not proved by the RC payload admission',
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


def far_bss_claims(module, comparison, raw, image, symbols, occupied=()):
    """Return file-backed zero bytes from independently placed private FAR_DATA.

    LINK stores private FAR_DATA zero-fill contributions inside the logical file
    length when they follow initialized contributions in the same packed far
    data segment. This does not apply to COMDEF/FAR_BSS, which only increases
    minimum allocation. A contribution is eligible only when the member proof
    carries an independent placement basis and there is no public in its span.
    """
    if comparison.get('result') not in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
        raise FormatError('far-BSS claim requires a complete admitted member')
    segments = {s['index']: s for s in module.get('segments', [])}
    public_symbols = symbols.get('segments', [])
    occupied = set(occupied)
    claims = {}
    anchors = comparison.get('anchors', {})
    private = set(comparison.get('private_constraint_placements', []))
    link_evidence = {row.get('segment_index') for row in comparison.get('link_order_placements', [])}
    for contribution in comparison.get('contributions', []):
        si = contribution.get('segment_index')
        source = segments.get(si)
        if source is None:
            raise FormatError('far-BSS contribution has unknown OMF segment index')
        if source.get('class') != 'FAR_DATA' or source.get('name') not in ('PACK', 'SIMANT_DATA_GROUP'):
            continue
        length = source.get('length')
        initialized = source.get('initialized_ranges')
        if (contribution.get('segment') != source.get('name') or
                contribution.get('length') != length or
                contribution.get('initialized_ranges') != initialized):
            raise FormatError('far-BSS contribution size or shape differs from its OMF segment')
        if not isinstance(length, int) or length <= 0:
            raise FormatError('far-BSS contribution has invalid size')
        if not isinstance(initialized, list):
            raise FormatError('far-BSS initialized-range metadata is missing')
        gaps = []
        cursor = 0
        for bounds in sorted(initialized):
            if (not isinstance(bounds, (list, tuple)) or len(bounds) != 2 or
                    not all(isinstance(v, int) for v in bounds)):
                raise FormatError('far-BSS initialized-range metadata is malformed')
            start, end = bounds
            if start < cursor or end < start or end > length:
                raise FormatError('far-BSS initialized ranges overlap or exceed contribution size')
            if cursor < start:
                gaps.append((cursor, start))
            cursor = end
        if cursor < length:
            gaps.append((cursor, length))
        if not gaps:
            continue
        if any(p.get('segment') == si for p in module.get('publics', [])):
            raise FormatError('private FAR_DATA contribution has an OMF public')
        anchor_key = si if si in anchors else str(si)
        has_anchor = bool(anchors.get(anchor_key))
        if not (has_anchor or si in private or si in link_evidence):
            raise FormatError('FAR_DATA contribution order or placement is not independently proven')
        original_segment = contribution.get('original_segment')
        original_offset = contribution.get('original_offset')
        if not isinstance(original_segment, int) or not isinstance(original_offset, int):
            raise FormatError('FAR_DATA contribution has unknown original placement')
        if original_segment < 1 or original_segment > len(image['segments']):
            raise FormatError('FAR_DATA contribution names an unknown original segment')
        target = image['segments'][original_segment - 1]
        if target.get('kind') != 'DATA':
            raise FormatError('FAR_DATA contribution does not target an original data segment')
        end = original_offset + length
        if original_offset < 0 or end > target.get('allocation_size', target.get('logical_size', 0)):
            raise FormatError('FAR_DATA contribution exceeds original allocation')
        if end > target.get('logical_size', 0):
            raise FormatError('FAR_DATA contribution is outside file-backed segment length')
        if original_segment > len(public_symbols):
            raise FormatError('MAPSYM metadata is missing for FAR_DATA segment')
        for public in public_symbols[original_segment - 1].get('symbols', []):
            if original_offset <= public['offset'] < end:
                raise FormatError('private FAR_DATA contribution span contains original public ' + public['name'])
        file_start = target['file_offset'] + original_offset
        for start, stop in gaps:
            for delta in range(start, stop):
                key = (original_segment, original_offset + delta)
                if key in occupied or key in claims:
                    raise FormatError('private FAR_DATA zero-fill overlaps admitted bytes')
                if raw[file_start + delta] != 0:
                    raise FormatError('private FAR_DATA zero-fill disagrees with original file byte')
                claims[key] = 0
    return claims


SCAFFOLD_MARK = re.compile(r'/\*\s*SCAFFOLD, not recovered source:(.*?)\*/', re.S)
SCAFFOLD_RANGE = re.compile(r'DGROUP ([0-9A-F]{4})-([0-9A-F]{4})')


def scaffold_ranges(manifest):
    """Object path -> DGROUP ranges its admitted source marks as scaffold
    stand-ins (`SCAFFOLD, not recovered source: ... (DGROUP LO-HI ...)`).
    Those bytes keep the unit's layout but earn no ownership; a marker whose
    range cannot be read fails closed."""
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    result = {}
    for row in manifest['game_objects']:
        source = recipes.get(row['symbol'], {}).get('source')
        if not source or row['object'] in result:
            continue
        path = ROOT / source
        text = path.read_text(encoding='latin1') if path.exists() else ''
        ranges = []
        for mark in SCAFFOLD_MARK.finditer(text):
            found = SCAFFOLD_RANGE.search(mark.group(1))
            if found:
                ranges.append((int(found.group(1), 16), int(found.group(2), 16)))
            elif 'bytes' in mark.group(1) and 'data' in mark.group(1):
                raise FormatError('scaffold data marker without a DGROUP range in ' + source)
        result[row['object']] = tuple(ranges)
    return result


def build(debt=False, manifest=None, write=True, recovery=None):
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    size = len(raw)
    hybrid = bytearray(size)
    owner = array('i', [-1]) * size
    owners = []
    problems = []

    recovery = recovery or read_json(ROOT / 'src/recovery.json')
    resource_proof, resource_output = resource_lane.load_admission(recovery.get('resources'))
    if isinstance(resource_output, str):
        problems.append(resource_output)
        resource_output = None
    link_proof, link_output = link_lane.load_admission(recovery.get('link'))
    if isinstance(link_output, str):
        problems.append(link_output)
        link_output = None
    resource_rows = {}
    if resource_proof is not None:
        try:
            for row in resource_proof['resources']:
                index = row['oracle_index']
                if index in resource_rows or not isinstance(index, int) or index < 0 or index >= len(image['resources']):
                    raise FormatError('duplicate or out-of-range oracle resource index in admission')
                oracle_row = image['resources'][index]
                target = row['oracle_range']
                if (target.get('start'), target.get('end'), target.get('size')) != \
                        (oracle_row['offset'], oracle_row['offset'] + oracle_row['size'], oracle_row['size']):
                    raise FormatError('admitted oracle range differs from the resource table')
                if row.get('type') in (['id', 15], ('id', 15)):
                    raise FormatError('admission attempts to own RT_NAMETABLE bytes')
                resource_rows[index] = row
        except (FormatError, KeyError, TypeError) as exc:
            problems.append('resource admission mapping invalid: ' + str(exc))
            resource_rows = {}
            resource_proof = None
            resource_output = None
    link_rows = {}
    if link_proof is not None:
        try:
            for row in link_proof['regions']:
                target = row['oracle_range']
                key = (target['start'], target['end'])
                if key in link_rows:
                    raise FormatError('duplicate oracle region in LINK admission')
                link_rows[key] = row
        except (FormatError, KeyError, TypeError) as exc:
            problems.append('LINK admission mapping invalid: ' + str(exc))
            link_rows = {}
            link_proof = None
            link_output = None

    def add_owner(kind, label, lane=None):
        owners.append(dict(kind=kind, label=label, lane=lane)); return len(owners) - 1

    # Container regions: everything outside segment data is linker/RC output.
    for region in image['file_regions']:
        if region['kind'] == 'SEGMENT':
            continue
        if region['kind'] == 'RESOURCE' and region.get('index') in resource_rows and resource_proof is not None:
            mapping = resource_rows[region['index']]
            oracle_row = image['resources'][region['index']]
            source_range = mapping.get('compiled_range', {})
            start, end = source_range.get('start'), source_range.get('end')
            if (not isinstance(start, int) or not isinstance(end, int) or end - start != oracle_row['size'] or
                    start < 0 or end > len(resource_output)):
                problems.append('resource payload source range is invalid for oracle row %d' % region['index'])
                o = add_owner('RAW', region['kind'], 'RESOURCES')
                for i in range(region['start'], region['end']):
                    owner[i] = o; hybrid[i] = raw[i]
                continue
            payload = resource_output[start:end]
            oracle_payload = raw[oracle_row['offset']:oracle_row['offset'] + oracle_row['size']]
            if sha256(payload) != mapping.get('sha256'):
                problems.append('stored RC payload bytes differ from the admitted range for oracle row %d' % region['index'])
            if payload != oracle_payload:
                problems.append('stored RC payload bytes differ from the oracle for resource row %d' % region['index'])
            if sha256(payload) != mapping.get('sha256') or payload != oracle_payload:
                o = add_owner('RAW', region['kind'], 'RESOURCES')
                for i in range(region['start'], region['end']):
                    owner[i] = o; hybrid[i] = raw[i]
                continue
            label = '%s %s' % (oracle_row['type_name'], oracle_row['identity'].get('name', oracle_row['identity'].get('id')))
            o = add_owner('RESOURCES', label, 'RESOURCES')
            for offset, byte in enumerate(payload):
                at = oracle_row['offset'] + offset
                owner[at] = o; hybrid[at] = byte
            continue
        mapping = link_rows.get((region['start'], region['end']))
        if mapping is not None and link_proof is not None:
            source_range = mapping.get('output_range', {})
            start, end = source_range.get('start'), source_range.get('end')
            region_size = region['end'] - region['start']
            if (mapping.get('kind') != region['kind'] or not isinstance(start, int) or
                    not isinstance(end, int) or end - start != region_size or start < 0 or
                    end > len(link_output)):
                problems.append('LINK output range is invalid for oracle region %s' % region['kind'])
                o = add_owner('RAW', region['kind'], 'LINK')
                for i in range(region['start'], region['end']):
                    owner[i] = o; hybrid[i] = raw[i]
                continue
            payload = link_output[start:end]
            oracle_payload = raw[region['start']:region['end']]
            if sha256(payload) != mapping.get('sha256') or payload != oracle_payload:
                problems.append('stored LINK bytes differ from the oracle for region %s' % region['kind'])
                o = add_owner('RAW', region['kind'], 'LINK')
                for i in range(region['start'], region['end']):
                    owner[i] = o; hybrid[i] = raw[i]
                continue
            o = add_owner('LINK', region['kind'], 'LINK')
            for offset, byte in enumerate(payload):
                at = region['start'] + offset
                owner[at] = o; hybrid[at] = byte
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
    scaffold_data = scaffold_ranges(manifest)
    seen = {}
    objects = [(row['object'], 'C', row['symbol']) for row in manifest['game_objects']] + \
              [(row['object'], 'RUNTIME', row['member']) for row in manifest['runtime_objects']]
    conflicts = Counter()
    far_bss_candidates = []
    far_bss_rejections = []
    for path, kind, label in objects:
        digest = identity(ROOT / path)['sha256']
        if digest in seen:
            continue
        module = omf.parse((ROOT / path).read_bytes())
        o = add_owner(kind, ', '.join(sorted(symbols_of[path])) if kind == 'C' else label)
        seen[digest] = o
        try:
            comparison, placed = regenerate(module, raw, image, symbols, imports)
        except FormatError as exc:
            problems.append('%s %s: %s' % (kind, owners[o]['label'], exc)); continue
        try:
            claims = far_bss_claims(module, comparison, raw, image, symbols)
            if claims:
                far_bss_candidates.append((o, owners[o]['label'], claims))
        except FormatError as exc:
            far_bss_rejections.append(dict(owner=owners[o]['label'], object=path, reason=str(exc)))
        stand_in = scaffold_data.get(path, ())
        for (segment, offset), (byte, is_chain) in placed.items():
            if segment == 10 and any(lo <= offset < hi for lo, hi in stand_in):
                # Layout stand-in for unclaimed members' data (a scaffold filler
                # copied from the image): compared by the unit gate, never owned.
                continue
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

    # File-backed FAR_DATA zero-fill is a distinct contribution from the
    # initialized bytes emitted by regenerate(). Resolve these only after all
    # initialized owners are known so an overlap cannot be hidden by link order.
    far_bss_claimed = {}
    for o, label, claims in far_bss_candidates:
        collision = next((key for key in claims if
                          owner[image['segments'][key[0] - 1]['file_offset'] + key[1]] != -1 or
                          key in far_bss_claimed), None)
        if collision is not None:
            at = image['segments'][collision[0] - 1]['file_offset'] + collision[1]
            prior = owners[owner[at]]['label'] if owner[at] != -1 else owners[far_bss_claimed[collision]]['label']
            far_bss_rejections.append(dict(owner=label, reason='private FAR_DATA zero-fill overlaps admitted bytes at seg %d:%04X (%s)' % (collision[0], collision[1], prior)))
            continue
        for (segment, offset), byte in claims.items():
            at = image['segments'][segment - 1]['file_offset'] + offset
            owner[at] = o; hybrid[at] = byte
            far_bss_claimed[(segment, offset)] = o

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
                  file_bytes=size, owned=dict(C=totals['C'], RUNTIME=totals['RUNTIME'], RESOURCES=totals['RESOURCES'], LINK=totals['LINK']), debt=dict(sorted(lanes.items())),
                  debt_total=size - totals['C'] - totals['RUNTIME'] - totals['RESOURCES'] - totals['LINK'], code_segment_bytes=code_bytes,
                   objects=len(seen), problems=problems[:50], problem_count=len(problems), mismatched_bytes=len(mismatches),
                   far_bss_owned_bytes=len(far_bss_claimed), far_bss_claim_rejections=far_bss_rejections[:50],
                  claim_conflicts=dict(bytes=sum(conflicts.values()), pairs=len(conflicts),
                                       top=[dict(objects=list(k), bytes=v) for k, v in sorted(conflicts.items(), key=lambda kv: -kv[1])[:5]],
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
