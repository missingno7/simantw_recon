"""Parking records remain diagnostic metadata and reopen with an auditable reason."""
import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
TEST_SCRATCH = ROOT / 'build/test-parking-tmp'
TEST_SCRATCH.mkdir(parents=True, exist_ok=True)

import context
import parking
from common import FormatError, write_json


def toy_repository(root):
    (root / 'evidence/recovery/drafts').mkdir(parents=True)
    (root / 'evidence/disassembly').mkdir(parents=True)
    (root / 'src').mkdir(parents=True)
    (root / 'build/search/Toy').mkdir(parents=True)
    (root / 'layout').mkdir(parents=True)
    rows = [dict(differences=['register_allocation'], target='mov ax, bx', candidate='mov ax, cx')]
    comparison = dict(result='NO_COMPLETE_MATCH', diagnostic=dict(
        opcode_matches=8, opcode_total=12, candidate_bytes=20, target_bytes=22, aligned_asm=rows))
    result = dict(results=[dict(candidate=0, comparison=comparison)])
    report = root / 'build/search/Toy/frontier.json'
    write_json(report, result)
    frontier_time = '2026-09-29T10:00:00+00:00'
    entry = dict(frontier=dict(source='evidence/recovery/drafts/Toy/frontier.c',
                               origin='build/search/Toy/frontier.json', candidate=0,
                               key=[False, False, 0, 8], first_divergence_row=0,
                               opcode_matches=8, opcode_total=12, recorded=frontier_time),
                 notes=[])
    write_json(root / 'evidence/recovery/drafts/index.json', {'_Toy': entry})
    (root / 'evidence/disassembly/cards.jsonl').write_text(json.dumps(dict(symbol='_Toy', ownership='GAME')) + '\n', encoding='utf-8')
    write_json(root / 'src/recovery.json', {'targets': {}})
    session_report = root / 'build/search/Toy/session.json'
    write_json(session_report, result)
    sessions = [dict(time='20260929T100100-1', report='build/search/Toy/session.json'),
                dict(time='20260929T100200-2', report='build/search/Toy/session.json')]
    (root / 'build/search/Toy/history.jsonl').write_text(''.join(json.dumps(s) + '\n' for s in sessions), encoding='utf-8')
    return entry


class ParkingTests(unittest.TestCase):
    def test_park_reopen_round_trip_keeps_reason(self):
        with tempfile.TemporaryDirectory(dir=TEST_SCRATCH) as td:
            root = Path(td)
            toy_repository(root)
            record = parking.park_symbol('_Toy', 'REGISTER_ALLOCATION', 'Target keeps BX while draft selects CX.', root=root)
            self.assertEqual(record['blocker_class'], 'REGISTER_ALLOCATION')
            self.assertEqual(record['residue']['first_divergence_row'], 0)
            self.assertEqual(record['frontier']['opcodes'], '8/12')
            outcome = parking.reopen(symbol='_Toy', because='New MSC7 register allocation probe.', root=root)
            self.assertEqual(outcome['reopened'], ['_Toy'])
            state = parking.status('_Toy', root=root)
            self.assertEqual(state['status'], 'REOPENED')
            self.assertIn('New MSC7 register allocation probe.', state['record']['reopen_history'][0]['because'])

    def test_park_refuses_without_stagnation_evidence(self):
        with tempfile.TemporaryDirectory(dir=TEST_SCRATCH) as td:
            root = Path(td)
            toy_repository(root)
            (root / 'build/search/Toy/history.jsonl').write_text('', encoding='utf-8')
            with self.assertRaises(FormatError):
                parking.park_symbol('_Toy', 'REGISTER_ALLOCATION', 'No sessions or notes support this park.', root=root)
            self.assertFalse((root / 'layout/parking.json').exists())

    def test_class_reopen_reopens_every_matching_function_only(self):
        with tempfile.TemporaryDirectory(dir=TEST_SCRATCH) as td:
            root = Path(td)
            parking.save_parking({
                '_A': dict(blocker_class='REGISTER_ALLOCATION', active=True),
                '_B': dict(blocker_class='REGISTER_ALLOCATION', active=True),
                '_C': dict(blocker_class='HOME_ORDER', active=True),
            }, root)
            result = parking.reopen(blocker_class='REGISTER_ALLOCATION', because='New compiler tool probe.', root=root)
            self.assertEqual(set(result['reopened']), {'_A', '_B'})
            records = parking.load_parking(root)
            self.assertFalse(parking.is_active(records['_A']))
            self.assertTrue(parking.is_active(records['_C']))

    def test_context_exposes_parked_record(self):
        record = dict(blocker_class='FRAME_SIZE', active=True, parked='2026-09-29')
        result = context.parking_info('_Toy', {'_Toy': record})
        self.assertEqual(result['status'], 'PARKED')
        self.assertIs(result['record'], record)

    def test_candidate_rule_accepts_two_stagnant_sessions(self):
        with tempfile.TemporaryDirectory(dir=TEST_SCRATCH) as td:
            root = Path(td)
            toy_repository(root)
            result = parking.candidates(root, note_rounds=10)
            self.assertIn('_Toy', result['candidates'])
            proposal = result['candidates']['_Toy']
            self.assertEqual(proposal['blocker_class'], 'REGISTER_ALLOCATION')
            self.assertEqual(proposal['residue']['target'], 'mov ax, bx')
            self.assertEqual(proposal['evidence']['stagnation']['basis'], 'last_two_sessions_no_frontier_improvement')

    def test_candidate_note_threshold_is_since_frontier(self):
        with tempfile.TemporaryDirectory(dir=TEST_SCRATCH) as td:
            root = Path(td)
            entry = toy_repository(root)
            entry['notes'] = [dict(text='round %d' % i, recorded='2026-09-29T10:%02d:00+00:00' % (i + 1)) for i in range(10)]
            write_json(root / 'evidence/recovery/drafts/index.json', {'_Toy': entry})
            (root / 'build/search/Toy/history.jsonl').write_text('', encoding='utf-8')
            result = parking.candidates(root, note_rounds=10)
            self.assertIn('_Toy', result['candidates'])
            self.assertEqual(result['candidates']['_Toy']['evidence']['stagnation']['basis'], 'note_rounds_since_frontier')

    def test_search_session_ids_sort_by_time_not_pid(self):
        earlier = parking._parse_time('20260929T070307-136728')
        later = parking._parse_time('20260929T070354-167788')
        self.assertLess(earlier, later)

    def test_fleet_planner_excludes_only_active_parked_rows(self):
        path = ROOT / 'build/supervisor/fleet2_plan.py'
        if not path.exists():
            self.skipTest('supervisor fleet planner is a local build/ script')
        spec = importlib.util.spec_from_file_location('parking_fleet2_plan', path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        rows = [dict(symbol='_A'), dict(symbol='_B')]
        remaining, excluded = module.split_parked(rows, {
            '_A': dict(blocker_class='FRAME_SIZE', active=True),
            '_B': dict(blocker_class='HOME_ORDER', active=False),
        })
        self.assertEqual([r['symbol'] for r in remaining], ['_B'])
        self.assertEqual([r['symbol'] for r in excluded], ['_A'])


if __name__ == '__main__':
    unittest.main()
