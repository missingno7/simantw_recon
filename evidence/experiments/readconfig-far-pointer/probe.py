"""Bounded MSC 7 declaration probes for the ReadConfig far globals."""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "tools"))
from compiler import compile_batch
from omf import parse
from analysis import decoder

FLAGS = ["/AL", "/G2", "/Gs", "/Oelw", "/NTGR_MODULE"]
FORMS = [
    ("triple_deref", "extern char far * far * far configFileName;", "*configFileName"),
    ("triple_index0", "extern char far * far * far configFileName;", "configFileName[0]"),
    ("double_deref", "extern char far * far * configFileName;", "*configFileName"),
    ("far_pointer_value", "extern char far * far configFileName;", "configFileName"),
    ("far_pointer_array", "extern char far * far configFileName[];", "configFileName[0]"),
    ("far_char_array", "extern char far configFileName[];", "configFileName"),
    ("near_pointer_value", "extern char far * near configFileName;", "configFileName"),
    ("far_struct_words", "struct Pair { unsigned off, sel; }; extern struct Pair far configFileName;", "*(char far *)&configFileName"),
]

sources = []
for index, (label, decl, expr) in enumerate(FORMS):
    path = HERE / f"form{index:02d}.c"
    path.write_text(
        "/* ABI probe only: pass the configured far filename pointer to _lopen. */\n"
        + decl + "\n"
        + "extern int far pascal _lopen(char far *path, int mode);\n"
        + f"int far Probe{index:02d}(void) {{ return _lopen({expr}, 0); }}\n"
    )
    sources.append(path)

jobs = [dict(source=p.relative_to(ROOT).as_posix(), flags=FLAGS) for p in sources]
compiled = compile_batch(jobs, compiler="msc700", session_limit=96)
results = []
for (label, decl, expr), (objpath, receipt) in zip(FORMS, compiled):
    if objpath is None:
        results.append(dict(label=label, error=receipt.get("stdout", "compile failed")))
        continue
    module = parse(objpath.read_bytes())
    code = next((s for s in module["segments"] if s["name"] == "GR_MODULE"), None)
    if code is None:
        results.append(dict(label=label, error="GR_MODULE missing", object=receipt["object"]))
        continue
    code_bytes = bytes.fromhex(code["data_hex"])
    instructions = [
        dict(offset=i.address, bytes=i.bytes.hex(), mnemonic=i.mnemonic, operands=i.op_str)
        for i in decoder().disasm(code_bytes, 0)
    ]
    public = next((p for p in module["publics"] if p["name"] == f"_Probe{len(results):02d}"), None)
    code_identity = __import__("hashlib").sha256(code_bytes).hexdigest()
    results.append(dict(
        label=label, declaration=decl, expression=expr,
        object_sha256=module["sha256"], code_sha256=code_identity,
        code_size=len(code_bytes), public=public,
        fixups=[f for f in module["fixups"] if f["segment"] == code["index"]],
        instructions=instructions,
    ))

# Effective-output classes use the code bytes plus semantic fixup facts.
classes = {}
for row in results:
    if "code_sha256" in row:
        fixups = json.dumps(row["fixups"], sort_keys=True, separators=(",", ":"))
        key = row["code_sha256"] + ":" + __import__("hashlib").sha256(fixups.encode()).hexdigest()
        classes.setdefault(key, []).append(row["label"])

report = dict(
    compiler="msc700", flags=FLAGS, component="gr:08F4", target_selector_slots=["DGROUP:0xC6AE", "DGROUP:0xC6B0"],
    target_object_symbols=["GR_MODULE:0x8B36 _configFileName", "GR_MODULE:0x8B32 _configFileMissingStr"],
    forms=results, effective_output_classes=list(classes.values()),
)
(HERE / "results.json").write_text(json.dumps(report, indent=2) + "\n")
print(json.dumps(dict(forms=len(results), effective_output_classes=list(classes.values())), indent=2))
