"""Failure-path tests for bounded recovery handoff; no live manifests mutated."""
import copy
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import FormatError, identity, sha256, read_json, write_json
import compiler
import codegen_cache as cache
import recovery_gate as gate
import recovery_workflow as workflow
from blocker_ledger import workflow_cases

class ScopeTests(unittest.TestCase):
    def setUp(self):
        self.module=dict(publics=[dict(name='_a',segment=1,offset=0)],segments=[dict(name='GR',**{'class':'CODE'},length=4,initialized_ranges=[(0,4)])])
        self.targets={'_a':dict(segment=1,offset=10,size=4,code_segment='GR',extent_status='CONFIRMED')}
    def check(self):
        with patch.object(gate,'unique_symbol',return_value=(1,10)):
            gate.check_coverage(self.module,{},self.targets)
    def test_full_scope_accepted(self):self.check()
    def test_matching_prefix_is_not_a_function(self):
        self.module['segments'][0]['length']=3
        with self.assertRaisesRegex(FormatError,'coverage'):self.check()
    def test_hole_is_not_initialized_coverage(self):
        self.module['segments'][0]['initialized_ranges']=[(0,1),(2,4)]
        with self.assertRaisesRegex(FormatError,'coverage'):self.check()
    def test_wrong_public_rejected(self):
        self.module['publics'][0]['name']='_b'
        with self.assertRaisesRegex(FormatError,'public'):self.check()
    def test_wrong_group_rejected(self):
        self.module['segments'][0]['name']='OTHER'
        with self.assertRaisesRegex(FormatError,'group'):self.check()
    def test_wrong_mapsym_address_rejected(self):
        self.targets['_a']['offset']=11
        with self.assertRaisesRegex(FormatError,'MAPSYM'):self.check()
    def test_probable_is_not_admitted_scope(self):
        self.targets['_a']['extent_status']='PROBABLE'
        with self.assertRaisesRegex(FormatError,'unreviewed'):self.check()
    def test_complete_member_mismatch_rejected(self):
        with patch.object(gate,'check_coverage'),patch.object(gate,'compare_member',return_value=dict(result='NO_COMPLETE_MATCH',issues=['private CONST'])):
            with self.assertRaisesRegex(FormatError,'complete member'):gate.check_member({},b'',{},{},{},{})

class AdmissionCFGTests(unittest.TestCase):
    def admit(self,original,candidate,entries):
        module=dict(publics=[dict(name='_a',segment=1,offset=0)],segments=[dict(name='GR',**{'class':'CODE'},length=len(candidate),initialized_ranges=[(0,len(candidate))],data_hex=candidate.hex())])
        symbols=dict(segments=[dict(number=1,name='GR',symbols=[dict(name=name,offset=pos) for name,pos in entries])])
        image=dict(segments=[dict(kind='CODE',file_offset=0,logical_size=len(original),relocations=[])])
        return gate.admission_targets(module,original,image,symbols,['_a'])
    def test_original_extent_must_be_covered(self):
        with self.assertRaisesRegex(FormatError,'full original'):
            self.admit(bytes.fromhex('90cb'),bytes.fromhex('cb'),[('_a',0)])
    def test_incoming_jump_rejects_isolated_tail(self):
        with self.assertRaisesRegex(FormatError,'cross-entry'):
            self.admit(bytes.fromhex('cbebfd'),bytes.fromhex('cb'),[('_a',0),('_b',1)])
    def test_alias_is_not_independent_function(self):
        with self.assertRaisesRegex(FormatError,'alias'):
            self.admit(bytes.fromhex('cb'),bytes.fromhex('cb'),[('_a',0),('_alias',0)])
    def test_jump_table_requires_expert_evidence(self):
        with self.assertRaisesRegex(FormatError,'expert extent'):
            self.admit(bytes.fromhex('ffe3'),bytes.fromhex('ffe3'),[('_a',0)])
    def test_closed_isolated_scope_is_eligible(self):
        target=self.admit(bytes.fromhex('90cb'),bytes.fromhex('90cb'),[('_a',0)])
        self.assertEqual(target['_a']['size'],2)

