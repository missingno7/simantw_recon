"""Read-only working context for one original function, or a listing of all of them.

    python tools/context.py SYMBOL [--brief] [--history]
    python tools/context.py --list [--open|--matched] [--segment NAME]
    python tools/context.py --data SYMBOL [--brief]            # DATA lane packet
    python tools/context.py --list --data [--open]             # DATA lane symbols

The packet carries masked disassembly with loader bindings, exact MAPSYM data
bindings, calls, globals, basic blocks, the catalogued compiler profile, unit
context, reconstruction rules, similar admitted sources and the best preserved
draft. Prior notes and blocker labels are hints, never gates.
"""
import argparse
import json
import sys
from common import ROOT, FormatError, cards, fixture, read_json, recipes, relative, sha256, write_json
import compiler_profiles
import drafts
import mapsym
import ne


def certify(card, raw, image, symbols):
    """Closed structural test extent, checked recursively and linearly (informational)."""
    from cfg_solver import solve
    from analysis import decoder
    e = card['extent']; reasons = []
    if e['end'] is None or e['status'] in ('SHARED_TAIL', 'OVERLAPPING_ENTRY', 'AMBIGUOUS_TABLE'):
        reasons.append('UNCLOSED_OR_SHARED_CFG')
    if e.get('incoming_branches') or e.get('entry_aliases'):
        reasons.append('CROSS_ENTRY_OR_ALIAS')
    if reasons:
        return dict(status='UNCONFIRMED', reasons=reasons)
    ns = image['segments'][card['segment'] - 1]; code = raw[ns['file_offset']:ns['file_offset'] + ns['logical_size']]
    entries = [p['offset'] for p in symbols['segments'][card['segment'] - 1]['symbols']]
    proof = solve(code, card['offset'], e['upper_bound'], entries, ns['relocations'], card['segment'])
    if proof['end'] != e['end'] or proof['status'] != 'PROBABLE' or proof['reasons']:
        reasons.append('RECURSIVE_SCOPE_NOT_CLOSED')
    # Linear decode of every code run between the proven jump tables; the
    # table bytes are data and count toward the extent without being decoded.
    spans = sorted((t['table'], t['table'] + 2 * t['count']) for t in proof.get('jump_tables', []))
    decoded = []; cursor = card['offset']; covered = 0
    for a, b in spans + [(e['end'], e['end'])]:
        decoded += list(decoder().disasm(code[cursor:a], cursor)); covered += b - a; cursor = b
    if sum(i.size for i in decoded) + covered != e['size']:
        reasons.append('INCOMPLETE_LINEAR_DECODE')
    if not set(proof['instruction_starts']).issubset({i.address for i in decoded}):
        reasons.append('OVERLAPPING_INSTRUCTION_STREAMS')
    for r in ns['relocations']:
        for site in r['sites']:
            if card['offset'] <= site < e['end'] and (site + r['width'] > e['end'] or r['source_type'] not in (2, 3, 5)):
                reasons.append('UNEVALUABLE_FIXUP_SCOPE')
    return dict(status='CONFIRMED' if not reasons else 'UNCONFIRMED', reasons=sorted(set(reasons)), start=card['offset'], size=e['size'], cfg_status=e['status'],
                target_sha256=sha256(code[card['offset']:e['end']]),
                scope='Structural test extent only; admission independently checks the complete original scope')


