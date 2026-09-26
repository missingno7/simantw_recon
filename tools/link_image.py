"""Rebuild and audit the LINK-owned portion of SIMANTW.EXE.

RAWDEBT objects generated here are link scaffolding. Their initializer bytes
come from the explicit image debt ledger and never count as recovered code or
data. This tool is deliberately separate from tools/image.py and the proof
pipeline.

Typical use:
    python tools/link_image.py analyze
    python tools/link_image.py package
    python tools/link_image.py link
    python tools/link_image.py compare build/workers/linkdef-2/LINKED.EXE
"""
import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

from common import ROOT, FormatError, fixture, identity, read_json, write_json
import library_match
import mapsym
import ne
import omf


EVIDENCE = ROOT / "evidence/experiments/link-container"
WORK = ROOT / "build/workers/linkdef-2"
EVIDENCE_CONTAINER = EVIDENCE / "link-container-linkdef-2.json"
EVIDENCE_ORDER = EVIDENCE / "link-order-linkdef-2.json"
EVIDENCE_RESULT = EVIDENCE / "link-result-linkdef-2.json"
RAW_LANES = {"GAME_CODE", "CODE_GAP", "RUNTIME_CODE", "DATA"}
RESOURCE_LANES = {"RESOURCES"}
LINK_LANES = {"LINK"}
DEF_STUB = "toolchain/sdk300/WINSTUB/WINSTUB.EXE"


def _json(path):
    return json.loads(Path(path).read_text(encoding="utf-8"))


def _sha(data):
    return hashlib.sha256(data).hexdigest()


def _le16(value):
    if not 0 <= value <= 0xFFFF:
        raise FormatError("16-bit field out of range: %r" % (value,))
    return int(value).to_bytes(2, "little")


def _omf_index(value):
    if not 1 <= value <= 0x7FFF:
        raise FormatError("OMF index out of range: %d" % value)
    if value < 0x80:
        return bytes([value])
    return bytes([0x80 | (value >> 8), value & 0xFF])


def _omf_name(value):
    raw = value.encode("ascii")
    if len(raw) > 255:
        raise FormatError("OMF name too long: " + value)
    return bytes([len(raw)]) + raw


def _omf_record(kind, body):
    size = len(body) + 1
    prefix = bytes([kind]) + size.to_bytes(2, "little") + body
    return prefix + bytes([(-sum(prefix)) & 0xFF])


def _segment_name_by_number(image, symbols):
    by_num = {s["number"]: s for s in symbols["segments"]}
    result = {}
    for seg in image["segments"]:
        result[seg["number"]] = by_num.get(seg["number"], {}).get("name", "SEG%d" % seg["number"])
    return result


def _exports(image, symbols):
    by_ordinal = {}
    for row in image["resident_names"] + image["nonresident_names"]:
        if row["ordinal"]:
            by_ordinal[row["ordinal"]] = row["name"]
    by_segment = {s["number"]: s["symbols"] for s in symbols["segments"]}
    out = []
    for entry in image["entries"]:
        name = by_ordinal.get(entry["ordinal"])
        if not name:
            raise FormatError("entry ordinal %d lacks a name-table entry" % entry["ordinal"])
        exact = next((p["name"] for p in by_segment.get(entry["segment"], [])
                      if p["offset"] == entry["offset"]), None)
        resident = any(x["ordinal"] == entry["ordinal"] for x in image["resident_names"])
        out.append({"ordinal": entry["ordinal"], "name": name,
                    "segment": entry["segment"], "offset": entry["offset"],
                    "internal_public": exact, "resident": resident,
                    "entry_flags": entry.get("flags")})
    return out


def build_def(image, symbols, stub=DEF_STUB):
    """Return a candidate DEF and evidence for every directive."""
    resident_module = next((x["name"] for x in image["resident_names"] if x["ordinal"] == 0), None)
    description = next((x["name"] for x in image["nonresident_names"] if x["ordinal"] == 0), None)
    if not resident_module or not description:
        raise FormatError("missing module/description names in NE name tables")
    exports = _exports(image, symbols)
    map_segments = {s["number"]: s for s in symbols["segments"]}
    directives = []

    def line(text, source, interpretation):
        directives.append({"line": text, "source": source, "interpretation": interpretation})

    name_line = "NAME %s WINDOWAPI" % resident_module
    desc_line = 'DESCRIPTION "%s"' % description
    line(name_line, "NE resident module name, ordinal 0; NE flags 778 imply WINDOWAPI", "module identity and Windows API application type")
    line(desc_line, "NE nonresident name, ordinal 0", "description string")
    line("EXETYPE WINDOWS 3.0", "NE target_os=2 and expected_windows_version=0x0300", "Windows 3.0 executable target")
    stub_line = 'STUB "%s"' % Path(stub).name
    line(stub_line, "toolchain/sdk300/WINSTUB/WINSTUB.EXE body equals original bytes 512:610; original DOS stub remainder is zero padding", "reproduces the original MZ stub body using the pinned Windows 3.0 SDK stub")
    line("CODE MOVEABLE DISCARDABLE", "NE code flags are 7440 except _TEXT=7504; 7440 is moveable+discardable+load-on-call", "default for load-on-call code segments")
    line("DATA PRELOAD MOVEABLE MULTIPLE", "NE data flags 3153/3409 and NE MULTIPLE_DATA bit", "default for initialized data and multiple data instances")
    line("HEAPSIZE %d" % image["header"]["heap_size"], "NE header heap_size", "application heap")
    line("STACKSIZE %d" % image["header"]["stack_size"], "NE header stack_size", "application stack")
    lines = [name_line, desc_line, "", "EXETYPE WINDOWS 3.0", stub_line,
             "CODE MOVEABLE DISCARDABLE", "DATA PRELOAD MOVEABLE MULTIPLE",
             "HEAPSIZE %d" % image["header"]["heap_size"],
             "STACKSIZE %d" % image["header"]["stack_size"]]
    lines += ["", "SEGMENTS"]
    for seg in image["segments"]:
        name = map_segments.get(seg["number"], {}).get("name", "SEG%d" % seg["number"])
        # DATA is a linker-added NE flag; relocation presence is generated from OMF FIXUPP.
        is_data = seg["kind"] == "DATA"
        clauses = ["CLASS 'DATA'" if is_data else "CLASS 'CODE'"]
        clauses.append("PRELOAD" if (seg["flags"] & 64) else "LOADONCALL")
        clauses.append("MOVEABLE")
        if seg["flags"] & 4096:
            clauses.append("DISCARDABLE")
        statement = "  %s %s" % (name, " ".join(clauses))
        lines.append(statement)
        line(statement, "NE segment %d: flags=%d, MAPSYM segment name=%s" % (seg["number"], seg["flags"], name),
             "preserve physical order and load/execute class; LINK regenerates relocation and DATA bits")
    lines += ["", "EXPORTS"]
    for item in exports:
        alias = item["name"]
        internal = item["internal_public"]
        exp = alias if not internal or internal.upper() == alias.upper() else "%s=%s" % (alias, internal)
        statement = "  %s @%d%s" % (exp, item["ordinal"], " RESIDENTNAME" if item["resident"] else "")
        lines.append(statement)
        line(statement, "NE entry ordinal %(ordinal)d -> segment %(segment)d:%(offset)04X; name table gives %(name)s; exact MAPSYM public=%(internal_public)s" % item,
             "export the mapped entry and preserve resident/nonresident name-table placement")
    return "\n".join(lines) + "\n", directives, exports


def _segment_at_file_offset(image, at):
    for seg in image["segments"]:
        if seg["file_offset"] is not None and seg["file_offset"] <= at < seg["file_offset"] + seg["logical_size"]:
            return seg
    return None


def _oracle_model():
    raw = fixture("SIMANTW.EXE")
    image = ne.parse(raw)
    symbols = mapsym.parse(fixture("SIMANTW.SYM"))
    ledger = read_json(ROOT / "build/image/ledger.json")
    manifest = read_json(ROOT / "build/recovered/manifest.json")
    return raw, image, symbols, ledger, manifest


