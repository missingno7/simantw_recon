"""Translation-unit assembly lane: compile several preserved sources as one unit.

An isolated function cannot reproduce a historical object's private selector
pool, private DATA/BSS/CONST or string ordering. This lane composes the
preserved exact-body sources of a build-topology component (or a reviewed
explicit group) into one candidate translation unit, compiles it under the
context's compiler profile and compares every contribution with the strict
member matcher. Admission still goes through the workflow's fresh promotion.

Unit identities are internal evidence ids (topology component ids); no
historical filename is claimed. Function bodies are never rewritten here.
"""
import argparse
import json
import re
from datetime import datetime, timezone
from common import ROOT, FormatError, read_json, write_json, identity, sha256

UNITS = ROOT / 'evidence/recovery/units'
TOPOLOGY = ROOT / 'evidence/topology/build-topology.json'


def timestamp():
    return datetime.now(timezone.utc).isoformat()


def strip_comments(text):
    return re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)


def split_items(text):
    """Split a C file into top-level items: comments, declarations, definitions.

    Only the subset used by the recovered corpus is understood (no preprocessor,
    no assembly). Braces, parentheses and string/char literals are tracked so
    that declarations end at a top-level ';' and definitions at their closing
    brace.
    """
    items = []
    i = 0
    n = len(text)
    while i < n:
        c = text[i]
        if c.isspace():
            i += 1
            continue
        if text.startswith('/*', i):
            j = text.index('*/', i) + 2
            items.append(dict(kind='comment', text=text[i:j]))
            i = j
            continue
        if text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            items.append(dict(kind='comment', text=text[i:j]))
            i = j
            continue
        if c == '#':
            j = text.find('\n', i)
            j = n if j < 0 else j
            line = text[i:j].strip()
            if not line.startswith('#define'):
                raise FormatError('only #define directives are composable: ' + line[:40])
            name = re.match(r'#define\s+([A-Za-z_]\w*)', line)
            items.append(dict(kind='declaration', names=[name.group(1)] if name else [], text=line, normalized=' '.join(line.split())))
            i = j
            continue
        start = i
        depth_brace = depth_paren = 0
        seen_brace = False
        while i < n:
            c = text[i]
            if c in '"\'':
                q = c
                i += 1
                while i < n and text[i] != q:
                    i += 2 if text[i] == '\\' else 1
                i += 1
                continue
            if text.startswith('/*', i):
                i = text.index('*/', i) + 2
                continue
            if c == '(':
                depth_paren += 1
            elif c == ')':
                depth_paren -= 1
            elif c == '{':
                depth_brace += 1
                seen_brace = True
            elif c == '}':
                depth_brace -= 1
                if depth_brace == 0 and seen_brace:
                    i += 1
                    # An initialiser or struct/typedef ends with ';' after '}'.
                    k = i
                    while k < n and text[k].isspace():
                        k += 1
                    if k < n and text[k] == ';':
                        i = k + 1
                    break
            elif c == ';' and depth_brace == 0 and depth_paren == 0:
                i += 1
                break
            i += 1
        item_text = text[start:i].strip()
        code = strip_comments(item_text)
        if not code.strip():
            continue
        head = code.split('{', 1)[0]
        is_definition = seen_brace and '(' in head and not re.match(r'\s*(typedef|struct|union|enum)\b', head) and '=' not in head.split('(')[0]
        if is_definition:
            name = re.findall(r'([A-Za-z_]\w*)\s*\(', head)[-1] if re.findall(r'([A-Za-z_]\w*)\s*\(', head) else None
            items.append(dict(kind='definition', name=name, text=item_text))
        else:
            names = declared_names(code)
            items.append(dict(kind='declaration', names=names, text=item_text, normalized=signature_form(code)))
    return items


def signature_form(code):
    """Declaration text with parameter names removed, so prototypes that differ
    only in parameter naming compare equal."""
    code = ' '.join(code.split())
    def strip(m):
        params = [p.strip() for p in m.group(1).split(',')]
        out = []
        for p in params:
            tokens = p.replace('*', ' * ').split()
            if len(tokens) >= 2 and re.fullmatch(r'[A-Za-z_]\w*', tokens[-1]) and tokens[-1] not in ('void', 'int', 'char', 'long', 'short', 'unsigned', 'signed', 'far', 'near', 'double', 'float'):
                tokens = tokens[:-1]
            out.append(' '.join(tokens).replace(' * ', '*'))
        return '(' + ', '.join(out) + ')'
    return re.sub(r'\(([^()]*)\)(?=\s*;)', strip, code)


