import copy
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture, FormatError
import mapsym
import ne
import omf
from library_match import compare_member, import_symbols


class RuntimeDgroupPlacementTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.raw = fixture('SIMANTW.EXE')
        cls.ne = ne.parse(cls.raw)
        cls.sym = mapsym.parse(fixture('SIMANTW.SYM'))
        cls.imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
        cls.members = {}
        for library in ('LLIBCW.LIB', 'LLIBFPW.LIB'):
            path = ROOT / 'toolchain/sdk300/CLIB' / library
            for data in omf.library_modules(path.read_bytes()):
                try:
                    member = omf.parse(data)
                except FormatError:
                    continue
                cls.members[member['name'].lower()] = member

    def compare(self, name, sym=None):
        return compare_member(self.members[name.lower()], self.raw, self.ne,
                              sym or self.sym, self.imports)

    def test_message_and_private_data_members_are_complete(self):
        targets = {
            r'\mrt6\c\87cdisp.asm': {'MSG'},
            'dos\\nmsghdr.asm': {'HDR', 'PAD', 'EPAD'},
            r'\mrt6\common\strgtod.asm': {'_DATA'},
            'crt0fp.asm': {'MSG', 'PAD'},
        }
        for name, expected in targets.items():
            with self.subTest(member=name):
                result = self.compare(name)
                self.assertIn(result['result'],
                              ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'),
                              result['issues'])
                placed = {row['segment'] for row in result['contributions']}
                self.assertTrue(expected <= placed, (expected, placed))
                self.assertEqual(result['literal_compared'], result['literal_equal'])
                self.assertEqual(result['fixups_equal'], result['fixups_total'])

    def test_bad_edata_anchor_rejects_message_placement(self):
        sym = copy.deepcopy(self.sym)
        dgroup = next(segment for segment in sym['segments'] if segment['number'] == 10)
        next(item for item in dgroup['symbols'] if item['name'] == '_edata')['offset'] += 1
        result = self.compare(r'\mrt6\c\87cdisp.asm', sym)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('_edata' in issue for issue in result['issues']))

    def test_ambiguous_caption_anchor_rejects_message_placement(self):
        sym = copy.deepcopy(self.sym)
        dgroup = next(segment for segment in sym['segments'] if segment['number'] == 10)
        caption = next(item for item in dgroup['symbols'] if item['name'] == '__caption')
        dgroup['symbols'].append(dict(caption, offset=caption['offset'] + 1))
        result = self.compare('dos\\nmsghdr.asm', sym)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('caption' in issue.lower() for issue in result['issues']))

    def test_wrong_lastiob_boundary_rejects_private_data_placement(self):
        sym = copy.deepcopy(self.sym)
        dgroup = next(segment for segment in sym['segments'] if segment['number'] == 10)
        next(item for item in dgroup['symbols'] if item['name'] == '__lastiob')['offset'] += 1
        result = self.compare(r'\mrt6\common\strgtod.asm', sym)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('uniquely tile' in issue for issue in result['issues']))

    def test_ambiguous_lastiob_boundary_rejects_private_data_placement(self):
        sym = copy.deepcopy(self.sym)
        dgroup = next(segment for segment in sym['segments'] if segment['number'] == 10)
        lastiob = next(item for item in dgroup['symbols'] if item['name'] == '__lastiob')
        dgroup['symbols'].append(dict(lastiob, offset=lastiob['offset'] + 1))
        result = self.compare(r'\mrt6\common\strgtod.asm', sym)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('ambiguous' in issue for issue in result['issues']))


if __name__ == '__main__':
    unittest.main()