class TemporaryWorkflow(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup);self.root=Path(self.tmp.name)
        for module in (workflow,compiler,cache):
            p=patch.object(module,'ROOT',self.root);p.start();self.addCleanup(p.stop)
        self.state=self.root/'evidence/recovery/workflow';p=patch.object(workflow,'STATE',self.state);p.start();self.addCleanup(p.stop)
    def put(self,name,data):
        path=self.root/name;path.parent.mkdir(parents=True,exist_ok=True);path.write_text(data);return path
    def fixture(self):
        self.put('layout/toolchain.json','{"files":{}}');self.put('tools/compiler.py','wrapper');self.put('input.c','int f(void) {return 1;}');self.put('output.obj','OMF')
        return dict(exit_code=0,unsupported_option=False,source='input.c',source_identity=identity(self.root/'input.c'),object='output.obj',object_identity=identity(self.root/'output.obj'),toolchain_lock_sha256=sha256((self.root/'layout/toolchain.json').read_bytes()))

class ReceiptAndCacheTests(TemporaryWorkflow):
    def test_failed_or_unknown_option_receipt_rejected(self):
        r=self.fixture()
        for changes in [dict(exit_code=1),dict(unsupported_option=True)]:
            with self.assertRaises(FormatError):compiler.validate_receipt(dict(r,**changes))
    def test_lock_cache_never_skips_object_or_source_hash(self):
        r=self.fixture();seen=set()
        with patch.object(compiler,'verify_lock') as lock:
            compiler.validate_receipt(r,seen);compiler.validate_receipt(r,seen);self.assertEqual(lock.call_count,1)
            self.put('input.c','changed')
            with self.assertRaisesRegex(FormatError,'source'):compiler.validate_receipt(r,seen)
            self.put('input.c','int f(void) {return 1;}');self.put('output.obj','changed')
            with self.assertRaisesRegex(FormatError,'object'):compiler.validate_receipt(r,seen)
    def test_cache_reuses_receipt_and_recompiles_corrupt_object(self):
        original=self.fixture();jobs=[dict(source='input.c',flags=['/AL'])]
        def compile_jobs(jobs,compiler_name):
            return [(self.root/'output.obj',dict(original,source=j['source'],compiler=compiler_name,flags=j['flags'],batch_directory='one-boot')) for j in jobs]
        with patch.object(cache,'compile_batch',side_effect=compile_jobs) as worker:
            first,a=cache.compile_cached(jobs);second,b=cache.compile_cached(jobs)
            self.assertEqual((a['misses'],b['hits'],b['environment_launches'],worker.call_count),(1,1,0,1))
            first[0][0].write_text('corrupt')
            _,c=cache.compile_cached(jobs);self.assertEqual((c['misses'],worker.call_count),(1,2))
    def test_changed_toolchain_snapshot_is_rejected(self):
        r=self.fixture();self.put('layout/toolchain.json','{"files":{},"changed":true}')
        with self.assertRaisesRegex(FormatError,'toolchain'):compiler.validate_receipt(r)

FLAGS=['/AL','/G2','/Gs','/Oelw','/NTGR_MODULE']

