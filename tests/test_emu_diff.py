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
        side, _ = emu_diff._target_side(fx, '_GPutStr', None)
        run = emu_diff._run_side(fx, side, [], {}, {'GDI!#1': (0x1234, 0)}, 4, 10000, [])
        self.assertEqual(run['status'], 'OK')
        calls = [event for event in run['observables'] if event['kind'] == 'call']
        self.assertTrue(calls)
        self.assertEqual(calls[0]['callee'], 'GDI!#1')
        self.assertTrue(calls[0]['import_call'])
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

    def test_return_comparison_uses_declared_abi_width(self):
        self.assertEqual(emu_diff._c_return_words('int far f(void) { return 0; }', '_f'), 1)
        self.assertEqual(emu_diff._c_return_words('unsigned long far f(void) { return 0; }', '_f'), 2)
        self.assertEqual(emu_diff._c_return_words('void far f(void) { return; }', '_f'), 0)
        self.assertEqual(emu_diff._c_return_words('void far * f(void) { return 0; }', '_f'), 2)
        self.assertEqual(emu_diff._c_return_words('HANDLE f(void) { return 0; }', '_f'), 2)
        target = dict(observables=[], return_value=dict(ax=1, dx=0),
                      return_instruction_offset=7, return_basic_block=4)
        candidate = dict(observables=[], return_value=dict(ax=1, dx=1),
                         return_instruction_offset=9, return_basic_block=4)
        self.assertIsNone(emu_diff._first_divergence(target, candidate, 1))
        self.assertEqual(emu_diff._first_divergence(target, candidate, 2)['target']['dx'], 0)

    def test_runtime_helper_executes_from_oracle_image(self):
        fx = self.fixture
        side, _ = emu_diff._target_side(fx, '_MyPow', None)
        params = [dict(name='b', pointer=False, words=2, byte=False, declaration='unsigned long'),
                  dict(name='n', pointer=False, words=2, byte=False, declaration='unsigned long')]
        run = emu_diff._run_side(fx, side, params, {'b': (3, 0), 'n': (3, 0)}, {}, 19, 10000, [])
        self.assertEqual(run['status'], 'OK')
        self.assertTrue(any(event['kind'] == 'call' and event['callee'].startswith('__aF')
                            and not event['import_call'] for event in run['observables']))

    def test_default_comparison_ignores_local_stack_frame_writes(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        local_store = bytes.fromhex('558bec c746fe0100 33c0 5dcb')
        candidate = dataclasses.replace(target, name='candidate', code=local_store,
                                        extent_size=len(local_store))
        normal = emu_diff._run_side(fx, candidate, [], {}, {}, 7, 10000, [])
        strict = emu_diff._run_side(fx, candidate, [], {}, {}, 7, 10000, [], strict=True)
        self.assertEqual(normal['status'], 'OK')
        self.assertFalse(normal['observables'])
        self.assertTrue(any(event['kind'] == 'write' and event['address']['segment'] == 'STACK'
                            for event in strict['observables']))

    def test_observable_writes_compare_final_state_without_order_noise(self):
        def write(address, value, offset):
            return dict(kind='write', linear_address=address, size=1, value=value,
                        instruction_offset=offset, basic_block=0)
        left = dict(observables=[write(0xA0100, 1, 3), write(0xA0101, 2, 4)],
                    return_value=dict(ax=0, dx=0), return_instruction_offset=5)
        right = dict(observables=[write(0xA0101, 2, 1), write(0xA0100, 1, 2)],
                     return_value=dict(ax=0, dx=0), return_instruction_offset=5)
        self.assertIsNone(emu_diff._first_divergence(left, right))
        right['observables'][0]['value'] = 3
        difference = emu_diff._first_divergence(left, right)
        self.assertEqual(difference['target_instruction_offset'], 4)
        self.assertEqual(difference['target_basic_block'], 0)

    def test_call_order_is_ignored_but_memory_view_is_compared(self):
        def call(name, offset, view):
            return dict(kind='call', callee=name, argument_words=[], argument_pointers=[],
                        result='executed-oracle-code', memory_view_sha256=view,
                        instruction_offset=offset, basic_block=0)
        left = dict(observables=[call('_A', 2, 'same'), call('_B', 4, 'same')],
                    return_value=dict(ax=0, dx=0), return_instruction_offset=5)
        right = dict(observables=[call('_B', 3, 'same'), call('_A', 1, 'same')],
                     return_value=dict(ax=0, dx=0), return_instruction_offset=5)
        self.assertIsNone(emu_diff._first_divergence(left, right))
        right['observables'][0]['memory_view_sha256'] = 'changed'
        self.assertIsNotNone(emu_diff._first_divergence(left, right))

    def test_one_sided_execution_fault_is_a_behavioral_divergence(self):
        target = dict(status='OK', error=None, return_instruction_offset=12, return_basic_block=8)
        candidate = dict(status='UNSUPPORTED', error='divide fault', return_instruction_offset=10,
                         return_basic_block=6)
        difference = emu_diff._execution_divergence(target, candidate)
        self.assertEqual(difference['target_instruction_offset'], 12)
        self.assertEqual(difference['target_basic_block'], 8)
        self.assertEqual(difference['candidate']['error'], 'divide fault')

    def test_unmapped_reads_use_deterministic_synthetic_pages(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        code = bytes.fromhex('b800f0 8ed8 bb3412 8a07 cb')
        candidate = dataclasses.replace(target, name='candidate', code=code, extent_size=len(code))
        left = emu_diff._run_side(fx, candidate, [], {}, {}, 42, 10000, [])
        right = emu_diff._run_side(fx, candidate, [], {}, {}, 42, 10000, [])
        self.assertEqual(left['status'], 'OK')
        self.assertTrue(left['synthesized_memory']['used'])
        self.assertEqual(left['synthesized_memory']['pages'], [0xF1000])
        self.assertEqual(left['return_value'], right['return_value'])
        zeroed = emu_diff._run_side(fx, candidate, [], {}, {}, 42, 10000, [], memory_mode='zeros')
        self.assertEqual(zeroed['return_value']['ax'], 0xF000)

    def test_unmapped_writes_synthesize_pages_and_remain_observable(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        code = bytes.fromhex('b800f0 8ed8 bb3412 c60755 33c0 cb')
        candidate = dataclasses.replace(target, name='candidate', code=code, extent_size=len(code))
        run = emu_diff._run_side(fx, candidate, [], {}, {}, 45, 10000, [])
        self.assertEqual(run['status'], 'OK')
        self.assertIn(0xF1000, run['synthesized_memory']['pages'])
        self.assertTrue(any(event['kind'] == 'write' and event['address']['segment'] == 'UNMAPPED'
                            for event in run['observables']))

    def test_null_global_far_pointer_gets_synthetic_segment(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        code = bytes.fromhex('c51e00f0 8a07 33c0 cb')
        candidate = dataclasses.replace(target, name='candidate', code=code, extent_size=len(code))
        run = emu_diff._run_side(fx, candidate, [], {}, {}, 43, 10000, [])
        self.assertEqual(run['status'], 'OK')
        self.assertTrue(run['synthesized_memory']['seeded_far_pointers'])
        self.assertEqual(run['synthesized_memory']['seeded_far_pointers'][0]['selector'], 0xF000)
        self.assertIn(0xF0000, run['synthesized_memory']['pages'])

    def test_unknown_far_selector_load_uses_synthetic_segment(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        segments = {number: bytearray(data) for number, data in target.segments.items()}
        segments[10][0x1000:0x1004] = b'\x34\x12\x34\x12'
        target = dataclasses.replace(target, segments=segments)
        code = bytes.fromhex('c51e0010 8a07 cb')  # lds bx,[1000], read through the unknown selector
        candidate = dataclasses.replace(target, name='candidate', code=code, extent_size=len(code))
        run = emu_diff._run_side(fx, candidate, [], {}, {}, 44, 10000, [])
        self.assertEqual(run['status'], 'OK')
        self.assertEqual(run['synthesized_memory']['selector_loads'],
                         [dict(original=0x1234, synthetic=0xF000)])
        self.assertIn(0xF1000, run['synthesized_memory']['pages'])

    def test_os_interrupt_is_observed_as_an_os_stub(self):
        fx = self.fixture
        target, _ = emu_diff._target_side(fx, '_ABS', None)
        code = bytes.fromhex('b80125 ba3412 cd21 cb')
        candidate = dataclasses.replace(target, name='candidate', code=code, extent_size=len(code))
        run = emu_diff._run_side(fx, candidate, [], {}, {}, 44, 10000, [])
        self.assertEqual(run['status'], 'OK')
        interrupt = next(event for event in run['observables'] if event.get('os_interrupt'))
        self.assertEqual(interrupt['callee'], 'DOS!INT21_25')
        self.assertEqual(interrupt['argument_words'][0], 0x2501)

    def test_far_pointer_arguments_are_labeled_by_mapsym(self):
        fx = self.fixture
        labels = emu_diff._address_labels(fx)
        segno, offset = fx.symbol_locations['_TurnTab']
        pointer = emu_diff._pointer_labels(fx, labels, emu_diff._selector(segno), offset)
        self.assertEqual(pointer['symbol'], '_TurnTab')
        self.assertEqual(pointer['symbol_offset'], 0)

    def test_stack_local_call_pointers_ignore_frame_offsets(self):
        left = dict(kind='call', callee='USER!#421', argument_words=[0x1000, 0xB000],
                    argument_word_keys=['STACK_LOCAL_POINTER', 'STACK_SELECTOR'],
                    argument_pointers=[dict(word_index=0, form='near', segment=10,
                                            symbol='_end', symbol_offset=0x1000,
                                            offset=0x1000),
                                       dict(word_index=0, form='far', segment='STACK',
                                            offset=0x1000, symbol_offset=None,
                                            selector=0xB000, stack_local=True)],
                    result={'ax': 0, 'dx': 0}, memory_view_sha256='same')
        right = dict(left, argument_words=[0x0FF0, 0xB000],
                     argument_pointers=[dict(word_index=0, form='near', segment=10,
                                             symbol='_end', symbol_offset=0x0FF0,
                                             offset=0x0FF0),
                                        dict(word_index=0, form='far', segment='STACK',
                                             offset=0x0FF0, symbol_offset=None,
                                             selector=0xB000, stack_local=True)])
        self.assertEqual(emu_diff._observable_key(left), emu_diff._observable_key(right))
        data_pointer = dict(right, argument_word_keys=[0x0FF0, 0xB000],
                            argument_pointers=[dict(word_index=0, form='far', segment=10,
                                                    symbol='_TurnTab', symbol_offset=0,
                                                    offset=0x0FF0, selector=0x2000)])
        self.assertNotEqual(emu_diff._observable_key(left), emu_diff._observable_key(data_pointer))

if __name__ == '__main__':
    unittest.main()
