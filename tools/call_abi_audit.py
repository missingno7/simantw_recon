"""Read-only audit of candidate near prototypes against target call bytes.

LINK 5.30 can lower a same-segment source far call to NOP; PUSH CS; CALL near.
The final CALL opcode alone therefore does not justify a near declaration.
This report flags source hypotheses for review; it is never recovery proof.
"""

import argparse
import json
import re
from collections import Counter
from hashlib import sha256
from pathlib import Path

from common import ROOT


EXTERN = re.compile(r"^[ \t]*extern\b[^;]*;", re.MULTILINE)
NEAR_FUNCTION = re.compile(r"\bnear\s+([A-Za-z_]\w*)\s*\(")


def near_function_declarations(source):
    """Return conservative (name, line, declaration) near-function prototypes."""
    declarations = []
    for statement in EXTERN.finditer(source):
        function = NEAR_FUNCTION.search(statement.group())
        if function:
            declarations.append((
                function.group(1),
                source.count("\n", 0, statement.start()) + 1,
                " ".join(statement.group().split()),
            ))
    return declarations


def named_call_sites(card, callee):
    """Identify named direct calls and the observed LINK far-call signature."""
    names = {callee, "_" + callee.lstrip("_")}
    sites = []
    rows = card["disassembly"]
    for index, row in enumerate(rows):
        if row["mnemonic"] != "call" or not row["bytes"].startswith("e8"):
            continue
        if not any(
            ref.get("kind") == "near_call" and names.intersection(ref.get("names", []))
            for ref in row["references"]
        ):
            continue
        lowered = (
            index >= 2
            and rows[index - 2]["bytes"] == "90"
            and rows[index - 1]["bytes"] == "0e"
            and rows[index - 2]["offset"] + 1 == rows[index - 1]["offset"]
            and rows[index - 1]["offset"] + 1 == row["offset"]
        )
        sites.append({
            "offset": row["offset"],
            "bytes": ("900e" if lowered else "") + row["bytes"],
            "observed_form": "linker_lowered_far_call" if lowered else "direct_near_call",
            "target": next(
                ref["offset"] for ref in row["references"]
                if ref.get("kind") == "near_call" and names.intersection(ref.get("names", []))
            ),
        })
    return sites


def linker_lowered_far_calls(card):
    """Compact named target sites with the exact LINK-lowered call signature."""
    rows = card["disassembly"]
    groups = {}
    for index in range(2, len(rows)):
        row = rows[index]
        if (
            row["mnemonic"] != "call" or not row["bytes"].startswith("e8")
            or rows[index - 2]["bytes"] != "90"
            or rows[index - 1]["bytes"] != "0e"
            or rows[index - 2]["offset"] + 1 != rows[index - 1]["offset"]
            or rows[index - 1]["offset"] + 1 != row["offset"]
        ):
            continue
        for ref in row["references"]:
            if ref.get("kind") != "near_call" or not ref.get("names"):
                continue
            key = (ref["segment"], ref["offset"], tuple(ref["names"]))
            groups.setdefault(key, []).append(row["offset"] - card["offset"])
    return [
        {"callee_names": list(names), "segment": segment,
         "target_offset": target, "caller_offsets": sites}
        for (segment, target, names), sites in sorted(groups.items())
    ]


def audit_source(source, card):
    """Flag declarations contradicted by at least one named target call site."""
    findings = []
    resolved = 0
    for callee, line, declaration in near_function_declarations(source):
        sites = named_call_sites(card, callee)
        if not sites:
            continue
        resolved += 1
        lowered = [site for site in sites if site["observed_form"] == "linker_lowered_far_call"]
        if lowered:
            findings.append({
                "callee": callee,
                "line": line,
                "declaration": declaration,
                "sites": sites,
                "diagnostic": "near prototype conflicts with target NOP; PUSH CS; CALL near signature",
            })
    return resolved, findings


def audit_jobs(root=ROOT, symbol=None):
    cards_path = root / "evidence/disassembly/cards.jsonl"
    cards = {card["symbol"]: card for card in (
        json.loads(line) for line in cards_path.open(encoding="utf-8")
    )}
    findings = []
    resolved = 0
    for candidate in sorted((root / "evidence/recovery/workflow/jobs").glob("*/candidate.c")):
        job_path = candidate.parent / "job.json"
        if not job_path.exists():
            continue
        job = json.loads(job_path.read_text(encoding="utf-8"))
        if symbol and job["symbol"] != symbol:
            continue
        card = cards.get(job["symbol"])
        if not card:
            continue
        source_bytes = candidate.read_bytes()
        count, candidate_findings = audit_source(source_bytes.decode("utf-8"), card)
        resolved += count
        for finding in candidate_findings:
            findings.append({
                "symbol": job["symbol"],
                "job": job["id"],
                "job_status": job["status"],
                "candidate": candidate.relative_to(root).as_posix(),
                "candidate_sha256": sha256(source_bytes).hexdigest(),
                **finding,
            })
    return {
        "scope": "Current workflow candidate.c files and current generated cards; a review diagnostic, not source or TU proof",
        "evidence": ["docs/grinder-lessons.md", "evidence/experiments/toolchain/link-probe/"],
        "near_declarations_with_named_call_sites": resolved,
        "conflicting_declarations": len(findings),
        "affected_jobs": len({finding["job"] for finding in findings}),
        "by_status": dict(sorted(Counter(finding["job_status"] for finding in findings).items())),
        "findings": findings,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--symbol", help="restrict to one MAPSYM symbol, including its leading underscore")
    parser.add_argument("--output", type=Path, help="write JSON to this file instead of stdout")
    args = parser.parse_args()
    result = json.dumps(audit_jobs(symbol=args.symbol), indent=2) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(result, encoding="utf-8")
    else:
        print(result, end="")


if __name__ == "__main__":
    main()
