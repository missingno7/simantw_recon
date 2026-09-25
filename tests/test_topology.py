"""Routing must stop wasted work without granting or broadening proof."""
import copy
import json
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from topology_diagnostics import classify
from common import ROOT


class TopologyRoutingTests(unittest.TestCase):
    def baseline(self):
        path=ROOT/'tests/fixtures/DialogWait-attempt01.json'
        return json.loads(path.read_text())['comparison']

    def test_real_historical_binding_failure_routes_without_credit(self):
        c=self.baseline();before=copy.deepcopy(c);r=classify(c)
        self.assertEqual(r['state'],'BODY_MATCHED_BINDING_BLOCKED')
        self.assertEqual(r['recovery_credit'],0)
        self.assertEqual(c,before)
        self.assertEqual(c['result'],'NO_COMPLETE_MATCH')

    def test_unknown_cfg_and_frame_or_register_changes_do_not_route(self):
        for key,value in [('cfg_shape_match',None),('instruction_layout_match',False),
                          ('register_only_differences',1),('stack_local_differences',1),
                          ('branch_target_differences',1),('extent_known',False)]:
            with self.subTest(key=key):
                c=self.baseline();c['diagnostic'][key]=value
                self.assertIsNone(classify(c))

    def test_uncovered_literal_byte_is_not_a_topology_failure(self):
        c=self.baseline();s=c['contributions'][0]
        s['divergences'].append(0);s['literal_equal']-=1
        self.assertIsNone(classify(c))

    def test_truncated_divergences_are_not_accepted(self):
        c=self.baseline();c['contributions'][0]['literal_equal']-=1
        self.assertIsNone(classify(c))

    def test_wrong_call_and_selector_bindings_are_not_body_solved(self):
        for kind in (2,3):
            c=self.baseline()
            f=next(f for f in c['contributions'][0]['fixups'] if not f['equal'])
            f['omf']['location_type']=kind
            self.assertIsNone(classify(c))
        c=self.baseline()
        next(r for r in c['diagnostic']['aligned_asm'] if r['differences'])['target']='lcall unknown'
        self.assertIsNone(classify(c))

    def test_strict_success_belongs_only_to_existing_admission(self):
        c=self.baseline();c['result']='STRONGLY_SUPPORTED_MEMBER'
        self.assertIsNone(classify(c))


    def test_packet_names_map_operand_without_guessing_private_objects(self):
        from topology_context import direct_data_bindings
        symbols=dict(segments=[{}]*9+[dict(symbols=[dict(offset=0x28e8,name='_MapA')])])
        image=dict(segments=[{}]*9+[dict(relocations=[dict(source_type=2,sites=[0xbf78],target=dict(kind='internal',segment=8,offset=0))])])
        card=dict(disassembly=[dict(bytes='8887e828',offset=0),dict(bytes='8e0678bf',offset=4),dict(bytes='8b46fe',offset=8)])
        rows=direct_data_bindings(card,symbols,image)
        self.assertEqual(len(rows),2)
        self.assertEqual(rows[0]['exact_mapsym_names'],['_MapA'])
        self.assertEqual(rows[1]['exact_mapsym_names'],[])
        self.assertEqual(rows[1]['selector_loader_target']['segment'],8)
        self.assertIn('assumes',rows[0]['frame_assumption'])


if __name__=='__main__':unittest.main()
