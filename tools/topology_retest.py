"""Expert-only reissue of a parked job for a new, evidenced topology experiment.

Preserves prior job context and all attempts. Budgets and strict promotion are
unchanged; this is deliberately separate from the ordinary grinder interface.
"""
import argparse, re
from common import ROOT, FormatError, read_json, write_json, identity
import recovery_workflow as wf


def reissue(job_id, spec_path, reason):
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
    if len(job['attempts']) >= wf.MAX_ATTEMPTS or sum(a.get('candidates', 1) for a in job['attempts']) >= wf.MAX_TOTAL_CANDIDATES:
        raise FormatError('existing budget exhausted; use a separately recorded expert research spec')
    planned=sum(1 for _ in wf.variants(spec))
    if sum(a.get('candidates',1) for a in job['attempts']) + planned > wf.MAX_TOTAL_CANDIDATES:
        raise FormatError('new experiment exceeds remaining target budget')
    index = len(list(directory.glob('expert-reissue-*.json'))) + 1
    write_json(directory / ('expert-reissue-%02d.json' % index),
               dict(previous_job=job, reason=reason, spec=spec_path,
                    spec_identity=identity(ROOT / spec_path), reviewed=wf.timestamp()))
    job = dict(job, status='OPEN', protected=wf.protected(),
               fixture_identity=read_json(ROOT / 'layout/fixtures.json'))
    wf.atomic_json(directory / 'submission.json', spec)
    wf.atomic_json(directory / 'job.json', job)
    return wf.run_attempt(job_id)


def refresh_unattempted(job_id, reason):
    """Expert context review only: no source change, attempt, or recovery credit."""
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}', job_id):
        raise FormatError('invalid job ID')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if (job.get('id') != job_id or job.get('status') != 'OPEN'
            or job.get('attempts') != [] or job.get('pending_attempt')):
        raise FormatError('context-only refresh requires an OPEN unattempted job')
    if not reason.strip():
        raise FormatError('expert review reason required')
    if job['fixture_identity'] != read_json(wf.ROOT / 'layout/fixtures.json'):
        raise FormatError('fixture identity changed; cannot refresh context')
    current = wf.protected()
    if set(job['protected']) != set(current):
        raise FormatError('protected input set changed; separate expert review required')
    changed = [p for p in current if job['protected'][p] != current[p]]
    if not changed:
        raise FormatError('job context is already current')
    if any(not p.startswith('tools/') or not p.endswith('.py') for p in changed):
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
    return dict(job=job_id, status='OPEN', context_refreshed=True,
                attempts=0, recovery_credit=0, changed_tools=changed)


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('job'); ap.add_argument('spec', nargs='?'); ap.add_argument('--reason', required=True)
    ap.add_argument('--refresh-unattempted', action='store_true')
    args = ap.parse_args()
    if args.refresh_unattempted and args.spec:
        ap.error('context-only refresh does not take a spec')
    if not args.refresh_unattempted and not args.spec:
        ap.error('reissue requires a spec')
    with wf.workflow_lock():
        wf.recover_transaction()
        print(refresh_unattempted(args.job, args.reason) if args.refresh_unattempted
              else reissue(args.job, args.spec, args.reason))
