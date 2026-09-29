"""Unnamed static helper stand-ins: a near call from compared code to a static
stand-in in the reserved scaffold segment is accepted only when the original
call reaches an independently established unnamed function entry, one entry
per stand-in. Everything else stays strict."""
import sys
import unittest
from unittest import mock
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture
import ne, mapsym
import library_match
from library_match import compare_member, import_symbols, unnamed_code_entry, SCAFFOLD_SEGMENT, HELPER_STAND_IN_REASON
import tu_assembly as tu


class Original:
    raw = image = symbols = imports = None

    @classmethod
    def load(cls):
        if cls.raw is None:
            cls.raw = fixture('SIMANTW.EXE')
            cls.image = ne.parse(cls.raw)
            cls.symbols = mapsym.parse(fixture('SIMANTW.SYM'))
            cls.imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
        return cls

    @classmethod
    def code(cls, segment, offset, length):
        cls.load()
        ns = cls.image['segments'][segment - 1]
        return cls.raw[ns['file_offset'] + offset:ns['file_offset'] + offset + length]


def module(public, segment, offset, length, calls, stand_in_segment=SCAFFOLD_SEGMENT):
    """The original bytes of PUBLIC as a one-segment candidate whose near calls
    at CALLS (site offset -> stand-in name) go to static stand-ins through
    LEXTDEF/LPUBDEF fixups, as MSC 7.00 emits for a static defined later."""
    code = bytearray(Original.code(segment, offset, length))
    stand_ins = sorted(set(calls.values()))
    fixups = []
    for site, name in sorted(calls.items()):
        assert code[site] == 0xE8
        code[site + 1:site + 3] = b'\0\0'
        fixups.append(dict(segment=1, offset=site + 1, location_type=1, width=2, self_relative=True, frame_method=5, frame_index=None,
                           target_method=2, target_index=stand_ins.index(name) + 1, displacement=0, target=dict(kind='external', name=name)))
    stub = bytes([0xC3] * len(stand_ins))
    return dict(sha256='test', name='helper-stand-in', segments=[
        dict(index=1, name='_TEXT', length=length, data_hex=code.hex(), initialized_ranges=[[0, length]], **{'class': 'CODE'}),
        dict(index=2, name=stand_in_segment, length=len(stub), data_hex=stub.hex(), initialized_ranges=[[0, len(stub)]], **{'class': 'CODE'})],
        groups=[], externals=[dict(name=n, type_index=0, local=True) for n in stand_ins],
        publics=[dict(name=public, offset=0, type_index=0, segment=1, group=0, frame=None, local=False)] +
                [dict(name=n, offset=i, type_index=0, segment=2, group=0, frame=None, local=True) for i, n in enumerate(stand_ins)],
        fixups=fixups, comments=[], commons=[], backpatches=[], aliases=[])


def check(m):
    o = Original.load()
    return compare_member(m, o.raw, o.image, o.symbols, o.imports)


class UnnamedEntryTests(unittest.TestCase):
    def setUp(self):
        self.o = Original.load()

    def entry(self, segment, address):
        return unnamed_code_entry(self.o.raw, self.o.image, self.o.symbols, segment, address)

    def test_chain_of_closed_extents_reaches_the_antedit_helpers(self):
        # _CenterEdit (3:1620) closes at 3:16D4, where UpdateEditBuffers starts;
        # _ResetEditScrollRange (3:6086) is followed by ScrollEditBy (3:616C,
        # one NOP pad) and the tile helper at 3:6250.
        self.assertEqual(self.entry(3, 0x16D4)['chain'][0], (0x1620, 0x16D4))
        self.assertEqual([a for a, b in self.entry(3, 0x6250)['chain']], [0x6086, 0x616C, 0x6250])

    def test_named_entry_mid_function_and_out_of_range_addresses_fail(self):
        self.assertIsNone(self.entry(3, 0x6086))   # a MAPSYM entry is called by name
        self.assertIsNone(self.entry(3, 0x6170))   # inside ScrollEditBy
        self.assertIsNone(self.entry(3, 0x16D5))   # inside UpdateEditBuffers
        self.assertIsNone(self.entry(3, 0xFFFF))


