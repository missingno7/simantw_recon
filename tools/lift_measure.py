"""Compile-loop measurements for the symbolic MSC7 lifter (generated detail in build/)."""
from __future__ import annotations

import argparse
import json
import statistics
import subprocess
import sys
import threading
import traceback
import re
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import lift
import lift_frame
from common import read_json

STRICT = {"CONFIRMED_MEMBER", "STRONGLY_SUPPORTED_MEMBER"}
_OUTPUT_NAMES: dict[str, str] | None = None
_OUTPUT_NAMES_LOCK = threading.Lock()


def _output_filename(symbol: str) -> str:
    global _OUTPUT_NAMES
    if _OUTPUT_NAMES is None:
        with _OUTPUT_NAMES_LOCK:
            if _OUTPUT_NAMES is None:
                names = sorted(set(lift.control_symbols() + lift.open_symbols()))
                _OUTPUT_NAMES = lift.output_filenames(names)
    return _OUTPUT_NAMES.get(symbol) or lift.output_filenames([symbol])[symbol]


def _search(symbol: str, source: Path) -> dict[str, Any]:
    run = subprocess.run([sys.executable, str(ROOT / "tools" / "search.py"), symbol,
                          str(source), "--frame"], cwd=ROOT, text=True, capture_output=True)
    if run.returncode:
        # A compiler ICE can leave no OUTPUT.OBJ, which makes search.py return
        # nonzero even though the source did reach MSC. Count that as a compile
        # failure; keep cache/worker errors as harness errors.
        diagnostic = f"{run.stderr}\n{run.stdout}"
        worker = re.search(r"compiler-workers[\\/]+(W[^\\/]+)[\\/]+work", diagnostic)
        if worker:
            compiler_log = ROOT / "build" / "compiler-workers" / worker.group(1) / "work" / "OUTPUT.LOG"
            try:
                log_text = compiler_log.read_text(encoding="latin1", errors="replace")
            except OSError:
                log_text = ""
            if re.search(r"fatal error C\d+|internal compiler error", log_text, re.IGNORECASE):
                return {"best": {"result": "COMPILE_FAILED", "compiler_error": log_text[-3000:]},
                        "report": None}
        raise RuntimeError(f"search returned {run.returncode} for {symbol}: {run.stderr[-3000:]}")
    try:
        payload = json.loads(run.stdout)
    except Exception:
        raise RuntimeError(f"search failed for {symbol}: {run.returncode}\n{run.stderr[-3000:]}\n{run.stdout[-1000:]}")
    return payload


def _summary(payload: dict[str, Any]) -> dict[str, Any]:
    best = payload.get("best", {})
    op, total = (0, 0)
    try:
        op, total = map(int, str(best.get("opcodes", "0/0")).split("/", 1))
    except ValueError:
        pass
    byte_count = 0
    byte_total = 0
    try:
        byte_count, byte_total = map(int, str(best.get("bytes", "0/0")).split("/", 1))
    except ValueError:
        pass
    diag = best.get("diagnostic") or {}
    if not total:
        total = int(diag.get("opcode_total") or 0)
        op = int(diag.get("opcode_matches") or 0)
    return {
        "compiled": best.get("result") != "COMPILE_FAILED" and bool(best),
        "result": best.get("result", "NO_RESULT"),
        "strict": best.get("result") in STRICT,
        "exact_body": bool(best.get("exact_body")),
        "opcodes": op,
        "opcode_total": total,
        "opcode_ratio": op / total if total else 0.0,
        "candidate_bytes": byte_count,
        "target_bytes": byte_total or int(best.get("target_size") or 0),
        "frame": best.get("frame"),
        "report": payload.get("report"),
    }


def _frame_controls(candidate: dict[str, Any] | None, oracle: dict[str, Any] | None) -> bool:
    return lift_frame.frame_exact(candidate, oracle)


def _write_source(symbol: str, path: Path, legacy: bool = False) -> tuple[str, Any]:
    lifter_type = lift.RegisterTransliterationLifter if legacy else lift.Lifter
    lifter = lifter_type(symbol)
    source = lifter.lift()
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(source, encoding="ascii", newline="\n")
    return source, lifter


