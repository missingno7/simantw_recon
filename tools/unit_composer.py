"""Bounded, relocation-aware placement search for extending an admitted unit.

The unit source is the seed, not a set of ingredients to recompose. Existing
member items and scaffold code stay intact; the runner inserts only supplied
member definitions and their missing file-scope declarations. Its variants
change the order or representation of file-scope placement items only.
"""
from __future__ import annotations

import argparse
import ast
import hashlib
import json
import re
import shutil
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

from common import ROOT, FormatError, read_json, write_json, identity, cards

RECOVERY = ROOT / "src/recovery.json"
UNITS = ROOT / "evidence/recovery/units"
WORKERS_ROOT = ROOT / "build/workers"
OUT_ROOT = WORKERS_ROOT / "f-infra-composer"
READY = OUT_ROOT / "ready"
GOOD = {"CONFIRMED_MEMBER", "STRONGLY_SUPPORTED_MEMBER"}
ALLOWED_EXTERNAL_READ = Path(r"D:\Prog\simantw_recon\build\workers")


@dataclass
class Item:
    kind: str
    text: str
    name: str | None = None
    names: tuple[str, ...] = ()


def _tu():
    import tu_assembly
    return tu_assembly


def _read_source(path: str | Path) -> tuple[Path, str]:
    p = Path(path)
    if not p.is_absolute():
        p = ROOT / p
    resolved = p.resolve()
    allowed = resolved.is_relative_to(ROOT.resolve()) or resolved.is_relative_to(ALLOWED_EXTERNAL_READ.resolve())
    if not allowed or not resolved.is_file():
        raise FormatError("source must be in this worktree or the permitted main-repo worker tree: " + str(path))
    return resolved, resolved.read_text(encoding="latin1")


def _itemize(text: str) -> list[Item]:
    rows = []
    for it in _tu().split_items(text):
        rows.append(Item(it["kind"], it["text"], it.get("name"), tuple(it.get("names", ()))))
    return rows


def _definition(items: list[Item], symbol: str) -> Item:
    expected = symbol.lstrip("_")
    matches = [x for x in items if x.kind == "definition" and (x.name == expected or (not symbol.startswith("_") and x.name and x.name.upper() == symbol))]
    if len(matches) != 1:
        raise FormatError("source must contain one definition of %s (found %d)" % (symbol, len(matches)))
    return matches[0]


def _latest_admitted_unit(component: str) -> tuple[str, dict, str, dict]:
    recovery = read_json(RECOVERY).get("targets", {})
    candidates: dict[str, dict] = {}
    for symbol, target in recovery.items():
        unit_id = target.get("unit")
        if not unit_id:
            continue
        path = UNITS / unit_id / "unit.json"
        if not path.is_file():
            continue
        spec = read_json(path)
        if spec.get("component") != component or spec.get("status") != "COMPOSED":
            continue
        candidates[unit_id] = spec
    if not candidates:
        raise FormatError("no admitted unit source found for object " + component)
    def score(pair):
        unit_id, spec = pair
        promoted = sum(1 for m in spec.get("members", []) if recovery.get(m, {}).get("unit") == unit_id)
        return (promoted, len(spec.get("members", [])), spec.get("created", ""), unit_id)
    unit_id, spec = max(candidates.items(), key=score)
    admitted_members = [m for m in spec.get("members", []) if recovery.get(m, {}).get("unit") == unit_id]
    if not admitted_members:
        raise FormatError("no recovered member records name the selected admitted unit: " + unit_id)
    frozen_sources = sorted({recovery[m].get("source") for m in admitted_members if recovery[m].get("source")})
    source = frozen_sources[0] if len(frozen_sources) == 1 else spec.get("source")
    if not source:
        raise FormatError("latest admitted unit has no source: " + unit_id)
    source_path, text = _read_source(source)
    spec = dict(spec, members=admitted_members, source=source_path.relative_to(ROOT).as_posix(),
                source_identity=identity(source_path))
    if spec.get("scaffold"):
        items = _itemize(text)
        actual_stubs = [x.name for x in items if x.kind == "definition" and x.name and x.name.startswith("pool_stub_")]
        spec["scaffold"] = dict(spec["scaffold"], stubs=[{"function": n} for n in actual_stubs])
    return unit_id, spec, text, recovery


def _static_decl(item: Item) -> bool:
    code = _tu().strip_comments(item.text)
    return item.kind == "declaration" and bool(re.search(r"\bstatic\b", code)) and "=" in code


def _literal_init(item: Item) -> tuple[str, str] | None:
    """A conservative `static char name[] = \"...\"` declaration."""
    if not _static_decl(item):
        return None
    code = _tu().strip_comments(item.text).strip()
    m = re.fullmatch(r"static\s+(?:unsigned\s+)?char\s+([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*=\s*(\"(?:\\.|[^\"\\])*\")\s*;", code, re.S)
    if not m:
        return None
    return m.group(1), m.group(2)


