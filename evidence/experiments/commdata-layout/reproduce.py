"""Reproduce MSC 7.00/LINK 5.30 data-placement contrasts for commdata.

All outputs are construction artifacts under build/workers/f-infra-commdata.
The probe DEF is derived from SIMANTW.DEF by retaining the original segment
order and executable model while omitting game exports/imports irrelevant to
the tiny objects. No oracle bytes are copied into these inputs.
"""
from __future__ import annotations

import json
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))

import common
import compiler
import ne
import omf
from assembler import assemble_source

EVIDENCE = ROOT / "evidence/experiments/commdata-layout"
WORK = ROOT / "build/workers/f-infra-commdata/link-layout"
SRC = EVIDENCE / "sources"
LINKER = ROOT / "toolchain/msc700/BIN/LINK.EXE"
WINSTUB = ROOT / "toolchain/sdk300/WINSTUB/WINSTUB.EXE"

SOURCES = {
    "code_anchor": ("void far commdata_anchor(void) { }\n", ["/NTSIMANT_MODULE"]),
    "pack_head": ("unsigned char __based(__segname(\"PACK\")) probe_head[3] = {0x11,0,0x22};\n", ["/NT_TEXT"]),
    "pack_tail": ("unsigned char __based(__segname(\"PACK\")) probe_tail[2] = {0x33,0x44};\n", ["/NT_TEXT"]),
    "far_common": ("int far probe_far_common[7];\n", ["/NT_TEXT"]),
    "far_static": ("static char far probe_far_static[9];\n", ["/NT_TEXT"]),
    "based_common": ("unsigned char __based(__segname(\"PACK\")) probe_based_common[13];\n", ["/NT_TEXT"]),
    "based_static": ("static unsigned char __based(__segname(\"PACK\")) probe_based_static[11];\n", ["/NT_TEXT"]),
    "pack_zero": ("unsigned char __based(__segname(\"PACK\")) probe_zero[15] = {0};\n", ["/NT_TEXT"]),
    "pack_nonzero": ("unsigned char __based(__segname(\"PACK\")) probe_nonzero[5] = {0xA5,0,0x5A,0,0x11};\n", ["/NT_TEXT"]),
    "far_huge": ("static char huge probe_huge[32768];\n", ["/NT_TEXT"]),
}

BASE = ["/AL", "/G2", "/Gs", "/Oelw"]


def write_inputs():
    SRC.mkdir(parents=True, exist_ok=True)
    for name, (body, extra) in SOURCES.items():
        (SRC / (name + ".c")).write_text(
            "/* Controlled LINK data layout probe; not reconstructed source. */\n" + body,
            encoding="ascii",
        )
    original = (ROOT / "src/link/SIMANTW.DEF").read_text(encoding="ascii")
    lines = original.splitlines()
    kept = []
    in_drop = False
    for line in lines:
        key = line.strip().upper()
        if key in ("EXPORTS", "IMPORTS"):
            in_drop = True
            continue
        if in_drop:
            if key and not line[:1].isspace():
                in_drop = False
            else:
                continue
        kept.append(line)
    (WORK / "SIMANTW.DEF").write_text("\n".join(kept) + "\n", encoding="ascii")
    shutil.copyfile(WINSTUB, WORK / "WINSTUB.EXE")


def omf_summary(path: Path):
    mod = omf.parse(path.read_bytes())
    return {
        "module": mod["name"],
        "sha256": mod["sha256"],
        "segments": [
            {
                "index": s["index"], "name": s["name"], "class": s["class"],
                "length": s["length"], "alignment": s["alignment"],
                "combine": s["combine"], "initialized_ranges": s["initialized_ranges"],
                "publics": [{"name": p["name"], "offset": p["offset"]}
                            for p in mod["publics"] if p["segment"] == s["index"]],
            } for s in mod["segments"] if s["length"] or s["name"] == "PACK"
        ],
        "commons": mod["commons"],
    }


