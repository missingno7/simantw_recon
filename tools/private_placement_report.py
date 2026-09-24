"""Explain private-segment placement constraints in a preserved compiler result.

This is a read-only diagnostic. It reproduces the input operands used by
library_match.compare_member's private-placement check, without deciding
whether a member matches or granting recovery credit.
"""

import argparse
import json
from collections import defaultdict
from pathlib import Path

from common import ROOT, fixture
import ne
import omf
import mapsym


def repeated_period(data):
    """Return an exact byte repetition period, if the initialized data has one."""
    if not data or not any(data):
        return None
    for width in range(1, len(data) // 2 + 1):
        if len(data) % width == 0 and data == data[:width] * (len(data) // width):
            return width
    return None


def report(result_path, candidate=0):
    result = json.loads(Path(result_path).read_text(encoding="utf-8"))
    rows = [row for row in result["results"] if row["candidate"] == candidate]
    if len(rows) != 1:
        raise ValueError("candidate %d has %d result rows" % (candidate, len(rows)))
    row = rows[0]
    receipt = row["receipt"]
    member = omf.parse((ROOT / receipt["object"]).read_bytes())
    original = fixture("SIMANTW.EXE")
    image = ne.parse(original)
    symbols = mapsym.parse(fixture("SIMANTW.SYM"))
    placements = {int(k): tuple(v) for k, v in row["comparison"].get("placements", {}).items()}
    constraints = defaultdict(list)

    for fixup in member["fixups"]:
        code_index = fixup["segment"]
        private_index = fixup["target_index"]
        if (code_index not in placements or fixup["target_method"] != 0
                or private_index in placements or fixup["location_type"] != 1
                or fixup["self_relative"]):
            continue
        target_segment = member["segments"][private_index - 1]
        if fixup["frame_method"] == 1 and member["groups"][fixup["frame_index"] - 1]["name"] == "DGROUP":
            original_segment = 10
        elif ((fixup["frame_method"] == 0 and fixup["frame_index"] == private_index)
              or fixup["frame_method"] == 5):
            named = [seg["number"] for seg in symbols["segments"] if seg["name"] == target_segment["name"]]
            if len(named) != 1:
                continue
            original_segment = named[0]
        else:
            continue

        source_segment, source_base = placements[code_index]
        candidate_code = bytes.fromhex(member["segments"][code_index - 1]["data_hex"])
        target_code = image["segments"][source_segment - 1]
        site = fixup["offset"]
        original_site = target_code["file_offset"] + source_base + site
        original_operand = int.from_bytes(original[original_site:original_site + 2], "little")
        candidate_operand = int.from_bytes(candidate_code[site:site + 2], "little")
        implied_base = (original_operand - candidate_operand - fixup["displacement"]) & 0xFFFF
        publics = [p for p in member["publics"] if p["segment"] == code_index and p["offset"] <= site]
        owner = max(publics, key=lambda p: p["offset"])["name"] if publics else None
        constraints[private_index].append(dict(
            code_segment=member["segments"][code_index - 1]["name"],
            code_offset=site,
            nearest_public=owner,
            original_operand=original_operand,
            candidate_operand=candidate_operand,
            displacement=fixup["displacement"],
            implied_original_segment=original_segment,
            implied_base=implied_base,
        ))

    private_segments = []
    for index, sites in sorted(constraints.items()):
        segment = member["segments"][index - 1]
        bases = sorted({(site["implied_original_segment"], site["implied_base"]) for site in sites})
        data = bytes.fromhex(segment["data_hex"])
        private_segments.append(dict(
            candidate_segment=index,
            name=segment["name"],
            segment_class=segment["class"],
            length=segment["length"],
            implied_placements=[dict(segment=s, base=b) for s, b in bases],
            conflicting=len(bases) > 1,
            exact_repeat_period=repeated_period(data),
            sites=sites,
        ))
    return dict(
        scope="Diagnostic only; each implied base is a fixup constraint, not a proven object boundary or recovery credit",
        result=str(Path(result_path)),
        candidate=candidate,
        object=receipt["object"],
        private_segments=private_segments,
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("result", help="preserved compiler results.json")
    parser.add_argument("--candidate", type=int, default=0)
    args = parser.parse_args()
    print(json.dumps(report(args.result, args.candidate), indent=2))


if __name__ == "__main__":
    main()
