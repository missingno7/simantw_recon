"""Evidence-driven reconstruction rules must reach the packets they cover."""
import sys
import json
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from reconstruction_rules import relevant_rules, triggers


class ReconstructionRuleTriggerTests(unittest.TestCase):
    def card(self):
        return {'symbol': '_TryMoveDirB', 'disassembly': [], 'calls': [], 'segment': 6}

    def binding(self, name, slot=50002, segment=8):
        return {'exact_mapsym_names': [name], 'selector_slot': slot,
                'addressed_segment': segment}

    def test_shared_segment8_ant_list_slot_attaches_narrow_rule(self):
        packet = {'direct_data_bindings': [
            self.binding('_BlistX'), self.binding('_BlistY'),
            self.binding('_BlistT'),
        ], 'unit_context': {'id': 'simant1:2D4E'}}
        self.assertIn('ant_list_shared_dx8', triggers(self.card(), packet))
        rules = relevant_rules(self.card(), packet)
        self.assertTrue(any(r['id'] == 'ant-list-fields-shared-selector' for r in rules))
        self.assertFalse(any('one Dx8 array' in r['rule'] and 'not that' not in r['rule'] for r in rules))
        self.assertFalse(any(r['id'] == 'based-list-fields-simant1-0000' for r in rules))

    def test_ant_list_rule_requires_shared_segment8_slot_evidence(self):
        unrelated_segment = {'direct_data_bindings': [
            self.binding('_BlistX', segment=9), self.binding('_BlistT', segment=9),
        ]}
        separate_slots = {'direct_data_bindings': [
            self.binding('_BlistX', slot=50002), self.binding('_BlistT', slot=50004),
        ]}
        lone_name = {'direct_data_bindings': [self.binding('_BlistX')]}
        for packet in (unrelated_segment, separate_slots, lone_name):
            with self.subTest(packet=packet):
                self.assertNotIn('ant_list_shared_dx8', triggers(self.card(), packet))

    def test_unit_specific_rule_is_not_sent_outside_its_context(self):
        card = self.card()
        binding = self.binding('_AlistX')
        elsewhere = {'unit_context': {'id': 'simant1:2D4E'},
                     'direct_data_bindings': [binding]}
        matching = {'unit_context': {'id': 'simant1:0000'},
                    'direct_data_bindings': [binding]}
        self.assertFalse(any(r['id'] == 'based-list-fields-simant1-0000'
                             for r in relevant_rules(card, elsewhere)))
        self.assertTrue(any(r['id'] == 'based-list-fields-simant1-0000'
                            for r in relevant_rules(card, matching)))

    def test_inline_hole_flag_rule_reaches_matching_simant1_packets(self):
        root = Path(__file__).resolve().parents[1]
        for job in ('DoToAlarm-eebd22beab', 'DoAttackAnt-80be755651',
                    'DoRecruitAnt-f80269cf27'):
            packet = json.loads((root / 'evidence' / 'recovery' / 'workflow' /
                                 'jobs' / job / 'factory-packet.json').read_text())
            card = {'symbol': packet['symbol'], 'disassembly': packet['disassembly'],
                    'calls': packet['calls'], 'segment': packet['segment']}
            with self.subTest(symbol=packet['symbol']):
                self.assertIn('inline_hole_flag_join', triggers(card, packet))
                self.assertTrue(any(r['id'] == 'inline-hole-flag-join-simant1-0000'
                                    for r in relevant_rules(card, packet)))

    def test_inline_hole_flag_rule_requires_calls_and_cx_flag_sequence(self):
        rows = [
            {'mnemonic': 'xor', 'operands': 'cx, cx'},
            {'mnemonic': 'mov', 'operands': 'cx, 1'},
            {'mnemonic': 'or', 'operands': 'cx, cx'},
        ]
        card = {'symbol': '_Other', 'disassembly': rows, 'calls': [], 'segment': 6}
        calls = {'unit_context': {'id': 'simant1:0000'}}
        self.assertNotIn('inline_hole_flag_join', triggers(card, calls))
        card['disassembly'] = rows[:2]
        calls['calls'] = [{'names': ['_IsValidA']}, {'names': ['_GoInNest']}]
        self.assertNotIn('inline_hole_flag_join', triggers(card, calls))

    def test_multimedia_state_rule_requires_sound_context_and_far_access(self):
        card = {'symbol': '_snd_IsSongDone', 'segment': 2,
                'disassembly': [{'mnemonic': 'mov', 'operands': 'es, word ptr [0xbf78]'}],
                'calls': []}
        sound = {'unit_context': {'id': 'gr:7712'}}
        elsewhere = {'unit_context': {'id': 'gr:514C'}}
        rule_id = 'multimedia-state-gr-7712'
        self.assertTrue(any(r['id'] == rule_id for r in relevant_rules(card, sound)))
        self.assertFalse(any(r['id'] == rule_id for r in relevant_rules(card, elsewhere)))
        card['disassembly'] = []
        self.assertFalse(any(r['id'] == rule_id for r in relevant_rules(card, sound)))

if __name__ == '__main__':
    unittest.main()
