import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import tu_assembly as tu


class TuAssemblyParsingTests(unittest.TestCase):
    def test_split_items_keeps_member_definition_text_and_names(self):
        source = 'extern int far State;\nstatic char label[] = "x";\nvoid far A(void) { State++; }'
        items = tu.split_items(source)
        self.assertEqual([item["kind"] for item in items], ["declaration", "declaration", "definition"])
        self.assertEqual(items[-1]["name"], "A")
        self.assertIn("State++", items[-1]["text"])

    def test_declaration_order_constraint_moves_only_named_declaration(self):
        declarations = [
            {"names": ["_Later"], "text": "extern int _Later;"},
            {"names": ["_Earlier"], "text": "extern int _Earlier;"},
        ]
        ordered = tu.apply_declaration_order(declarations, [{"before": "_Earlier", "after": "_Later"}])
        self.assertEqual([item["names"][0] for item in ordered], ["_Earlier", "_Later"])

    def test_split_items_accepts_only_pool_scaffold_alloc_text_pragma(self):
        items = tu.split_items('#pragma alloc_text(RUN2_TEXT, A, B)\nvoid A(void) { }')
        self.assertEqual(items[0]["text"], "#pragma alloc_text(RUN2_TEXT, A, B)")
        with self.assertRaises(tu.FormatError):
            tu.split_items('#pragma optimize("e")\nvoid A(void) { }')


if __name__ == "__main__":
    unittest.main()
