"""Promotion scope: unnamed static helpers (local PUBDEFs) are not targets; named ones stay."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from promote import promotion_names

SYMBOLS = dict(segments=[dict(symbols=[dict(name='_Anchor'), dict(name='_NamedStatic')])])
MODULE = dict(segments=[dict(cls='CODE', **{'class': 'CODE'}), dict(**{'class': 'CODE'})],
              publics=[dict(name='_Anchor', segment=1), dict(name='helperA', segment=1, local=True),
                       dict(name='_NamedStatic', segment=1, local=True), dict(name='stub', segment=2)])


class PromotionNames(unittest.TestCase):
    def test_unnamed_local_helper_excluded(self):
        self.assertEqual(promotion_names(MODULE, [2], SYMBOLS), {'_Anchor', '_NamedStatic'})

    def test_non_local_unknown_public_kept(self):
        module = dict(MODULE, publics=MODULE['publics'] + [dict(name='_Extra', segment=1)])
        self.assertIn('_Extra', promotion_names(module, [2], SYMBOLS))


if __name__ == '__main__':
    unittest.main()
