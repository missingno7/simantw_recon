"""Module-local symbols: a static function called before its definition.

MSC 7.00 emits such a call as a self-relative fixup to a local external
(LEXTDEF) that LINK binds to the local public (LPUBDEF) of the same module.
The matcher resolves exactly that binding and nothing looser."""
import copy
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from library_match import compare_member

BASE = 0x100            # original offset of _Caller in segment 1
# _Caller: call helper ; retf    helper: ret
CANDIDATE = bytes.fromhex('e80000cb') + bytes.fromhex('c3')
ORIGINAL = bytes.fromhex('e80100cb') + bytes.fromhex('c3')


def module(local=True, helper_name='helper', extern_name='helper', helper_offset=4):
    return dict(
        segments=[dict(name='CODE_TEXT', **{'class': 'CODE'}, length=len(CANDIDATE), data_hex=CANDIDATE.hex(),
                       initialized_ranges=[[0, len(CANDIDATE)]], index=1)],
        groups=[], names=[], comments=[], commons=[], backpatches=[], aliases=[],
        externals=[dict(name=extern_name, type_index=0, local=local)],
        publics=[dict(name='_Caller', offset=0, segment=1, group=None, frame=None, type_index=0, local=False),
                 dict(name=helper_name, offset=helper_offset, segment=1, group=None, frame=None, type_index=0, local=local)],
        fixups=[dict(segment=1, offset=1, width=2, location_type=1, self_relative=True, target_method=2,
                     target_index=1, target=dict(kind='external', name=extern_name), frame_method=5,
                     frame_index=None, displacement=0)])


class LocalSymbolTests(unittest.TestCase):
    def setUp(self):
        self.raw = bytes(BASE) + ORIGINAL + bytes(16)
        self.image = dict(segments=[dict(number=1, file_offset=0, logical_size=len(self.raw), relocations=[], kind='CODE')])
        self.symbols = dict(segments=[dict(number=1, name='CODE_TEXT', symbols=[dict(name='_Caller', offset=BASE)])],
                            absolute_symbols=[])

    def check(self, m, raw=None):
        return compare_member(m, raw or self.raw, self.image, self.symbols, {})

    def test_forward_static_call_binds_to_local_public(self):
        r = self.check(module())
        self.assertIn(r['result'], ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'), r.get('issues'))
        self.assertEqual(r['fixups_equal'], r['fixups_total'])

    def test_wrong_original_displacement_rejects(self):
        raw = bytes(BASE) + bytes.fromhex('e80200cb') + bytes.fromhex('c3') + bytes(16)
        self.assertEqual(self.check(module(), raw)['result'], 'NO_COMPLETE_MATCH')

    def test_global_external_is_not_bound_to_a_local_definition(self):
        self.assertEqual(self.check(module(local=False))['result'], 'NO_COMPLETE_MATCH')

    def test_missing_or_misnamed_local_public_rejects(self):
        self.assertEqual(self.check(module(helper_name='other'))['result'], 'NO_COMPLETE_MATCH')

    def test_duplicate_local_publics_reject(self):
        m = module(); m['publics'].append(dict(m['publics'][1], offset=3))
        self.assertEqual(self.check(m)['result'], 'NO_COMPLETE_MATCH')

    def test_helper_elsewhere_rejects(self):
        self.assertEqual(self.check(module(helper_offset=3))['result'], 'NO_COMPLETE_MATCH')


if __name__ == '__main__':
    unittest.main()


class NamedFillerTests(unittest.TestCase):
    def test_filler_may_not_cover_a_mapsym_public(self):
        import tu_assembly
        from common import FormatError
        with self.assertRaises(FormatError):
            tu_assembly.refuse_named_filler(0xBE05, 0xBE12)   # contains _lastProxObj
        tu_assembly.refuse_named_filler(0xBD3C, 0xBDDA)       # unnamed window literals


class EmptySegdefFrameTests(unittest.TestCase):
    """An assembly module's `PACKX SEGMENT ... EXTRN _buf ... ENDS` block is an
    empty SEGDEF; used as an F0 frame it stands for the MAPSYM segment of that
    name, and only for targets inside that segment."""
    def setUp(self):
        self.raw = bytes(BASE) + bytes.fromhex('a11000cb') + bytes(16)
        self.image = dict(segments=[dict(number=1, file_offset=0, logical_size=len(self.raw), relocations=[], kind='CODE'),
                                    dict(number=2, file_offset=0, logical_size=0x100, relocations=[], kind='DATA')])
        self.symbols = dict(segments=[dict(number=1, name='CODE_TEXT', symbols=[dict(name='_Caller', offset=BASE)]),
                                      dict(number=2, name='PACKX', symbols=[dict(name='_buf', offset=0x10)])],
                            absolute_symbols=[])

    def module(self, frame_name='PACKX', frame_length=0, target='_buf'):
        code = bytes.fromhex('a10000cb')
        return dict(
            segments=[dict(name='CODE_TEXT', length=len(code), data_hex=code.hex(), initialized_ranges=[[0, len(code)]], index=1, **{'class': 'CODE'}),
                      dict(name=frame_name, length=frame_length, data_hex='', initialized_ranges=[], index=2, **{'class': 'FAR_DATA'})],
            groups=[], names=[], comments=[], commons=[], backpatches=[], aliases=[],
            externals=[dict(name=target, type_index=0, local=False)],
            publics=[dict(name='_Caller', offset=0, segment=1, group=None, frame=None, type_index=0, local=False)],
            fixups=[dict(segment=1, offset=1, width=2, location_type=1, self_relative=False, target_method=2, target_index=1,
                         target=dict(kind='external', name=target), frame_method=0, frame_index=2, displacement=0)])

    def check(self, m):
        return compare_member(m, self.raw, self.image, self.symbols, {})['result']

    def test_empty_named_frame_resolves_target_in_that_segment(self):
        self.assertIn(self.check(self.module()), ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'))

    def test_frame_of_another_segment_rejects(self):
        self.assertEqual(self.check(self.module(frame_name='OTHER')), 'NO_COMPLETE_MATCH')

    def test_non_empty_frame_segment_is_not_a_name_standin(self):
        self.assertEqual(self.check(self.module(frame_length=2)), 'NO_COMPLETE_MATCH')
