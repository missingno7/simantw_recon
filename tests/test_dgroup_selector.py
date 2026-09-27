"""A selector fixup through the DGROUP group frame (interrupt DS load) is DGROUP's selector."""
import copy
import json
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture
import ne, mapsym
from library_match import compare_member, import_symbols


class DGroupSelectorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = json.loads((ROOT / 'evidence/topology/supervisor-dgroup-selector/mainwnd-unit-module.json').read_text())
        cls.raw = fixture('SIMANTW.EXE'); cls.image = ne.parse(cls.raw)
        cls.symbols = mapsym.parse(fixture('SIMANTW.SYM')); cls.imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
        cls.fixup = next(f for f in cls.module['fixups'] if f['frame_method'] == 1 and f['location_type'] == 2)

    def check(self, module):
        return compare_member(module, self.raw, self.image, self.symbols, self.imports)['result']

    def test_dgroup_frame_selector_admits(self):
        self.assertEqual(self.check(self.module), 'STRONGLY_SUPPORTED_MEMBER')

    def test_other_group_rejects(self):
        module = copy.deepcopy(self.module)
        module['groups'][self.fixup['frame_index'] - 1]['name'] = 'OTHERGROUP'
        self.assertEqual(self.check(module), 'NO_COMPLETE_MATCH')

    def test_target_outside_group_rejects(self):
        module = copy.deepcopy(self.module)
        group = module['groups'][self.fixup['frame_index'] - 1]
        group['segments'] = [s for s in group['segments'] if s != self.fixup['target_index']]
        self.assertEqual(self.check(module), 'NO_COMPLETE_MATCH')

    def test_offset_fixup_kind_rejects(self):
        module = copy.deepcopy(self.module)
        f = next(g for g in module['fixups'] if g == self.fixup)
        f['location_type'] = 1
        self.assertEqual(self.check(module), 'NO_COMPLETE_MATCH')


if __name__ == '__main__':
    unittest.main()
