"""Fast local checks for Win16 resource extraction and template round trips."""
import sys
import tempfile
import unittest
import copy
from unittest.mock import patch
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import ne
import resources
from common import fixture, read_json


class ResourceRoundTripTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.raw = fixture('SIMANTW.EXE')
        cls.image = ne.parse(cls.raw)

    def test_fixture_dialogs_and_accelerator_round_trip(self):
        self.assertEqual(len(self.image['resources']), 41)
        for row in self.image['resources']:
            payload = self.raw[row['offset']:row['offset'] + row['size']]
            if row['type_name'] == 'DIALOG':
                model = resources.decode_dialog(payload)
                self.assertEqual(resources.encode_dialog(model), payload, row['identity'])
                self.assertEqual(len(model['controls']), model['count'])
            elif row['type_name'] == 'ACCELERATOR':
                model = resources.decode_accelerators(payload)
                self.assertEqual(resources.encode_accelerators(model), payload, row['identity'])
                self.assertTrue(model['entries'][-1]['flags'] & 0x80)

    def test_decompiler_writes_text_and_each_opaque_payload(self):
        scratch = ROOT / 'build/workers/resources/test-scratch'
        scratch.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='resources-test-', dir=scratch) as temp:
            out = Path(temp)
            manifest, script_path = resources.build_script(self.image, self.raw, out)
            script = script_path.read_text(encoding='latin1')
            self.assertEqual(manifest['resource_count'], 41)
            self.assertIn('\"OPEN\" DIALOG', script)
            self.assertIn('\"SAVEAS\" DIALOG', script)
            self.assertIn('\"ACCELERATORTABLE\" ACCELERATORS', script)
            binary_rows = [r for r in self.image['resources'] if r['type_name'] not in ('DIALOG', 'ACCELERATOR', 'STRING')]
            self.assertEqual(len(list((out / 'payloads').glob('*.CUR'))), 8)
            self.assertEqual(len(list((out / 'payloads').glob('*.ICO'))), 11)
            for group_index, group in enumerate(r for r in self.image['resources'] if r['type']['id'] in (12, 14)):
                is_cursor = group['type']['id'] == 12
                file_path = out / 'payloads' / ('R%02d.%s' % (group_index, 'CUR' if is_cursor else 'ICO'))
                image_file = file_path.read_bytes()
                count = int.from_bytes(image_file[4:6], 'little')
                self.assertEqual(count, 1)
                entry = image_file[6:22]
                size = int.from_bytes(entry[8:12], 'little')
                offset = int.from_bytes(entry[12:16], 'little')
                group_data = self.raw[group['offset']:group['offset'] + group['size']]
                leaf_id = int.from_bytes(group_data[18:20], 'little')
                leaf_type = 1 if is_cursor else 3
                leaf = next(r for r in self.image['resources']
                            if r['type'].get('id') == leaf_type and r['identity'].get('id') == leaf_id)
                leaf_data = self.raw[leaf['offset']:leaf['offset'] + leaf['size']]
                expected_image = leaf_data[4:4 + size] if is_cursor else leaf_data[:size]
                self.assertEqual(image_file[offset:offset + size], expected_image)
            for row in binary_rows:
                payload = self.raw[row['offset']:row['offset'] + row['size']]
                self.assertEqual(__import__('hashlib').sha256(payload).hexdigest(), row['sha256'])

    def test_nested_menu_round_trip(self):
        model = {
            'version': 0, 'offset': 0, 'padding': b'', 'trailer': b'',
            'items': [
                {'flags': resources.MENU_POPUP, 'id': None, 'text': '&File', 'children': [
                    {'flags': 0, 'id': 101, 'text': '&Open', 'children': None},
                    {'flags': resources.MENU_SEPARATOR, 'id': 0,
                     'text': '', 'children': None},
                    {'flags': resources.MENU_END, 'id': 102, 'text': 'E&xit', 'children': None},
                ]},
                {'flags': resources.MENU_END, 'id': 200, 'text': '&Help', 'children': None},
            ],
        }
        encoded = resources.encode_menu(model)
        decoded = resources.decode_menu(encoded)
        self.assertEqual(decoded, model)
        source = resources.menu_source(
            {'identity': {'name': 'MAINMENU'}, 'flags': 0x1C30}, decoded)
        self.assertIn('"MAINMENU" MENU', source)
        self.assertIn('POPUP "&File"', source)
        self.assertIn('MENUITEM SEPARATOR', source)
        self.assertIn('MENUITEM "E&xit", 102', source)

    def test_font_rcdata_and_custom_numeric_resources_use_files(self):
        scratch = ROOT / 'build/workers/resources/test-scratch'
        scratch.mkdir(parents=True, exist_ok=True)
        resources_in = [
            {'type': {'id': 8}, 'type_name': 'FONT', 'identity': {'id': 7},
             'flags': 0x1C10, 'flag_names': [], 'size': 4, 'sha256': '', 'offset': 0},
            {'type': {'id': 10}, 'type_name': 'RCDATA', 'identity': {'id': 8},
             'flags': 0x1C10, 'flag_names': [], 'size': 3, 'sha256': '', 'offset': 4},
            {'type': {'id': 0x123}, 'type_name': 'CUSTOM', 'identity': {'name': 'CUSTOMDATA'},
             'flags': 0x1C10, 'flag_names': [], 'size': 2, 'sha256': '', 'offset': 7},
        ]
        image = {'resources': resources_in, 'resource_alignment_shift': 9}
        payload = b'FONTRCDxx'
        with tempfile.TemporaryDirectory(prefix='resources-binary-', dir=scratch) as temp:
            out = Path(temp)
            _, script_path = resources.build_script(image, payload, out)
            script = script_path.read_text(encoding='latin1')
            self.assertIn('7 FONT', script)
            self.assertIn('8 RCDATA', script)
            self.assertIn('"CUSTOMDATA" 291', script)
            self.assertEqual((out / 'payloads/R00.FNT').read_bytes(), b'FONT')
            self.assertEqual((out / 'payloads/R01.BIN').read_bytes(), b'RCD')
            self.assertEqual((out / 'payloads/R02.BIN').read_bytes(), b'xx')

    def test_accelerator_without_final_record_is_rejected(self):
        with self.assertRaisesRegex(resources.FormatError, 'LAST'):
            resources.decode_accelerators(b'\x01\x4e\x00\x01\x00')

    def test_extract_rejects_paths_outside_repository(self):
        outside = ROOT.parent / (ROOT.name + '-resources-escape')
        with self.assertRaisesRegex(resources.FormatError, 'inside the repository'):
            resources.extract(str(outside))


class ResourceAdmissionMappingTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.oracle_raw = fixture('SIMANTW.EXE')
        cls.oracle = ne.parse(cls.oracle_raw)
        cls.script = (ROOT / 'src/resources/SIMANTW.RC').read_bytes()
        cls.candidate, cls.candidate_raw = cls.make_candidate()

    @classmethod
    def make_candidate(cls):
        rows = [copy.deepcopy(row) for row in cls.oracle['resources']]
        occurrence = {}
        for row in rows:
            typ = row['type'].get('id')
            if typ in resources.NAMED_RC_TYPES.values():
                rank = occurrence.get(typ, 0) + 1
                occurrence[typ] = rank
                row['identity'] = {'id': rank}
        table_offset = len(cls.oracle_raw)
        table = {'type': {'id': 15}, 'identity': {'id': 1}, 'offset': table_offset,
                 'size': 512, 'flags': 0x1C30}
        # RC 3.00 emits its generated name table before the mapped resources.
        candidate_rows = [table] + rows
        raw = cls.oracle_raw + bytes(512)
        return {'resources': candidate_rows,
                'resource_alignment_shift': cls.oracle['resource_alignment_shift']}, raw

    def test_exact_payloads_map_and_table_stays_uncredited(self):
        result = resources.map_payloads(self.oracle_raw, self.oracle, self.candidate_raw,
                                        self.candidate, self.script)
        self.assertEqual(result['resource_count'], 41)
        self.assertEqual(result['compiled_resource_count'], 42)
        self.assertEqual(len(result['resources']), 41)
        self.assertFalse(result['table_credit'])
        self.assertEqual(result['uncredited'][0]['type'], ['id', 15])

    def test_changed_payload_byte_is_rejected(self):
        changed = bytearray(self.candidate_raw)
        first = self.candidate['resources'][1]
        changed[first['offset']] ^= 1
        with self.assertRaisesRegex(resources.FormatError, 'payload differs'):
            resources.map_payloads(self.oracle_raw, self.oracle, bytes(changed), self.candidate, self.script)

    def test_missing_resource_is_rejected(self):
        candidate = copy.deepcopy(self.candidate)
        candidate['resources'].pop()
        with self.assertRaisesRegex(resources.FormatError, 'missing resources'):
            resources.map_payloads(self.oracle_raw, self.oracle, self.candidate_raw, candidate, self.script)

    def test_extra_resource_is_rejected(self):
        candidate = copy.deepcopy(self.candidate)
        extra = copy.deepcopy(candidate['resources'][-1])
        extra['identity'] = {'id': 99}
        candidate['resources'].append(extra)
        candidate_raw = self.candidate_raw + bytes(extra['size'])
        extra['offset'] = len(self.candidate_raw)
        with self.assertRaisesRegex(resources.FormatError, 'extra resources'):
            resources.map_payloads(self.oracle_raw, self.oracle, candidate_raw, candidate, self.script)

    def test_ambiguous_compiled_identity_is_rejected(self):
        candidate = copy.deepcopy(self.candidate)
        # Two GROUP_CURSOR rows now claim the same compiled ordinal.
        candidate['resources'][2]['identity'] = dict(candidate['resources'][1]['identity'])
        with self.assertRaisesRegex(resources.FormatError, 'ambiguous duplicate'):
            resources.map_payloads(self.oracle_raw, self.oracle, self.candidate_raw, candidate, self.script)

    def test_changed_source_identity_is_rejected(self):
        expected = resources.source_identity()
        changed = copy.deepcopy(expected)
        source = next(iter(changed['files']))
        changed['files'][source]['sha256'] = '0' * 64
        with self.assertRaisesRegex(resources.FormatError, 'source identity changed'):
            resources.require_source_identity(changed)

    def test_image_credits_payloads_and_keeps_table_debt(self):
        record = read_json(ROOT / 'src/recovery.json').get('resources')
        if not record:
            self.skipTest('resource admission has not been published yet')
        import image
        report = image.build(debt=True, write=False)
        proof, issue = resources.load_admission(record)
        self.assertIsNotNone(proof, issue)
        self.assertEqual(report['status'], 'HYBRID_EXACT')
        self.assertEqual(report['owned']['RESOURCES'],
                         sum(row['oracle_range']['size'] for row in proof['resources']))
        self.assertEqual(report['debt']['RESOURCES'], 722)
        self.assertFalse(proof['table_credit'])

    def test_changed_recorded_payload_makes_hybrid_image_not_exact(self):
        record = read_json(ROOT / 'src/recovery.json').get('resources')
        if not record:
            self.skipTest('resource admission has not been published yet')
        proof, issue = resources.load_admission(record)
        self.assertIsNotNone(proof, issue)
        output = bytearray((ROOT / proof['placement_output']['path']).read_bytes())
        first = proof['resources'][0]['compiled_range']['start']
        output[first] ^= 1
        import image
        with patch.object(image.resource_lane, 'load_admission', return_value=(proof, bytes(output))):
            report = image.build(write=False)
        self.assertEqual(report['status'], 'NOT_EXACT')
        self.assertTrue(any('payload bytes differ' in problem for problem in report['problems']))


if __name__ == '__main__':
    unittest.main()
