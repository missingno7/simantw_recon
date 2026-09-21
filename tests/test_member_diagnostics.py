import copy,json,sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from common import ROOT,fixture
import ne
from codegen_diff import unresolved_member_obligations,render

class MemberDiagnosticTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls): cls.image=ne.parse(fixture('SIMANTW.EXE'))
    def comparison(self,attempt):
        path=ROOT/f'evidence/recovery/workflow/jobs/IsItFood-c02f58780a/attempt{attempt:02}/results.json'
        return json.loads(path.read_text())['results'][0]['comparison']

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

if __name__=='__main__':unittest.main()
