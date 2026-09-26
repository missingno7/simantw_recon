import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import link_image
import omf


class LinkImageTests(unittest.TestCase):
    def test_rawdebt_omf_round_trip_preserves_fixup_semantics(self):
        raw = link_image.build_omf(
            'RAWDEBT_TEST', 'SIMANT_MODULE', 'CODE', bytes(range(16)),
            publics=[('_raw_public', 0)], externals=['_target'],
            fixups=[{'site': 4, 'width': 2, 'location_type': 5,
                     'frame_method': 0, 'frame_index': 1,
                     'target_method': 2, 'target_index': 1,
                     'displacement': 0x1234}],
        )
        parsed = omf.parse(raw)
        self.assertEqual(parsed['name'], 'RAWDEBT_TEST')
        self.assertEqual(parsed['segments'][0]['data_hex'], bytes(range(16)).hex())
        self.assertEqual(parsed['publics'][0]['name'], '_raw_public')
        fixup = parsed['fixups'][0]
        self.assertEqual((fixup['offset'], fixup['location_type'], fixup['width']), (4, 5, 2))
        self.assertFalse(fixup['self_relative'])
        self.assertEqual(fixup['target'], {'kind': 'external', 'name': '_target'})
        self.assertEqual(fixup['displacement'], 0x1234)

    def test_rawdebt_fixup_without_displacement(self):
        raw = link_image.build_omf(
            'RAWDEBT_TEST', 'SIMANT_MODULE', 'CODE', b'\x00\x00',
            fixups=[{'site': 0, 'width': 2, 'location_type': 2,
                     'frame_method': 0, 'frame_index': 1,
                     'target_method': 0, 'target_index': 1,
                     'displacement': None}],
        )
        fixup = omf.parse(raw)['fixups'][0]
        self.assertFalse(fixup['self_relative'])
        self.assertEqual(fixup['displacement'], 0)

    def test_rawdebt_segments_use_byte_alignment(self):
        module = omf.parse(link_image.build_omf(
            'RAWDEBT_ALIGN', 'SIMANT_MODULE', 'CODE', b'\x01\x02\x03'))
        self.assertEqual(module['segments'][0]['alignment'], 1)

    def test_link_map_labels_preserve_physical_segment_and_class(self):
        labels = link_image._map_segment_labels(
            ' 0001:0000 05C04H     SIMANT_MODULE          CODE\n'
            ' 000B:C67A 00082H     MSG                    MSG\n')
        self.assertEqual(labels[1][0], {
            'offset': 0, 'length': 0x5C04, 'name': 'SIMANT_MODULE', 'class': 'CODE'})
        self.assertEqual(labels[11][0]['name'], 'MSG')

    def test_segment_relative_frame_uses_the_internal_target_segdef(self):
        target = {'frame_method': 0, 'frame_index': None, 'target_index': 2}
        self.assertIs(link_image._pair_segment_frame(target), target)
        self.assertEqual(target['frame_index'], 2)

    def test_def_records_segment_defaults_and_named_exports(self):
        image = {
            'header': {'heap_size': 4096, 'stack_size': 8192, 'cs': 4, 'ip': 0x61, 'other_flags': 0, 'return_thunk_offset': 0, 'segment_reference_offset': 0},
            'resident_names': [{'name': 'SIMANT', 'ordinal': 0},
                               {'name': '___ExportedStub', 'ordinal': 2}],
            'nonresident_names': [{'name': 'SimAnt', 'ordinal': 0},
                                  {'name': 'MAINWNDPROC', 'ordinal': 1}],
            'entries': [{'ordinal': 1, 'segment': 1, 'offset': 0x20, 'flags': 1},
                        {'ordinal': 2, 'segment': 2, 'offset': 0x40, 'flags': 1}],
            'segments': [{'number': 1, 'kind': 'CODE', 'flags': 7440},
                         {'number': 2, 'kind': 'DATA', 'flags': 3409}],
        }
        symbols = {'segments': [
            {'number': 1, 'name': 'SIMANT_MODULE', 'symbols': [{'name': '_WndProc', 'offset': 0x20}]},
            {'number': 2, 'name': 'DGROUP', 'symbols': []},
        ]}
        text, evidence, exports = link_image.build_def(image, symbols)
        self.assertIn('CODE MOVEABLE DISCARDABLE', text)
        self.assertIn('SIMANT_MODULE CLASS \'CODE\' LOADONCALL MOVEABLE DISCARDABLE', text)
        self.assertIn('MAINWNDPROC=_WndProc @1', text)
        self.assertIn('___ExportedStub @2 RESIDENTNAME', text)
        self.assertEqual([x['ordinal'] for x in exports], [1, 2])
        self.assertTrue(all('source' in row for row in evidence))

    def test_region_byte_comparison_uses_both_sides(self):
        facts = link_image._byte_region_facts(b'\x01\x02\x03', b'\x01\x04\x03\x05')
        self.assertFalse(facts['equal'])
        self.assertEqual(facts['matching_bytes_at_region_offsets'], 2)
        self.assertEqual(facts['common_prefix_bytes'], 1)

    def test_runtime_claim_splits_rawdebt_and_keeps_chain_sites_outside(self):
        spans = [{'start': 10, 'end': 30, 'chain_sites': [12, 18, 26]}]
        claims = [{'start': 15, 'end': 20}, {'start': 24, 'end': 26}]
        self.assertEqual(link_image._subtract_spans(spans, claims), [
            {'start': 10, 'end': 15, 'chain_sites': [12]},
            {'start': 20, 'end': 24, 'chain_sites': []},
            {'start': 26, 'end': 30, 'chain_sites': [26]},
        ])


if __name__ == '__main__':
    unittest.main()
