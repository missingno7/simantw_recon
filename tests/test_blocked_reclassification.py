"""Fresh blocker labels must respect the native TU source gate."""

import json
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from blocked_reclassification import classify_fresh
from common import ROOT


class SourceEligibilityTests(unittest.TestCase):
    def classify_preserved(self, result):
        comparison = json.loads((ROOT / result).read_text(encoding="utf-8"))["results"][0]["comparison"]
        return classify_fresh(comparison, "_fixture", {}, [], None, {}, {})

    def test_matching_shape_with_invented_externs_is_ineligible(self):
        category, _, evidence = self.classify_preserved(
            "evidence/recovery/workflow/jobs/ClearHistory-2a7aae3cf9/attempt03/results.json")
        self.assertEqual(category, "SOURCE_BINDING_INELIGIBLE")
        self.assertEqual(evidence["opcode_matches"], evidence["opcode_total"])
        self.assertEqual(len(evidence["source_gate"]["unknown_externals"]), 9)

    def test_unresolved_private_selectors_remain_body_eligible(self):
        category, _, evidence = self.classify_preserved(
            "evidence/recovery/workflow/jobs/GetMyInitialRandDir-72875fbed4/attempt07/results.json")
        self.assertEqual(category, "BODY_EXACT_LAYOUT_BLOCKED")
        self.assertNotIn("source_gate", evidence)


if __name__ == "__main__":
    unittest.main()
