"""Focused regression tests for the MSC 7 Win16 first-draft lifter."""
from __future__ import annotations

import json
import subprocess
import sys
from types import SimpleNamespace
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import lift


def _ins(mnemonic: str, operands: str = ""):
    return lift.Ins(0, 1, mnemonic, operands, None, {})


def test_prologue_recognizers_cover_bp_enter_and_windows_export():
    bp = lift.recognize_prologue([_ins("push", "bp"), _ins("mov", "bp, sp"), _ins("push", "si")])
    enter = lift.recognize_prologue([_ins("enter", "4, 0"), _ins("push", "di")])
    win = lift.recognize_prologue([_ins("inc", "bp"), _ins("push", "ds"), _ins("mov", "bp, sp")])
    assert (bp["kind"], bp["body_start"], bp["saved"]) == ("bp", 3, ["si"])
    assert (enter["kind"], enter["frame_size"], enter["saved"]) == ("enter", 4, ["di"])
    assert (win["kind"], win["body_start"]) == ("windows_far_export", 2)


def test_branch_signedness_and_far_return_recognizers():
    assert "<" in lift.condition_text("jl", "dx", "96", 2, True)
    assert "unsigned int" in lift.condition_text("jb", "ax", "3", 2, False)
    far, pascal, size = lift.recognize_far_return([_ins("retf", "8")])
    assert (far, pascal, size) == (True, True, 8)
    assert lift.recognize_long_helper("__aFlmul") == "mul"
    assert lift.recognize_long_helper("__aFldiv") == "div"


def test_structurer_folds_single_entry_if_and_back_edge():
    structured = lift.Structurer().run([
        "if ((ax) == (0)) goto L_0005;",
        "ax = (1);",
        "L_0005: ;",
        "L_0006: ;",
        "if ((cx) >= (4)) goto L_000a;",
        "dx = (dx + 1);",
        "goto L_0006;",
        "L_000a: ;",
    ])
    assert structured[0] == "if (!((ax) == (0))) {"
    assert "for (; !((cx) >= (4)); dx = (dx + 1)) {" in structured
    assert not any("goto L_0006" in line for line in structured)


def test_structurer_refines_condition_polarity_and_loop_forms():
    branch = [
        "if ((cx) == (0)) goto L_0004;",
        "left = (1);",
        "goto L_0006;",
        "L_0004: ;",
        "right = (2);",
        "L_0006: ;",
    ]
    flipped = lift.Structurer(condition_flip=True).run(branch)
    assert flipped[:4] == ["if ((cx) == (0)) {", "    right = (2);", "} else {", "    left = (1);"]
    assert flipped[-1] == "}"

    loop = [
        "L_0000: ;",
        "if ((cx) >= (4)) goto L_0006;",
        "dx = (dx + 1);",
        "dx++;",
        "goto L_0000;",
        "L_0006: ;",
    ]
    while_form = lift.Structurer(loop_style="while").run(loop)
    forever_form = lift.Structurer(loop_style="forever").run(loop)
    assert while_form[0] == "while (!((cx) >= (4))) {"
    assert "    dx++;" in while_form
    assert forever_form[:2] == ["for (;;) {", "    if ((cx) >= (4)) break;"]
    assert "goto L_0000" not in forever_form


def test_global_memory_uses_scalar_names_and_address_operands(monkeypatch):
    monkeypatch.setitem(lift.DECLS.variables, "lift_scalar", "extern int far lift_scalar;")
    monkeypatch.setitem(lift.DECLS.variables, "lift_rect", "extern struct Rect far lift_rect;")
    lifter = lift.Lifter("_CountUpdate")
    assert lifter._global_lvalue("lift_scalar", 0, 2, True) == "lift_scalar"
    assert "&lift_rect" in lifter._global_lvalue("lift_rect", 0, 2, True)
    used = {int(row["offset"]) for rows in lift.MAPSYM_BY_CNAME.values() for row in rows}
    offset = next(value for value in range(0xfffe, 0x1000, -1) if value not in used)
    monkeypatch.setitem(lift.MAPSYM_BY_CNAME, "lift_scalar", [{"name": "_lift_scalar", "segment": 10, "offset": offset}])
    ins = _ins("mov", "ax, 0x1234")
    result = lifter._immediate_info(ins, SimpleNamespace(imm=offset, size=2))
    assert result["text"] == "((unsigned int)(&lift_scalar))"