class BudgetTests(TemporaryWorkflow):
    def spec(self):return dict(symbol='_a',compiler='msc700',flags=list(FLAGS),template='int a(void) { return 1; }',semantic_summary='Return one',publics=['_a'],max_candidates=96)
    def job(self):return dict(symbol='_a',flags=list(FLAGS),status='OPEN',attempts=[])
    def reader(self,spec,job):
        return lambda path:job if str(path).endswith('job.json') else spec
    def test_unbounded_or_changed_profile_rejected(self):
        for change in [dict(max_candidates=97),dict(flags=['/AL','/Oa']),dict(semantic_summary=''),dict(publics=['_a','_b'])]:
            with self.assertRaises(FormatError):workflow.check_submission(dict(self.spec(),**change),self.job())
    def test_uncatalogued_flags_rejected_even_when_job_agrees(self):
        job=dict(self.job(),flags=['/AL','/G2','/Gs','/Ox','/NTGR_MODULE']);spec=dict(self.spec(),flags=list(job['flags']))
        with self.assertRaisesRegex(FormatError,'catalog'):workflow.check_submission(spec,job)
    def test_assembly_or_absolute_pointer_rejected(self):
        for code in ['int a(void) { _asm nop; }','char far *p=(char far *)0x12345678;']:
            with self.assertRaises(FormatError):workflow.check_submission(dict(self.spec(),template=code),self.job())
    def test_product_cannot_exceed_budget(self):
        spec=dict(self.spec(),template='@a@ @b@',axes=[dict(name=x,marker='@'+x+'@',rationale='test',values=[str(i) for i in range(10)]) for x in 'ab'])
        with self.assertRaisesRegex(FormatError,'budget'):workflow.check_submission(spec,self.job())
    def test_source_outside_repository_rejected(self):
        spec=self.spec();spec.pop('template');spec['source']='../external.c'
        with self.assertRaisesRegex(FormatError,'repository'):workflow.check_submission(spec,self.job())
    def test_reworded_description_is_not_a_new_experiment(self):
        spec=self.spec();changed=dict(spec,semantic_summary='Different description of same source',max_candidates=95)
        self.assertEqual(workflow.experiment_digest(spec),workflow.experiment_digest(changed))
    def test_duplicate_experiment_does_not_compile(self):
        spec=self.spec();job=self.job();digest=workflow.experiment_digest(spec);job['attempts']=[dict(submission_digest=digest)]
        with patch.object(workflow,'checked_job',return_value=(self.root,job)),patch.object(workflow,'read_json',side_effect=self.reader(spec,job)),patch.object(workflow,'run') as run:
            with self.assertRaisesRegex(FormatError,'identical'):workflow.run_attempt('unused')
            run.assert_not_called()
    def test_final_mismatch_escalates_without_promotion(self):
        spec=self.spec();job=self.job();job['attempts']=[dict(submission_digest='previous%d'%i,candidates=1) for i in range(workflow.MAX_ATTEMPTS-1)]
        result=dict(results=[dict(candidate=0,comparison=dict(result='NO_COMPLETE_MATCH'))],completed_candidates=1,candidates=1,cache={},exact_candidates=[])
        with patch.object(workflow,'checked_job',return_value=(self.root,job)),patch.object(workflow,'read_json',side_effect=self.reader(spec,job)),patch.object(workflow,'run',return_value=result),patch.object(workflow,'refresh') as refresh,patch.object(workflow,'commit_core') as commit:
            response=workflow.run_attempt('unused')
            self.assertEqual(response['status'],'ESCALATED');refresh.assert_called_once();commit.assert_not_called()
    def test_source_syntax_error_can_be_revised_without_expert_escalation(self):
        spec=self.spec();job=self.job();result=dict(results=[dict(candidate=0,comparison=dict(result='COMPILE_FAILED'))],completed_candidates=0,candidates=1,cache={},exact_candidates=[])
        with patch.object(workflow,'checked_job',return_value=(self.root,job)),patch.object(workflow,'read_json',side_effect=self.reader(spec,job)),patch.object(workflow,'run',return_value=result),patch.object(workflow,'queue'):
            response=workflow.run_attempt('unused')
            self.assertEqual(response['status'],'NEEDS_REVISION')
    def test_total_candidate_budget_prevents_more_compilation(self):
        spec=self.spec();job=self.job();job['attempts']=[dict(submission_digest=str(i),candidates=96) for i in range(2)]
        with patch.object(workflow,'checked_job',return_value=(self.root,job)),patch.object(workflow,'read_json',side_effect=self.reader(spec,job)),patch.object(workflow,'run') as run:
            with self.assertRaisesRegex(FormatError,'total target budget'):workflow.run_attempt('unused')
            run.assert_not_called()
    def test_mismatch_cannot_enter_promotion(self):
        job=dict(status='EXACT_CANDIDATE',attempts=[dict(report='report.json')])
        result=dict(exact_candidates=[0],results=[dict(candidate=0,comparison=dict(result='NO_COMPLETE_MATCH'))])
        with patch.object(workflow,'checked_job',return_value=(self.root,job)),patch.object(workflow,'read_json',return_value=result),patch.object(workflow,'compile_source') as compile_,patch.object(workflow,'commit_core') as commit:
            with self.assertRaises(FormatError):workflow.promote('unused')
            compile_.assert_not_called();commit.assert_not_called()
    def test_shared_tail_and_old_blocker_avoid_ready_lane(self):
        card=dict(symbol='_a',extent=dict(end=3,size=3,status='SHARED_TAIL'),disassembly=[],calls=[])
        self.assertEqual(workflow.classify(card,{})[0],'EXPERT')
        card['extent']['status']='PROBABLE';self.assertEqual(workflow.classify(card,{'_a':dict(blockers=['REGISTER_ALLOCATION'])})[0],'EXPERT')
        self.assertEqual(workflow.classify(card,{})[0],'READY')

