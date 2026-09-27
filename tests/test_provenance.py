"""Source provenance classes recorded by promote.py (EXACT_NATURAL by default, EXACT_STEERED on request)."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import promote
from common import read_json


class Provenance(unittest.TestCase):
    def test_steered_then_natural(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'provenance.json'
            with mock.patch.object(promote, 'PROVENANCE', path), mock.patch.object(promote.publication, 'publication_lock', mock.MagicMock()):
                self.assertEqual(promote.record_provenance(['_f', '_g'], 'tu_x', 'dead guard steers DI'), 'EXACT_STEERED')
                data = read_json(path)
                self.assertEqual(data['entries']['_f']['provenance'], 'EXACT_STEERED')
                self.assertEqual(data['entries']['_g']['steering'], 'dead guard steers DI')
                # A later natural admission of _f clears its steered record; _g stays steered.
                self.assertEqual(promote.record_provenance(['_f'], 'f-1'), 'EXACT_NATURAL')
                data = read_json(path)
                self.assertNotIn('_f', data['entries'])
                self.assertIn('_g', data['entries'])


if __name__ == '__main__':
    unittest.main()
