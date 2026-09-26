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


def probe(symbol, source=None):
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
    PROBES.mkdir(parents=True, exist_ok=True)
    stable = PROBES / (job_id + '.c')
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
    path = PROBES / (job_id + '.json')
    write_json(path, record)
    return record


def assign(context_id, profile, reason, evidence, symbols=None, strength=None):
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
    scope = set(cat['contexts'][context_id]['publics']) | set(symbols or [])
    # Evidence must discriminate for a member of the scope.
    strengths = []
    minimal = []
    fingerprints = set()
    for path in evidence:
        record = read_json(ROOT / path)
        if record.get('symbol') not in scope:
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
    if any(a['id'] == record['id'] for a in cat['assignments']):
        raise FormatError('assignment already exists: ' + record['id'])
    cat['assignments'].append(record)
    validate(cat)
    write_json(CATALOG, cat)
    return record


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest='action', required=True)
    sub.add_parser('validate')
    p = sub.add_parser('show'); p.add_argument('symbol')
    p = sub.add_parser('probe'); p.add_argument('symbol'); p.add_argument('--source')
    p = sub.add_parser('assign'); p.add_argument('context'); p.add_argument('profile'); p.add_argument('--reason', required=True); p.add_argument('--evidence', action='append', required=True); p.add_argument('--symbol', action='append')
    args = ap.parse_args()
    if args.action == 'validate':
        print(json.dumps(validate(), indent=2))
    elif args.action == 'show':
        print(json.dumps(resolve(args.symbol), indent=2))
    elif args.action == 'probe':
        record = probe(args.symbol, args.source)
        print(json.dumps(dict(job=record['job'], discriminating=record['discriminating'], results={k: (v['result'], v.get('opcode_matches'), v.get('opcode_total'), v.get('candidate_bytes')) for k, v in record['results'].items()}), indent=2))
    else:
        print(json.dumps(assign(args.context, args.profile, args.reason, args.evidence, args.symbol), indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
