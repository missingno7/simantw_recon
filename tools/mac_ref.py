"""Read-only extraction and cross-reference tools for the supplied SimAnt Mac CD.

The extraction command understands ISO 9660, Apple Partition Map, classic HFS,
and Macintosh resource forks. The normal SYMBOL command disassembles a matched
Mac routine and reports cautious source-shape observations.
"""
from __future__ import annotations

import argparse
import hashlib
import json
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
    for operand in operands:
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
                            "size": getattr(operand, "size", None)})
            regs.add(base)
            if index:
                regs.add(index)
    return regs, memrefs


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
    lines = []
    for insn in instructions:
        mnem = insn.mnemonic.upper()
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
        if mnem in ("JSR", "JMP", "BSR") and insn.op_str:
            target = None
            # PC-relative operands are printed as $disp(pc), and take priority
            # over the generic hexadecimal-address match below.
            dm = re.search(r"\$([0-9A-F]+)\(PC\)", insn.op_str.upper())
            if dm:
                disp = int(dm.group(1), 16)
                if disp & 0x8000:
                    disp -= 0x10000
                target = insn.address + 2 + disp
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
    a5 = sorted({ref["displacement"] for ref in memrefs if ref["base"] == "A5"})
    fields = {}
    for ref in memrefs:
        if ref["base"] in ("A0", "A1", "A2", "A3", "A4"):
            fields.setdefault(ref["base"], set()).add(ref["displacement"])
    nonvolatile = sorted(r for r in regs if r in {f"D{i}" for i in range(2, 8)} | {f"A{i}" for i in range(2, 6)})
    switchish = [x for x in instructions if x.mnemonic.upper() == "JMP" and ",PC" in x.op_str.upper() and "D" in x.op_str.upper()]
    return {"name": span["name"], "code_id": span["code_id"], "offset": span["start"], "size": span["size"],
            "disassembly": lines, "callees": called, "source_shape": {
                "parameters": parameter_report,
                "link_frame_bytes": frame,
                "register_allocated_local_candidates": nonvolatile,
                "register_allocated_local_candidate_count": len(nonvolatile),
                "loops_by_backward_branch": loops,
                "loop_count": len(loops),
                "switch_dispatch_candidates": [x.address for x in switchish],
                "switch_dispatch_candidate_count": len(switchish),
                "constants_hex": [f"0x{x:X}" for x in sorted(constants)],
                "a5_global_offsets_hex": [f"0x{x & 0xffff:04X}" for x in a5],
                "struct_field_offsets_by_base_register": {r: sorted(v) for r, v in fields.items()},
                "struct_field_offset_count": sum(len(v) for v in fields.values()),
                "notes": ["frame size is a lower bound on stack locals; register candidates are not proven C locals",
                          "A5 offsets have no name unless a direct data-layout correspondence is proven",
                          "loop and switch counts are instruction-pattern estimates"]},
            "win16": win_row}


def extract_disc(iso_path: Path, out: Path) -> dict:
    image = iso_path.read_bytes()
    out.mkdir(parents=True, exist_ok=True)
    files = parse_iso(image)
    (out / "iso-files.json").write_text(json.dumps({"iso_sha256": sha256(image), "iso_size": len(image),
                                                      "expected_iso_sha256": EXPECTED_ISO_SHA256,
                                                      "matches_expected_iso": sha256(image) == EXPECTED_ISO_SHA256,
                                                      "files": files}, indent=2), encoding="utf-8")
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
    globals_checks = {res["type"]: {"size": res["size"], "sha256": res["sha256"]}
                      for res in resources if res["type"] in ("DATA", "ZERO", "DREL")}
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
    args = parser.parse_args(argv)
    try:
        if args.extract_disc:
            print(json.dumps(extract_disc(args.extract_disc, args.mac_root), indent=2))
            return 0
        if args.rebuild_correspondence:
            result = build_correspondence(args.mac_root)
            (args.mac_root / "correspondence.json").write_text(json.dumps(result, indent=2), encoding="utf-8")
            print(json.dumps(result["coverage"], indent=2))
            return 0
        if args.import_export_plan:
            print(json.dumps(import_mpw_export_plan(args.import_export_plan, args.mac_root), indent=2))
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
            print(json.dumps({"symbol": name, "win16": row, "mac": None, "message": "no Mac counterpart found"}, indent=2))
            return 2
        codes, spans = load_mac_code(args.mac_root)
        all_spans = [s for entries in spans.values() for s in entries]
        results = [analyse_function(s, codes, all_spans, row["win16"]) for s in row["mac"]]
        print(json.dumps({"symbol": name, "coverage": corr["coverage"], "counterparts": results}, indent=2))
        return 0
    except (MacRefError, OSError, KeyError, ValueError) as e:
        print(f"mac_ref: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
