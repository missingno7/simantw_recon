"""Exact-body classification must respect the native TU source gate."""

import json
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from common import ROOT
from tu_assembly import body_exact


def fixture(name):
    return json.loads((ROOT / "tests/fixtures" / name).read_text(encoding="utf-8"))["comparison"]


class SourceEligibilityTests(unittest.TestCase):
    def test_matching_shape_with_invented_externs_is_not_an_exact_body(self):
        comparison = fixture("ClearHistory-attempt03.json")
        diagnostic = comparison["diagnostic"]
        self.assertEqual(diagnostic["opcode_matches"], diagnostic["opcode_total"])
        self.assertFalse(body_exact(comparison))

    def test_unresolved_private_selectors_remain_body_exact(self):
        comparison = fixture("GetMyInitialRandDir-attempt07.json")
        self.assertEqual(comparison["result"], "NO_COMPLETE_MATCH")
        self.assertTrue(body_exact(comparison))


if __name__ == "__main__":
    unittest.main()
