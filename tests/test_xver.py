"""Cross-version DOS references are optional supporting evidence: absent data never breaks triage."""
import sys
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import xver


class XverTests(unittest.TestCase):
    def test_missing_dos_project_yields_no_reference(self):
        with mock.patch.object(xver, 'DOS_ROOT', ROOT / 'build/no-such-dos-project'):
            xver.exact_dos_functions.cache_clear(); xver.pairs.cache_clear()
            try:
                self.assertEqual(xver.references(), [])
                self.assertIsNone(xver.triage_evidence('_DigTileB'))
            finally:
                xver.exact_dos_functions.cache_clear(); xver.pairs.cache_clear()

    def test_references_join_exact_claims_by_address_and_rank_confidence(self):
        exact = {'root:14EE:0519': dict(name='f_14EE_0519', source='src/root/m14EE.c', size=302, flags=['/AL'], provenance='EXACT_NATURAL')}
        pairs = [dict(win16='_DigTileB', dos='f', dos_address='root:14EE:0519', confidence='HIGH'),
                 dict(win16='_DigTileB', dos='g', dos_address='root:0000:0000', confidence='CONFIRMED')]
        with mock.patch.object(xver, 'exact_dos_functions', lambda: exact), mock.patch.object(xver, 'pairs', lambda: pairs):
            rows = xver.references('_DigTileB')
            self.assertEqual([r['dos_function'] for r in rows], ['f_14EE_0519'])
            self.assertEqual(xver.triage_evidence('_DigTileB')['confidence'], 'HIGH')


if __name__ == '__main__':
    unittest.main()
