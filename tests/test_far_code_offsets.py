"""OMF LOC 5 far code offsets: statically linked offset plus validated selector half."""
import copy
import json
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture
import ne, mapsym
from library_match import compare_member, import_symbols

class FarCodeOffsetTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = json.loads((ROOT/'evidence/topology/supervisor-far-code-offsets/loc5-module.json').read_text())
        cls.raw = fixture('SIMANTW.EXE')
        cls.image = ne.parse(cls.raw)
        cls.symbols = mapsym.parse(fixture('SIMANTW.SYM'))
        cls.imports = import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')

    def check(self, module=None, image=None, symbols=None):
        return compare_member(module or self.module, self.raw, image or self.image,
                              symbols or self.symbols, self.imports)

    def loc5(self, module, name='_win_DrawEditWindow'):
        return next(f for f in module['fixups'] if f['location_type']==5 and f['target']['name']==name)

    def selector(self, module, name='_win_DrawEditWindow'):
        return next(f for f in module['fixups'] if f['location_type']==2 and f['target']['name']==name)

    def test_eleven_far_code_offsets_confirm_with_selector_partners(self):
        result = self.check()
        self.assertEqual(result['result'], 'CONFIRMED_MEMBER')
        rows = [f for c in result['contributions'] for f in c['fixups'] if f['omf']['location_type']==5]
        self.assertEqual(len(rows), 11)
        self.assertTrue(all(f['equal'] for f in rows))
        self.assertEqual(result['fixups_equal'], result['fixups_total'])
        # F2 naming the same external is the equivalent explicit frame.
        module = copy.deepcopy(self.module); f = self.loc5(module)
        f.update(frame_method=2, frame_index=f['target_index'])
        self.assertEqual(self.check(module)['result'], 'CONFIRMED_MEMBER')

    def test_wrong_target_symbol_rejects(self):
        module = copy.deepcopy(self.module)
        self.loc5(module)['target']['name'] = '_win_DrawMapWindow'
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_wrong_frame_rejects(self):
        for frame in (dict(frame_method=4, frame_index=None), dict(frame_method=1, frame_index=1), dict(frame_method=2, frame_index=1)):
            module = copy.deepcopy(self.module); self.loc5(module).update(frame)
            self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_wrong_offset_rejects(self):
        module = copy.deepcopy(self.module); self.loc5(module)['displacement'] = 2
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_self_relative_rejects(self):
        module = copy.deepcopy(self.module); self.loc5(module)['self_relative'] = True
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_wrong_relocation_kind_rejects(self):
        # A selector site carries an NE obligation; a LOC 5 offset must not claim it.
        module = copy.deepcopy(self.module); f = self.loc5(module); sel = self.selector(module)
        f['offset'], sel['offset'] = sel['offset'], f['offset']
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')
        module = copy.deepcopy(self.module); self.loc5(module)['location_type'] = 2
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_wrong_segment_is_caught_by_selector_half(self):
        # Same offset in another segment: the selector obligation names segment 3, not 1.
        symbols = copy.deepcopy(self.symbols)
        for segment in symbols['segments']:
            segment['symbols'] = [p for p in segment['symbols'] if p['name']!='_win_DrawEditWindow']
        symbols['segments'][0]['symbols'].append(dict(name='_win_DrawEditWindow', offset=5360))
        result = self.check(symbols=symbols)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('unpaired far code offset' in issue for issue in result['issues']))

    def test_unpaired_offset_rejects(self):
        module = copy.deepcopy(self.module); sel = self.selector(module)
        module['fixups'].remove(sel)
        result = self.check(module)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertTrue(any('unpaired far code offset' in issue for issue in result['issues']))
        row = next(f for c in result['contributions'] for f in c['fixups'] if f['omf']['location_type']==5 and f['omf']['target']['name']=='_win_DrawEditWindow')
        self.assertFalse(row['equal'])

    def test_data_target_is_not_a_far_code_offset(self):
        symbols = copy.deepcopy(self.symbols)
        for segment in symbols['segments']:
            segment['symbols'] = [p for p in segment['symbols'] if p['name']!='_win_DrawEditWindow']
        symbols['segments'][7]['symbols'].append(dict(name='_win_DrawEditWindow', offset=5360))
        result = self.check(symbols=symbols)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')

    def test_body_change_still_rejects(self):
        module = copy.deepcopy(self.module)
        raw = bytearray.fromhex(module['segments'][0]['data_hex']); raw[1] ^= 1
        module['segments'][0]['data_hex'] = raw.hex()
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

if __name__ == '__main__': unittest.main()
