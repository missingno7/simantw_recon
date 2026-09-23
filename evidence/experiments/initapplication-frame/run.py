"""Bounded, isolated MSC7 test of the missing WNDCLASS frame slot."""
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
source = (ROOT / "evidence/recovery/workflow/jobs/InitApplication-6c36964eac/candidate.c").read_text()
needle = "    struct WndClass wcRibbon, wcGeneric, wcRoot;"
if source.count(needle) != 1:
    raise SystemExit("unexpected source declaration")
template = source.replace(needle, needle + "\n/*FRAME_DECL*/")
(HERE / "template.c").write_text(template)
spec = {
    "symbol": "_InitApplication",
    "source": (HERE / "template.c").relative_to(ROOT).as_posix(),
    "compiler": "msc700",
    "flags": ["/AL", "/G2", "/Gs", "/Oelw", "/NTSIMANT_MODULE"],
    "max_candidates": 5,
    "axes": [{
        "name": "trailing_unused_storage",
        "marker": "/*FRAME_DECL*/",
        "rationale": "Target stack is exactly one 26-byte WNDCLASS deeper than the opcode-exact candidate; prior unused declaration was placed before the used locals, so test trailing and scoped placement separately.",
        "values": [
            "",
            "struct WndClass wcUnused;",
            "volatile struct WndClass wcUnused;",
            "char unused[26];",
            "volatile char unused[26];",
        ],
    }],
    "semantic_summary": "Isolated frame-layout research on exact-opcode InitApplication; no production reissue.",
    "binding_evidence": [
        "Preserved attempt06 is 315 bytes and 90/90 opcodes with all 20/20 fixups; only the frame/stack-home offset differs by one 26-byte WNDCLASS.",
        "A prior unused WNDCLASS before the three used locals shrank the frame and is a separate negative control.",
    ],
    "publics": ["_InitApplication"],
}
(HERE / "spec.json").write_text(json.dumps(spec, indent=2))
subprocess.run(
    [sys.executable, "tools/codegen_grinder.py", (HERE / "spec.json").relative_to(ROOT).as_posix(),
     "--out", "evidence/experiments/initapplication-frame/run", "--cache",
     "--evidence", "evidence/experiments/initapplication-frame/compact.json"],
    cwd=ROOT, check=True,
)
