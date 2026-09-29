"""Sweep / triage / attempt-history / ownership orchestration: routing metadata that fails closed."""
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
SCRATCH = ROOT / 'build/test-orchestration-tmp'
SCRATCH.mkdir(parents=True, exist_ok=True)

import attempts
import drafts
import shared_state
import sweep
import triage
import unit_owner
from common import FormatError, write_json


def comparison(matches, total, cand_bytes, target_bytes, rows=None, result='NO_COMPLETE_MATCH'):
    return dict(result=result, diagnostic=dict(opcode_matches=matches, opcode_total=total, candidate_bytes=cand_bytes,
                                               target_bytes=target_bytes, aligned_asm=rows or [dict(differences=['register_allocation'],
                                                                                                     target='mov ax, bx', candidate='mov ax, cx')],
                                               instruction_layout_match=False, register_only_differences=1,
                                               branch_target_differences=0, stack_local_differences=0))


class FamilyVocabularyTests(unittest.TestCase):
    def test_declared_family_normalises_and_wins_over_inference(self):
        self.assertEqual(attempts.normalize_family('cse'), 'CSE_SUBEXPRESSION')
        self.assertEqual(attempts.normalize_family('loop structure'), 'LOOP_STRUCTURE')
        self.assertIsNone(attempts.normalize_family('mapped-entry-and-register-residue'))
        fams, source = attempts.families_from(['register hint'], 'branch polarity loop')
        self.assertEqual((fams, source), (['REGISTER_HINT'], 'declared'))

    def test_free_text_is_inferred_and_marked(self):
        fams, source = attempts.families_from(['round 3: local declaration order and register keyword'], None)
        self.assertEqual(source, 'inferred')
        self.assertIn('LOCAL_ORDER', fams)
        self.assertIn('REGISTER_HINT', fams)
        self.assertEqual(attempts.families_from(None, None), (['UNSPECIFIED'], 'none'))

    def test_record_refuses_unknown_family_or_outcome(self):
        with tempfile.TemporaryDirectory(dir=SCRATCH) as td:
            with self.assertRaises(FormatError):
                attempts.record('_Toy', dict(families=['MADE_UP']), root=td)
            with self.assertRaises(FormatError):
                attempts.record('_Toy', dict(families=['TYPE'], outcome='GREAT'), root=td)


class OutcomeTests(unittest.TestCase):
    def test_outcome_classes(self):
        before = dict(strict=False, body_exact=False, row=10, opcodes=50)
        self.assertEqual(attempts.outcome_of(before, dict(strict=True, opcodes=60)), 'EXACT')
        self.assertEqual(attempts.outcome_of(before, dict(body_exact=True, opcodes=60, row=61)), 'BODY_EXACT')
        self.assertEqual(attempts.outcome_of(before, dict(opcodes=52, row=12)), 'IMPROVED')
        self.assertEqual(attempts.outcome_of(before, dict(opcodes=40, row=3)), 'NEUTRAL')
        self.assertEqual(attempts.outcome_of(before, dict(opcodes=40, row=3), reevaluation=True), 'REGRESSED')
        self.assertEqual(attempts.outcome_of(before, dict(opcodes=50, row=10), same_output=True), 'NO_OP')
        self.assertEqual(attempts.outcome_of(before, None), 'COMPILE_FAILED')


