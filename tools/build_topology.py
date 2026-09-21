"""Reconstruct the probable historical build topology from linker-preserved evidence.

Three levels are kept distinct: a code group (named physical NE segment), a
translation unit / object member (contiguous code contribution, private
selector pool and private data), and a build component (library membership,
only when the link order proves it). Nothing here grants recovery credit or
asserts a historical filename.

Evidence used, all independent of function names:
- MSC 7 pools far-object selectors in a private CONST word table, one pool per
  object, in first-use order; two functions sharing a pool word are in the
  same object.
- LINK 5.30 appends each object's contribution to every logical segment in
  link order, so pool/_DATA positions record the global link order while code
  offsets record the order inside each logical segment (see
  evidence/experiments/toolchain/link-layout/).
- Explicit objects precede library members; C runtime members interleaved
  with game units mark library-pulled units.
"""
import argparse
import json
import re
from collections import Counter, defaultdict
from common import ROOT, fixture, read_json, write_json, identity
from analysis import decoder, cs
import ne, mapsym

GAME_GROUPS = ['SIMANT_MODULE', 'GR_MODULE', 'ANTEDIT_MODULE', 'SIMONE_MODULE', 'SIMANT1_MODULE', 'SIMTWO_MODULE']
REPORT = ROOT / 'evidence/topology/build-topology.json'


def cards():
    return [json.loads(line) for line in (ROOT / 'evidence/disassembly/cards.jsonl').read_text().splitlines()]


def selector_sites(image):
    return {site: r['target'] for r in image['segments'][9]['relocations'] if r['source_type'] == 2 for site in r['sites']}


def dense_regions(addresses, gap=16):
    regions = []
    for a in sorted(addresses):
        if regions and a - regions[-1][1] <= gap:
            regions[-1][1] = a
        else:
            regions.append([a, a])
    return regions


def pool_region(image, symbols):
    """Largest dense run of selector-relocated DGROUP words with no MAPSYM name inside."""
    sites = selector_sites(image)
    named = sorted({p['offset'] for p in symbols['segments'][9]['symbols']})
    # Split dense runs at named symbols: a pool word never carries a public name.
    regions = []
    for a, b in dense_regions(sites, gap=16):
        cuts = [o for o in named if a <= o <= b]
        lo = a
        for cut in cuts + [b + 1]:
            part = [s for s in sites if lo <= s <= b and s < cut]
            if part:
                regions.append([min(part), max(part)])
            lo = cut + 1
    start, end = max(regions, key=lambda r: sum(1 for s in sites if r[0] <= s <= r[1]))
    return dict(start=start, end=end + 1, words=sum(1 for a in sites if start <= a <= end),
                basis='Dense selector-relocated DGROUP words without MAPSYM names: the compiler-generated CONST selector pools of all objects, in link order')


def data_regions(symbols):
    names = {p['name']: p['offset'] for p in symbols['segments'][9]['symbols']}
    return dict(edata=names.get('_edata'), end=names.get('_end'))


def function_features(card, sites, pool, named):
    slots = []
    unnamed = []
    for row in card['disassembly']:
        for ins in decoder().disasm(bytes.fromhex(row['bytes']), row['offset']):
            for op in ins.operands:
                if op.type != cs.x86.X86_OP_MEM or op.mem.base or op.mem.index:
                    continue
                if ins.reg_name(op.mem.segment) not in (None, '', 'ds'):
                    continue
                a = op.mem.disp & 65535
                if pool['start'] <= a < pool['end'] and a in sites:
                    if a not in slots:
                        slots.append(a)
                elif a >= 0x40 and a not in named and not (pool['start'] <= a < pool['end']):
                    if a not in unnamed:
                        unnamed.append(a)
    return slots, unnamed


def name_token(symbol):
    name = symbol.lstrip('_')
    m = re.match(r'([a-z][a-z0-9]*)_', name)
    if m:
        return m.group(1) + '_'
    m = re.match(r'([A-Z][a-z]+)', name)
    return m.group(1) if m else name[:4]