def _insert_definition(items: list[Item], addition: Item, symbol: str, members: list[str], recovery: dict) -> list[Item]:
    expected = symbol.lstrip("_")
    existing = [i for i, x in enumerate(items) if x.kind == "definition" and (x.name == expected or (not symbol.startswith("_") and x.name and x.name.upper() == symbol))]
    if existing:
        result = list(items)
        result[existing[0]] = addition
        # Replacing an existing admitted member never changes its source
        # position. In particular, RUN*_TEXT and POOLSTUB source order is
        # evidence that must survive extension.
        return result
    result = list(items)
    stub_name = "pool_stub_" + symbol.lstrip("_")
    stub_index = next((i for i, x in enumerate(result) if x.kind == "definition" and x.name == stub_name), None)
    if stub_index is not None:
        stub_definition_rank = sum(1 for x in result[:stub_index] if x.kind == "definition")
        result.pop(stub_index)
        # The stand-in is retired with the claimed member. Leaving its old
        # prototype/alloc_text entry can add an empty or stale selector run.
        result = [item for item in result if not (
            item.kind == "declaration" and
            ((item.names and stub_name in item.names) or
             (item.text.lstrip().startswith("#pragma alloc_text") and
              re.search(r"\bPOOLSTUB_TEXT\s*,[^)]*\b" + re.escape(stub_name) + r"\b", item.text))))]
        # Retire this member's stand-in selector load and assign the real public
        # to the same RUN segment as the nearest earlier public with a fixed
        # address. Keep the function body at the old stand-in's source slot.
        c_name = addition.name or symbol.lstrip("_")
        offset = recovery.get(symbol, {}).get("offset")
        pragma_rows = []
        for i, item in enumerate(result):
            if item.kind != "declaration" or not item.text.lstrip().startswith("#pragma alloc_text"):
                continue
            match = re.fullmatch(r"#pragma\s+alloc_text\s*\(\s*([A-Za-z_]\w*)\s*,\s*(.*?)\s*\)", item.text.strip())
            if not match:
                continue
            segment, tail = match.groups()
            names = [x.strip() for x in tail.split(",") if x.strip()]
            if stub_name in names:
                names.remove(stub_name)
                result[i] = (Item("declaration", "#pragma alloc_text(%s, %s)" % (segment, ", ".join(names)), names=())
                             if names else Item("comment", ""))
            elif segment.startswith("RUN"):
                group_offsets = [(recovery.get("_" + name, {}).get("offset"), segment, i)
                                 for name in names if recovery.get("_" + name, {}).get("offset") is not None]
                if group_offsets:
                    pragma_rows.append((min(x[0] for x in group_offsets), max(x[0] for x in group_offsets), segment, i, names))
        if offset is not None and pragma_rows:
            before = [x for x in pragma_rows if x[0] <= offset]
            after = [x for x in pragma_rows if x[0] > offset]
            selected = max(before, key=lambda x: x[0]) if before else min(after, key=lambda x: x[0])
            _, _, segment, i, names = selected
            if c_name not in names:
                names.append(c_name)
            result[i] = Item("declaration", "#pragma alloc_text(%s, %s)" % (segment, ", ".join(names)), names=())
            # MSC requires an alloc_text member to be declared before the
            # pragma. Keep this prototype outside the function definition.
            head = addition.text.split("{", 1)[0].strip()
            if head and not any(x.kind == "declaration" and re.search(r"\b" + re.escape(c_name) + r"\s*\(", x.text) for x in result):
                proto = Item("declaration", head.rstrip(";") + ";", names=(c_name,))
                pragma_at = next((j for j, x in enumerate(result) if x.kind == "declaration" and x.text.lstrip().startswith("#pragma alloc_text")), i)
                result.insert(pragma_at, proto)
                if pragma_at <= i:
                    i += 1
        definition_positions = [i for i, x in enumerate(result) if x.kind == "definition"]
        insert_at = (definition_positions[stub_definition_rank]
                     if stub_definition_rank < len(definition_positions)
                     else (definition_positions[-1] + 1 if definition_positions else len(result)))
        result.insert(insert_at, addition)
        return result
    # MAPSYM function order is fixed wherever recorded. An unnamed scaffold
    # definition remains anchored; the new member is placed immediately before
    # the first later public, otherwise immediately after the last earlier one.
    target = recovery.get(symbol, {})
    offset = target.get("offset")
    if offset is None:
        result.append(addition)
        return result
    later_positions = []
    earlier_positions = []
    for i, item in enumerate(result):
        if item.kind != "definition" or not item.name:
            continue
        name = next((m for m in members if (m.lstrip("_") == item.name or (not m.startswith("_") and m.upper() == item.name.upper()))), None)
        if name is None:
            continue
        other = recovery.get(name, {}).get("offset")
        if other is None:
            continue
        if other > offset:
            later_positions.append(i)
        elif other < offset:
            earlier_positions.append(i)
    if later_positions:
        result.insert(min(later_positions), addition)
    elif earlier_positions:
        result.insert(max(earlier_positions) + 1, addition)
    else:
        result.append(addition)
    return result


def _all_target_records(recovery: dict) -> dict:
    result = dict(recovery)
    for card in cards():
        result.setdefault(card["symbol"], card)
    return result


def _refresh_scaffold(spec: dict, items: list[Item]) -> None:
    scaffold = spec.get("scaffold")
    if not scaffold:
        return
    stubs = [x.name for x in items if x.kind == "definition" and x.name and x.name.startswith("pool_stub_")]
    runs = []
    for item in items:
        if item.kind != "declaration" or not item.text.lstrip().startswith("#pragma alloc_text"):
            continue
        match = re.fullmatch(r"#pragma\s+alloc_text\s*\(\s*(RUN\d+_TEXT)\s*,\s*(.*?)\s*\)", item.text.strip())
        if match:
            runs.append(["_" + x.strip() for x in match.group(2).split(",") if x.strip()])
    scaffold["stubs"] = [{"function": name} for name in stubs]
    if runs:
        scaffold["runs"] = runs


def _render(items: list[Item]) -> str:
    return "\n\n".join(it.text.rstrip() for it in items if it.text.strip()) + "\n"


def _first_function(items: list[Item]) -> int:
    return next((i for i, it in enumerate(items) if it.kind == "definition"), len(items))


def _dedupe_additions(base: list[Item], add_items: list[Item]) -> tuple[list[Item], list[Item]]:
    """Keep base declarations byte-for-byte; return new declaration items.

    Conflicting declaration spellings are kept as candidate diagnostics rather
    than silently selected. A strict compile/result will reject an invalid
    arrangement; callers can resolve forms in a source hypothesis first.
    """
    seen = defaultdict(set)
    for it in base:
        if it.kind == "declaration":
            for name in it.names or ("#" + " ".join(it.text.split()),):
                seen[name].add(" ".join(it.text.split()))
    fresh = []
    conflicts = []
    fingerprints = set()
    for it in add_items:
        if it.kind != "declaration":
            continue
        normalized = " ".join(it.text.split())
        if normalized in fingerprints:
            continue
        fingerprints.add(normalized)
        names = it.names or ("#" + normalized,)
        if all(normalized in seen[n] for n in names):
            continue
        if any(seen[n] and normalized not in seen[n] for n in names):
            conflicts.append(it)
            continue
        fresh.append(it)
        for name in names:
            seen[name].add(normalized)
    return fresh, conflicts


