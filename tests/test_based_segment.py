"""An empty named segment from extern __based(__segname("X")) declarations names the original segment X."""
import copy
import json
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture
import ne, mapsym
from library_match import compare_member, import_symbols

class BasedSegmentTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = json.loads((ROOT/'evidence/topology/supervisor-based-segment/randworld-unit-module.json').read_text())
        cls.raw = fixture('SIMANTW.EXE'); cls.image = ne.parse(cls.raw)
        cls.symbols = mapsym.parse(fixture('SIMANTW.SYM')); cls.imports = import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
        cls.based = next(s for s in cls.module['segments'] if s['name'] == 'SIMANT_DATA_GROUP')

    def check(self, module=None, symbols=None):
        return compare_member(module or self.module, self.raw, self.image, symbols or self.symbols, self.imports)

    def test_empty_named_segment_selector_fixups_admit(self):
        self.assertEqual(self.based['length'], 0)
        result = self.check()
        self.assertEqual(result['result'], 'STRONGLY_SUPPORTED_MEMBER')
        rows = [f for c in result['contributions'] for f in c['fixups'] if f['omf']['target_method'] == 0 and f['omf']['target_index'] == self.based['index']]
        self.assertEqual(len(rows), 3)
        self.assertTrue(all(f['equal'] and f['target']['segment'] == 8 for f in rows))

    def test_wrong_or_ambiguous_segment_name_rejects(self):
        module = copy.deepcopy(self.module); module['segments'][self.based['index'] - 1]['name'] = 'PACK'
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')
        module = copy.deepcopy(self.module); module['segments'][self.based['index'] - 1]['name'] = 'NO_SUCH_SEGMENT'
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')
        symbols = copy.deepcopy(self.symbols); symbols['segments'][8]['name'] = 'SIMANT_DATA_GROUP'
        self.assertEqual(self.check(symbols=symbols)['result'], 'NO_COMPLETE_MATCH')

    def test_missing_selector_obligation_rejects(self):
        image = copy.deepcopy(self.image)
        r = next(r for r in image['segments'][6]['relocations'] if 23216 + 0x49 in r['sites'])
        r['sites'].remove(23216 + 0x49)
        self.assertEqual(compare_member(self.module, self.raw, image, self.symbols, self.imports)['result'], 'NO_COMPLETE_MATCH')

if __name__ == '__main__': unittest.main()