def declared_names(code):
    """Identifiers introduced by a declaration (extern, static, typedef, plain)."""
    code = ' '.join(code.split())
    # __based(__segname("X")) is a storage qualifier, never the declared name.
    code = re.sub(r'__based\s*\(\s*__segname\s*\(\s*"[^"]*"\s*\)\s*\)', ' ', code)
    if re.match(r'\s*typedef\b', code):
        m = re.search(r'([A-Za-z_]\w*)\s*(\[[^\]]*\])*\s*;\s*$', code)
        return [m.group(1)] if m else []
    if re.match(r'\s*(struct|union|enum)\s+[A-Za-z_]\w*\s*\{', code):
        m = re.match(r'\s*(struct|union|enum)\s+([A-Za-z_]\w*)', code)
        return [m.group(1) + ' ' + m.group(2)]
    head = code.split('=', 1)[0]
    head = re.sub(r'\([^()]*\)', '()', head)
    head = re.sub(r'\([^()]*\)', '()', head)
    names = re.findall(r'\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*(?:\(\)|,|;|$|\))', head)
    keywords = {'extern', 'static', 'far', 'near', 'int', 'char', 'long', 'short', 'unsigned', 'signed', 'void', 'pascal', 'const', 'struct', 'union', 'enum', 'float', 'double', 'huge', 'cdecl', 'volatile', 'register'}
    return [n for n in names if n not in keywords]


def compose(sources, order, unit_id, layout='preambles-first', overrides=None):
    """Merge preserved sources into one unit; conflicts are reported, not resolved."""
    overrides = overrides or {}
    files = []
    for symbol in order:
        path = ROOT / sources[symbol]
        items = split_items(path.read_text(encoding='latin1'))
        definitions = [it for it in items if it['kind'] == 'definition']
        if not any(it['name'] == symbol.lstrip('_') for it in definitions):
            raise FormatError('source for %s does not define it: %s' % (symbol, sources[symbol]))
        files.append(dict(symbol=symbol, source=sources[symbol], identity=identity(path), items=items))
    declarations = []
    seen = {}
    conflicts = []
    definitions = []
    emitted_overrides = set()
    for f in files:
        for it in f['items']:
            if it['kind'] == 'declaration':
                key_names = it['names'] or [it['normalized']]
                # A reviewed override replaces every declaration of that name
                # with one recorded spelling, emitted at its first occurrence.
                if any(name in overrides for name in key_names):
                    for name in key_names:
                        if name in overrides and name not in emitted_overrides:
                            emitted_overrides.add(name)
                            declarations.append(dict(kind='declaration', names=[name], text=overrides[name].strip(), normalized=' '.join(overrides[name].split()), origin='override'))
                    continue
                for name in key_names:
                    previous = seen.get(name)
                    if previous is None:
                        seen[name] = (it['normalized'], f['symbol'])
                    elif previous[0] != it['normalized']:
                        conflicts.append(dict(name=name, first=previous[0], first_from=previous[1], other=it['normalized'], other_from=f['symbol']))
                if any(seen[name][1] == f['symbol'] and seen[name][0] == it['normalized'] for name in key_names if name in seen):
                    if it['normalized'] not in [d['normalized'] for d in declarations]:
                        declarations.append(dict(it, origin=f['symbol']))
            elif it['kind'] == 'definition':
                # A preserved unit source may already define several members;
                # each definition is emitted once, in MAPSYM order below.
                if any(d['name'] == it['name'] for d in definitions):
                    continue
                if it['name'] == f['symbol'].lstrip('_') or ('_' + it['name']) in sources:
                    definitions.append(dict(it, origin=f['symbol']))
                else:
                    # A helper (e.g. static function) defined by a preserved source.
                    definitions.append(dict(it, origin=f['symbol'], helper=True))
    # Unresolved conflicts stop composition: a reviewed override must choose.
    if conflicts:
        return dict(status='DECLARATION_CONFLICT', conflicts=conflicts, files=[{k: v for k, v in f.items() if k != 'items'} for f in files])
    header = ['/* Candidate translation unit %s: composed from preserved exact-body sources' % unit_id,
              ' * in MAPSYM order. Internal evidence id, not a historical filename.',
              ' * Members: %s */' % ', '.join(order), '']
    lines = list(header)
    if layout == 'preambles-first':
        for d in declarations:
            lines.append(d['text'])
        lines.append('')
        rank = {m.lstrip('_'): i for i, m in enumerate(order)}
        for d in sorted(definitions, key=lambda d: rank.get(d['name'], len(rank))):
            lines.append(d['text'])
            lines.append('')
    else:
        # Each file's declarations immediately precede its definition.
        emitted = set()
        for f in files:
            for it in f['items']:
                if it['kind'] == 'declaration' and it['normalized'] not in emitted and any(d['normalized'] == it['normalized'] for d in declarations):
                    lines.append(it['text'])
                    emitted.add(it['normalized'])
            for d in definitions:
                if d['origin'] == f['symbol']:
                    lines.append(d['text'])
                    lines.append('')
    return dict(status='COMPOSED', text='\n'.join(lines) + '\n', files=[{k: v for k, v in f.items() if k != 'items'} for f in files],
                declarations=len(declarations), definitions=[d['name'] for d in definitions], layout=layout, overrides=sorted(overrides))