def _collect_object_layout(raw, image, symbols, manifest):
    """Read-only strict placement mapping for every manifest OMF object."""
    imports = library_match.import_symbols(ROOT / "toolchain/sdk300/WLIB/LIBW.LIB")
    rows = []
    owned = defaultdict(set)
    known_publics = set()
    seen = set()
    failures = []
    for group_name, group in (("GAME", manifest["game_objects"]), ("RUNTIME", manifest["runtime_objects"])):
        for row in group:
            obj_path = ROOT / row["object"]
            digest = row["identity"]["sha256"]
            if digest in seen:
                continue
            seen.add(digest)
            try:
                module = omf.parse(obj_path.read_bytes())
                known_publics.update(p["name"] for p in module["publics"])
                comparison, placed = __import__("image").regenerate(module, raw, image, symbols, imports)
                if comparison["result"] not in ("CONFIRMED_MEMBER", "STRONGLY_SUPPORTED_MEMBER"):
                    failures.append({"object": row["object"], "result": comparison["result"], "issues": comparison.get("issues", [])[:4]})
                seg_by_name = {s["name"]: s for s in module["segments"]}
                item = {"object": row["object"], "module": module["name"], "sha256": digest,
                        "group": group_name, "member": row.get("member", row.get("symbol")),
                        "contributions": []}
                for c in comparison.get("contributions", []):
                    seg = seg_by_name[c["segment"]]
                    item["contributions"].append({"logical_segment": c["segment"], "class": seg["class"],
                        "ne_segment": c["original_segment"], "start": c["original_offset"],
                        "end": c["original_offset"] + c["length"], "length": c["length"]})
                for (segnum, offset), (byte, is_chain) in placed.items():
                    owned[segnum].add(offset)
                rows.append(item)
            except Exception as exc:
                failures.append({"object": row["object"], "error": str(exc)})
    return rows, owned, known_publics, failures


def _raw_spans(image, ledger, owned):
    """Coalesce raw debt with its unowned chain words into segment-local spans."""
    raw_offsets = defaultdict(set)
    for interval in ledger["intervals"]:
        if interval["lane"] not in RAW_LANES:
            continue
        seg = _segment_at_file_offset(image, interval["start"])
        if not seg:
            continue
        lo = interval["start"] - seg["file_offset"]
        hi = min(interval["end"], seg["file_offset"] + seg["logical_size"]) - seg["file_offset"]
        raw_offsets[seg["number"]].update(range(lo, hi))
    raw_chain_sites = defaultdict(dict)
    for seg in image["segments"]:
        if seg["file_offset"] is None:
            continue
        for reloc in seg["relocations"]:
            if reloc["additive"]:
                continue
            for i, site in enumerate(reloc["sites"]):
                width = 2
                if any(p in owned[seg["number"]] for p in range(site, min(site + width, seg["logical_size"]))):
                    continue
                raw_offsets[seg["number"]].update(range(site, min(site + width, seg["logical_size"])))
                raw_chain_sites[seg["number"]][site] = {"next": reloc["sites"][i + 1] if i + 1 < len(reloc["sites"]) else 0xFFFF,
                    "relocation": reloc}
    spans = defaultdict(list)
    for seg in image["segments"]:
        offsets = sorted(p for p in raw_offsets[seg["number"]] if p not in owned[seg["number"]])
        if not offsets:
            continue
        start = prev = offsets[0]
        for p in offsets[1:] + [None]:
            if p is not None and p == prev + 1:
                prev = p
                continue
            end = prev + 1
            spans[seg["number"]].append({"start": start, "end": end,
                "chain_sites": [site for site in sorted(raw_chain_sites[seg["number"]]) if start <= site < end]})
            if p is not None:
                start = prev = p
    return spans, raw_chain_sites


def _subtract_spans(spans, claims):
    """Split raw gaps around independently evidenced non-RAW contributions."""
    carved = []
    for span in spans:
        pieces = [(span["start"], span["end"])]
        for claim in claims:
            updated = []
            for a, b in pieces:
                if claim["end"] <= a or claim["start"] >= b:
                    updated.append((a, b))
                else:
                    if a < claim["start"]:
                        updated.append((a, claim["start"]))
                    if claim["end"] < b:
                        updated.append((claim["end"], b))
            pieces = updated
        for a, b in pieces:
            if a < b:
                carved.append({"start": a, "end": b,
                    "chain_sites": [q for q in span.get("chain_sites", []) if a <= q < b]})
    return carved


def analyze(write=True):
    raw, image, symbols, ledger, manifest = _oracle_model()
    def_text, def_lines, exports = build_def(image, symbols)
    layouts, owned, known_publics, failures = _collect_object_layout(raw, image, symbols, manifest)
    spans, raw_chain_sites = _raw_spans(image, ledger, owned)
    seg_names = _segment_name_by_number(image, symbols)
    by_logical = defaultdict(list)
    for row in layouts:
        for c in row["contributions"]:
            by_logical[(c["ne_segment"], c["logical_segment"])].append({
                "object": row["object"], "group": row["group"], "member": row["member"],
                "start": c["start"], "end": c["end"], "class": c["class"]})
    segment_orders = []
    for (number, logical), contributions in sorted(by_logical.items()):
        contributions.sort(key=lambda x: (x["start"], x["end"], x["object"]))
        segment_orders.append({"ne_segment": number, "output_name": seg_names[number],
            "logical_segment": logical, "contributions": contributions,
            "order_basis": "strict member placement in the oracle plus OMF SEGDEF name"})
    order_constraints = {
        "scope": "routing/layout evidence only; RAWDEBT objects are never recovery credit",
        "topology_basis": "evidence/topology/build-topology.json and docs/build-topology.md; within one logical segment LINK follows object order; explicit objects precede library members",
        "segment_orders": segment_orders,
        "raw_gap_spans": {str(k): v for k, v in sorted(spans.items())},
        "counts": {"unique_manifest_objects": len(layouts), "layout_failures": len(failures),
                   "raw_gap_spans": sum(map(len, spans.values())),
                   "raw_chain_sites": sum(len(v) for v in raw_chain_sites.values()),
                   "logical_segment_groups": len(segment_orders)},
        "layout_failures": failures,
        "known_unresolved_topology": [
            "GR_MODULE and ANTEDIT_MODULE contain packed logical segments whose historical boundaries/names are not fully observed from the EXE; see docs/build-topology.md",
            "the image ledger reports %d overlapping claim-conflict groups totaling %d bytes; incompatible isolated members must be merged before a production LINK" % (len(ledger["merge"]), sum(x["bytes"] for x in ledger["merge"])),
            "runtime library partition is not distinguishable from explicit objects after the CRT; see docs/build-topology.md"],
    }
    # Compact evidence contains no oracle payload bytes.
    stub = raw[512:1024]
    stub_exe = (ROOT / DEF_STUB).read_bytes()
    evidence = {
        "schema_version": 1,
        "scope": "LINK-container investigation; raw placeholder OMF contributions are scaffolding only",
        "oracle": {"size": len(raw), "sha256": _sha(raw)},
        "def": {"path": "build/workers/linkdef-2/SIMANTW.DEF", "directives": def_lines,
                "exports": exports, "stub": {"source": DEF_STUB, "source_sha256": _sha(stub_exe),
                    "oracle_body_sha256": _sha(stub[:98]), "oracle_stub_area_bytes": len(stub),
                    "body_bytes": 98, "body_equal": stub[:98] == stub_exe[512:],
                    "oracle_tail_all_zero": not any(stub[98:])}},
        "ne_header": {k: image["header"][k] for k in (
            "linker_major", "linker_minor", "flags", "automatic_data_segment", "heap_size", "stack_size",
            "cs", "ip", "ss", "sp", "segment_count", "module_count", "alignment_shift", "target_os",
            "other_flags", "expected_windows_version")},
        "segments": [{k: s[k] for k in ("number", "flags", "kind", "logical_size", "allocation_size", "relocations") if k != "relocations"}
                     | {"name": seg_names[s["number"]], "relocation_records": len(s["relocations"])} for s in image["segments"]],
        "resident_names": image["resident_names"], "nonresident_names": image["nonresident_names"],
        "module_references": image["modules"], "imported_names": image["imported_names"],
        "link_order": order_constraints,
        "ledger": {"status": ledger["status"], "owned": ledger["owned"], "debt": ledger["debt"],
                   "claim_conflicts": ledger["claim_conflicts"]},
    }
    if write:
        WORK.mkdir(parents=True, exist_ok=True)
        EVIDENCE.mkdir(parents=True, exist_ok=True)
        (WORK / "SIMANTW.DEF").write_text(def_text, encoding="ascii")
        write_json(EVIDENCE_CONTAINER, evidence)
        write_json(WORK / "layout-model.json", {"objects": layouts, "known_publics": sorted(known_publics),
                     "spans": {str(k): v for k, v in spans.items()}})
    return {"raw": raw, "image": image, "symbols": symbols, "ledger": ledger, "manifest": manifest,
            "def": def_text, "def_lines": def_lines, "exports": exports, "layouts": layouts,
            "owned": owned, "known_publics": known_publics, "failures": failures,
            "spans": spans, "raw_chain_sites": raw_chain_sites, "evidence": evidence}


