import json
from pathlib import Path

root = Path(__file__).resolve().parents[4]
out = Path(__file__).resolve().parent
base = (root / "evidence/recovery/workflow/jobs/GetEnterDirB-a5248385bb/attempt02/candidate0000.c").read_text()
flags = ["/AL", "/G2", "/Gs", "/Oelw", "/NTSIMONE_MODULE"]

def move_local(src, local, declaration, initializer):
    decl = f"    int {local};\n"
    if src.count(decl) != 1:
        raise ValueError(f"expected one declaration for {local}")
    src = src.replace(decl, "", 1)
    init = f"    {local} = {initializer};\n"
    if src.count(init) != 1:
        raise ValueError(f"expected one initialization for {local}")
    block = f"    {{\n        {declaration}\n{init}"
    src = src.replace(init, block, 1)
    ending = "    }\n    return best;\n"
    if src.count(ending) != 1:
        raise ValueError("expected loop close and return")
    src = src.replace(ending, "    }\n    }\n    return best;\n", 1)
    return src

cases = {
    "back_block": move_local(base, "back", "int back;", "dir ^ 4"),
    "bestvalue_block": move_local(base, "bestValue", "int bestValue;", "EXITMAP(x, y)"),
}
both = base
both = both.replace("    int back;\n", "", 1).replace("    int bestValue;\n", "", 1)
both = both.replace("    back = dir ^ 4;\n", "    {\n        int back;\n        int bestValue;\n\n        back = dir ^ 4;\n", 1)
ending = "    }\n    return best;\n"
both = both.replace(ending, "    }\n    }\n    return best;\n", 1)
cases["both_block"] = both

for name, src in cases.items():
    source_path = out / f"{name}.c"
    source_path.write_text(src)
    spec = {
        "symbol": "_GetEnterDirB",
        "source": source_path.relative_to(root).as_posix(),
        "compiler": "msc700",
        "flags": flags,
        "max_candidates": 1,
        "axes": [],
        "semantic_summary": f"Isolated lexical-lifetime hypothesis {name}: scope the saved reverse direction and/or running best value only around the loop; preserve the same comparisons and update order.",
        "binding_evidence": ["Fresh MATCH_BLOCKED packet: all opcodes, fixups and selectors match; only back/bestValue stack homes are swapped. Earlier declaration-order, naming, initializer, expression/body and nx/ny-order matrices collapsed."],
        "publics": ["_GetEnterDirB"],
    }
    (out / f"{name}-spec.json").write_text(json.dumps(spec, indent=2) + "\n")