def _placement_declarations(items: list[Item], mode: str) -> list[Item]:
    """Reorder placement declarations without touching any function body."""
    result = list(items)
    positions = [i for i, item in enumerate(result) if _static_decl(item)]
    placement = [result[i] for i in positions]
    if mode == "reverse-static":
        placement.reverse()
    elif mode == "lexical-static":
        placement.sort(key=lambda x: tuple(x.names) or x.text)
    elif mode == "first-use-static":
        body_text = "\n".join(x.text for x in result if x.kind == "definition")
        def first_use(item):
            names = item.names
            positions = [m.start() for name in names for m in re.finditer(r"\b" + re.escape(name) + r"\b", body_text)]
            return (min(positions) if positions else 1 << 30, names, item.text)
        placement.sort(key=first_use)
    # Keep comments, extern/prototype declarations and every function item in
    # its original slot. Only initialized file-scope statics move.
    for index, item in zip(positions, placement):
        result[index] = item
    return result


def _literal_representation_variants(items: list[Item]) -> list[tuple[str, list[Item], list[str]]]:
    """Try a named static string as a literal macro without editing a body."""
    bodies = "\n".join(item.text for item in items if item.kind == "definition")
    rows = []
    for i, item in enumerate(items):
        parsed = _literal_init(item)
        if not parsed:
            continue
        name, literal = parsed
        # A write through the object would make a string-literal representation
        # observably different, so that alternative is not generated.
        writes = re.search(r"\b" + re.escape(name) + r"\s*(?:\[[^\]]*\]\s*)?=", bodies)
        if writes:
            continue
        changed = list(items)
        changed[i] = Item("declaration", "#define %s %s" % (name, literal), names=(name,))
        rows.append(("literal-macro-" + name, changed,
                     ["`%s` static array represented as an identical string-literal macro; member definition text is unchanged." % name,
                      "EXACT_STEERED if admitted: change `%s` from a named static array to literal allocation." % name]))
    return rows


def _poolstub_variants(items: list[Item]) -> list[tuple[str, list[Item], list[str]]]:
    """Reposition existing uncredited POOLSTUB functions as whole definitions."""
    positions = [i for i, item in enumerate(items) if item.kind == "definition" and item.name and item.name.startswith("pool_stub_")]
    if not positions:
        return []
    stubs = [items[i] for i in positions]
    rows = []
    for name, ordered, at_end in (("poolstub-last", stubs, True), ("poolstub-reverse", list(reversed(stubs)), False)):
        changed = [item for item in items if not (item.kind == "definition" and item.name and item.name.startswith("pool_stub_"))]
        if at_end:
            changed.extend(ordered)
        else:
            insert_at = min(positions[0], len(changed))
            changed[insert_at:insert_at] = ordered
        rows.append((name, changed, ["Existing POOLSTUB stand-ins moved as whole functions; body text and alloc_text directives are unchanged."]))
    return rows


def _regenerated_scaffold(items: list[Item], component: str, members: list[str],
                          spec: dict, recovery: dict,
                          additions: dict[str, dict]) -> tuple[list[Item], list[str]] | None:
    """Rebuild only uncredited selector stand-ins from the reviewed pool map.

    Recovered member definitions remain byte-for-byte source items. Existing
    POOLSTUB bodies are scaffolding, so the pool-map plan is the authority for
    their names, first-use references, and positions after an added member
    changes the claimed set.
    """
    tu = _tu()
    if not any(x.kind == "definition" and x.name and x.name.startswith("pool_stub_") for x in items):
        return None
    declared = {n for x in items if x.kind == "declaration" for n in (x.names or ())}
    declared_texts = {n: x.text for x in items if x.kind == "declaration" for n in (x.names or ())}
    source_catalog = {}
    chosen_sources = {}
    for member in members:
        added = additions.get(member)
        if added:
            chosen_sources[member] = added["path"]
            source_catalog[member] = {"source": added["path"], "basis": "REVIEWED_SOURCE_OVERRIDE"}
            continue
        record = recovery.get(member, {})
        source = record.get("source")
        if source:
            source_catalog[member] = {"source": source, "basis": "ADMITTED"}
    if len(source_catalog) != len(members):
        return None
    try:
        plan = tu.scaffold_plan(component, members, spec["flags"], declared,
                                declared_texts=declared_texts,
                                chosen_sources=chosen_sources,
                                source_catalog=source_catalog)
    except (FormatError, KeyError, OSError, ValueError):
        return None
    if set(plan.get("claimed", [])) != set(members):
        return None
    c_names = {m: m.lstrip("_") for m in members}
    parts = tu.scaffold_text(plan, declared_texts, c_names)
    old_scaffold_names = {
        x.name for x in items
        if x.kind == "definition" and x.name and
        (x.name.startswith("pool_stub_") or re.match(r"pool_(?:data|bss)_fill_", x.name))
    }
    clean = []
    for x in items:
        if x.kind == "definition" and x.name in old_scaffold_names:
            continue
        if x.kind == "declaration":
            code = tu.strip_comments(x.text)
            if "scaffold reference for pool word" in x.text:
                continue
            if x.names and all(n.startswith("pool_stub_") or n in old_scaffold_names or
                                n.startswith("pool_segment_ref_") for n in x.names):
                continue
            if code.lstrip().startswith("#pragma alloc_text(POOLSTUB_TEXT,"):
                continue
            if re.search(r"^static\\s+(?:unsigned\\s+)?char\\s+pool_(?:data|bss)_fill_", code.strip()):
                continue
        clean.append(x)

    # New helper externs and prototypes belong before the first function; exact
    # duplicate declarations already present in the admitted unit are retained
    # only once.
    fresh_decls = []
    existing = {" ".join(x.text.split()) for x in clean if x.kind == "declaration"}
    pool_pragmas = [text for text in parts["pragmas"]
                    if text.lstrip().startswith("#pragma alloc_text(POOLSTUB_TEXT,")]
    for text in parts["declarations"] + parts["prototypes"] + pool_pragmas:
        normalized = " ".join(text.split())
        if normalized in existing:
            continue
        existing.add(normalized)
        fresh_decls.append(Item("declaration", text, names=tuple(tu.declared_names(text))))
    insert = _first_function(clean)
    clean[insert:insert] = fresh_decls

    # Reinsert stand-ins before the next known public in original code order.
    target_rank = {name.lstrip("_"): i for i, name in enumerate(plan["publics_order"])}
    target_rank.update({name.lstrip("_").upper(): i for i, name in enumerate(plan["publics_order"])})
    generated = list(parts["definitions"])
    generated.sort(key=lambda d: (d.get("rank", 0), d.get("name", "")))
    for row in generated:
        item = Item("definition", row["text"], row["name"])
        rank = row.get("rank", 0)
        at = len(clean)
        for i, current in enumerate(clean):
            if current.kind != "definition" or not current.name:
                continue
            cur_rank = target_rank.get(current.name, target_rank.get(current.name.upper()))
            if cur_rank is not None and cur_rank > rank:
                at = i
                break
        clean.insert(at, item)

    # File-scope data fillers are placement stand-ins too. Place each just
    # before the following claimed member, as the ordinary TU scaffold does.
    for member, texts in plan.get("data_fillers", {}).items():
        c_name = member.lstrip("_")
        at = next((i for i, x in enumerate(clean)
                   if x.kind == "definition" and x.name == c_name), _first_function(clean))
        additions = [Item("declaration", text,
                          names=tuple(tu.declared_names(text))) for text in texts]
        clean[at:at] = additions
    return clean, ["POOLSTUB bodies were regenerated from the reviewed selector map; admitted member bodies were retained."]


