"""Focused tests for symbolic expressions and the MSC frame solver."""
from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import frame_map
import lift
import lift_frame


def test_expression_nodes_retain_tree_shape_until_rendered():
    a, b = lift.sx("left"), lift.sx("right")
    expr = lift.SExpr("binary", (a, b), "+", 2)
    assert expr.render() == "(left + right)"
    expr.flip = True
    assert expr.render() == "(right + left)"


def test_boolean_long_helper_and_far_pointer_names_are_recognized():
    assert lift.recognize_long_helper("__aFlmul") == "mul"
    assert lift.recognize_long_helper("__aFulshr") == "shr"
    lifter = lift.Lifter("_IsItWall")
    source = lifter.lift()
    assert "arg_6" in source
    assert "unsigned int dx;" not in source


def test_adc_sbb_stay_in_the_symbolic_carry_expression():
    lifter = lift.Lifter("_DeleteIndex")
    assert any(row.mnemonic in ("adc", "sbb") for row in lifter.f.instructions)
    source = lifter.lift()
    assert not lifter.f.unsupported.get("adc", 0)
    assert not lifter.f.unsupported.get("sbb", 0)
    assert "lifter residue: adc" not in source
    assert "lifter residue: sbb" not in source


def test_frame_solver_generates_observed_and_alternative_home_orders():
    slots = [
        lift.FrameSlot(-2, 2, "unsigned int", "v_bp_m2"),
        lift.FrameSlot(-4, 2, "unsigned int", "v_bp_m4"),
    ]
    solver = lift_frame.FrameSolver(slots, [
        {"mnemonic": "mov", "operands": "word ptr [bp - 4], ax"},
        {"mnemonic": "mov", "operands": "word ptr [bp - 2], bx"},
    ])
    orders = {x.name: x.order for x in solver.variants(8)}
    assert orders["bp-near-first"] == ("v_bp_m2", "v_bp_m4")
    assert ("v_bp_m4", "v_bp_m2") in orders.values()


def test_frame_solver_offers_a_compiler_tested_merge_for_overlapping_homes():
    slots = [
        lift.FrameSlot(-4, 4, "unsigned long", "v_bp_m4"),
        lift.FrameSlot(-2, 2, "unsigned int", "v_bp_m2"),
    ]
    solver = lift_frame.FrameSolver(slots, [])
    assert solver.overlap_groups == [("v_bp_m4", "v_bp_m2")]
    assert any(x.merges == (("v_bp_m4", "v_bp_m2"),) for x in solver.variants(32))


def test_frame_exactness_compares_enter_homes_and_registers():
    oracle = {"status": "OK", "candidate_enter": 4,
              "candidate_locals": [{"offset": -2, "size": 2}],
              "candidate_registers": [{"register": "si", "type": 0x11}]}
    assert lift_frame.frame_exact(oracle, dict(oracle))
    changed = dict(oracle, candidate_enter=6)
    assert not lift_frame.frame_exact(changed, oracle)
    assert lift_frame.target_access_exact({
        "status": "OK", "candidate_enter": 4, "target_enter": 4,
        "candidate_locals": [{"offset": -2, "size": 2}],
        "target_slots": {"-2": [2]},
    })


def test_bp_access_map_preserves_width_and_enter():
    enter, slots = frame_map.target_frame([
        {"mnemonic": "enter", "operands": "4, 0"},
        {"mnemonic": "mov", "operands": "word ptr [bp - 2], ax"},
    ])
    assert enter == 4
    assert slots[-2] == [2]