def link(label: str, objects: list[str], packdata: bool = True):
    out = WORK / label
    out.mkdir(parents=True, exist_ok=True)
    for name in objects:
        shutil.copyfile(WORK / "objects" / (name + ".OBJ"), out / (name + ".OBJ"))
    shutil.copyfile(WORK / "SIMANTW.DEF", out / "SIMANTW.DEF")
    shutil.copyfile(WINSTUB, out / "WINSTUB.EXE")
    rsp = " +\n".join(name + ".OBJ" for name in objects)
    packing = "/PACKDATA" if packdata else "/NOPACKDATA"
    rsp += ",\nPROBE.EXE,\nPROBE.MAP,\n,\nSIMANTW.DEF /NOD /NOI /MAP /NOPACKCODE %s;\n" % packing
    (out / "PROBE.RSP").write_text(rsp, encoding="ascii")
    lock = common.read_json(ROOT / "layout/toolchain.json")
    runner = ROOT / lock["runner"]
    result = subprocess.run([str(runner), "-d", str(LINKER), "@PROBE.RSP"],
                            cwd=out, capture_output=True, timeout=300)
    log = (result.stdout + result.stderr).decode("latin1", errors="replace")
    (out / "LINK.LOG").write_text(log, encoding="latin1")
    exe = out / "PROBE.EXE"
    row = {"label": label, "objects": objects, "packdata": packdata, "rsp": rsp,
           "exit_code": result.returncode, "log_tail": log.splitlines()[-20:],
           "linked": exe.exists()}
    if exe.exists():
        raw = exe.read_bytes()
        image = ne.parse(raw)
        row["exe_identity"] = common.identity(exe)
        row["segments"] = [
            {k: s.get(k) for k in ("number", "sector", "file_offset", "length_word",
                                   "logical_size", "allocation_word", "allocation_size", "flags", "flag_names")}
            for s in image["segments"]
        ]
        row["segment_bytes"] = [
            {"number": s["number"], "logical_size": s["logical_size"],
             "nonzero_offsets": [i for i, b in enumerate(raw[s["file_offset"]:s["file_offset"] + s["logical_size"]]) if b][:64] if s.get("file_offset") is not None else [],
             "zero_bytes_in_file": sum(b == 0 for b in raw[s["file_offset"]:s["file_offset"] + s["logical_size"]]) if s.get("file_offset") is not None else 0}
            for s in image["segments"]
        ]
    map_path = out / "PROBE.MAP"
    if map_path.exists():
        row["map_identity"] = common.identity(map_path)
        row["map_text"] = map_path.read_text(encoding="latin1", errors="replace")
    return row


def main():
    WORK.mkdir(parents=True, exist_ok=True)
    (WORK / "objects").mkdir(exist_ok=True)
    write_inputs()
    jobs = []
    for name, (body, extra) in SOURCES.items():
        flags = BASE + extra
        jobs.append({"source": (SRC / (name + ".c")).relative_to(ROOT).as_posix(),
                     "flags": flags})
    compiled = compiler.compile_batch(jobs, "msc700")
    objects = {}
    for (name, _), (obj, receipt) in zip(SOURCES.items(), compiled):
        if obj is None:
            objects[name] = {"compile_error": receipt}
            continue
        destination = WORK / "objects" / (name + ".OBJ")
        shutil.copyfile(obj, destination)
        objects[name] = {"receipt": receipt, "omf": omf_summary(destination)}
    link_results = []
    combos = {
        "zero_and_nonzero_control": ["code_anchor", "pack_head", "pack_zero", "pack_nonzero", "pack_tail"],
        "communals_between_initialized": ["code_anchor", "pack_head", "far_common", "based_common", "far_static", "based_static", "pack_tail"],
        "communals_reversed": ["code_anchor", "pack_tail", "based_static", "far_static", "based_common", "far_common", "pack_head"],
        "huge_and_based": ["code_anchor", "pack_head", "far_huge", "based_common", "pack_tail"],
        "positive_initialized_only": ["code_anchor", "pack_head", "pack_tail"],
        "communal_only": ["code_anchor", "far_common"],
        "based_only": ["code_anchor", "based_static", "based_common"],
        "nopackdata_contrast": ["code_anchor", "pack_head", "far_common", "based_common", "far_static", "based_static", "pack_tail"],
    }
    for label, names in combos.items():
        if any("compile_error" in objects.get(name, {}) for name in names):
            link_results.append({"label": label, "skipped": "one or more objects failed compilation"})
            continue
        link_results.append(link(label, names, packdata=label != "nopackdata_contrast"))
    result = {
        "id": "LINK-D1-layout-probe",
        "status": "EXPERIMENTAL_REPRODUCER",
        "original_def": common.identity(ROOT / "src/link/SIMANTW.DEF"),
        "probe_def": common.identity(WORK / "SIMANTW.DEF"),
        "linker": common.identity(LINKER),
        "runner": common.identity(ROOT / common.read_json(ROOT / "layout/toolchain.json")["runner"]),
        "compiler": "MSC C/C++ 7.00, assigned baseline data profile /AL /G2 /Gs /Oelw",
        "packdata": True,
        "segment_order_from_original_def": segment_order_from_original_def(),
        "objects": objects,
        "links": link_results,
        "scope": "Not source provenance; distinguishes OMF initialization/common classes and LINK file length versus allocation.",
    }
    common.write_json(EVIDENCE / "layout-results.json", result)
    print(json.dumps({"output": str(EVIDENCE / "layout-results.json"),
                      "compiled": len(objects), "linked": sum(bool(x.get("linked")) for x in link_results),
                      "compile_errors": [k for k, v in objects.items() if "compile_error" in v],
                      "link_results": [{"label": x["label"], "exit_code": x.get("exit_code"), "linked": x.get("linked")} for x in link_results]}, indent=2))


def segment_order_from_original_def():
    found = []
    in_segments = False
    for line in (ROOT / "src/link/SIMANTW.DEF").read_text(encoding="ascii").splitlines():
        stripped = line.strip()
        upper = stripped.upper()
        if not stripped or stripped.startswith(";"):
            continue
        if not line[:1].isspace():
            in_segments = upper == "SEGMENTS"
            continue
        if in_segments:
            found.append(stripped.split()[0])
    return found


if __name__ == "__main__":
    main()