def _run_symbol(symbol: str, kind: str, outdir: Path, v1: bool) -> dict[str, Any]:
    try:
        if kind == "open":
            v2_path = outdir / "open" / _output_filename(symbol)
            _, v2_lifter = _write_source(symbol, v2_path)
            v2 = _summary(_search(symbol, v2_path))
            v2["frame_exact"] = lift_frame.target_access_exact(v2.get("frame"))
            v2["source"] = str(v2_path)
            index = read_json(ROOT / "evidence" / "recovery" / "drafts" / "index.json")
            old = (index.get(symbol) or {}).get("best") or {}
            target_size = int(v2.get("target_bytes") or old.get("target_bytes") or 0)
            old_size = int(old.get("candidate_bytes") or 0)
            old_total = int(old.get("opcode_total") or 0)
            old_opcodes = int(old.get("opcode_matches") or 0)
            # The requested "new best" criterion is the preserved draft's
            # opcode_matches field. Size closeness or a strict result must not
            # turn an equal/lower opcode score into a better open draft.
            v2["beats_preserved_best"] = v2["opcodes"] > old_opcodes
            v2["preserved_best"] = {"result": old.get("result"), "candidate_bytes": old_size,
                                    "target_bytes": old.get("target_bytes"), "opcode_matches": old.get("opcode_matches"),
                                    "opcode_total": old_total}
            v2["target_size"] = target_size
            v2["instructions"] = len(v2_lifter.f.instructions)
            v2["unsupported"] = dict(v2_lifter.f.unsupported)
            return {"symbol": symbol, "kind": kind, "v2": v2}

        # Controls are lifted from the target packet. The admitted source is
        # used only as a /Zi CodeView oracle after the candidate is generated.
        v2_path = outdir / "controls" / _output_filename(symbol)
        _, v2_lifter = _write_source(symbol, v2_path)
        v2 = _summary(_search(symbol, v2_path))
        recipe = lift.recipes()[symbol]
        oracle_path = ROOT / recipe["source"]
        oracle = _summary(_search(symbol, oracle_path))
        v2["frame_exact"] = _frame_controls(v2.get("frame"), oracle.get("frame"))
        v2["frame_oracle_status"] = (oracle.get("frame") or {}).get("status")
        v2["source"] = str(v2_path)
        v2["oracle_source"] = str(oracle_path)
        v2["instructions"] = len(v2_lifter.f.instructions)
        v2["unsupported"] = dict(v2_lifter.f.unsupported)

        if v1:
            v1_path = outdir / "v1" / "controls" / _output_filename(symbol)
            _, _v1_lifter = _write_source(symbol, v1_path, legacy=True)
            baseline = _summary(_search(symbol, v1_path))
            baseline["frame_exact"] = _frame_controls(baseline.get("frame"), oracle.get("frame"))
            baseline["source"] = str(v1_path)
        else:
            baseline = None
        return {"symbol": symbol, "kind": kind, "v1": baseline, "v2": v2,
                "oracle": {"result": oracle.get("result"), "frame": oracle.get("frame")}}
    except Exception:
        return {"symbol": symbol, "kind": kind, "error": traceback.format_exc()}


def _metrics(rows: list[dict[str, Any]], key: str) -> dict[str, Any]:
    good = [r[key] for r in rows if key in r and isinstance(r.get(key), dict) and "error" not in r.get(key, {})]
    compiled = [x for x in good if x.get("compiled")]
    return {
        "count": len(good),
        "compiled": len(compiled),
        "compile_percent": round(100 * len(compiled) / len(good), 1) if good else 0.0,
        "frame_exact": sum(bool(x.get("frame_exact")) for x in good),
        "strict": sum(bool(x.get("strict")) for x in good),
        "strict_percent": round(100 * sum(bool(x.get("strict")) for x in good) / len(good), 1) if good else 0.0,
        "median_opcode_agreement": round(100 * statistics.median([x["opcode_ratio"] for x in compiled]), 1) if compiled else 0.0,
    }


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--mode", choices=("controls", "open", "all"), default="all")
    ap.add_argument("--out", default="build/lift2")
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--v1", action="store_true", help="also replay the preserved register-transliteration generator on controls")
    ap.add_argument("--limit", type=int, help="debug or pilot limit per selected population")
    args = ap.parse_args(argv)
    outdir = Path(args.out)
    if not outdir.is_absolute(): outdir = ROOT / outdir
    work: list[tuple[str, str]] = []
    if args.mode in ("controls", "all"):
        names = lift.control_symbols()
        work.extend((name, "control") for name in (names[:args.limit] if args.limit is not None else names))
    if args.mode in ("open", "all"):
        names = lift.open_symbols()
        work.extend((name, "open") for name in (names[:args.limit] if args.limit is not None else names))
    rows: list[dict[str, Any]] = []
    with ThreadPoolExecutor(max_workers=max(1, min(6, args.workers))) as pool:
        futures = {pool.submit(_run_symbol, symbol, kind, outdir, args.v1): (symbol, kind)
                   for symbol, kind in work}
        for n, future in enumerate(as_completed(futures), 1):
            row = future.result()
            rows.append(row)
            if n % 10 == 0 or n == len(futures):
                rows.sort(key=lambda x: (x["kind"], x["symbol"]))
                outdir.mkdir(parents=True, exist_ok=True)
                (outdir / "measurement.partial.json").write_text(json.dumps(rows, indent=2) + "\n", encoding="utf-8")
                print(f"measured {n}/{len(futures)}", flush=True)
    rows.sort(key=lambda x: (x["kind"], x["symbol"]))
    controls = [x for x in rows if x["kind"] == "control"]
    opened = [x for x in rows if x["kind"] == "open"]
    report = {
        "generator": "tools/lift.py SymbolicLifter",
        "counts": {"controls": len(controls), "open": len(opened), "errors": sum("error" in x for x in rows)},
        "controls_v2": _metrics(controls, "v2"),
        "controls_v1": _metrics(controls, "v1") if args.v1 else None,
        "open_v2": {
            **_metrics(opened, "v2"),
            "at_least_90_percent_target_bytes": sum((x.get("v2", {}).get("candidate_bytes", 0) >=
                                                       0.9 * x.get("v2", {}).get("target_size", 1)) for x in opened),
            "beats_preserved_best": sum(bool(x.get("v2", {}).get("beats_preserved_best")) for x in opened),
            "new_best_symbols": [x["symbol"] for x in opened if x.get("v2", {}).get("beats_preserved_best")],
        },
        "errors": [x for x in rows if "error" in x],
        "rows": rows,
    }
    outdir.mkdir(parents=True, exist_ok=True)
    (outdir / "measurement.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: v for k, v in report.items() if k not in ("rows", "errors")}, indent=2))
    return 1 if report["errors"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
