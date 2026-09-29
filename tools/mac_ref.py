"""Read-only extraction and cross-reference tools for the supplied SimAnt Mac CD.

The extraction command understands ISO 9660, Apple Partition Map, classic HFS,
and Macintosh resource forks. The normal SYMBOL command disassembles a matched
Mac routine and reports cautious source-shape observations.
"""
from __future__ import annotations

import argparse
import ast
import collections
import hashlib
import json
import math
import re
import struct
import sys
from pathlib import Path

try:
    from capstone import Cs, CS_ARCH_M68K, CS_MODE_BIG_ENDIAN, CS_MODE_M68K_000
except ImportError:  # pragma: no cover - clear CLI error on unsupported hosts
    Cs = None

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ISO = Path(r"D:\Games\DOS\dos_recosystem\simantmac_forged\assets\SimAnt_CD.iso")
ORACLE_EXE_SHA256 = "538fed3f0fd60a6528a5e5b20990361ac4d274c58266a81e71c24f751612589d"
EXPECTED_ISO_SHA256 = "8e7518796dbf32db9ff483dcc49069d4d8ec6e4625918fe4d47b03de8cc5fb0b"
EXPECTED_HFS_SHA256 = "9646d9017e3f44836316dc907c34c738a09f1e0d32aec0d6126252943d3d3112"
EXPECTED_RSRC_SHA256 = "3e73ef63500bed0c666db56a25b5a5951c09d9a266c8c682f373b2825050f351"
EXPECTED_CODE = {
    0: (2936, "d6ac71166c6447dd50ab82a948a210ddf8be505764a72c3397f83852ca8697d9"),
    1: (558, "3197dfc0a09445fdbf59400502ffffe185fb274ec6aa8a3f7c5bafbe083d0291"),
    2: (13304, "3d1a9830253d409a78bb1e9ed230377fb93b7ff902f0693316d150b5d696bdfc"),
    3: (7346, "28513fe426b53594d2e2a8ed877530ead72b77bb8c2cda089fdcfc1f3b184c77"),
    4: (5178, "ae464e6484885562d5d5a140f7c3571fb95e3b99700d9ad7ffce1b4a25f66718"),
    5: (25056, "f7b46796d3f57174fdcca3d983a447e47599b0183502eee8a6f4bb84bf515917"),
    6: (9538, "1f08adf42031406c8c57c3aefaadfacc14c8d658236e03058c01e06f119bf022"),
    7: (22322, "9a12b3e21b962b5660dbaf2bf4eb6487e2d279dcba220f169fff153451ea1b96"),
    8: (18604, "d3ba54d04e7b4f7e5c0468fd2fb1fb5850212fd2d0ab6094562c87e32df0354e"),
    9: (26080, "8c0c8a6b351b75fdda2ee3fd111d2a30783f49e2cd49db62069caf92fc0acd83"),
    10: (25974, "c89c81f052c82787221aae3745fe897a8986688444bc005ffe46e085c6201a13"),
    11: (13048, "2cf5b15841ec848a8ec2dfab047a8b192b7311be674eceb911e97f0cfbd44324"),
    12: (15306, "8ddc8a30684a6a67889eb5f70cb7f699c71a121dc96977f3f2995c890783365a"),
}
EXPECTED_GLOBALS = {
    "DATA": (5630, "e2b59778923fda7521f83b462e71f531e38a4b4d616f179a834f2a874ad3aeeb"),
    "ZERO": (202, "841a056b3ddcfe5358689c930688356ccee11cd573a111cde73b157b79f2ff5a"),
    "DREL": (94, "0044a1aef0ed93a96e998e94e60d68743d3b6abac05a7f760d167496b4ef0d06"),
}
BLOCK = 512


class MacRefError(ValueError):
    pass


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def be16(data: bytes, off: int) -> int:
    return struct.unpack_from(">H", data, off)[0]


def be32(data: bytes, off: int) -> int:
    return struct.unpack_from(">I", data, off)[0]


def iso_record(data: bytes, at: int) -> dict:
    length = data[at]
    if length < 34 or at + length > len(data):
        raise MacRefError(f"invalid ISO directory record at {at}")
    r = data[at:at + length]
    name_len = r[32]
    name_raw = r[33:33 + name_len]
    if name_raw == b"\x00":
        name = "."
    elif name_raw == b"\x01":
        name = ".."
    else:
        name = name_raw.decode("ascii", "replace")
        name = re.sub(r";[0-9]+$", "", name)
        if name.endswith("."):
            name = name[:-1]
    extent_lba = struct.unpack_from("<I", r, 2)[0]
    extent_be = struct.unpack_from(">I", r, 6)[0]
    size = struct.unpack_from("<I", r, 10)[0]
    size_be = struct.unpack_from(">I", r, 14)[0]
    if extent_lba != extent_be or size != size_be:
        raise MacRefError("ISO both-endian directory fields disagree")
    return {"name": name, "extent_lba": extent_lba, "size": size,
            "directory": bool(r[25] & 2), "flags": r[25], "raw_name": name_raw.hex()}