def preserved_sources():
    """Best preserved source per symbol: admitted recipe, else body-solved / best job candidate."""
    result = {}
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    for symbol, target in recipes.items():
        result[symbol] = dict(source=target['source'], basis='ADMITTED', profile=target.get('profile', 'baseline'))
    families = ROOT / 'evidence/recovery/blocker-families.json'
    if families.exists():
        for symbol, f in read_json(families)['functions'].items():
            if symbol in result:
                continue
            if f.get('preserved_source'):
                result[symbol] = dict(source=f['preserved_source'], basis='BODY_MATCHED_BINDING_BLOCKED')
    for path in (ROOT / 'evidence/recovery/workflow/jobs').glob('*/job.json'):
        job = read_json(path)
        if job['symbol'] in result or job.get('lane') == 'TU_ASSEMBLY' or not job.get('attempts'):
            continue
        best = None
        for attempt in job['attempts']:
            report_path = ROOT / attempt['report']
            if not report_path.exists():
                continue
            report = read_json(report_path)
            for row in report['results']:
                d = (row.get('comparison') or {}).get('diagnostic') or {}
                if d.get('opcode_matches') is None:
                    continue
                exact_body = d.get('instruction_layout_match') is True and d.get('opcode_matches') == d.get('opcode_total') and d.get('register_only_differences', 1) == 0 and d.get('branch_target_differences', 1) == 0
                key = (exact_body, d['opcode_matches'], -abs(d.get('candidate_bytes', 0) - d.get('target_bytes', 0)))
                source = ROOT / row['receipt']['source']
                if source.exists() and (best is None or key > best[0]):
                    best = (key, source.relative_to(ROOT).as_posix(), exact_body)
        if best:
            result[job['symbol']] = dict(source=best[1], basis='EXACT_BODY_CANDIDATE' if best[2] else 'BEST_CANDIDATE_NOT_EXACT')
    return result


def topology_units():
    if not TOPOLOGY.exists():
        raise FormatError('run tools/build_topology.py first')
    report = read_json(TOPOLOGY)
    result = {}
    for unit in report['units']:
        for component in unit['components']:
            result[component['id']] = dict(component, segment=unit['segment'], range=unit['candidate_unit'])
    return result


def pool_words_in_code_order(symbol, functions):
    """Selector-pool words a function loads, in code (first-use) order."""
    return [int(w, 16) if isinstance(w, str) else w for w in functions[symbol]['slots']]


def predicted_pool(order, functions):
    """First-use order of pool words when the given functions are compiled together in this order."""
    seen = []
    for symbol in order:
        for w in pool_words_in_code_order(symbol, functions):
            if w not in seen:
                seen.append(w)
    return seen


