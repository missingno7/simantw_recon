"""Fail-closed tests for the exact-region LINK 5.30 admission."""
import copy
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import image
import link_lane
import ne
from common import FormatError, fixture, read_json


class LinkLaneTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.oracle_raw = fixture('SIMANTW.EXE')
        cls.oracle = ne.parse(cls.oracle_raw)

    def test_exact_parser_regions_admit(self):
        regions = link_lane.prove_regions(self.oracle_raw, self.oracle_raw)
        proof = {'scope': link_lane.SCOPE, 'regions': regions}
        self.assertEqual(link_lane.validate_claims(proof, self.oracle_raw, self.oracle_raw), regions)
        self.assertEqual([row['kind'] for row in regions], list(link_lane.CLAIMED_REGION_KINDS))
        self.assertEqual(sum(row['oracle_range']['size'] for row in regions), 1195)

    def test_changed_claimed_byte_is_rejected(self):
        regions = link_lane.prove_regions(self.oracle_raw, self.oracle_raw)
        proof = {'scope': link_lane.SCOPE, 'regions': regions}
        changed = bytearray(self.oracle_raw)
        changed[100] ^= 1
        with self.assertRaisesRegex(FormatError, 'DOS_HEADER_AND_STUB bytes differ'):
            link_lane.validate_claims(proof, self.oracle_raw, bytes(changed))

    def test_region_outside_proven_set_is_rejected(self):
        proof = {'scope': link_lane.SCOPE,
                 'regions': link_lane.prove_regions(self.oracle_raw, self.oracle_raw)}
        proof['regions'].append({'kind': 'RELOCATION_TABLE'})
        with self.assertRaisesRegex(FormatError, 'outside the proven set'):
            link_lane.validate_claims(proof, self.oracle_raw, self.oracle_raw)

    def test_changed_source_identity_is_rejected(self):
        expected = link_lane.source_identity()
        changed = copy.deepcopy(expected)
        changed[link_lane.DEF_SOURCE]['sha256'] = '0' * 64
        with self.assertRaisesRegex(FormatError, 'source identity changed'):
            link_lane.require_source_identity(expected, current=changed)

    def test_changed_toolchain_identity_is_rejected(self):
        expected = link_lane.toolchain_identity()
        changed = copy.deepcopy(expected)
        name = next(iter(changed['files']))
        changed['files'][name]['sha256'] = '0' * 64
        with self.assertRaisesRegex(FormatError, 'toolchain identity changed'):
            link_lane.require_toolchain_identity(expected, current=changed)

    def _admitted(self):
        record = read_json(ROOT / 'src/recovery.json').get('link')
        if not record:
            self.skipTest('LINK admission has not been published')
        proof, output = link_lane.load_admission(record)
        self.assertIsNotNone(proof, output)
        self.assertIsInstance(output, bytes)
        return proof, output

    def test_recorded_candidate_proves_exact_regions(self):
        proof, output = self._admitted()
        regions = link_lane.validate_claims(proof, self.oracle_raw, output)
        self.assertEqual(len(regions), 5)
        self.assertEqual(sum(row['oracle_range']['size'] for row in regions), 1195)

    def test_changed_recorded_output_makes_image_not_exact(self):
        proof, output = self._admitted()
        changed = bytearray(output)
        changed[100] ^= 1
        with patch.object(image.link_lane, 'load_admission', return_value=(proof, bytes(changed))):
            report = image.build(write=False)
        self.assertEqual(report['status'], 'NOT_EXACT')
        self.assertTrue(any('stored LINK bytes differ from the oracle' in row for row in report['problems']))

    def test_relocation_tables_and_chain_words_remain_debt(self):
        proof, _ = self._admitted()
        kinds = {row['kind'] for row in proof['regions']}
        self.assertNotIn('SEGMENT', kinds)
        self.assertNotIn('RELOCATION_TABLE', kinds)
        report = image.build(write=False)
        self.assertEqual(report['status'], 'HYBRID_EXACT')
        self.assertEqual(report['owned']['LINK'], 1195)
        chain_bytes = sum(2 * len(relocation['sites'])
                          for segment in self.oracle['segments']
                          for relocation in segment['relocations'] if not relocation['additive'])
        self.assertEqual(chain_bytes, 16064)
        self.assertEqual(report['debt']['LINK'] - chain_bytes, 8506)


if __name__ == '__main__':
    unittest.main()
