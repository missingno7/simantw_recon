"""Fresh root-cause classification of every MATCH_BLOCKED function.

Old blocker labels were recorded before object-level compiler profiles,
translation-unit assembly, selector-pool reconstruction, private DATA/BSS
layout and scaffolded units existed. This tool ignores them: every blocked
function's best preserved candidate is recompiled under the *current* object
profile and compared with the strict matcher; the fresh comparison decides
the category. Historical labels are kept only as `previous_blockers`.

Categories (first match wins):

- BODY_EXACT_LAYOUT_BLOCKED: opcode body exact, zero register / branch /
  stack differences; only offset bindings, private DATA/BSS/CONST placement
  or translation-unit context remain. Admissible through a scaffolded unit.
- PROFILE_CONTEXT_RETEST: the job's recorded flags differ from the profile
  now assigned to its object context (the fresh compile below already uses
  the current profile; the category records that the parked evidence was
  produced under another one).
- TU_SCAFFOLD_CANDIDATE: instruction layout and registers agree; the only
  differences are displacement literals inside private data or pool ranges,
  i.e. declaration order / pool topology of the object.
- MIRRORED_SOURCE_PAIR: a B/R (or Blk/Red) counterpart is admitted or exact,
  so the member is mechanically derivable from it.
- ABI_TYPE_INFERENCE: the fresh diagnostic shows only immediate / call
  binding differences on calls, or the parked cause was an ABI cause and the
  fresh result confirms a call-shape difference.
- TRUE_SOURCE_SHAPE_MISMATCH: instruction shape, register allocation,
  branch or frame differences under the correct profile (sub-cause recorded).
- UNKNOWN: no compilable candidate.

Output: evidence/recovery/blocked-reclassification.json and
docs/blocked-reclassification.md. Nothing here grants credit or changes a
job's admission state.
"""
import argparse
import json
import re
from collections import Counter, defaultdict
from datetime import datetime, timezone
from common import ROOT, FormatError, read_json, write_json

OUT = ROOT / 'evidence/recovery/blocked-reclassification.json'
DOC = ROOT / 'docs/blocked-reclassification.md'
WORK = 'build/reclassify'

ABI_CAUSES = {'FAR_POINTER_TYPE', 'CALLING_CONVENTION', 'FP_MODE', 'STRING_INTRINSIC_IDIOM'}
PAIR_RULES = [(re.compile(r'B$'), 'R'), (re.compile(r'R$'), 'B'), (re.compile(r'Blk'), 'Red'), (re.compile(r'Red'), 'Blk'), (re.compile(r'Black'), 'Red'), (re.compile(r'Red'), 'Black')]


def mirror_partner(symbol, universe):
    """The structurally mirrored counterpart of a colony function, if it exists."""
    for pattern, repl in PAIR_RULES:
        if pattern.search(symbol):
            other = pattern.sub(repl, symbol, count=1)
            if other != symbol and other in universe:
                return other
    return None


def best_source(symbol, preserved, ledger):
    entry = preserved.get(symbol)
    if entry:
        return entry['source'], entry['basis']
    draft = ledger.get(symbol)
    if draft and draft.get('source') and (ROOT / draft['source']).exists():
        return draft['source'], 'LEDGER_DRAFT'
    return None, None


def fresh_comparison(symbol, source, flags):
    """Recompile the candidate under the current profile; cached when unchanged."""
    from codegen_grinder import run
    report = run(dict(symbol=symbol, source=source, compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[symbol]),
                 '%s/%s' % (WORK, symbol.lstrip('_')), cache=True)
    row = report['results'][0]
    return row['comparison'], row['receipt']


def private_ranges(component, functions):
    """Original DGROUP private data words and pool words of a component."""
    words = set(int(x, 16) for x in component.get('pool_words', []))
    data = set(component.get('data_words', []))
    return words, data