def assemblable(group, functions):
    """A subset reproduces its pool only if its words are one contiguous original
    block in the same order as the composed first-use order (predicted from code)."""
    words = predicted_pool(group, functions)
    if not words:
        return True, 'no pool words'
    expected = sorted(words)
    if any(b - a != 2 for a, b in zip(expected, expected[1:])):
        return False, 'pool words are not contiguous in the original: %s' % ' '.join('%04X' % w for w in expected)
    if words != expected:
        return False, 'composed first-use order %s differs from the original pool order' % ' '.join('%04X' % w for w in words)
    return True, 'contiguous pool block %04X-%04X' % (expected[0], expected[-1])


def propose(min_functions=1):
    """Candidate unit groups per component: usable preserved sources whose selector
    pool is predicted to reproduce, plus the missing introducers that block the rest."""
    sources = preserved_sources()
    functions = read_json(TOPOLOGY)['functions']
    rows = []
    for cid, comp in topology_units().items():
        members = comp['publics']
        if len(members) < min_functions:
            continue
        have = {m: sources.get(m) for m in members}
        usable = [m for m in members if have[m] and have[m]['basis'] in ('ADMITTED', 'BODY_MATCHED_BINDING_BLOCKED', 'EXACT_BODY_CANDIDATE')]
        missing = [m for m in members if m not in usable]
        # Greedy scan in code order: extend the group while the predicted pool
        # still reproduces; a member that breaks it is skipped and its blocking
        # words attributed to their original introducers.
        # A composed unit's code is contiguous, so a group must be a run of
        # consecutive members (a missing member ends the run) whose predicted
        # pool block is contiguous and in order.
        groups = []
        current = []
        blocked = {}
        for m in members:
            if m not in usable:
                if current:
                    groups.append(current)
                current = []
                continue
            ok, why = assemblable(current + [m], functions)
            if ok:
                current.append(m)
            else:
                if current:
                    groups.append(current)
                current = [m] if assemblable([m], functions)[0] else []
                introducers = sorted({functions[x]['symbol'] for x in members for w in pool_words_in_code_order(m, functions) if w in pool_words_in_code_order(x, functions) and x in missing})
                blocked[m] = dict(reason=why, missing_introducers=introducers)
        if current:
            groups.append(current)
        groups = [g for g in groups if any(have[m]['basis'] != 'ADMITTED' for m in g)]
        unlock = sum(1 for g in groups for m in g if have[m]['basis'] != 'ADMITTED')
        rows.append(dict(component=cid, segment=comp['segment'], range=comp['range'], members=members, usable=usable, missing=missing,
                         groups=groups, blocked=blocked, unlock=unlock, join_evidence=comp.get('join_evidence'), complete=not missing))
    rows.sort(key=lambda r: (-r['unlock'], r['component']))
    return rows


