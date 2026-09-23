import sys
import unittest
from pathlib import Path

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from analysis import decoder
from topology_context import ds_states,direct_data_bindings


class SegmentHintTests(unittest.TestCase):
    def states(self,hexcode):
        return ds_states(list(decoder().disasm(bytes.fromhex(hexcode),0)))

    def test_ds_write_call_and_join_invalidate_local_name_assumption(self):
        self.assertEqual(self.states('a134128ed8a13412')[5],'UNKNOWN')
        self.assertEqual(self.states('a13412e80000a13412')[6],'UNKNOWN')
        self.assertEqual(self.states('eb00a13412')[2],'UNKNOWN')

    def test_direct_name_is_conditional_after_ds_change(self):
        card={'disassembly':[{'bytes':'a134128ed8a13412','offset':0,'mnemonic':'mov'}]}
        segments=[{'symbols':[],'relocations':[]} for _ in range(10)]
        segments[9]['symbols']=[{'offset':0x1234,'name':'_Example'}]
        result=direct_data_bindings(card,{'segments':segments},{'segments':segments})
        self.assertEqual(result[0]['exact_mapsym_names'],['_Example'])
        self.assertEqual(result[1]['exact_mapsym_names'],[])
        self.assertEqual(result[1]['possible_dgroup_names'],['_Example'])
        self.assertEqual(result[1]['ds_state'],'UNKNOWN')

    def test_far_selector_after_call_is_visible_only_as_conditional(self):
        card={'disassembly':[{'bytes':'e800008e063412268a07','offset':0,'mnemonic':'call'}]}
        segments=[{'symbols':[],'relocations':[]} for _ in range(10)]
        segments[7]['symbols']=[{'offset':0,'name':'_Dx8'}]
        segments[9]['relocations']=[{'source_type':2,'additive':False,
                                      'target':{'kind':'internal','segment':8,'offset':0},
                                      'sites':[0x1234]}]
        rows=direct_data_bindings(card,{'segments':segments},{'segments':segments})
        far=next(r for r in rows if r.get('observed_selector_offset')==0x1234)
        self.assertIsNone(far['addressed_segment'])
        self.assertEqual(far['possible_addressed_segment'],8)
        self.assertEqual(far['possible_mapsym_names'],['_Dx8'])


if __name__=='__main__': unittest.main()