def parse_iso(data: bytes) -> list[dict]:
    pvd = None
    for sec in range(16, min(len(data) // 2048, 64)):
        d = data[sec * 2048:(sec + 1) * 2048]
        if d[1:6] != b"CD001" or d[6] != 1:
            continue
        if d[0] == 1:
            pvd = d
            break
    if pvd is None:
        raise MacRefError("ISO 9660 primary volume descriptor not found")
    root_len = pvd[156]
    root = iso_record(pvd[156:156 + root_len], 0)
    files: list[dict] = []
    seen: set[tuple[int, str]] = set()

    def walk(rec: dict, parent: str):
        key = (rec["extent_lba"], parent)
        if key in seen:
            return
        seen.add(key)
        start = rec["extent_lba"] * 2048
        raw = data[start:start + rec["size"]]
        if len(raw) != rec["size"]:
            raise MacRefError(f"ISO extent outside image: {parent}")
        pos = 0
        while pos < len(raw):
            if raw[pos] == 0:
                pos = ((pos // 2048) + 1) * 2048
                continue
            child = iso_record(raw, pos)
            pos += raw[pos]
            if child["name"] in (".", ".."):
                continue
            path = f"{parent}/{child['name']}" if parent else child["name"]
            if child["directory"]:
                walk(child, path)
            else:
                content = data[child["extent_lba"] * 2048:child["extent_lba"] * 2048 + child["size"]]
                if len(content) != child["size"]:
                    raise MacRefError(f"short ISO file extent: {path}")
                files.append({"path": path, "size": len(content), "sha256": sha256(content),
                              "extent_lba": child["extent_lba"], "flags": child["flags"]})

    walk(root, "")
    return sorted(files, key=lambda x: x["path"].casefold())


def parse_apm(data: bytes) -> list[dict]:
    if len(data) < 1024 or data[:2] != b"ER":
        raise MacRefError("Apple Driver Descriptor Record signature ER not found")
    block_size = be16(data, 2)
    if block_size < 512 or block_size > 4096:
        raise MacRefError(f"implausible APM block size {block_size}")
    first = data[block_size:block_size + block_size]
    if first[:2] != b"PM":
        raise MacRefError("Apple Partition Map signature PM not found at block 1")
    count = be32(first, 4)
    if count > 256:
        raise MacRefError("implausible APM entry count")
    out = []
    for i in range(count):
        p = (i + 1) * block_size
        e = data[p:p + block_size]
        if e[:2] != b"PM":
            raise MacRefError(f"bad APM entry {i + 1}")
        out.append({"map_index": i + 1, "start_block": be32(e, 8), "block_count": be32(e, 12),
                    "name": e[16:48].split(b"\0", 1)[0].decode("mac_roman"),
                    "type": e[48:80].split(b"\0", 1)[0].decode("mac_roman"),
                    "data_start": be32(e, 80), "data_count": be32(e, 84), "block_size": block_size})
    return out


def _extent_records(data: bytes, off: int, count: int = 3) -> list[tuple[int, int]]:
    result = []
    for i in range(count):
        start, blocks = struct.unpack_from(">HH", data, off + i * 4)
        if blocks:
            result.append((start, blocks))
    return result


def hfs_volume_info(image: bytes, part: dict) -> dict:
    base = part["start_block"] * part["block_size"]
    mdb = image[base + 1024:base + 1536]
    if mdb[:2] not in (b"BD", b"H+", b"H-"):
        raise MacRefError(f"classic HFS MDB signature missing: {mdb[:2]!r}")
    if mdb[:2] != b"BD":
        raise MacRefError("this parser currently supports classic HFS (BD), not HFS Plus")
    alloc_block_size = be32(mdb, 20)
    alloc_start_512 = be16(mdb, 28)
    if not alloc_block_size:
        raise MacRefError("HFS allocation block size is zero")
    info = {"base": base, "volume_name": mdb[36 + 1:36 + 1 + mdb[36]].decode("mac_roman"),
            "allocation_block_size": alloc_block_size, "allocation_start_512": alloc_start_512,
            "catalog_file_size": be32(mdb, 146), "catalog_extents": _extent_records(mdb, 150),
            "extents_file_size": be32(mdb, 130), "extents_extents": _extent_records(mdb, 134)}
    info["catalog"] = read_hfs_fork(image, base, alloc_start_512, alloc_block_size,
                                    info["catalog_extents"], info["catalog_file_size"])
    info["extents"] = read_hfs_fork(image, base, alloc_start_512, alloc_block_size,
                                    info["extents_extents"], info["extents_file_size"])
    return info


def read_hfs_fork(image: bytes, base: int, alloc_start_512: int, alloc_size: int,
                  extents: list[tuple[int, int]], logical_size: int) -> bytes:
    chunks = []
    for first, count in extents:
        start = base + alloc_start_512 * BLOCK + first * alloc_size
        end = start + count * alloc_size
        chunks.append(image[start:end])
    content = b"".join(chunks)[:logical_size]
    if len(content) != logical_size:
        raise MacRefError(f"HFS fork truncated: wanted {logical_size}, got {len(content)}")
    return content


def parse_hfs_catalog(catalog: bytes) -> list[dict]:
    if len(catalog) < 128:
        raise MacRefError("short HFS catalog B-tree")
    node_size = be16(catalog, 32)
    if not node_size:
        raise MacRefError("HFS catalog B-tree has zero node size")
    files = []
    # HFS catalog root is CNID 2 and its own parent ID is 1.
    parent_by_id = {1: ""}
    entries = []
    node_count = len(catalog) // node_size
    for node_i in range(node_count):
        at = node_i * node_size
        if at + 14 > len(catalog):
            break
        kind = struct.unpack_from(">b", catalog, at + 8)[0]
        nrec = be16(catalog, at + 10)
        if kind != -1 or nrec == 0:
            continue
        offsets_base = at + node_size - 2 * (nrec + 1)
        if offsets_base < at + 14:
            continue
        # HFS stores the offset table backwards from the end of each node.
        offsets = [be16(catalog, offsets_base + 2 * i) for i in range(nrec + 1)][::-1]
        for j in range(nrec):
            lo, hi = offsets[j], offsets[j + 1]
            if lo < 14 or hi <= lo or hi > node_size:
                continue
            rec = catalog[at + lo:at + hi]
            klen = rec[0]
            if klen < 6 or 1 + klen > len(rec):
                continue
            parent = be32(rec, 2)
            name_len = rec[6]
            if 7 + name_len > 1 + klen:
                continue
            name = rec[7:7 + name_len].decode("mac_roman", "replace")
            data_at = (1 + klen + 1) & ~1
            if data_at + 2 > len(rec):
                continue
            # In classic HFS, catalog record type is one byte followed by a
            # reserved byte (the following fields are big-endian).
            rectype = rec[data_at]
            payload = rec[data_at:]
            entries.append((parent, name, rectype, payload))
    directory_records = [(parent, name, payload) for parent, name, rectype, payload in entries
                          if rectype == 1 and len(payload) >= 8]
    pending = directory_records[:]
    while pending:
        rest = []
        for parent, name, payload in pending:
            cnid = be32(payload, 6)
            if parent in parent_by_id or parent == 2:
                parent_by_id[cnid] = (parent_by_id.get(parent, "") + ":" + name).strip(":")
            else:
                rest.append((parent, name, payload))
        if len(rest) == len(pending):
            break
        pending = rest
    for parent, name, rectype, payload in entries:
        if rectype == 2 and len(payload) >= 102:
            info = payload[4:20]
            data_size = be32(payload, 26)
            rsrc_size = be32(payload, 36)
            # Apple's classic HFS catalog file record has the two 12-byte
            # ExtentDescriptors at offsets 74 and 86 in this byte layout.
            data_ext = _extent_records(payload, 74)
            rsrc_ext = _extent_records(payload, 86)
            files.append({"parent_id": parent, "parent_path": parent_by_id.get(parent, "?"),
                          "name": name, "path": (parent_by_id.get(parent, "") + ":" + name).strip(":"),
                          "finder_type": info[:4].decode("mac_roman", "replace"),
                          "creator": info[4:8].decode("mac_roman", "replace"),
                          "finder_flags": be16(info, 8), "cnid": be32(payload, 20),
                          "data_size": data_size, "resource_size": rsrc_size,
                          "data_extents": data_ext, "resource_extents": rsrc_ext,
                          "record": payload})
    for f in files:
        f["parent_path"] = parent_by_id.get(f["parent_id"], f["parent_path"])
        f["path"] = (f["parent_path"] + ":" + f["name"]).strip(":")
    return files


def parse_resource_fork(data: bytes) -> tuple[list[dict], dict]:
    if len(data) < 16:
        raise MacRefError("short Macintosh resource fork")
    data_off, map_off, data_len, map_len = struct.unpack_from(">IIII", data, 0)
    if data_off + data_len > len(data) or map_off + map_len > len(data):
        raise MacRefError("resource fork header ranges exceed fork")
    m = data[map_off:map_off + map_len]
    if len(m) < 30:
        raise MacRefError("short resource map")
    type_off = be16(m, 24)
    name_off = be16(m, 26)
    if type_off + 2 > len(m):
        raise MacRefError("resource type list outside map")
    type_count = be16(m, type_off) + 1
    resources = []
    tp = type_off + 2
    for _ in range(type_count):
        if tp + 8 > len(m):
            raise MacRefError("truncated resource type record")
        typ = m[tp:tp + 4].decode("mac_roman", "replace")
        nres = be16(m, tp + 4) + 1
        ref_off = be16(m, tp + 6)
        rp = type_off + ref_off
        tp += 8
        for _ in range(nres):
            if rp + 12 > len(m):
                raise MacRefError("truncated resource reference list")
            rid = struct.unpack_from(">h", m, rp)[0]
            name_index = be16(m, rp + 2)
            attrs = m[rp + 4]
            rel = int.from_bytes(m[rp + 5:rp + 8], "big")
            pos = data_off + rel
            if pos + 4 > len(data):
                raise MacRefError("resource data offset outside fork")
            size = be32(data, pos)
            content = data[pos + 4:pos + 4 + size]
            if len(content) != size:
                raise MacRefError("truncated resource data")
            name = None
            if name_index != 0xFFFF:
                np = name_off + name_index
                if np >= len(m):
                    raise MacRefError("resource name offset outside map")
                nlen = m[np]
                name = m[np + 1:np + 1 + nlen].decode("mac_roman", "replace")
            resources.append({"type": typ, "id": rid, "name": name, "attributes": attrs,
                              "size": size, "sha256": sha256(content), "data": content})
            rp += 12
    return resources, {"data_offset": data_off, "map_offset": map_off,
                       "data_length": data_len, "map_length": map_len,
                       "type_count": type_count, "resource_count": len(resources)}


def decode_string_list(content: bytes) -> list[str]:
    if len(content) < 2:
        return []
    count = be16(content, 0)
    pos = 2
    strings = []
    for _ in range(count):
        if pos >= len(content):
            break
        n = content[pos]
        pos += 1
        strings.append(content[pos:pos + n].decode("mac_roman", "replace"))
        pos += n
    return strings


def write_iso_markdown(files: list[dict], image_sha: str, image_size: int, out: Path) -> None:
    lines = ["# ISO 9660 file inventory", "", f"Image: {image_size:,} bytes; SHA-256 `{image_sha}`.", "",
             "| File | Bytes | SHA-256 |", "|---|---:|---|"]
    for row in files:
        path = row["path"].replace("|", "\\|")
        lines.append(f"| `{path}` | {row['size']:,} | `{row['sha256']}` |")
    (out / "iso-files.md").write_text("\n".join(lines) + "\n", encoding="utf-8")


def _clean_symbol(raw: bytes) -> str | None:
    if not raw or len(raw) > 80:
        return None
    # MacsBug procedure names use a restricted identifier alphabet.
    for b in raw:
        if b < 0x20 or b > 0x7e:
            return None
    value = raw.decode("ascii", "replace")
    value = value.rstrip(" ")
    if not re.fullmatch(r"[_A-Za-z][_A-Za-z0-9.% ]*", value):
        return None
    return value


def scan_macsbug_symbols(code: bytes, first_code: int = 4) -> list[dict]:
    """Find MacsBug procedure definitions after RTS/RTD/JMP (A0) tails."""
    found = []
    seen = set()
    for off in range(first_code, len(code) - 3, 2):
        op = be16(code, off)
        if op == 0x4E75:
            end = off + 2
        elif op == 0x4E74:
            end = off + 4
        elif op == 0x4ED0:
            end = off + 2
        else:
            continue
        if end >= len(code):
            continue
        prefix = code[end]
        name = None
        name_end = end
        name_kind = None
        encoded_length = None
        if 0x80 <= prefix <= 0x9F:
            n = prefix & 0x1F
            chars_at = end + 1
            if n == 0:
                if chars_at >= len(code):
                    continue
                n = code[chars_at]
                chars_at += 1
            if not 1 <= n <= 255 or chars_at + n > len(code):
                continue
            name = _clean_symbol(code[chars_at:chars_at + n])
            name_end = chars_at + n
            name_kind = "variable"
            encoded_length = n
        elif 0x20 <= prefix <= 0x7F and end + 8 <= len(code):
            first = prefix & 0x7F
            second = code[end + 1]
            n = 16 if second & 0x80 else 8
            raw = bytes([first]) + code[end + 1:end + n]
            raw = bytes(b & 0x7F for b in raw)
            name = _clean_symbol(raw)
            name_end = end + n
            name_kind = "fixed"
            encoded_length = n
        if not name or (off, name) in seen:
            continue
        # MacsBug aligns the following constant-length word after the name.
        constant_word_at = (name_end + 1) & ~1
        constant_bytes = be16(code, constant_word_at) if constant_word_at + 2 <= len(code) else 0
        next_record = min(len(code), (constant_word_at + 2 + constant_bytes + 1) & ~1)
        found.append({"name": name, "terminal_offset": off, "end_offset": end,
                      "record_offset": end, "prefix": prefix, "encoded_length": encoded_length,
                      "name_format": name_kind, "constant_bytes": constant_bytes,
                      "next_code_offset": next_record,
                      "terminal": {0x4E75: "RTS", 0x4E74: "RTD", 0x4ED0: "JMP (A0)"}[op]})
        seen.add((off, name))
    return found


def function_spans(code_id: int, code: bytes) -> list[dict]:
    symbols = scan_macsbug_symbols(code)
    spans = []
    start = 4
    for sym in symbols:
        end = sym["end_offset"]
        if end < start:
            continue
        spans.append({"name": sym["name"], "code_id": code_id, "start": start, "end": end,
                      "size": end - start, "terminal": sym["terminal"],
                      "symbol_record_offset": sym["record_offset"]})
        start = sym["next_code_offset"]
    return spans


def normalize_symbol(name: str) -> str:
    return name.lstrip("_").casefold()


def _recovery_status(target: dict) -> str:
    if target.get("proof") == "BYTE_MATCHED_RECONSTRUCTION":
        return "admitted"
    return "open"


def load_mac_code(mac_root: Path) -> tuple[dict[int, bytes], dict[int, list[dict]]]:
    resources = {}
    spans = {}
    for path in sorted((mac_root / "code").glob("CODE_*.bin")):
        match = re.fullmatch(r"CODE_(\d+)\.bin", path.name)
        if not match:
            continue
        rid = int(match.group(1))
        data = path.read_bytes()
        resources[rid] = data
        spans[rid] = function_spans(rid, data)
    return resources, spans


def load_mpw_export_spans(mac_root: Path) -> list[dict]:
    path = mac_root / "mpw-export-boundaries.json"
    if not path.exists():
        return []
    record = json.loads(path.read_text(encoding="utf-8"))
    return [{"name": item["code_identity"], "code_id": item["resource_id"],
             "start": item["entry_resource_offset"], "end": item["end_resource_offset"],
             "size": item["byte_span"], "terminal": None,
             "symbol_record_offset": None, "boundary_source": record["boundary_authority"]}
            for item in record.get("functions", [])]


def import_mpw_export_plan(plan_path: Path, mac_root: Path) -> dict:
    plan = json.loads(plan_path.read_text(encoding="utf-8"))
    functions = []
    for item in plan.get("functions", []):
        functions.append({k: item.get(k) for k in ("code_identity", "resource_id", "entry_resource_offset",
            "end_resource_offset", "byte_span", "decoded_instructions", "decoded_bytes", "boundary_caveat")})
    if not functions:
        raise MacRefError("MPW export plan contains no function boundaries")
    dest = mac_root / "mpw-export-boundaries.json"
    dest.parent.mkdir(parents=True, exist_ok=True)
    doc = {"source": str(plan_path), "source_sha256": sha256(plan_path.read_bytes()),
           "resource_sha256": plan.get("resource_sha256"), "export_count": len(functions),
           "boundary_authority": "MPW export table (as recorded by the Mac project lift plan)",
           "functions": functions}
    code_files = {int(p.stem.split("_")[1]): sha256(p.read_bytes())
                  for p in (mac_root / "code").glob("CODE_*.bin")}
    if plan.get("resource_sha256") and (mac_root / "SimAnt.rsrc").exists():
        if sha256((mac_root / "SimAnt.rsrc").read_bytes()) != plan["resource_sha256"]:
            raise MacRefError("MPW export plan belongs to a different resource fork")
    for item in functions:
        rid = item["resource_id"]
        if rid not in code_files or item["end_resource_offset"] > (mac_root / "code" / f"CODE_{rid}.bin").stat().st_size:
            raise MacRefError(f"MPW export boundary outside extracted CODE {rid}")
    dest.write_text(json.dumps(doc, indent=2), encoding="utf-8")
    return {k: v for k, v in doc.items() if k != "functions"}


def correspondence_from_records(sym: dict, recovery: dict, spans_by_id: dict[int, list[dict]],
                                export_doc: dict | None = None) -> dict:
    recovery_targets = recovery.get("targets", {})
    target_names = {normalize_symbol(name): name for name in recovery_targets}
    mac_by_name: dict[str, list[dict]] = {}
    for spans in spans_by_id.values():
        for span in spans:
            norm = normalize_symbol(span["name"])
            # The code stream can contain fixed-length ASCII that resembles a
            # MacsBug name. Only retain labels that independently exist in the
            # Win16 function inventory.
            if norm in target_names:
                mac_by_name.setdefault(norm, []).append(span)
    rows = {}
    counts = {"win16_functions": 0, "admitted": 0, "open": 0, "with_mac_counterpart": 0,
              "admitted_with_mac_counterpart": 0, "open_with_mac_counterpart": 0}
    for segment in sym["segments"]:
        for item in segment["symbols"]:
            name = item["name"]
            # recovery.json is the authoritative Win16 function inventory;
            # ordinary MAPSYM data publics are not counted as functions.
            target = recovery_targets.get(name)
            if target is None:
                continue
            status = _recovery_status(target or {})
            mac_matches = mac_by_name.get(normalize_symbol(name), [])
            rows[name] = {"win16": {"segment": segment["number"], "offset": item["offset"],
                                    "status": status},
                          "mac": mac_matches}
            counts["win16_functions"] += 1
            counts[status] += 1
            if mac_matches:
                counts["with_mac_counterpart"] += 1
                counts[f"{status}_with_mac_counterpart"] += 1
    counts["without_mac_counterpart"] = counts["win16_functions"] - counts["with_mac_counterpart"]
    named_candidates = sum(len(v) for v in mac_by_name.values())
    return {"format": "Mac/Win16 SimAnt correspondence", "win16_mapsym_sha256": sym["sha256"],
            "mac_named_symbols_scanned": sum(map(len, spans_by_id.values())),
            "mac_named_symbols_matching_win16": named_candidates,
            "mac_symbol_scan_candidates": [{"code_id": span["code_id"], "offset": span["start"],
                "name": span["name"]} for spans in spans_by_id.values() for span in spans],
            "mac_mpw_export_boundaries": export_doc.get("export_count") if export_doc else None,
            "mac_export_boundary_source": export_doc.get("source") if export_doc else None,
            "coverage": counts,
            "symbols": dict(sorted(rows.items()))}


def build_correspondence(mac_root: Path, win_sym_path: Path = ROOT / "assets" / "SIMANTW.SYM") -> dict:
    sys.path.insert(0, str(ROOT / "tools"))
    import mapsym  # type: ignore
    sym = mapsym.parse(win_sym_path.read_bytes())
    recovery = json.loads((ROOT / "src" / "recovery.json").read_text(encoding="utf-8"))
    _, spans_by_id = load_mac_code(mac_root)
    export_path = mac_root / "mpw-export-boundaries.json"
    export_doc = json.loads(export_path.read_text(encoding="utf-8")) if export_path.exists() else None
    return correspondence_from_records(sym, recovery, spans_by_id, export_doc)


def _global_mapping(matches: list[dict], mac_features: list[dict], win_features: list[dict],
                    recovery: dict, mac_data_size: int, mac_zero_size: int) -> dict:
    by_mac = {m["identity"]: m for m in mac_features}
    by_win = {w["symbol"]: w for w in win_features}
    votes: dict[int, collections.Counter] = collections.defaultdict(collections.Counter)
    support: dict[tuple[int, str], list[dict]] = collections.defaultdict(list)
    cluster_mac: collections.Counter = collections.Counter()
    cluster_win: collections.Counter = collections.Counter()
    for pair in matches:
        if pair["confidence"] < .70:
            continue
        mid, wid = pair["mac_id"], pair["win16_symbol"]
        m, w = by_mac[mid], by_win[wid]
        mac_patterns = m["global_patterns"]
        win_patterns = w["global_patterns"]
        mac_items = []
        for key, pattern in mac_patterns.items():
            widths = set(pattern.get("widths_bytes", []))
            raw_off = int(key, 16)
            off = raw_off - 0x10000 if raw_off & 0x8000 else raw_off
            mac_items.append((off, widths, pattern.get("reads", 0) + pattern.get("writes", 0)))
            cluster_mac[tuple(sorted(widths))] += 1
        win_items = []
        for name, pattern in win_patterns.items():
            widths = set(pattern.get("widths_bytes", []))
            win_items.append((name, widths, pattern.get("uses", 0)))
            cluster_win[tuple(sorted(widths))] += 1
        options = []
        for off, mw, mc in mac_items:
            for name, ww, wc in win_items:
                if not mw or not ww:
                    continue
                width_score = len(mw & ww) / len(mw | ww)
                count_score = math.exp(-abs(mc - wc) / max(2, mc, wc))
                options.append((.72 * width_score + .28 * count_score, off, name, sorted(mw), sorted(ww)))
        # Greedy one-to-one within this pair prevents a single Mac slot from
        # voting for every Win global in the routine.
        used_offsets = set(); used_names = set()
        for score, off, name, mw, ww in sorted(options, reverse=True):
            if score < .58 or off in used_offsets or name in used_names:
                continue
            used_offsets.add(off); used_names.add(name)
            votes[off][name] += score
            support[(off, name)].append({"win16_symbol": wid, "confidence": pair["confidence"],
                                          "access_pattern_similarity": round(score, 3),
                                          "mac_widths": mw, "win_widths": ww})
    mappings = []
    unresolved = []
    for off, names in sorted(votes.items()):
        name, weight = names.most_common(1)[0]
        total = sum(names.values())
        ratio = weight / total if total else 0
        evidence = support[(off, name)]
        row = {"mac_a5_displacement": (f"-0x{-off:X}" if off < 0 else f"0x{off:X}"), "win16_symbol": name,
               "confidence": round(min(.95, .35 + .12 * len(evidence) + .35 * ratio), 3),
               "supporting_matched_functions": len(evidence), "vote_share": round(ratio, 3),
               "evidence": evidence,
               "mac_region_note": "Signed A5 displacement; the runtime A5 base is not recovered, so this is not an absolute DATA/ZERO offset"}
        target = recovery.get("targets", {}).get(name, {})
        row["win16_data_declaration_evidence"] = {k: target.get(k) for k in
            ("segment", "offset", "size", "source", "proof") if target.get(k) is not None}
        if len(evidence) >= 2 and ratio >= .70:
            mappings.append(row)
        else:
            unresolved.append(row)
    return {"method": "matched-function co-access plus per-function width/use-pattern assignment",
            "mappings": mappings, "tentative": unresolved,
            "mac_access_width_clusters": [{"widths_bytes": list(k), "observations": v}
                                           for k, v in cluster_mac.most_common()],
            "win16_access_width_clusters": [{"widths_bytes": list(k), "observations": v}
                                            for k, v in cluster_win.most_common()],
            "layout_note": "Use as declaration evidence for tools/typedb.py review; no Win16 declaration was changed.",
            "confidence_policy": "Only publish a mapping after at least two independent matched-function votes and >=70% vote share."}


def build_structural_correspondence(mac_root: Path) -> dict:
    """Feature-extract both binaries and construct only supported structural pairs."""
    sys.path.insert(0, str(ROOT / "tools"))
    import common  # type: ignore
    import mapsym  # type: ignore
    import ne  # type: ignore
    image = common.fixture("SIMANTW.EXE")
    ne_doc = ne.parse(image)
    sym = mapsym.parse(common.fixture("SIMANTW.SYM"))
    recovery = json.loads((ROOT / "src" / "recovery.json").read_text(encoding="utf-8"))
    cards = [c for c in common.cards() if c.get("ownership") == "GAME" and c.get("extent", {}).get("size")]
    win_string_resources = _win_string_resources(image, ne_doc)
    win_features = [_win_features(c, image, ne_doc, win_string_resources) for c in cards]
    code_resources, named = load_mac_code(mac_root)
    exports = load_mpw_export_spans(mac_root)
    if not exports:
        raise MacRefError("no imported MPW export boundaries; run --import-export-plan first")
    all_spans = exports + [s for vals in named.values() for s in vals]
    mac_lists, mac_strings = _load_mac_string_resources(mac_root)
    rsrc = json.loads((mac_root / "resource-inventory.json").read_text(encoding="utf-8"))
    mac_res_ids = {int(r["id"]) for r in rsrc.get("resources", []) if r.get("type") in ("STR#", "STR ")}
    mac_features = [_mac_features(s, code_resources, all_spans, mac_lists, mac_strings, mac_res_ids)
                    for s in exports]
    mac_callers: dict[str, set[str]] = collections.defaultdict(set)
    win_callers: dict[str, set[str]] = collections.defaultdict(set)
    for feature in mac_features:
        for callee in feature["callees"]:
            mac_callers[callee].add(feature["identity"])
    for feature in win_features:
        for callee in feature["callees"]:
            win_callers[callee].add(feature["symbol"])
    for feature in mac_features:
        feature["callers"] = mac_callers.get(feature["identity"], set())
    for feature in win_features:
        feature["callers"] = win_callers.get(feature["symbol"], set())
    pairs, validation, review_candidates = _match_structural(mac_features, win_features)
    win_to_pair = {p["win16_symbol"]: p for p in pairs}
    pair_by_mac = {p["mac_id"]: p for p in pairs}
    recovery_targets = recovery.get("targets", {})
    rows = {}
    counts = collections.Counter()
    cards_by_name = {c["symbol"]: c for c in cards}
    for segment in sym["segments"]:
        for item in segment["symbols"]:
            name = item["name"]
            card = cards_by_name.get(name)
            if card is None:
                continue
            status = "admitted" if card.get("proof") == "BYTE_MATCHED_RECONSTRUCTION" else "open"
            pair = win_to_pair.get(name)
            rows[name] = {"win16": {"segment": segment["number"], "offset": item["offset"],
                                    "size": card.get("extent", {}).get("size"), "status": status,
                                    "ownership": card.get("ownership")},
                          "mac": ([{"code_id": int(pair["mac_id"].split(":")[0]),
                                    "offset": int(pair["mac_id"].split(":")[1]),
                                    "size": next(m["size"] for m in mac_features if m["identity"] == pair["mac_id"]),
                                    "confidence": pair["confidence"], "confidence_band": pair["confidence_band"],
                                    "method": pair["method"], "score": pair["score"],
                                    "evidence": pair["evidence"]}] if pair else [])}
            counts[status] += 1
            if pair:
                counts[status + "_with_mac_counterpart"] += 1
                counts["with_mac_counterpart"] += 1
            else:
                counts["without_mac_counterpart"] += 1
    counts["win16_game_code_functions"] = len(rows)
    counts["admitted"] = sum(1 for n in rows if rows[n]["win16"]["status"] == "admitted")
    counts["open"] = sum(1 for n in rows if rows[n]["win16"]["status"] == "open")
    confidence_counts = collections.Counter(p["confidence_band"] for p in pairs)
    global_map = _global_mapping(pairs, mac_features, win_features, recovery,
                                 len((mac_root / "globals" / "DATA_0.bin").read_bytes()) if (mac_root / "globals" / "DATA_0.bin").exists() else 0,
                                 len((mac_root / "globals" / "ZERO_0.bin").read_bytes()) if (mac_root / "globals" / "ZERO_0.bin").exists() else 0)
    mac_pair_inverse = {p["mac_id"]: p for p in pairs}
    win_pair_inverse = {p["win16_symbol"]: p for p in pairs}
    mac_function_features = []
    for m in mac_features:
        pair = mac_pair_inverse.get(m["identity"])
        mac_function_features.append({"mac_id": m["identity"], "code_id": m["code_id"],
            "offset": m["offset"], "size": m["size"],
            "matched_win16_symbol": pair and pair["win16_symbol"], "pair_confidence": pair and pair["confidence"],
            "strings": {"pc_relative": sorted(m["pc_strings"]), "resource_text": sorted(m["resource_strings"])},
            "numeric_constants": sorted(m["constants"]), "resource_ids": sorted(m["resource_ids"]),
            "toolbox_traps": [f"0x{x:04X}" for x in m["toolbox_traps"]],
            "os_call_families": sorted(m["os_families"]),
            "call_graph": {"callers": sorted(m.get("callers", set())), "callees": sorted(m["callees"])},
            "control_flow": {"backward_branches": m["loops"], "switch_dispatches": m["switch_dispatches"],
                             "switch_case_counts": sorted(m["switch_case_counts"]),
                             "switch_case_distribution": sorted(m["switch_case_list"])},
            "a5_globals": m["global_patterns"], "source_shape": {
                k: m["shape"].get(k) for k in ("link_frame_bytes", "parameter_slot_count_observed",
                    "register_allocated_local_candidate_count", "struct_field_offsets_by_base_register",
                    "struct_field_offset_count")}})
    win_function_features = []
    for w in win_features:
        pair = win_pair_inverse.get(w["symbol"])
        imports = [{"module": c.get("module"), "ordinal": c.get("ordinal"), "names": c.get("names", [])}
                   for c in w["card"].get("calls", []) if c.get("kind") == "import"]
        win_function_features.append({"symbol": w["symbol"], "segment": w["segment"],
            "offset": w["offset"], "size": w["size"],
            "status": rows.get(w["symbol"], {}).get("win16", {}).get("status"),
            "source": w["card"].get("source"), "matched_mac_id": pair and pair["mac_id"],
            "pair_confidence": pair and pair["confidence"],
            "strings": {"admitted_source_literals": sorted(w["source_strings"]),
                        "resource_text_candidates": sorted(w["resource_strings"])},
            "numeric_constants": sorted(w["constants"]), "resource_ids": sorted(w["resource_ids"]),
            "imports": imports, "os_call_families": sorted(w["os_families"]),
            "call_graph": {"callers": sorted(w.get("callers", set())), "callees": sorted(w["callees"])},
            "control_flow": {"backward_branches": w["loops"], "switch_dispatches": w["switch_dispatches"],
                             "switch_case_counts": sorted(w["switch_case_counts"]),
                             "switch_case_distribution": sorted(w["switch_case_list"])},
            "globals": w["global_patterns"]})
    data_targets = [{"symbol": name, **{k: target.get(k) for k in
                    ("segment", "offset", "size", "source", "proof") if target.get(k) is not None}}
                    for name, target in recovery_targets.items()
                    if target.get("proof") == "BYTE_MATCHED_DATA_RECONSTRUCTION"]
    return {"format": "Mac/Win16 SimAnt structural correspondence v1",
            "win16_mapsym_sha256": sym["sha256"],
            "mac_resource_sha256": rsrc.get("fork_sha256"),
            "method": {"features": ["function strings (inline MacRoman, STR#/STR resources, recovered C bodies, NE RT_STRING references)",
                                       "immediate numeric constants", "resource IDs", "OS trap/import families",
                                       "callers/callees and iterative call-graph propagation", "loop/switch shape and case counts",
                                       "global access widths, counts, and co-access clusters"],
                       "matching": "rare shared anchors, reciprocal top score with margin, one-to-one assignment, then call-graph propagation",
                       "scope_note": "Win16 rows include only GAME code cards. The recovery ledger also has DATA targets; they are not functions."},
            "coverage": {**dict(counts), "mac_mpw_exports": len(exports), "matched_pairs": len(pairs),
                         "confidence": dict(confidence_counts),
                         "unmatched_mac_exports": len(exports) - len(pairs)},
            "heldout_validation": validation,
            "review_candidates": review_candidates,
            "global_mappings": global_map,
            "win16_data_symbols": data_targets,
            "function_features": {"mac": mac_function_features, "win16": win_function_features},
            "pairs": pairs,
            "symbols": dict(sorted(rows.items())),
            "unmatched_mac_exports": [{"mac_id": m["identity"], "code_id": m["code_id"],
                                       "offset": m["offset"], "size": m["size"],
                                       "boundary_caveat": m["boundary_caveat"]}
                                      for m in mac_features if m["identity"] not in pair_by_mac]}


def _capstone():
    if Cs is None:
        raise MacRefError("capstone is required (capstone 5.0.7 supports M68K)")
    md = Cs(CS_ARCH_M68K, CS_MODE_M68K_000 | CS_MODE_BIG_ENDIAN)
    md.detail = True
    md.skipdata = True
    return md


def _operand_regs(insn) -> tuple[set[str], list[dict]]:
    regs = set()
    memrefs = []
    try:
        operands = insn.operands
    except Exception:
        return regs, memrefs
    suffix = insn.mnemonic.lower().rsplit(".", 1)[-1] if "." in insn.mnemonic else ""
    operand_width = {"b": 1, "w": 2, "l": 4}.get(suffix)
    for operand_index, operand in enumerate(operands):
        typ = getattr(operand, "type", None)
        reg = getattr(operand, "reg", None)
        if reg:
            try:
                regs.add(insn.reg_name(reg).upper())
            except Exception:
                pass
        mem = getattr(operand, "mem", None)
        if mem and getattr(mem, "base_reg", 0):
            base = insn.reg_name(mem.base_reg).upper()
            disp = getattr(mem, "disp", 0)
            index = insn.reg_name(mem.index_reg).upper() if getattr(mem, "index_reg", 0) else None
            memrefs.append({"base": base, "displacement": disp, "index": index,
                            "size": operand_width, "operand_index": operand_index})
            regs.add(base)
            if index:
                regs.add(index)
    return regs, memrefs


def _mac_string_at(code: bytes, offset: int) -> str | None:
    """Read a cautious inline MacRoman C or Pascal string at a code offset."""
    if not 0 <= offset < len(code):
        return None
    candidates = []
    end = code.find(b"\0", offset, min(len(code), offset + 241))
    if end >= 0:
        candidates.append(code[offset:end])
    n = code[offset]
    if 3 <= n <= 120 and offset + 1 + n <= len(code):
        candidates.append(code[offset + 1:offset + 1 + n])
    for raw in candidates:
        if len(raw) < 4:
            continue
        if sum(0x20 <= b <= 0x7E for b in raw) < len(raw) * .9:
            continue
        value = raw.decode("mac_roman", "replace").strip()
        if len(value) >= 4 and any(ch.isalpha() for ch in value):
            return _normalize_text(value)
    return None


def _normalize_text(value: str) -> str:
    value = value.casefold().replace("\u00a0", " ")
    return re.sub(r"\s+", " ", value).strip(" \t\r\n\"'.,:;!?()[]{}")


def _load_mac_string_resources(mac_root: Path) -> tuple[dict[int, list[str]], dict[int, list[str]]]:
    lists: dict[int, list[str]] = {}
    strings: dict[int, list[str]] = {}
    for path in (mac_root / "strings").glob("STR#_*.bin"):
        match = re.fullmatch(r"STR#_(\d+)\.bin", path.name)
        if match:
            lists[int(match.group(1))] = [_normalize_text(s) for s in decode_string_list(path.read_bytes())]
    for path in (mac_root / "strings").glob("STR _*.bin"):
        match = re.fullmatch(r"STR _(\d+)\.bin", path.name)
        if not match:
            continue
        data = path.read_bytes()
        n = data[0] if data else 0
        if 0 < n <= len(data) - 1:
            text = _normalize_text(data[1:1 + n].decode("mac_roman", "replace"))
            if text:
                strings[int(match.group(1))] = [text]
    return lists, strings


def _source_body(source: str, symbol: str) -> str:
    """Find one function body in a recovered C translation unit, if present."""
    path = Path(source)
    if not path.is_absolute():
        path = ROOT / path
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return ""
    bare = symbol.lstrip("_")
    match = re.search(r"(?<![A-Za-z0-9_])" + re.escape(bare) + r"\s*\(", text)
    if not match:
        return ""
    # Balance the parameter list while respecting literals and comments.
    start = text.find("(", match.start())
    depth, pos, quote, escape, line_comment, block_comment = 0, start, None, False, False, False
    while pos < len(text):
        ch = text[pos]
        nxt = text[pos + 1] if pos + 1 < len(text) else ""
        if line_comment:
            if ch == "\n": line_comment = False
        elif block_comment:
            if ch == "*" and nxt == "/": block_comment = False; pos += 1
        elif quote:
            if escape: escape = False
            elif ch == "\\": escape = True
            elif ch == quote: quote = None
        elif ch == "/" and nxt == "/": line_comment = True; pos += 1
        elif ch == "/" and nxt == "*": block_comment = True; pos += 1
        elif ch in "\"'": quote = ch
        elif ch == "(": depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                break
        pos += 1
    if depth:
        return ""
    # K&R declarations may intervene; reject a call expression ending in ';'.
    brace = text.find("{", pos + 1, min(len(text), pos + 1800))
    if brace < 0:
        return ""
    between = text[pos + 1:brace]
    if ";" in between and "\n" not in between:
        return ""
    depth, pos, quote, escape, line_comment, block_comment = 0, brace, None, False, False, False
    while pos < len(text):
        ch = text[pos]
        nxt = text[pos + 1] if pos + 1 < len(text) else ""
        if line_comment:
            if ch == "\n": line_comment = False
        elif block_comment:
            if ch == "*" and nxt == "/": block_comment = False; pos += 1
        elif quote:
            if escape: escape = False
            elif ch == "\\": escape = True
            elif ch == quote: quote = None
        elif ch == "/" and nxt == "/": line_comment = True; pos += 1
        elif ch == "/" and nxt == "*": block_comment = True; pos += 1
        elif ch in "\"'": quote = ch
        elif ch == "{": depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return text[brace:pos + 1]
        pos += 1
    return ""


def _c_strings(body: str) -> set[str]:
    found = set()
    for raw in re.findall(r'"(?:\\.|[^"\\])*"', body):
        try:
            value = ast.literal_eval(raw)
        except (SyntaxError, ValueError):
            continue
        if isinstance(value, str):
            value = _normalize_text(value)
            if len(value) >= 4 and any(ch.isalpha() for ch in value):
                found.add(value)
    return found


def _win_string_resources(image: bytes, ne_doc: dict) -> dict[int, str]:
    """Decode NE RT_STRING blocks into their public string ordinals."""
    result = {}
    for item in ne_doc.get("resources", []):
        if item.get("type", {}).get("id") != 6 or item.get("identity", {}).get("id") is None:
            continue
        start, end = item.get("offset", -1), item.get("offset", -1) + item.get("size", 0)
        if start < 0 or end > len(image):
            continue
        raw = image[start:end]
        block_id = item["identity"]["id"]
        pos = 0
        for index in range(16):
            if pos >= len(raw): break
            n = raw[pos]; pos += 1
            value = raw[pos:pos + n].decode("cp1252", "replace"); pos += n
            value = _normalize_text(value)
            if value:
                result[(block_id - 1) * 16 + index] = value
    return result


def _mac_os_family(trap: int) -> str:
    high = trap & 0xFF00
    return {0xA000: "OS_OR_MEMORY", 0xA100: "MEMORY_OR_OS", 0xA800: "DRAWING",
            0xA900: "WINDOW_MENU_RESOURCE"}.get(high, "TOOLBOX")


def _win_os_families(card: dict) -> set[str]:
    groups = set()
    for call in card.get("calls", []):
        if call.get("kind") != "import":
            continue
        module = str(call.get("module", "")).upper()
        if module == "GDI": groups.add("DRAWING")
        elif module == "USER": groups.add("WINDOW_MENU_RESOURCE")
        elif module in ("KERNEL", "KRNL386"): groups.add("OS_OR_MEMORY")
        elif "MMSYSTEM" in module or "SOUND" in module: groups.add("SOUND")
        else: groups.add("TOOLBOX")
    return groups


def _mac_features(span: dict, codes: dict[int, bytes], all_spans: list[dict],
                  string_lists: dict[int, list[str]], string_resources: dict[int, list[str]],
                  mac_resource_ids: set[int]) -> dict:
    analysed = analyse_function(span, codes, all_spans)
    shape = analysed["source_shape"]
    constants = {int(v, 16) for v in shape["constants_hex"]}
    constants |= {v & 0xFFFF for v in constants if v < 0 or v > 0xFFFF}
    resource_ids = constants & mac_resource_ids
    pc_text = set(shape.get("pc_relative_strings", []))
    resource_text = set()
    for rid in resource_ids:
        resource_text.update(string_lists.get(rid, []))
        resource_text.update(string_resources.get(rid, []))
    text = pc_text | resource_text
    traps = set()
    # Count A-line trap words only at decoded instruction boundaries so data
    # tables inside the export span do not masquerade as OS calls.
    md = _capstone()
    raw = codes[span["code_id"]]
    for insn in md.disasm(raw[span["start"]:span["end"]], span["start"]):
        if len(insn.bytes) >= 2:
            word = be16(insn.bytes, 0)
            if word & 0xF000 == 0xA000:
                traps.add(word)
    callees = {c.get("name") for c in analysed.get("callees", [])
               if c.get("name") and c.get("kind") != "A5 call slot"}
    return {"identity": f"{span['code_id']}:{span['start']}", "code_id": span["code_id"],
            "offset": span["start"], "size": span["size"], "strings": text,
            "pc_strings": pc_text, "resource_strings": resource_text,
            "constants": constants, "resource_ids": resource_ids,
            "loops": shape.get("loop_count", 0),
            "switch_dispatches": shape.get("switch_dispatch_candidate_count", 0),
            "switch_case_counts": set(shape.get("switch_case_counts", [])),
            "switch_case_list": list(shape.get("switch_case_counts", [])),
            "parameters": shape.get("parameter_slot_count_observed", 0),
            "globals": {int(x, 16) - (0x10000 if int(x, 16) & 0x8000 else 0)
                        for x in shape.get("a5_global_offsets_hex", [])},
            "global_patterns": shape.get("a5_access_patterns", {}),
            "callees": callees, "os_families": {_mac_os_family(t) for t in traps},
            "toolbox_traps": sorted(traps), "shape": shape,
            "boundary_caveat": span.get("boundary_caveat") or
                "MPW export boundary may include local routines or embedded data"}


def _win_features(card: dict, image: bytes, ne_doc: dict,
                  resource_strings: dict[int, str]) -> dict:
    seg = ne_doc["segments"][card["segment"] - 1]
    start, end = card["offset"], card["extent"].get("end")
    if end is None:
        end = start + (card["extent"].get("size") or 0)
    blob = image[seg["file_offset"] + start:seg["file_offset"] + end]
    constants = set()
    if Cs is not None:
        try:
            from capstone import CS_ARCH_X86, CS_MODE_16, CS_GRP_CALL, CS_GRP_JUMP, CS_OP_IMM
            decoder = Cs(CS_ARCH_X86, CS_MODE_16)
            decoder.detail = True
            for insn in decoder.disasm(blob, start):
                if insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP):
                    continue
                for op in insn.operands:
                    if op.type == CS_OP_IMM:
                        value = op.imm
                        if -0x10000 <= value <= 0xFFFF:
                            constants.add(value & 0xFFFF)
                        else:
                            constants.add(value & 0xFFFFFFFF)
        except Exception:
            pass
    strings = set()
    source_strings = set()
    source = card.get("source")
    if source:
        source_strings.update(_c_strings(_source_body(source, card["symbol"])))
    used_resources = constants & set(resource_strings)
    resource_text = {resource_strings[rid] for rid in used_resources}
    strings.update(source_strings | resource_text)
    globals_by_name = collections.Counter()
    global_widths: dict[str, set[int]] = collections.defaultdict(set)
    for row in card.get("disassembly", []):
        refs = row.get("references", [])
        operand = row.get("operands", "")
        width = 1 if "byte ptr" in operand else 2 if "word ptr" in operand else 4 if "dword ptr" in operand else 0
        for ref in refs:
            if ref.get("kind") == "global_ds_assumed":
                for name in ref.get("names", []):
                    globals_by_name[name] += 1
                    if width:
                        global_widths[name].add(width)
    calls = set()
    for call in card.get("calls", []):
        if call.get("kind") == "internal":
            calls.update(call.get("names", []))
    switches = [int(t.get("count", 0)) for t in card.get("extent", {}).get("jump_tables", [])]
    # Count backedges from the original decoded rows; jump-table payload is not
    # present in the instruction list, so this remains conservative.
    loops = 0
    for row in card.get("disassembly", []):
        if row.get("mnemonic", "").lower().startswith("j"):
            m = re.fullmatch(r"(?:0x)?([0-9a-fA-F]+)", row.get("operands", "").strip())
            if m and int(m.group(1), 16) < row.get("offset", 0):
                loops += 1
    resource_ids = {rid for rid in used_resources}
    return {"symbol": card["symbol"], "segment": card["segment"], "offset": start,
            "size": card.get("extent", {}).get("size") or end - start,
            "strings": strings, "constants": constants, "resource_ids": resource_ids,
            "source_strings": source_strings, "resource_strings": resource_text,
            "loops": loops, "switch_dispatches": len(switches), "switch_case_counts": set(switches),
            "switch_case_list": switches,
            "parameters": sum(1 for row in card.get("disassembly", [])
                               if "[bp +" in row.get("operands", "") and
                               (m := re.search(r"\[bp \+ (0x[0-9a-f]+|[0-9]+)\]", row["operands"])) and
                               int(m.group(1), 0) >= 4),
            "globals": set(globals_by_name),
            "global_patterns": {name: {"uses": count, "widths_bytes": sorted(global_widths[name])}
                                for name, count in globals_by_name.items()},
            "callees": calls, "os_families": _win_os_families(card),
            "card": card}


def _weighted_jaccard(left: set, right: set, document_frequency: collections.Counter,
                      population: int) -> float:
    if not left or not right:
        return 0.0
    intersection = left & right
    if not intersection:
        return 0.0
    weight = lambda x: 1.0 + math.log((population + 1) / (document_frequency[x] + 1))
    numerator = sum(weight(x) for x in intersection)
    denominator = sum(weight(x) for x in left | right)
    return numerator / denominator if denominator else 0.0


def _feature_frequency(features: list[dict], key: str) -> collections.Counter:
    return collections.Counter(item for f in features for item in f.get(key, set()))


def _feature_similarity(mac: dict, win: dict, freqs: dict, nm: int, nw: int,
                        graph_support: float = 0.0,
                        holdout: str | None = None) -> tuple[float, dict]:
    families = {"strings": (mac["strings"], win["strings"], 0.28),
                "constants": (mac["constants"], win["constants"], 0.22),
                "resource_ids": (mac["resource_ids"], win["resource_ids"], 0.10),
                "switch_case_counts": (mac["switch_case_counts"], win["switch_case_counts"], 0.20),
                "callees": (mac["callees"], win["callees"], 0.0),
                "os_families": (mac["os_families"], win["os_families"], 0.05)}
    components = {}
    available_weight = 0.0
    total = 0.0
    for key, (left, right, weight) in families.items():
        if key == holdout or key == "callees":
            continue
        if left and right:
            score = _weighted_jaccard(left, right, freqs[key], max(nm, nw))
            components[key] = score
            available_weight += weight
            total += score * weight
    shape_parts = []
    if mac["size"] and win["size"]:
        shape_parts.append(math.exp(-abs(math.log(max(mac["size"], 1) / max(win["size"], 1))) * .7))
    shape_parts.append(math.exp(-abs(mac["loops"] - win["loops"])))
    shape_parts.append(math.exp(-abs(mac["switch_dispatches"] - win["switch_dispatches"])))
    shape_parts.append(math.exp(-abs(mac["parameters"] - win["parameters"]) / 2.0))
    mcases, wcases = collections.Counter(mac.get("switch_case_list", [])), collections.Counter(win.get("switch_case_list", []))
    case_overlap = sum((mcases & wcases).values())
    case_union = sum((mcases | wcases).values())
    case_similarity = case_overlap / case_union if case_union else 0.0
    components["switch_case_multiset"] = case_similarity
    if mcases or wcases:
        shape_parts.append(case_similarity)
    shape = sum(shape_parts) / len(shape_parts)
    components["shape"] = shape
    available_weight += .15
    total += shape * .15
    components["call_graph"] = graph_support
    if graph_support:
        available_weight += .15
        total += graph_support * .15
    score = total / available_weight if available_weight else 0.0
    common = {key: sorted(mac[key] & win[key], key=str)
              for key in ("strings", "constants", "resource_ids", "switch_case_counts")}
    rare = {}
    for key, values in common.items():
        freq = freqs[key]
        rare[key] = [v for v in values if freq[v] <= 4]
    size_ratio = max(mac["size"], win["size"]) / max(1, min(mac["size"], win["size"]))
    return score, {"components": components, "common": common, "rare_common": rare,
                   "shape_similarity": shape, "switch_case_multiset_similarity": case_similarity,
                   "size_ratio": round(size_ratio, 3), "graph_support": graph_support}


def _match_structural(mac_features: list[dict], win_features: list[dict]) -> tuple[list[dict], dict]:
    """Conservative one-to-one anchor matches, then caller/callee propagation."""
    nm, nw = len(mac_features), len(win_features)
    freqs = {key: _feature_frequency(mac_features, key) + _feature_frequency(win_features, key)
             for key in ("strings", "constants", "resource_ids", "switch_case_counts", "os_families")}
    m_by_id = {m["identity"]: m for m in mac_features}
    w_by_id = {w["symbol"]: w for w in win_features}
    m_rankings: dict[str, list[tuple[str, float, dict]]] = collections.defaultdict(list)
    w_rankings: dict[str, list[tuple[str, float, dict]]] = collections.defaultdict(list)
    candidates = []
    for m in mac_features:
        for w in win_features:
            score, evidence = _feature_similarity(m, w, freqs, nm, nw)
            if not any(evidence["rare_common"].values()):
                continue
            # Exact shared, corpus-rare literals are strongest. Rare constants
            # are useful corroboration, but a constant alone never admits a pair.
            string_anchor = len(evidence["rare_common"]["strings"])
            resource_anchor = len(evidence["rare_common"]["resource_ids"])
            rare_constants = len(evidence["rare_common"]["constants"])
            switch_anchor = len(evidence["rare_common"]["switch_case_counts"])
            anchor = max(min(.95, .76 + .08 * (string_anchor - 1)) if string_anchor else 0,
                         min(.78, .63 + .06 * (resource_anchor - 1)) if resource_anchor else 0,
                         min(.70, .55 + .04 * (rare_constants - 1)) if rare_constants else 0,
                         min(.76, .65 + .04 * (switch_anchor - 1)) if switch_anchor else 0)
            evidence["anchor_strength"] = anchor
            confidence = min(.98, .30 + .40 * score + .30 * anchor)
            evidence["confidence"] = confidence
            candidates.append((m["identity"], w["symbol"], score, confidence, evidence))
    # Require the candidate to be each side's top anchor and retain a useful
    # margin. This avoids assigning common branch constants arbitrarily.
    for mid, wid, score, confidence, evidence in candidates:
        m_rankings[mid].append((wid, score, evidence))
        w_rankings[wid].append((mid, score, evidence))
    matches: dict[str, dict] = {}
    rejected: list[dict] = []
    used_mac = set(); used_win = set()
    m_best = {mid: sorted(rows, key=lambda x: -x[1]) for mid, rows in m_rankings.items()}
    w_best = {wid: sorted(rows, key=lambda x: -x[1]) for wid, rows in w_rankings.items()}
    for mid, ranked in sorted(m_best.items(), key=lambda x: -x[1][0][1]):
        wid, score, evidence = ranked[0]
        win_ranked = w_best[wid]
        if win_ranked[0][0] != mid or mid in used_mac or wid in used_win:
            continue
        m_margin = score - ranked[1][1] if len(ranked) > 1 else score
        w_margin = score - win_ranked[1][1] if len(win_ranked) > 1 else score
        if min(m_margin, w_margin) < .035:
            rejected.append({"mac_id": mid, "win16_symbol": wid, "candidate_score": round(score, 3),
                             "confidence_before_rejection": evidence.get("confidence"),
                             "reason": "AMBIGUOUS_RECIPROCAL_MARGIN",
                             "mutual_top_margin": round(min(m_margin, w_margin), 3),
                             "evidence": evidence})
            continue
        anchor = evidence.get("anchor_strength", 0)
        if anchor < .63:
            continue
        anchor_families = sum(bool(evidence["rare_common"][key]) for key in
                              ("strings", "resource_ids", "constants", "switch_case_counts"))
        reasons = []
        if evidence["rare_common"]["switch_case_counts"] and evidence["switch_case_multiset_similarity"] < .75:
            reasons.append("SWITCH_CASE_DISTRIBUTION_MISMATCH")
        if evidence["size_ratio"] >= 3.0 and anchor_families < 2:
            reasons.append("MPW_SPAN_AT_LEAST_3X_WIN_SIZE_WITH_ONLY_ONE_ANCHOR_FAMILY")
        if reasons:
            rejected.append({"mac_id": mid, "win16_symbol": wid, "candidate_score": round(score, 3),
                             "confidence_before_rejection": evidence.get("confidence"), "reason": reasons,
                             "evidence": evidence,
                             "interpretation": "The MPW boundary may include local routines/data; retain as a review candidate, not a correspondence."})
            continue
        confidence = min(.98, evidence["confidence"] + .08)
        matches[wid] = {"mac_id": mid, "confidence": round(confidence, 3),
                        "score": round(score, 3), "confidence_band": "high" if confidence >= .85 else "medium",
                        "method": "unique shared string/resource/switch-case anchor" if evidence["rare_common"]["strings"] or evidence["rare_common"]["resource_ids"] or evidence["rare_common"]["switch_case_counts"] else "rare constant anchor",
                        "mutual_top_margin": round(min(m_margin, w_margin), 3),
                        "evidence": evidence}
        used_mac.add(mid); used_win.add(wid)
    # Call-graph propagation may create a pair without its own string/constant
    # anchor, but only from two independent edges through stable anchor seeds.
    mac_callers: dict[str, set[str]] = collections.defaultdict(set)
    win_callers: dict[str, set[str]] = collections.defaultdict(set)
    for m in mac_features:
        for c in m["callees"]: mac_callers[c].add(m["identity"])
    for w in win_features:
        for c in w["callees"]: win_callers[c].add(w["symbol"])
    changed = True
    while changed:
        changed = False
        win_to_mac = {w: row["mac_id"] for w, row in matches.items()
                      if row.get("confidence", 0) >= .76}
        mac_to_win = {m: w for w, m in win_to_mac.items()}
        proposals = []
        for mid, m in m_by_id.items():
            if mid in used_mac:
                continue
            incoming_m = mac_callers.get(mid, set())
            mapped_incoming = {mac_to_win[c] for c in incoming_m if c in mac_to_win}
            mapped_outgoing = {mac_to_win[c] for c in m["callees"] if c in mac_to_win}
            if not mapped_incoming and not mapped_outgoing:
                continue
            for wid, w in w_by_id.items():
                if wid in used_win:
                    continue
                out_hits = len(mapped_outgoing & w["callees"])
                incoming_w = win_callers.get(wid, set())
                in_hits = len(mapped_incoming & incoming_w)
                if out_hits + in_hits < 2 or not (out_hits >= 2 or in_hits >= 2 or (out_hits and in_hits)):
                    continue
                support = min(1.0, (out_hits + in_hits) / 3.0)
                score2, evidence = _feature_similarity(m, w, freqs, nm, nw, support)
                shape = evidence["shape_similarity"]
                if shape < .35:
                    continue
                conf = min(.90, .50 + .14 * support + .14 * shape + .035 * min(out_hits + in_hits, 4))
                evidence.update({"confidence": round(conf, 3), "anchor_strength": 0,
                                 "graph_outgoing_edges": out_hits, "graph_incoming_edges": in_hits,
                                 "graph_seed_pairs": sorted(set(mapped_incoming & incoming_w) |
                                                             set(mapped_outgoing & w["callees"]))})
                proposals.append((conf, mid, wid, score2, evidence, out_hits, in_hits))
        mprops: dict[str, list[tuple]] = collections.defaultdict(list)
        wprops: dict[str, list[tuple]] = collections.defaultdict(list)
        for prop in proposals:
            conf, mid, wid = prop[0], prop[1], prop[2]
            mprops[mid].append(prop); wprops[wid].append(prop)
        accepted = []
        for mid, rows0 in mprops.items():
            rows0.sort(key=lambda x: -x[0])
            best = rows0[0]
            wr = sorted(wprops[best[2]], key=lambda x: -x[0])
            if wr[0][1] != mid:
                continue
            mm = best[0] - rows0[1][0] if len(rows0) > 1 else best[0]
            wm = best[0] - wr[1][0] if len(wr) > 1 else best[0]
            if min(mm, wm) >= .035:
                best[4]["mutual_top_margin"] = round(min(mm, wm), 3)
                accepted.append(best)
        for conf, mid, wid, score, evidence, out_hits, in_hits in sorted(accepted, reverse=True):
            if mid in used_mac or wid in used_win:
                continue
            matches[wid] = {"mac_id": mid, "confidence": round(conf, 3), "score": round(score, 3),
                            "confidence_band": "high" if conf >= .85 else "medium",
                            "method": "call-graph propagation from anchor matches", "evidence": evidence}
            used_mac.add(mid); used_win.add(wid); changed = True
    rows = []
    for wid, match in sorted(matches.items()):
        rows.append({"win16_symbol": wid, **match})
    validation = _heldout_anchor_validation(mac_features, win_features, freqs, candidates, matches)
    return rows, validation, sorted(rejected, key=lambda x: -x.get("candidate_score", 0))[:100]


def _heldout_anchor_validation(mac_features: list[dict], win_features: list[dict],
                               freqs: dict, candidates: list[tuple], matches: dict) -> dict:
    """Leave one shared anchor out and check whether other evidence retains rank."""
    by_pair: dict[tuple[str, str], list[tuple[str, object]]] = collections.defaultdict(list)
    accepted = {(row["mac_id"], wid) for wid, row in matches.items()}
    for mid, wid, score, confidence, ev in candidates:
        if (mid, wid) not in accepted:
            continue
        for value in ev["rare_common"]["strings"]:
            by_pair[(mid, wid)].append(("strings", value))
        for value in ev["rare_common"]["constants"]:
            by_pair[(mid, wid)].append(("constants", value))
        for value in ev["rare_common"]["switch_case_counts"]:
            by_pair[(mid, wid)].append(("switch_case_counts", value))
    m = {x["identity"]: x for x in mac_features}
    holdout_rows = []
    for (mid, wid), anchors in by_pair.items():
        # One held-out value is sufficient for a singleton anchor; for functions
        # with several anchors, each is tested independently.
        for family, value in anchors:
            query = dict(m[mid])
            query[family] = set(query[family]) - {value}
            ranked = []
            for candidate in win_features:
                target = dict(candidate)
                target[family] = set(target[family]) - {value}
                score, _ = _feature_similarity(query, target, freqs, len(mac_features), len(win_features),
                                               holdout=None)
                ranked.append((score, candidate["symbol"]))
            ranked.sort(reverse=True)
            rank = next((i + 1 for i, (_, name) in enumerate(ranked) if name == wid), None)
            holdout_rows.append({"mac_id": mid, "win16_symbol": wid,
                                 "heldout_family": family, "heldout_value": value,
                                 "rank_without_value": rank})
    if not holdout_rows:
        return {"method": "leave one shared rare string, numeric constant, or switch-case anchor out; rerank using remaining features",
                "heldout_anchor_pairs": 0, "top1_recovered": 0, "top3_recovered": 0,
                "status": "NO_REDUNDANT_ANCHORS_AVAILABLE_FOR_HOLDOUT"}
    top1 = sum(x["rank_without_value"] == 1 for x in holdout_rows)
    top3 = sum(x["rank_without_value"] is not None and x["rank_without_value"] <= 3 for x in holdout_rows)
    return {"method": "leave one shared rare string, numeric constant, or switch-case anchor out; rerank using remaining features",
            "heldout_anchor_pairs": len({(x["mac_id"], x["win16_symbol"]) for x in holdout_rows}),
            "heldout_anchor_trials": len(holdout_rows), "top1_recovered": top1, "top3_recovered": top3,
            "top1_rate": round(top1 / len(holdout_rows), 3),
            "top3_rate": round(top3 / len(holdout_rows), 3),
            "status": "DESCRIPTIVE_CROSS_VALIDATION_NOT_GROUND_TRUTH", "trials": holdout_rows}


def analyse_function(span: dict, code_resources: dict[int, bytes], all_spans: list[dict],
                     win_row: dict | None = None) -> dict:
    md = _capstone()
    raw = code_resources[span["code_id"]][span["start"]:span["end"]]
    instructions = list(md.disasm(raw, span["start"]))
    function_at = {(s["code_id"], s["start"]): s["name"] for s in all_spans}
    frame = None
    regs: set[str] = set()
    loops = []
    constants = set()
    memrefs: list[dict] = []
    called = []
    a5_call_sites: set[int] = set()
    lines = []
    for insn in instructions:
        mnem = insn.mnemonic.upper()
        base_mnem = mnem.split(".", 1)[0]
        lines.append(f"{insn.address:04X}: {insn.mnemonic:<8} {insn.op_str}".rstrip())
        rset, mset = _operand_regs(insn)
        regs.update(rset)
        memrefs.extend({**x, "instruction": insn.address} for x in mset)
        if mnem.startswith("LINK") and "A6" in insn.op_str.upper():
            nums = re.findall(r"#(?:\$|0X)?(-?[0-9A-F]+)", insn.op_str.upper())
            if nums:
                token = nums[-1]
                try:
                    signed = int(token, 16)
                    if signed & 0x8000:
                        signed -= 0x10000
                    frame = abs(signed)
                except ValueError:
                    pass
        if mnem.startswith("B") and insn.op_str:
            match = re.search(r"(?:\$|0X)?([0-9A-F]+)$", insn.op_str.upper())
            if match:
                try:
                    dest = int(match.group(1), 16)
                    if span["start"] <= dest <= insn.address:
                        loops.append({"from": insn.address, "to": dest, "mnemonic": insn.mnemonic})
                except ValueError:
                    pass
        if "#" in insn.op_str:
            for token in re.findall(r"#(?:\$|0X)?(-?[0-9A-F]+)", insn.op_str.upper()):
                try:
                    constants.add(int(token, 16))
                except ValueError:
                    pass
        if base_mnem in ("JSR", "JMP", "BSR") and insn.op_str:
            a5_ref = next((x for x in mset if x["base"] == "A5"), None)
            if a5_ref and base_mnem in ("JSR", "JMP", "BSR"):
                a5_call_sites.add(insn.address)
                called.append({"address": insn.address, "mnemonic": insn.mnemonic,
                               "operand": insn.op_str, "kind": "A5 call slot",
                               "slot_offset_hex": f"0x{a5_ref['displacement'] & 0xffff:04X}",
                               "name": None})
                continue
            target = None
            # PC-relative operands are printed as $disp(pc), and take priority
            # over the generic hexadecimal-address match below.
            dm = re.search(r"\$([0-9A-F]+)\(PC\)", insn.op_str.upper())
            if dm:
                # Capstone renders the resolved PC effective address here,
                # rather than the encoded displacement.
                target = int(dm.group(1), 16)
            else:
                om = re.search(r"(?:\$|0X)([0-9A-F]+)", insn.op_str.upper())
                if om:
                    target = int(om.group(1), 16)
            name = function_at.get((span["code_id"], target)) if target is not None else None
            called.append({"address": insn.address, "mnemonic": insn.mnemonic,
                           "operand": insn.op_str, "target": target,
                           "name": name or ("toolbox trap" if insn.op_str.upper().startswith("#$A") else None)})
    # positive A6 displacements are caller-passed values; operand size gives the access width.
    params = {}
    for ref in memrefs:
        if ref["base"] == "A6" and ref["displacement"] >= 8:
            params.setdefault(ref["displacement"], set()).add(ref.get("size"))
    parameter_report = [{"stack_offset": off, "access_widths_bytes": sorted(x for x in widths if isinstance(x, int)),
                         "width_note": "inferred from instruction operand size; repeated/partial accesses can be ambiguous"}
                        for off, widths in sorted(params.items())]
    a5 = sorted({ref["displacement"] for ref in memrefs
                 if ref["base"] == "A5" and ref["instruction"] not in a5_call_sites})
    a5_accesses = {}
    pc_strings = set()
    for insn in instructions:
        for token in re.findall(r"\$([0-9A-F]+)\(PC\)", insn.op_str.upper()):
            content = _mac_string_at(code_resources[span["code_id"]], int(token, 16))
            if content:
                pc_strings.add(content)
        _, refs = _operand_regs(insn)
        for ref in refs:
            if ref["base"] == "A5" and insn.address not in a5_call_sites:
                slot = a5_accesses.setdefault(ref["displacement"], {"widths": set(), "modes": set(),
                                                                        "reads": 0, "writes": 0})
                if isinstance(ref.get("size"), int):
                    slot["widths"].add(ref["size"])
                slot["modes"].add("indexed" if ref.get("index") else "direct")
                mnemonic = insn.mnemonic.lower().split(".", 1)[0]
                is_destination = bool(insn.operands) and ref.get("operand_index") == len(insn.operands) - 1
                write_only = {"move", "movea", "clr", "st"}
                if is_destination and mnemonic in write_only:
                    slot["writes"] += 1
                if not is_destination or mnemonic not in write_only:
                    slot["reads"] += 1
        # LEA/PEA/operand loads that use d16(PC) often point at inline constants.
        try:
            for operand in insn.operands:
                mem = getattr(operand, "mem", None)
                if mem and getattr(mem, "base_reg", 0) and insn.reg_name(mem.base_reg).upper() == "PC":
                    target = insn.address + 2 + getattr(mem, "disp", 0)
                    content = _mac_string_at(code_resources[span["code_id"]], target)
                    if content:
                        pc_strings.add(content)
        except Exception:
            pass
    fields = {}
    for ref in memrefs:
        if ref["base"] in ("A0", "A1", "A2", "A3", "A4"):
            fields.setdefault(ref["base"], set()).add(ref["displacement"])
    nonvolatile = sorted(r for r in regs if r in {f"D{i}" for i in range(2, 8)} | {f"A{i}" for i in range(2, 5)})
    switchish = []
    for ix, insn in enumerate(instructions):
        if insn.mnemonic.upper().split(".", 1)[0] != "JMP":
            continue
        if re.search(r"\(A[0-7],\s*D[0-7](?:\.W)?\)", insn.op_str.upper()):
            switchish.append(insn)
        else:
            indirect = re.fullmatch(r"\(A([0-7])\)", insn.op_str.strip().upper())
            if indirect and any(re.search(r"\(A" + indirect.group(1) + r",\s*D[0-7](?:\.W)?\)", p.op_str.upper())
                                for p in instructions[max(0, ix - 6):ix]):
                switchish.append(insn)
    switch_case_counts = _mac_switch_case_counts(span, code_resources)
    return {"name": span["name"], "code_id": span["code_id"], "offset": span["start"], "size": span["size"],
            "disassembly": lines, "callees": called, "source_shape": {
                "parameters": parameter_report,
                "parameter_slot_count_observed": len(parameter_report),
                "link_frame_bytes": frame,
                "register_allocated_local_candidates": nonvolatile,
                "register_allocated_local_candidate_count": len(nonvolatile),
                "loops_by_backward_branch": loops,
                "loop_count": len(loops),
                "switch_dispatch_candidates": [x.address for x in switchish],
                "switch_dispatch_candidate_count": max(len(switchish), len(switch_case_counts)),
                "switch_case_counts": switch_case_counts,
                "constants_hex": [f"0x{x:X}" for x in sorted(constants)],
            "a5_global_offsets_hex": [f"0x{x & 0xffff:04X}" for x in a5],
            "a5_global_name_candidates": {f"0x{x & 0xffff:04X}": [] for x in a5},
            "a5_access_patterns": {f"0x{off & 0xffff:04X}": {
                "widths_bytes": sorted(item["widths"]), "modes": sorted(item["modes"]),
                "reads": item["reads"], "writes": item["writes"]}
                for off, item in sorted(a5_accesses.items())},
            "pc_relative_strings": sorted(pc_strings),
                "struct_field_offsets_by_base_register": {r: sorted(v) for r, v in fields.items()},
                "struct_field_offset_count": sum(len(v) for v in fields.values()),
                "notes": ["frame size is a lower bound on stack locals; register candidates are not proven C locals",
                          "A5 offsets have no name unless a direct data-layout correspondence is proven",
                          "loop and switch counts are instruction-pattern estimates"]},
            "win16": win_row}


def _mac_switch_case_counts(span: dict, code_resources: dict[int, bytes]) -> list[int]:
    """Infer bounded 68k computed-switch counts from a guard and indexed JMP."""
    md = _capstone()
    code = code_resources[span["code_id"]]
    insns = list(md.disasm(code[span["start"]:span["end"]], span["start"]))
    counts = []
    for ix, insn in enumerate(insns):
        if insn.mnemonic.lower().split(".", 1)[0] != "jmp":
            continue
        index_reg = re.search(r"\(a[0-7],\s*(d[0-7])", insn.op_str.lower())
        if not index_reg:
            indirect = re.fullmatch(r"\(a([0-7])\)", insn.op_str.strip().lower())
            if indirect:
                for prior in reversed(insns[max(0, ix - 6):ix]):
                    index_reg = re.search(r"\(a" + indirect.group(1) + r",\s*(d[0-7])", prior.op_str.lower())
                    if index_reg:
                        break
        if not index_reg:
            continue
        reg = index_reg.group(1)
        lo = max(0, ix - 18)
        bound = None
        for prior in reversed(insns[lo:ix]):
            if reg not in prior.op_str.lower():
                continue
            cmp = re.search(r"#\$([0-9a-f]+),\s*" + reg, prior.op_str.lower())
            if cmp:
                bound = int(cmp.group(1), 16)
                break
        if bound is not None and 0 <= bound < 256:
            counts.append(bound + 1)
    return counts


def export_shape_catalog(mac_root: Path) -> dict:
    codes, _ = load_mac_code(mac_root)
    spans = load_mpw_export_spans(mac_root)
    rows = []
    for span in spans:
        result = analyse_function(span, codes, spans)
        result.pop("disassembly", None)
        rows.append(result)
    return {"source": "build/mac/mpw-export-boundaries.json",
            "boundary_count": len(spans),
            "method_note": "instruction-pattern estimates; no source declarations or Mac C names are present",
            "exports": rows}


def extract_disc(iso_path: Path, out: Path) -> dict:
    image = iso_path.read_bytes()
    out.mkdir(parents=True, exist_ok=True)
    files = parse_iso(image)
    (out / "iso-files.json").write_text(json.dumps({"iso_sha256": sha256(image), "iso_size": len(image),
                                                      "expected_iso_sha256": EXPECTED_ISO_SHA256,
                                                      "matches_expected_iso": sha256(image) == EXPECTED_ISO_SHA256,
                                                      "files": files}, indent=2), encoding="utf-8")
    write_iso_markdown(files, sha256(image), len(image), out)
    iso_execs = []
    oracle = (ROOT / "assets" / "SIMANTW.EXE").read_bytes()
    oracle_sym = (ROOT / "assets" / "SIMANTW.SYM").read_bytes()
    for f in files:
        if f["path"].upper().endswith((".EXE", ".SYM", ".MAP", ".DBG", ".PDB")):
            content = image[f["extent_lba"] * 2048:f["extent_lba"] * 2048 + f["size"]]
            iso_execs.append({"path": f["path"], "size": len(content), "sha256": f["sha256"],
                              "oracle_exe_exact": sha256(content) == ORACLE_EXE_SHA256,
                              "oracle_exe_same_bytes": content == oracle})
    (out / "windows-comparison.json").write_text(json.dumps({"oracle_path": "assets/SIMANTW.EXE",
        "oracle_sha256_expected": ORACLE_EXE_SHA256, "oracle_sha256_actual": sha256(oracle),
        "oracle_sym_path": "assets/SIMANTW.SYM", "oracle_sym_sha256": sha256(oracle_sym),
        "oracle_sym_sha256_expected": "9d27f4d0872e483ddbf460bda8a2e34b7180f153c6d7c1a74d692720476c9a7f",
        "iso_candidates": iso_execs,
        "iso_sym_comparisons": [{"path": f["path"], "sha256": f["sha256"],
            "same_as_oracle_sym": f["sha256"] == sha256(oracle_sym)}
            for f in files if f["path"].upper().endswith(".SYM")],
        "related_files": [f for f in files if re.search(r"\.(SYM|MAP|DBG|PDB)(;[0-9]+)?$", f["path"], re.I)]}, indent=2), encoding="utf-8")
    parts = parse_apm(image)
    (out / "apple-partition-map.json").write_text(json.dumps({"driver_descriptor_block_size": be16(image, 2),
                                                                "partitions": parts}, indent=2), encoding="utf-8")
    hfs_parts = [p for p in parts if p["type"] == "Apple_HFS"]
    if not hfs_parts:
        raise MacRefError("no Apple_HFS partition found")
    hinfo = hfs_volume_info(image, hfs_parts[0])
    hfs_start = hfs_parts[0]["start_block"] * hfs_parts[0]["block_size"]
    hfs_length = hfs_parts[0]["block_count"] * hfs_parts[0]["block_size"]
    hfs_sha = sha256(image[hfs_start:hfs_start + hfs_length])
    hfiles = parse_hfs_catalog(hinfo["catalog"])
    for f in hfiles:
        f.pop("record", None)
    (out / "hfs-files.json").write_text(json.dumps({"partition": hfs_parts[0], "volume_name": hinfo["volume_name"],
                                                        "allocation_block_size": hinfo["allocation_block_size"],
                                                        "catalog_file_size": hinfo["catalog_file_size"],
                                                        "files": hfiles}, indent=2, ensure_ascii=False), encoding="utf-8")
    apps = [f for f in hfiles if f["name"].startswith("SimAnt") and f["creator"] == "SANT" and f["finder_type"] == "APPL"]
    if not apps:
        apps = [f for f in hfiles if f["creator"] == "SANT" and f["finder_type"] == "APPL"]
    if len(apps) != 1:
        raise MacRefError(f"expected one SANT/APPL game, found {len(apps)}")
    app = apps[0]
    base = hfs_parts[0]["start_block"] * hfs_parts[0]["block_size"]
    data = read_hfs_fork(image, base, hinfo["allocation_start_512"], hinfo["allocation_block_size"],
                         app["data_extents"], app["data_size"])
    rsrc = read_hfs_fork(image, base, hinfo["allocation_start_512"], hinfo["allocation_block_size"],
                         app["resource_extents"], app["resource_size"])
    (out / "SimAnt.data").write_bytes(data)
    (out / "SimAnt.rsrc").write_bytes(rsrc)
    resources, rinfo = parse_resource_fork(rsrc)
    manifest = []
    for res in resources:
        row = {k: v for k, v in res.items() if k != "data"}
        manifest.append(row)
        typ, rid = res["type"], res["id"]
        if typ == "CODE" and 0 <= rid <= 12:
            dest = out / "code" / f"CODE_{rid}.bin"
        elif typ in ("DATA", "ZERO", "DREL"):
            dest = out / "globals" / f"{typ}_{rid}.bin"
        elif typ in ("STR#", "STR "):
            dest = out / "strings" / f"{typ.replace('#', 'HASH')}_{rid}.bin"
        else:
            continue
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(res["data"])
        if typ == "STR#":
            row["strings"] = decode_string_list(res["data"])
        elif typ == "STR ":
            row["string"] = res["data"][1:1 + res["data"][0]].decode("mac_roman", "replace") if res["data"] else ""
    (out / "resource-inventory.json").write_text(json.dumps({"fork_sha256": sha256(rsrc), **rinfo,
                                                               "resources": manifest}, indent=2, ensure_ascii=False), encoding="utf-8")
    expected_code_checks = {}
    for res in resources:
        if res["type"] == "CODE" and res["id"] in EXPECTED_CODE:
            expected_size, expected_hash = EXPECTED_CODE[res["id"]]
            expected_code_checks[str(res["id"])] = {"size_expected": expected_size,
                "sha256_expected": expected_hash, "size_actual": res["size"],
                "sha256_actual": res["sha256"],
                "matches": (res["size"], res["sha256"]) == (expected_size, expected_hash)}
    globals_checks = {}
    for res in resources:
        if res["type"] in EXPECTED_GLOBALS:
            expected_size, expected_hash = EXPECTED_GLOBALS[res["type"]]
            globals_checks[res["type"]] = {"size_expected": expected_size, "size_actual": res["size"],
                "sha256_expected": expected_hash, "sha256_actual": res["sha256"],
                "matches": (res["size"], res["sha256"]) == (expected_size, expected_hash)}
    app_facts = {k: app[k] for k in ("path", "cnid", "finder_type", "creator", "finder_flags",
                                      "data_size", "resource_size")}
    checks = {"iso_sha256": {"expected": EXPECTED_ISO_SHA256, "actual": sha256(image),
                              "matches": sha256(image) == EXPECTED_ISO_SHA256},
              "apple_hfs_partition_sha256": {"expected": EXPECTED_HFS_SHA256, "actual": hfs_sha,
                                               "size": hfs_length, "matches": hfs_sha == EXPECTED_HFS_SHA256},
              "application": {**app_facts, "resource_sha256": sha256(rsrc),
                  "resource_sha256_expected": EXPECTED_RSRC_SHA256,
                  "matches": app["cnid"] == 23 and app["finder_type"] == "APPL" and
                      app["creator"] == "SANT" and app["finder_flags"] == 0x2100 and
                      app["data_size"] == 0 and app["resource_size"] == 1188458 and
                      sha256(rsrc) == EXPECTED_RSRC_SHA256},
              "code_resources": expected_code_checks,
              "global_resources": globals_checks}
    (out / "asset-verification.json").write_text(json.dumps(checks, indent=2, ensure_ascii=False), encoding="utf-8")
    correspondence = build_correspondence(out)
    (out / "correspondence.json").write_text(json.dumps(correspondence, indent=2), encoding="utf-8")
    return {"iso_files": len(files), "hfs_files": len(hfiles), "resources": len(resources),
            "mac_named_symbols_matching_win16": correspondence["mac_named_symbols_matching_win16"],
            "mpw_export_boundaries": correspondence["mac_mpw_export_boundaries"],
            "coverage": correspondence["coverage"]}


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("symbol", nargs="?", help="Win16 MAPSYM C symbol (underscore optional)")
    parser.add_argument("--mac-root", type=Path, default=ROOT / "build" / "mac")
    parser.add_argument("--extract-disc", type=Path, help="read-only ISO path; extract into --mac-root")
    parser.add_argument("--rebuild-correspondence", action="store_true")
    parser.add_argument("--import-export-plan", type=Path, help="copy MPW export boundaries from a lift-plan JSON")
    parser.add_argument("--mac-code", help="analyze an unnamed export by CODE_ID:OFFSET")
    parser.add_argument("--export-shapes", action="store_true", help="write a shape summary for all imported MPW exports")
    args = parser.parse_args(argv)
    try:
        if args.extract_disc:
            print(json.dumps(extract_disc(args.extract_disc, args.mac_root), indent=2))
            return 0
        if args.rebuild_correspondence:
            result = build_structural_correspondence(args.mac_root)
            (args.mac_root / "correspondence.json").write_text(json.dumps(result, indent=2), encoding="utf-8")
            print(json.dumps(result["coverage"], indent=2))
            return 0
        if args.import_export_plan:
            print(json.dumps(import_mpw_export_plan(args.import_export_plan, args.mac_root), indent=2))
            return 0
        if args.export_shapes:
            result = export_shape_catalog(args.mac_root)
            dest = args.mac_root / "export-shapes.json"
            dest.write_text(json.dumps(result, indent=2), encoding="utf-8")
            print(json.dumps({"path": str(dest), "boundary_count": result["boundary_count"]}, indent=2))
            return 0
        if args.mac_code:
            match = re.fullmatch(r"(\d+):(?:0x)?([0-9a-fA-F]+)", args.mac_code)
            if not match:
                raise MacRefError("--mac-code must be CODE_ID:OFFSET, e.g. 5:0x1234")
            rid, off = int(match.group(1)), int(match.group(2), 16)
            codes, named_by_id = load_mac_code(args.mac_root)
            exports = load_mpw_export_spans(args.mac_root)
            span = next((s for s in exports if s["code_id"] == rid and s["start"] == off), None)
            if span is None:
                raise MacRefError(f"no MPW export begins at CODE {rid} offset 0x{off:X}")
            all_spans = exports + [s for vals in named_by_id.values() for s in vals]
            print(json.dumps(analyse_function(span, codes, all_spans), indent=2))
            return 0
        if not args.symbol:
            parser.error("SYMBOL is required unless --extract-disc or --rebuild-correspondence is used")
        corr = json.loads((args.mac_root / "correspondence.json").read_text(encoding="utf-8"))
        name = args.symbol if args.symbol.startswith("_") else "_" + args.symbol
        row = corr["symbols"].get(name)
        if not row or not row["mac"]:
            print(json.dumps({"symbol": name, "win16": row, "mac": None,
                "mac_mpw_export_boundaries": corr.get("mac_mpw_export_boundaries"),
                "mac_symbol_scan_candidates": corr.get("mac_symbol_scan_candidates", []),
                "message": "no structural Mac counterpart passed the recorded confidence and uniqueness gates"}, indent=2))
            return 2
        codes, spans = load_mac_code(args.mac_root)
        exports = load_mpw_export_spans(args.mac_root)
        all_spans = exports + [s for entries in spans.values() for s in entries]
        global_map = {}
        for g in corr.get("global_mappings", {}).get("mappings", []):
            disp = g["mac_a5_displacement"]
            signed = (-1 if disp.startswith("-") else 1) * int(disp.lstrip("-"), 16)
            global_map[f"0x{signed & 0xffff:04X}"] = g["win16_symbol"]
        inverse_pairs = {p["mac_id"]: p["win16_symbol"] for p in corr.get("pairs", [])}
        results = []
        for matched in row["mac"]:
            span = next((s for s in exports if s["code_id"] == matched["code_id"] and
                         s["start"] == matched["offset"]), None)
            if span is None:
                continue
            result = analyse_function(span, codes, all_spans, row["win16"])
            for offset, candidates in result["source_shape"].get("a5_global_name_candidates", {}).items():
                if offset in global_map:
                    candidates.append({"symbol": global_map[offset], "evidence": "structural correspondence global map"})
            for callee in result.get("callees", []):
                if callee.get("name"):
                    callee["win16_name"] = inverse_pairs.get(f"{span['code_id']}:{callee.get('target')}")
            result["correspondence"] = {k: matched.get(k) for k in
                ("confidence", "confidence_band", "method", "score", "evidence")}
            result["source_shape_summary"] = {
                "frame_bytes": result["source_shape"].get("link_frame_bytes"),
                "parameter_slots_observed": result["source_shape"].get("parameter_slot_count_observed"),
                "register_local_candidates": result["source_shape"].get("register_allocated_local_candidate_count"),
                "backward_branches": result["source_shape"].get("loop_count"),
                "switch_dispatches": result["source_shape"].get("switch_dispatch_candidate_count"),
                "constants": result["source_shape"].get("constants_hex"),
                "mapped_globals": result["source_shape"].get("a5_global_name_candidates"),
                "callees": [c.get("win16_name") or c.get("name") for c in result.get("callees", [])]}
            results.append(result)
        print(json.dumps({"symbol": name, "coverage": corr["coverage"], "counterparts": results}, indent=2))
        return 0
    except (MacRefError, OSError, KeyError, ValueError) as e:
        print(f"mac_ref: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