def build_omf(module_name, active_name, active_class, payload, publics=(), externals=(), fixups=(), extra_segments=()):
    """Serialize one RAWDEBT scaffolding contribution as a valid OMF module."""
    names = []
    def name_index(value):
        if value not in names:
            names.append(value)
        return names.index(value) + 1
    # A raw span already includes the alignment bytes present in the image.
    # Aligning every placeholder to a paragraph inserts new bytes before each
    # span and shifts following contributions; BYTE alignment preserves slots.
    seg_specs = [(active_name, active_class, len(payload), 1)]
    for spec in extra_segments:
        if all(spec[0] != row[0] for row in seg_specs):
            seg_specs.append(spec)
    group_classes = {"DATA", "CONST", "BSS", "BEGDATA"}
    group_members = [(i + 1, spec[0]) for i, spec in enumerate(seg_specs)
                     if spec[1] in group_classes]
    for spec in seg_specs:
        name_index(spec[0]); name_index(spec[1]); name_index("")
    if group_members:
        name_index("DGROUP")
    for ext in externals:
        name_index(ext)
    for public in publics:
        name_index(public[0])
    records = [_omf_record(0x80, bytes([len(module_name)]) + module_name.encode("ascii"))]
    records.append(_omf_record(0x96, b"".join(_omf_name(x) for x in names)))
    segment_indexes = {spec[0]: i + 1 for i, spec in enumerate(seg_specs)}
    for seg_name, seg_class, length, alignment in seg_specs:
        if length > 0xFFFF:
            raise FormatError("placeholder contribution exceeds 64K")
        acbp = (alignment << 5) | (2 << 2)
        body = bytes([acbp]) + _le16(length) + _omf_index(name_index(seg_name))
        body += _omf_index(name_index(seg_class)) + _omf_index(name_index(""))
        records.append(_omf_record(0x98, body))
    if group_members:
        body = _omf_index(name_index("DGROUP"))
        for index, _ in group_members:
            body += b"\xff" + _omf_index(index)
        records.append(_omf_record(0x9A, body))
    if externals:
        records.append(_omf_record(0x8C, b"".join(_omf_name(x) + b"\x00" for x in externals)))
    if publics:
        body = b"\x00" + _omf_index(1)
        for name, offset in publics:
            body += _omf_name(name) + _le16(offset) + b"\x00"
        records.append(_omf_record(0x90, body))
    by_site = sorted(fixups, key=lambda x: (x["site"], x.get("target_method", 0), x.get("target_index", 0)))
    pos = 0
    while pos < len(payload):
        end = min(pos + 900, len(payload))
        crossing = [f["site"] for f in by_site if f["site"] < end < f["site"] + f["width"]]
        if crossing:
            end = min(crossing)
        if end <= pos:
            raise FormatError("could not split LEDATA around a fixup")
        records.append(_omf_record(0xA0, _omf_index(1) + _le16(pos) + payload[pos:end]))
        chunk_fixups = [f for f in by_site if pos <= f["site"] and f["site"] + f["width"] <= end]
        if chunk_fixups:
            body = bytearray()
            for f in chunk_fixups:
                local = f["site"] - pos
                if local > 1023:
                    raise FormatError("FIXUPP local offset exceeds 10 bits")
                loc = f["location_type"]
                body += bytes([0xC0 | (loc << 2) | (local >> 8), local & 0xFF])
                frame_method = f.get("frame_method", 0)
                target_method = f.get("target_method", 0)
                displacement = f.get("displacement")
                fd = (frame_method << 4) | target_method
                if displacement is None:
                    fd |= 0x04
                body.append(fd)
                if frame_method not in (4, 5):
                    body += _omf_index(f.get("frame_index", 1))
                body += _omf_index(f.get("target_index", 1))
                if displacement is not None:
                    body += _le16(displacement & 0xFFFF)
            records.append(_omf_record(0x9C, bytes(body)))
        pos = end
    records.append(_omf_record(0x8A, b"\x00"))
    result = b"".join(records)
    omf.parse(result)
    return result


def _active_for_raw_span(model, segnum, span):
    seg_names = _segment_name_by_number(model["image"], model["symbols"])
    if segnum <= 7:
        rows = [c for obj in model["layouts"] for c in obj["contributions"]
                if c["ne_segment"] == segnum and c["class"] == "CODE"]
        before = [c for c in rows if c["end"] <= span["start"]]
        after = [c for c in rows if c["start"] >= span["end"]]
        left = max(before, key=lambda x: x["end"], default=None)
        right = min(after, key=lambda x: x["start"], default=None)
        if left and right and left["logical_segment"] == right["logical_segment"]:
            return left["logical_segment"], "CODE"
        if left and span["start"] - left["end"] <= 64:
            return left["logical_segment"], "CODE"
        if right and right["start"] - span["end"] <= 64:
            return right["logical_segment"], "CODE"
        return seg_names[segnum], "CODE"
    if segnum == 8:
        return seg_names[segnum], "FAR_DATA"
    if segnum == 9:
        return seg_names[segnum], "FAR_DATA"
    if segnum == 10:
        if span["start"] >= 51808:
            return "_BSS", "BSS"
        if 0xBE6E <= span["start"] and span["end"] <= 0xC6DF:
            return "CONST", "CONST"
        rows = [c for obj in model["layouts"] for c in obj["contributions"]
                if c["ne_segment"] == 10 and c["class"] in {"DATA", "CONST", "BSS", "BEGDATA"}]
        before = [c for c in rows if c["end"] <= span["start"]]
        after = [c for c in rows if c["start"] >= span["end"]]
        left = max(before, key=lambda x: x["end"], default=None)
        right = min(after, key=lambda x: x["start"], default=None)
        chosen = left or right
        if left and right and left["class"] == right["class"]:
            chosen = left
        if chosen:
            return chosen["logical_segment"], chosen["class"]
        return "_DATA", "DATA"
    raise FormatError("no OMF section mapping for NE segment %d" % segnum)


def _symbol_near(symbols, segnum, offset):
    segment = next(s for s in symbols["segments"] if s["number"] == segnum)
    rows = [p for p in segment["symbols"] if p["offset"] <= offset]
    if not rows:
        return None
    return max(rows, key=lambda p: (p["offset"], p["table_order"]))