class SummaryTests(unittest.TestCase):
    def test_exhausted_family_goes_stale_after_shared_change(self):
        fp = dict(shared_state.fingerprint())
        with tempfile.TemporaryDirectory(dir=SCRATCH) as td:
            for i in range(3):
                attempts.record('_Toy', dict(families=['REGISTER_HINT'], family_source='declared', candidates=2, outcome='NEUTRAL',
                                             before=dict(opcodes=10), after=dict(opcodes=9), state=fp), root=td)
            attempts.record('_Toy', dict(families=['LOOP_STRUCTURE'], family_source='declared', outcome='IMPROVED',
                                         before=dict(opcodes=10), after=dict(opcodes=14), state=fp), root=td)
            s = attempts.summary('_Toy', root=td, current_fp=fp)
            self.assertEqual(s['REGISTER_HINT']['verdict'], 'EXHAUSTED')
            self.assertEqual(s['LOOP_STRUCTURE']['verdict'], 'PRODUCTIVE')
            self.assertEqual(s['LOOP_STRUCTURE']['best_gain'], 4)
            self.assertTrue(attempts.advice('_Toy', ['REGISTER_HINT'], fam_summary=s))
            self.assertEqual(attempts.advice('_Toy', ['REGISTER_HINT'], why_repeat='new MSC7-R0 fact', fam_summary=s), [])
            changed = dict(fp, facts='0' * 16)
            s2 = attempts.summary('_Toy', root=td, current_fp=changed)
            self.assertEqual(s2['REGISTER_HINT']['stale_since'], ['facts'])
            self.assertEqual(attempts.advice('_Toy', ['REGISTER_HINT'], fam_summary=s2), [])

    def test_inferred_rows_weigh_half(self):
        with tempfile.TemporaryDirectory(dir=SCRATCH) as td:
            for i in range(4):
                attempts.record('_Toy', dict(families=['TYPE'], family_source='inferred', outcome='NEUTRAL'), root=td)
            self.assertEqual(attempts.summary('_Toy', root=td)['TYPE']['verdict'], 'TRIED')
            for i in range(2):
                attempts.record('_Toy', dict(families=['TYPE'], family_source='inferred', outcome='NEUTRAL'), root=td)
            self.assertEqual(attempts.summary('_Toy', root=td)['TYPE']['verdict'], 'EXHAUSTED')


class SharedStateTests(unittest.TestCase):
    def test_fingerprint_ignores_line_endings_and_names_changed_components(self):
        with tempfile.TemporaryDirectory(dir=SCRATCH) as td:
            root = Path(td)
            (root / 'layout').mkdir()
            (root / 'layout/compiler-profiles.json').write_bytes(b'{"a": 1}\n')
            a = shared_state.fingerprint(root)
            (root / 'layout/compiler-profiles.json').write_bytes(b'{"a": 1}\r\n')
            self.assertEqual(shared_state.fingerprint(root), a)
            (root / 'layout/compiler-profiles.json').write_bytes(b'{"a": 2}\n')
            b = shared_state.fingerprint(root)
            self.assertEqual(shared_state.changed(a, b), ['profiles'])
            self.assertNotEqual(shared_state.recompile_key(a), shared_state.recompile_key(b))
            self.assertIn('profiles', shared_state.SWEEP_TRIGGERS)


