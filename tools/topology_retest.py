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


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('job'); ap.add_argument('spec'); ap.add_argument('--reason', required=True)
    args = ap.parse_args()
    with wf.workflow_lock():
        wf.recover_transaction()
        print(reissue(args.job, args.spec, args.reason))