def classify_fresh(comparison, symbol, job, profile_flags, partner_state, component, functions):
    """Category, sub-cause and the evidence used, from a fresh comparison."""
    from topology_diagnostics import classify
    d = comparison.get('diagnostic') or {}
    result = comparison.get('result')
    evidence = dict(result=result, opcode_matches=d.get('opcode_matches'), opcode_total=d.get('opcode_total'),
                    candidate_bytes=d.get('candidate_bytes'), target_bytes=d.get('target_bytes'),
                    register_only=d.get('register_only_differences'), branch=d.get('branch_target_differences'),
                    stack=d.get('stack_local_differences'), layout_match=d.get('instruction_layout_match'),
                    issues=(comparison.get('issues') or [])[:8], categories=d.get('categories', []))
    if result in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
        return 'BODY_EXACT_LAYOUT_BLOCKED', 'strict match in isolation; promotion pending', evidence
    if result == 'COMPILE_FAILED' or not d or d.get('opcode_total') is None:
        return 'UNKNOWN', 'no comparable candidate (compile failed or unmeasured)', evidence
    exact_opcodes = d.get('opcode_matches') == d.get('opcode_total') and d.get('candidate_bytes') == d.get('target_bytes')
    clean = all(d.get(k, 1) == 0 for k in ('register_only_differences', 'branch_target_differences', 'stack_local_differences'))
    changed = [r for r in d.get('aligned_asm', []) if r['differences']]
    shape = any('instruction_shape' in r['differences'] for r in changed)
    failed = [f for c in comparison.get('contributions', []) for f in c.get('fixups', []) if not f['equal']]
    wrong_literal = [f for f in failed if f.get('target') is not None and f.get('reason') in ('resolved offset and frame', 'same-segment relative offset')]
    pool_words, data_words = private_ranges(component or {}, functions)
    def private_target(f):
        t = f.get('target') or {}
        return t.get('kind') == 'internal' and t.get('segment') == 10 and (t.get('offset') in data_words or t.get('offset') in pool_words or any(abs(t.get('offset', -1) - w) < 64 for w in data_words))
    if exact_opcodes and clean and not shape:
        if classify(comparison) is not None:
            return 'BODY_EXACT_LAYOUT_BLOCKED', 'exact body; only unresolved offset bindings (pool / private data / TU context)', evidence
        if wrong_literal and all(private_target(f) for f in wrong_literal):
            return 'TU_SCAFFOLD_CANDIDATE', 'exact body; resolved private DGROUP displacements differ (declaration order / pool topology)', evidence
        if wrong_literal:
            names = sorted({(f.get('omf') or {}).get('target', {}).get('name', '?') for f in wrong_literal})
            return 'TRUE_SOURCE_SHAPE_MISMATCH', 'exact body but wrong displacement/index for %s (binding semantics)' % ', '.join(names[:4]), evidence
        return 'BODY_EXACT_LAYOUT_BLOCKED', 'exact body; private placement / contribution issues only', evidence
    if partner_state in ('MATCHED', 'EXACT'):
        return 'MIRRORED_SOURCE_PAIR', 'counterpart %s is %s; derive mechanically' % (partner_state.lower(), partner_state), evidence
    old = set(job.get('blockers') or []) if job else set()
    call_only = changed and all(set(r['differences']) <= {'immediate_or_binding', 'memory_operand'} for r in changed) and not shape
    if old & ABI_CAUSES or (call_only and not clean):
        return 'ABI_TYPE_INFERENCE', 'call/pointer-shape differences (%s)' % ', '.join(sorted(old & ABI_CAUSES) or ['fresh']), evidence
    subs = []
    if shape:
        subs.append('instruction shape')
    if d.get('register_only_differences'):
        subs.append('register allocation')
    if d.get('branch_target_differences'):
        subs.append('branch layout')
    if d.get('stack_local_differences'):
        subs.append('frame layout')
    if not subs:
        subs.append('operand/immediate differences')
    return 'TRUE_SOURCE_SHAPE_MISMATCH', '%s under the current profile (%d/%d opcodes, %s/%s bytes)' % (', '.join(subs), d.get('opcode_matches', 0), d.get('opcode_total', 0), d.get('candidate_bytes'), d.get('target_bytes')), evidence


