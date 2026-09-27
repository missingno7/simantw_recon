import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from codegen_diff import branch_destinations


def row(to, t, co, c):
    return dict(target_offset=to, target=t, candidate_offset=co, candidate=c, differences=[])


class BranchDestinations(unittest.TestCase):
    def test_retry_loop_skips_decrement(self):
        # _InitSow: the target's failed test jumps past `sub si,2` to the loop test.
        rows = [row(0, 'cmp byte ptr [bx], 0x10', 0, 'cmp byte ptr [bx], 0x10'),
                row(3, 'jae 0x9', 3, 'jae 0x6'),
                row(5, 'mov byte ptr [bx], al', 5, 'mov byte ptr [bx], al'),
                row(6, 'sub si, 2', 6, 'sub si, 2'),
                row(9, 'or si, si', None, None),
                row(11, 'je 0xf', 9, 'je 0xd'),
                row(13, 'jmp 0', 11, 'jmp 0'),
                row(15, 'retf', 13, 'retf')]
        rows[4]['candidate'] = None
        found = branch_destinations(rows)
        # or si,si has no candidate counterpart, so the je shift is not reported; the jae is not either
        # (its target row is unpaired). Pair the destination to make it a genuine difference:
        rows[4] = row(9, 'or si, si', 8, 'nop')
        found = branch_destinations(rows)
        self.assertEqual([f['target_offset'] for f in found], [3])
        self.assertEqual(found[0]['target_lands_on']['instruction'], 'or si, si')
        self.assertEqual(found[0]['candidate_lands_on']['instruction'], 'sub si, 2')

    def test_offset_shift_is_not_a_destination_difference(self):
        rows = [row(0, 'je 0x4', 0, 'je 0x5'),
                row(2, 'inc ax', 2, 'inc ax'),
                row(None, None, 3, 'nop'),
                row(3, 'nop', 4, 'nop'),
                row(4, 'retf', 5, 'retf')]
        rows[0]['target'] = 'je 0x4'
        self.assertEqual(branch_destinations(rows), [])


if __name__ == '__main__':
    unittest.main()
