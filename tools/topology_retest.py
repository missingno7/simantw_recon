"""Expert-only reissue of a parked job for a new, evidenced topology experiment.

Preserves prior job context and all attempts. Budgets and strict promotion are
unchanged; this is deliberately separate from the ordinary grinder interface.
"""
import argparse, json, re
from common import ROOT, FormatError, read_json, write_json, identity
import recovery_workflow as wf


NEAR_EXACT_ATTEMPTS = 4


def near_exact_reopen(job_id, reason):
    """Reopen an escalated job whose fresh classification is a near-exact
    source-shape mismatch (>= 95% opcode agreement under the current profile)
    with one recorded extension of NEAR_EXACT_ATTEMPTS attempts, so the
    near-exact lane can iterate on frame/idiom/binding variants through the
    ordinary grinder path. Granted once per job; the parked context is kept."""
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if job['status'] != 'ESCALATED':
        raise FormatError('only an escalated job can be reopened for the near-exact lane')
    root = job.get('root_cause') or {}
    lane = read_json(ROOT / 'evidence/recovery/near-exact-lane.json') if (ROOT / 'evidence/recovery/near-exact-lane.json').exists() else {}
    if job['symbol'] not in {r['symbol'] for r in lane.get('rows', [])}:
        raise FormatError('symbol is not in the recorded near-exact lane (evidence/recovery/near-exact-lane.json)')
    extensions = list(job.get('budget_extensions', []))
    if any(e.get('kind') == 'NEAR_EXACT_LANE' for e in extensions):
        raise FormatError('near-exact lane extension already granted for this job')
    extensions.append(dict(kind='NEAR_EXACT_LANE', attempts=NEAR_EXACT_ATTEMPTS, candidates=NEAR_EXACT_ATTEMPTS, reviewed=wf.timestamp(), reason=reason, fresh_root_cause=root))
    new_job = dict(job, status='NEEDS_REVISION', protected=wf.protected(), fixture_identity=read_json(ROOT / 'layout/fixtures.json'), budget_extensions=extensions)
    for key in ('blockers', 'reason', 'next_experiment'):
        if key in new_job:
            new_job['parked_' + key] = new_job.pop(key)
    write_json(directory / 'near-exact-reopen.json', dict(previous_job=job, reason=reason, reviewed=wf.timestamp(), recovery_credit=0))
    wf.atomic_json(directory / 'job.json', new_job)
    with wf.global_lock():
        wf.refresh()
    return dict(job=job_id, status='NEEDS_REVISION', attempts_granted=NEAR_EXACT_ATTEMPTS)


def reissue(job_id, spec_path, reason, hypothesis_cause=None):
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if job['id'] != job_id or job['status'] != 'ESCALATED':
        raise FormatError('only an existing escalated job can be reissued')
    if job['fixture_identity'] != read_json(ROOT / 'layout/fixtures.json'):
        raise FormatError('fixture identity changed; reissue cannot replace the oracle')
    if not reason.strip():
        raise FormatError('expert review reason required')
    spec = read_json(ROOT / spec_path)
    wf.check_submission(spec, job)
    if wf.experiment_digest(spec) in {a['submission_digest'] for a in job['attempts']}:
        raise FormatError('this source experiment was already attempted')
    planned=sum(1 for _ in wf.variants(spec))
    if sum(a.get('candidates',1) for a in job['attempts']) + planned > wf.MAX_TOTAL_CANDIDATES:
        raise FormatError('new experiment exceeds remaining target budget')
    extensions=list(job.get('budget_extensions',[]))
    if len(job['attempts']) >= wf.attempt_limit(job):
        if hypothesis_cause not in ('ABI','DATA_IDENTITY','TYPE_REPRESENTATION','SOURCE_LAYOUT','LOCAL_LIFETIME','COMPILER_CONTEXT','DIAGNOSTIC') or planned!=1:
            raise FormatError('exhausted job requires one bounded, evidenced hypothesis extension')
        if any(e.get('kind')=='HYPOTHESIS_REISSUE' and e.get('cause')==hypothesis_cause for e in extensions):
            raise FormatError('this hypothesis cause already received an extension')
        extensions.append(dict(kind='HYPOTHESIS_REISSUE',cause=hypothesis_cause,attempts=1,candidates=1,
                               reason=reason,reviewed=wf.timestamp(),spec=spec_path))
    index = len(list(directory.glob('expert-reissue-*.json'))) + 1
    write_json(directory / ('expert-reissue-%02d.json' % index),
               dict(previous_job=job, reason=reason, hypothesis_cause=hypothesis_cause, spec=spec_path,
                    spec_identity=identity(ROOT / spec_path), reviewed=wf.timestamp()))
    job = dict(job, status='OPEN', budget_extensions=extensions, protected=wf.protected(),
               fixture_identity=read_json(ROOT / 'layout/fixtures.json'))
    wf.atomic_json(directory / 'submission.json', spec)
    wf.atomic_json(directory / 'job.json', job)
    return wf.run_attempt(job_id)


