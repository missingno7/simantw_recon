import json
from pathlib import Path

root = Path(__file__).resolve().parents[4]
out = Path(__file__).resolve().parent
members = {
    "win_DrawHBar": ("_win_DrawHBar", "right"),
    "win_DrawVBar": ("_win_DrawVBar", "top"),
}
for name, (symbol, edge) in members.items():
    src = (root / "build/reclassify" / name / "candidate0000.c").read_text()
    src = src.replace(f"    struct WinBucket far *bucket;\n    int {edge};\n",
                      "    struct WinBucket far *bucket;\n", 1)
    anchor = "    win_UnlockWin(objectNumber);\n"
    tail = src.split(anchor, 1)[1]
    tail = tail.replace(f"    {edge} = rect.{edge};\n", "", 1)
    # New block lifetime and initializer put the retained old endpoint in scope
    # only for the split calculation and fills.
    tail = "    {\n        int %s = rect.%s;\n" % (edge, edge) + tail.rstrip()
    if not tail.endswith("}"):
        raise ValueError("source tail lacks function close")
    tail = tail[:-1].rstrip() + "\n    }\n}"
    src = src.split(anchor, 1)[0] + anchor + tail
    source_path = out / f"{name}-tail.c"
    source_path.write_text(src)
    spec = {
        "symbol": symbol,
        "source": source_path.relative_to(root).as_posix(),
        "compiler": "msc700",
        "flags": ["/AL", "/G2", "/Gs", "/Oelw", "/GA", "/NTSIMTWO_MODULE"],
        "max_candidates": 1,
        "axes": [],
        "semantic_summary": f"Narrow {edge}'s lexical lifetime to a tail block beginning immediately after win_UnlockWin, with its initialization in the declaration; inspect whether C7 retains the old edge in SI before fraction argument setup.",
        "binding_evidence": ["Fresh strict reclassification candidate; target SI load at +0x60 precedes fraction pushes; prior broad expression and register probes did not move the load."],
        "publics": [symbol],
    }
    (out / f"{name}-spec.json").write_text(json.dumps(spec, indent=2) + "\n")
