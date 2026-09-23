"""Probe both selector-backed pointer objects in source reference order."""
import hashlib
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
CASES = [
    ("single_farptr_both", "char far * far", "configFileName", "configFileMissingStr"),
    ("triple_filename", "char far * far * far", "*configFileName", "configFileMissingStr"),
    ("triple_error_text", "char far * far * far", "configFileName", "*configFileMissingStr"),
    ("triple_both", "char far * far * far", "*configFileName", "*configFileMissingStr"),
    ("near_pointer_both", "char far * near", "configFileName", "configFileMissingStr"),
]

jobs=[]
for n,(label,typ,filename,text) in enumerate(CASES):
    source=HERE/f"pair{n:02d}.c"
    source.write_text(
        "/* ABI probe only: open one stored far path and display one stored far text. */\n"
        f"extern {typ} configFileName;\n"
        f"extern {typ} configFileMissingStr;\n"
        "extern int near rootWnd;\n"
        "extern char near configCaption[];\n"
        "extern int far pascal _lopen(char far *path, int mode);\n"
        "extern int far pascal MessageBox(int hwnd, char far *text, char far *caption, unsigned int type);\n"
        f"int far Probe{n:02d}(void) {{ int fd = _lopen({filename}, 0); "
        f"if (fd <= 0) MessageBox(rootWnd, {text}, configCaption, 0x30); return fd; }}\n"
    )
    jobs.append(dict(source=source.relative_to(ROOT).as_posix(),flags=FLAGS))

compiled=compile_batch(jobs,compiler="msc700",session_limit=96)
rows=[]
for n,((label,typ,filename,text),(objpath,receipt)) in enumerate(zip(CASES,compiled)):
    if objpath is None:
        rows.append(dict(label=label,error=receipt.get("stdout","compile failed")))
        continue
    module=parse(objpath.read_bytes())
    code=next(s for s in module["segments"] if s["name"]=="GR_MODULE")
    body=bytes.fromhex(code["data_hex"])
    instructions=[dict(offset=i.address,bytes=i.bytes.hex(),mnemonic=i.mnemonic,operands=i.op_str)
                  for i in decoder().disasm(body,0)]
    fixups=[f for f in module["fixups"] if f["segment"]==code["index"]]
    body_hash=hashlib.sha256(body).hexdigest()
    fixup_hash=hashlib.sha256(json.dumps(fixups,sort_keys=True,separators=(",",":")).encode()).hexdigest()
    rows.append(dict(label=label,declaration_type=typ,filename_expression=filename,
                     error_text_expression=text,object_sha256=module["sha256"],code_sha256=body_hash,
                     semantic_fixups_sha256=fixup_hash,code_size=len(body),fixups=fixups,
                     instructions=instructions))
classes={}
for row in rows:
    if "code_sha256" in row:
        key=row["code_sha256"]+":"+row["semantic_fixups_sha256"]
        classes.setdefault(key,[]).append(row["label"])
report=dict(compiler="msc700",flags=FLAGS,component="gr:08F4",
            target_selector_slots=["DGROUP:0xC6AE filename", "DGROUP:0xC6B0 missing-text"],
            target_far_objects=["GR_MODULE:0x8B36 _configFileName", "GR_MODULE:0x8B32 _configFileMissingStr"],
            cases=rows,effective_output_classes=list(classes.values()))
(HERE/"pair-results.json").write_text(json.dumps(report,indent=2)+"\n")
print(json.dumps(dict(cases=len(rows),effective_output_classes=list(classes.values())),indent=2))
