"""Evidence-backed compiler profiles attached to candidate historical objects.

The catalog (layout/compiler-profiles.json) enumerates the few admissible
MSC 7.00 optimiser profiles. A symbol resolves to the locked baseline unless a
reviewed assignment covers its object context (a build-topology component or
an explicit symbol list) and no refutation contradicts it. There is no
per-function flag search: `probe` compiles one preserved candidate under every
catalog profile and records the strict and diagnostic outcome as evidence;
`assign` records a reviewed assignment that cites such evidence.
"""
import argparse
import json
import re
from pathlib import Path
from datetime import datetime, timezone
from common import ROOT, FormatError, read_json, write_json, identity, fixture, sha256

CATALOG = ROOT / 'layout/compiler-profiles.json'
TOPOLOGY = ROOT / 'evidence/topology/build-topology.json'
PROBES = ROOT / 'evidence/experiments/optimizer-profile/probes'
GOOD = {'CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'}


def catalog():
    return read_json(CATALOG)


def profile_flags(name, segment, cat=None):
    cat = cat or catalog()
    if name not in cat['profiles']:
        raise FormatError('unknown compiler profile ' + name)
    return list(cat['common_flags']) + list(cat['profiles'][name]['flags']) + [cat['segment_flag'] + segment]


def identify_profile(flags, cat=None):
    """Return (profile name, segment) for a full flag list, or raise."""
    cat = cat or catalog()
    flags = list(flags)
    segments = [f[len(cat['segment_flag']):] for f in flags if f.startswith(cat['segment_flag'])]
    if len(segments) != 1:
        raise FormatError('flags must name exactly one code segment')
    for name in cat['profiles']:
        if profile_flags(name, segments[0], cat) == flags:
            return name, segments[0]
    raise FormatError('flags do not match any catalog compiler profile: ' + ' '.join(flags))


_COMPONENTS = {}


def components():
    if not TOPOLOGY.exists():
        return {}
    stat = TOPOLOGY.stat()
    key = (stat.st_mtime_ns, stat.st_size)
    if key in _COMPONENTS:
        return _COMPONENTS[key]
    result = {}
    for unit in read_json(TOPOLOGY)['units']:
        for component in unit['components']:
            for public in component['publics']:
                result[public] = dict(id=component['id'], publics=component['publics'], segment=unit['segment'], range=unit['candidate_unit'])
    _COMPONENTS.clear()
    _COMPONENTS[key] = result
    return result


def component_of(symbol):
    return components().get(symbol)


def resolve(symbol, cat=None):
    cat = cat or catalog()
    comp = component_of(symbol)
    context_ids = set()
    for cid, ctx in cat['contexts'].items():
        if symbol in ctx['publics']:
            context_ids.add(cid)
    matches = [a for a in cat['assignments'] if symbol in a.get('symbols', []) or a.get('context') in context_ids]
    refuted = sorted({p for r in cat['refutations'] for p in r['profiles']
                      if symbol in r['symbols'] or any(s in cat['contexts'].get(cid, {}).get('publics', []) for cid in context_ids for s in r['symbols'])})
    if len({a['profile'] for a in matches}) > 1:
        raise FormatError('ambiguous compiler profile assignments for ' + symbol)
    if matches:
        a = matches[0]
        if a['profile'] in refuted:
            raise FormatError('assigned profile %s is refuted for the context of %s' % (a['profile'], symbol))
        return dict(name=a['profile'], basis='ASSIGNED', assignment=a['id'], context=a.get('context'), evidence=a['evidence'],
                    component=comp['id'] if comp else None, refuted_profiles=refuted)
    return dict(name=cat['default_profile'], basis='DEFAULT', assignment=None, context=next(iter(sorted(context_ids)), None), evidence=None,
                component=comp['id'] if comp else None, refuted_profiles=refuted)


def flags_for(symbol, segment):
    return profile_flags(resolve(symbol)['name'], segment)