class DraftRefreshTests(unittest.TestCase):
    def setUp(self):
        self.td = tempfile.TemporaryDirectory(dir=SCRATCH)
        base = Path(self.td.name)
        self.patches = [mock.patch.object(drafts, 'DRAFTS', base / 'drafts'), mock.patch.object(drafts, 'INDEX', base / 'drafts/index.json'),
                        mock.patch.object(drafts, 'LOCK', base / 'drafts.lock'), mock.patch.object(drafts, 'ROOT', base)]
        for p in self.patches:
            p.start()
        (base / 'drafts').mkdir()
        self.source = base / 'a.c'
        self.source.write_text('int f(void) { return 1; }\n')

    def tearDown(self):
        for p in self.patches:
            p.stop()
        self.td.cleanup()

    def test_refresh_rescored_keeps_history_and_drops_stub_frontier(self):
        from common import identity
        digest = identity(self.source)['sha256']
        write_json(drafts.INDEX, {'_Toy': dict(
            best=dict(source='drafts/Toy/x.c', sha256=digest, key=[False, False, 170, -6], result='NO_COMPLETE_MATCH', flags=['/Oelw'],
                      opcode_matches=170, opcode_total=186),
            frontier=dict(source='drafts/Toy/y.c', sha256='stub', key=[False, False, 1, 9], opcode_matches=9, opcode_total=186, flags=['/Oelw']))})
        changed = drafts.refresh('_Toy', digest, comparison(157, 186, 480, 484), 'sweep', ['/Oegilw'])
        self.assertEqual(changed, ['best'])
        best = drafts.load()['_Toy']['best']
        self.assertEqual(best['opcode_matches'], 157)
        self.assertEqual(best['flags'], ['/Oegilw'])
        self.assertEqual(best['rescored'][-1]['key'], [False, False, 170, -6])
        changed = drafts.refresh('_Toy', 'stub', comparison(9, 186, 40, 484), 'sweep', ['/Oegilw'])
        self.assertEqual(changed, ['frontier_dropped'])
        self.assertNotIn('frontier', drafts.load()['_Toy'])
        self.assertIn('frontier_dropped', drafts.load()['_Toy'])

    def test_store_refuses_incomplete_frontier(self):
        write_json(drafts.INDEX, {'_Toy': dict(best=dict(source='drafts/Toy/x.c', sha256='x', key=[False, False, 150, 0], opcode_matches=150))})
        drafts.store('_Toy', self.source, comparison(20, 160, 60, 500), 'o', ['/Oelw'])
        self.assertNotIn('frontier', drafts.load()['_Toy'])
        self.assertTrue(drafts.plausible_frontier(80, dict(opcode_matches=150)))
        self.assertFalse(drafts.plausible_frontier(20, dict(opcode_matches=150)))


class SweepClassificationTests(unittest.TestCase):
    def ev(self, rank, frontier=None, strict=False, body=False, kind='best'):
        return dict(eval=dict(rank=rank, frontier_rank=frontier, strict=strict, body_exact=body), origin_kind=kind)

    def test_code_level_outcomes(self):
        before = dict(key=[False, False, 100, -4])
        front = dict(key=[False, False, 30, 100])
        self.assertEqual(sweep.classify_change(before, front, [self.ev([False, False, 100, -4], [False, False, 30, 100], strict=True)]), 'NEWLY_EXACT')
        self.assertEqual(sweep.classify_change(before, front, [self.ev([False, True, 100, 0], [False, True, 101, 100], body=True)]), 'NEWLY_BODY_EXACT')
        self.assertEqual(sweep.classify_change(before, front, [self.ev([False, False, 102, 0])]), 'IMPROVED')
        self.assertEqual(sweep.classify_change(before, front, [self.ev([False, False, 90, -4])]), 'REGRESSED')
        self.assertEqual(sweep.classify_change(before, front, [self.ev([False, False, 100, -4], [False, False, 0, 100])]), 'RESCORED')
        self.assertEqual(sweep.classify_change(before, front, [self.ev([False, False, 100, -4], [False, False, 30, 100])]), 'UNCHANGED')
        self.assertEqual(sweep.classify_change(before, front, [dict(eval=dict(rank=None), origin_kind='best')]), 'COMPILE_FAILED')

    def test_change_cause_names_profile_change(self):
        causes = sweep.change_cause(dict(flags=['/AL', '/G2', '/Gs', '/Oelw', '/NTX']), [self.ev([False, False, 1, 0])], ['/AL', '/G2', '/Gs', '/Oegilw', '/NTX'])
        self.assertTrue(causes[0].startswith('PROFILE_CHANGED /Oelw -> /Oegilw'))

    def test_admit_requires_a_fresh_gate_route(self):
        with mock.patch.object(sys, 'argv', ['sweep.py', '--admit']):
            with self.assertRaises(FormatError):
                sweep.main()


