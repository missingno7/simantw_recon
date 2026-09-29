"""MSC7-M5/M6: every compiler runner keeps TMP inside the verified heap-phase window.

C2 reserves dead frame copies depending on its heap's 16-byte phase, which the TMP path length shifts.
All admitted sources reproduce only when len(TMP) % 16 is in {2..5}; the batch runner's former
per-directory TMP (W:\\B0000) broke two admitted units.
"""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
WINDOW = range(2, 6)


def dos_tmp_values(text):
    """TMP values a runner writes into its DOS batch scripts (Python string escapes resolved)."""
    values = []
    for match in re.finditer(r"set TMP=((?:[^\\'\"]|\\\\)*?)(?:\\n|'|\")", text):
        values.append(match.group(1).replace('\\\\', '\\'))
    return values


class HeapPhaseTests(unittest.TestCase):
    def test_runner_tmp_paths_stay_in_the_verified_phase_window(self):
        found = {}
        for name in ('tools/compiler.py', 'tools/compiler_worker.py'):
            text = (ROOT / name).read_text(encoding='utf-8')
            values = dos_tmp_values(text)
            self.assertTrue(values, name)
            found[name] = values
            for value in values:
                self.assertIn(len(value) % 16, WINDOW, '%s sets TMP=%r (length %d)' % (name, value, len(value)))
        self.assertIn('W:\\', found['tools/compiler_worker.py'])

    def test_batch_runner_no_longer_sets_a_per_directory_tmp(self):
        text = (ROOT / 'tools/compiler.py').read_text(encoding='utf-8')
        self.assertNotIn("'set TMP=W:\\\\'+jobdir.name", text)


if __name__ == '__main__':
    unittest.main()