def _raw_fixup_target(reloc, site, model, import_reverse, export_by_ordinal):
    target = reloc["target"]
    if target["kind"] == "import":
        key = (target["module"], target.get("ordinal"), target.get("name"))
        options = import_reverse.get(key, [])
        if options:
            return {"target_method": 2, "symbol": sorted(options)[0], "frame_method": 5,
                    "frame_index": None, "displacement": 0}
        if target["module"] == "WIN87EM" and target.get("ordinal") == 1:
            return {"target_method": 2, "symbol": "__RAWIMP_WIN87EM_1", "frame_method": 5,
                    "frame_index": None, "displacement": 0, "def_import": "__RAWIMP_WIN87EM_1=WIN87EM.1"}
        raise FormatError("no import-library or DEF binding for %r" % (target,))
    if target["kind"] == "entry":
        item = export_by_ordinal.get(target["ordinal"])
        symbol = (item or {}).get("internal_public")
        if not symbol:
            raise FormatError("NE entry relocation ordinal %d has no exact MAPSYM public" % target["ordinal"])
        return {"target_method": 2, "symbol": symbol, "frame_method": 5,
                "frame_index": None, "displacement": 0}
    if target["kind"] == "internal":
        target_seg, target_off = target["segment"], target["offset"]
        public = _symbol_near(model["symbols"], target_seg, target_off)
        if public:
            return {"target_method": 2, "symbol": public["name"], "frame_method": 5,
                    "frame_index": None, "displacement": target_off - public["offset"]}
        # Unnamed internal targets retain segment/offset semantics as explicit OMF fixups.
        return {"target_method": 0, "target_segment": target_seg, "frame_method": 0,
                "displacement": target_off}
    if target["kind"] == "os_fixup":
        kind = target["type"]
        helpers = {3: "FICRQQ", 4: "FIERQQ", 5: "FIDRQQ", 6: "FIWRQQ"}
        if kind not in helpers:
            raise FormatError("uncalibrated NE OS fixup type %d" % kind)
        if kind == 3:
            seg = model["image"]["segments"][reloc["_seg"] - 1]
            b = model["raw"][seg["file_offset"] + site:seg["file_offset"] + site + 2]
            if b != b"\x9b\x2e":
                raise FormatError("type-3 OS fixup at %d:%04X is not calibrated 9B 2E form" % (reloc["_seg"], site))
            return {"target_method": 2, "symbol": "FICRQQ", "frame_method": 5,
                    "frame_index": None, "displacement": 0,
                    "partner": {"target_method": 2, "symbol": "FJCRQQ", "frame_method": 5,
                                 "frame_index": None, "displacement": 0, "relative_site": 1}}
        return {"target_method": 2, "symbol": helpers[kind], "frame_method": 5,
                "frame_index": None, "displacement": 0}
    raise FormatError("unsupported NE relocation target kind " + str(target["kind"]))


def _pair_segment_frame(target):
    """Keep a segment-relative OMF frame on the internal target SEGDEF."""
    if target.get("frame_method") == 0 and target.get("frame_index") is None:
        target["frame_index"] = target["target_index"]
    return target


def _carve_crt0msg_member(model):
    """Extract the exact pinned CRT0MSG member and remove its bytes from RAWDEBT.

    MAPSYM anchors _DATA through __adbgmsg; MSG is uniquely byte-placed and
    PAD is required to immediately follow it.  The member has no fixups, so
    these contributions can be carried by LINK without synthesizing fixups.
    """
    library_rel = "toolchain/sdk300/CLIB/LLIBCW.LIB"
    library_path = ROOT / library_rel
    module_bytes = None
    module = None
    for candidate in omf.library_modules(library_path.read_bytes()):
        try:
            parsed = omf.parse(candidate)
        except FormatError:
            continue
        if parsed["name"].lower() == "dos\\crt0msg.asm":
            module_bytes, module = candidate, parsed
            break
    if module is None:
        raise FormatError("pinned CRT library lacks dos\\crt0msg.asm")
    if module["fixups"]:
        raise FormatError("CRT0MSG member fixup layout changed; cannot safely carve it")

    ne_seg = model["image"]["segments"][9]
    if ne_seg["number"] != 10:
        raise FormatError("expected NE data segment 10 for CRT0MSG placement")
    raw = model["raw"][ne_seg["file_offset"]:ne_seg["file_offset"] + ne_seg["logical_size"]]
    mapsym_segment = next(s for s in model["symbols"]["segments"] if s["number"] == 10)
    public = next((p for p in module["publics"] if p["name"] == "__adbgmsg" and p["segment"]), None)
    mapped = next((p for p in mapsym_segment["symbols"] if p["name"] == "__adbgmsg"), None)
    if public is None or mapped is None:
        raise FormatError("CRT0MSG __adbgmsg public/MAPSYM anchor missing")
    data_segment = module["segments"][public["segment"] - 1]
    data_start = mapped["offset"] - public["offset"]
    if data_segment["name"] != "_DATA" or data_start < 0:
        raise FormatError("CRT0MSG _DATA anchor is not the expected MAPSYM contribution")

    msg_segment = next((s for s in module["segments"] if s["name"] == "MSG" and s["length"]), None)
    pad_segment = next((s for s in module["segments"] if s["name"] == "PAD" and s["length"]), None)
    if not msg_segment or not pad_segment:
        raise FormatError("CRT0MSG MSG/PAD contributions missing")
    msg_bytes = bytes.fromhex(msg_segment["data_hex"])
    pad_bytes = bytes.fromhex(pad_segment["data_hex"])
    msg_start = raw.find(msg_bytes)
    if not msg_bytes or msg_start < 0 or raw.find(msg_bytes, msg_start + 1) >= 0:
        raise FormatError("CRT0MSG MSG bytes are not a unique data-segment placement")
    edata = next((p for p in mapsym_segment["symbols"] if p["name"] == "_edata"), None)
    if not pad_bytes or edata is None:
        raise FormatError("CRT0MSG PAD or exact _edata MAPSYM boundary missing")
    # PAD is a distinct OMF segment class/name. LINK coalesces the runtime
    # message segments before the initialized-data boundary; its two 0xFF
    # bytes are therefore anchored by the unique matching suffix immediately
    # before MAPSYM _edata, with zero alignment bytes between PAD and _edata.
    pad_candidates = [p for p in range(max(0, edata["offset"] - 16),
                                      edata["offset"] - len(pad_bytes) + 1)
                      if raw[p:p + len(pad_bytes)] == pad_bytes
                      and not any(raw[p + len(pad_bytes):edata["offset"]])]
    if len(pad_candidates) != 1:
        raise FormatError("CRT0MSG PAD has no unique initialized-data suffix placement")
    pad_start = pad_candidates[0]
    if pad_start < msg_start + len(msg_bytes):
        raise FormatError("CRT0MSG PAD suffix precedes its MSG contribution")

    claims = []
    for segment, start in ((data_segment, data_start), (msg_segment, msg_start), (pad_segment, pad_start)):
        payload = bytes.fromhex(segment["data_hex"])
        end = start + len(payload)
        if end > len(raw) or raw[start:end] != payload:
            raise FormatError("CRT0MSG %s bytes do not match their target placement" % segment["name"])
        claims.append({"segment": segment["name"], "class": segment["class"],
                       "start": start, "end": end, "sha256": _sha(payload)})

    spans = model["spans"][10]
    sites = [(r, q) for r in ne_seg["relocations"] for q in r["sites"]]
    chains = set(model["raw_chain_sites"].get(10, []))
    carve_issues = []
    for claim in claims:
        a, b = claim["start"], claim["end"]
        if not any(span["start"] <= a and b <= span["end"] for span in spans):
            carve_issues.append({"segment": claim["segment"], "reason": "current ledger has admitted coverage or splits the runtime interval"})
        if any(a <= q < b for _, q in sites) or any(a <= q < b for q in chains):
            carve_issues.append({"segment": claim["segment"], "reason": "interval intersects an NE loader or chain site"})
    if carve_issues:
        evidence = {"library": library_rel, "library_sha256": identity(library_path)["sha256"],
            "member": module["name"], "member_sha256": _sha(module_bytes), "claims": claims,
            "included": False, "omitted_reasons": carve_issues,
            "scope": "pinned runtime member omitted because current admitted objects own part of its mapped interval"}
        model["runtime_library_claims"] = []
        model["runtime_library_skips"] = [evidence]
        model["evidence"]["runtime_library_skips"] = [evidence]
        write_json(EVIDENCE_CONTAINER, model["evidence"])
        return evidence

    model["spans"][10] = _subtract_spans(spans, claims)
    member_path = WORK / "objects" / "RUNTIME_CRT0MSG.OBJ"
    member_path.parent.mkdir(parents=True, exist_ok=True)
    member_path.write_bytes(module_bytes)
    evidence = {"library": library_rel, "library_sha256": identity(library_path)["sha256"],
        "member": module["name"], "member_sha256": _sha(module_bytes),
        "object": member_path.relative_to(ROOT).as_posix(), "claims": claims,
        "placement_basis": ["_DATA anchored by exact __adbgmsg MAPSYM public",
                            "MSG byte sequence has a unique placement in NE segment 10",
                            "PAD uniquely matches the suffix before MAPSYM _edata after zero alignment"],
        "fixups": len(module["fixups"]), "scope": "pinned runtime library member; never RAWDEBT or recovered source"}
    model["runtime_library_claims"] = [evidence]
    model["runtime_library_skips"] = []
    order = model["evidence"]["link_order"]
    order["raw_gap_spans"]["10"] = model["spans"][10]
    order["counts"]["raw_gap_spans"] = sum(map(len, model["spans"].values()))
    order["counts"]["raw_chain_sites"] = sum(len(x) for x in model["raw_chain_sites"].values())
    full_orders = defaultdict(list)
    for layout in model["layouts"]:
        for c in layout["contributions"]:
            full_orders[(c["ne_segment"], c["logical_segment"])].append({
                "kind": "ADMITTED_" + layout["group"], "object": layout["object"],
                "start": c["start"], "end": c["end"], "class": c["class"]})
    for segnum, spans in model["spans"].items():
        for gap_index, span in enumerate(spans):
            logical, cls = _active_for_raw_span(model, segnum, span)
            full_orders[(segnum, logical)].append({
                "kind": "RAWDEBT", "object": "RAWDEBT_S%02d_G%03d.OBJ" % (segnum, gap_index),
                "start": span["start"], "end": span["end"], "class": cls})
    for claim in claims:
        full_orders[(10, claim["segment"])].append({
            "kind": "RUNTIME_MEMBER", "object": "RUNTIME_CRT0MSG.OBJ",
            "start": claim["start"], "end": claim["end"], "class": claim["class"]})
    order["logical_orders_with_gaps"] = [
        {"ne_segment": segnum, "logical_segment": logical,
         "contributions": sorted(rows, key=lambda x: (x["start"], x["end"], x["kind"], x["object"]))}
        for (segnum, logical), rows in sorted(full_orders.items())]
    order["counts"]["ordered_contributions_with_gaps"] = sum(map(len, full_orders.values()))
    write_json(EVIDENCE_ORDER, {
        "scope": "oracle placement constraints; RAWDEBT rows are scaffolding and receive zero recovery credit",
        "oracle_sha256": model["evidence"]["oracle"]["sha256"],
        "topology_basis": order["topology_basis"],
        "sort_rule": "within each NE segment and logical SEGDEF, contributions are ordered by strict oracle start/end offsets; RAWDEBT gaps and pinned runtime members are explicit rows",
        "counts": order["counts"],
        "logical_orders": order["logical_orders_with_gaps"]})
    order.pop("logical_orders_with_gaps")
    order["detail_path"] = EVIDENCE_ORDER.relative_to(ROOT).as_posix()
    model["evidence"]["runtime_library_claims"] = [evidence]
    write_json(EVIDENCE_CONTAINER, model["evidence"])
    write_json(WORK / "layout-model.json", {"objects": model["layouts"],
        "known_publics": sorted(model["known_publics"]),
        "spans": {str(k): v for k, v in model["spans"].items()},
        "runtime_library_claims": [evidence]})
    return evidence


