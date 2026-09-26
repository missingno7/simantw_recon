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


if __name__ == '__main__':
    unittest.main()