def admitted_private():
    result = defaultdict(list)
    path = ROOT / 'evidence/recovery/verified-objects.json'
    if not path.exists():
        return result
    for g in read_json(path)['game']:
        for x in g['comparison'].get('contributions', []):
            if x['segment'] in ('_DATA', 'CONST', '_BSS'):
                result[g['symbol']].append((x['segment'], x['original_offset'], x['length']))
    return result


def known_units():
    units = []
    path = ROOT / 'layout/translation-units.json'
    if path.exists():
        for u in read_json(path)['units']:
            units.append(dict(id=u['id'], publics=u['publics'], status=u['status'], evidence=u.get('evidence')))
    path = ROOT / 'evidence/topology/solved-families.json'
    if path.exists():
        for f in read_json(path)['families']:
            if len(f['members']) > 1:
                units.append(dict(id=f['id'], publics=f['members'], status='STRICT_FAMILY', evidence=f.get('evidence')))
    return units


class Union:
    def __init__(self):
        self.parent = {}
        self.reasons = defaultdict(list)

    def find(self, x):
        self.parent.setdefault(x, x)
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def join(self, a, b, reason):
        ra, rb = self.find(a), self.find(b)
        if ra != rb:
            self.parent[ra] = rb
        self.reasons[frozenset((a, b))].append(reason)