def packet(symbol, brief=False, history=False):
    from codegen_diff import blocks, instructions
    from recovery_context import compact_packet
    from reconstruction_rules import relevant_rules
    from topology_context import direct_data_bindings
    all_cards = cards(); targets = recipes()
    card = next((c for c in all_cards if c['symbol'] == symbol), None)
    if card is None:
        raise FormatError('unknown function symbol; try context.py --list')
    ledger = drafts.entry(symbol)
    result = compact_packet(card, all_cards, targets, {})
    result.pop('prior_draft', None)
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    code = bytes.fromhex(''.join(r['bytes'] for r in card['disassembly']))
    profile = compiler_profiles.resolve(symbol)
    state = 'MATCHED' if symbol in targets else 'OPEN' if card['ownership'] == 'GAME' else card['ownership']
    result.update(state=state, admitted_source=targets.get(symbol, {}).get('source'),
                  structural_extent=certify(card, raw, image, symbols) if state == 'OPEN' else None,
                  target_bytes_hex=code.hex(), target_bytes_note='Raw target includes loader-chain words; use masked disassembly and semantic bindings for source inference',
                  basic_blocks=blocks(instructions(code)), calls=card['calls'], globals=card['globals'], relocations=card['known_fixups'],
                  compiler_profile=dict(compiler='msc700', flags=compiler_profiles.profile_flags(profile['name'], card['segment_name']), profile=profile,
                                        catalog='layout/compiler-profiles.json',
                                        note='Profile belongs to the object context with recorded evidence; it is not a per-function search dimension'))
    result['unit_context'] = compiler_profiles.component_of(symbol)
    matching = [c for c in all_cards if c['source'] and c['ownership'] == 'GAME' and c['segment'] == card['segment']]
    matching.sort(key=lambda c: abs((c['extent']['size'] or 65536) - (card['extent']['size'] or 65536)))
    result['similar_matched_functions'] = [dict(symbol=c['symbol'], source=c['source'], size=c['extent']['size'], basis='Same code group and nearest size; similarity is not semantic proof') for c in matching[:5]]
    result['direct_data_bindings'] = direct_data_bindings(card, symbols, image)
    # Rule triggers include named far-data bindings, so evaluate only after
    # those semantic bindings have been attached.
    result['reconstruction_rules'] = relevant_rules(card, result)
    result['known_families'] = [{k: u[k] for k in ['id', 'status', 'publics', 'evidence']} for u in read_json(ROOT / 'layout/translation-units.json')['units'] if symbol in u['publics']]
    from library_match import import_symbols
    known = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    result['known_imported_symbols'] = [dict(target=r['target'], symbols=[name for name, t in known.items() if t == r['target']]) for r in card['known_fixups'] if r['target']['kind'] == 'import']
    result['best_draft'] = ledger.get('best')
    result['notes'] = ledger.get('notes', [])
    if history:
        result['legacy_jobs'] = ledger.get('legacy_jobs', [])
        result['legacy_draft'] = ledger.get('legacy_draft')
        log = ROOT / 'build/search' / symbol.lstrip('_') / 'history.jsonl'
        result['search_history'] = [json.loads(line) for line in log.read_text(encoding='utf-8').splitlines()] if log.exists() else []
    else:
        result['legacy_jobs'] = [{k: j[k] for k in j if k in ('job', 'status', 'attempts', 'blockers')} for j in ledger.get('legacy_jobs', [])]
    path = ROOT / 'build/context' / (symbol.lstrip('_') + '.json')
    write_json(path, result)
    if brief:
        result = dict(size=card['extent']['size'], **{k: result[k] for k in ('symbol', 'state', 'code_segment', 'offset', 'structural_extent', 'compiler_profile', 'unit_context', 'calls',
                                         'direct_data_bindings', 'reconstruction_rules', 'similar_matched_functions', 'best_draft', 'notes', 'legacy_jobs')})
    result['packet'] = relative(path)
    return result


def data_spans(symbols, image):
    """Every public of a data segment with its span to the next public (a scope hint, not a type)."""
    rows = []
    for seg in symbols['segments']:
        ns = image['segments'][seg['number'] - 1]
        if ns['kind'] != 'DATA':
            continue
        ordered = sorted(seg['symbols'], key=lambda p: p['offset'])
        for k, p in enumerate(ordered):
            end = ordered[k + 1]['offset'] if k + 1 < len(ordered) else ns['logical_size']
            rows.append(dict(symbol=p['name'], segment=seg['number'], segment_name=seg['name'], offset=p['offset'], span=max(0, min(end, ns['logical_size']) - p['offset'])))
    return rows


def data_packet(symbol, brief=False):
    """Working context for an original data symbol (DATA lane)."""
    from recovery_context import declaration_index
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    row = next((r for r in data_spans(symbols, image) if r['symbol'] == symbol), None)
    if row is None:
        raise FormatError('unknown data symbol')
    ns = image['segments'][row['segment'] - 1]
    data = raw[ns['file_offset'] + row['offset']:ns['file_offset'] + row['offset'] + row['span']]
    seg_names = {s['number']: s['name'] for s in symbols['segments']}
    names_at = {}
    for s in symbols['segments']:
        for x in s['symbols']:
            names_at.setdefault((s['number'], x['offset']), []).append(x['name'])
    relocations = []
    for r in ns['relocations']:
        for site in r['sites']:
            if row['offset'] <= site < row['offset'] + row['span']:
                target = dict(r['target'])
                if target.get('kind') == 'internal':
                    target['segment_name'] = seg_names.get(target['segment'])
                    target['names'] = names_at.get((target['segment'], target['offset']), [])
                relocations.append(dict(offset=site - row['offset'], type=r['source_type'], width=r['width'], target=target,
                                        note='loader site: the file bytes here are chain metadata; declare a far pointer/selector to the named target'))
    ledger = read_json(ROOT / 'build/image/ledger.json') if (ROOT / 'build/image/ledger.json').exists() else {}
    start = ns['file_offset'] + row['offset']
    owned = [dict(start=i['start'] - ns['file_offset'], end=i['end'] - ns['file_offset'], lane=i['lane']) for i in ledger.get('intervals', [])
             if i['start'] < start + row['span'] and i['end'] > start]
    users = sorted({c['symbol'] for c in cards() for r in c['disassembly'] for ref in r['references'] if symbol in ref.get('names', [])})
    plain = symbol[1:] if symbol.startswith('_') else symbol
    result = dict(symbol=symbol, lane='DATA', state='MATCHED' if symbol in recipes() else 'OPEN', segment=row['segment'], segment_name=row['segment_name'],
                  offset=row['offset'], span_to_next_public=row['span'], nonzero_bytes=sum(1 for b in data if b),
                  bytes_hex=data[:4096].hex(), bytes_truncated=len(data) > 4096, relocations=relocations, raw_debt_in_span=owned,
                  referencing_functions=users, admitted_declarations=declaration_index(recipes()).get(plain, [])[:8],
                  notes=['The span runs to the next original public; unnamed statics of other objects may lie inside it. A data module must not claim bytes an admitted object owns.',
                         'Far data in segment %s is declared with __based(__segname("%s")); DGROUP data is ordinary near data.' % (row['segment_name'], row['segment_name']),
                         'Promote with: python tools/promote.py --data FILE.c (several adjacent publics per module are fine).'])
    if brief:
        result.pop('bytes_hex')
    return result


