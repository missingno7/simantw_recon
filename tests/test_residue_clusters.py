"""tools/residue_clusters.py: earliest meaningful divergence classification."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from residue_clusters import classify


def row(to, t, co, c, diffs=()):
    return dict(target_offset=to, target=t, candidate_offset=co, candidate=c, differences=list(diffs))


class Classify(unittest.TestCase):
    def test_frame(self):
        self.assertEqual(classify([row(0, 'enter 8, 0', 0, 'enter 6, 0', ['immediate_or_binding'])])[0], 'FRAME_SIZE')

    def test_fixup_noise_skipped_then_register(self):
        rows = [row(0, 'enter 2, 0', 0, 'enter 2, 0'),
                row(4, "mov <resolved fixup> [x]", 4, "mov <resolved fixup> [y]", ['immediate_or_binding']),
                row(8, 'add ax, cx', 8, 'add cx, ax', ['register_allocation'])]
        self.assertEqual(classify(rows)[0], 'WRONG_REGISTER')

    def test_signedness(self):
        self.assertEqual(classify([row(0, 'jl 0x10', 0, 'jb 0x10', ['instruction_shape'])])[0], 'SIGNEDNESS')

    def test_missing_les_is_far_pointer(self):
        self.assertEqual(classify([row(0, 'les si, ptr [bp + 6]', None, None, ['instruction_shape'])])[0], 'FAR_POINTER')

    def test_relocation_only(self):
        rows = [row(0, "mov <resolved fixup> [x]", 0, "mov <resolved fixup> [y]", ['immediate_or_binding'])]
        self.assertEqual(classify(rows)[0], 'RELOCATION_ONLY')


if __name__ == '__main__':
    unittest.main()


class Frontier(unittest.TestCase):
    def test_earlier_decision_outranks_more_opcodes(self):
        import drafts
        from unittest import mock
        frame_fixed = {'result': 'NO_COMPLETE_MATCH', 'diagnostic': {'opcode_matches': 40, 'aligned_asm': [
            row(0, 'enter 2, 0', 0, 'enter 2, 0'), row(4, 'mov ax, 1', 4, 'mov bx, 1', ['register_allocation'])]}}
        more_opcodes = {'result': 'NO_COMPLETE_MATCH', 'diagnostic': {'opcode_matches': 45, 'aligned_asm': [
            row(0, 'enter 2, 0', 0, 'enter 4, 0', ['immediate_or_binding'])]}}
        with mock.patch('tu_assembly.body_exact', return_value=False):
            self.assertGreater(drafts.frontier_rank(frame_fixed), drafts.frontier_rank(more_opcodes))


class DownstreamBranch(unittest.TestCase):
    def test_displacement_only_jump_is_skipped(self):
        rows = [row(0, 'jmp 0x6', 0, 'jmp 0x7', ['branch_target']),
                row(2, 'mov ax, 1', 2, 'mov bx, 1', ['register_allocation']),
                row(6, 'retf', 7, 'retf')]
        self.assertEqual(classify(rows)[0], 'WRONG_REGISTER')
