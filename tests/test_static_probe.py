"""static_probe: refuses named entries and exposes LINK's same-segment far-call view."""
import sys
import unittest
from pathlib import Path
from unittest import mock
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import static_probe
from common import FormatError


class StaticProbe(unittest.TestCase):
    def test_named_entry_refused(self):
        from common import cards
        card = next(c for c in cards() if c['symbol'] == '_ShowIntro')
        with self.assertRaises(FormatError):
            static_probe.original_bytes(card['segment'], card['offset'])

    def test_same_segment_far_call_becomes_near(self):
        code = bytes.fromhex('c8000000' + '9a00000000' + 'c9cb')
        module = dict(publics=[dict(name='_helper', segment=1, offset=0)],
                      segments=[dict(data_hex=code.hex())],
                      fixups=[dict(segment=1, offset=5, location_type=3, target=dict(kind='external', name='_other'))])
        with mock.patch.object(static_probe.omf, 'parse', return_value=module):
            view, bindings = static_probe.candidate_bytes(mock.Mock(read_bytes=lambda: b''), '_helper', 3, 0x100, {'_other': (3, 0x200)})
        self.assertEqual(view[4:7], b'\x90\x0e\xe8')
        self.assertEqual(int.from_bytes(view[7:9], 'little'), (0x200 - (0x100 + 4 + 5)) & 0xFFFF)
        self.assertEqual(bindings, {})


if __name__ == '__main__':
    unittest.main()
