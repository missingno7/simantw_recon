import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import alloc_lab
from common import FormatError


class AllocationLabTests(unittest.TestCase):
    def test_grid_covers_requested_factor_families(self):
        rows = alloc_lab.generate_cases()
        self.assertGreaterEqual(len(rows), 300)
        factors = {row['factor'].split(':')[0] for row in rows}
        self.assertTrue({'word_locals', 'static_uses', 'loop_depth', 'declaration',
                         'first_use', 'first_definition', 'far_call_live', 'parameter_form',
                         'parameter_copies', 'pointer_vs_arithmetic', 'shift_count',
                         'scalar_type', 'address_taken', 'reuse_purpose',
                         'cse_temporary', 'if_arm_uses'} <= factors)
        self.assertTrue(all('int f(' in row['source'] for row in rows))

    def test_observation_parser_accepts_complete_and_rejects_truncated(self):
        good = dict(id='A0001', family='competition', factor='word_locals', value=2,
                    profile='baseline', status='OK', frame=2, homes={}, registers=['si'],
                    named_homes=[], named_registers=[{'name': 'a', 'register': 'si'}],
                    byte_sha256='a'*64)
        with tempfile.TemporaryDirectory() as d:
            path = Path(d) / 'observations.jsonl'
            path.write_text(json.dumps(good) + '\n', encoding='utf-8')
            self.assertEqual(alloc_lab.read_observations(path), [good])
            path.write_text('{bad json}\n', encoding='utf-8')
            with self.assertRaises(FormatError):
                alloc_lab.read_observations(path)
            path.write_text(json.dumps({'id': 'A', 'status': 'OK'}) + '\n', encoding='utf-8')
            with self.assertRaises(FormatError):
                alloc_lab.read_observations(path)


if __name__ == '__main__':
    unittest.main()