def _alias_identical_strings(items: list[Item]) -> tuple[list[Item], list[str]]:
    groups = defaultdict(list)
    for i, item in enumerate(items):
        parsed = _literal_init(item)
        if parsed:
            groups[parsed[1]].append((i, parsed[0]))
    aliases = []
    replacements = {}
    for _, rows in groups.items():
        if len(rows) < 2:
            continue
        rows.sort()
        canonical = rows[0][1]
        for index, name in rows[1:]:
            replacements[index] = Item("declaration", "#define %s %s" % (name, canonical), names=(name,))
            aliases.append("%s -> %s (identical static string initializer)" % (name, canonical))
    return [replacements.get(i, item) for i, item in enumerate(items)], aliases


def _variants(seed_items: list[Item], max_arrangements: int, recovery: dict) -> list[tuple[str, list[Item], list[str]]]:
    rows = []
    seen = set()
    def add(name, items, notes=()):
        text = _render(items)
        digest = hashlib.sha256(text.encode("latin1")).hexdigest()
        if digest in seen or len(rows) >= max_arrangements:
            return
        seen.add(digest)
        rows.append((name, items, list(notes)))
    add("seed", list(seed_items), ["Latest admitted unit items retained; new declarations appended before the first function."])
    for mode in ("reverse-static", "first-use-static", "lexical-static"):
        add(mode, _placement_declarations(list(seed_items), mode), ["Only initialized file-scope static declarations were reordered."])
    for name, items, notes in _literal_representation_variants(seed_items):
        add(name, items, notes)
    aliased, aliases = _alias_identical_strings(list(seed_items))
    if aliases:
        add("share-identical-strings", aliased, ["File-scope aliases: " + "; ".join(aliases), "EXACT_STEERED if admitted: identical static strings share one allocation through object-like macros."])
        for mode in ("reverse-static", "first-use-static"):
            add("share-identical-strings+" + mode, _placement_declarations(aliased, mode), ["File-scope aliases: " + "; ".join(aliases), "EXACT_STEERED if admitted: identical static strings share one allocation through object-like macros."])
    for name, items, notes in _poolstub_variants(seed_items):
        add(name, items, notes)
    # MAPSYM offsets fix order when present. Permute only the definitions whose
    # source positions are genuinely unconstrained, keeping every anchored
    # member and every intervening placement item in its original slot.
    definitions = [x for x in seed_items if x.kind == "definition" and x.name]
    unknown = [x for x in definitions
               if not x.name.startswith("pool_stub_") and
               recovery.get("_" + x.name) is not None and
               recovery.get("_" + x.name, {}).get("offset") is None]
    if len(unknown) > 1:
        positions = [i for i, item in enumerate(seed_items) if item in unknown]
        lexical = sorted(unknown, key=lambda x: x.name)
        for name, ordered in (("member-unknown-name-order", lexical),
                              ("member-unknown-reverse-name-order", list(reversed(lexical)))):
            changed = list(seed_items)
            for index, definition in zip(positions, ordered):
                changed[index] = definition
            add(name, changed, ["Only members lacking fixed MAPSYM offsets changed order; anchored definitions and their slots were preserved."])
    return rows


def _result_row(report: dict) -> dict:
    results = report.get("results", [])
    if not results:
        return {"result": "NO_RESULT", "issues": ["compiler produced no candidate row"]}
    return results[0]


def _body_preflight(symbol: str, source: Path, flags: list[str], folder: Path) -> dict:
    """Require an exact body (allowing only unresolved unit placement) first."""
    from codegen_grinder import run
    from tu_assembly import body_exact
    report = run(dict(symbol=symbol, source=source.relative_to(ROOT).as_posix(),
                      compiler="msc700", flags=flags, max_candidates=1, axes=[],
                      semantic_summary="Composer body-exact preflight for " + symbol,
                      publics=[symbol]), folder.relative_to(ROOT).as_posix(), cache=True)
    row = _result_row(report)
    comparison = row.get("comparison", {})
    return {"symbol": symbol, "source": source.relative_to(ROOT).as_posix(),
            "result": comparison.get("result"), "body_exact": body_exact(comparison),
            "issues": comparison.get("issues", []),
            "diagnostic": comparison.get("diagnostic", {})}


def _strict_summary(row: dict) -> dict:
    c = row.get("comparison", {})
    contributions = c.get("contributions", [])
    diverged = sum(len(x.get("divergences", [])) for x in contributions)
    failed_fixups = sum(sum(1 for f in x.get("fixups", []) if not f.get("equal")) for x in contributions)
    status = c.get("result", "UNKNOWN")
    candidate_match = status in GOOD and not c.get("issues") and not diverged and not failed_fixups
    return {"result": status, "strict_pass": False, "candidate_match": candidate_match, "issues": c.get("issues", []),
            "divergences": diverged, "failed_fixups": failed_fixups,
            "placements": c.get("placements", {}),
            "private_constraint_placements": c.get("private_constraint_placements", []),
            "literal_equal": c.get("literal_equal"), "literal_compared": c.get("literal_compared"),
            "fixups_equal": c.get("fixups_equal"), "fixups_total": c.get("fixups_total"),
            "candidate_fixups_equal": c.get("fixups_equal"), "candidate_fixups_total": c.get("fixups_total"),
            "contributions": [{"segment": x.get("segment"), "original_offset": x.get("original_offset"),
                               "length": x.get("length"), "divergences": len(x.get("divergences", [])),
                               "failed_fixups": sum(1 for f in x.get("fixups", []) if not f.get("equal"))}
                              for x in contributions]}