def build():
    raw = fixture('SIMANTW.EXE')
    image = ne.parse(raw)
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    sites = selector_sites(image)
    pool = pool_region(image, symbols)
    regions = data_regions(symbols)
    named = {p['offset'] for p in symbols['segments'][9]['symbols']}
    private = admitted_private()
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    jobs = {}
    for path in (ROOT / 'evidence/recovery/workflow/jobs').glob('*/job.json'):
        job = read_json(path)
        jobs[job['symbol']] = job
    functions = {}
    for card in cards():
        if card['ownership'] != 'GAME':
            continue
        slots, unnamed = function_features(card, sites, pool, named)
        string_ops = sorted({r['mnemonic'] for r in card['disassembly'] if any(x in r['mnemonic'] for x in ('stos', 'movs', 'scas', 'lods', 'cmps'))})
        job = jobs.get(card['symbol'])
        functions[card['symbol']] = dict(symbol=card['symbol'], group=card['segment_name'], segment=card['segment'], offset=card['offset'],
            size=card['extent']['size'], slots=slots, unnamed_ds_operands=unnamed, token=name_token(card['symbol']),
            admitted=card['symbol'] in recipes, private_contributions=private.get(card['symbol'], []),
            string_ops=string_ops, job_status=job['status'] if job else None, job_blockers=job.get('blockers') if job else None,
            calls=sorted({n for r in card['calls'] for n in r.get('names', [])}))
    # Words attributable to each function in two link-order coordinates: the
    # CONST selector pool (slots plus admitted CONST contributions) and admitted
    # private _DATA contributions. An object owns one contiguous interval in
    # each coordinate and objects are laid out in link order.
    seen = defaultdict(set)
    for f in sorted(functions.values(), key=lambda f: (f['group'], f['offset'])):
        f['words'] = dict(pool=sorted(set(f['slots']) | {o for s, o, n in f['private_contributions'] if s == 'CONST'}),
                          data=sorted({o for s, o, n in f['private_contributions'] if s == '_DATA'}))
        # Words first used by this function in its group's code order.
        f['introduced'] = {space: sorted(w for w in words if w not in seen[(f['group'], space)]) for space, words in f['words'].items()}
        for space, words in f['words'].items():
            seen[(f['group'], space)].update(words)
        f['pool_position'] = [f['words']['pool'][0], f['words']['pool'][-1]] if f['words']['pool'] else None
        f['data_position'] = [f['words']['data'][0], f['words']['data'][-1]] if f['words']['data'] else None
        f['positions'] = {space: [v[0], v[-1]] for space, v in f['words'].items() if v}
    # J1/J2: a shared pool word or private data word proves one object.
    union = Union()
    owners = defaultdict(list)
    for f in functions.values():
        for a in f['slots']:
            owners[('slot', a)].append(f['symbol'])
        for s, o, n in f['private_contributions']:
            if s != '_BSS':
                owners[('private', s, o)].append(f['symbol'])
    for key, users in owners.items():
        for other in users[1:]:
            union.join(users[0], other, dict(kind='shared_' + key[0], key=key[1:] if key[0] == 'private' else '%04X' % key[1]))
    controls = known_units()
    for unit in controls:
        members = [p for p in unit['publics'] if p in functions]
        for other in members[1:]:
            union.join(members[0], other, dict(kind='joint_compile_evidence', unit=unit['id'], status=unit['status']))
    cross_segment = [k for k, users in owners.items() if k[0] == 'slot' and len({functions[u]['group'] for u in users}) > 1]
    # Foreign words: every attributed word with its owning group, per coordinate,
    # including verified C runtime members (library members linked after the
    # explicit objects) whose _DATA/CONST placements are known exactly.
    foreign = {space: {(w, f['group']) for f in functions.values() for w in f['words'][space]} for space in ('pool', 'data')}
    runtime_words = []
    verified = ROOT / 'evidence/recovery/verified-objects.json'
    if verified.exists():
        for r in read_json(verified)['runtime']:
            for c in r['comparison'].get('contributions', []):
                if c['original_segment'] == 10 and c['segment'] in ('_DATA', 'CONST'):
                    runtime_words.append((c['original_offset'], c['segment'], r['member']))
                    foreign['data' if c['segment'] == '_DATA' else 'pool'].add((c['original_offset'], 'RUNTIME'))
    foreign = {space: sorted(words) for space, words in foreign.items()}
    owner_words = {space: sorted({(w, f['group'], f['symbol']) for f in functions.values() for w in f['words'][space]}) for space in ('pool', 'data')}

    def foreign_between(space, lo, hi, group):
        return sorted({g for w, g in foreign[space] if lo < w < hi and g != group})

    groups = {}
    units = []
    violations = []
    assumptions = []
    observed_reversals = []
    for group in GAME_GROUPS:
        fs = sorted([f for f in functions.values() if f['group'] == group], key=lambda f: f['offset'])
        index = {f['symbol']: i for i, f in enumerate(fs)}
        different = []   # (earlier symbol, later symbol, reason)
        # Link-order relations between consecutive located functions of one
        # group, per coordinate; a proven difference localises a boundary to
        # the stretch between them.
        for space in ('pool', 'data'):
            # Interleaving: consecutive functions with any word in this coordinate.
            located = [f for f in fs if space in f['positions']]
            for a, b in zip(located, located[1:]):
                xa, xb = a['words'][space], b['words'][space]
                lo, hi = min(xa + xb), max(xa + xb)
                between = foreign_between(space, lo, hi, group)
                if between and not (min(xb) < max(xa)):
                    different.append((a['symbol'], b['symbol'], dict(kind='interleaved_object', space=space, other_groups=between,
                                      note='Another code group contributed between these link positions; one object is contiguous in link order')))
            # Reversal: consecutive functions that introduce words. Reusing an
            # earlier object word is ordinary; introducing a lower word is not.
            introducing = [f for f in fs if f['introduced'][space]]
            for a, b in zip(introducing, introducing[1:]):
                ia, ib = a['introduced'][space], b['introduced'][space]
                if not min(ib) < max(ia):
                    continue
                between = foreign_between(space, min(ib), max(ia), group)
                if between:
                    different.append((a['symbol'], b['symbol'], dict(kind='logical_segment_reversal', space=space, other_groups=between,
                                      note='Later code introduces an earlier link position with foreign contributions between: different objects in different logical segments')))
                    continue
                # Reversals without foreign contributions between are not
                # evidence either way: inside one proven object the pool order
                # deviates from code order at function granularity (e.g.
                # win_DrawMapWindow introduces a word below DrawMapCursor's).
                observed_reversals.append(dict(group=group, earlier=a['symbol'], later=b['symbol'], space=space,
                                               same_object=union.find(a['symbol']) == union.find(b['symbol'])))
        # Contiguity closure: objects are contiguous in a logical segment.
        spans = {}
        for f in fs:
            root = union.find(f['symbol'])
            lo, hi = spans.get(root, (index[f['symbol']], index[f['symbol']]))
            spans[root] = (min(lo, index[f['symbol']]), max(hi, index[f['symbol']]))
        merged = []
        for lo, hi in sorted(spans.values()):
            if merged and lo <= merged[-1][1]:
                merged[-1][1] = max(merged[-1][1], hi)
            else:
                merged.append([lo, hi])
        for lo, hi in merged:
            for i in range(lo, hi + 1):
                union.join(fs[lo]['symbol'], fs[i]['symbol'], dict(kind='contiguity', note='object contributions are contiguous in a logical segment'))
        # Consistency: a proven-different pair must not have been joined.
        for a, b, reason in different:
            if union.find(a) == union.find(b):
                violations.append(dict(group=group, earlier=a, later=b, reason=reason, note='proven different objects but joined by sharing/contiguity'))
        # Boundaries: proven-different pairs localise a boundary between the
        # last member of the earlier component and the first of the later one.
        cut = {}
        for a, b, reason in different:
            ca, cb = union.find(a), union.find(b)
            if ca == cb:
                continue
            left = max(index[f['symbol']] for f in fs if union.find(f['symbol']) == ca and index[f['symbol']] < index[b])
            right = min(index[f['symbol']] for f in fs if union.find(f['symbol']) == cb and index[f['symbol']] > left)
            cut.setdefault((left, right), []).append(dict(reason, between=[a, b]))
        # A zone (l, r) with r - l > 1 holds functions that cannot be attached
        # to either side by link evidence; they are cut out as their own run.
        edges = {}
        for (l, r), rs in cut.items():
            if r - l == 1:
                edges.setdefault(l, []).append(('HARD', rs, [fs[l]['symbol'], fs[r]['symbol']]))
            else:
                edges.setdefault(l, []).append(('HARD_ZONE_START', rs, [fs[l]['symbol'], fs[r]['symbol']]))
                edges.setdefault(r - 1, []).append(('HARD_ZONE_END', rs, [fs[l]['symbol'], fs[r]['symbol']]))
        boundaries = []
        for i in range(len(fs) - 1):
            a, b = fs[i], fs[i + 1]
            same = union.find(a['symbol']) == union.find(b['symbol'])
            if i in edges:
                kind = 'HARD' if any(k == 'HARD' for k, rs, z in edges[i]) else edges[i][0][0]
                reasons = [dict(reason, zone=z) for k, rs, z in edges[i] for reason in rs]
                if all(r['kind'] == 'likely_logical_segment_reversal' for r in reasons):
                    kind = kind.replace('HARD', 'LIKELY')
                if same:
                    violations.append(dict(group=group, earlier=a['symbol'], later=b['symbol'], note='boundary edge inside a joined component'))
            elif same:
                kind, reasons = 'SAME_OBJECT', []
            elif a['token'] != b['token']:
                kind, reasons = 'SOFT', [dict(kind='name_token_change', left=a['token'], right=b['token'], note='Weak signal only')]
            else:
                kind, reasons = 'UNKNOWN', []
            boundaries.append(dict(after=a['symbol'], before=b['symbol'], kind=kind, reasons=reasons))
        runs = [[fs[0]]]
        for f, boundary in zip(fs[1:], boundaries):
            if boundary['kind'].startswith(('HARD', 'LIKELY')):
                runs.append([])
            runs[-1].append(f)
        for run_index, members in enumerate(runs):
            comps = Counter(union.find(m['symbol']) for m in members)
            joins = [r for pair, rs in union.reasons.items() for r in rs if any(m['symbol'] in pair for m in members) and r['kind'] != 'contiguity']
            slots_all = sorted({a for m in members for a in m['slots']})
            const_all = sorted({w for m in members for w in m['words']['pool']})
            data_all = sorted({w for m in members for w in m['words']['data']})
            joint = sorted({r['unit'] for r in joins if r['kind'] == 'joint_compile_evidence'})
            tokens = Counter(m['token'] for m in members)
            inner = [b for b in boundaries if any(b['after'] == m['symbol'] for m in members[:-1]) and b['kind'] != 'SAME_OBJECT']
            unit_id = '%s:%04X-%04X' % (group.split('_')[0].lower(), members[0]['offset'], members[-1]['offset'] + (members[-1]['size'] or 0))
            located_run = any(m['positions'] for m in members)
            confidence = ('UNLOCATED' if not located_run else 'STRONGLY_SUPPORTED_TU' if joint and len(comps) == 1 else
                          'CANDIDATE_TU' if len(comps) == 1 and (len(members) == 1 or joins) else 'CANDIDATE_RANGE')
            # Same-object components inside the run: the finest grouping the
            # evidence supports, each a contiguous span after closure.
            components = []
            for root in dict.fromkeys(union.find(m['symbol']) for m in members):
                span = [m for m in members if union.find(m['symbol']) == root]
                kinds = Counter(r['kind'] for pair, rs in union.reasons.items() for r in rs if all(functions.get(q, {}).get('group') == group for q in pair) and any(m['symbol'] in pair for m in span) and r['kind'] != 'contiguity')
                components.append(dict(id='%s:%04X' % (group.split('_')[0].lower(), span[0]['offset']), publics=[m['symbol'] for m in span],
                    pool_words=sorted({'%04X' % w for m in span for w in m['words']['pool']}), data_words=sorted({w for m in span for w in m['words']['data']}),
                    join_evidence=dict(kinds), admitted=sum(m['admitted'] for m in span), parked=[m['symbol'] for m in span if m['job_status'] == 'ESCALATED']))
            units.append(dict(candidate_unit=unit_id, segment=group, range=[members[0]['symbol'], members[-1]['symbol']],
                publics=[m['symbol'] for m in members], function_count=len(members), code_bytes=sum(m['size'] or 0 for m in members),
                admitted=sum(m['admitted'] for m in members), pool_range=['%04X' % const_all[0], '%04X' % const_all[-1]] if const_all else None,
                data_range=[data_all[0], data_all[-1]] if data_all else None,
                evidence=dict(contiguous_publics=True, shared_selectors=sorted('%04X' % a for a in slots_all),
                    shared_private_data=sorted({'%s:%d' % (s, o) for m in members for s, o, n in m['private_contributions']}),
                    hard_join_count=sum(1 for r in joins if r['kind'] in ('shared_slot', 'shared_private')),
                    reversed_reuse_joins=sum(1 for r in joins if r['kind'] == 'reversed_reuse'),
                    joint_compile_evidence=joint, semantic_cluster=tokens.most_common(3),
                    string_intrinsic_fingerprints=sorted({op for m in members for op in m['string_ops']}),
                    same_object_components=len(comps), internal_soft_boundaries=[b['after'] + '|' + b['before'] for b in inner]),
                components=components, confidence=confidence))
        groups[group] = dict(segment=fs[0]['segment'], functions=len(fs), code_bytes=sum(f['size'] or 0 for f in fs),
                             units=sum(1 for u in units if u['segment'] == group), boundaries=boundaries,
                             proven_different_pairs=len(different))
    # Library-membership evidence: units whose link position follows C runtime _DATA members.
    runtime_start = min([o for o, s, m in runtime_words if s == '_DATA'] or [None])
    for u in units:
        u['after_runtime_data'] = bool(u['data_range'] and runtime_start and u['data_range'][0] > runtime_start)
    # Controls: every known joint unit must fall inside one candidate unit.
    control_results = []
    for unit in controls:
        homes = {next((u['candidate_unit'] for u in units if p in u['publics']), None) for p in unit['publics'] if p in functions}
        control_results.append(dict(unit=unit['id'], status=unit['status'], publics=unit['publics'], candidate_units=sorted(h for h in homes if h), passed=len(homes) == 1))
    report = dict(schema_version=1, scope='Probable historical build topology; routing and grouping evidence only, never recovery credit or historical filenames',
        inputs={p: identity(ROOT / p) for p in ['evidence/disassembly/cards.jsonl', 'evidence/recovery/verified-objects.json', 'layout/translation-units.json']},
        code_group_naming=dict(observed=GAME_GROUPS, compiler_default='<basename>_TEXT (observed INPUT_TEXT for INPUT.C under MSC 7.00)',
            interpretation='Explicitly assigned code segment names (/NT or equivalent); not compiler defaults and not linker-generated',
            evidence='evidence/experiments/toolchain/link-layout/'),
        linker_model=dict(logical_segment_order='DEF SEGMENTS entries first, then first occurrence in link order; /PACKCODE packs adjacent logical code segments into one physical segment',
            contribution_order='Within one logical segment, contributions follow link order; explicit objects precede library members; library members are pulled in member order',
            evidence='evidence/experiments/toolchain/link-layout/'),
        pool_region=dict(start='%04X' % pool['start'], end='%04X' % pool['end'], words=pool['words'], basis=pool['basis']),
        bss_region=dict(edata=regions['edata'], end=regions['end'], note='Class BSS follows all DATA/CONST classes; a private uninitialised static cannot be placed below _edata'),
        falsification=dict(cross_segment_shared_pool_words=len(cross_segment), contradictions=violations, single_logical_segment_assumptions=assumptions,
            observed_reversals=observed_reversals, reversals_inside_proven_objects=sum(1 for r in observed_reversals if r['same_object'])),
        code_groups=groups, units=units, controls=control_results,
        functions={k: {kk: vv for kk, vv in v.items() if kk not in ('calls', 'words')} for k, v in functions.items()})
    write_json(REPORT, report)
    return report