def profile_reissue(job_id, reason, spec_path=None):
    """Expert re-profile of a parked job under its context's assigned compiler profile.

    The profile must already be assigned in layout/compiler-profiles.json with
    evidence; this only replays the preserved candidate (or a reviewed spec)
    under the unit-level profile. Previous attempts, flags and budget are
    archived; an exhausted budget receives exactly one recorded extension for
    the profile change. Admission still requires fresh promotion.
    """
    import compiler_profiles
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if job['id'] != job_id or job['status'] != 'ESCALATED':
        raise FormatError('only an existing escalated job can be re-profiled')
    if job['fixture_identity'] != read_json(ROOT / 'layout/fixtures.json'):
        raise FormatError('fixture identity changed; reissue cannot replace the oracle')
    if not reason.strip():
        raise FormatError('expert review reason required')
    profile = compiler_profiles.resolve(job['symbol'])
    if profile['basis'] != 'ASSIGNED':
        raise FormatError('no evidence-backed profile assignment covers ' + job['symbol'])
    card = next(c for c in wf.cards() if c['symbol'] == job['symbol'])
    flags = compiler_profiles.profile_flags(profile['name'], card['segment_name'])
    if flags == job['flags']:
        raise FormatError('job already uses the assigned profile')
    if spec_path:
        spec = read_json(ROOT / spec_path)
    else:
        source, row = compiler_profiles.best_candidate(job)
        preserved = directory / 'profile-candidate.c'
        preserved.write_bytes(source.read_bytes())
        spec = dict(symbol=job['symbol'], source=wf.relative(preserved), compiler='msc700', flags=flags, max_candidates=1, axes=[],
                    semantic_summary=read_json(directory / 'submission.json').get('semantic_summary', 'Preserved candidate replayed under the unit profile'),
                    binding_evidence=['layout/compiler-profiles.json', profile['assignment']], publics=[job['symbol']])
    spec['flags'] = flags
    new_job = dict(job, status='OPEN', flags=flags, profile=profile, protected=wf.protected(), fixture_identity=read_json(ROOT / 'layout/fixtures.json'))
    for key in ('blockers', 'reason', 'next_experiment', 'evidence_state', 'topology_diagnostic'):
        if key in new_job:
            new_job['parked_' + key] = new_job.pop(key)
    wf.check_submission(spec, new_job)
    if wf.experiment_digest(spec) in {a['submission_digest'] for a in job['attempts']}:
        raise FormatError('this exact experiment was already attempted')
    extensions = list(job.get('budget_extensions', []))
    if len(job['attempts']) >= wf.attempt_limit(job) or sum(a.get('candidates', 1) for a in job['attempts']) + sum(1 for _ in wf.variants(spec)) > wf.MAX_TOTAL_CANDIDATES:
        if any(e.get('profile') == profile['name'] for e in extensions):
            raise FormatError('budget extension for this profile already used')
        extensions.append(dict(kind='PROFILE_REISSUE', profile=profile['name'], attempts=1, candidates=1, reviewed=wf.timestamp(), reason=reason))
        if sum(1 for _ in wf.variants(spec)) != 1:
            raise FormatError('a budget extension covers exactly one candidate')
    new_job['budget_extensions'] = extensions
    index = len(list(directory.glob('expert-profile-reissue-*.json'))) + 1
    write_json(directory / ('expert-profile-reissue-%02d.json' % index),
               dict(previous_job=job, previous_flags=job['flags'], new_flags=flags, profile=profile, reason=reason, spec=spec, reviewed=wf.timestamp(), recovery_credit=0))
    wf.atomic_json(directory / 'submission.json', spec)
    wf.atomic_json(directory / 'job.json', new_job)
    return wf.run_attempt(job_id)