class TriageClassificationTests(unittest.TestCase):
    def ev(self, m, t, cb, tb, **kw):
        return dict(opcode_matches=m, opcode_total=t, candidate_bytes=cb, target_bytes=tb, **kw)

    def test_blocker_classes(self):
        self.assertEqual(triage.classify_blocker(self.ev(10, 10, 30, 30, strict=True), {}), 'EXACT_PENDING')
        self.assertEqual(triage.classify_blocker(self.ev(10, 10, 30, 30, body_exact=True), {}), 'PLACEMENT')
        self.assertEqual(triage.classify_blocker(self.ev(90, 100, 300, 300), {'kind': 'EXPRESSION_SHAPE'}, 'DIVERGED'), 'SEMANTICS')
        self.assertEqual(triage.classify_blocker(self.ev(100, 100, 300, 300), {'kind': 'RELOCATION_ONLY'}), 'BINDING')
        self.assertEqual(triage.classify_blocker(self.ev(40, 100, 200, 300), {'kind': 'WRONG_REGISTER'}), 'AUTHORING')
        self.assertEqual(triage.classify_blocker(self.ev(100, 100, 300, 300, register_only_differences=3), {'kind': 'WRONG_REGISTER'}), 'REGISTER_ALLOCATION')
        self.assertEqual(triage.classify_blocker(self.ev(100, 100, 300, 300, stack_local_differences=3), {'kind': 'WRONG_STACK_SLOT'}), 'HOME_ORDER')
        self.assertEqual(triage.classify_blocker(self.ev(95, 100, 300, 302), {'kind': 'FRAME_SIZE'}), 'FRAME_SIZE')
        self.assertEqual(triage.classify_blocker(self.ev(95, 100, 300, 302), {'kind': 'EXPRESSION_SHAPE'}, typedb_better=True), 'DECLARATION_TYPE')
        self.assertEqual(triage.classify_blocker(self.ev(95, 100, 300, 302), {'kind': 'CFG_DESTINATION'}), 'CFG_STRUCTURE')

    def test_lane_routes_exhausted_allocation_tail_to_background_and_respects_parking(self):
        fam = {f: dict(verdict='EXHAUSTED', stale_since=None) for f in triage.PLAYBOOK['REGISTER_ALLOCATION'][0]}
        ev = self.ev(100, 100, 300, 300)
        self.assertEqual(triage.choose_lane('REGISTER_ALLOCATION', fam, 'NOT_PARKED', ev)[0], 'BACKGROUND_PERMUTER')
        self.assertEqual(triage.choose_lane('REGISTER_ALLOCATION', {}, 'NOT_PARKED', ev)[0], 'TAIL_INTERACTIVE')
        self.assertEqual(triage.choose_lane('REGISTER_ALLOCATION', {}, 'PARKED', ev)[0], 'PARKED')
        self.assertEqual(triage.choose_lane('PLACEMENT', {}, 'PARKED', ev)[0], 'COMPOSE')
        stale = dict(fam, CSE_SUBEXPRESSION=dict(verdict='EXHAUSTED', stale_since=['facts']))
        lane, ordered, _, _ = triage.choose_lane('REGISTER_ALLOCATION', stale, 'NOT_PARKED', ev)
        self.assertEqual((lane, ordered[0]), ('TAIL_INTERACTIVE', 'CSE_SUBEXPRESSION'))

    def test_allocation_classes_lead_with_subexpressions_not_declaration_order(self):
        families, avoid, _, _ = triage.PLAYBOOK['REGISTER_ALLOCATION']
        self.assertEqual(families[0], 'CSE_SUBEXPRESSION')
        self.assertIn('DECLARATION_ORDER', avoid)
        self.assertIn('REGISTER_HINT', avoid)
        self.assertIn('SUBEXPRESSIONS', triage.ALLOCATION_ADVICE)

    def test_fact_register_parses_statuses(self):
        facts = triage.facts()
        self.assertIn('MSC7-R0', facts)
        self.assertEqual(facts['MSC7-F7'][0], 'FALSIFIED')


