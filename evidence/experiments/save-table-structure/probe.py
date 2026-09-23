"""Compile source-shaped SaveGame table declarations and summarize OMF."""

import hashlib
import json
from pathlib import Path
import shutil
import struct
import sys

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import compiler
import mapsym
import ne
import omf

HERE = Path(__file__).resolve().parent
PROVENANCE = ROOT / "evidence/experiments/savegame-table/provenance.json"
FLAGS = ["/AL", "/G2", "/Gs", "/Oeglw", "/NTANTEDIT_MODULE"]
EXE = ROOT / "assets/SIMANTW.EXE"
SYM = ROOT / "assets/SIMANTW.SYM"


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def make_source(name_object, with_sentinel, const_table):
    records, _ = derive_table()
    owners = sorted({row["exact_mapsym_name"][1:] for row in records})
    lines = [
        "/* generated from named MAPSYM owners in savegame-table/provenance.json */",
        "struct SaveRecord { unsigned int element_bytes; unsigned int count; void far *data; };",
    ]
    lines += [f"extern unsigned char far {owner}[];" for owner in owners]
    lines.append(f"static char __based(__segname(\"SIMANT_DATA_GROUP\")) lastFileName[80] = {name_object};")
    qualifier = "const " if const_table else ""
    lines.append(
        f"static {qualifier}struct SaveRecord __based(__segname(\"SIMANT_DATA_GROUP\")) saveRecords[] = {{"
    )
    lines += [
        f"    {{{row['kind_word']}, {row['byte_count']}, {row['exact_mapsym_name'][1:]}}},"
        for row in records
    ]
    if with_sentinel:
        lines.append("    {0, 0, 0}")
    lines.append("};")
    return "\n".join(lines) + "\n"


def derive_table():
    """Extend root's first 50 rows to the count-zero terminator by NE semantics."""
    provenance = json.loads(PROVENANCE.read_text(encoding="utf-8"))
    prefix = provenance["table"]["records"]
    exe = EXE.read_bytes()
    parsed_ne = ne.parse(exe)
    parsed_sym = mapsym.parse(SYM.read_bytes())
    segment = parsed_ne["segments"][7]
    base = segment["file_offset"]
    relocations = {
        site: relocation
        for relocation in segment["relocations"]
        for site in relocation["sites"]
    }
    symbol_names = {
        (group["number"], symbol["offset"]): symbol["name"]
        for group in parsed_sym["segments"]
        for symbol in group["symbols"]
    }
    rows = []
    terminator = None
    for index in range(512):
        offset = 0x9570 + index * 8
        kind, count, target_offset = struct.unpack_from("<3H", exe, base + offset)
        if count == 0:
            terminator = {
                "index": index,
                "offset": offset,
                "kind": kind,
                "count": count,
                "selector_relocation_present": offset + 6 in relocations,
            }
            break
        relocation = relocations.get(offset + 6)
        if relocation is None:
            raise ValueError(f"missing selector relocation for record {index}")
        if relocation["source_type"] != 2 or relocation["width"] != 2:
            raise ValueError(f"unexpected relocation form at record {index}")
        target = relocation["target"]
        if target["kind"] != "internal" or target["offset"] != 0:
            raise ValueError(f"non-segment relocation at record {index}")
        name = symbol_names.get((target["segment"], target_offset))
        if name is None:
            raise ValueError(f"unnamed pointer target at record {index}")
        row = {
            "index": index,
            "record_offset": offset,
            "kind_word": kind,
            "byte_count": count,
            "pointer_segment": target["segment"],
            "exact_mapsym_name": name,
        }
        if index < len(prefix):
            earlier = prefix[index]
            for field in ("record_offset", "kind_word", "byte_count", "pointer_segment", "exact_mapsym_name"):
                if row[field] != earlier[field]:
                    raise ValueError(f"root provenance prefix disagrees at row {index}: {field}")
        rows.append(row)
    else:
        raise ValueError("no count-zero table terminator found within 512 rows")
    return rows, terminator


def summarize(name, source):
    source_path = HERE / f"{name}.c"
    source_path.write_text(source, encoding="ascii", newline="\n")
    obj_path, receipt = compiler.compile_source(
        source_path.relative_to(ROOT).as_posix(), FLAGS, "msc700"
    )
    saved_obj = HERE / f"{name}.obj"
    shutil.copyfile(obj_path, saved_obj)
    parsed = omf.parse(saved_obj.read_bytes())
    segments = [
        {
            "name": seg["name"],
            "class": seg["class"],
            "length": seg["length"],
            "initialized_bytes_sha256": hashlib.sha256(bytes.fromhex(seg["data_hex"])).hexdigest(),
        }
        for seg in parsed["segments"]
    ]
    fixups = [
        {
            "segment": parsed["segments"][fixup["segment"] - 1]["name"],
            "offset": fixup["offset"],
            "width": fixup["width"],
            "target": fixup["target"],
        }
        for fixup in parsed["fixups"]
    ]
    return {
        "source": source_path.relative_to(ROOT).as_posix(),
        "sentinel_in_source": "no_sentinel" not in name,
        "source_sha256": digest(source_path),
        "object": saved_obj.relative_to(ROOT).as_posix(),
        "object_sha256": digest(saved_obj),
        "compiler": receipt["compiler"],
        "flags": receipt["flags"],
        "toolchain_lock_sha256": receipt["toolchain_lock_sha256"],
        "segments": segments,
        "fixup_count": len(fixups),
        "fixups": fixups,
        "externals": parsed["externals"],
        "compile_stdout": receipt["stdout"],
    }


