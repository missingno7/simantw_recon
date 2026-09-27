"""tools/probe.py: variant enumeration and profile enforcement (no compilation)."""
import sys
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import probe
from common import FormatError


class Variants(unittest.TestCase):
    def test_one_at_a_time_keeps_baseline_first(self):
        spec = dict(text='A={{A}} B={{B}}', axes=dict(A={'a0': '0', 'a1': '1'}, B={'b0': 'x', 'b1': 'y', 'b2': 'z'}))
        vs = probe.variants(spec)
        self.assertEqual(vs[0], ({'A': 'a0', 'B': 'b0'}, 'A=0 B=x'))
        self.assertEqual(len(vs), 1 + 1 + 2)

    def test_product_mode(self):
        spec = dict(text='{{A}}{{B}}', mode='product', axes=dict(A={'a': 'a', 'b': 'b'}, B={'c': 'c', 'd': 'd'}))
        self.assertEqual(sorted(t for _, t in probe.variants(spec)), ['ac', 'ad', 'bc', 'bd'])

    def test_missing_placeholder_rejected(self):
        with self.assertRaises(FormatError):
            probe.variants(dict(text='nothing', axes=dict(A={'a': '1'})))


class Profiles(unittest.TestCase):
    def test_wrong_profile_for_symbol_rejected(self):
        with mock.patch('promote.function_flags', return_value=({'name': 'ogi'}, ['/AL'])):
            with self.assertRaises(FormatError):
                probe.resolve_flags(dict(symbol='_x', profile='baseline'))
            self.assertEqual(probe.resolve_flags(dict(symbol='_x')), ('ogi', ['/AL']))

    def test_toy_probe_needs_catalogued_profile(self):
        with self.assertRaises(FormatError):
            probe.resolve_flags(dict(text='x'))


if __name__ == '__main__':
    unittest.main()