def build_unit(component_id, members=None, layout='preambles-first', overrides=None, reason='', source_overrides=None, unit_source=None):
    """Compose a candidate unit from preserved sources and write its evidence folder."""
    import compiler_profiles
    from recovery_workflow import cards
    comps = topology_units()
    if component_id not in comps:
        raise FormatError('unknown build-topology component ' + component_id)
    comp = comps[component_id]
    members = members or comp['publics']
    if any(m not in comp['publics'] for m in members):
        raise FormatError('members must belong to the component')
    order = [m for m in comp['publics'] if m in members]
    if order != members:
        raise FormatError('members must be given in MAPSYM order')
    if unit_source is not None:
        # A reviewed hand-written unit (publics plus static helpers between them).
        path = ROOT / unit_source
        if not path.exists() or not path.resolve().is_relative_to(ROOT):
            raise FormatError('unit source must be a repository file')
        text = path.read_text(encoding='latin1')
        for m in members:
            if not re.search(r'\b' + re.escape(m.lstrip('_')) + r'\s*\(', text):
                raise FormatError('unit source does not define ' + m)
        import compiler_profiles
        names = {compiler_profiles.resolve(m)['name'] for m in members}
        if len(names) != 1:
            raise FormatError('members resolve to different compiler profiles: ' + str(names))
        profile = next(iter(names))
        unit_id = re.sub(r'[^A-Za-z0-9]+', '_', component_id) + '_%s_%d_reviewed' % (members[0].lstrip('_'), len(members))
        folder = UNITS / unit_id
        folder.mkdir(parents=True, exist_ok=True)
        (folder / 'unit.c').write_text(text, encoding='latin1')
        spec = dict(unit=unit_id, component=component_id, segment=comp['segment'], members=members, sources={'*': dict(source=unit_source, basis='REVIEWED_UNIT_SOURCE', identity=identity(path))},
                    profile=profile, flags=compiler_profiles.profile_flags(profile, comp['segment']), layout='reviewed', overrides={}, reason=reason, created=timestamp(),
                    topology=dict(join_evidence=comp.get('join_evidence'), range=comp['range']), status='COMPOSED', source=(folder / 'unit.c').relative_to(ROOT).as_posix(), source_identity=identity(folder / 'unit.c'))
        write_json(folder / 'unit.json', spec)
        return spec
    sources = preserved_sources()
    for m, path in (source_overrides or {}).items():
        if not (ROOT / path).exists() or not (ROOT / path).resolve().is_relative_to(ROOT):
            raise FormatError('reviewed source override must be a repository file: ' + path)
        sources[m] = dict(source=path, basis='REVIEWED_SOURCE_OVERRIDE')
    chosen = {}
    for m in members:
        if m not in sources:
            raise FormatError('no preserved source for ' + m)
        chosen[m] = sources[m]['source']
    unit_id = re.sub(r'[^A-Za-z0-9]+', '_', component_id) + ('' if members == comp['publics'] else '_%s_%d' % (members[0].lstrip('_'), len(members)))
    folder = UNITS / unit_id
    folder.mkdir(parents=True, exist_ok=True)
    result = compose(chosen, order, unit_id, layout, overrides)
    profiles = {m: compiler_profiles.resolve(m) for m in members}
    names = {p['name'] for p in profiles.values()}
    if len(names) != 1:
        raise FormatError('members resolve to different compiler profiles: ' + str(names))
    profile = next(iter(names))
    segment = comp['segment']
    spec = dict(unit=unit_id, component=component_id, segment=segment, members=members, sources={m: dict(sources[m], identity=identity(ROOT / sources[m]['source'])) for m in members},
                profile=profile, flags=compiler_profiles.profile_flags(profile, segment), layout=layout, overrides=overrides or {}, reason=reason, created=timestamp(),
                topology=dict(join_evidence=comp.get('join_evidence'), range=comp['range']), status=result['status'])
    if result['status'] != 'COMPOSED':
        spec['conflicts'] = result['conflicts']
        write_json(folder / 'unit.json', spec)
        return spec
    (folder / 'unit.c').write_text(result['text'], encoding='latin1')
    spec.update(source=(folder / 'unit.c').relative_to(ROOT).as_posix(), source_identity=identity(folder / 'unit.c'), declarations=result['declarations'], definitions=result['definitions'])
    write_json(folder / 'unit.json', spec)
    return spec


def test_unit(unit_id):
    """Compile the composed unit and compare all contributions; diagnostic only."""
    from codegen_grinder import run
    folder = UNITS / unit_id
    spec = read_json(folder / 'unit.json')
    if spec['status'] != 'COMPOSED':
        raise FormatError('unit is not composed: ' + spec['status'])
    if identity(ROOT / spec['source']) != spec['source_identity']:
        raise FormatError('unit source changed since composition')
    grinder_spec = dict(symbol=spec['members'][0], source=spec['source'], compiler='msc700', flags=spec['flags'], max_candidates=1, axes=[],
                        semantic_summary='Unit assembly of preserved sources: ' + unit_id, publics=spec['members'])
    report = run(grinder_spec, (folder / 'test').relative_to(ROOT).as_posix(), cache=True)
    best = report['results'][0]
    comparison = best['comparison']
    summary = dict(unit=unit_id, result=comparison['result'], issues=comparison.get('issues', []), placements=comparison.get('placements'),
                   private_constraint_placements=comparison.get('private_constraint_placements'), literal_equal=comparison.get('literal_equal'), literal_compared=comparison.get('literal_compared'),
                   fixups_equal=comparison.get('fixups_equal'), fixups_total=comparison.get('fixups_total'),
                   contributions=[dict(segment=c['segment'], original_offset=c['original_offset'], length=c['length'], divergences=len(c['divergences']), failed_fixups=sum(1 for f in c['fixups'] if not f['equal'])) for c in comparison.get('contributions', [])],
                   compiler_log=best['receipt']['stdout'][-600:] if comparison['result'] == 'COMPILE_FAILED' else None, report=(folder / 'test/results.json').relative_to(ROOT).as_posix(), tested=timestamp())
    spec['last_test'] = summary
    write_json(folder / 'unit.json', spec)
    return summary


