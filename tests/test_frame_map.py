"""Diagnostic frame map: CodeView parsing, target frame slots and findings."""
import struct
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import frame_map


def cv_record(kind, payload):
    return struct.pack('<HH', len(payload) + 2, kind) + payload


def proc(name):
    body = b'\0' * 12 + struct.pack('<HHHHHH', 0x20, 0, 0x1F, 0, 0, 0x1001) + b'\0' + bytes([len(name)]) + name.encode()
    return cv_record(0x0105, body)


class FrameMapTests(unittest.TestCase):
    def test_codeview_locals_of_one_procedure(self):
        sym = (b'\x01\0\0\0' + proc('other') + cv_record(0x0100, struct.pack('<hH', -2, 0x72) + b'\x01x')
               + proc('f') + cv_record(0x0100, struct.pack('<hH', -6, 0x0272) + b'\x01p')
               + cv_record(0x0002, struct.pack('<HH', 0x72, 15) + b'\x01i'))
        homes, regs = frame_map.codeview_locals(sym, '_f')
        self.assertEqual([(h['name'], h['offset'], h['size']) for h in homes], [('p', -6, 4)])
        self.assertEqual([(r['name'], r['register']) for r in regs], [('i', 'si')])

    def test_target_frame_widths(self):
        dis = [dict(mnemonic='enter', operands='4, 0'), dict(mnemonic='mov', operands='word ptr [bp - 4], ax'),
               dict(mnemonic='les', operands='bx, ptr [bp - 4]'), dict(mnemonic='lea', operands='ax, [bp - 2]')]
        enter, slots = frame_map.target_frame(dis)
        self.assertEqual(enter, 4)
        self.assertEqual(set(slots), {-4, -2})
        self.assertIn(4, slots[-4])

    def test_extra_local_and_shifted_pointer_are_reported(self):
        homes = [dict(name='p', offset=-6, size=4), dict(name='pp', offset=-2, size=2)]
        findings = frame_map.compare(homes, [], 6, 4, {-4: [2], -2: [2]})
        self.assertTrue(any('p (4 bytes) starts at bp-6' in f for f in findings))
        self.assertTrue(any('frame size differs' in f for f in findings))

    def test_equal_frames_stay_quiet_on_register_homes_and_temporaries(self):
        # An exact function: a register-resident local keeps an untouched home,
        # and a compiler temporary occupies an unnamed slot.
        homes = [dict(name='count', offset=-2, size=2)]
        self.assertEqual(frame_map.compare(homes, [], 4, 4, {-4: [2]}), [])
        self.assertEqual(frame_map.compare([dict(name='v', offset=-4, size=4)], [], None, None, {}), [])


if __name__ == '__main__':
    unittest.main()
