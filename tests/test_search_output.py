"""Effective-output grouping in search.py: repeated objects and score stagnation."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import search


def row(name, obj, opcodes):
    return (None, dict(input=name, object=obj, opcodes=opcodes))


class EffectiveOutput(unittest.TestCase):
    def test_repeats_against_history_and_batch(self):
        rows = [row('a.c', 'x1', '10/20'), row('b.c', 'x2', '12/20'), row('c.c', 'x2', '12/20')]
        report = search.effective_output(rows, {'x1': 'old.c'}, [9])
        self.assertEqual(report['same_output_as'], {'a.c': 'old.c', 'c.c': 'b.c'})
        self.assertEqual(report['distinct_outputs'], 2)
        self.assertEqual(report['rounds_since_best_opcodes_improved'], 0)
        self.assertTrue(report['hint'])

    def test_stagnation_counts_rounds_after_first_best(self):
        report = search.effective_output([row('d.c', 'y', '5/20')], {}, [3, 7, 7, 6])
        self.assertEqual(report['rounds_since_best_opcodes_improved'], 3)
        self.assertEqual(report['same_output_as'], {})
        self.assertIsNone(report['hint'])

    def test_failed_compile_has_no_score(self):
        report = search.effective_output([row('e.c', None, None)], {}, [])
        self.assertEqual(report['distinct_outputs'], 0)
        self.assertEqual(report['rounds_since_best_opcodes_improved'], 0)


if __name__ == '__main__':
    unittest.main()