def _promote_verify(unit_spec: dict, members: list[str], source_path: Path,
                    candidate_result: dict, trial_name: str) -> dict:
    """Run the CLI's complete unit verifier using a short-lived generated spec.

    The unit.json is tool-generated, exists only while promote.py is running,
    and is removed in a finally block. The source and proof remain under build.
    """
    import uuid
    unit_id = "composer_" + uuid.uuid4().hex[:12]
    folder = UNITS / unit_id
    folder.mkdir(parents=True, exist_ok=False)
    temp_spec = dict(unit_spec)
    temp_spec.update(unit=unit_id, members=members, status="COMPOSED",
                     source=source_path.relative_to(ROOT).as_posix(), source_identity=identity(source_path),
                     last_test={"result": candidate_result.get("result"), "issues": candidate_result.get("issues", []),
                                "report": "build/workers/f-infra-composer/promote-verify/%s.json" % unit_id})
    try:
        write_json(folder / "unit.json", temp_spec)
        command = [sys.executable, str(ROOT / "tools/promote.py"), "--unit", unit_id,
                   "--reason", "bounded placement composer trial %s" % trial_name, "--verify-only"]
        proc = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=600)
        text = proc.stdout.strip() or proc.stderr.strip()
        result = None
        if proc.stdout.strip():
            try:
                result = json.loads(proc.stdout)
            except json.JSONDecodeError:
                result = None
        return {"command": "python tools/promote.py --unit %s --reason <composer trial> --verify-only" % unit_id,
                "exit_code": proc.returncode, "result": result, "output": text[-4000:],
                "strict_pass": proc.returncode == 0 and bool(result and result.get("admission") == "PASSED")}
    except subprocess.TimeoutExpired as exc:
        return {"exit_code": None, "strict_pass": False, "output": "promotion verification timed out: " + str(exc)}
    finally:
        shutil.rmtree(folder, ignore_errors=True)


def _static_size(item: Item) -> int | None:
    parsed = _literal_init(item)
    if parsed:
        try:
            value = ast.literal_eval(parsed[1])
            return len(value.encode("latin1")) + 1 if isinstance(value, str) else None
        except (SyntaxError, ValueError, UnicodeEncodeError):
            return None
    code = _tu().strip_comments(item.text).strip()
    scalar = re.fullmatch(r"static\s+(?:(?:near|far)\s+)?(char|unsigned\s+char|int|unsigned\s+int|short|unsigned\s+short|long|unsigned\s+long)\s+[A-Za-z_]\w*\s*=\s*.+;", code, re.S)
    if scalar:
        kind = scalar.group(1).replace("unsigned ", "")
        return 1 if kind == "char" else (4 if kind == "long" else 2)
    return None


def _target_private_start(spec: dict) -> tuple[str, int] | None:
    report = (spec.get("last_test") or {}).get("report")
    options = [ROOT / report] if report else []
    options.append(UNITS / spec.get("unit", "") / "test/results.json")
    for path in options:
        if not path.is_file():
            continue
        try:
            data = read_json(path)
            row = (data.get("results") or [{}])[0]
            comparison = row.get("comparison", {})
            for contribution in comparison.get("contributions", []):
                if contribution.get("segment") in ("_DATA", "_BSS"):
                    return contribution["segment"], int(contribution["original_offset"])
        except (FormatError, OSError, ValueError, KeyError, IndexError):
            continue
    return None


def _static_offsets(items: list[Item], start: int | None) -> dict[str, dict]:
    if start is None:
        return {}
    offset = start
    result = {}
    for item in items:
        if not _static_decl(item):
            continue
        size = _static_size(item)
        if size is None:
            continue
        for name in item.names:
            result[name] = {"offset": offset, "size": size, "declaration": " ".join(item.text.split())}
        offset += size
    return result


def _pool_placement_diagnosis(component: str | None, object_file: str | None) -> list[str]:
    if not component or not object_file:
        return []
    map_name = re.sub(r"[^A-Za-z0-9]+", "_", component) + ".json"
    map_path = ROOT / "evidence/experiments/pool-maps" / map_name
    object_path = ROOT / object_file
    if not map_path.is_file() or not object_path.is_file():
        return []
    try:
        import omf
        pool_map = read_json(map_path)
        module = omf.parse(object_path.read_bytes())
        const = next((s for s in module["segments"] if s.get("name") == "CONST"), None)
        if not const:
            return []
        fixups = [f for f in module["fixups"] if f.get("segment") == const["index"] and
                  f.get("target", {}).get("kind") == "external"]
        words = sorted(pool_map.get("words", []), key=lambda w: int(w["word"], 16))
        if not fixups or not words:
            return []
        expected = {int(w["word"], 16): w.get("symbol") for w in words}
        # Match candidate CONST words to the reviewed target map by their
        # external names. The best supported origin handles a leading string
        # literal or other non-selector bytes in CONST without assuming offset 0.
        origins = {}
        mapped_first = None
        for f in sorted(fixups, key=lambda row: row["offset"]):
            name = f["target"].get("name", "").lstrip("_")
            matches = [word for word, symbol in expected.items()
                       if symbol and symbol.lstrip("_") == name]
            if matches and mapped_first is None:
                mapped_first = (f["offset"], min(matches))
            for word, symbol in expected.items():
                if symbol and symbol.lstrip("_") == name:
                    origin = word - f["offset"]
                    origins[origin] = origins.get(origin, 0) + 1
        if not origins:
            return []
        origin = (mapped_first[1] - mapped_first[0] if mapped_first else
                  max(origins, key=lambda x: (origins[x], -x)))
        candidate_at = {f["offset"]: f["target"].get("name", "?") for f in fixups}
        notes = []
        for offset, actual in sorted(candidate_at.items()):
            slot = origin + offset
            wanted = expected.get(slot)
            actual_normal = actual.lstrip("_")
            wanted_normal = wanted.lstrip("_") if wanted else None
            if wanted_normal == actual_normal:
                continue
            if wanted:
                notes.append("CONST+0x%04X places %s at pool %04X; target wants %s there" %
                             (offset, actual, slot, wanted))
            else:
                notes.append("CONST+0x%04X places %s at pool %04X; target has no mapped selector there" %
                             (offset, actual, slot))
        candidate_offsets = set(candidate_at)
        first_candidate_offset = min(candidate_offsets)
        first_candidate_slot = origin + first_candidate_offset
        for slot, name in expected.items():
            offset = slot - origin
            if offset < first_candidate_offset:
                notes.append("candidate CONST selector stream starts at pool %04X with %s; target expects %s at earlier pool word %04X" %
                             (first_candidate_slot, candidate_at[first_candidate_offset],
                              name or "unresolved selector", slot))
                continue
            if offset in candidate_offsets:
                continue
            notes.append("candidate omits %s at target pool %04X (no CONST word at +0x%04X)" %
                         (name or "unresolved selector", slot, offset))
        return notes
    except (FormatError, OSError, ValueError, KeyError, TypeError):
        return []


