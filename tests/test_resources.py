"""Fast local checks for Win16 resource extraction and template round trips."""
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import ne
import resources
from common import fixture


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
            for index, row in enumerate(self.image['resources']):
                if row['type'].get('id') in (1, 3, 12, 14):
                    payload = self.raw[row['offset']:row['offset'] + row['size']]
                    self.assertEqual((out / 'payloads' / ('R%02d.BIN' % index)).read_bytes(), payload)
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

    def test_accelerator_without_final_record_is_rejected(self):
        with self.assertRaisesRegex(resources.FormatError, 'LAST'):
            resources.decode_accelerators(b'\x01\x4e\x00\x01\x00')

    def test_extract_rejects_paths_outside_repository(self):
        outside = ROOT.parent / (ROOT.name + '-resources-escape')
        with self.assertRaisesRegex(resources.FormatError, 'inside the repository'):
            resources.extract(str(outside))


if __name__ == '__main__':
    unittest.main()
