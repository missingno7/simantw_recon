"""Whole-image ledger: exact rebuild, fail-closed ownership and binder rules."""
import sys
import unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import FormatError
import image


def module_with(data_hex, name='SEG'):
    return dict(segments=[dict(index=1, name=name, data_hex=data_hex)])


def comparison(fixups=(), transformations=(), length=None, data_hex='', base=0x100, result='CONFIRMED_MEMBER'):
    return dict(result=result, contributions=[dict(segment='SEG', original_segment=1, original_offset=base, length=length or len(data_hex) // 2,
                                                   initialized_ranges=[[0, len(data_hex) // 2]], fixups=list(fixups), transformations=list(transformations))])


class BinderRuleTests(unittest.TestCase):
    def regen(self, data_hex, **kwargs):
        with patch.object(image, 'compare_member', return_value=comparison(data_hex=data_hex, **kwargs)):
            return image.regenerate(module_with(data_hex), b'', {}, {}, {})[1]

    def test_resolved_offset_written_from_target(self):
        placed = self.regen('b80000', fixups=[dict(offset=1, equal=True, reason='resolved offset and frame', target=dict(kind='internal', segment=10, offset=0x1234))])
        self.assertEqual([placed[(1, 0x100 + i)][0] for i in range(3)], [0xB8, 0x34, 0x12])

    def test_relative_call_uses_site_origin(self):
        placed = self.regen('e80000', fixups=[dict(offset=1, equal=True, reason='same-segment relative offset', target=dict(kind='internal', segment=1, offset=0x200))])
        self.assertEqual(placed[(1, 0x101)][0] | placed[(1, 0x102)][0] << 8, 0x200 - 0x103)

    def test_far_call_translation_matches_link(self):
        placed = self.regen('9a00000000', transformations=[dict(offset=0, kind='LINK same-segment far call/jump translation', target=dict(kind='internal', segment=1, offset=0x300))])
        got = bytes(placed[(1, 0x100 + i)][0] for i in range(5))
        self.assertEqual(got, b'\x90\x0e\xe8' + (0x300 - 0x105).to_bytes(2, 'little'))

    def test_loader_sites_are_marked_as_chain_not_object_bytes(self):
        placed = self.regen('8e060000', fixups=[dict(offset=2, equal=True, reason='NE selector for independently named target', target=dict(kind='internal', segment=9, offset=0))])
        self.assertTrue(placed[(1, 0x102)][1] and placed[(1, 0x103)][1])
        self.assertFalse(placed[(1, 0x101)][1])

    def test_unknown_fixup_rule_fails_closed(self):
        with self.assertRaisesRegex(FormatError, 'no rule'):
            self.regen('0000', fixups=[dict(offset=0, equal=True, reason='something new', target=None)])

    def test_unequal_fixup_or_incomplete_member_fails_closed(self):
        with self.assertRaisesRegex(FormatError, 'unequal'):
            self.regen('0000', fixups=[dict(offset=0, equal=False, reason='resolved offset and frame', target=None)])
        with patch.object(image, 'compare_member', return_value=dict(result='NO_COMPLETE_MATCH', issues=['x'])):
            with self.assertRaisesRegex(FormatError, 'complete member'):
                image.regenerate(module_with('00'), b'', {}, {}, {})


class WholeImageTests(unittest.TestCase):
    def test_current_image_is_exact(self):
        result = image.build(write=False)
        self.assertEqual(result['status'], 'HYBRID_EXACT')
        self.assertEqual(result['mismatched_bytes'], 0)
        self.assertEqual(sum(result['owned'].values()) + result['debt_total'], result['file_bytes'])

    def test_wrong_object_byte_is_detected(self):
        original = image.regenerate
        state = {'done': False}
        def corrupt(*args):
            comparison, placed = original(*args)
            if not state['done']:
                key = next(k for k, v in placed.items() if not v[1])
                placed[key] = ((placed[key][0] + 1) & 255, False); state['done'] = True
            return comparison, placed
        with patch.object(image, 'regenerate', side_effect=corrupt):
            result = image.build(write=False)
        self.assertEqual(result['status'], 'NOT_EXACT')
        self.assertEqual(result['mismatched_bytes'], 1)

    def test_failed_object_is_a_problem_not_silent_debt(self):
        with patch.object(image, 'regenerate', side_effect=FormatError('object is not a complete member')):
            result = image.build(write=False)
        self.assertEqual(result['status'], 'NOT_EXACT')
        self.assertTrue(result['problems'])


if __name__ == '__main__':
    unittest.main()


class DataGateTests(unittest.TestCase):
    def setUp(self):
        import recovery_gate
        self.gate = recovery_gate
        self.symbols = dict(absolute_symbols=[], segments=[dict(number=1, name='FARDATA', symbols=[dict(name='_A', offset=0x10), dict(name='_B', offset=0x14), dict(name='_C', offset=0x20)])])
        self.image = dict(segments=[dict(kind='DATA', logical_size=0x40, relocations=[])])
    def module(self, publics, length=8, klass='FAR_DATA', ranges=None):
        return dict(publics=[dict(name=n, segment=1, offset=o) for n, o in publics],
                    segments=[dict(index=1, name='FARDATA', **{'class': klass}, length=length, initialized_ranges=ranges if ranges is not None else [(0, length)])])
    def test_span_runs_to_next_public_of_the_object(self):
        t = self.gate.data_targets(self.module([('_A', 0), ('_B', 4)], length=12), b'', self.image, self.symbols, ['_A', '_B'])
        self.assertEqual((t['_A']['size'], t['_B']['size']), (4, 8))
        self.assertEqual(t['_A']['comparison'], 'data_member')
    def test_span_may_not_swallow_an_original_public(self):
        with self.assertRaisesRegex(FormatError, 'swallow'):
            self.gate.data_targets(self.module([('_A', 0)], length=8), b'', self.image, self.symbols, ['_A'])
    def test_uninitialized_or_code_or_bss_refused(self):
        with self.assertRaisesRegex(FormatError, 'initialized'):
            self.gate.data_targets(self.module([('_A', 0)], length=4, ranges=[]), b'', self.image, self.symbols, ['_A'])
        for klass in ('CODE', 'BSS'):
            with self.assertRaisesRegex(FormatError, 'initialized data only'):
                self.gate.data_targets(self.module([('_A', 0)], length=4, klass=klass), b'', self.image, self.symbols, ['_A'])
    def test_code_segment_symbol_refused(self):
        image = dict(segments=[dict(kind='CODE', logical_size=0x40, relocations=[])])
        with self.assertRaisesRegex(FormatError, 'not a data-segment'):
            self.gate.data_targets(self.module([('_A', 0)], length=4), b'', image, self.symbols, ['_A'])
    def test_selector_pool_and_linker_bss_refused(self):
        symbols = dict(absolute_symbols=[], segments=[dict(number=n, name='S%d' % n, symbols=[]) for n in range(1, 10)] +
                       [dict(number=10, name='DGROUP', symbols=[dict(name='_P', offset=0xBE70), dict(name='_edata', offset=0xCA60), dict(name='_Z', offset=0xCA70), dict(name='_end', offset=0xCF56)])])
        image = dict(segments=[dict(kind='DATA', logical_size=0xD000, relocations=[])] * 10)
        with self.assertRaisesRegex(FormatError, 'selector-pool'):
            self.gate.data_targets(self.module([('_P', 0)], length=4), b'', image, symbols, ['_P'])
        with self.assertRaisesRegex(FormatError, 'BSS region'):
            self.gate.data_targets(self.module([('_Z', 0)], length=4), b'', image, symbols, ['_Z'])