def _placement_diagnosis(summary: dict, items: list[Item] | None = None,
                         target_offsets: dict[str, dict] | None = None,
                         data_segment: str | None = None,
                         component: str | None = None,
                         object_file: str | None = None) -> list[str]:
    out = []
    for c in summary.get("contributions", []):
        if c["divergences"] or c["failed_fixups"]:
            out.append("%s: candidate contribution length %s at target offset %s; %s byte divergences, %s failed fixups" %
                       (c.get("segment"), c.get("length"), c.get("original_offset"), c["divergences"], c["failed_fixups"]))
    placements = summary.get("placements", {})
    for index in summary.get("private_constraint_placements", []):
        value = placements.get(str(index))
        out.append("private segment %s: candidate placement %s; target offset is constrained by its member operands (see literal/static map below)" % (index, value))
    if items is not None and target_offsets:
        start = min(x["offset"] for x in target_offsets.values())
        candidate_offsets = _static_offsets(items, start)
        target_at = {v["offset"]: name for name, v in target_offsets.items()}
        candidate_at = {v["offset"]: name for name, v in candidate_offsets.items()}
        for name in sorted(set(target_offsets) | set(candidate_offsets)):
            target = target_offsets.get(name)
            candidate = candidate_offsets.get(name)
            if target and candidate and target["offset"] == candidate["offset"]:
                continue
            if candidate:
                target_name = target_at.get(candidate["offset"])
                wants = (target_name + " there" if target_name else
                         ("%s at %s+0x%04X" % (name, data_segment or "_DATA", target["offset"]) if target else "unclaimed bytes there"))
                out.append("%s sits at candidate %s+0x%04X; target wants %s" %
                           (name, data_segment or "_DATA", candidate["offset"], wants))
            elif target:
                out.append("%s is omitted from candidate static data; target wants it at %s+0x%04X (candidate has %s there)" %
                           (name, data_segment or "_DATA", target["offset"], candidate_at.get(target["offset"], "no named static")))
    out.extend(_pool_placement_diagnosis(component, object_file))
    if not out and not summary.get("strict_pass"):
        out.append("No private placement row was available; inspect the recorded comparison issues and compiler report.")
    return out


def _object_literals(items: list[Item], recovery: dict, members: list[str],
                     target_offsets: dict[str, dict] | None = None,
                     candidate_offsets: dict[str, dict] | None = None) -> list[dict]:
    """Describe declared private strings/statics and their original first-use anchors."""
    body = "\n".join(x.text for x in items if x.kind == "definition")
    rows = []
    for item in items:
        if not _static_decl(item):
            continue
        names = list(item.names)
        for name in names:
            parsed = _literal_init(item)
            uses = [m for m in members if re.search(r"\b" + re.escape(name) + r"\b", body)]
            rows.append({"name": name, "initializer": parsed[1] if parsed else None,
                         "target_offset": (target_offsets or {}).get(name, {}).get("offset"),
                         "candidate_offset": (candidate_offsets or {}).get(name, {}).get("offset"),
                         "size": _static_size(item), "members_using": uses,
                         "declaration": " ".join(item.text.split())})
    return rows


def _steering_constructs(items: list[Item], target_offsets: dict[str, dict],
                        candidate_offsets: dict[str, dict]) -> list[str]:
    """Name explicit code-free source shapes whose purpose is placement."""
    statics = [item for item in items if _static_decl(item)]
    notes = []
    for left, right in zip(statics, statics[1:]):
        left_code = _tu().strip_comments(left.text).strip()
        scalar = re.fullmatch(r"static\s+char\s+([A-Za-z_]\w*)\s*=\s*'((?:\\.|[^'\\])*)'\s*;", left_code, re.S)
        tail = _literal_init(right)
        if not scalar or not tail:
            continue
        left_name, first_char = scalar.groups()
        right_name, literal = tail
        try:
            decoded = ast.literal_eval("'" + first_char + "'") + ast.literal_eval(literal)
        except (SyntaxError, ValueError):
            continue
        left_pos = candidate_offsets.get(left_name, {}).get("offset")
        right_pos = candidate_offsets.get(right_name, {}).get("offset")
        if len(decoded) < 4 or left_pos is None or right_pos != left_pos + 1:
            continue
        target_left = target_offsets.get(left_name, {}).get("offset")
        target_right = target_offsets.get(right_name, {}).get("offset")
        if target_left is not None and target_right == target_left + 1:
            notes.append("Split label `%s` / `%s` is kept in adjacent bytes at 0x%04X/0x%04X to form `%s`; this declaration split exists to steer private-data placement." %
                         (left_name, right_name, left_pos, right_pos, decoded))
    return notes