def unit_job(unit_id, reason):
    """Create a TU_ASSEMBLY workflow job so admission uses the ordinary fresh promotion path."""
    import recovery_workflow as wf
    folder = UNITS / unit_id
    spec = read_json(folder / 'unit.json')
    if spec['status'] != 'COMPOSED':
        raise FormatError('unit is not composed')
    if not spec.get('last_test') or spec['last_test']['result'] not in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
        raise FormatError('unit has no exact test result; a job is only issued for an exact unit')
    if not reason.strip():
        raise FormatError('reviewed reason required')
    recipes = wf.recipes()
    members = spec['members']
    supersedes = [m for m in members if m in recipes]
    key = sha256((unit_id + spec['source_identity']['sha256']).encode())[:10]
    job_id = 'tu_' + unit_id + '-' + key
    directory = wf.STATE / 'jobs' / job_id
    if directory.exists():
        raise FormatError('unit job already exists: ' + job_id)
    directory.mkdir(parents=True)
    candidate = directory / 'candidate.c'
    candidate.write_bytes((ROOT / spec['source']).read_bytes())
    submission = dict(symbol=members[0], source=wf.relative(candidate), compiler='msc700', flags=spec['flags'], max_candidates=1, axes=[],
                      semantic_summary='Unit assembly %s: %s' % (unit_id, reason), binding_evidence=['evidence/topology/build-topology.json', wf.relative(folder / 'unit.json')], publics=members)
    write_json(directory / 'submission.json', submission)
    job = dict(id=job_id, symbol=members[0], lane='TU_ASSEMBLY', unit=unit_id, component=spec['component'], publics=members, supersedes=supersedes,
               status='OPEN', created=wf.timestamp(), flags=spec['flags'], profile=__import__('compiler_profiles').resolve(members[0]), protected=wf.protected(),
               fixture_identity=read_json(ROOT / 'layout/fixtures.json'), attempts=[], reason=reason, unit_evidence=wf.relative(folder / 'unit.json'))
    wf.atomic_json(directory / 'job.json', job)
    (directory / 'packet.md').write_text('# Unit assembly job %s\n\nMembers: %s\n\nEvidence: %s\n' % (job_id, ', '.join(members), wf.relative(folder / 'unit.json')), encoding='utf-8')
    return dict(job=job_id, publics=members, supersedes=supersedes)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest='action', required=True)
    p = sub.add_parser('propose'); p.add_argument('--min', type=int, default=1); p.add_argument('--limit', type=int, default=40)
    p = sub.add_parser('build'); p.add_argument('component'); p.add_argument('--members'); p.add_argument('--layout', default='preambles-first', choices=['preambles-first', 'interleaved']); p.add_argument('--override', action='append', default=[]); p.add_argument('--source', action='append', default=[], help='SYMBOL=path reviewed source override'); p.add_argument('--unit-source', help='reviewed hand-written unit source (publics plus static helpers)'); p.add_argument('--reason', default='')
    p = sub.add_parser('test'); p.add_argument('unit')
    p = sub.add_parser('job'); p.add_argument('unit'); p.add_argument('--reason', required=True)
    args = ap.parse_args()
    if args.action == 'propose':
        rows = propose(args.min)
        for r in rows[:args.limit]:
            print('%-14s unlock=%2d usable=%2d/%2d groups=%s blocked=%d' % (r['component'], r['unlock'], len(r['usable']), len(r['members']), [len(g) for g in r['groups']], len(r['blocked'])))
        write_json(UNITS / 'proposals.json', dict(generated=timestamp(), proposals=rows))
    elif args.action == 'build':
        overrides = {}
        for item in args.override:
            name, text = item.split('=', 1)
            overrides[name] = text
        source_overrides = dict(item.split('=', 1) for item in args.source)
        result = build_unit(args.component, args.members.split(',') if args.members else None, args.layout, overrides, args.reason, source_overrides, args.unit_source)
        print(json.dumps({k: v for k, v in result.items() if k not in ('sources',)}, indent=2))
    elif args.action == 'test':
        print(json.dumps(test_unit(args.unit), indent=2))
    else:
        print(json.dumps(unit_job(args.unit, args.reason), indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
