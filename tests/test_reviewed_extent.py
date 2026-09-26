"""recovery_gate: reviewed extents must reach the next entry and nothing else."""
import sys
import unittest
from pathlib import Path
from unittest import mock
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import recovery_gate
from common import FormatError


class ReviewedExtent(unittest.TestCase):
    def review(self, symbols, name, code, offset, upper):
        with mock.patch.object(recovery_gate, 'read_json', return_value=dict(symbols=symbols)), \
             mock.patch.object(recovery_gate.REVIEWED_EXTENTS.__class__, 'is_file', return_value=True):
            return recovery_gate.reviewed_extent(name, code, offset, upper)

    def test_span_to_next_entry(self):
        hit = self.review({'_f': dict(size=4, evidence='x')}, '_f', b'\x90' * 8, 2, 6)
        self.assertEqual((hit['size'], hit['end']), (4, 6))

    def test_one_zero_alignment_byte_allowed(self):
        self.assertEqual(self.review({'_f': dict(size=3, evidence='x')}, '_f', b'\x90\x90\x90\x00', 0, 4)['size'], 3)

    def test_short_span_refused(self):
        with self.assertRaises(FormatError):
            self.review({'_f': dict(size=2, evidence='x')}, '_f', b'\x90' * 8, 0, 4)

    def test_nonzero_tail_refused(self):
        with self.assertRaises(FormatError):
            self.review({'_f': dict(size=3, evidence='x')}, '_f', b'\x90\x90\x90\xcc', 0, 4)

    def test_unreviewed_is_none(self):
        self.assertIsNone(self.review({}, '_f', b'\x90' * 4, 0, 4))


if __name__ == '__main__':
    unittest.main()
