"""MSC 7 switch jump tables are recognised only from the exact dispatch idiom."""
import sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from cfg_solver import solve
from codegen_diff import compare_code

def table(*targets):return b''.join(t.to_bytes(2,'little') for t in targets)

# cmp ax,1 ; ja default ; shl ax,1 ; xchg bx,ax ; jmp cs:[bx+0x0d] ; T[2] ; default: ret ; case1: ret
JA=bytes.fromhex('3d0100'+'770c'+'d1e0'+'93'+'2effa70d00')+table(0x11,0x12)+bytes.fromhex('cbcb')
# cmp ax,1 ; jbe shift ; jmp default ; shift: shl ax,1 ; xchg bx,ax ; jmp cs:[bx+0x0f] ; T[2] ; default: ret ; case: ret
JBE=bytes.fromhex('3d0100'+'7602'+'eb0c'+'d1e0'+'93'+'2effa70f00')+table(0x13,0x14)+bytes.fromhex('cbcb')
# table preceded by one alignment NOP
NOP=bytes.fromhex('3d0100'+'770d'+'d1e0'+'93'+'2effa70e00'+'90')+table(0x12,0x13)+bytes.fromhex('cbcb')

class JumpTables(unittest.TestCase):
    def test_ja_form_closes_with_table_gap(self):
        r=solve(JA,0,len(JA))
        self.assertEqual(r['status'],'PROBABLE');self.assertEqual(r['end'],len(JA))
        self.assertEqual([t['targets'] for t in r['jump_tables']],[[0x11,0x12]])
        self.assertEqual([g['classification'] for g in r['gaps']],['JUMP_TABLE'])
        self.assertEqual(sorted(e['kind'] for e in r['edges'] if e['kind']=='TABLE'),['TABLE','TABLE'])
    def test_jbe_form_reaches_shift_by_branch(self):
        r=solve(JBE,0,len(JBE))
        self.assertEqual(r['end'],len(JBE));self.assertEqual(r['jump_tables'][0]['count'],2)
    def test_alignment_nop_before_table(self):
        r=solve(NOP,0,len(NOP))
        self.assertEqual(r['end'],len(NOP));self.assertEqual([g['classification'] for g in r['gaps']],['JUMP_TABLE'])
    def test_table_bytes_with_relocation_are_not_a_table(self):
        r=solve(JA,0,len(JA),relocations=[dict(sites=[0x0d],width=2)])
        self.assertEqual(r['status'],'AMBIGUOUS_TABLE');self.assertIsNone(r['end'])
    def test_entry_outside_bound_is_not_a_table(self):
        bad=JA[:0x0d]+table(0x11,0x40)+JA[0x11:]
        self.assertEqual(solve(bad,0,len(bad))['status'],'AMBIGUOUS_TABLE')
    def test_missing_bound_check_is_ambiguous(self):
        # shl ax,1 ; xchg bx,ax ; jmp cs:[bx+8] ; T ; ret ; ret
        code=bytes.fromhex('d1e0'+'93'+'2effa70800')+table(0x0c,0x0d)+bytes.fromhex('cbcb')
        self.assertEqual(solve(code,0,len(code))['status'],'AMBIGUOUS_TABLE')
    def test_table_not_adjacent_to_jump_is_ambiguous(self):
        code=bytes.fromhex('3d0100'+'770a'+'d1e0'+'93'+'2effa70f00'+'cb90')+table(0x13,0x13)+bytes.fromhex('cb')
        self.assertEqual(solve(code,0,len(code))['status'],'AMBIGUOUS_TABLE')

class DiagnosticTables(unittest.TestCase):
    def test_table_words_align_as_case_targets(self):
        r=solve(JA,0,len(JA));tables=[(t['table'],t['count']) for t in r['jump_tables']]
        d=compare_code(JA,JA,closure=[r,r],target_tables=tables,candidate_tables=tables)
        self.assertEqual(d['opcode_matches'],d['opcode_total']);self.assertTrue(d['cfg_shape_match'])
        self.assertEqual([x['target'] for x in d['aligned_asm'] if x['target'].startswith('dw')],['dw offset 0x11','dw offset 0x12'])
    def test_bound_table_word_uses_fixup_target(self):
        r=solve(JA,0,len(JA));tables=[(t['table'],t['count']) for t in r['jump_tables']]
        shifted=JA[:0x0d]+bytes(4)+JA[0x11:]
        bindings={0x0d:dict(kind='internal',segment=1,offset=0x11),0x0f:dict(kind='internal',segment=1,offset=0x12)}
        d=compare_code(JA,shifted,None,bindings,closure=[r,r],target_tables=tables,candidate_tables=tables)
        self.assertEqual([x['differences'] for x in d['aligned_asm'] if x['target'].startswith('dw')],[[],[]])

if __name__=='__main__':unittest.main()