def main(only=None, limit=None):
    import compiler_profiles as cp
    import tu_assembly as tu
    import recovery_workflow as wf
    queue = read_json(ROOT / 'docs/production-queue.json')
    functions = read_json(ROOT / 'evidence/topology/build-topology.json')['functions']
    components = tu.topology_units()
    preserved = tu.preserved_sources()
    ledger_all = read_json(ROOT / 'evidence/recovery/blockers.json')
    ledger = {**ledger_all.get('drafts', {}), **ledger_all.get('workflow_cases', {})}
    jobs = {j['symbol']: j for j in wf.jobs()}
    recipes = wf.recipes()
    states = {f['symbol']: f['state'] for f in queue['functions']}
    exact = {s for s, v in preserved.items() if v['basis'] in ('BODY_MATCHED_BINDING_BLOCKED', 'EXACT_BODY_CANDIDATE')}
    blocked = [f for f in queue['functions'] if f['state'] == 'MATCH_BLOCKED' and (not only or f['symbol'] in only)]
    if limit:
        blocked = blocked[:limit]
    rows = []
    for f in blocked:
        symbol = f['symbol']
        job = jobs.get(symbol)
        comp = cp.component_of(symbol) or {}
        profile = cp.resolve(symbol)
        flags = cp.profile_flags(profile['name'], comp.get('segment') or f['segment'])
        job_flags = job.get('flags') if job else None
        stale_profile = bool(job_flags) and job_flags != flags
        partner = mirror_partner(symbol, set(states) | set(recipes))
        partner_state = None
        if partner:
            partner_state = 'MATCHED' if partner in recipes else 'EXACT' if partner in exact else states.get(partner)
        source, basis = best_source(symbol, preserved, ledger)
        category, cause, evidence, receipt = 'UNKNOWN', 'no preserved candidate', {}, None
        if source:
            try:
                comparison, receipt = fresh_comparison(symbol, source, flags)
                category, cause, evidence = classify_fresh(comparison, symbol, job, flags, partner_state, components.get(comp.get('id')), functions)
            except FormatError as exc:
                category, cause = 'UNKNOWN', 'fresh compile refused: %s' % str(exc)[:120]
            except Exception as exc:  # a broken preserved source must not stop the census
                category, cause = 'UNKNOWN', 'fresh compile failed: %s' % repr(exc)[:120]
        elif partner_state in ('MATCHED', 'EXACT'):
            category, cause = 'MIRRORED_SOURCE_PAIR', 'no candidate, but counterpart %s is %s' % (partner, partner_state)
        if stale_profile and category not in ('BODY_EXACT_LAYOUT_BLOCKED',):
            secondary = category
            category = 'PROFILE_CONTEXT_RETEST'
            cause = 'parked under %s, context profile is now %s (%s); fresh result: %s' % (' '.join(job_flags), profile['name'], ' '.join(flags), secondary + ': ' + cause)
        rows.append(dict(symbol=symbol, component=comp.get('id'), segment=f['segment'], size=f['size'], profile=profile['name'], profile_basis=profile['basis'],
                         job=job['id'] if job else None, attempts=len(job.get('attempts', [])) if job else 0, previous_blockers=f['blockers'],
                         stale_profile=stale_profile, source=source, source_basis=basis, mirror_partner=partner, partner_state=partner_state,
                         category=category, cause=cause, evidence=evidence))
        print('%-28s %-28s %s' % (symbol, category, cause[:90]), flush=True)
    by_category = Counter(r['category'] for r in rows)
    corrected = sum(1 for r in rows if r['previous_blockers'] and r['category'] not in ('UNKNOWN',) and not label_agrees(r))
    report = dict(schema_version=1, generated=datetime.now(timezone.utc).isoformat(), scope=__doc__.strip().split('\n')[0],
                  counts=dict(by_category), corrected_labels=corrected, rows=rows)
    if not only and not limit:
        write_json(OUT, report)
        DOC.write_text(render(report, components, recipes, states, exact), encoding='utf-8')
    return report


def label_agrees(row):
    """Does the historical label still describe the fresh category?"""
    old = set(row['previous_blockers'])
    cat = row['category']
    if cat == 'BODY_EXACT_LAYOUT_BLOCKED':
        return bool(old & {'TRANSLATION_UNIT_CONTEXT', 'PRIVATE_CONST_LAYOUT', 'DATA_LAYOUT', 'TRANSLATION_UNIT_CONTEXT_REQUIRED'})
    if cat == 'TU_SCAFFOLD_CANDIDATE':
        return bool(old & {'DATA_LAYOUT', 'PRIVATE_CONST_LAYOUT', 'TRANSLATION_UNIT_CONTEXT'})
    if cat == 'ABI_TYPE_INFERENCE':
        return bool(old & ABI_CAUSES)
    if cat == 'TRUE_SOURCE_SHAPE_MISMATCH':
        return bool(old & {'REGISTER_ALLOCATION', 'EXPRESSION_SHAPE', 'LOCAL_FRAME_LAYOUT', 'SEMANTICS_UNKNOWN', 'OPTIMIZER_VARIANT_REQUIRED'})
    return False