def test_declaration_database_carries_struct_tags_used_by_prototypes():
    assert "MapPoint" in lift.DECLS.structs
    assert "int x" in lift.DECLS.structs["MapPoint"]


def test_indirect_calls_lower_stack_values_to_text():
    lifter = lift.Lifter("_CountUpdate")
    lifter.pushes.append({"text": "7", "width": 2})
    rows = []
    lifter._emit_call(_ins("call", "ax"), rows)
    assert rows == ["ax = (__lift_indirect_0(7));"]


def test_symbolic_rep_copy_and_fill_use_resolved_far_objects(monkeypatch):
    name = "lift_test_far_array"
    monkeypatch.setitem(lift.DECLS.variables, name, f"extern unsigned char far {name}[];")
    lifter = lift.Lifter("_LoadTiles")
    lifter.es_object = name
    lifter._trees.update({"di": lift.sx("dest"), "si": lift.sx("source"),
                          "cx": lift.sx("words"), "ax": lift.sx("fill")})
    lifter._rep_byte_count = lift.sx("byte_count")
    copy_rows = lifter._emit_rep("movsw", _ins("rep movsw"))
    assert copy_rows[0].startswith("_fmemcpy(")
    assert "byte_count" in copy_rows[0] and "lift_test_far_array" in copy_rows[0]
    fill_rows = lifter._emit_rep("stosw", _ins("rep stosw"))
    assert fill_rows[0].startswith("memset(")
    assert "(words * 2)" in fill_rows[0] and "lift_test_far_array" in fill_rows[0]


def test_symbolic_lifter_keeps_register_arithmetic_in_expression_trees():
    lifter = lift.Lifter("_DeleteIndex")
    source = lifter.lift()
    assert lifter.carry_needed
    assert "__carry_w_" not in source
    assert "unsigned int ax;" not in source
    assert "reg_ax =" in source
    assert "reg_bx =" not in source or "bx =" not in source


def test_output_names_disambiguate_case_only_symbols():
    names = lift.output_filenames(["_mem_free", "_mem_Free", "_CountUpdate"])
    assert names["_CountUpdate"] == "CountUpdate.c"
    assert names["_mem_free"].casefold() != names["_mem_Free"].casefold()


def test_measurement_output_names_use_the_full_population():
    import lift_measure
    pairs = [("_mem_free", "_mem_Free"),
             ("_font_FontHeight", "__font_FontHeight")]
    for left, right in pairs:
        assert lift_measure._output_filename(left).casefold() != \
            lift_measure._output_filename(right).casefold()


def test_fixed_controls_lift_compile_and_match_strictly(tmp_path: Path):
    # These controls cover a far call, signed branch/return paths, a MAPSYM
    # DGROUP object and an imported far Pascal call with a far string + DWORD.
    for symbol in ("_CountUpdate", "_IsItWall", "_ClosePalette", "_ProcMenuHelp"):
        source, _function = lift.lift_symbol(symbol)
        candidate = tmp_path / f"{symbol.lstrip('_')}.c"
        candidate.write_text(source, encoding="ascii", newline="\n")
        run = subprocess.run(
            [sys.executable, str(ROOT / "tools" / "search.py"), symbol, str(candidate)],
            cwd=ROOT,
            text=True,
            capture_output=True,
            check=True,
        )
        report = json.loads(run.stdout)
        assert report["best"]["result"] == "CONFIRMED_MEMBER", (symbol, report["best"])
        assert report["best"]["exact_body"] is True
