"""Compose the preserved ButtonHeld attempt 08 with admitted ButtonHeldInit.

This is a research-only TU replay. The earlier gr_4A2C unit used attempt 01.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))

from tu_assembly import compose, declaration_order_constraints

sources = {
    "_ButtonHeldInit": "src/recovered/ButtonHeldInit.c",
    "_ButtonHeld": "evidence/recovery/workflow/jobs/ButtonHeld-0235ac43d4/attempt08/candidate0000.c",
}
result = compose(
    sources,
    ["_ButtonHeldInit", "_ButtonHeld"],
    "gr_4A2C_attempt08_reviewed",
    declaration_order=declaration_order_constraints("gr:4A2C"),
)
if result["status"] != "COMPOSED":
    raise SystemExit(f"TU composition failed: {result['status']} {result.get('conflicts')}")
(Path(__file__).parent / "unit.c").write_text(result["text"], encoding="latin1")
print("Composed reviewed research TU from preserved attempt 08")