class TransactionTests(TemporaryWorkflow):
    def prepare(self):
        for name in workflow.CORE:self.put(name,'old')
        return {p:dict(new=p) for p in workflow.CORE}
    def test_partial_commit_restores_every_old_file(self):
        values=self.prepare();original=workflow.atomic_bytes;calls=[]
        def fail_once(path,data):
            calls.append(path)
            if len(calls)==3:raise OSError('simulated disk failure')
            original(path,data)
        with patch.object(workflow,'atomic_bytes',side_effect=fail_once):
            with self.assertRaises(OSError):workflow.commit_core(values)
        self.assertTrue(all((self.root/p).read_text()=='old' for p in workflow.CORE))
        self.assertEqual(read_json(self.state/'transaction.json')['status'],'ROLLED_BACK_AFTER_INTERRUPTION')
    def test_crash_after_commit_reconciles_job(self):
        values=self.prepare();path=self.state/'jobs/a-1234567890/job.json';write_json(path,dict(status='EXACT_CANDIDATE'))
        workflow.commit_core(values,'a-1234567890');workflow.recover_transaction()
        self.assertEqual(read_json(path)['status'],'PROMOTED');self.assertNotIn('old',read_json(self.state/'transaction.json'))
    def test_interrupted_worker_is_durably_parked(self):
        path=self.state/'jobs/a-1234567890/job.json';write_json(path,dict(id='a-1234567890',status='RUNNING'))
        with patch.object(workflow,'LOCKS',self.root/'locks'),patch.object(workflow,'refresh') as refresh:workflow.recover_interrupted_attempts()
        self.assertEqual(read_json(path)['status'],'ESCALATED');refresh.assert_called_once()
    def test_live_worker_is_not_parked(self):
        path=self.state/'jobs/a-1234567890/job.json';write_json(path,dict(id='a-1234567890',status='RUNNING'))
        with patch.object(workflow,'LOCKS',self.root/'locks'),patch.object(workflow,'refresh') as refresh:
            with workflow.job_lock('a-1234567890'):
                workflow.recover_interrupted_attempts()
        self.assertEqual(read_json(path)['status'],'RUNNING');refresh.assert_not_called()
    def test_independent_jobs_lock_independently(self):
        with patch.object(workflow,'LOCKS',self.root/'locks'):
            with workflow.job_lock('a-1234567890'):
                with workflow.job_lock('b-1234567890'):pass
                with self.assertRaisesRegex(FormatError,'another process'):
                    with workflow.job_lock('a-1234567890'):pass
            with workflow.job_lock('a-1234567890'):pass
    def test_global_lock_waits_then_times_out(self):
        with patch.object(workflow,'ROOT',self.root):
            with workflow.global_lock():
                with self.assertRaisesRegex(FormatError,'shared-state'):
                    with workflow.global_lock(timeout=0.2):pass
    def test_stale_attempt_result_is_not_recorded(self):
        # Another process changed the job while this attempt compiled: refuse to commit.
        spec=dict(symbol='_a',compiler='msc700',flags=list(FLAGS),template='int a(void) { return 1; }',semantic_summary='Return one',publics=['_a'],max_candidates=96)
        job=dict(symbol='_a',flags=list(FLAGS),status='OPEN',attempts=[]);stolen=dict(job,status='ESCALATED')
        result=dict(results=[dict(candidate=0,comparison=dict(result='NO_COMPLETE_MATCH'))],completed_candidates=1,candidates=1,cache={},exact_candidates=[])
        reader=lambda path:stolen if str(path).endswith('job.json') else spec
        with patch.object(workflow,'checked_job',return_value=(self.root,job)),patch.object(workflow,'read_json',side_effect=reader),patch.object(workflow,'run',return_value=result),patch.object(workflow,'refresh'),patch.object(workflow,'queue'):
            with self.assertRaisesRegex(FormatError,'changed while'):workflow.run_attempt('unused')
        self.assertEqual(job['attempts'],[])
    def test_escalation_survives_ledger_rebuild(self):
        path=self.state/'jobs/a-1234567890/job.json';write_json(path,dict(id='a-1234567890',symbol='_a',status='ESCALATED',blockers=['FAR_POINTER_TYPE'],reason='LES mismatch',next_experiment='Inspect callers',attempts=[]))
        write_json(path.parent/'submission.json',dict(source='candidate.c',semantic_summary='Store far pointer'))
        cases=workflow_cases(self.root)
        self.assertEqual(cases['_a']['next_experiment'],'Inspect callers');self.assertEqual(cases['_a']['blockers'],['FAR_POINTER_TYPE'])

if __name__=='__main__':unittest.main()
