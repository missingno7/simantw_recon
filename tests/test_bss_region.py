"""A derived BSS placement is only meaningful inside the original BSS region."""
import copy
import json
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture
import ne, mapsym
from library_match import compare_member, import_symbols

class BssRegionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = json.loads((ROOT/'evidence/topology/supervisor-bss-region/DrawYard-old-module.json').read_text())
        cls.raw = fixture('SIMANTW.EXE'); cls.image = ne.parse(cls.raw)
        cls.symbols = mapsym.parse(fixture('SIMANTW.SYM')); cls.imports = import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')

    def check(self, module=None, symbols=None):
        return compare_member(module or self.module, self.raw, self.image, symbols or self.symbols, self.imports)

    def test_private_static_placed_inside_public_data_is_rejected(self):
        # The old DrawYard draft declared win_hwnd[25] (DGROUP 48344, below _edata) as a private BSS word.
        result = self.check()
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertIn('_BSS contribution placed outside the original BSS region', result['issues'])

    def test_bss_region_symbols_are_required(self):
        symbols = copy.deepcopy(self.symbols)
        for segment in symbols['segments']:
            segment['symbols'] = [p for p in segment['symbols'] if p['name'] not in ('_edata', '_end')]
        self.assertEqual(self.check(symbols=symbols)['result'], 'NO_COMPLETE_MATCH')

    def test_bss_inside_region_still_admits(self):
        # Move the original BSS region symbolically to cover the derived word: the rule alone then passes.
        symbols = copy.deepcopy(self.symbols)
        for p in symbols['segments'][9]['symbols']:
            if p['name'] == '_edata':
                p['offset'] = 48300
        result = self.check(symbols=symbols)
        self.assertNotIn('_BSS contribution placed outside the original BSS region', result['issues'])

if __name__ == '__main__': unittest.main()