def validate(cat=None):
    """Fail closed on any inconsistency between catalog, recipes and evidence."""
    cat = cat or catalog()
    problems = []
    for name, profile in cat['profiles'].items():
        if not profile.get('flags') or any(not re.fullmatch(r'/[A-Za-z][A-Za-z0-9]*', f) for f in profile['flags']):
            problems.append('profile %s has invalid flags' % name)
    if cat['default_profile'] not in cat['profiles']:
        problems.append('default profile missing from catalog')
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    for symbol, target in recipes.items():
        if target.get('compiler') != cat['compiler']:
            continue
        declared = target.get('profile', cat['default_profile'])
        try:
            found, segment = identify_profile(target['flags'], cat)
        except FormatError as exc:
            problems.append('%s: %s' % (symbol, exc))
            continue
        if found != declared:
            problems.append('%s: recipe flags are profile %s but the recipe declares %s' % (symbol, found, declared))
    ids = [a['id'] for a in cat['assignments']]
    if len(ids) != len(set(ids)):
        problems.append('duplicate assignment ids')
    changed = set(cat['invariance'].get('discriminating', {}))
    for a in cat['assignments']:
        if a['profile'] not in cat['profiles']:
            problems.append('assignment %s names unknown profile' % a['id'])
        scope = list(a.get('symbols', []))
        if a.get('context'):
            if a['context'] not in cat['contexts']:
                problems.append('assignment %s names unknown context' % a['id'])
            else:
                scope += cat['contexts'][a['context']]['publics']
        if not scope:
            problems.append('assignment %s has empty scope' % a['id'])
        for path in a.get('evidence', []):
            if not (ROOT / path).exists():
                problems.append('assignment %s cites missing evidence %s' % (a['id'], path))
        for r in cat['refutations']:
            if a['profile'] in r['profiles'] and set(r['symbols']) & set(scope):
                problems.append('assignment %s contradicts refutation %s' % (a['id'], r['id']))
        for symbol in scope:
            if symbol in recipes and recipes[symbol].get('profile', cat['default_profile']) != a['profile'] and symbol in changed and a['profile'] in cat['invariance']['discriminating'][symbol]:
                problems.append('assignment %s covers admitted %s whose object changes under %s' % (a['id'], symbol, a['profile']))
        if a.get('strength') not in ('STRICT', 'DIAGNOSTIC'):
            problems.append('assignment %s lacks a reviewed strength' % a['id'])
    for symbol in recipes:
        try:
            resolve(symbol, cat)
        except FormatError as exc:
            problems.append(str(exc))
    # One object is compiled once: every public of a build-topology component
    # must resolve to the same profile (a joint-compile merge can join
    # components that carried different assignments).
    topology = ROOT / 'evidence/topology/build-topology.json'
    if topology.exists():
        for unit in read_json(topology)['units']:
            for comp in unit['components']:
                names = set()
                for public in comp['publics']:
                    try:
                        names.add(resolve(public, cat)['name'])
                    except FormatError:
                        pass
                if len(names) > 1:
                    problems.append('component %s resolves to several profiles %s' % (comp['id'], sorted(names)))
    if problems:
        raise FormatError('compiler profile catalog invalid: ' + '; '.join(problems))
    return dict(profiles=sorted(cat['profiles']), assignments=len(cat['assignments']), contexts=len(cat['contexts']), refutations=len(cat['refutations']))


def best_candidate(symbol):
    """The symbol's best preserved draft (tools/drafts.py), never a new source."""
    from drafts import best_source
    source = best_source(symbol)
    if source is None or not source.exists():
        raise FormatError('no preserved draft for ' + symbol + '; pass --source')
    return source, None


