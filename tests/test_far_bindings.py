"""Far-name hints must not survive unknown segment or control-flow changes."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from topology_context import far_data_bindings
from analysis import decoder


class FarBindingTests(unittest.TestCase):
    def rows(self, code, additive=False):
        card = dict(disassembly=[dict(bytes=i.bytes.hex(), offset=i.address)
                                 for i in decoder().disasm(bytes.fromhex(code), 0)])
        symbols = dict(segments=[dict(symbols=[]) for _ in range(10)])
        symbols['segments'][8]['symbols'] = [dict(offset=0x7d4a, name='_BoyMsgCnt'),
                                             dict(offset=0x809c, name='_LionListX')]
        image = dict(segments=[{} for _ in range(10)])
        image['segments'][9] = dict(relocations=[dict(source_type=2, sites=[0xc4f6],
            additive=additive, target=dict(kind='internal', segment=9, offset=0))])
        return far_data_bindings(card, symbols, image)

    def test_exact_selector_and_signed_indexed_displacement(self):
        rows = self.rows('8e06f6c4 26a14a7d 268a849c80')
        self.assertEqual([r['exact_mapsym_names'] for r in rows], [['_BoyMsgCnt'], ['_LionListX']])
        self.assertEqual(rows[0]['addressed_segment'], 9)
        self.assertEqual(rows[1]['index_registers'], ['si'])

    def test_call_jump_segment_write_and_interrupt_invalidate(self):
        for middle in ['e80000', 'eb00', '07', '8ec0', '8ed8', 'cd03']:
            with self.subTest(middle=middle):
                self.assertEqual(self.rows('8e06f6c4 ' + middle + ' 26a14a7d'), [])

    def test_branch_join_after_selector_load_invalidates(self):
        # Conditional branch targets the ES read, bypassing the selector load.
        self.assertEqual(self.rows('7404 8e06f6c4 26a14a7d'), [])

    def test_les_read_uses_old_es_then_invalidates(self):
        rows = self.rows('8e06f6c4 26c41e4a7d 26a14a7d')
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]['exact_mapsym_names'], ['_BoyMsgCnt'])

    def test_unknown_or_additive_selector_does_not_claim_name(self):
        self.assertEqual(self.rows('8e060000 26a14a7d'), [])
        self.assertEqual(self.rows('8e06f6c4 26a14a7d', additive=True), [])

if __name__ == '__main__':
    unittest.main()
