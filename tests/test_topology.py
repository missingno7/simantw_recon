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
        path=ROOT/'evidence/recovery/workflow/jobs/DialogWait-50782e4ed5/attempt01/results.json'
        return json.loads(path.read_text())['results'][0]['comparison']

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


    def test_workflow_stops_after_first_binding_only_attempt(self):
        from unittest.mock import patch
        import recovery_workflow as wf
        job=dict(id='Test-1234567890',symbol='_Test',status='OPEN',attempts=[])
        result=dict(results=[dict(candidate=0,comparison=self.baseline())],
                    completed_candidates=1,candidates=1,cache={},exact_candidates=[])
        with patch.object(wf,'checked_job',return_value=(ROOT/'build/topology-test',job)), \
             patch.object(wf,'read_json',return_value={}), \
             patch.object(wf,'check_submission'), \
             patch.object(wf,'variants',return_value=iter([('source',{})])), \
             patch.object(wf,'experiment_digest',return_value='new-source'), \
             patch.object(wf,'atomic_json'),patch.object(wf,'run',return_value=result), \
             patch.object(wf,'refresh'),patch.object(wf,'queue'):
            outcome=wf.run_attempt(job['id'])
        self.assertEqual(outcome['status'],'ESCALATED')
        self.assertEqual(job['evidence_state'],'BODY_MATCHED_BINDING_BLOCKED')
        self.assertEqual(len(job['attempts']),1)



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
