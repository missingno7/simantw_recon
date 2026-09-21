"""Supervisor re-evaluation of every parked job against the reconstruction model.

Each escalated job is classified by the evidence now available (profile
probes, build topology, unit-assembly proposals, strict-matcher fixup
reasons, search diagnostics) into one root-cause class:

  A PROFILE_RESOLVABLE       a catalog profile reaches a strict result (A) or a
                             diagnostic gain without regression (A_CANDIDATE)
  B TU_LAYOUT_RESOLVABLE     body exact; only private placement / selector-pool
                             / private data obligations fail (with the unit
                             group that can assemble it, or the missing
                             introducers / static helpers that block it)
  C MATCHER_TOOLING          a fixup form the strict matcher cannot yet express
  D SOURCE_SEMANTIC_MISMATCH body differs in branches, calls, constants or CFG
  E ABI_TYPE_INFERENCE       pointer loads, cleanup, frame or calling convention
  F STRUCTURAL_CFG           extent or dispatch structure unresolved
  G STILL_UNKNOWN            nothing above explains the best divergence

Previous escalation records, attempts and budgets are untouched; the review
is a separate evidence file consumed by packets and the report.
"""
import argparse
import json
from collections import Counter
from common import ROOT, read_json, write_json, identity

REPORT = ROOT / 'evidence/recovery/parked-reclassification.json'
GOOD = {'CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'}


def best_row(job):
    best = None
    for attempt in job.get('attempts', []):
        path = ROOT / attempt['report']
        if not path.exists():
            continue
        report = read_json(path)
        for row in report['results']:
            c = row.get('comparison') or {}
            d = c.get('diagnostic') or {}
            key = (c.get('result') in GOOD, d.get('opcode_matches') or -1, -abs((d.get('candidate_bytes') or 0) - (d.get('target_bytes') or 0)), c.get('fixups_equal') or 0)
            if best is None or key > best[0]:
                best = (key, row, attempt['report'])
    return (best[1], best[2]) if best else (None, None)


def body_exact(d):
    return bool(d) and d.get('instruction_layout_match') is True and d.get('cfg_shape_match') is True and d.get('opcode_matches') == d.get('opcode_total') \
        and d.get('register_only_differences', 1) == 0 and d.get('branch_target_differences', 1) == 0 and d.get('stack_local_differences', 1) == 0 and d.get('target_bytes') == d.get('candidate_bytes')


