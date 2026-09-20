import copy, json, sys, unittest
from unittest.mock import patch
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import ROOT, FormatError, read_json
from cfg_solver import solve
from codegen_grinder import variants, rank

class CFGTests(unittest.TestCase):
    def test_skipped_nop_padding_is_probable_not_proof(self):
        r=solve(bytes.fromhex('eb0190cb'),0,4)
        self.assertEqual((r['status'],r['size']),('PROBABLE',4))
        self.assertEqual(r['gaps'][0]['classification'],'ALIGNMENT_NOP')
    def test_unowned_data_not_silently_padding(self):
        self.assertIsNone(solve(bytes.fromhex('eb0100cb'),0,4)['end'])
    def test_loader_operand_cannot_be_padding(self):
        r=solve(bytes.fromhex('eb0190cb'),0,4,relocations=[dict(sites=[2],width=1)])
        self.assertIsNone(r['end'])
    def test_next_public_is_not_a_return(self):
        self.assertIsNone(solve(bytes.fromhex('9090cb'),0,2)['end'])
    def test_cross_entry_tail_and_indirect_jump(self):
        self.assertEqual(solve(bytes.fromhex('eb02cb90cb'),0,2)['status'],'SHARED_TAIL')
        self.assertEqual(solve(bytes.fromhex('ffe3'),0,2)['status'],'AMBIGUOUS_TABLE')
    def test_overlapping_public_is_explicit(self):
        self.assertEqual(solve(bytes.fromhex('9090cb'),0,3,entries=[0,1])['status'],'OVERLAPPING_ENTRY')
    def test_conditional_arm_cannot_disappear(self):
        r=solve(bytes.fromhex('7402cb90ffe3'),0,6)
        self.assertEqual(r['status'],'AMBIGUOUS_TABLE')
        self.assertIsNone(r['end'])

class GrinderTests(unittest.TestCase):
    def test_no_unexplained_mutation(self):
        with self.assertRaises(FormatError):list(variants(dict(template='@X@',axes=[dict(marker='@X@',values=['a'])])))
    def test_duplicate_or_missing_marker_rejected(self):
        for template in ['@X@@X@','none']:
            with self.assertRaises(FormatError):list(variants(dict(template=template,axes=[dict(name='x',marker='@X@',rationale='test',values=['a'])])))
    def test_semantic_corpus_generation_stable(self):
        d=read_json(ROOT/'evidence/codegen/specs/DoWinHelp.json')
        self.assertEqual(len(list(variants(d))),40)
        d=read_json(ROOT/'evidence/codegen/specs/db_GetObjectSize.json')
        self.assertEqual(len(list(variants(d))),384)
    def test_partial_bytes_never_outrank_exact_member(self):
        exact=dict(comparison=dict(result='CONFIRMED_MEMBER',fixups_equal=1,fixups_total=1,literal_equal=4,literal_compared=4))
        bad=dict(comparison=dict(result='NO_COMPLETE_MATCH',fixups_equal=99,fixups_total=100,literal_equal=100,literal_compared=100))
        self.assertGreater(rank(exact),rank(bad))

class BatchQueueTests(unittest.TestCase):
    def test_large_queue_keeps_every_job_and_amortizes_boot(self):
        import compiler
        jobs=[dict(source=str(i),flags=['/AL']) for i in range(384)]
        with patch.object(compiler,'_compile_session',side_effect=lambda group,*args:list(group)) as worker:
            result=compiler._compile_batch(jobs)
        self.assertEqual(result,jobs)
        self.assertEqual([len(call.args[0]) for call in worker.call_args_list],[96,96,96,96])
    def test_invalid_session_budget_rejected(self):
        import compiler
        with self.assertRaises(FormatError):compiler._compile_batch([],session_limit=0)

class RecoveredTUProofTests(unittest.TestCase):
    def test_second_menu_function_and_private_const_are_required(self):
        import omf, ne, mapsym
        from common import fixture
        from library_match import compare_member, import_symbols
        raw=fixture('SIMANTW.EXE');n=ne.parse(raw);symbols=mapsym.parse(fixture('SIMANTW.SYM'))
        imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
        from compiler import compile_source
        obj,_=compile_source('src/recovered/menu_state_tu.c',['/AL','/G2','/Gs','/Oelw','/NTGR_MODULE'],'msc700')
        m=omf.parse(obj.read_bytes())
        self.assertEqual(compare_member(m,raw,n,symbols,imports)['result'],'STRONGLY_SUPPORTED_MEMBER')
        from codegen_grinder import score_object
        with self.assertRaises(FormatError):score_object(m,raw,n,symbols,imports,'_DoWinHelp')
        pub=next(p for p in m['publics'] if p['name']=='_SetMenuOptionState')
        bad=copy.deepcopy(m);seg=bad['segments'][pub['segment']-1];code=bytearray.fromhex(seg['data_hex']);code[pub['offset']]^=1;seg['data_hex']=code.hex()
        self.assertEqual(compare_member(bad,raw,n,symbols,imports)['result'],'NO_COMPLETE_MATCH')
        bad=copy.deepcopy(m);seg=next(s for s in bad['segments'] if s['name']=='CONST' and s['length'])
        # Removing selector evidence must not leave a successful code-only proof.
        bad['fixups']=[f for f in bad['fixups'] if f['segment']!=seg['index']]
        self.assertEqual(compare_member(bad,raw,n,symbols,imports)['result'],'NO_COMPLETE_MATCH')

if __name__=='__main__':unittest.main()

