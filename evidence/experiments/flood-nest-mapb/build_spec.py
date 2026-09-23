"""Build a bounded MapB binding probe from the preserved FloodNestB draft."""

import json
from pathlib import Path

root = Path(__file__).resolve().parents[3]
here = Path(__file__).resolve().parent
candidate = (root / "evidence/recovery/workflow/jobs/FloodNestB-7a01e41f2d/attempt02/candidate0000.c").read_text()
template = candidate.replace(
    "extern unsigned char near nestMap[];", "extern unsigned char near MapB[];"
).replace(
    "nestMap + row + cell + 0x48e8", "MapB + row + cell"
).replace(
    "    int row;\n    int cell;", "@DECLS@"
)
assert template != candidate and template.count("@DECLS@") == 1
spec = {
    "symbol": "_FloodNestB",
    "template": template,
    "axes": [{
        "name": "counter_declarations",
        "marker": "@DECLS@",
        "rationale": "The MapB binding is independently named by MAPSYM at DGROUP:48E8; the target allocates row/cell to DI/BX, while the preserved source used CX/DI. Test only the three already evidenced declaration forms with the corrected binding.",
        "values": [
            "    int row;\n    int cell;",
            "    register int row;\n    register int cell;",
            "    register int cell;\n    register int row;",
        ],
    }],
    "compiler": "msc700",
    "flags": ["/AL", "/G2", "/Gs", "/Oelw", "/NTSIMONE_MODULE"],
    "max_candidates": 3,
}
(here / "spec.json").write_text(json.dumps(spec, indent=2) + "\n")