def tool_reissue(job_id, reason):
    """Replay a parked job's preserved best candidate unchanged after a validated proof-tool change.

    The experiment digest excludes tool identity, so an identical replay is
    normally refused; this expert path allows exactly one replay per validated
    tool change, recording which protected tools changed. No source change,
    no budget change beyond the one recorded attempt, no recovery credit.
    """
    import compiler_profiles
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if job['id'] != job_id or job['status'] != 'ESCALATED':
        raise FormatError('only an existing escalated job can be replayed')
    if job['fixture_identity'] != read_json(ROOT / 'layout/fixtures.json'):
        raise FormatError('fixture identity changed; reissue cannot replace the oracle')
    if not reason.strip():
        raise FormatError('expert review reason required')
    current = wf.protected()
    changed = [p for p in current if job['protected'].get(p) != current[p]]
    if not changed:
        raise FormatError('no protected tool changed since the job was parked')
    if any(not (p.startswith('tools/') and p.endswith('.py')) and not p.startswith('layout/compiler-profiles') for p in changed):
        raise FormatError('only validated Python tool changes may justify a replay')
    validation = read_json(wf.STATE / 'validation.json')
    inputs = validation.get('inputs', {})
    if not validation.get('passed') or any(p not in inputs or identity(ROOT / p) != inputs[p] for p in changed if p.startswith('tools/')):
        raise FormatError('current successful handoff validation covering the changed tools required')
    source, row = compiler_profiles.best_candidate(job)
    preserved = directory / 'tool-replay-candidate.c'
    preserved.write_bytes(source.read_bytes())
    spec = dict(symbol=job['symbol'], source=wf.relative(preserved), compiler='msc700', flags=job['flags'], max_candidates=1, axes=[],
                semantic_summary=read_json(directory / 'submission.json').get('semantic_summary', 'Preserved candidate replayed after a validated tool change'),
                binding_evidence=['evidence/recovery/workflow/validation.json'], publics=[job['symbol']])
    new_job = dict(job, status='OPEN', protected=current, fixture_identity=read_json(ROOT / 'layout/fixtures.json'))
    for key in ('blockers', 'reason', 'next_experiment', 'evidence_state', 'topology_diagnostic'):
        if key in new_job:
            new_job['parked_' + key] = new_job.pop(key)
    wf.check_submission(spec, new_job)
    digest = wf.experiment_digest(spec)
    index = len(list(directory.glob('expert-tool-replay-*.json'))) + 1
    if any(r.get('changed_tools') == changed for r in (read_json(p) for p in directory.glob('expert-tool-replay-*.json'))):
        raise FormatError('this tool change was already replayed for the job')
    extensions = list(job.get('budget_extensions', []))
    extensions.append(dict(kind='TOOL_REPLAY', changed_tools=changed, attempts=1, candidates=1, reviewed=wf.timestamp(), reason=reason))
    new_job['budget_extensions'] = extensions
    # Allow the identical digest once: record it as replayed.
    new_job['attempts'] = [dict(a, submission_digest=a['submission_digest'] + ':superseded-by-tool-replay') if a['submission_digest'] == digest else a for a in job['attempts']]
    write_json(directory / ('expert-tool-replay-%02d.json' % index),
               dict(previous_job=job, changed_tools=changed, validation_identity=identity(wf.STATE / 'validation.json'), reason=reason, spec=spec, reviewed=wf.timestamp(), recovery_credit=0))
    wf.atomic_json(directory / 'submission.json', spec)
    wf.atomic_json(directory / 'job.json', new_job)
    return wf.run_attempt(job_id)


def refresh_unattempted(job_id, reason):
    """Expert context review only: no source change, attempt, or recovery credit."""
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if (job.get('id') != job_id or job.get('status') not in ('OPEN', 'NEEDS_REVISION')
            or job.get('pending_attempt')):
        raise FormatError('context-only refresh requires an OPEN or NEEDS_REVISION job without a pending attempt')
    if not reason.strip():
        raise FormatError('expert review reason required')
    if job['fixture_identity'] != read_json(wf.ROOT / 'layout/fixtures.json'):
        raise FormatError('fixture identity changed; cannot refresh context')
    current = wf.protected()
    if set(current) - set(job['protected']):
        raise FormatError('protected input set gained entries; separate expert review required')
    removed = sorted(set(job['protected']) - set(current))
    changed = [p for p in current if job['protected'][p] != current[p]] + removed
    if not changed:
        raise FormatError('job context is already current')
    if any(not (p.startswith('tools/') and p.endswith('.py')) and p not in removed for p in changed):
        raise FormatError('only validated Python tool changes may be refreshed')
    validation = read_json(wf.STATE / 'validation.json')
    expected = {p.relative_to(wf.ROOT).as_posix()
                for folder in ('tools', 'tests') for p in (wf.ROOT / folder).glob('*.py')}
    inputs = validation.get('inputs', {})
    if (not validation.get('passed') or not expected.issubset(inputs)
            or any(not (wf.ROOT / p).exists() or identity(wf.ROOT / p) != value
                   for p, value in inputs.items())):
        raise FormatError('current successful handoff validation required')
    # Independently verify the complete existing manifest before refreshing.
    wf.verify(publish=False)
    index = len(list(directory.glob('expert-context-review-*.json'))) + 1
    write_json(directory / ('expert-context-review-%02d.json' % index),
               dict(previous_job=job, reason=reason, changed_tools=changed,
                    validation_identity=identity(wf.STATE / 'validation.json'),
                    preserved_inputs={name:identity(directory / name)
                                      for name in ('candidate.c','submission.json')},
                    reviewed=wf.timestamp(), recovery_credit=0))
    wf.atomic_json(directory / 'job.json', dict(job, protected=current))
    return dict(job=job_id, status=job['status'], context_refreshed=True,
                attempts=len(job['attempts']), recovery_credit=0, changed_tools=changed)