def probe(symbol, source=None, out=None):
    """out: a directory for sweep records, so they never overwrite cited evidence."""
    from common import cards
    from codegen_cache import compile_cached
    from library_match import compare_member, import_symbols
    from codegen_diff import compare_code
    import omf, ne, mapsym
    cat = catalog()
    card = next(c for c in cards() if c['symbol'] == symbol)
    job_id = symbol.lstrip('_')
    if source is None:
        source, row = best_candidate(symbol)
    else:
        source, row = ROOT / source, None
    if not source.resolve().is_relative_to(ROOT):
        raise FormatError('probe source must be inside the repository')
    target = bytes.fromhex(''.join(r['bytes'] for r in card['disassembly']))
    names = sorted(cat['profiles'])
    folder = out or PROBES
    folder.mkdir(parents=True, exist_ok=True)
    stable = folder / (job_id + '.c')
    stable.write_bytes(source.read_bytes())
    jobs = [dict(source=stable.relative_to(ROOT).as_posix(), flags=profile_flags(name, card['segment_name'], cat)) for name in names]
    compiled, cache = compile_cached(jobs, cat['compiler'])
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM')); imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    results = {}
    for name, (obj, receipt) in zip(names, compiled):
        if obj is None or receipt['exit_code']:
            results[name] = dict(result='COMPILE_FAILED', log=receipt['stdout'][-400:])
            continue
        module = omf.parse(obj.read_bytes())
        strict = compare_member(module, raw, image, symbols, imports) or dict(result='UNPLACED', issues=[])
        code = bytes.fromhex(next(s for s in module['segments'] if s['class'] == 'CODE')['data_hex'])
        diag = compare_code(target, code)
        results[name] = dict(result=strict['result'], issues=len(strict.get('issues', [])), literal_equal=strict.get('literal_equal'), literal_compared=strict.get('literal_compared'),
                             fixups_equal=strict.get('fixups_equal'), fixups_total=strict.get('fixups_total'), candidate_bytes=len(code), target_bytes=len(target),
                             opcode_matches=diag.get('opcode_matches'), opcode_total=diag.get('opcode_total'), register_only_differences=diag.get('register_only_differences'),
                             object_identity=receipt.get('object_identity'), flags=receipt['flags'])
    def gain(r, base):
        if r.get('result') == 'COMPILE_FAILED' or not base:
            return 'NONE'
        strict_gain = r['result'] in GOOD and base.get('result') not in GOOD
        closer = abs((r.get('candidate_bytes') or 0) - r['target_bytes']) < abs((base.get('candidate_bytes') or 0) - base.get('target_bytes', 0))
        diag_gain = (r.get('opcode_matches') or 0) > (base.get('opcode_matches') or 0) or (closer and (r.get('opcode_matches') or 0) >= (base.get('opcode_matches') or 0))
        regression = (r.get('opcode_matches') or 0) < (base.get('opcode_matches') or 0)
        return 'STRICT' if strict_gain else 'DIAGNOSTIC' if diag_gain and not regression else 'NONE'
    # Discrimination against the baseline, and minimality against the parent
    # profile: every additional switch must earn its place.
    base = results.get(cat['default_profile'], {})
    discriminating = {name: gain(r, base) for name, r in results.items() if name != cat['default_profile']}
    def over_parents(name, r):
        outcomes = [gain(r, results.get(parent, {})) for parent in cat['profiles'][name].get('parents', [cat['default_profile']])]
        return 'NONE' if any(o == 'NONE' for o in outcomes) else 'STRICT' if all(o == 'STRICT' for o in outcomes) else 'DIAGNOSTIC'
    minimal = {name: over_parents(name, r) for name, r in results.items() if name != cat['default_profile']}
    record = dict(job=job_id, symbol=symbol, segment=card['segment_name'], source=stable.relative_to(ROOT).as_posix(), source_identity=identity(stable),
                  origin=str(source.relative_to(ROOT).as_posix()), origin_candidate=row['candidate'] if row else None, checked=datetime.now(timezone.utc).isoformat(),
                  component=(component_of(symbol) or {}).get('id'), string_ops=sorted({r['mnemonic'] for r in card['disassembly'] if any(x in r['mnemonic'] for x in ('stos', 'movs', 'scas', 'lods', 'cmps'))}),
                  results=results, discriminating=discriminating, minimal_over_parent=minimal, cache=cache,
                  scope='Bounded profile probe of one preserved candidate: evidence for a context assignment, never recovery credit or a queue change')
    path = folder / (job_id + '.json')
    write_json(path, record)
    return record


def _helper_address(symbol):
    match = re.fullmatch(r'helper:([1-9][0-9]*):([0-9A-Fa-f]{1,4})', str(symbol or ''))
    if not match:
        raise FormatError('invalid helper evidence symbol; expected helper:SEG:OFF')
    segment, offset = int(match.group(1)), int(match.group(2), 16)
    if segment < 1 or offset > 0xffff:
        raise FormatError('invalid helper evidence address')
    return segment, offset


