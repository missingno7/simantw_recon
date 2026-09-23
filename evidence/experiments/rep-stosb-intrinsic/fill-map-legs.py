"""Generate and strictly compare one isolated intrinsic hypothesis for FillMapLegs."""
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
source = (ROOT / "evidence/recovery/workflow/jobs/FillMapLegs-094a0f3eee/candidate.c").read_text()
source = source.replace(
    "extern int far SRand1(int range);",
    "extern int far SRand1(int range);\nextern void *memset(void *, int, unsigned);\n#pragma intrinsic(memset)",
)
source = source.replace(
    "                run = columnCount;\n                while (run--)\n"
    "                    MapA[rowOffset + columnStart + columnCount - run - 1] = fillValue;",
    "                memset(&MapA[rowOffset + columnStart], fillValue, columnCount);",
)
for start in ("firstColumn", "lastColumn - 3"):
    source = source.replace(
        "            for (column = " + start + "; column <= "
        + ("firstColumn + 3" if start == "firstColumn" else "lastColumn")
        + "; ++column)\n                MapA[rowOffset + column] = 0xC0;",
        "            memset(&MapA[rowOffset + " + start + "], 0xC0, 4);",
    )
if source.count("memset(&MapA") != 5 or "while (run--)" in source:
    raise SystemExit("source replacement did not cover five target runs")
(HERE / "fill-map-legs-intrinsic.c").write_text(source)
spec = {
    "symbol": "_FillMapLegs",
    "source": (HERE / "fill-map-legs-intrinsic.c").relative_to(ROOT).as_posix(),
    "compiler": "msc700",
    "flags": ["/AL", "/G2", "/Gs", "/Oelw", "/NTSIMONE_MODULE"],
    "max_candidates": 1,
    "axes": [],
    "semantic_summary": "Isolated test of source-local intrinsic memset for five observed REP STOSB runs; not an ordinary production submission.",
    "binding_evidence": [
        "Target FillMapLegs has five REP STOSB sites.",
        "Pinned MSC7 microfixture proves #pragma intrinsic(memset) emits REP STOSB under baseline flags.",
    ],
    "publics": ["_FillMapLegs"],
}
(HERE / "fill-map-legs-spec.json").write_text(json.dumps(spec, indent=2))
subprocess.run(
    [sys.executable, "tools/codegen_grinder.py", (HERE / "fill-map-legs-spec.json").relative_to(ROOT).as_posix(),
     "--out", "evidence/experiments/rep-stosb-intrinsic/fill-map-legs-run"],
    cwd=ROOT, check=True,
)