def compose_object(component: str, additions: list[tuple[str, str]], *, max_arrangements: int = 12,
                   out_dir: str | None = None, naive: bool = False, persist: bool = False) -> dict:
    """Compose and test bounded placement variants for an object component."""
    if max_arrangements < 1 or max_arrangements > 64:
        raise FormatError("max_arrangements must be between 1 and 64")
    base_unit_id, spec, base_text, recovery = _latest_admitted_unit(component)
    members = list(spec.get("members", []))
    if not additions:
        raise FormatError("compose requires at least one --add SYMBOL=FILE.c")
    base_items = _itemize(base_text)
    all_targets = _all_target_records(recovery)
    private_start = _target_private_start(spec)
    data_segment, data_offset = private_start if private_start else (None, None)
    target_static_offsets = _static_offsets(base_items, data_offset)
    add_decl_items = []
    add_defs = []
    add_paths = {}
    for symbol, source in additions:
        if symbol not in all_targets:
            raise FormatError("no MAPSYM/context target record for " + symbol)
        path, text = _read_source(source)
        items = _itemize(text)
        definition = _definition(items, symbol)
        if symbol not in members:
            members.append(symbol)
        add_defs.append((symbol, definition))
        add_decl_items.extend(it for it in items if it.kind == "declaration")
        add_paths[symbol] = {"path": str(path), "identity": identity(path)}
    missing, declaration_conflicts = _dedupe_additions(base_items, add_decl_items)
    base_definitions = {"_" + item.name: item.text for item in base_items if item.kind == "definition" and item.name}
    seed_exact = (not naive and not missing and not declaration_conflicts and
                  all(base_definitions.get(symbol) == definition.text for symbol, definition in add_defs))
    # In the explicit naive seed, additions are deterministic and private
    # declarations start in lexical order. The bounded first-use/reverse trials
    # then have to recover any target ordering from the strict unit result.
    naive_decls = sorted(missing, key=lambda x: (tuple(x.names) or (), x.text)) if naive else missing
    seed_items = list(base_items)
    insertion = _first_function(seed_items)
    seed_items[insertion:insertion] = naive_decls
    for symbol, definition in add_defs:
        seed_items = _insert_definition(seed_items, definition, symbol, members, all_targets)
    # Ensure current unit member definitions that were not part of the addition
    # set remain in their original relative order; only insertion changed.
    if naive:
        seed_items = _placement_declarations(seed_items, "lexical-static")
    _refresh_scaffold(spec, seed_items)
    variants = _variants(seed_items, max_arrangements, all_targets)
    regenerated = _regenerated_scaffold(seed_items, component, members, spec, recovery, add_paths)
    if regenerated:
        scaffold_items, scaffold_notes = regenerated
        remaining = max(0, max_arrangements - len(variants))
        for name, candidate, notes in _variants(scaffold_items, max_arrangements, all_targets):
            rendered = _render(candidate)
            if any(_render(old_items) == rendered for _, old_items, _ in variants):
                continue
            if len(variants) >= max_arrangements:
                break
            trial_name = "poolmap-scaffold" if name == "seed" else "poolmap-" + name
            variants.append((trial_name, candidate, scaffold_notes + notes))
    if naive and variants:
        name, items, _ = variants[0]
        variants[0] = ("naive-seed", items,
                       ["Initialized static declarations begin in lexical name order; the search must recover any target order."])
    session = Path(out_dir) if out_dir else READY / (re.sub(r"[^A-Za-z0-9_-]+", "_", component) + "_compose")
    if not session.is_absolute():
        # "build/workers/NAME/..." is taken from the repository root; a bare name lands in the composer's own directory.
        session = ROOT / session if session.parts[:2] == ("build", "workers") else OUT_ROOT / session
    if not session.resolve().is_relative_to(WORKERS_ROOT.resolve()):
        raise FormatError("output must stay below build/workers")
    session.mkdir(parents=True, exist_ok=True)
    body_preflight = []
    for symbol, _ in add_defs:
        source_path = Path(add_paths[symbol]["path"])
        checked = _body_preflight(symbol, source_path, spec["flags"],
                                  session / "preflight" / symbol.lstrip("_"))
        body_preflight.append(checked)
        if not checked["body_exact"]:
            write_json(session / "preflight.json", {"object": component,
                                                     "body_preflight": body_preflight,
                                                     "refused": symbol,
                                                     "reason": "unit compose accepts only an exact body; remaining code/frame/register differences are not placement hypotheses"})
            raise FormatError("%s is not body-exact under the unit profile; see %s" %
                              (symbol, (session / "preflight.json").relative_to(ROOT).as_posix()))
    trials = []
    best = None
    for number, (name, items, notes) in enumerate(variants, 1):
        trial_dir = session / ("trial-%02d-%s" % (number, re.sub(r"[^A-Za-z0-9_-]+", "_", name)))
        trial_dir.mkdir(parents=True, exist_ok=True)
        source_path = trial_dir / "unit.c"
        source_text = base_text if seed_exact and name == "seed" else _render(items)
        source_path.write_text(source_text, encoding="latin1")
        from codegen_grinder import run
        report = run(dict(symbol=members[0], source=source_path.relative_to(ROOT).as_posix(), compiler="msc700",
                          flags=spec["flags"], max_candidates=1, axes=[],
                          semantic_summary="Bounded placement arrangement of admitted unit %s" % base_unit_id,
                          publics=members), (trial_dir / "test").relative_to(ROOT).as_posix(), cache=True)
        row = _result_row(report)
        summary = _strict_summary(row)
        if summary["candidate_match"]:
            verify_result = _promote_verify(spec, members, source_path, summary, name)
        else:
            verify_result = {"strict_pass": False, "skipped": True,
                             "reason": "candidate comparison did not reach an admissible member result"}
        summary["promote_verify"] = verify_result
        summary["strict_pass"] = bool(verify_result.get("strict_pass"))
        result_path = trial_dir / "test/results.json"
        trial = {"name": name, "source": source_path.relative_to(ROOT).as_posix(), "source_identity": identity(source_path),
                 "result_file": result_path.relative_to(ROOT).as_posix(), "notes": notes,
                 "strict": summary,
                  "placement_diagnosis": _placement_diagnosis(summary, items, target_static_offsets,
                                                                data_segment, component,
                                                                row.get("receipt", {}).get("object"))}
        trials.append(trial)
        if best is None or (summary["strict_pass"], summary["candidate_match"], -summary["divergences"], -summary["failed_fixups"], summary["literal_equal"] or 0) > best[0]:
            best = ((summary["strict_pass"], summary["candidate_match"], -summary["divergences"], -summary["failed_fixups"], summary["literal_equal"] or 0), trial, source_path, items)
    if best is None:
        raise FormatError("no distinct placement arrangements were generated")
    _, best_trial, best_path, best_items = best
    if best_trial["strict"].get("promote_verify", {}).get("skipped"):
        # One complete unit gate is attempted for the selected arrangement
        # even when the grinder's member comparator already found a residue.
        # promote.py is the authoritative pass/fail decision and will give its
        # own fail-closed reason for a non-exact unit.
        best_trial["strict"]["promote_verify"] = _promote_verify(
            spec, members, best_path, best_trial["strict"], best_trial["name"])
        best_trial["strict"]["strict_pass"] = bool(best_trial["strict"]["promote_verify"].get("strict_pass"))
    ready_path = session / "unit.c"
    ready_path.write_bytes(best_path.read_bytes())
    best_candidate_offsets = _static_offsets(best_items, data_offset)
    detected_steering = _steering_constructs(best_items, target_static_offsets, best_candidate_offsets)
    steering_notes = [n for n in best_trial["notes"] if "EXACT_STEERED" in n] + detected_steering
    steering = bool(steering_notes)
    provenance = {
        "object": component, "seed_unit": base_unit_id, "seed_source": spec.get("source"),
        "members": members, "added": add_paths, "arrangement": best_trial["name"],
        "unit_result": best_trial["strict"],
        "source_provenance": "EXACT_STEERED" if steering else "EXACT_NATURAL",
        "steering": steering_notes if steering else [],
        "body_preflight": body_preflight,
        "placement_items": _object_literals(best_items, all_targets, members, target_static_offsets,
                                             best_candidate_offsets),
        "declaration_conflicts_not_imported": [{"names": list(x.names), "text": x.text} for x in declaration_conflicts],
        "search_space": [t[0] for t in variants],
        "trials": trials,
        "scope": "Unit source is seeded from the latest admitted source; each added body passes an isolated body-exact preflight and claimed member definitions are never edited. Search changes only file-scope literal/static arrangement, existing POOLSTUB stand-ins/fillers, and definitions whose code offsets are unknown.",
    }
    (session / "provenance.json").write_text(json.dumps(provenance, indent=2, ensure_ascii=True) + "\n", encoding="utf-8")
    note = ["# Unit composer provenance", "", "- Object: `%s`" % component,
            "- Seed: `%s` (`%s`)" % (base_unit_id, spec.get("source")),
            "- Best arrangement: `%s`" % best_trial["name"],
            "- Unit result: `%s` (strict gate: %s)" % (best_trial["strict"]["result"], "PASS" if best_trial["strict"]["strict_pass"] else "FAIL"),
            "- Source provenance: `%s`" % provenance["source_provenance"],
            "- Candidate source: `unit.c`", "", "## Placement notes", ""]
    note.extend("- " + x for x in (steering_notes if steering else best_trial["notes"]) or ["No steering construct was needed."])
    note += ["", "## Arrangements", "", "| Arrangement | Unit result | Strict pass | Diagnostic |", "|---|---|---:|---|"]
    note += ["| %s | %s | %s | %s |" % (t["name"], t["strict"]["result"], "yes" if t["strict"]["strict_pass"] else "no", "; ".join(t["placement_diagnosis"]) or "—") for t in trials]
    if declaration_conflicts:
        note += ["", "## Declaration conflicts", ""]
        note.extend("- `%s`: %s" % (", ".join(x.names), " ".join(x.text.split())) for x in declaration_conflicts)
    (session / "provenance.md").write_text("\n".join(note) + "\n", encoding="utf-8")
    if persist:
        # Keep a strictly passing arrangement as a real unit record so promote.py --unit can
        # publish it. The id is derived from the component and the source hash, so it never
        # collides with another worker's diagnostic unit.
        if not best_trial["strict"].get("strict_pass"):
            raise FormatError("--persist needs a strictly passing arrangement; none passed")
        digest = hashlib.sha256(ready_path.read_bytes()).hexdigest()[:10]
        unit_id = "%s_compose_%s" % (re.sub(r"[^A-Za-z0-9]+", "_", component), digest)
        folder = UNITS / unit_id
        if folder.exists():
            raise FormatError("unit %s already exists" % unit_id)
        folder.mkdir(parents=True)
        (folder / "unit.c").write_bytes(ready_path.read_bytes())
        persisted = dict(spec)
        persisted.update(unit=unit_id, members=members, status="COMPOSED", layout="composed",
                         reason="unit composer arrangement %s extending %s" % (best_trial["name"], base_unit_id),
                         source=(folder / "unit.c").relative_to(ROOT).as_posix(),
                         source_identity=identity(folder / "unit.c"),
                         last_test={"result": best_trial["strict"].get("result"), "issues": best_trial["strict"].get("issues", []),
                                    "report": best_trial.get("result_file")})
        write_json(folder / "unit.json", persisted)
        provenance["persisted_unit"] = unit_id
        provenance["promote"] = ("python tools/promote.py --unit %s --reason \"...\"%s"
                                 % (unit_id, ' --steered "..."' if steering else ""))
    provenance["best_source"] = ready_path.relative_to(ROOT).as_posix()
    provenance["note"] = (session / "provenance.md").relative_to(ROOT).as_posix()
    write_json(session / "compose.json", provenance)
    return provenance