def render(report, components, recipes, states, exact):
    rows = report['rows']
    lines = ['# Fresh classification of the MATCH_BLOCKED population', '', 'Generated %s from the current HEAD: every blocked function\'s best preserved candidate recompiled under the current object profile and compared strictly. Historical labels are shown only as `previous`.' % report['generated'], '',
             '## Counts by fresh root cause', '']
    for k, v in sorted(report['counts'].items(), key=lambda kv: -kv[1]):
        lines.append('- %s: %d' % (k, v))
    lines += ['', 'Historical labels that no longer describe the fresh result: %d' % report['corrected_labels'], '', '## By historical object / TU context', '']
    by_comp = defaultdict(list)
    for r in rows:
        by_comp[r['component'] or '?'].append(r)
    def fanout(cid):
        return sum(1 for r in by_comp[cid] if r['category'] in ('BODY_EXACT_LAYOUT_BLOCKED', 'TU_SCAFFOLD_CANDIDATE', 'MIRRORED_SOURCE_PAIR', 'PROFILE_CONTEXT_RETEST'))
    functions = read_json(ROOT / 'evidence/topology/build-topology.json')['functions']
    for cid in sorted(by_comp, key=lambda c: (-fanout(c), -len(by_comp[c]), c)):
        comp = components.get(cid, {})
        publics = comp.get('publics', [])
        matched = sum(1 for p in publics if p in recipes)
        ready = sum(1 for p in publics if states.get(p) == 'MATCH_READY')
        exact_here = sum(1 for p in publics if p in exact and p not in recipes)
        mirrored = sum(1 for r in by_comp[cid] if r['mirror_partner'])
        cats = Counter(r['category'] for r in by_comp[cid])
        # Selector-pool completeness: words introduced by admitted or exact members.
        pool = [int(x, 16) for x in comp.get('pool_words', [])]
        introducer = {}
        for f in publics:
            for w in functions.get(f, {}).get('introduced', {}).get('pool', []):
                introducer.setdefault(w, f)
        known = sum(1 for w in pool if introducer.get(w) in recipes or introducer.get(w) in exact)
        # Next missing introducer: first unclaimed public (code order) that introduces pool words.
        missing = next((f for f in publics if f not in recipes and f not in exact and functions.get(f, {}).get('introduced', {}).get('pool')), None)
        data_state = 'private data words %d (%s)' % (len(comp.get('data_words', [])), 'reproduced' if not comp.get('data_words') or any(p in recipes for p in publics if functions.get(p, {}).get('introduced', {}).get('data')) else 'open')
        lines.append('### %s — %d members, %d matched, %d blocked, %d ready; profile %s' % (cid, len(publics), matched, len(by_comp[cid]), ready, (by_comp[cid][0]['profile'] if by_comp[cid] else '?')))
        lines.append('')
        lines.append('- exact bodies awaiting admission: %d; mirrored blocked members: %d' % (exact_here, mirrored))
        lines.append('- selector pool: %d/%d words introduced by admitted or exact members; %s' % (known, len(pool), data_state))
        lines.append('- likely next missing introducer: %s' % (missing or 'none (all introducers known)'))
        lines.append('- estimated unlock fan-out (exact + scaffold + mirrored + profile-retest rows): %d' % fanout(cid))
        lines.append('- fresh causes: ' + ', '.join('%s %d' % kv for kv in cats.most_common()))
        lines.append('')
        lines.append('| symbol | size | fresh category | cause | previous | partner |')
        lines.append('|---|---|---|---|---|---|')
        for r in sorted(by_comp[cid], key=lambda r: (r['category'], r['symbol'])):
            lines.append('| %s | %s | %s | %s | %s | %s |' % (r['symbol'], r['size'], r['category'], r['cause'].replace('|', '/')[:110], ','.join(r['previous_blockers'][:2]), (r['mirror_partner'] or '') + (' (%s)' % r['partner_state'] if r['partner_state'] else '')))
        lines.append('')
    return '\n'.join(lines) + '\n'


def write_back(report=None):
    """Record the fresh root cause on each blocked job (status and the
    historical `blockers` list are left untouched; `root_cause` is the
    current classification, `previous_blockers` the label it replaces)."""
    import recovery_workflow as wf
    report = report or read_json(OUT)
    jobs = {j['symbol']: j for j in wf.jobs()}
    changed = 0
    for r in report['rows']:
        job = jobs.get(r['symbol'])
        if not job:
            continue
        path = wf.STATE / 'jobs' / job['id'] / 'job.json'
        current = read_json(path)
        cause = dict(category=r['category'], cause=r['cause'], profile=r['profile'], stale_profile=r['stale_profile'], mirror_partner=r['mirror_partner'], partner_state=r['partner_state'], classified=report['generated'], evidence='evidence/recovery/blocked-reclassification.json')
        if current.get('root_cause') == cause:
            continue
        current['root_cause'] = cause
        current.setdefault('previous_blockers', current.get('blockers', []))
        wf.atomic_json(path, current)
        changed += 1
    return changed


if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('symbols', nargs='*')
    p.add_argument('--limit', type=int)
    p.add_argument('--write-back', action='store_true', help='record root_cause on each blocked job from the saved report')
    args = p.parse_args()
    if args.write_back:
        print('jobs updated:', write_back())
    else:
        main(args.symbols or None, args.limit)
