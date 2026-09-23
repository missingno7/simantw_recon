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

    def test_supersede_requires_verified_tu_and_preserves_history(self):
        proof=self.root/'proof.json';proof.write_text('{}')
        recipe={'unit':'unit-1','promotion_evidence':'proof.json','source':'unit.c'}
        self.job.update(status='NEEDS_REVISION',symbol='_Test',attempts=[{'number':1}])
        self.save_job()
        with patch.object(wf,'recipes',return_value={'_Test':recipe}):
            result=review.supersede_admitted(self.job_id,'TU admitted the member')
        self.assertEqual(result['status'],'SUPERSEDED_BY_TU')
        after=json.loads((self.directory/'job.json').read_text())
        self.assertEqual(after['attempts'],[{'number':1}])
        self.assertEqual(after['superseded_by'],'proof.json')
        record=json.loads((self.directory/'superseded-by-tu.json').read_text())
        self.assertEqual(record['previous_job'],self.job)
        self.verify.assert_called_once_with(publish=False)

    def test_supersede_rejects_unadmitted_or_unverified(self):
        self.job.update(symbol='_Test');self.save_job()
        with patch.object(wf,'recipes',return_value={}):
            with self.assertRaises(FormatError):review.supersede_admitted(self.job_id,'reason')
        self.assertFalse((self.directory/'superseded-by-tu.json').exists())

    def test_exhausted_job_gets_one_recorded_hypothesis_attempt(self):
        self.job.update(status='ESCALATED',symbol='_Test',flags=['/AL'],
                        attempts=[{'submission_digest':str(i),'candidates':1} for i in range(8)])
        self.save_job()
        spec={'symbol':'_Test','source':'source.c','compiler':'msc700','flags':['/AL'],
              'max_candidates':1,'axes':[],'publics':['_Test'],'semantic_summary':'new ABI'}
        (self.root/'spec.json').write_text(json.dumps(spec))
        with patch.object(review,'ROOT',self.root),patch.object(wf,'check_submission'),patch.object(wf,'variants',side_effect=lambda spec:iter([('source',{})])), \
             patch.object(wf,'experiment_digest',return_value='new-digest'), \
             patch.object(wf,'run_attempt',return_value={'job':self.job_id}):
            result=review.reissue(self.job_id,'spec.json','Original far-call frame proves ABI change','ABI')
            self.assertEqual(result['job'],self.job_id)
            after=json.loads((self.directory/'job.json').read_text())
            self.assertEqual(len(after['attempts']),8)
            self.assertEqual(after['budget_extensions'][0]['cause'],'ABI')
            self.assertEqual(after['status'],'OPEN')
            after['status']='ESCALATED';after['attempts'].append({'submission_digest':'used','candidates':1});self.job=after;self.save_job()
            with self.assertRaises(FormatError):
                review.reissue(self.job_id,'spec.json','Repeated ABI extension','ABI')

if __name__=='__main__':unittest.main()