def package():
    model = analyze(write=True)
    runtime_claim = _carve_crt0msg_member(model)
    import_rows = library_match.import_symbols(ROOT / "toolchain/sdk300/WLIB/LIBW.LIB")
    import_reverse = defaultdict(list)
    for symbol, target in import_rows.items():
        import_reverse[(target.get("module"), target.get("ordinal"), target.get("name"))].append(symbol)
    exports = {x["ordinal"]: x for x in model["exports"]}
    public_by_segment = {s["number"]: s["symbols"] for s in model["symbols"]["segments"]}
    existing_publics = set(model["known_publics"])
    object_dir = WORK / "objects"
    object_dir.mkdir(parents=True, exist_ok=True)
    spans_by_seg = model["spans"]
    packaged = []
    raw_fixup_sites = set()
    def_imports = set()
    selector_alias = "_pool_segment_ref_SIMANT_DATA_GROUP"
    needs_selector_alias = any(
        ext["name"] == selector_alias
        for layout in model["layouts"]
        for ext in omf.parse((ROOT / layout["object"]).read_bytes())["externals"])
    if needs_selector_alias and selector_alias not in existing_publics:
        # Scaffolded TU members use this external only as an OMF reference to
        # the beginning of the original far-data logical segment.  A zero-byte
        # RAWDEBT bridge supplies that linker name without copying or crediting
        # any executable/data bytes.
        module = "RAWDEBT_SELECTOR_SIMANT_DATA_GROUP"
        out_path = object_dir / (module + ".OBJ")
        omf_bytes = build_omf(module, "SIMANT_DATA_GROUP", "FAR_DATA", b"",
                              publics=[(selector_alias, 0)])
        out_path.write_bytes(omf_bytes)
        packaged.append({"object": out_path.relative_to(ROOT).as_posix(), "module": module,
            "ne_segment": 8, "start": 0, "end": 0,
            "logical_segment": "SIMANT_DATA_GROUP", "class": "FAR_DATA",
            "public_count": 1, "omf_fixup_count": 0, "ne_relocation_site_count": 0,
            "rawdebt_bytes": 0, "scaffolding_role": "selector-symbol bridge; no image bytes",
            "identity": identity(out_path)})
    for segnum, spans in sorted(spans_by_seg.items()):
        ne_seg = model["image"]["segments"][segnum - 1]
        seg_bytes = model["raw"][ne_seg["file_offset"]:ne_seg["file_offset"] + ne_seg["logical_size"]]
        for gap_index, span in enumerate(spans):
            active_name, active_class = _active_for_raw_span(model, segnum, span)
            payload = bytearray(seg_bytes[span["start"]:span["end"]])
            fixups = []
            externals = []
            extras = []
            for reloc in ne_seg["relocations"]:
                for site in reloc["sites"]:
                    touched = set(range(site, min(site + reloc["width"], ne_seg["logical_size"])))
                    raw_touched = touched.intersection(range(span["start"], span["end"]))
                    if not raw_touched:
                        continue
                    if len(raw_touched) != len(touched):
                        raise FormatError("NE relocation crosses placeholder/owned boundary at %d:%04X" % (segnum, site))
                    if any(p in model["owned"][segnum] for p in touched):
                        raise FormatError("NE relocation site overlaps admitted member and raw placeholder at %d:%04X" % (segnum, site))
                    row = dict(reloc)
                    row["_seg"] = segnum
                    target = _raw_fixup_target(row, site, model, import_reverse, exports)
                    if target.get("def_import"):
                        def_imports.add(target["def_import"])
                    sym = target.pop("symbol", None)
                    if sym:
                        if sym not in externals:
                            externals.append(sym)
                        target["target_index"] = externals.index(sym) + 1
                    elif target["target_method"] == 0:
                        target_seg = target.pop("target_segment")
                        extra_name = _segment_name_by_number(model["image"], model["symbols"])[target_seg]
                        if target_seg == 10:
                            extra_name, extra_class = "_DATA", "DATA"
                        else:
                            extra_class = "FAR_DATA" if target_seg in (8, 9) else "CODE"
                        if extra_name == active_name:
                            target["target_index"] = 1
                        else:
                            if not any(x[0] == extra_name for x in extras):
                                extras.append((extra_name, extra_class, 0, 3))
                            target["target_index"] = 1 + next(i for i, x in enumerate(extras) if x[0] == extra_name)
                        # OMF frame method 0 carries a SEGDEF index. Keep it
                        # paired with the internal target SEGDEF; defaulting
                        # every such frame to segment 1 silently changes the
                        # NE relocation's segment-relative meaning.
                        _pair_segment_frame(target)
                    target["site"] = site - span["start"]
                    target["location_type"] = reloc["source_type"]
                    target["width"] = reloc["width"]
                    fixups.append(target)
                    raw_fixup_sites.add((segnum, site))
                    partner = target.get("partner")
                    if partner:
                        ps = site + partner.pop("relative_site")
                        if ps + partner.get("width", 2) > span["end"]:
                            raise FormatError("paired OS fixup crosses RAWDEBT object boundary at %d:%04X" % (segnum, site))
                        if not any((segnum, ps) == x for x in raw_fixup_sites):
                            partner.update({"site": ps - span["start"], "location_type": 1, "width": 2,
                                            "target_index": None})
                            if partner["symbol"] not in externals:
                                externals.append(partner["symbol"])
                            partner["target_index"] = externals.index(partner["symbol"]) + 1
                            partner.pop("symbol", None)
                            fixups.append(partner)
                            raw_fixup_sites.add((segnum, ps))
                    if not reloc["additive"]:
                        payload[target["site"]:target["site"] + 2] = b"\x00\x00"
            publics = []
            for sym in public_by_segment.get(segnum, []):
                if span["start"] <= sym["offset"] < span["end"] and sym["name"] not in existing_publics:
                    public = (sym["name"], sym["offset"] - span["start"])
                    if public not in publics:
                        publics.append(public)
                        existing_publics.add(sym["name"])
            module = "RAWDEBT_S%02d_G%03d" % (segnum, gap_index)
            object_name = module + ".OBJ"
            out_path = object_dir / object_name
            omf_bytes = build_omf(module, active_name, active_class, bytes(payload),
                                  publics=publics, externals=externals, fixups=fixups,
                                  extra_segments=extras)
            out_path.write_bytes(omf_bytes)
            parsed = omf.parse(omf_bytes)
            packaged.append({"object": out_path.relative_to(ROOT).as_posix(), "module": module,
                "ne_segment": segnum, "start": span["start"], "end": span["end"],
                "logical_segment": active_name, "class": active_class,
                "public_count": len(publics), "omf_fixup_count": len(parsed["fixups"]),
                "ne_relocation_site_count": sum(1 for x in raw_fixup_sites if x[0] == segnum and span["start"] <= x[1] < span["end"]),
                "identity": identity(out_path)})
    # Every relocation source site outside admitted contributions must exist in one RAWDEBT module.
    expected_sites = set()
    for ne_seg in model["image"]["segments"]:
        for reloc in ne_seg["relocations"]:
            for site in reloc["sites"]:
                touched = range(site, min(site + reloc["width"], ne_seg["logical_size"]))
                if not any(p in model["owned"][ne_seg["number"]] for p in touched):
                    expected_sites.add((ne_seg["number"], site))
    missing = sorted(expected_sites - raw_fixup_sites)
    if missing:
        raise FormatError("RAWDEBT package missed %d NE relocation source sites; first=%r" % (len(missing), missing[0]))
    def_text = model["def"]
    if def_imports:
        def_text = def_text.rstrip() + "\n\nIMPORTS\n" + "".join("  %s\n" % x for x in sorted(def_imports))
        evidence = model["evidence"]
        for statement in sorted(def_imports):
            evidence["def"]["directives"].append({"line": statement, "source": "NE import relocation target not named by the Windows import libraries", "interpretation": "define missing imported module/ordinal from the original relocation table"})
        EVIDENCE_CONTAINER.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    (WORK / "SIMANTW.DEF").write_text(def_text, encoding="ascii")
    receipt = {"scope": "RAWDEBT placeholders only; zero recovery credit",
        "objects": packaged, "object_count": len(packaged), "raw_ne_relocation_sites": len(raw_fixup_sites),
        "expected_raw_ne_relocation_sites": len(expected_sites), "missing_sites": missing,
        "runtime_library_members": [runtime_claim],
        "def_imports": sorted(def_imports),
        "limitations": ["Every copied byte remains explicit raw debt", "Raw section names are inferred from mapped neighbors; hidden original logical-segment names are not recoverable from MAPSYM"]}
    write_json(WORK / "rawdebt-package.json", receipt)
    return model, packaged, receipt