def listing(which='all', segment=None):
    targets = recipes(); ledger = drafts.load(); rows = []
    for card in cards():
        if card['ownership'] != 'GAME' or (segment and card['segment_name'] != segment):
            continue
        state = 'MATCHED' if card['symbol'] in targets else 'OPEN'
        if which != 'all' and state.lower() != which:
            continue
        best = (ledger.get(card['symbol']) or {}).get('best') or {}
        jobs = (ledger.get(card['symbol']) or {}).get('legacy_jobs', [])
        rows.append(dict(symbol=card['symbol'], state=state, segment=card['segment_name'], size=card['extent']['size'], calls=len(card['calls']),
                         best=best.get('basis'), opcodes='%s/%s' % (best['opcode_matches'], best['opcode_total']) if best.get('opcode_total') else None,
                         hint=next((j['blockers'][0] for j in reversed(jobs) if j.get('blockers')), None)))
    order = {'EXACT_BODY_CANDIDATE': 0, 'BODY_MATCHED_BINDING_BLOCKED': 0, 'BEST_CANDIDATE_NOT_EXACT': 1, None: 2}
    def closeness(r):
        if not r['opcodes']:
            return 0
        a, b = r['opcodes'].split('/')
        return -int(a) / max(int(b), 1)
    rows.sort(key=lambda r: (r['state'] != 'OPEN', order.get(r['best'], 2), closeness(r), r['size'] or 65536, r['symbol']))
    return dict(counts=dict(open=sum(r['state'] == 'OPEN' for r in rows), matched=sum(r['state'] == 'MATCHED' for r in rows)), functions=rows)


def data_listing(which='open'):
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    targets = recipes(); rows = []
    for row in data_spans(symbols, image):
        state = 'MATCHED' if row['symbol'] in targets else 'OPEN'
        if which != 'all' and state.lower() != which:
            continue
        ns = image['segments'][row['segment'] - 1]
        data = raw[ns['file_offset'] + row['offset']:ns['file_offset'] + row['offset'] + row['span']]
        sites = sum(1 for r in ns['relocations'] for s in r['sites'] if row['offset'] <= s < row['offset'] + row['span'])
        rows.append(dict(row, state=state, nonzero=sum(1 for b in data if b), relocations=sites))
    return dict(counts=dict(open=sum(r['state'] == 'OPEN' for r in rows), matched=sum(r['state'] == 'MATCHED' for r in rows)), symbols=rows)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('symbol', nargs='?')
    ap.add_argument('--brief', action='store_true')
    ap.add_argument('--history', action='store_true', help='include legacy job summaries and every search round')
    ap.add_argument('--list', action='store_true')
    ap.add_argument('--open', action='store_true')
    ap.add_argument('--matched', action='store_true')
    ap.add_argument('--segment')
    ap.add_argument('--data', action='store_true', help='DATA lane: data symbol packet, or with --list the data symbols')
    args = ap.parse_args()
    which = 'open' if args.open else 'matched' if args.matched else 'all'
    if args.list and args.data:
        result = data_listing(which)
    elif args.list:
        result = listing(which, args.segment)
    elif args.symbol and args.data:
        result = data_packet(args.symbol, args.brief)
    elif args.symbol:
        result = packet(args.symbol, args.brief, args.history)
    else:
        ap.error('give SYMBOL or --list')
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