def markdown(report):
    lines = ['# Probable historical build topology', '',
             'Generated by `python tools/build_topology.py`. Routing evidence only: no recovery credit, no historical filenames.', '',
             '## Model', '',
             '- Code groups `%s` are explicitly assigned segment names: MSC 7.00 defaults to `<basename>_TEXT` (%s).' % ('`, `'.join(GAME_GROUPS), report['code_group_naming']['evidence']),
             '- One object contributes contiguously to each logical segment; LINK 5.30 appends contributions in link order, so the private CONST selector pools (`%s`-`%s`, %d words) and private `_DATA` record the global link order.' % (report['pool_region']['start'], report['pool_region']['end'], report['pool_region']['words']),
             '- Two functions sharing a pool word or a private data word are in the same object; a reversal of link order inside a physical segment marks a logical-segment boundary; another code group contributing between two functions marks an object boundary.',
             '- Falsification: %d pool words shared across code groups; %d contradictions between proven-different and joined pairs; %d joins rely on the single-logical-segment assumption.' % (report['falsification']['cross_segment_shared_pool_words'], len(report['falsification']['contradictions']), len(report['falsification']['single_logical_segment_assumptions'])), '',
             '## Controls', '', '| Known unit | Status | Passed | Candidate unit |', '| --- | --- | --- | --- |']
    for c in report['controls']:
        lines.append('| %s | %s | %s | %s |' % (c['unit'], c['status'], c['passed'], ', '.join(c['candidate_units'])))
    lines += ['', '## Units by code group', '']
    for group in GAME_GROUPS:
        g = report['code_groups'][group]
        lines += ['### %s (%d functions, %d bytes, %d candidate units)' % (group, g['functions'], g['code_bytes'], g['units']), '',
                  '| Unit | Range | n | admitted | pool | _DATA | joins | cluster | lib-order | confidence |', '| --- | --- | ---: | ---: | --- | --- | ---: | --- | --- | --- |']
        for u in report['units']:
            if u['segment'] != group:
                continue
            lines.append('| %s | %s .. %s | %d | %d | %s | %s | %d | %s | %s | %s |' % (u['candidate_unit'], u['range'][0], u['range'][1], u['function_count'], u['admitted'],
                '-'.join(u['pool_range']) if u['pool_range'] else '', '%d-%d' % tuple(u['data_range']) if u['data_range'] else '', u['evidence']['hard_join_count'],
                ', '.join('%s×%d' % t for t in u['evidence']['semantic_cluster']), 'after CRT' if u['after_runtime_data'] else '', u['confidence']))
        lines.append('')
    return '\n'.join(lines) + '\n'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--markdown', default='docs/build-topology-units.md')
    args = ap.parse_args()
    report = build()
    (ROOT / args.markdown).write_text(markdown(report), encoding='utf-8')
    print(json.dumps(dict(units=len(report['units']), controls=[(c['unit'], c['passed']) for c in report['controls']], falsification=report['falsification']), indent=2))


if __name__ == '__main__':
    main()
