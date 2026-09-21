import copy
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import identity, FormatError
import recovery_workflow as wf
import topology_retest as review

class UnattemptedContextTests(unittest.TestCase):
    def setUp(self):
        tmp=tempfile.TemporaryDirectory();self.addCleanup(tmp.cleanup)
        self.root=Path(tmp.name);self.state=self.root/'state';self.job_id='Test-0123456789'
        self.directory=self.state/'jobs'/self.job_id;self.directory.mkdir(parents=True)
        (self.root/'tools').mkdir();(self.root/'tests').mkdir();(self.root/'layout').mkdir()
        (self.root/'tools/check.py').write_text('new tool')
        self.fixture={'fixture':'unchanged'}
        (self.root/'layout/fixtures.json').write_text(json.dumps(self.fixture))
        self.current={'tools/check.py':identity(self.root/'tools/check.py'),'layout/toolchain.json':{'sha256':'same'}}
        old=copy.deepcopy(self.current);old['tools/check.py']={'sha256':'old'}
        self.job=dict(id=self.job_id,status='OPEN',attempts=[],protected=old,fixture_identity=self.fixture)
        self.save_job()
        for name in ['candidate.c','submission.json']:(self.directory/name).write_text('untouched')
        self.validation=dict(passed=True,inputs={'tools/check.py':identity(self.root/'tools/check.py')})
        self.save_validation()
        for target,field,value in [(wf,'ROOT',self.root),(wf,'STATE',self.state),(wf,'protected',lambda:self.current)]:
            p=patch.object(target,field,value);p.start();self.addCleanup(p.stop)
        p=patch.object(wf,'verify',return_value={});self.verify=p.start();self.addCleanup(p.stop)

    def save_job(self): (self.directory/'job.json').write_text(json.dumps(self.job))
    def save_validation(self): (self.state/'validation.json').write_text(json.dumps(self.validation))
    def run_review(self): return review.refresh_unattempted(self.job_id,'Reviewed change and passing proof tests')

    def test_refresh_preserves_sources_attempts_and_previous_context(self):
        before=copy.deepcopy(self.job);result=self.run_review()
        self.assertEqual(result['recovery_credit'],0)
        after=json.loads((self.directory/'job.json').read_text())
        self.assertEqual(after,dict(before,protected=self.current))
        record=json.loads((self.directory/'expert-context-review-01.json').read_text())
        self.assertEqual(record['previous_job'],before)
        for name in ['candidate.c','submission.json']:
            self.assertEqual((self.directory/name).read_text(),'untouched')
            self.assertEqual(record['preserved_inputs'][name],identity(self.directory/name))
        self.verify.assert_called_once_with(publish=False)

    def test_attempted_job_keeps_its_attempts_after_refresh(self):
        self.job['attempts']=[{'number':1}];self.job['status']='NEEDS_REVISION';self.save_job()
        result=self.run_review()
        self.assertEqual((result['status'],result['attempts']),('NEEDS_REVISION',1))
        self.assertEqual(json.loads((self.directory/'job.json').read_text())['attempts'],[{'number':1}])
    def test_running_exact_escalated_or_pending_jobs_reject(self):
        baseline=copy.deepcopy(self.job)
        for changes in [dict(status='ESCALATED'),dict(status='RUNNING'),dict(status='EXACT_CANDIDATE'),dict(pending_attempt={'output':'x'})]:
            self.job=dict(baseline,**changes);self.save_job()
            with self.assertRaises(FormatError):self.run_review()
        self.verify.assert_not_called()

    def test_changed_fixture_or_toolchain_reject(self):
        self.job['fixture_identity']={};self.save_job()
        with self.assertRaises(FormatError):self.run_review()
        self.job['fixture_identity']=self.fixture
        self.job['protected']['layout/toolchain.json']={'sha256':'different'};self.save_job()
        with self.assertRaises(FormatError):self.run_review()

    def test_failed_stale_or_incomplete_validation_reject(self):
        for validation in [dict(passed=False,inputs=self.validation['inputs']),dict(passed=True,inputs={}),dict(passed=True,inputs={'tools/check.py':{'sha256':'stale'}})]:
            self.validation=validation;self.save_validation()
            with self.assertRaises(FormatError):self.run_review()
        self.verify.assert_not_called()

    def test_added_unvalidated_tool_reject(self):
        (self.root/'tools/new.py').write_text('new')
        with self.assertRaises(FormatError):self.run_review()

    def test_failed_full_verification_does_not_refresh(self):
        before=(self.directory/'job.json').read_bytes()
        self.verify.side_effect=FormatError('full proof failed')
        with self.assertRaises(FormatError):self.run_review()
        self.assertEqual((self.directory/'job.json').read_bytes(),before)
        self.assertEqual(list(self.directory.glob('expert-context-review-*')),[])

    def test_missing_reason_and_invalid_id_reject(self):
        with self.assertRaises(FormatError):review.refresh_unattempted(self.job_id,' ')
        with self.assertRaises(FormatError):review.refresh_unattempted('../outside','reason')

if __name__=='__main__':unittest.main()