def classify(job, row, probe, topology, proposals, unnamed, unit_tests=()):
    c = (row or {}).get('comparison') or {}
    d = c.get('diagnostic') or {}
    issues = c.get('issues', [])
    failed = [f for con in c.get('contributions', []) for f in con.get('fixups', []) if not f['equal']]
    reasons = Counter(f['reason'] for f in failed)
    blockers = job.get('blockers', [])
    evidence = dict(blockers=blockers, best_result=c.get('result'), opcode_matches=d.get('opcode_matches'), opcode_total=d.get('opcode_total'),
                    candidate_bytes=d.get('candidate_bytes'), target_bytes=d.get('target_bytes'), register_only_differences=d.get('register_only_differences'),
                    branch_target_differences=d.get('branch_target_differences'), failed_fixup_reasons=dict(reasons), issues=issues[:8])
    # A: profile evidence.
    if probe:
        strict = [p for p, s in probe['discriminating'].items() if s == 'STRICT']
        diag = [p for p, s in probe['discriminating'].items() if s == 'DIAGNOSTIC']
        evidence['probe'] = dict(strict=strict, diagnostic=diag, results={k: v.get('result') for k, v in probe['results'].items()})
        if strict:
            minimal = [p for p in strict if probe.get('minimal_over_parent', {}).get(p) != 'NONE'] or strict
            return 'A_PROFILE_RESOLVABLE', dict(evidence, profile=minimal[0], note='strict result under a catalog profile; assign the context and reissue')
    # F: structural.
    if 'EXTENT_UNKNOWN' in blockers or d.get('extent_known') is False or 'SHARED_TAIL' in blockers:
        return 'F_STRUCTURAL_CFG', evidence
    # C: matcher tooling - unsupported fixup forms with resolvable targets.
    unsupported = [f for f in failed if f['reason'] == 'unsupported or unresolved target/frame' and f['omf']['target'].get('kind') == 'external' and f['omf']['location_type'] not in (1, 2, 3)]
    if unsupported and body_exact(d):
        evidence['unsupported_forms'] = sorted({'loc%d/frame%s' % (f['omf']['location_type'], f['omf']['frame_method']) for f in unsupported})
        return 'C_MATCHER_TOOLING', evidence
    # B: unit layout - body exact, only private placement obligations fail.
    private_issue = any(k in ' '.join(issues) for k in ('private placement', 'unplaced contribution', 'CONST', '_DATA', '_BSS', 'uncovered NE relocations'))
    private_fixups = all(f['omf']['target'].get('kind') == 'segment' or f['reason'].startswith('unsupported') for f in failed) if failed else True
    if body_exact(d) and (private_issue or set(blockers) & {'DATA_LAYOUT', 'PRIVATE_CONST_LAYOUT', 'TRANSLATION_UNIT_CONTEXT', 'TRANSLATION_UNIT_CONTEXT_REQUIRED'}):
        comp = topology.get(job['symbol'])
        detail = dict(evidence, component=comp['id'] if comp else None, component_size=len(comp['publics']) if comp else None)
        prop = proposals.get(comp['id']) if comp else None
        if prop:
            group = next((g for g in prop['groups'] if job['symbol'] in g), None)
            if group and len(group) > 1:
                detail.update(subclass='B1_GROUP_ASSEMBLABLE', group=group)
                tested = [u for u in unit_tests if job['symbol'] in u['members']]
                if tested:
                    last = tested[-1]
                    detail.update(unit=last['unit'], unit_result=last['result'], unit_issues=last['issues'][:4])
                    if last['result'] not in GOOD:
                        detail['subclass'] = 'B1_GROUP_TESTED_NOT_EXACT'
            elif job['symbol'] in prop['blocked']:
                detail.update(subclass='B2_MISSING_INTRODUCERS', **prop['blocked'][job['symbol']])
            else:
                detail.update(subclass='B4_PRIVATE_DATA_ORDER', note='pool block predicted fine alone; private DATA/BSS or string placement needs the unit neighbours')
            statics = [u for u in unnamed if comp and u['group'] == comp['segment'] and u['after'] in comp['publics']]
            if statics:
                detail['static_helpers_in_unit'] = statics
                if detail.get('subclass') != 'B1_GROUP_ASSEMBLABLE':
                    detail['subclass'] = 'B3_STATIC_HELPER_REQUIRED'
        return 'B_TU_LAYOUT_RESOLVABLE', detail
    # E: ABI / type inference - explicit ABI blockers, or a near-exact body
    # whose only feature differences are pointer loads, stack cleanup or frame.
    features = c.get('features') or {}
    target_features = c.get('target_features') or {}
    ratio = (d.get('opcode_matches') or 0) / d['opcode_total'] if d.get('opcode_total') else 0
    abi_features = features and any(features.get(k) != target_features.get(k) for k in ('cleanup', 'pointer_loads', 'frame'))
    if set(blockers) & {'FAR_POINTER_TYPE', 'CALLING_CONVENTION', 'CALLING_CONVENTION_UNRESOLVED'} or (ratio >= 0.85 and abi_features and not d.get('branch_target_differences')):
        return 'E_ABI_TYPE_INFERENCE', dict(evidence, cleanup=[features.get('cleanup'), target_features.get('cleanup')], pointer_loads=[features.get('pointer_loads'), target_features.get('pointer_loads')], frame=[features.get('frame'), target_features.get('frame')])
    if probe and any(s == 'DIAGNOSTIC' for s in probe['discriminating'].values()):
        return 'A_PROFILE_CANDIDATE', dict(evidence, note='diagnostic gain under a profile but no strict result; the body still needs a source change under the unit profile')
    # D: semantic mismatch - control flow, calls or a body far from the target.
    if d and (d.get('branch_target_differences') or d.get('cfg_shape_match') is False or d.get('instruction_layout_match') is False or ratio < 0.85):
        return 'D_SOURCE_SEMANTIC_MISMATCH', evidence
    return 'G_STILL_UNKNOWN', evidence


