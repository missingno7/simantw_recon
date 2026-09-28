import json
import shutil
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import unit_composer as uc
from common import ROOT


class UnitComposerTests(unittest.TestCase):
    def test_literal_alias_is_file_scope_only(self):
        items = uc._itemize('static char first[] = "same";\nstatic char second[] = "same";\nvoid A(void) { use(first); use(second); }')
        before = [it.text for it in items if it.kind == "definition"]
        changed, notes = uc._alias_identical_strings(items)
        self.assertEqual(notes, ["second -> first (identical static string initializer)"])
        self.assertEqual([it.text for it in changed if it.kind == "definition"], before)
        self.assertIn("#define second first", [it.text for it in changed])

    def test_static_reorder_does_not_touch_member_bodies(self):
        items = uc._itemize('static char one[] = "one";\nstatic char two[] = "two";\nvoid A(void) { use(one); }')
        body = [it.text for it in items if it.kind == "definition"]
        changed = uc._placement_declarations(items, "reverse-static")
        self.assertEqual([it.text for it in changed if it.kind == "definition"], body)
        self.assertEqual([it.names[0] for it in changed if uc._static_decl(it)], ["two", "one"])

    def test_add_definition_uses_original_offset_and_keeps_other_text(self):
        items = uc._itemize('void First(void) { first(); }\nvoid Last(void) { last(); }')
        new = uc._itemize('void Middle(void) { middle(); }')[0]
        recovery = {"_First": {"offset": 10}, "_Middle": {"offset": 20}, "_Last": {"offset": 30}}
        merged = uc._insert_definition(items, new, "_Middle", ["_First", "_Middle", "_Last"], recovery)
        self.assertEqual([it.name for it in merged if it.kind == "definition"], ["First", "Middle", "Last"])
        self.assertEqual([it.text for it in merged if it.kind == "definition"][0], items[0].text)

    def test_retiring_poolstub_removes_its_prototype_and_alloc_text(self):
        items = uc._itemize('void far pool_stub_HoleBorder(void);\n'
                            '#pragma alloc_text(POOLSTUB_TEXT, pool_stub_HoleBorder)\n'
                            'void far pool_stub_HoleBorder(void) { use(poolWord); }\n'
                            'void Later(void) { later(); }')
        new = uc._itemize('void far HoleBorder(void) { body(); }')[-1]
        merged = uc._insert_definition(items, new, "_HoleBorder", ["_HoleBorder", "_Later"],
                                       {"_HoleBorder": {"offset": 10}, "_Later": {"offset": 20}})
        self.assertEqual([it.name for it in merged if it.kind == "definition"], ["HoleBorder", "Later"])
        self.assertFalse(any("pool_stub_HoleBorder" in it.text for it in merged if it.kind == "declaration"))

    def test_wrong_literal_order_is_diagnosed_and_not_accepted(self):
        items = uc._itemize('static char alpha[] = "a";\n'
                            'static char beta[] = "b";\n'
                            'void A(void) { use(alpha); use(beta); }')
        targets = {"alpha": {"offset": 7}, "beta": {"offset": 5}}
        summary = {"strict_pass": False, "placements": {}, "private_constraint_placements": [],
                   "contributions": []}
        diagnosis = uc._placement_diagnosis(summary, items, targets, "_DATA")
        self.assertTrue(any("alpha sits at candidate _DATA+0x0005; target wants beta there" in x
                            for x in diagnosis))
        self.assertTrue(any("beta sits at candidate _DATA+0x0007; target wants alpha there" in x
                            for x in diagnosis))
        failed = uc._strict_summary({"comparison": {"result": "NO_COMPLETE_MATCH", "issues": [],
                                                      "contributions": [], "private_constraint_placements": []}})
        self.assertFalse(failed["candidate_match"])

    def test_only_unanchored_members_are_reordered(self):
        items = uc._itemize('void Beta(void) { beta(); }\n'
                            'void Fixed(void) { fixed(); }\n'
                            'void Alpha(void) { alpha(); }')
        recovery = {"_Beta": {"offset": None}, "_Fixed": {"offset": 20}, "_Alpha": {"offset": None}}
        variants = uc._variants(items, 8, recovery)
        trial = next(rows for name, rows, _ in variants if name == "member-unknown-name-order")
        self.assertEqual([x.name for x in trial if x.kind == "definition"], ["Alpha", "Fixed", "Beta"])
        self.assertEqual([x.name for x in items if x.kind == "definition"], ["Beta", "Fixed", "Alpha"])

    def test_compose_records_each_bounded_arrangement_and_emits_source(self):
        session = ROOT / "build/workers/f-infra-composer/test-composer"
        if session.exists():
            shutil.rmtree(session)
        session.mkdir(parents=True)
        base = session / "base.c"
        addition = session / "addition.c"
        base.write_text('static char oldText[] = "old";\nvoid Old(void) { use(oldText); }\n', encoding="latin1")
        addition.write_text('static char newText[] = "new";\nvoid New(void) { use(newText); }\n', encoding="latin1")
        recovery = {"_Old": {"offset": 10}, "_New": {"offset": 20}}
        spec = {"component": "test:0000", "members": ["_Old"], "source": "build/workers/f-infra-composer/test-composer/base.c",
                "source_identity": uc.identity(base), "flags": ["/AL", "/G2", "/Gs", "/Oelw", "/NTTEST_TEXT"]}
        comparison = {"result": "CONFIRMED_MEMBER", "issues": [], "contributions": [], "placements": {},
                      "private_constraint_placements": [], "literal_equal": 2, "literal_compared": 2,
                      "fixups_equal": 0, "fixups_total": 0}
        report = {"results": [{"comparison": comparison, "receipt": {}}]}
        try:
            with patch.object(uc, "_latest_admitted_unit", return_value=("test_unit", spec, base.read_text(encoding="latin1"), recovery)), \
                 patch("codegen_grinder.run", return_value=report), \
                 patch.object(uc, "_promote_verify", return_value={"strict_pass": True, "exit_code": 0}):
                result = uc.compose_object("test:0000", [("_New", str(addition))], max_arrangements=3,
                                           out_dir="build/workers/f-infra-composer/test-composer/out")
            self.assertEqual(len(result["trials"]), 3)
            self.assertTrue((ROOT / result["best_source"]).is_file())
            self.assertTrue((ROOT / result["note"]).is_file())
            self.assertTrue(all(t["strict"]["strict_pass"] for t in result["trials"]))
        finally:
            shutil.rmtree(session, ignore_errors=True)


if __name__ == "__main__":
    unittest.main()
