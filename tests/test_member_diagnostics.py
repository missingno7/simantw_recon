import copy,json,sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import ROOT,fixture
import ne
from codegen_diff import unresolved_member_obligations,render,compare_code
from search import focused_alignment

class MemberDiagnosticTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls): cls.image=ne.parse(fixture('SIMANTW.EXE'))
    def comparison(self,attempt):
        path=ROOT/f'tests/fixtures/IsItFood-attempt{attempt:02}.json'
        return json.loads(path.read_text())['comparison']

    def test_clean_body_does_not_hide_wrong_selector_segment(self):
        old=self.comparison(4);before=copy.deepcopy(old)
        self.assertFalse(any(r['differences'] for r in old['diagnostic']['aligned_asm']))
        result=unresolved_member_obligations(old,self.image)
        const=next(c for c in result['contributions'] if c['segment']=='CONST')
        fixup=const['failed_fixups'][0]
        self.assertEqual(fixup['candidate_target']['segment'],8)
        self.assertEqual(fixup['original_loader_bindings'][0]['target']['segment'],9)
        self.assertEqual(old,before)
        shown=render(dict(aligned_asm=[],unresolved_member_obligations=result))
        self.assertIn('Whole-member issues:',shown)
        self.assertIn('CONST+0x0',shown)
        self.assertEqual(result['strict_member_result'],'NO_COMPLETE_MATCH')

    def test_exact_member_has_no_unresolved_obligations(self):
        result=unresolved_member_obligations(self.comparison(5),self.image)
        self.assertEqual(result['issues'],[])
        self.assertEqual(result['contributions'],[])

    def test_missing_literal_counts_remain_unknown(self):
        result=unresolved_member_obligations(dict(result='NO_COMPLETE_MATCH',contributions=[dict(original_segment=1,original_offset=0,fixups=[])]),self.image)
        self.assertIsNone(result['contributions'][0]['literal_differences'])

    def test_unplaced_contributions_are_preserved_in_issue_list(self):
        result=unresolved_member_obligations(dict(result='NO_COMPLETE_MATCH',issues=['unplaced contribution CONST'],contributions=[]),self.image)
        self.assertIn('unplaced contribution CONST',result['issues'])
        self.assertEqual(result['strict_member_result'],'NO_COMPLETE_MATCH')

    def test_push_cs_is_a_call_frame_difference_not_register_allocation(self):
        # Real TryMoveDirB failure: the target's far-call frame pushes CS,
        # whereas its old near GetOutB prototype emitted an argument register.
        result=compare_code(bytes.fromhex('0e'),bytes.fromhex('57'))
        self.assertIn('CALL_FRAME_OR_SEGMENT_REGISTER',result['categories'])
        self.assertNotIn('REGISTER_ALLOCATION',result['categories'])
        self.assertIn('call_frame_or_segment_register',result['aligned_asm'][0]['differences'])

    def test_nearby_shape_error_makes_push_alignment_uncertain(self):
        # A missing target argument push can pair PUSH CS with the candidate's
        # unrelated PUSH DI; the pair must carry an alignment caveat.
        result=compare_code(bytes.fromhex('ff76060e e80000'.replace(' ','')),
                            bytes.fromhex('57 9a00000000'.replace(' ','')))
        self.assertIn('ALIGNMENT_UNCERTAIN',result['categories'])

    def test_focused_alignment_includes_late_mismatch(self):
        rows=[dict(target=str(i),candidate=str(i),differences=[]) for i in range(150)]
        rows[140]['differences']=['call_frame_or_segment_register']
        shown=focused_alignment(rows)
        self.assertTrue(any(r['alignment_index']==140 for r in shown))
        self.assertLessEqual(len(shown),60)

    def test_focused_alignment_handles_dense_differences(self):
        rows=[dict(target=str(i),candidate=str(i),differences=['instruction_shape']) for i in range(200)]
        shown=focused_alignment(rows)
        self.assertLessEqual(len(shown),60)
        self.assertTrue(any(r['alignment_index']>=190 for r in shown))

if __name__=='__main__':unittest.main()
