"""F5/T0 private named-segment inference retains complete proof obligations."""
import copy
import json
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from common import ROOT, fixture, FormatError
import ne, mapsym
from library_match import compare_member, import_symbols

class NamedFrameTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = json.loads((ROOT/'evidence/topology/supervisor-mm-segment/frame5-module.json').read_text())
        cls.raw = fixture('SIMANTW.EXE')
        cls.image = ne.parse(cls.raw)
        cls.symbols = mapsym.parse(fixture('SIMANTW.SYM'))
        cls.imports = import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')

    def check(self, module=None, image=None, symbols=None):
        return compare_member(module or self.module, self.raw, image or self.image,
                              symbols or self.symbols, self.imports)

    def private_fixup(self, module):
        return next(f for f in module['fixups'] if f['segment']==1 and f['target_method']==0 and f['target_index']==5)

    def test_f5_matches_and_is_equivalent_to_explicit_target_frame(self):
        result = self.check()
        self.assertEqual(result['result'], 'STRONGLY_SUPPORTED_MEMBER')
        self.assertEqual(result['placements']['5'], [8, 0x8d08])
        self.assertEqual(result['fixups_equal'], result['fixups_total'])
        module = copy.deepcopy(self.module)
        fixup = self.private_fixup(module)
        fixup.update(frame_method=0, frame_index=5)
        self.assertEqual(self.check(module)['placements'], result['placements'])
        self.assertEqual(self.check(module)['result'], result['result'])

    def test_unknown_ambiguous_and_wrong_named_segment_reject(self):
        for action in ('unknown', 'ambiguous', 'wrong'):
            module = copy.deepcopy(self.module)
            symbols = copy.deepcopy(self.symbols)
            if action=='unknown': module['segments'][4]['name']='NO_SUCH_SEGMENT'
            elif action=='ambiguous': symbols['segments'][8]['name']='SIMANT_DATA_GROUP'
            else: module['segments'][4]['name']='PACK'
            self.assertEqual(self.check(module, symbols=symbols)['result'], 'NO_COMPLETE_MATCH')

    def test_unsupported_frames_and_self_relative_reject(self):
        for action in ('location_frame', 'wrong_explicit', 'self_relative'):
            module = copy.deepcopy(self.module);fixup=self.private_fixup(module)
            if action=='location_frame': fixup['frame_method']=4
            elif action=='wrong_explicit': fixup.update(frame_method=0, frame_index=1)
            else: fixup['self_relative']=True
            self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_wrong_missing_or_additive_selector_reject(self):
        for action in ('wrong', 'missing', 'additive'):
            image=copy.deepcopy(self.image)
            r=next(r for r in image['segments'][9]['relocations'] if 0xbf78 in r['sites'])
            if action=='wrong': r['target']['segment']=9
            elif action=='missing': r['sites'].remove(0xbf78)
            else: r['additive']=True
            self.assertEqual(self.check(image=image)['result'], 'NO_COMPLETE_MATCH')

    def test_initialized_private_bytes_are_checked(self):
        module=copy.deepcopy(self.module)
        module['segments'][4].update(initialized_ranges=[[0,2]], data_hex='0000')
        self.assertEqual(self.check(module)['result'], 'STRONGLY_SUPPORTED_MEMBER')
        module['segments'][4]['data_hex']='0100'
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

    def test_conflicting_private_constraints_reject(self):
        module=copy.deepcopy(self.module)
        other=copy.deepcopy(self.private_fixup(module));other['displacement']=2
        module['fixups'].append(other)
        result=self.check(module)
        self.assertEqual(result['result'], 'NO_COMPLETE_MATCH')
        self.assertIn('conflicting private placement constraints SIMANT_DATA_GROUP',result['issues'])

    def test_out_of_bounds_contribution_rejects(self):
        module=copy.deepcopy(self.module)
        module['segments'][4]['length']=65536
        with self.assertRaises(FormatError): self.check(module)

    def test_body_change_still_rejects(self):
        module=copy.deepcopy(self.module)
        raw=bytearray.fromhex(module['segments'][0]['data_hex']);raw[1]^=1
        module['segments'][0]['data_hex']=raw.hex()
        self.assertEqual(self.check(module)['result'], 'NO_COMPLETE_MATCH')

if __name__=='__main__': unittest.main()
