import dataclasses
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import emu_diff


class EmulatorDiffTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.fixture = emu_diff.Fixture.load()

    def test_ne_relocation_maps_same_segment_selector(self):
        fx = self.fixture
        side, _ = emu_diff._target_side(fx, '_RandTurn', None)
        # The function's far call to _SRand8 has a selector word loader fixup.
        call = next(i for i in emu_diff._decoder().disasm(side.code, side.function_offset)
                    if i.mnemonic == 'lcall')
        self.assertEqual(call.bytes[0], 0x9a)
        self.assertEqual(int.from_bytes(call.bytes[3:5], 'little'), emu_diff._selector(5))

    def test_omf_external_fixup_maps_by_mapsym_name(self):
        fx = self.fixture
        module = dict(externals=[dict(name='_TurnTab')], groups=[], publics=[])
        fixup = dict(target_method=2, target_index=1)
        selector, offset, name = emu_diff._resolve_omf_target(fx, module, fixup, {})
        self.assertEqual(name, '_TurnTab')
        self.assertEqual(selector, emu_diff._selector(fx.symbol_locations['_TurnTab'][0]))
        self.assertEqual(offset, fx.symbol_locations['_TurnTab'][1])

    def test_omf_group_relocation_uses_synthetic_dgroup_offset(self):
        fx = self.fixture
        module = dict(
            segments=[
                dict(index=1, name='CODE', **{'class': 'CODE'}, length=6, alignment=2, data_hex='000000000000'),
                dict(index=2, name='CONST', **{'class': 'CONST'}, length=2, alignment=2, data_hex='0000'),
            ],
            groups=[dict(index=1, name='DGROUP', segments=[2])], externals=[], publics=[], fixups=[
                dict(segment=1, offset=2, width=2, location_type=1, self_relative=False,
                     frame_method=1, frame_index=1, target_method=0, target_index=2, displacement=0),
            ],
        )
        patched, _, _ = emu_diff._patch_omf(module, fx, 1, 6, 0x200, 0, {})
        self.assertEqual(int.from_bytes(patched[1][2:4], 'little'), 0xE000)

    def test_target_and_candidate_call_stub_records_name_and_scripted_result(self):
        fx = self.fixture
        side, _ = emu_diff._target_side(fx, '_RandTurn', None)
        run = emu_diff._run_side(fx, side, [], {}, {'_SRand8': (0x1234, 0)}, 4, 10000, [])
        self.assertEqual(run['status'], 'OK')
        calls = [event for event in run['observables'] if event['kind'] == 'call']
        self.assertEqual(len(calls), 1)
        self.assertEqual(calls[0]['callee'], '_SRand8')
        self.assertEqual(calls[0]['result']['ax'], 0x1234)

    def test_equivalent_executed_pair_has_no_divergence(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        candidate = dataclasses.replace(target, name='candidate')
        left = emu_diff._run_side(fx, target, [], {}, {}, 81, 10000, [])
        right = emu_diff._run_side(fx, candidate, [], {}, {}, 81, 10000, [])
        self.assertEqual(left['status'], 'OK')
        self.assertEqual(right['status'], 'OK')
        self.assertIsNone(emu_diff._first_divergence(left, right))

    def test_divergent_executed_pair_reports_return_difference(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        changed = bytearray(target.code)
        changed[16:18] = b'\xb8\x01\x00'  # return 1 on the nonnegative path
        candidate = dataclasses.replace(target, name='candidate', code=bytes(changed), extent_size=len(changed))
        left = emu_diff._run_side(fx, target, [], {}, {}, 81, 10000, [])
        right = emu_diff._run_side(fx, candidate, [], {}, {}, 81, 10000, [])
        divergence = emu_diff._first_divergence(left, right)
        self.assertIsNotNone(divergence)
        self.assertEqual(divergence['target']['kind'], 'return')
        self.assertEqual(divergence['target']['ax'], 0)
        self.assertEqual(divergence['candidate']['ax'], 1)

    def test_runtime_helper_is_reported_unsupported(self):
        fx = self.fixture
        side, _ = emu_diff._target_side(fx, '_MyPow', None)
        params = [dict(name='b', pointer=False, words=2, byte=False, declaration='unsigned long'),
                  dict(name='n', pointer=False, words=2, byte=False, declaration='unsigned long')]
        run = emu_diff._run_side(fx, side, params, {'b': (3, 0), 'n': (3, 0)}, {}, 19, 10000, [])
        self.assertEqual(run['status'], 'UNSUPPORTED')
        self.assertIn('runtime helper', run['error'])

if __name__ == '__main__':
    unittest.main()
