"""Isolated MSC7 probe of ordinary and intrinsic memset lowering."""
import json
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
from compiler import compile_batch
import omf

HERE = Path(__file__).resolve().parent
FLAGS = ["/AL", "/G2", "/Gs", "/Oelw", "/NTSIMONE_MODULE"]
PROTOTYPE = "extern void *memset(void *, int, unsigned);\n"
FUNCTION = "void far Fill(unsigned char *p, unsigned char v, unsigned n) { memset(p, v, n); }\n"
SOURCES = {
    "external": PROTOTYPE + FUNCTION,
    "intrinsic": PROTOTYPE + "#pragma intrinsic(memset)\n" + FUNCTION,
    "intrinsic_local": PROTOTYPE + "#pragma intrinsic(memset)\n"
        + "void far Fill(unsigned char *p, unsigned char v, unsigned n) { unsigned i; memset(p, v, n); i = n; if (i) p[0] = v; }\n",
}

jobs = []
for name, source in SOURCES.items():
    path = HERE / (name + ".c")
    path.write_text(source, encoding="ascii")
    jobs.append({"source": path.relative_to(ROOT).as_posix(), "flags": FLAGS})

out = []
for (name, _), (obj, receipt) in zip(SOURCES.items(), compile_batch(jobs)):
    row = {"name": name, "receipt": receipt}
    if obj:
        dest = HERE / (name + ".obj")
        shutil.copyfile(obj, dest)
        module = omf.parse(dest.read_bytes())
        row["segments"] = [
            {"name": segment["name"], "class": segment["class"],
             "length": segment["length"],
             "rep_stosb": bytes.fromhex(segment["data_hex"]).count(bytes.fromhex("f3aa")),
             "rep_stosw": bytes.fromhex(segment["data_hex"]).count(bytes.fromhex("f3ab"))}
            for segment in module["segments"]
        ]
    out.append(row)
(HERE / "results.json").write_text(json.dumps(out, indent=2), encoding="utf-8")
for row in out:
    print(row["name"], row.get("segments"), row["receipt"]["exit_code"])