def _component_bounds(component):
    match = re.fullmatch(r'[^:]+:([0-9A-Fa-f]{1,8})-([0-9A-Fa-f]{1,8})', str(component.get('range', '')))
    if not match:
        raise FormatError('helper evidence component has an ambiguous code range')
    start, end = (int(value, 16) for value in match.groups())
    if end <= start:
        raise FormatError('helper evidence component has an invalid code range')
    return start, end


def _validate_helper_evidence(record, context_id, context, context_publics):
    """Prove a helper record is in this member context's MAPSYM-bounded range."""
    from common import cards
    import mapsym
    import static_probe

    segment, offset = _helper_address(record.get('symbol'))
    caller = record.get('like')
    if caller not in context_publics:
        raise FormatError('helper evidence caller is not a member of the context')
    caller_cards = [card for card in cards() if card['symbol'] == caller]
    if len(caller_cards) != 1:
        raise FormatError('helper evidence caller is not an unambiguous MAPSYM member')
    caller_card = caller_cards[0]
    if caller_card['segment'] != segment:
        raise FormatError('helper evidence target and caller are in different segments')

    if not TOPOLOGY.exists():
        raise FormatError('helper evidence has no build-topology component bounds')
    topology_components = []
    topology_units = read_json(TOPOLOGY)['units']
    for unit in topology_units:
        for row in unit['components']:
            if caller in row['publics']:
                topology_components.append(dict(id=row['id'], publics=row['publics'],
                                                segment=unit['segment'], range=unit['candidate_unit']))
    if len(topology_components) != 1:
        raise FormatError('helper evidence caller has no unambiguous build-topology component')
    component = topology_components[0]
    if component.get('segment') != caller_card.get('segment_name'):
        raise FormatError('helper evidence caller has no unambiguous build-topology component')
    component_publics = set(component.get('publics', []))
    if caller not in component_publics:
        raise FormatError('helper evidence caller is not in its component')
    public_components = {}
    for public in context_publics:
        matches = []
        for unit in topology_units:
            for row in unit['components']:
                if public in row['publics']:
                    matches.append(row['id'])
        if len(matches) != 1:
            raise FormatError('helper evidence context contains an ambiguous topology public')
        public_components[public] = matches[0]
    if (not context_publics or not context_publics <= component_publics or
            set(public_components.values()) != {component['id']}):
        raise FormatError('helper evidence context spans more than one build-topology component')
    if context.get('segment') != component.get('segment'):
        raise FormatError('helper evidence context and component segments disagree')
    known_component_ids = {row['id'] for unit in topology_units for row in unit['components']}
    if context_id in known_component_ids and context_id != component.get('id'):
        raise FormatError('helper evidence caller is in a different component from the context')

    range_start, range_end = _component_bounds(component)
    if not range_start <= offset < range_end:
        raise FormatError('helper extent lies outside the context code range')

    # Recompute the original extent; caller-supplied JSON cannot widen it.
    target, _bindings, _names, extent = static_probe.original_bytes(segment, offset)
    actual = dict(start=offset, end=extent['end'], upper=extent['upper'],
                  status=extent.get('status'), target_bytes=len(target))
    if record.get('helper_extent') != actual:
        raise FormatError('helper evidence extent does not match the oracle helper extent')
    end = actual['end']
    if end <= offset or end > range_end or end > actual['upper']:
        raise FormatError('helper extent lies outside the context code range')

    symbol_table = mapsym.parse(fixture('SIMANTW.SYM'))
    if segment > len(symbol_table['segments']):
        raise FormatError('helper evidence names an unknown MAPSYM segment')
    publics = sorted((entry['offset'], entry['name'])
                     for entry in symbol_table['segments'][segment - 1]['symbols'])
    before = [(site, name) for site, name in publics if site < offset]
    after = [(site, name) for site, name in publics if site > offset]
    previous_offset = max((site for site, _name in before), default=None)
    previous_names = {name for site, name in before if site == previous_offset}
    if not previous_names or not previous_names <= context_publics:
        raise FormatError('helper is not between publics of the context')
    if not after or end > after[0][0]:
        raise FormatError('helper extent overlaps or crosses a MAPSYM public')
    if offset in {site for site, _name in publics}:
        raise FormatError('helper evidence address is a named MAPSYM entry')