def main():
    records, terminator = derive_table()
    runs = []
    for row in records:
        if not runs or runs[-1]["target_segment"] != row["pointer_segment"]:
            runs.append(
                {
                    "first_index": row["index"],
                    "last_index": row["index"],
                    "start_offset": row["record_offset"],
                    "end_exclusive": row["record_offset"] + 8,
                    "target_segment": row["pointer_segment"],
                    "count": 1,
                }
            )
        else:
            runs[-1]["last_index"] = row["index"]
            runs[-1]["end_exclusive"] = row["record_offset"] + 8
            runs[-1]["count"] += 1
    variants = [
        ("mutable_sentinel_braced", "{0}", True, False),
        ("mutable_no_sentinel_braced", "{0}", False, False),
        ("const_sentinel_braced", "{0}", True, True),
        ("mutable_sentinel_string", '""', True, False),
    ]
    results = {
        "scope": "Research only: compiler and OMF shape probes; no production job, member, proof, manifest, or recovery credit changed.",
        "provenance": {
            "path": "evidence/experiments/savegame-table/provenance.json",
            "sha256": digest(PROVENANCE),
        },
        "extended_table": {
            "record_count_before_count_zero": len(records),
            "start_offset": records[0]["record_offset"],
            "records_end_exclusive": terminator["offset"],
            "records_after_root_report_end": len(records) - len(
                json.loads(PROVENANCE.read_text(encoding="utf-8"))["table"]["records"]
            ),
            "terminator": terminator,
            "target_segment_runs": runs,
            "kind_counts": {},
            "target_segment_counts": {},
            "tail_target_segment_counts": {},
            "record_owners": [
                {
                    "index": row["index"],
                    "kind_word": row["kind_word"],
                    "count": row["byte_count"],
                    "target_segment": row["pointer_segment"],
                    "target_mapsym": row["exact_mapsym_name"],
                }
                for row in records
            ],
        },
        "profile": "ANTEDIT_MODULE /AL /G2 /Gs /Oeglw",
        "variants": [],
    }
    for row in records:
        kinds = results["extended_table"]["kind_counts"]
        kinds[str(row["kind_word"])] = kinds.get(str(row["kind_word"]), 0) + 1
        targets = results["extended_table"]["target_segment_counts"]
        targets[str(row["pointer_segment"])] = targets.get(str(row["pointer_segment"]), 0) + 1
        if row["index"] >= 50:
            tail_targets = results["extended_table"]["tail_target_segment_counts"]
            tail_targets[str(row["pointer_segment"])] = (
                tail_targets.get(str(row["pointer_segment"]), 0) + 1
            )
    for name, name_object, sentinel, const_table in variants:
        results["variants"].append(
            summarize(name, make_source(name_object, sentinel, const_table))
        )
    results["variant_checks"] = []
    expected_owners = [row["exact_mapsym_name"] for row in records]
    for variant in results["variants"]:
        data_segment = next(
            segment for segment in variant["segments"] if segment["name"] == "SIMANT_DATA_GROUP"
        )
        parsed = omf.parse((HERE / variant["object"].split("/")[-1]).read_bytes())
        data = bytes.fromhex(next(seg["data_hex"] for seg in parsed["segments"] if seg["name"] == "SIMANT_DATA_GROUP"))
        pointer_fixups = sorted(
            [fixup for fixup in variant["fixups"] if fixup["segment"] == "SIMANT_DATA_GROUP"],
            key=lambda fixup: fixup["offset"],
        )
        actual_owners = [fixup["target"].get("name") for fixup in pointer_fixups]
        actual_offsets = [fixup["offset"] for fixup in pointer_fixups]
        record_fields_match = all(
            struct.unpack_from("<2H", data, 80 + index * 8)
            == (row["kind_word"], row["byte_count"])
            for index, row in enumerate(records)
        )
        terminator_fields_match = (
            variant["sentinel_in_source"]
            and struct.unpack_from("<2H", data, 80 + len(records) * 8) == (0, 0)
        )
        results["variant_checks"].append(
            {
                "source": variant["source"],
                "source_sha256": variant["source_sha256"],
                "object": variant["object"],
                "object_sha256": variant["object_sha256"],
                "based_segment_length": data_segment["length"],
                "sentinel_in_source": variant["sentinel_in_source"],
                "initial_name_span_all_zero": data[:80] == bytes(80),
                "record_fields_all_match": record_fields_match,
                "records_have_expected_8_byte_stride": actual_offsets
                == [84 + index * 8 for index in range(len(records))],
                "pointer_fixup_names_match_all_records": actual_owners == expected_owners,
                "pointer_fixups_are_four_byte_far_relocations": all(
                    fixup["width"] == 4 for fixup in pointer_fixups
                ),
                "terminator_count_zero": terminator_fields_match,
                "pointer_fixup_count": len(pointer_fixups),
                "omf_data_sha256": data_segment["initialized_bytes_sha256"],
            }
        )
    (HERE / "results.json").write_text(
        json.dumps(results, indent=2) + "\n", encoding="utf-8"
    )
    print(HERE / "results.json")


if __name__ == "__main__":
    main()