def _link_input_key(row):
    """Stable tie breaker after hard per-logical-segment constraints."""
    contributions = row.get("layout", {}).get("contributions", [])
    if not contributions and row.get("kind") == "RAWDEBT":
        contributions = [{"ne_segment": row.get("ne_segment", 99),
                          "start": row.get("start", 0)}]
    anchor = min(((c.get("ne_segment", 99), c.get("start", 0)) for c in contributions),
                 default=(99, 0))
    return (anchor[0], anchor[1], row["object"])


def _order_link_inputs(rows):
    """Topologically order modules using measured contribution positions.

    LINK consumes one global object list, so every logical SEGDEF contribution
    imposes an order on the same list.  Sorting by only DGROUP or one code
    anchor can silently reverse another segment; this graph keeps all measured
    constraints and reports overlaps that the image ledger already identifies.
    """
    by_segment = defaultdict(list)
    nodes = {row["object"]: row for row in rows}
    for row in rows:
        for c in row.get("layout", {}).get("contributions", []):
            name = c.get("logical_segment", c.get("segment"))
            if name is None:
                continue
            by_segment[(c.get("ne_segment", 99), name, c.get("class"))].append({
                "object": row["object"], "start": c["start"], "end": c["end"],
                "ne_segment": c.get("ne_segment", 99)})

    edges = set()
    overlaps = []
    name_to_ne = defaultdict(set)
    for (ne_segment, segment, cls), records in sorted(by_segment.items()):
        name_to_ne[(segment, cls)].add(ne_segment)
        records.sort(key=lambda x: (x["start"], x["end"], x["object"]))
        for i, left in enumerate(records):
            for right in records[i + 1:]:
                if left["object"] == right["object"]:
                    continue
                if left["end"] <= right["start"]:
                    edges.add((left["object"], right["object"]))
                elif right["end"] <= left["start"]:
                    edges.add((right["object"], left["object"]))
                else:
                    overlaps.append({"ne_segment": ne_segment,
                        "logical_segment": segment, "class": cls,
                        "left": left, "right": right})

    outgoing = {name: set() for name in nodes}
    indegree = {name: 0 for name in nodes}
    for before, after in edges:
        if after not in outgoing[before]:
            outgoing[before].add(after)
            indegree[after] += 1
    ready = sorted((name for name, degree in indegree.items() if degree == 0),
                   key=lambda name: _link_input_key(nodes[name]))
    ordered = []
    while ready:
        name = ready.pop(0)
        ordered.append(nodes[name])
        for after in sorted(outgoing[name], key=lambda x: _link_input_key(nodes[x])):
            indegree[after] -= 1
            if indegree[after] == 0:
                ready.append(after)
                ready.sort(key=lambda x: _link_input_key(nodes[x]))
    cycles = sorted((name for name, degree in indegree.items() if degree),
                    key=lambda name: _link_input_key(nodes[name]))
    ordered.extend(nodes[name] for name in cycles)
    reused_names = [{"logical_segment": segment, "class": cls,
        "ne_segments": sorted(ne_segments)}
        for (segment, cls), ne_segments in sorted(name_to_ne.items()) if len(ne_segments) > 1]
    facts = {"basis": "topological order of strict member and RAWDEBT interval positions per target NE segment and OMF logical segment",
        "node_count": len(nodes), "constraint_count": len(edges),
        "overlap_count": len(overlaps), "cycle_count": len(cycles),
        "logical_names_reused_across_ne_segments": reused_names,
        "reused_name_count": len(reused_names),
        "overlaps": overlaps[:64], "cycle_objects": cycles,
        "ordered_objects": [row["object"] for row in ordered]}
    return ordered, facts


