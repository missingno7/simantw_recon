"""Read-only provenance report for the SaveGame/LoadGame data table.

This inspects the original NE and MAPSYM. It does not generate source or
promote a recovered member. Segment-relocation chain words are deliberately
excluded from the semantic record fields.
"""

import collections
import json
from pathlib import Path
import struct
import sys


ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import mapsym  # noqa: E402
import ne  # noqa: E402


def main():
    exe = (ROOT / "assets" / "SIMANTW.EXE").read_bytes()
    sym = (ROOT / "assets" / "SIMANTW.SYM").read_bytes()
    parsed_ne = ne.parse(exe)
    parsed_sym = mapsym.parse(sym)
    segment = parsed_ne["segments"][7]
    assert segment["number"] == 8 and segment["kind"] == "DATA"
    base = segment["file_offset"]
    by_site = {
        site: relocation
        for relocation in segment["relocations"]
        for site in relocation["sites"]
    }
    sites = sorted(site for site in by_site if 0x9500 <= site < 0x9700)
    assert len(sites) == 50
    assert sites == list(range(0x9576, 0x96FF, 8))
    names = {
        (entry["number"], symbol["offset"]): symbol["name"]
        for entry in parsed_sym["segments"]
        for symbol in entry["symbols"]
    }
    records = []
    for index, site in enumerate(sites):
        origin = site - 6
        kind, byte_count, pointer_offset = struct.unpack_from("<3H", exe, base + origin)
        relocation = by_site[site]
        assert relocation["source_type"] == 2 and relocation["width"] == 2
        target = relocation["target"]
        assert target["kind"] == "internal" and target["offset"] == 0
        target_segment = target["segment"]
        name = names.get((target_segment, pointer_offset))
        assert name is not None, (index, target_segment, pointer_offset)
        records.append(
            {
                "index": index,
                "record_offset": origin,
                "kind_word": kind,
                "byte_count": byte_count,
                "pointer_offset": pointer_offset,
                "pointer_segment": target_segment,
                "exact_mapsym_name": name,
                "segment_relocation_site": site,
            }
        )
    assert all(x == 0 for x in exe[base + 0x9520 : base + 0x9570])
    crossrefs = []
    for line in (ROOT / "evidence" / "disassembly" / "cards.jsonl").open(encoding="utf-8"):
        card = json.loads(line)
        if card["symbol"] not in ("_LoadGame", "_SaveGame", "_ClearLastFileName"):
            continue
        for instruction in card.get("disassembly", []):
            operand = instruction.get("operands", "")
            if "0x9520" in operand or "0x9570" in operand:
                crossrefs.append(
                    {
                        "symbol": card["symbol"],
                        "code_offset": instruction["offset"],
                        "instruction": instruction["mnemonic"] + " " + operand,
                    }
                )
    report = {
        "scope": "Research only; observed 50-record prefix, not a proven complete table; no historical TU ownership, source declaration, or recovery credit",
        "fixtures": {
            "exe_sha256": parsed_ne["sha256"],
            "sym_sha256": parsed_sym["sha256"],
        },
        "original_segment": 8,
        "zero_span": {
            "start": 0x9520,
            "end_exclusive": 0x9570,
            "all_zero": True,
            "note": "The 80-byte span is observed, not proof of one object or its source class.",
        },
        "table": {
            "start": sites[0] - 6,
            "end_exclusive": sites[-1] + 2,
            "extent_status": "observed_prefix_only; scan continues beyond this range",
            "record_size": 8,
            "record_count": len(records),
            "all_pointer_targets_named": True,
            "target_segment_counts": dict(collections.Counter(str(row["pointer_segment"]) for row in records)),
            "kind_counts": dict(collections.Counter(str(row["kind_word"]) for row in records)),
            "records": records,
        },
        "crossrefs": crossrefs,
        "relocation_note": "The fourth word in each on-disk record is an NE loader-chain link at a segment relocation site, not a source constant. Use its relocation target segment instead.",
    }
    destination = Path(__file__).with_name("provenance.json")
    destination.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(destination)
    print(report["table"]["target_segment_counts"], report["table"]["kind_counts"])


if __name__ == "__main__":
    main()