class UnitOwnerTests(unittest.TestCase):
    def test_single_owner_with_lease_and_audit_history(self):
        with tempfile.TemporaryDirectory(dir=SCRATCH) as td:
            path = Path(td) / 'owners.json'
            with mock.patch.object(unit_owner, 'LOCK', Path(td) / 'owners.lock'):
                unit_owner.claim('simant:6A38', 'w1', 'compose YellowBirth', path=path)
                with self.assertRaises(FormatError):
                    unit_owner.claim('simant:6A38', 'w2', 'also', path=path)
                with self.assertRaises(FormatError):
                    unit_owner.require('simant:6A38', 'w2', path=path)
                self.assertEqual(unit_owner.require('simant:6A38', 'w1', path=path), 'w1')
                with self.assertRaises(FormatError):
                    unit_owner.release('simant:6A38', 'w2', path=path)
                unit_owner.release('simant:6A38', 'w1', path=path)
                self.assertIsNone(unit_owner.owner_of('simant:6A38', path=path))
                unit_owner.claim('simant:6A38', 'w2', 'expired', hours=-1, path=path)
                self.assertIsNone(unit_owner.owner_of('simant:6A38', path=path))
                history = json.loads(path.read_text())['history']
                self.assertEqual([h['action'] for h in history], ['claim', 'release', 'claim'])


class PermuterQueueTests(unittest.TestCase):
    def test_mutation_selection_drops_falsified_and_no_effect_families(self):
        import permuter_queue
        muts, dead = permuter_queue.select_mutations({'LOOP_STRUCTURE': dict(verdict='NO_EFFECT', stale_since=None),
                                                      'CFG_STRUCTURE': dict(verdict='NO_EFFECT', stale_since=['facts'])})
        self.assertNotIn('register_toggle', muts)
        self.assertNotIn('for_to_while', muts)
        self.assertIn('invert_if', muts)
        self.assertIn('inline_temp', muts)
        self.assertEqual(dead, ['DECLARATION_ORDER', 'LOOP_STRUCTURE', 'REGISTER_HINT'])
        for name in permuter_queue.mutation_names():
            self.assertIn(permuter_queue.MUTATION_FAMILY.get(name, 'OTHER'), attempts.FAMILIES)


class FleetPlanTests(unittest.TestCase):
    def row(self, symbol, lane, obj, value, cls='AUTHORING', families=('SEMANTICS',)):
        return dict(symbol=symbol, lane=lane, value=value, blocker_class=cls, unit=dict(component=obj), next_families=list(families),
                    current=dict(opcodes='1/2'), size=100)

    def test_tail_needs_untried_family_and_objects_stay_with_one_worker(self):
        import fleet_plan
        rows = [self.row('_A', 'AUTHORING', 'o:1', 50), self.row('_B', 'AUTHORING', 'o:1', 10), self.row('_C', 'AUTHORING', 'o:2', 40),
                self.row('_T', 'TAIL_INTERACTIVE', 'o:3', 30, 'HOME_ORDER', ()), self.row('_U', 'TAIL_INTERACTIVE', 'o:4', 20, 'HOME_ORDER'),
                self.row('_P', 'BACKGROUND_PERMUTER', 'o:5', 90, 'REGISTER_ALLOCATION')]
        plans = fleet_plan.assign(rows, 'AUTHORING', 2, 3, 't', set())
        owners = {obj: p['name'] for p in plans for obj in p['objects']}
        self.assertEqual(len(owners), 2)
        self.assertEqual({t['symbol'] for p in plans if 'o:1' in p['objects'] for t in p['targets']} >= {'_A', '_B'}, True)
        tails = fleet_plan.assign(rows, 'TAIL', 1, 3, 't', set())
        self.assertEqual([t['symbol'] for p in tails for t in p['targets']], ['_U'])
        self.assertFalse(any(t['symbol'] == '_P' for p in plans + tails for t in p['targets']))


if __name__ == '__main__':
    unittest.main()