class MatcherStandInTests(unittest.TestCase):
    # __cldtog (4:224C, 132 bytes, no loader relocations) near-calls the unnamed
    # runtime helpers 4:1F4C (site +5D) and 4:211E (site +79).
    CLDTOG = ('__cldtog', 4, 0x224C, 132)

    def test_distinct_stand_ins_for_distinct_helpers_pass_and_are_recorded(self):
        result = check(module(*self.CLDTOG, calls={0x5D: 'stub_a', 0x79: 'stub_b'}))
        self.assertEqual(result['result'], 'STRONGLY_SUPPORTED_MEMBER', result['issues'])
        calls = {c['stand_in']: c['original'] for c in result['helper_stand_in_calls']}
        self.assertEqual(calls, {'stub_a': [4, 0x1F4C], 'stub_b': [4, 0x211E]})
        rows = [r for r in result['contributions'][0]['fixups']]
        self.assertTrue(all(r['equal'] and r['reason'] == HELPER_STAND_IN_REASON for r in rows))
        self.assertEqual(result['scaffold_segments'], [SCAFFOLD_SEGMENT])

    def test_one_stand_in_for_two_helpers_fails(self):
        result = check(module(*self.CLDTOG, calls={0x5D: 'stub_a', 0x79: 'stub_a'}))
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('inconsistent helper stand-in call' in i for i in result['issues']))

    def test_two_stand_ins_for_one_helper_fail(self):
        # Reference view in which the second original call also reaches 4:1F4C:
        # two stand-ins may not stand for one helper.
        o = Original.load()
        ref = bytearray(o.raw)
        site = o.image['segments'][3]['file_offset'] + 0x224C + 0x79
        ref[site + 1:site + 3] = ((0x1F4C - (0x224C + 0x79 + 3)) & 0xFFFF).to_bytes(2, 'little')
        result = compare_member(module(*self.CLDTOG, calls={0x5D: 'stub_a', 0x79: 'stub_b'}), bytes(ref), o.image, o.symbols, o.imports)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('inconsistent helper stand-in call' in i for i in result['issues']))

    def test_stand_in_outside_the_reserved_segment_is_unresolved(self):
        result = check(module(*self.CLDTOG, calls={0x5D: 'stub_a', 0x79: 'stub_b'}, stand_in_segment='OTHER_TEXT'))
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertIn('unplaced contribution OTHER_TEXT', result['issues'])
        self.assertEqual(result['helper_stand_in_calls'], [])

    def test_call_into_the_candidates_own_code_is_not_a_helper(self):
        # __output (4:0F3A) calls its own internal subroutine at 4:13D8: that
        # code is compared here, so a stand-in may not stand for it.
        result = check(module('__output', 4, 0xF3A, 1270, calls={0x65: 'stub_a'}))
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertEqual(result['helper_stand_in_calls'], [])

    def test_unrecognized_helper_entry_fails(self):
        with mock.patch.object(library_match, 'unnamed_code_entry', return_value=None):
            result = check(module(*self.CLDTOG, calls={0x5D: 'stub_a', 0x79: 'stub_b'}))
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('unresolved/mismatched fixup' in i for i in result['issues']))


class ReviewedRunsTests(unittest.TestCase):
    def test_runs_follow_alloc_text_segments(self):
        text = ('#pragma alloc_text(POOLSTUB_TEXT, pool_stub_A)\n'
                '#pragma alloc_text(RUN4_TEXT, UpdateEditWindow, UpdateEditIfBufInvalid)\n'
                '#pragma alloc_text(RUN11_TEXT, CenterEdit, UpdateEditBuffers)\n'
                '#pragma alloc_text(RUN12_TEXT, DoEditScrollLine)\n')
        members = ['_OverlayTileSet', '_UpdateEditWindow', '_UpdateEditIfBufInvalid', '_CenterEdit', '_DoEditScrollLine']
        self.assertEqual(tu.reviewed_runs(text, members),
                         [['_OverlayTileSet'], ['_UpdateEditWindow', '_UpdateEditIfBufInvalid'], ['_CenterEdit'], ['_DoEditScrollLine']])

    def test_reviewed_scaffold_records_the_runs(self):
        text = ('void far pool_stub_A(void);\n#pragma alloc_text(POOLSTUB_TEXT, pool_stub_A)\n'
                '#pragma alloc_text(RUN2_TEXT, B)\nvoid far pool_stub_A(void) { }\n')
        scaffold = tu.reviewed_scaffold(text, ['_A', '_B'], ['_A', '_B'])
        self.assertEqual(scaffold['runs'], [['_A'], ['_B']])


if __name__ == '__main__':
    unittest.main()