def assign(context_id, profile, reason, evidence, symbols=None, strength=None,
           dry_run=False, supersede=None):
    cat = catalog()
    if profile not in cat['profiles'] or profile == cat['default_profile']:
        raise FormatError('assign a non-default catalog profile')
    if not reason.strip():
        raise FormatError('reviewed reason required')
    comp = None
    if context_id not in cat['contexts']:
        comps = {c['id']: c for c in components().values()}
        if context_id not in comps:
            raise FormatError('unknown context; use a build-topology component id or define the context first')
        comp = comps[context_id]
        cat['contexts'][context_id] = dict(publics=comp['publics'], segment=comp['segment'], source='evidence/topology/build-topology.json',
                                          basis='Same-object component (shared selector pool / private data / contiguity)', recorded=datetime.now(timezone.utc).isoformat())
    context_publics = set(cat['contexts'][context_id]['publics'])
    scope = context_publics | set(symbols or [])
    # Evidence must discriminate for a member of the scope.
    strengths = []
    minimal = []
    fingerprints = set()
    for path in evidence:
        record = read_json(ROOT / path)
        record_symbol = record.get('symbol')
        if isinstance(record_symbol, str) and record_symbol.startswith('helper:'):
            _validate_helper_evidence(record, context_id, cat['contexts'][context_id], context_publics)
        elif record_symbol not in scope:
            raise FormatError('evidence %s is not about a member of the context' % path)
        strengths.append(record['discriminating'].get(profile, 'NONE'))
        minimal.append(record.get('minimal_over_parent', {}).get(profile, 'NONE'))
        fingerprints.update(record.get('string_ops', []))
    if not strengths or all(s == 'NONE' for s in strengths):
        raise FormatError('evidence does not discriminate profile %s for this context' % profile)
    parents = cat['profiles'][profile].get('parents', [cat['default_profile']])
    if all(s == 'NONE' for s in minimal):
        raise FormatError('evidence does not justify profile %s over its parents %s; assign the minimal profile' % (profile, ', '.join(parents)))
    if 'i' in cat['profiles'][profile]['flags'][0][2:] and not fingerprints:
        raise FormatError('an intrinsic profile requires string-intrinsic fingerprints in the evidence targets')
    computed = 'STRICT' if 'STRICT' in strengths else 'DIAGNOSTIC'
    if strength and strength != computed:
        raise FormatError('requested strength %s disagrees with evidence (%s)' % (strength, computed))
    record = dict(id='asg-%s-%s' % (re.sub(r'[^a-z0-9]+', '-', context_id.lower()), profile), context=context_id, profile=profile, symbols=sorted(symbols or []),
                  strength=computed, evidence=list(evidence), reason=reason, reviewed=datetime.now(timezone.utc).isoformat())
    if supersede:
        old = [assignment for assignment in cat['assignments'] if assignment['id'] == supersede]
        if len(old) != 1 or old[0].get('context') != context_id:
            raise FormatError('--supersede must name one existing assignment for this context')
        cat['assignments'] = [assignment for assignment in cat['assignments'] if assignment['id'] != supersede]
        record['supersedes'] = supersede
    if any(a['id'] == record['id'] for a in cat['assignments']):
        raise FormatError('assignment already exists: ' + record['id'])
    cat['assignments'].append(record)
    validate(cat)
    if not dry_run:
        write_json(CATALOG, cat)
    return record


