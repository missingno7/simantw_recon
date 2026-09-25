"""Search diagnostics and structural boundaries, independent from proof acceptance."""
import sys,unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from codegen_diff import compare_code,diagnose
from compiler_worker import validate_flags
from common import FormatError
from context import certify
import compiler

class InstructionDiffTests(unittest.TestCase):
    def compare(self,a,b,**kwargs):return compare_code(bytes.fromhex(a),bytes.fromhex(b),**kwargs)
    def test_register_only(self):
        r=self.compare('8bc3cb','8bc1cb');self.assertEqual(r['register_only_differences'],1);self.assertTrue(r['cfg_shape_match']);self.assertIsNone(r['first_structural_difference'])
    def test_memory_register_schedule(self):
        r=self.compare('8b04cb','8b05cb');self.assertEqual(r['register_only_differences'],1);self.assertEqual(r['memory_operand_differences'],0)
    def test_stack_local_layout(self):
        r=self.compare('8b46fecb','8b46fccb');self.assertEqual(r['stack_local_differences'],1);self.assertIn('LOCAL_FRAME_LAYOUT',r['categories'])
    def test_immediate_difference(self):
        r=self.compare('b80100cb','b80200cb');self.assertEqual(r['immediate_differences'],1)
    def test_relocation_chain_words_are_not_immediates(self):
        binding={1:dict(kind='internal',segment=10,offset=100)}
        r=self.compare('b84512cb','b80000cb',target_bindings=binding,candidate_bindings=binding);self.assertEqual(r['immediate_differences'],0)
    def test_branch_target_difference(self):
        r=self.compare('750290cbcb','750190cbcb');self.assertEqual(r['branch_target_differences'],1)
    def test_unknown_indirect_cfg_not_reported_as_match(self):
        r=self.compare('ffe3','ffe3');self.assertIsNone(r['cfg_shape_match'])
    def test_instruction_reordering(self):
        r=self.compare('b8010043cb','43b80100cb');self.assertIn('INSTRUCTION_ORDER',r['categories'])
    def test_link_normalization_does_not_patch_object_or_grant_proof(self):
        code='9a00000000cb';module=dict(publics=[dict(name='_a',segment=1,offset=0)],segments=[dict(data_hex=code,length=6)])
        symbols=dict(segments=[dict(number=1,symbols=[dict(name='_a',offset=0)])]);image=dict(segments=[dict(file_offset=0,logical_size=6,relocations=[])])
        comparison=dict(result='NO_COMPLETE_MATCH',contributions=[dict(original_segment=1,original_offset=0,fixups=[],transformations=[dict(offset=0,target=dict(kind='internal',segment=1,offset=21))])])
        r=diagnose(module,bytes.fromhex('900ee81000cb'),image,symbols,'_a',comparison)
        self.assertTrue(r['instruction_layout_match']);self.assertEqual(r['opcode_matches'],4);self.assertFalse(r['exact_match']);self.assertEqual(module['segments'][0]['data_hex'],code)
    def test_diagnostic_score_has_no_acceptance_field(self):
        r=self.compare('cb','cb');self.assertEqual(r['score'],1);self.assertNotIn('admitted',r);self.assertIn('DIAGNOSTIC_ONLY',r['scope'])

class StructuralBoundaryTests(unittest.TestCase):
    def test_unclosed_extent_never_certified(self):
        r=certify(dict(extent=dict(end=None,status='AMBIGUOUS_TABLE')),b'',{},{})
        self.assertEqual(r['status'],'UNCONFIRMED')
    def test_known_shared_tail_never_certified(self):
        r=certify(dict(extent=dict(end=1,status='SHARED_TAIL')),b'',{},{})
        self.assertEqual(r['status'],'UNCONFIRMED')
    def test_flags_cannot_inject_commands_or_host_paths(self):
        for flags in [['/AL & exit'],['/FoC:\\evil'],['/Oe\nexit'],[]]:
            with self.assertRaises(FormatError):validate_flags(flags)
        validate_flags(['/AL','/G2','/Gs','/Oelw','/NTGR_MODULE'])
    def test_msc600a_does_not_switch_to_win31(self):self.assertFalse(compiler.persistent_enabled('msc600a'))
    def test_reference_override_retains_original_runner(self):
        with patch.dict('os.environ',{'SIMANT_COMPILER_REFERENCE':'1'}):self.assertFalse(compiler.persistent_enabled('msc700'))

class ServiceTransportTests(unittest.TestCase):
    def test_transient_completed_read_does_not_recompile(self):
        import tempfile,json
        import compiler_service as service
        from common import write_json,read_json
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);base=root/'service';(base/'jobs').mkdir(parents=True);(root/'input.c').write_text('int a(void) {return 0;}');(root/'output.obj').write_bytes(b'object')
            original_atomic=service.atomic;reads=[]
            def deliver(path,value):
                original_atomic(path,value)
                if path.parent.name=='requests':
                    for key in value['requests']:write_json(base/'completed'/(key+'.json'),dict(object='output.obj',receipt=dict(exit_code=0)))
            def busy_once(path):
                if Path(path).parent.name=='completed' and not reads:
                    reads.append(path);raise PermissionError('simulated Windows rename/read sharing race')
                return read_json(path)
            with patch.object(service,'ROOT',root),patch.object(service,'BASE',base),patch.object(service,'start',return_value=dict(implementation={})),patch.object(service,'state',return_value=dict(status='RUNNING',heartbeat=__import__('time').time())),patch.object(service,'atomic',side_effect=deliver),patch.object(service,'read_json',side_effect=busy_once):
                result=service.compile_jobs([dict(source='input.c',flags=['/AL'])])
            self.assertEqual(len(result),1);self.assertEqual(len(list((base/'pending').glob('*.json'))),1);self.assertEqual(len(reads),1)

if __name__=='__main__':unittest.main()
