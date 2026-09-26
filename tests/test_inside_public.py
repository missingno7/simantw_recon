"""context.py data-binding hint: unnamed DGROUP words inside a named public."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import topology_context


class InsidePublic(unittest.TestCase):
    names = {0xBCA6: ['_win_hwnd'], 0xBD00: ['_next']}
    starts = sorted(names)

    def test_word_in_array(self):
        hit = topology_context.inside_public(0xBCAC, self.starts, self.names)
        self.assertEqual(hit['names'], ['_win_hwnd'])
        self.assertEqual(hit['offset'], 6)
        self.assertIn('name[3]', hit['hint'])

    def test_out_of_reach_or_before_first(self):
        self.assertIsNone(topology_context.inside_public(0xBCA6 + 65, self.starts, self.names))
        self.assertIsNone(topology_context.inside_public(0x100, self.starts, self.names))


def rows(*texts):
    return [dict(mnemonic=t.split(' ')[0], operands=t.partition(' ')[2]) for t in texts]


class CodegenShape(unittest.TestCase):
    def test_pop_bp_exit_is_flagged(self):
        card = dict(disassembly=rows('push bp', 'mov bp, sp', 'push di', 'pop di', 'pop bp', 'retf'))
        self.assertIn('LEAVE', topology_context.codegen_shape(card)['shape'])

    def test_leave_exit_is_msc(self):
        card = dict(disassembly=rows('push bp', 'mov bp, sp', 'push si', 'pop si', 'leave', 'retf'))
        self.assertIsNone(topology_context.codegen_shape(card))

    def test_enter_prologue_not_judged(self):
        self.assertIsNone(topology_context.codegen_shape(dict(disassembly=rows('enter 2, 0', 'pop bp', 'retf'))))


class IntrinsicHint(unittest.TestCase):
    card = dict(disassembly=rows('push bp', 'repne scasb al, byte ptr es:[di]', 'retf'))

    def test_fingerprint_without_oi(self):
        hit = topology_context.intrinsic_hint(self.card, ['/AL', '/G2', '/Gs', '/Oeglw', '/NTX'])
        self.assertEqual(hit['fingerprints'], ['repne scasb'])

    def test_quiet_under_oi(self):
        self.assertIsNone(topology_context.intrinsic_hint(self.card, ['/AL', '/Oeilw', '/GA']))

    def test_copy_idiom(self):
        card = dict(disassembly=rows('rep movsw word ptr es:[di], word ptr [si]', 'adc cx, cx', 'rep movsb byte ptr es:[di], byte ptr [si]'))
        self.assertIn('rep movsw; adc cx, cx; rep movsb', topology_context.intrinsic_hint(card, ['/Oelw'])['fingerprints'])


if __name__ == '__main__':
    unittest.main()