def probe_helper(address, source, function, like, out=None):
    """Sweep catalog profiles against an unnamed helper with static_probe's view."""
    from common import cards
    from codegen_cache import compile_cached
    from codegen_diff import compare_code, instructions
    import cfg_solver
    import mapsym
    import ne
    import omf
    import static_probe

    match = re.fullmatch(r'([1-9][0-9]*):([0-9A-Fa-f]{1,4})', str(address))
    if not match:
        raise FormatError('helper address must be SEG:OFF (decimal segment, hexadecimal offset)')
    segment, offset = int(match.group(1)), int(match.group(2), 16)
    caller = next((card for card in cards() if card['symbol'] == like), None)
    if caller is None:
        raise FormatError('unknown caller ' + str(like))
    if caller['segment'] != segment:
        raise FormatError('%s is in segment %d, not %d' % (like, caller['segment'], segment))

    source_path = Path(source)
    if not source_path.is_absolute():
        source_path = ROOT / source_path
    source_path = source_path.resolve()
    if not source_path.is_relative_to(ROOT.resolve()):
        raise FormatError('probe-helper source must be inside the repository')
    folder = Path(out) if out is not None else PROBES
    if not folder.is_absolute():
        folder = ROOT / folder
    folder = folder.resolve()
    if not folder.is_relative_to(ROOT.resolve()):
        raise FormatError('probe-helper output must be inside the repository')
    folder.mkdir(parents=True, exist_ok=True)
    job_id = 'helper_%d_%04X' % (segment, offset)
    stable = folder / (job_id + '.c')
    stable.write_bytes(source_path.read_bytes())

    target, target_bindings, names, extent = static_probe.original_bytes(segment, offset)
    raw = fixture('SIMANTW.EXE')
    image = ne.parse(raw)
    target_segment = image['segments'][segment - 1]
    target_code = raw[target_segment['file_offset']:target_segment['file_offset'] + target_segment['logical_size']]
    symbol_table = mapsym.parse(fixture('SIMANTW.SYM'))
    entries = [entry['offset'] for entry in symbol_table['segments'][segment - 1]['symbols']]
    target_graph = cfg_solver.solve(target_code, offset, extent['upper'], entries,
                                    target_segment['relocations'], segment)
    target_table_defs = [dict(start=table['table'] - offset, count=table['count'],
                              targets=table['targets'])
                         for table in target_graph.get('jump_tables', [])]
    target_table_spans = [(table['start'], table['count']) for table in target_table_defs]
    target_rows = instructions(target, target_bindings, target_table_spans)
    string_names = ('stos', 'movs', 'scas', 'lods', 'cmps')
    target_string_rows = [row for row in target_rows
                          if any(name in row['mnemonic'] for name in string_names)]
    string_ops = sorted({row['mnemonic'] for row in target_string_rows})
    if target_string_rows:
        first_index = target_rows.index(target_string_rows[0])
        last_index = target_rows.index(target_string_rows[-1])
        start_index = max(0, first_index - 9)
        end_index = min(len(target_rows), last_index + 3)
        string_span = (target_rows[start_index]['offset'],
                       target_rows[end_index - 1]['offset'] + target_rows[end_index - 1]['size'])
    else:
        string_span = None

    def normalized_table_view(code, bindings, tables, code_base):
        view = bytearray(code)
        bound = {pos: dict(target) if isinstance(target, dict) else target
                 for pos, target in bindings.items()}
        spans = []
        for table in tables:
            start, count = table['start'], table['count']
            spans.append((start, count))
            for index, target_offset in enumerate(table['targets']):
                pos = start + 2 * index
                if not 0 <= pos <= len(view) - 2:
                    raise FormatError('jump table lies outside the helper body')
                view[pos:pos + 2] = ((target_offset - code_base) & 0xffff).to_bytes(2, 'little')
                target_binding = bound.get(pos)
                if isinstance(target_binding, dict) and target_binding.get('kind') == 'internal':
                    adjusted = dict(target_binding)
                    adjusted['offset'] = adjusted['offset'] - code_base
                    bound[pos] = adjusted
        return bytes(view), bound, spans

    normalized_target, normalized_target_bindings, normalized_target_tables = normalized_table_view(
        target, target_bindings, target_table_defs, offset)

    cat = catalog()
    profile_names = sorted(cat['profiles'])
    jobs = [dict(source=stable.relative_to(ROOT).as_posix(),
                 flags=profile_flags(name, caller['segment_name'], cat)) for name in profile_names]
    compiled, cache = compile_cached(jobs, cat['compiler'])
    results = {}
    for name, (obj, receipt) in zip(profile_names, compiled):
        if obj is None or receipt.get('exit_code'):
            results[name] = dict(result='COMPILE_FAILED', log=receipt.get('stdout', '')[-400:],
                                 flags=receipt.get('flags'))
            continue
        try:
            compared = static_probe.compare_object(address, obj, function, like)
        except Exception as exc:
            results[name] = dict(result='COMPILE_FAILED', error='%s: %s' % (type(exc).__name__, exc),
                                 flags=receipt['flags'], object_identity=receipt.get('object_identity'))
            continue
        diagnostic = compared['diagnostic']
        diagnostic_basis = 'static_probe'
        try:
            module = omf.parse(obj.read_bytes())
            pubs = [public for public in module['publics']
                    if public['name'].lstrip('_') == function.lstrip('_') and public['segment']]
            if len(pubs) != 1:
                raise FormatError('candidate helper public is ambiguous')
            public = pubs[0]
            code_segment = module['segments'][public['segment'] - 1]
            candidate_code_segment = bytes.fromhex(code_segment['data_hex'])
            following = [item['offset'] for item in module['publics']
                         if item['segment'] == public['segment'] and item['offset'] > public['offset']]
            candidate_limit = min(following + [len(candidate_code_segment)])
            candidate_graph = cfg_solver.solve(candidate_code_segment, public['offset'], candidate_limit)
            candidate_view, candidate_bindings = static_probe.candidate_bytes(
                obj, function, segment, offset, names)
            candidate_table_defs = [dict(start=table['table'] - public['offset'], count=table['count'],
                                          targets=table['targets'])
                                    for table in candidate_graph.get('jump_tables', [])]
            if (target_graph.get('status') == 'PROBABLE' and
                    candidate_graph.get('status') == 'PROBABLE' and
                    len(candidate_view) == candidate_graph['end'] - public['offset']):
                normalized_candidate, normalized_candidate_bindings, candidate_tables = normalized_table_view(
                    candidate_view, candidate_bindings, candidate_table_defs, public['offset'])
                diagnostic = compare_code(
                    normalized_target, normalized_candidate,
                    normalized_target_bindings, normalized_candidate_bindings,
                    target_tables=normalized_target_tables, candidate_tables=candidate_tables)
                diagnostic_basis = 'static_probe plus recursive CFG switch-table decoding'
        except Exception:
            # The base static_probe result remains useful if either compiler
            # switch cannot be proven by the conservative CFG solver.
            pass
        region_rows = []
        region_target_rows = []
        if string_span:
            region_start, region_end = string_span
            region_target_rows = [row for row in target_rows
                                  if region_start <= row['offset'] < region_end and row['mnemonic'] != 'dw']
            region_rows = [row for row in diagnostic.get('aligned_asm', [])
                           if row.get('target_offset') is not None and
                           region_start <= row['target_offset'] < region_end]
        region_matches = sum('instruction_shape' not in row.get('differences', [])
                             for row in region_rows)
        exact = bool(compared.get('exact_match'))
        result = dict(result='CONFIRMED_MEMBER' if exact else 'NO_COMPLETE_MATCH',
                      exact_match=exact, issues=0 if exact else 1,
                      candidate_bytes=diagnostic.get('candidate_bytes'), target_bytes=len(target),
                      opcode_matches=diagnostic.get('opcode_matches'), opcode_total=diagnostic.get('opcode_total'),
                      register_only_differences=diagnostic.get('register_only_differences'),
                      diagnostic_basis=diagnostic_basis,
                      static_probe_opcode_matches=compared['diagnostic'].get('opcode_matches'),
                      static_probe_opcode_total=compared['diagnostic'].get('opcode_total'),
                      object_identity=receipt.get('object_identity'), flags=receipt['flags'],
                      first_structural_difference=diagnostic.get('first_structural_difference'))
        if string_span:
            result['string_region'] = dict(
                target_start=string_span[0], target_end=string_span[1],
                address_start='%d:%04X' % (segment, offset + string_span[0]),
                address_end='%d:%04X' % (segment, offset + string_span[1]),
                opcode_matches=region_matches, opcode_total=len(region_target_rows),
                aligned_asm=region_rows)
        results[name] = result

    def gain(candidate, base):
        if candidate.get('result') == 'COMPILE_FAILED' or not base:
            return 'NONE'
        strict_gain = candidate['result'] in GOOD and base.get('result') not in GOOD
        closer = abs((candidate.get('candidate_bytes') or 0) - len(target)) < abs(
            (base.get('candidate_bytes') or 0) - len(target))
        diagnostic_gain = ((candidate.get('opcode_matches') or 0) > (base.get('opcode_matches') or 0) or
                           (closer and (candidate.get('opcode_matches') or 0) >= (base.get('opcode_matches') or 0)))
        regression = (candidate.get('opcode_matches') or 0) < (base.get('opcode_matches') or 0)
        return 'STRICT' if strict_gain else 'DIAGNOSTIC' if diagnostic_gain and not regression else 'NONE'

    base = results.get(cat['default_profile'], {})
    discriminating = {name: gain(result, base) for name, result in results.items()
                      if name != cat['default_profile']}
    minimal = {}
    for name, result in results.items():
        if name == cat['default_profile']:
            continue
        outcomes = [gain(result, results.get(parent, {})) for parent in
                    cat['profiles'][name].get('parents', [cat['default_profile']])]
        minimal[name] = ('NONE' if any(value == 'NONE' for value in outcomes) else
                         'STRICT' if all(value == 'STRICT' for value in outcomes) else 'DIAGNOSTIC')

    helper_extent = dict(start=offset, end=extent['end'], upper=extent['upper'],
                         status=extent.get('status'), target_bytes=len(target))
    record = dict(job=job_id, symbol='helper:%d:%04X' % (segment, offset), like=like,
                  function=function, segment=caller['segment_name'],
                  source=stable.relative_to(ROOT).as_posix(), source_identity=identity(stable),
                  origin=source_path.relative_to(ROOT).as_posix(), origin_candidate=None,
                  checked=datetime.now(timezone.utc).isoformat(),
                  component=(component_of(like) or {}).get('id'), helper_extent=helper_extent,
                  string_ops=string_ops, results=results, discriminating=discriminating,
                  minimal_over_parent=minimal, cache=cache,
                  scope='Bounded helper profile probe using static_probe fixup binding and LINK far-call translation')
    write_json(folder / (job_id + '.json'), record)
    return record


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest='action', required=True)
    sub.add_parser('validate')
    p = sub.add_parser('show'); p.add_argument('symbol')
    p = sub.add_parser('probe'); p.add_argument('symbol'); p.add_argument('--source'); p.add_argument('--out', help='directory for the record (default: the cited evidence directory); use a build/ path for exploratory variants')
    p = sub.add_parser('probe-helper'); p.add_argument('address'); p.add_argument('source'); p.add_argument('--function', required=True); p.add_argument('--like', required=True); p.add_argument('--out', help='directory for the record (default: the evidence directory; use a build/ path for exploratory variants)')
    p = sub.add_parser('assign'); p.add_argument('context'); p.add_argument('profile'); p.add_argument('--reason', required=True); p.add_argument('--evidence', action='append', required=True); p.add_argument('--symbol', action='append')
    p.add_argument('--dry-run', action='store_true', help='validate the proposed assignment without writing the catalog')
    p.add_argument('--supersede', help='replace an existing assignment for this same context after all gates pass')
    args = ap.parse_args()
    if args.action == 'validate':
        print(json.dumps(validate(), indent=2))
    elif args.action == 'show':
        print(json.dumps(resolve(args.symbol), indent=2))
    elif args.action == 'probe':
        record = probe(args.symbol, args.source, out=(ROOT / args.out) if args.out else None)
        print(json.dumps(dict(job=record['job'], discriminating=record['discriminating'], results={k: (v['result'], v.get('opcode_matches'), v.get('opcode_total'), v.get('candidate_bytes')) for k, v in record['results'].items()}), indent=2))
    elif args.action == 'probe-helper':
        record = probe_helper(args.address, args.source, args.function, args.like,
                              out=(ROOT / args.out) if args.out else None)
        print(json.dumps(dict(job=record['job'], symbol=record['symbol'], like=record['like'],
                              helper_extent=record['helper_extent'], string_ops=record['string_ops'],
                              discriminating=record['discriminating'], minimal_over_parent=record['minimal_over_parent'],
                              results={k: (v['result'], v.get('opcode_matches'), v.get('opcode_total'),
                                           v.get('candidate_bytes'),
                                           (v.get('string_region') or {}).get('opcode_matches'),
                                           (v.get('string_region') or {}).get('opcode_total'))
                                       for k, v in record['results'].items()}), indent=2))
    else:
        assigned = assign(args.context, args.profile, args.reason, args.evidence, args.symbol,
                          dry_run=args.dry_run, supersede=args.supersede)
        print(json.dumps(dict(dry_run=True, assignment=assigned) if args.dry_run else assigned, indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