def review():
    topology = {}
    unnamed = []
    if (ROOT / 'evidence/topology/build-topology.json').exists():
        report = read_json(ROOT / 'evidence/topology/build-topology.json')
        for unit in report['units']:
            for comp in unit['components']:
                for p in comp['publics']:
                    topology[p] = dict(id=comp['id'], publics=comp['publics'], segment=unit['segment'])
        cards = report['functions']
        by_group = {}
        for f in cards.values():
            by_group.setdefault(f['group'], []).append(f)
        for group, fs in by_group.items():
            fs.sort(key=lambda f: f['offset'])
            for a, b in zip(fs, fs[1:]):
                end = a['offset'] + (a['size'] or 0)
                if a['size'] and b['offset'] - end > 2:
                    unnamed.append(dict(group=group, after=a['symbol'], before=b['symbol'], bytes=b['offset'] - end))
    proposals = {}
    path = ROOT / 'evidence/recovery/units/proposals.json'
    if path.exists():
        proposals = {p['component']: p for p in read_json(path)['proposals']}
    probes = {}
    for p in (ROOT / 'evidence/experiments/optimizer-profile/probes').glob('*.json'):
        probes[p.stem] = read_json(p)
    unit_tests = []
    for p in sorted((ROOT / 'evidence/recovery/units').glob('*/unit.json')):
        spec = read_json(p)
        if spec.get('last_test'):
            unit_tests.append(dict(unit=spec['unit'], members=spec['members'], result=spec['last_test']['result'], issues=spec['last_test'].get('issues', [])))
    import compiler_profiles
    rows = {}
    for path in sorted((ROOT / 'evidence/recovery/workflow/jobs').glob('*/job.json')):
        job = read_json(path)
        if job['status'] != 'ESCALATED' or job.get('lane') == 'TU_ASSEMBLY':
            continue
        row, report = best_row(job)
        cls, detail = classify(job, row, probes.get(job['id']), topology, proposals, unnamed, unit_tests)
        try:
            profile = compiler_profiles.resolve(job['symbol'])
            detail['unit_profile'] = dict(name=profile['name'], basis=profile['basis'], assignment=profile.get('assignment'))
            if profile['basis'] == 'ASSIGNED' and cls not in ('A_PROFILE_RESOLVABLE',):
                detail['note_profile'] = 'unit context now carries profile %s; a fresh attempt inherits it' % profile['name']
        except Exception as exc:
            detail['unit_profile'] = dict(error=str(exc))
        rows[job['symbol']] = dict(job=job['id'], root_cause=cls, previous_blockers=job.get('blockers'), attempts=len(job.get('attempts', [])),
                                   candidates=sum(a.get('candidates', 1) for a in job.get('attempts', [])), best_report=report, detail=detail)
    summary = Counter(r['root_cause'] for r in rows.values())
    sub = Counter(r['detail'].get('subclass') for r in rows.values() if r['root_cause'].startswith('B'))
    out = dict(schema_version=1, scope='Supervisor re-evaluation of parked jobs; classification only, no budget or escalation change, no recovery credit',
               inputs={p: identity(ROOT / p) for p in ['evidence/topology/build-topology.json', 'evidence/recovery/units/proposals.json'] if (ROOT / p).exists()},
               summary=dict(summary), unit_subclasses=dict(sub), unnamed_code_regions=unnamed, functions=rows)
    write_json(REPORT, out)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.parse_args()
    out = review()
    print(json.dumps(dict(summary=out['summary'], unit_subclasses=out['unit_subclasses']), indent=2))


if __name__ == '__main__':
    main()