def link(out_path="build/workers/linkdef-2/LINKED.EXE", pack_code=True):
    model, packaged, package_receipt = package()
    out = WORK / "link"
    out.mkdir(parents=True, exist_ok=True)
    in_dir = out
    in_dir.mkdir(parents=True, exist_ok=True)
    # Include each distinct admitted object exactly once. Repeated manifest rows identify the same OMF.
    rows = []
    by_digest = {}
    for layout in model["layouts"]:
        digest = layout["sha256"]
        if digest in by_digest:
            continue
        src = ROOT / layout["object"]
        dest = in_dir / ("A%04d.OBJ" % len(by_digest))
        shutil.copyfile(src, dest)
        by_digest[digest] = dest
        rows.append({"kind": "ADMITTED_" + layout["group"], "object": dest.name, "layout": layout,
                     "path": dest, "identity": identity(dest)})
    for member in model.get("runtime_library_claims", []):
        src = ROOT / member["object"]
        dest = in_dir / ("R%04d.OBJ" % len([x for x in rows if x["kind"] == "RUNTIME_MEMBER"]))
        shutil.copyfile(src, dest)
        anchor = next(c["start"] for c in member["claims"] if c["segment"] == "_DATA")
        rows.append({"kind": "RUNTIME_MEMBER", "object": dest.name, "ne_segment": 10,
                     "start": anchor, "path": dest, "identity": identity(dest),
                     "layout": {"contributions": [{"logical_segment": c["segment"],
                         "class": c["class"], "ne_segment": 10,
                         "start": c["start"], "end": c["end"], "length": c["end"] - c["start"]}
                         for c in member["claims"]]},
                     "runtime_member": member["member"]})
    for item in packaged:
        src = ROOT / item["object"]
        dest = in_dir / ("P%04d.OBJ" % len([x for x in rows if x["kind"] == "RAWDEBT"]))
        shutil.copyfile(src, dest)
        rows.append({"kind": "RAWDEBT", "object": dest.name, "ne_segment": item["ne_segment"],
                     "start": item["start"], "path": dest, "identity": identity(dest),
                     "layout": {"contributions": [{"logical_segment": item["logical_segment"],
                         "class": item["class"], "ne_segment": item["ne_segment"],
                         "start": item["start"], "end": item["end"],
                         "length": item["end"] - item["start"]}]}})
    rows, input_order_constraints = _order_link_inputs(rows)
    write_json(WORK / "link-order-constraints.json", input_order_constraints)
    object_names = [x["object"] for x in rows]
    lib_sources = {
        "CRT.LIB": "toolchain/sdk300/CLIB/LLIBCW.LIB",
        "FP.LIB": "toolchain/sdk300/CLIB/LLIBFPW.LIB",
        "HELPER.LIB": "toolchain/sdk300/CLIB/LIBH.LIB",
        "WIN.LIB": "toolchain/sdk300/WLIB/LIBW.LIB",
    }
    for dest, src in lib_sources.items():
        shutil.copyfile(ROOT / src, out / dest)
    shutil.copyfile(ROOT / DEF_STUB, out / "WINSTUB.EXE")
    shutil.copyfile(WORK / "SIMANTW.DEF", out / "SIMANTW.DEF")
    output_name = Path(out_path).name
    code_packing_switch = "/PACKCODE" if pack_code else "/NOPACKCODE"
    rsp = "+\n".join(object_names) + ",\n" + output_name + ",\nSIMANTW.MAP,\n" + "+".join(lib_sources) + ",\nSIMANTW.DEF /NOD /NOI /MAP " + code_packing_switch + ";\n"
    (out / "SIMANTW.RSP").write_text(rsp, encoding="ascii")
    lock = read_json(ROOT / "layout/toolchain.json")
    runner = ROOT / lock["runner"]
    linker = ROOT / "toolchain/msc700/BIN/LINK.EXE"
    command = [str(runner), "-d", str(linker), "@SIMANTW.RSP"]
    exe = out / output_name
    # Remove only this worker's stale candidate before LINK runs. LINK can emit a
    # structurally useful NE file and still exit nonzero when some fixups fail.
    if exe.exists():
        exe.unlink()
    result = subprocess.run(command, cwd=out, capture_output=True, timeout=300)
    log = (result.stdout + result.stderr).decode("latin1", errors="replace")
    (out / "link.log").write_text(log, encoding="latin1")
    report = {"scope": "RAWDEBT placeholders plus admitted OMF objects; placeholders receive no recovery credit",
        "code_packing": code_packing_switch,
        "input_order_constraints": {k:v for k,v in input_order_constraints.items() if k != "ordered_objects"},
        "command": command, "exit_code": result.returncode, "linker": identity(linker),
        "def": identity(out / "SIMANTW.DEF"), "stub": identity(out / "WINSTUB.EXE"),
         "input_object_count": len(rows), "rawdebt_object_count": len(packaged),
         "runtime_library_member_count": sum(1 for x in rows if x["kind"] == "RUNTIME_MEMBER"),
        "rawdebt_fixup_sites": package_receipt["raw_ne_relocation_sites"],
        "link_error_count": len(re.findall(r"error L\d+:", log)),
        "link_error_codes": dict(Counter(re.findall(r"error (L\d+):", log))),
        "input_order": [{"kind": x["kind"], "object": x["object"], "ne_segment": x.get("ne_segment"), "start": x.get("start"), "runtime_member": x.get("runtime_member"), "identity": x["identity"]} for x in rows],
        "log": log}
    if exe.exists():
        out_target = ROOT / out_path
        out_target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(exe, out_target)
        report["output"] = identity(exe)
        report["delivered_candidate"] = out_target.relative_to(ROOT).as_posix()
        report["comparison"] = compare_outputs(model["raw"], exe.read_bytes())
        write_json(WORK / ("comparison-" + Path(output_name).stem + ".json"), report["comparison"])
        write_json(WORK / "comparison.json", report["comparison"])
    write_json(WORK / ("link-receipt-" + Path(output_name).stem + ".json"), report)
    write_json(WORK / "link-receipt.json", report)
    EVIDENCE.mkdir(parents=True, exist_ok=True)
    compact = {k:v for k,v in report.items() if k not in ("input_order", "log")}
    compact["input_order_sha256"] = _sha(json.dumps(report["input_order"], sort_keys=True).encode())
    compact["log_tail"] = "\n".join(log.splitlines()[-24:])
    write_json(EVIDENCE_RESULT, compact)
    print("LINK exit:", result.returncode, "objects:", len(rows), "RAWDEBT:", len(packaged))
    if exe.exists():
        print("Comparison:", report["comparison"]["different_region_count"], "different regions")
    else:
        print("LINK log:", "\n".join(log.splitlines()[-12:]))
    return result.returncode

def _byte_region_facts(expected_region, actual_region):
    return {
        "equal": expected_region == actual_region,
        "matching_bytes_at_region_offsets": sum(
            left == right for left, right in zip(expected_region, actual_region)),
        "common_prefix_bytes": next((i for i, (left, right) in enumerate(
            zip(expected_region, actual_region)) if left != right),
            min(len(expected_region), len(actual_region))),
    }