def supersede_admitted(job_id, reason):
    """Close an old individual job only after its current TU recipe verifies."""
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if job.get('id') != job_id or job.get('lane') == 'TU_ASSEMBLY' or job.get('status') not in ('OPEN', 'NEEDS_REVISION', 'ESCALATED') or job.get('pending_attempt'):
        raise FormatError('only a settled individual job may be superseded')
    if not reason.strip():
        raise FormatError('supersession reason required')
    recipe = wf.recipes().get(job['symbol'])
    if not recipe or not recipe.get('unit') or not recipe.get('promotion_evidence'):
        raise FormatError('no admitted TU recipe supersedes this symbol')
    proof = wf.ROOT / recipe['promotion_evidence']
    if not proof.exists():
        raise FormatError('TU promotion proof is missing')
    wf.verify(publish=False)
    record = dict(previous_job=job, admitted_symbol=job['symbol'],
                  recipe=recipe, promotion_evidence=recipe['promotion_evidence'],
                  promotion_identity=identity(proof), reason=reason,
                  reviewed=wf.timestamp(), recovery_credit=0)
    write_json(directory / 'superseded-by-tu.json', record)
    wf.atomic_json(directory / 'job.json', dict(job, status='SUPERSEDED_BY_TU',
                   superseded_by=recipe['promotion_evidence']))
    return dict(job=job_id, status='SUPERSEDED_BY_TU',
                promotion_evidence=recipe['promotion_evidence'], attempts=len(job['attempts']))


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('job'); ap.add_argument('spec', nargs='?'); ap.add_argument('--reason', required=True)
    ap.add_argument('--refresh-unattempted', action='store_true')
    ap.add_argument('--profile-reissue', action='store_true', help='replay the preserved candidate under the assigned unit profile')
    ap.add_argument('--tool-replay', action='store_true', help='replay the preserved candidate unchanged after a validated proof-tool change')
    ap.add_argument('--near-exact', action='store_true', help='reopen a near-exact source-shape job with one recorded bounded extension')
    ap.add_argument('--supersede-admitted', action='store_true', help='close an old individual job after verifying its admitted TU recipe')
    ap.add_argument('--hypothesis-cause', choices=['ABI','DATA_IDENTITY','TYPE_REPRESENTATION','SOURCE_LAYOUT','LOCAL_LIFETIME','COMPILER_CONTEXT','DIAGNOSTIC'], help='one recorded single-candidate extension for an exhausted job')
    args = ap.parse_args()
    if args.refresh_unattempted and args.spec:
        ap.error('context-only refresh does not take a spec')
    if not args.refresh_unattempted and not args.profile_reissue and not args.tool_replay and not args.near_exact and not args.supersede_admitted and not args.spec:
        ap.error('reissue requires a spec')
    with wf.global_lock():
        wf.recover_transaction()
    with wf.job_lock(args.job):
        if args.refresh_unattempted:
            result = refresh_unattempted(args.job, args.reason)
        elif args.supersede_admitted:
            result = supersede_admitted(args.job, args.reason)
        elif args.near_exact:
            result = near_exact_reopen(args.job, args.reason)
        elif args.profile_reissue:
            result = profile_reissue(args.job, args.reason, args.spec)
        elif args.tool_replay:
            result = tool_reissue(args.job, args.reason)
        else:
            result = reissue(args.job, args.spec, args.reason, args.hypothesis_cause)
    print(json.dumps(result, indent=2))