def parse_add(value: str) -> tuple[str, str]:
    if "=" not in value:
        raise argparse.ArgumentTypeError("expected SYMBOL=FILE.c")
    symbol, path = value.split("=", 1)
    if not symbol or not path:
        raise argparse.ArgumentTypeError("expected SYMBOL=FILE.c")
    return symbol, path


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("component", help="build-topology object component, e.g. simant:4C24")
    parser.add_argument("--add", action="append", type=parse_add, default=[], metavar="SYMBOL=FILE.c")
    parser.add_argument("--max-arrangements", type=int, default=12)
    parser.add_argument("--out", help="output directory below build/workers (a bare name goes to build/workers/f-infra-composer/NAME)")
    parser.add_argument("--naive", action="store_true", help="start with added declarations in deterministic name order")
    parser.add_argument("--persist", action="store_true", help="keep a strictly passing arrangement as evidence/recovery/units/<component>_compose_<hash> for promote.py --unit")
    args = parser.parse_args(argv)
    print(json.dumps(compose_object(args.component, args.add, max_arrangements=args.max_arrangements,
                                    out_dir=args.out, naive=args.naive, persist=args.persist), indent=2))


if __name__ == "__main__":
    try:
        main()
    except FormatError as exc:
        raise SystemExit("ERROR: " + str(exc))