def compare_outputs(oracle_bytes, candidate_bytes):
    """Compare the NE container structurally and by raw region bytes."""
    expected = ne.parse(oracle_bytes)
    actual = ne.parse(candidate_bytes)
    rows = []
    def add(name, expected_region, actual_region, note="", excluded=False):
        facts = _byte_region_facts(expected_region, actual_region)
        rows.append({"region": name, "expected_bytes": len(expected_region), "actual_bytes": len(actual_region),
            **facts,
            "expected_sha256": _sha(expected_region), "actual_sha256": _sha(actual_region),
            "excluded_lane": excluded, "note": note})
    def table_bytes(data, image, start, size, relative=True):
        base = image["header"]["file_offset"] if relative else 0
        return data[base + start:base + start + size]
    for label, data, image in (("expected", oracle_bytes, expected), ("actual", candidate_bytes, actual)):
        pass
    en, an = expected["header"]["file_offset"], actual["header"]["file_offset"]
    add("DOS_MZ_HEADER", oracle_bytes[:expected["dos"]["header_paragraphs"] * 16],
        candidate_bytes[:actual["dos"]["header_paragraphs"] * 16])
    add("DOS_STUB_AND_PADDING", oracle_bytes[expected["dos"]["header_paragraphs"] * 16:en],
        candidate_bytes[actual["dos"]["header_paragraphs"] * 16:an],
        "The target stub body is independently checked against WINSTUB.EXE.")
    add("NE_HEADER", oracle_bytes[en:en + 64], candidate_bytes[an:an + 64])
    def off(image, field):
        return image["header"]["file_offset"] + image["header"][field]
    for name, field, size in (
        ("SEGMENT_TABLE", "segment_table_offset", 8 * expected["header"]["segment_count"]),
        ("RESIDENT_NAMES", "resident_table_offset", expected["header"]["module_table_offset"] - expected["header"]["resident_table_offset"]),
        ("MODULE_REFERENCES", "module_table_offset", expected["header"]["import_table_offset"] - expected["header"]["module_table_offset"]),
        ("IMPORTED_NAMES", "import_table_offset", expected["header"]["entry_table_offset"] - expected["header"]["import_table_offset"]),
        ("ENTRY_TABLE", "entry_table_offset", expected["header"]["entry_table_size"]),
    ):
        e_start = off(expected, field)
        a_start = off(actual, field)
        a_size = size
        if name == "SEGMENT_TABLE":
            a_size = 8 * actual["header"]["segment_count"]
        elif name in ("RESIDENT_NAMES", "MODULE_REFERENCES", "IMPORTED_NAMES"):
            next_field = {"RESIDENT_NAMES":"module_table_offset", "MODULE_REFERENCES":"import_table_offset", "IMPORTED_NAMES":"entry_table_offset"}[name]
            a_size = actual["header"][next_field] - actual["header"][field]
        elif name == "ENTRY_TABLE":
            a_size = actual["header"]["entry_table_size"]
        add(name, oracle_bytes[e_start:e_start + size], candidate_bytes[a_start:a_start + a_size])
    enon = expected["header"]["nonresident_table_offset"]
    anon = actual["header"]["nonresident_table_offset"]
    add("NONRESIDENT_NAMES", oracle_bytes[enon:enon + expected["header"]["nonresident_size"]],
        candidate_bytes[anon:anon + actual["header"]["nonresident_size"]])
    # Resource bytes belong to the independent RC lane; their table is measured, not compared.
    er_start, er_end = off(expected, "resource_table_offset"), off(expected, "resident_table_offset")
    ar_start, ar_end = off(actual, "resource_table_offset"), off(actual, "resident_table_offset")
    e_resource_payload = sum(x["size"] for x in expected["resources"])
    a_resource_payload = sum(x["size"] for x in actual["resources"])
    add("RESOURCE_TABLE_RC_LANE", oracle_bytes[er_start:er_end], candidate_bytes[ar_start:ar_end],
        "Resource table and payload are owned by the separate RC lane.", excluded=True)
    add("RESOURCE_PAYLOAD_RC_LANE", b"\x00" * e_resource_payload, b"\x00" * a_resource_payload,
        "Only sizes are compared here; payload bytes belong to the separate RC lane.", excluded=True)
    for index, es in enumerate(expected["segments"]):
        name = "SEGMENT_%02d" % (index + 1)
        if index >= len(actual["segments"]):
            rows.append({"region": name + "_DATA", "equal": False, "expected_bytes": es["logical_size"],
                         "actual_bytes": 0, "note": "candidate lacks segment"})
            continue
        ac = actual["segments"][index]
        e_data = oracle_bytes[es["file_offset"]:es["file_offset"] + es["logical_size"]] if es["file_offset"] is not None else b""
        a_data = candidate_bytes[ac["file_offset"]:ac["file_offset"] + ac["logical_size"]] if ac["file_offset"] is not None else b""
        add(name + "_DATA", e_data, a_data)
        er_size = 2 + 8 * len(es["relocations"]) if es.get("relocation_table_offset") is not None else 0
        ar_size = 2 + 8 * len(ac["relocations"]) if ac.get("relocation_table_offset") is not None else 0
        er_data = oracle_bytes[es["relocation_table_offset"]:es["relocation_table_offset"] + er_size] if er_size else b""
        ar_data = candidate_bytes[ac["relocation_table_offset"]:ac["relocation_table_offset"] + ar_size] if ar_size else b""
        add(name + "_RELOCATION_TABLE", er_data, ar_data)
        def chains(seg, data):
            out = bytearray()
            for reloc in seg["relocations"]:
                if reloc["additive"]:
                    continue
                for site in reloc["sites"]:
                    out += site.to_bytes(2, "little") + data[site:site + 2]
            return bytes(out)
        add(name + "_CHAIN_WORDS", chains(es, e_data), chains(ac, a_data))
    def padding(data, image):
        chunks = []
        for region in image["file_regions"]:
            if region["kind"] == "UNASSIGNED_OR_PADDING":
                chunks.append(data[region["start"]:region["end"]])
        return b"".join(chunks)
    add("FILE_PADDING", padding(oracle_bytes, expected), padding(candidate_bytes, actual))
    fields = ("linker_major", "linker_minor", "flags", "automatic_data_segment", "heap_size", "stack_size",
              "ip", "cs", "sp", "ss", "segment_count", "module_count", "nonresident_size",
              "segment_table_offset", "resource_table_offset", "resident_table_offset", "module_table_offset",
              "import_table_offset", "nonresident_table_offset", "movable_entry_count", "alignment_shift",
              "target_os", "other_flags", "return_thunk_offset", "segment_reference_offset", "expected_windows_version")
    field_diff = {k:{"expected":expected["header"][k],"actual":actual["header"][k]} for k in fields if expected["header"][k]!=actual["header"][k]}
    active = [x for x in rows if not x.get("excluded_lane")]
    return {"expected_size":len(oracle_bytes),"actual_size":len(candidate_bytes),"ne_header_field_differences":field_diff,
            "resource_lane": {"expected_resource_count":len(expected["resources"]),"actual_resource_count":len(actual["resources"]),
                              "expected_payload_bytes":e_resource_payload,"actual_payload_bytes":a_resource_payload},
            "regions":rows,"compared_region_count":len(active),
            "equal_region_count":sum(bool(x.get("equal")) for x in active),
            "different_region_count":sum(not bool(x.get("equal")) for x in active)}

def _write_analyze_files(model):
    pass


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="action", required=True)
    sub.add_parser("analyze", help="derive the DEF, NE evidence, and per-segment object order")
    sub.add_parser("package", help="build explicit RAWDEBT OMF placeholder objects")
    p_link = sub.add_parser("link", help="run pinned LINK 5.30 with recovered objects and RAWDEBT placeholders")
    p_link.add_argument("--out", default="build/workers/linkdef-2/LINKED.EXE")
    p_link.add_argument("--no-packcode", action="store_true", help="diagnostic run without /PACKCODE")
    p_cmp = sub.add_parser("compare", help="compare a linked NE executable by region")
    p_cmp.add_argument("candidate")
    args = parser.parse_args()
    if args.action == "analyze":
        model = analyze()
        print(json.dumps({"def": str(WORK / "SIMANTW.DEF"), "layout_model": str(WORK / "layout-model.json"),
            "evidence": str(EVIDENCE_CONTAINER), "layout_failures": len(model["failures"]),
            "raw_spans": sum(map(len, model["spans"].values()))}, indent=2))
    elif args.action == "package":
        _, _, receipt = package()
        print(json.dumps({"rawdebt_objects": receipt["object_count"], "relocation_sites": receipt["raw_ne_relocation_sites"], "package": str(WORK / "rawdebt-package.json")}, indent=2))
    elif args.action == "link":
        raise SystemExit(link(args.out, pack_code=not args.no_packcode))
    else:
        model = _oracle_model()
        result = compare_outputs(model[0], Path(args.candidate).read_bytes())
        WORK.mkdir(parents=True, exist_ok=True)
        write_json(WORK / "comparison.json", result)
        print(json.dumps({"comparison": str(WORK / "comparison.json"),
            "different_regions": result["different_region_count"],
            "header_differences": result["ne_header_field_differences"]}, indent=2))


if __name__ == "__main__":
    try:
        main()
    except FormatError as exc:
        raise SystemExit("ERROR: " + str(exc))
