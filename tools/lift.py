#!/usr/bin/env python3
"""Deterministic first-draft lifter for MSC C/C++ 7.00 Win16 members.

    python tools/lift.py SYMBOL [SYMBOL ...] --out DIR
    python tools/lift.py --open --out DIR
    python tools/lift.py --controls [--limit N] --out DIR
    python tools/lift.py SYMBOL --refine --out DIR

The lifter consumes the same inspection packet as context.py. Its output is a
readable, compilable hypothesis; only search.py's complete-member comparison
can establish an exact result. In particular, NE relocation-chain words are
never used as C constants.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "toolchain" / "analysis"))

import analysis  # noqa: E402
import frame_map  # noqa: E402
import lift_frame  # noqa: E402
from common import FormatError, fixture, recipes, read_json  # noqa: E402
from context import cards, packet  # noqa: E402
import mapsym  # noqa: E402

try:  # Used to validate jump-table idioms against the repository's CFG solver.
    import cfg_solver  # noqa: E402
except Exception:  # pragma: no cover - packets still carry reviewed table rows
    cfg_solver = None


REG16 = {"ax", "bx", "cx", "dx", "si", "di", "bp", "sp"}
REG8 = {"al", "ah", "bl", "bh", "cl", "ch", "dl", "dh"}
ROOT_REG = {"al": "ax", "ah": "ax", "bl": "bx", "bh": "bx",
            "cl": "cx", "ch": "cx", "dl": "dx", "dh": "dx"}
JCC = {"je", "jz", "jne", "jnz", "jl", "jnge", "jle", "jng", "jg", "jnle",
       "jge", "jnl", "jb", "jc", "jnae", "jbe", "jna", "ja", "jnbe", "jae",
       "jnb", "jnc", "js", "jns", "jo", "jno", "jp", "jpe", "jnp", "jpo"}
COMMUTATIVE = {"+", "*", "&", "|", "^", "==", "!="}
BINOP = {"add": "+", "adc": "+", "sub": "-", "sbb": "-", "and": "&", "or": "|", "xor": "^",
         "imul": "*", "mul": "*", "shl": "<<", "sal": "<<", "shr": ">>", "sar": ">>"}
COND = {
    "je": "==", "jz": "==", "jne": "!=", "jnz": "!=",
    "jl": "<", "jnge": "<", "jge": ">=", "jnl": ">=",
    "jle": "<=", "jng": "<=", "jg": ">", "jnle": ">",
    "jb": "<", "jc": "<", "jnae": "<", "jae": ">=", "jnb": ">=", "jnc": ">=",
    "jbe": "<=", "jna": "<=", "ja": ">", "jnbe": ">",
}


def c_name(symbol: str) -> str:
    """Map a MAPSYM public to the C spelling used by MSC's leading underscore."""
    return symbol[1:] if symbol.startswith("_") else symbol


def _hex_int(text: str) -> int:
    return int(text, 0)


@dataclass
class Ins:
    offset: int
    size: int
    mnemonic: str
    op_str: str
    raw: Any
    row: dict[str, Any]

    @property
    def operands(self):
        return self.raw.operands if self.raw is not None else ()

    def reg(self, index: int) -> str:
        return self.raw.reg_name(self.operands[index].reg) if self.raw is not None else ""


@dataclass
class Expr:
    text: str
    width: int = 2
    signed: bool = False
    op: str | None = None
    left: "Expr | None" = None
    right: "Expr | None" = None
    swapped: bool = False

    def render(self) -> str:
        if self.op and self.left and self.right:
            a, b = self.left, self.right
            if self.swapped:
                a, b = b, a
            return f"({a.render()} {self.op} {b.render()})"
        return self.text

    def swaps(self):
        if self.left:
            yield from self.left.swaps()
        if self.right:
            yield from self.right.swaps()
        if self.op in COMMUTATIVE:
            yield self


@dataclass
class FrameSlot:
    displacement: int
    width: int
    type_name: str
    name: str


@dataclass
class Function:
    symbol: str
    packet: dict[str, Any]
    code: bytes
    instructions: list[Ins]
    tables: list[dict[str, Any]] = field(default_factory=list)
    params: list[dict[str, Any]] = field(default_factory=list)
    locals: list[FrameSlot] = field(default_factory=list)
    externs: list[str] = field(default_factory=list)
    globals: dict[str, dict[str, Any]] = field(default_factory=dict)
    unsupported: Counter = field(default_factory=Counter)
    return_type: str = "void"
    far: bool = True
    pascal: bool = False
    frame_size: int = 0
    commutative_nodes: list[Expr] = field(default_factory=list)


class SourceDeclarations:
    """Declaration-only index of public names already used by admitted C sources."""
    def __init__(self):
        self.functions: dict[str, str] = {}
        self.variables: dict[str, str] = {}
        self.structs: dict[str, str] = {}
        self._load()

    def _add(self, statement: str):
        s = " ".join(statement.strip().split())
        if not s.startswith("extern ") or "{" in s or "}" in s:
            return
        fn = re.match(r"extern\s+(.+?\b([A-Za-z_]\w*)\s*\([^;]*\))\s*;?$", s)
        if fn:
            self.functions.setdefault(fn.group(2), s.rstrip(";") + ";")
            return
        # Preserve exact extern spelling for admitted globals, including far/near.
        for name in re.findall(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?=,|;|\[)", s):
            if name not in {"extern", "unsigned", "signed", "char", "short", "int", "long", "far", "near", "const", "volatile"}:
                self.variables.setdefault(name, s.rstrip(";") + ";")

    def _load(self):
        for path in sorted((ROOT / "src").rglob("*.c")):
            try:
                text = path.read_text(encoding="latin1", errors="replace")
            except OSError:
                continue
            # The declaration index deliberately takes only standalone extern
            # statements; it never parses or reuses a function body.
            text = re.sub(r"/\*.*?\*/|//[^\r\n]*", " ", text, flags=re.S)
            # Struct tags are type declarations, not recovered function bodies.
            # Retain the first complete layout needed by standalone drafts.
            for match in re.finditer(r"\bstruct\s+([A-Za-z_]\w*)\s*\{([^{}]*)\}\s*;", text, re.S):
                tag = match.group(1)
                body = " ".join(match.group(2).split())
                self.structs.setdefault(tag, f"struct {tag} {{ {body} }};")
            for m in re.finditer(r"(?m)^\s*extern\s+[^;{}\r\n]+;", text):
                self._add(m.group(0))


DECLS = SourceDeclarations()
try:
    _sym_packet = mapsym.parse(fixture("SIMANTW.SYM"))
    MAPSYM_BY_CNAME: dict[str, list[dict[str, Any]]] = defaultdict(list)
    MAPSYM_BY_SEGMENT: dict[int, list[dict[str, Any]]] = defaultdict(list)
    for _seg in _sym_packet.get("segments", []):
        for _sym in _seg.get("symbols", []):
            _item = {"segment": _seg["number"], "offset": _sym["offset"], "name": _sym["name"]}
            MAPSYM_BY_CNAME[c_name(_sym["name"])].append(_item)
            MAPSYM_BY_SEGMENT[_seg["number"]].append(_item)
except Exception:  # pragma: no cover - source names degrade to neutral placeholders
    MAPSYM_BY_CNAME = defaultdict(list)
    MAPSYM_BY_SEGMENT = defaultdict(list)


def recognize_prologue(instructions: list[Ins]) -> dict[str, Any]:
    """Recognize the measured MSC BP frame and Windows far-export shells."""
    m = [x.mnemonic for x in instructions[:8]]
    ops = [x.op_str.lower().replace(" ", "") for x in instructions[:8]]
    result = {"kind": "none", "body_start": 0, "saved": [], "frame_size": 0}
    if len(m) >= 2 and m[:2] == ["push", "mov"] and ops[0] == "bp" and ops[1] == "bp,sp":
        result.update(kind="bp", body_start=2)
        j = 2
        while j < len(instructions) and instructions[j].mnemonic == "push" and instructions[j].op_str in ("si", "di"):
            result["saved"].append(instructions[j].op_str)
            j += 1
        result["body_start"] = j
    elif instructions and instructions[0].mnemonic == "enter":
        if instructions[0].operands:
            n = instructions[0].operands[0].imm
        else:
            n = int(instructions[0].op_str.split(",", 1)[0], 0) if instructions[0].op_str else 0
        result.update(kind="enter", body_start=1, frame_size=max(0, n))
        j = 1
        while j < len(instructions) and instructions[j].mnemonic == "push" and instructions[j].op_str in ("si", "di"):
            result["saved"].append(instructions[j].op_str)
            j += 1
        result["body_start"] = j
    elif len(m) >= 2 and m[:2] == ["inc", "push"] and ops[:2] == ["bp", "ds"]:
        result.update(kind="windows_far_export", body_start=2)
    return result


def recognize_far_return(instructions: list[Ins]) -> tuple[bool, bool, int]:
    """Return (far, pascal-pop, argument-byte-count) from RET/RETF forms."""
    returns = [i for i in instructions if i.mnemonic in ("ret", "retf", "retn")]
    if not returns:
        return True, False, 0
    far = any(i.mnemonic == "retf" for i in returns)
    pops = []
    for i in returns:
        if len(i.operands) and i.operands[0].type == analysis.cs.x86.X86_OP_IMM:
            pops.append(i.operands[0].imm)
        elif i.op_str:
            try:
                pops.append(_hex_int(i.op_str))
            except ValueError:
                pass
    amount = max(pops, default=0)
    return far, bool(amount), amount


def recognize_long_helper(name: str) -> str | None:
    """Classify MSC's 32-bit arithmetic helper family by its packet name."""
    n = name.lower().replace("_", "")
    if "flmul" in n or "fulmul" in n:
        return "mul"
    if "fldiv" in n or "flmod" in n or "fuldiv" in n or "fulmod" in n:
        return "div"
    if "flshl" in n or "fulshl" in n:
        return "shl"
    if "flshr" in n or "flsar" in n or "fulshr" in n or "fulsar" in n:
        return "shr"
    return None


def condition_text(mnemonic: str, left: str, right: str = "0", width: int = 2,
                   signed: bool = False) -> str | None:
    """Translate the common 8086 conditional branches to C flag predicates."""
    m = mnemonic.lower()
    if m in ("jcxz", "jecxz"):
        return "cx == 0"
    if m not in COND:
        if m in ("js",):
            return f"(({signed_c_type(width)})({left}) < 0)"
        if m == "jns":
            return f"(({signed_c_type(width)})({left}) >= 0)"
        return None
    op = COND[m]
    if op in ("<", "<=", ">", ">="):
        ty = signed_c_type(width) if signed or m in {"jl", "jnge", "jle", "jng", "jg", "jnle", "jge", "jnl"} else unsigned_c_type(width)
        return f"(({ty})({left}) {op} ({ty})({right}))"
    return f"(({left}) {op} ({right}))"


def signed_c_type(width: int) -> str:
    return {1: "signed char", 2: "int", 4: "long"}.get(width, "int")


def unsigned_c_type(width: int) -> str:
    return {1: "unsigned char", 2: "unsigned int", 4: "unsigned long"}.get(width, "unsigned int")


class Structurer:
    """Conservative label folder for single-entry ifs and simple loop shells.

    Shared tails and multi-entry regions stay as gotos. This intentionally
    follows the packet's branch graph instead of guessing structure from names.
    """
    LABEL = re.compile(r"^(L_[0-9a-fA-F]+):\s*;$")
    COND = re.compile(r"^if \((.*)\) goto (L_[0-9a-fA-F]+);$")
    GOTO = re.compile(r"^goto (L_[0-9a-fA-F]+);$")

    def __init__(self, condition_flip: bool = False, loop_style: str = "canonical"):
        if loop_style not in {"canonical", "while", "for", "forever"}:
            raise ValueError(f"unknown loop style: {loop_style}")
        self.condition_flip = condition_flip
        self.loop_style = loop_style

    @classmethod
    def _refs(cls, lines: list[str]) -> Counter:
        refs = Counter()
        for line in lines:
            for target in re.findall(r"\bgoto\s+(L_[0-9a-fA-F]+)", line):
                refs[target] += 1
        return refs

    @classmethod
    def _is_label(cls, line: str) -> str | None:
        match = cls.LABEL.match(line.strip())
        return match.group(1) if match else None

    @classmethod
    def _safe_body(cls, lines: list[str]) -> bool:
        return all(not cls._is_label(x) and "goto " not in x for x in lines)

    def run(self, input_lines: list[str]) -> list[str]:
        lines = [x.strip() for x in input_lines]
        # A top-tested loop has one exit edge, a straight-line body, and one
        # back edge. The branch and fall-through roles come directly from the
        # CFG; any internal/shared label keeps the original goto form.
        changed = True
        while changed:
            changed = False
            refs = self._refs(lines)
            labels = {name: i for i, line in enumerate(lines) if (name := self._is_label(line))}
            # Forward branch to an else arm followed by an unconditional jump
            # to the join. Fold only single-entry, label-free arm bodies.
            for i, line in enumerate(lines):
                branch = self.COND.match(line)
                if not branch:
                    continue
                else_label = branch.group(2)
                else_i = labels.get(else_label)
                if else_i is None or else_i <= i + 2 or lines[else_i - 1] == f"goto {else_label};":
                    continue
                if else_i < 1 or not self.GOTO.match(lines[else_i - 1]):
                    continue
                end_label = self.GOTO.match(lines[else_i - 1]).group(1)
                end_i = labels.get(end_label)
                if end_i is None or end_i <= else_i or refs[else_label] != 1 or refs[end_label] != 1:
                    continue
                then_body = lines[i + 1:else_i - 1]
                else_body = lines[else_i + 1:end_i]
                if not self._safe_body(then_body) or not self._safe_body(else_body):
                    continue
                if self.condition_flip:
                    lines[i:end_i + 1] = [f"if ({branch.group(1)}) {{",
                                          *["    " + x for x in else_body], "} else {",
                                          *["    " + x for x in then_body], "}"]
                else:
                    lines[i:end_i + 1] = [f"if (!({branch.group(1)})) {{",
                                          *["    " + x for x in then_body], "} else {",
                                          *["    " + x for x in else_body], "}"]
                changed = True
                break
            if changed:
                continue
            for top, top_i in sorted(labels.items(), key=lambda row: row[1]):
                if top_i + 2 >= len(lines):
                    continue
                branch = self.COND.match(lines[top_i + 1])
                if not branch:
                    continue
                exit_label = branch.group(2)
                exit_i = labels.get(exit_label)
                if exit_i is None or exit_i <= top_i + 2 or lines[exit_i - 1] != f"goto {top};":
                    continue
                body = lines[top_i + 2:exit_i - 1]
                if not self._safe_body(body) or refs[top] != 1:
                    continue
                step = None
                if body:
                    candidate_step = body[-1].strip()
                    if re.fullmatch(r"[A-Za-z_]\w*\s*(?:\+\+|--)", candidate_step.rstrip(";")) or re.fullmatch(
                            r"[A-Za-z_]\w*\s*=.*", candidate_step.rstrip(";")):
                        step = candidate_step.rstrip(";")
                if self.loop_style == "forever":
                    lines[top_i:exit_i + 1] = ["for (;;) {", f"    if ({branch.group(1)}) break;",
                                               *["    " + x for x in body], "}"]
                elif step is not None and self.loop_style in ("canonical", "for"):
                    loop_body = body[:-1]
                    lines[top_i:exit_i + 1] = [f"for (; !({branch.group(1)}); {step}) {{",
                                               *["    " + x for x in loop_body], "}"]
                elif step is not None:
                    loop_body = body[:-1]
                    lines[top_i:exit_i + 1] = [f"while (!({branch.group(1)})) {{",
                                               *["    " + x for x in loop_body], "    " + step + ";", "}"]
                elif self.loop_style == "for":
                    lines[top_i:exit_i + 1] = [f"for (; !({branch.group(1)}); ) {{",
                                               *["    " + x for x in body], "}"]
                else:
                    lines[top_i:exit_i + 1] = [f"while (!({branch.group(1)})) {{", *["    " + x for x in body], "}"]
                changed = True
                break
            if changed:
                continue
            # A conditional back edge is a do/while shell.
            refs = self._refs(lines)
            labels = {name: i for i, line in enumerate(lines) if (name := self._is_label(line))}
            for i, line in enumerate(lines):
                branch = self.COND.match(line)
                if not branch:
                    continue
                target_i = labels.get(branch.group(2))
                if target_i is None or target_i >= i or refs[branch.group(2)] != 1:
                    continue
                body = lines[target_i + 1:i]
                if not self._safe_body(body):
                    continue
                if self.loop_style == "forever":
                    lines[target_i:i + 1] = ["for (;;) {", *["    " + x for x in body],
                                             f"    if (!({branch.group(1)})) break;", "}"]
                elif self.loop_style == "while":
                    lines[target_i:i + 1] = ["while (1) {", *["    " + x for x in body],
                                             f"    if (!({branch.group(1)})) break;", "}"]
                else:
                    lines[target_i:i + 1] = ["do {", *["    " + x for x in body], f"}} while ({branch.group(1)});"]
                changed = True
                break
            if changed:
                continue
            # Fold a one-entry forward conditional skip into a structured if.
            refs = self._refs(lines)
            labels = {name: i for i, line in enumerate(lines) if (name := self._is_label(line))}
            for i, line in enumerate(lines):
                branch = self.COND.match(line)
                if not branch:
                    continue
                target_i = labels.get(branch.group(2))
                if target_i is None or target_i <= i + 1 or refs[branch.group(2)] != 1:
                    continue
                body = lines[i + 1:target_i]
                if not self._safe_body(body):
                    continue
                if self.condition_flip:
                    lines[i:target_i + 1] = [f"if ({branch.group(1)}) {{", "} else {",
                                             *["    " + x for x in body], "}"]
                else:
                    lines[i:target_i + 1] = [f"if (!({branch.group(1)})) {{", *["    " + x for x in body], "}"]
                changed = True
                break
        return lines


def _instruction_rows(pkt: dict[str, Any]) -> tuple[bytes, list[Ins]]:
    raw = bytes.fromhex(pkt["target_bytes_hex"])
    decoder = analysis.decoder()
    out: list[Ins] = []
    for row in pkt.get("disassembly", []):
        if row.get("mnemonic") == "dw":
            out.append(Ins(int(row["offset"]), len(bytes.fromhex(row["bytes"])), "dw", row.get("operands", ""), None, row))
            continue
        off = int(row["offset"])
        n = len(row.get("bytes", "").split())
        decoded = next(decoder.disasm(raw[off:off + n], off, count=1), None)
        if decoded is None:
            continue
        out.append(Ins(off, decoded.size, decoded.mnemonic.lower(), decoded.op_str, decoded, row))
    out.sort(key=lambda i: i.offset)
    return raw, out


def _candidate_switch_tables(pkt: dict[str, Any], insns: list[Ins]) -> list[dict[str, Any]]:
    """Use cfg_solver.switch_table when the original packet has table bytes."""
    rows = {i.offset: i for i in insns if i.raw is not None}
    data = [i for i in insns if i.mnemonic == "dw"]
    tables = []
    start = int(pkt.get("offset", 0))
    extent = pkt.get("extent") or {}
    limit = start + int(extent.get("size") or len(bytes.fromhex(pkt.get("target_bytes_hex", ""))))
    if cfg_solver is None or not data:
        return tables
    try:
        import common, ne
        raw_exe = common.fixture("SIMANTW.EXE")
        image = ne.parse(raw_exe)
        segno = int(extent.get("segment") or pkt.get("code_segment_number") or 0)
        if not segno:
            segno = int(pkt.get("code_segment_number", 0))
        seg = image["segments"][segno - 1]
        code = raw_exe[seg["file_offset"]:seg["file_offset"] + seg["logical_size"]]
        relbytes = {p for r in pkt.get("relocations", []) for q in r.get("sites", [])
                    for p in range(int(q), int(q) + int(r.get("width", 2)))}
        seen = {start + i.offset: i.raw for i in rows.values()}
        chain = {}
        prev = None
        for i in sorted(rows.values(), key=lambda x: x.offset):
            here = start + i.offset
            if prev is not None and prev.address + prev.size == here:
                chain[here] = prev.address
            prev = i.raw
        for i in rows.values():
            if i.mnemonic != "jmp" or not i.operands or i.operands[0].type != analysis.cs.x86.X86_OP_MEM:
                continue
            table = cfg_solver.switch_table(i.raw, chain, seen, code, start, limit, relbytes)
            if table:
                tables.append(table)
    except Exception:
        # The packet's reviewed `dw` rows remain a conservative fallback.
        pass
    return tables


def _all_pool_words(component: str | None) -> dict[int, dict[str, Any]]:
    if not component or ":" not in component:
        return {}
    a, b = component.split(":", 1)
    path = ROOT / "evidence" / "experiments" / "pool-maps" / f"{a.lower()}_{b.upper()}.json"
    if not path.exists():
        return {}
    try:
        data = read_json(path)
    except Exception:
        return {}
    result = {}
    for row in data.get("words", []):
        conf = row.get("confidence")
        if conf not in ("HIGH", "MEDIUM") or not row.get("symbol"):
            continue
        try:
            off = int(row["word"], 0)
        except Exception:
            continue
        result[off] = row
    return result


def _parse_decl_signature(decl: str) -> dict[str, Any] | None:
    s = " ".join(decl.strip().rstrip(";").split())
    m = re.match(r"(?:extern\s+)?(?P<ret>.+?)\s+(?P<name>[A-Za-z_]\w*)\s*\((?P<args>.*)\)$", s)
    if not m:
        return None
    args = m.group("args").strip()
    params = [] if not args or args == "void" else [x.strip() for x in args.split(",")]
    return {"name": m.group("name"), "ret": m.group("ret"), "params": params,
            "far": bool(re.search(r"\bfar\b", m.group("ret"))),
            "pascal": bool(re.search(r"\bpascal\b", m.group("ret"))),
            "void": bool(re.search(r"\bvoid\b", m.group("ret")))}


def _param_bytes(param: str) -> int:
    p = param.lower()
    if "far" in p and "*" in p:
        return 4
    if "*" in p and "near" in p:
        return 2
    if "long" in p or "far" in p:
        return 4
    return 2


def _type_from_access(width: int, signed: bool, farptr: bool = False) -> str:
    if farptr:
        return "void far *"
    if width >= 4:
        return "long" if signed else "unsigned long"
    if width == 1:
        return "signed char" if signed else "unsigned char"
    return "int" if signed else "unsigned int"


def _memory_slots(insns: list[Ins], pkt: dict[str, Any]) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    params: dict[int, dict[str, Any]] = {}
    locals_: dict[int, dict[str, Any]] = {}
    for ins in insns:
        if ins.raw is None:
            continue
        for op in ins.operands:
            if op.type != analysis.cs.x86.X86_OP_MEM:
                continue
            mem = op.mem
            if ins.raw.reg_name(mem.base) != "bp":
                continue
            d = int(mem.disp)
            if d == 0:
                continue
            farptr = ins.mnemonic in ("les", "lds") and op.size == 4
            width = max(int(op.size), 1)
            if d > 0:
                cur = params.setdefault(d, {"offset": d, "width": width, "farptr": farptr, "signed": False})
            else:
                cur = locals_.setdefault(d, {"offset": d, "width": width, "farptr": farptr, "signed": False})
            cur["width"] = max(cur["width"], width)
            cur["farptr"] = cur["farptr"] or farptr
            if ins.mnemonic in ("movsx", "cbw"):
                cur["signed"] = True
    # Caller-side context, where present, supplies exact prototype facts.
    source = SourceDeclarations()
    local_max = max([abs(x) for x in locals_] or [0])
    params_out = []
    far, pascal, pop_bytes = recognize_far_return(insns)
    base = 6 if far else 4
    # Keep every directly observed argument start; do not synthesize hidden args.
    for off in sorted(k for k in params if k >= base):
        row = params[off]
        typ = _type_from_access(row["width"], row["signed"], row["farptr"])
        params_out.append({"offset": off, "name": f"arg_{off:x}", "type": typ,
                           "width": max(2, _param_bytes(typ)), "farptr": row["farptr"]})
    # A callee-pop count can expose trailing params not directly read; use word
    # placeholders only when no observed slot explains those bytes.
    known_bytes = sum(p["width"] for p in params_out)
    while pascal and known_bytes < pop_bytes:
        off = base + known_bytes
        params_out.append({"offset": off, "name": f"arg_{off:x}", "type": "int", "width": 2, "farptr": False})
        known_bytes += 2
    return params_out, list(locals_.values())


class Lifter:
    def __init__(self, symbol: str, pkt: dict[str, Any] | None = None):
        self.symbol = symbol
        self.packet = pkt or packet(symbol)
        if self.packet.get("state") != "OPEN" and self.packet.get("state") not in ("MATCHED", "GAME"):
            raise FormatError(f"{symbol}: packet is not a GAME function")
        code, instructions = _instruction_rows(self.packet)
        self.f = Function(symbol, self.packet, code, instructions)
        self.f.tables = _candidate_switch_tables(self.packet, instructions)
        self.prologue = recognize_prologue(instructions)
        self.f.far, self.f.pascal, pop = recognize_far_return(instructions)
        self.f.frame_size = self.prologue["frame_size"]
        if not self.f.frame_size:
            em = next((i for i in instructions if i.mnemonic == "enter" and i.operands), None)
            if em:
                self.f.frame_size = int(em.operands[0].imm)
        self.f.params, local_accesses = _memory_slots(instructions, self.packet)
        self._frame_slots(local_accesses)
        self._infer_return()
        self.pool_words = _all_pool_words((self.packet.get("unit_context") or {}).get("id"))
        self.es_object: str | None = None
        self.es_offset: int | None = None
        self.pushes: list[dict[str, Any]] = []
        self.flag: tuple[str, str, int, bool] = ("__lift_flag", "0", 2, False)
        self.calls: dict[str, str] = {}
        self._swap_at: int | None = None
        self.carry_needed = any(i.mnemonic in ("adc", "sbb") for i in instructions)
        self._known_prototypes()
        self._bindings_by_instruction = {int(x.get("instruction", -1)): x for x in self.packet.get("direct_data_bindings", [])}
        self._global_decls: dict[str, str] = {}
        self._unknown_globals: dict[tuple[str, int], str] = {}
        self._line_for_offset: dict[int, list[str]] = defaultdict(list)

    def _frame_slots(self, accesses: list[dict[str, Any]]):
        by_disp = {int(x["offset"]): x for x in accesses}
        for disp in sorted(by_disp, key=abs):
            row = by_disp[disp]
            width = 4 if row.get("farptr") else row.get("width", 2)
            typ = _type_from_access(width, bool(row.get("signed")), bool(row.get("farptr")))
            self.f.locals.append(FrameSlot(disp, width, typ, f"v_bp_m{abs(disp):x}"))
        # Use frame_map's target pass and preserve every observed slot. The
        # frame-model evidence says declaration order is the best global prior;
        # slots closest to BP are declared first, with char packing explicit.
        enter, slots = frame_map.target_frame(self.packet.get("disassembly", []))
        self.f.frame_size = max(self.f.frame_size, enter or 0,
                                max([abs(s.displacement) for s in self.f.locals] or [0]))

    def _infer_return(self):
        # Return-value inference is intentionally conservative. A value written
        # to AX in the return tail is evidence; calls alone are not.
        returns = [i for i, x in enumerate(self.f.instructions) if x.mnemonic in ("ret", "retf", "retn")]
        if not returns:
            return
        evidence = False
        wide = False
        for r in returns:
            start = r
            while start > 0 and r - start < 12 and self.f.instructions[start - 1].mnemonic not in (*JCC, "jmp", "ret", "retf", "retn"):
                start -= 1
            prior = self.f.instructions[start:r]
            wrote_ax = False
            wrote_dx = False
            for i in prior:
                if i.mnemonic in ("mov", "xor", "or", "and", "add", "sub", "inc", "dec", "neg", "imul") and i.operands:
                    dst = i.operands[0]
                    if dst.type == analysis.cs.x86.X86_OP_REG and i.raw.reg_name(dst.reg) in ("ax", "al", "ah"):
                        evidence = True
                        wrote_ax = True
                    if dst.type == analysis.cs.x86.X86_OP_REG and i.raw.reg_name(dst.reg) == "dx":
                        wrote_dx = True
                if i.mnemonic in ("mul", "imul", "div", "idiv"):
                    evidence = True
                    wide = True
                if i.mnemonic in ("call", "lcall", "callf"):
                    callee = self._call_name(i) or ""
                    if callee.lower().startswith("__afl"):
                        evidence = True
                        wide = True
            # A DX write from an argument/setup path does not make the return
            # wide. Require both halves to be produced in this return tail.
            if wrote_ax and wrote_dx:
                wide = True
        if evidence:
            self.f.return_type = "unsigned long" if wide else "int"

    def _known_prototypes(self):
        decls = []
        for row in self.packet.get("referenced_declarations", []):
            decls.append(row.get("declaration", ""))
        # Declaration index is only extern statements, never admitted bodies.
        decls.extend(DECLS.functions.values())
        byname = {}
        for decl in decls:
            info = _parse_decl_signature(decl)
            if info:
                byname[info["name"]] = (decl.rstrip(";") + ";", info)
        for ins in self.f.instructions:
            if ins.mnemonic in ("call", "lcall", "callf"):
                cname = self._call_name(ins)
                if not cname:
                    continue
                got = byname.get(cname)
                if not got:
                    got = next((entry for n, entry in byname.items() if n.upper() == cname.upper()), None)
                if got:
                    declaration, info = got
                    # The declaration-only index does not yet import typedefs.
                    # Do not emit a prototype whose return/parameter type name
                    # is absent from the packet's struct and scalar vocabulary.
                    type_words = {"void", "char", "short", "int", "long", "unsigned", "signed",
                                  "far", "near", "pascal", "const", "volatile", "struct"}
                    names = set(re.findall(r"\b[A-Za-z_]\w*\b", declaration)) - type_words
                    known = set(DECLS.structs) | {info["name"]}
                    unknown_type = any(n[:1].isupper() and n not in known and n != cname for n in names)
                    self.calls[cname] = self._generic_prototype(cname, ins) if unknown_type else declaration
                elif cname not in self.calls:
                    self.calls[cname] = self._generic_prototype(cname, ins)

    def _generic_prototype(self, name: str, ins: Ins) -> str:
        # The packet's push stream is the reliable argument-count evidence only
        # when it is local to the call; an unprototyped C declaration avoids
        # inventing parameter semantics and remains accepted by MSC 7.00.
        helper = recognize_long_helper(name)
        if helper:
            unsigned = "u" in name.lower().replace("_", "")
            word = "unsigned int" if unsigned else "int"
            long = "unsigned long" if unsigned else "long"
            if helper in ("mul", "div"):
                return f"extern {long} far {name}({long}, {long});"
            return f"extern {long} far {name}({long}, {word});"
        return f"extern unsigned int far {name}();"

    def _slot_for(self, displacement: int) -> FrameSlot | None:
        exact = next((s for s in self.f.locals if s.displacement == displacement), None)
        if exact:
            return exact
        for p in self.f.params:
            if p["offset"] == displacement:
                return FrameSlot(displacement, p["width"], p["type"], p["name"])
        return None

    def _name_for_mem(self, ins: Ins, mem, width: int) -> tuple[str, str | None]:
        base = ins.raw.reg_name(mem.base) if mem.base else ""
        index = ins.raw.reg_name(mem.index) if mem.index else ""
        seg = ins.raw.reg_name(mem.segment) if mem.segment else ""
        disp = int(mem.disp)
        if base == "bp":
            slot = self._slot_for(disp)
            if slot:
                return slot.name, None
            if disp > 0:
                # Address-taken/aggregate parameters can be accessed inside a
                # four-byte span even when the instruction starts at +2.
                containing = next((p for p in self.f.params if p["offset"] <= disp < p["offset"] + p["width"]), None)
                if containing:
                    return containing["name"], None
            missing = f"__lift_bp_{'p' if disp > 0 else 'm'}{abs(disp):x}"
            return missing, f"extern unsigned char {missing};"
        if not base and not index:
            absolute = disp & 0xffff
            cname = self._resolved_memory_name(ins, seg, absolute)
            if cname:
                segno = 9 if seg == "es" else 10
                return self._global_lvalue(cname, absolute, width, seg == "es",
                                           self._mapsym_offset(cname, segno)), None
            key = (seg or "ds", absolute)
            name = self._unknown_globals.get(key)
            if not name:
                name = f"__lift_{'far' if seg == 'es' else 'dgroup'}_{absolute:04x}"
                self._unknown_globals[key] = name
            far = seg == "es"
            decl = f"extern unsigned char {'far ' if far else ''}{name}[];"
            self._global_decls[name] = decl
            if far and self.es_object:
                return self._global_lvalue(self.es_object, absolute, width, True, self.es_offset), None
            return self._global_lvalue(name, absolute, width, far), None
        if seg == "es" and self.es_object:
            return self._based_lvalue(self.es_object, self.es_offset, base, index, disp, width, True), None
        # Register-indirect ordinary pointers are kept typed and symbolic. This
        # is a C dereference, not a fixed-address cast.
        expr = self._address_expr(base, index, disp)
        ptrty = "far " if seg == "es" else "near "
        return f"(*(({unsigned_c_type(width)} {ptrty}*)({expr})))", None

    def _resolved_memory_name(self, ins: Ins, seg: str, absolute: int) -> str | None:
        names = []
        for ref in ins.row.get("references", []):
            if ref.get("kind") in ("global_ds_assumed", "global"):
                names.extend(ref.get("names", []))
        bind = self._bindings_by_instruction.get(int(self.packet.get("offset", 0)) + ins.offset)
        if bind:
            names.extend(bind.get("exact_mapsym_names", []))
            if bind.get("ds_state") == "ASSUMED_DGROUP":
                names.extend(bind.get("possible_dgroup_names", []))
        if seg == "es":
            selector = self.es_object
            if selector:
                return selector
            # Some exact packet bindings identify an ES operand directly.
            if bind:
                names.extend(bind.get("exact_mapsym_names", []))
        if names:
            return c_name(names[0])
        # A reviewed pool map may resolve this selector to a named far object.
        if seg == "es":
            return self.es_object
        return None

    @staticmethod
    def _mapsym_offset(name: str, segment: int | None = None) -> int | None:
        rows = MAPSYM_BY_CNAME.get(name, [])
        if segment is not None:
            rows = [r for r in rows if r["segment"] == segment]
        return int(rows[0]["offset"]) if len(rows) == 1 else None

    def _global_lvalue(self, name: str, absolute: int, width: int, far: bool,
                       object_offset: int | None = None) -> str:
        target = object_offset
        rel = absolute - target if target is not None else absolute
        declaration = DECLS.variables.get(name)
        if declaration:
            self._global_decls[name] = declaration
        elif name not in self._global_decls:
            qualifier = "far " if far else ""
            self._global_decls[name] = f"extern unsigned char {qualifier}{name}[];"
        aggregate = bool(declaration and re.search(r"\bstruct\s+\w+\b", declaration))
        if width == 1:
            if rel == 0 and declaration and "[" not in declaration and not aggregate:
                return name
            if aggregate:
                return f"(*((unsigned char {('far' if far else 'near')}*)((unsigned char {('far' if far else 'near')}*)&{name} + ({rel}))))"
            return f"{name}[{rel}]"
        ty = unsigned_c_type(width)
        ptr = "far" if far else "near"
        if rel == 0 and declaration and "[" not in declaration and not aggregate:
            return name
        base = f"(unsigned char {ptr}*)&{name}" if aggregate else f"(unsigned char {ptr}*){name}"
        return f"(*(({ty} {ptr}*)({base} + ({rel}))))"

    def _based_lvalue(self, name: str, object_offset: int | None, base: str,
                      index: str, disp: int, width: int, far: bool) -> str:
        rel = disp - object_offset if object_offset is not None else disp
        terms = [x for x in (base, index) if x]
        if rel:
            terms.append(str(rel))
        offset = " + ".join(terms) or "0"
        self._global_decls.setdefault(name, DECLS.variables.get(name, f"extern unsigned char far {name}[];"))
        ptr = "far" if far else "near"
        if width == 1:
            return f"*((unsigned char {ptr}*){name} + ({offset}))"
        return f"(*(({unsigned_c_type(width)} {ptr}*)((unsigned char {ptr}*){name} + ({offset}))))"

    @staticmethod
    def _address_expr(base: str, index: str, disp: int) -> str:
        terms = [x for x in (base, index) if x]
        if disp:
            terms.append(str(disp))
        return " + ".join(terms) or "0"

    def operand(self, ins: Ins, op, address: bool = False) -> str:
        cs = analysis.cs
        if op.type == cs.x86.X86_OP_REG:
            name = ins.raw.reg_name(op.reg)
            return self._reg_read(name)
        if op.type == cs.x86.X86_OP_IMM:
            if ins.mnemonic in JCC or ins.mnemonic in ("jmp", "call"):
                return str(int(op.imm) - int(self.packet.get("offset", 0)))
            info = self._immediate_info(ins, op)
            return info["text"]
        if op.type == cs.x86.X86_OP_MEM:
            lvalue, _ = self._name_for_mem(ins, op.mem, max(1, int(op.size)))
            return f"&({lvalue})" if address else lvalue
        return "0"

    def _immediate_info(self, ins: Ins, op) -> dict[str, Any]:
        value = int(op.imm)
        value &= 0xff if op.size == 1 else 0xffff if op.size == 2 else 0xffffffff
        absolute_ins = int(self.packet.get("offset", 0)) + ins.offset
        fixups = [b for b in ins.row.get("bindings", [])
                  if int(b.get("operand_offset", -1)) >= absolute_ins
                  and int(b.get("operand_offset", -1)) < absolute_ins + ins.size]
        refs = ins.row.get("references", [])
        target_seg = None
        selector = False
        for b in fixups:
            target = b.get("target", {})
            if target.get("kind") == "internal":
                target_seg = int(target.get("segment", 0)) or None
                selector = int(b.get("type", 0)) == 3
                break
        # A public at this exact segment:offset is stronger evidence than a
        # numeric immediate. Never copy a relocation-chain word into source.
        choices = []
        if target_seg:
            choices = [x for x in MAPSYM_BY_SEGMENT.get(target_seg, []) if int(x["offset"]) == value]
        else:
            choices = [x for rows in MAPSYM_BY_CNAME.values() for x in rows if int(x["offset"]) == value]
        unique = {x["name"] for x in choices}
        if len(unique) == 1:
            name = c_name(next(iter(unique)))
            declaration = DECLS.variables.get(name)
            self._global_decls.setdefault(name, declaration or f"extern char far {name}[];")
            if selector:
                return {"text": f"__lift_selector_{target_seg}", "selector_segment": target_seg,
                        "address_name": name, "width": max(1, int(op.size)), "bound": True}
            address = f"&{name}[0]" if "[" in (declaration or "") else f"&{name}"
            return {"text": f"((unsigned int)({address}))", "address_name": name,
                    "width": max(1, int(op.size)), "bound": bool(fixups)}
        if selector or fixups:
            self.f.unsupported["relocated_immediate_binding"] += 1
            return {"text": "0", "selector_segment": target_seg if selector else None,
                    "width": max(1, int(op.size)), "bound": True}
        return {"text": str(value), "width": max(1, int(op.size)), "bound": False}

    def _reg_read(self, name: str) -> str:
        name = name.lower()
        if name in REG8:
            root = ROOT_REG[name]
            if name.endswith("h"):
                return f"((unsigned char)({root} >> 8))"
            return f"((unsigned char){root})"
        if name in REG16:
            if name in ("bp", "sp"):
                return name
            return name
        if name in ("es", "ds", "cs", "ss"):
            return "0"
        return name

    def _reg_write(self, name: str, rhs: str) -> str:
        name = name.lower()
        if name in REG8:
            root = ROOT_REG[name]
            mask = "0xff00U" if name.endswith("l") else "0x00ffU"
            shift = "" if name.endswith("l") else " << 8"
            return f"{root} = ({root} & {mask}) | (((unsigned int)({rhs}) & 0xffU){shift});"
        if name in REG16 and name not in ("bp", "sp"):
            return f"{name} = ({rhs});"
        return ""

    def _set_flag(self, expr: str, right: str = "0", width: int = 2, signed: bool = False):
        self.flag = (expr, right, width, signed)

    def _branch_condition(self, mnemonic: str) -> str:
        left, right, width, signed = self.flag
        if mnemonic in ("jcxz", "jecxz"):
            return condition_text(mnemonic, "cx") or "0"
        cond = condition_text(mnemonic, left, right, width, signed)
        if cond:
            return cond
        self.f.unsupported[f"condition:{mnemonic}"] += 1
        return "__lift_flag != 0"

    def _pool_symbol_for_selector(self, ins: Ins) -> tuple[str | None, int | None]:
        if not ins.operands or ins.operands[-1].type != analysis.cs.x86.X86_OP_MEM:
            return None, None
        absolute = int(ins.operands[-1].mem.disp) & 0xffff
        bind = self._bindings_by_instruction.get(int(self.packet.get("offset", 0)) + ins.offset)
        if bind:
            for name in bind.get("exact_mapsym_names", []):
                return c_name(name), None
            for segkey in ("addressed_segment", "possible_addressed_segment"):
                seg = bind.get(segkey)
                if seg:
                    mapped = self.pool_words.get(absolute)
                    if mapped:
                        return c_name(mapped["symbol"]), int(mapped.get("symbol_extent", {}).get("offset", 0))
        row = self.pool_words.get(absolute)
        if row:
            return c_name(row["symbol"]), int(row.get("symbol_extent", {}).get("offset", 0))
        return None, None

    def _call_name(self, ins: Ins) -> str | None:
        for ref in ins.row.get("references", []):
            names = ref.get("names", [])
            if names:
                return c_name(names[0])
            if ref.get("kind") == "import":
                imported = next((x for x in self.packet.get("known_imported_symbols", [])
                                 if x.get("target", {}).get("module") == ref.get("module")
                                 and x.get("target", {}).get("ordinal") == ref.get("ordinal")), None)
                if imported and imported.get("symbols"):
                    imp = imported["symbols"][0]
                    decl_name = next((n for n in DECLS.functions if n.upper() == imp.upper()), None)
                    return decl_name or imp
        if ins.operands and ins.operands[0].type == analysis.cs.x86.X86_OP_IMM:
            target = int(ins.operands[0].imm) + int(self.packet.get("offset", 0))
            for call in self.packet.get("calls", []):
                if int(call.get("offset", -1)) == target and call.get("names"):
                    return c_name(call["names"][0])
        if ins.mnemonic == "call" and ins.operands and ins.operands[0].type == analysis.cs.x86.X86_OP_IMM:
            return None
        return None

    def _call_args(self, name: str, raw: list[str]) -> list[str]:
        proto = _parse_decl_signature(self.calls.get(name, ""))
        if not proto or not proto["params"] or proto["params"] == ["..."]:
            return [x["text"] for x in reversed(raw)]
        ordered = list(raw if proto.get("pascal") else reversed(raw))
        result = []
        cursor = 0
        for param in proto["params"]:
            n = _param_bytes(param)
            if cursor >= len(ordered):
                break
            if n >= 4 and cursor + 1 < len(ordered):
                first, second = ordered[cursor:cursor + 2]
                if "*" in param and "far" in param:
                    addr = first.get("address_name") or second.get("address_name")
                    if addr:
                        result.append(addr)
                    else:
                        self.f.unsupported["far_call_argument_binding"] += 1
                        result.append("((void far *)0)")
                elif "long" in param:
                    low, high = (second["text"], first["text"]) if proto.get("pascal") else (first["text"], second["text"])
                    result.append(f"(((unsigned long)({high}) << 16) | (unsigned int)({low}))")
                else:
                    result.append(first["text"])
                cursor += 2
            else:
                result.append(ordered[cursor]["text"])
                cursor += 1
        result.extend(x["text"] for x in ordered[cursor:])
        return result

    def _emit_call(self, ins: Ins, lines: list[str]):
        name = self._call_name(ins)
        args = self._call_args(name, self.pushes) if name else [x["text"] for x in reversed(self.pushes)]
        self.pushes.clear()
        if not name:
            name = f"__lift_indirect_{ins.offset:x}"
            self.calls[name] = f"extern unsigned int far {name}();"
        proto = _parse_decl_signature(self.calls.get(name, ""))
        call = f"{name}({', '.join(args)})"
        if proto and proto.get("void"):
            lines.append(f"{call};")
        elif self.f.return_type == "void" and not (proto and proto.get("ret", "").strip() not in ("void", "")):
            lines.append(f"{call};")
        else:
            lines.append(self._reg_write("ax", call))
            if proto and re.search(r"\blong\b", proto.get("ret", "")):
                lines.append(f"dx = (unsigned int)((unsigned long)({call}) >> 16);")

    def _switch_stmt(self, ins: Ins, lines: list[str]) -> bool:
        if not ins.operands or ins.operands[0].type != analysis.cs.x86.X86_OP_MEM:
            return False
        mem = ins.operands[0].mem
        if ins.raw.reg_name(mem.segment) != "cs":
            return False
        table = int(mem.disp) & 0xffff
        table_local = table - int(self.packet.get("offset", 0))
        table_rows = [x for x in self.f.instructions if x.mnemonic == "dw" and table_local <= x.offset]
        if not table_rows:
            return False
        # Prefer the exact table length supplied by cfg_solver. The packet's
        # reviewed table rows are a fallback when there is no solver result.
        found = next((t for t in self.f.tables if int(t.get("table", -1)) == int(self.packet.get("offset", 0)) + table), None)
        if found:
            count = int(found["count"])
            targets = [int(x) - int(self.packet.get("offset", 0)) for x in found["targets"]]
        else:
            same = [x for x in table_rows if x.offset < table_local + 512]
            same.sort(key=lambda x: x.offset)
            contiguous = []
            for row in same:
                if contiguous and row.offset != contiguous[-1].offset + 2:
                    break
                if row.offset < table_local:
                    continue
                contiguous.append(row)
            if not contiguous:
                return False
            targets = []
            for row in contiguous:
                ref = next((r for r in row.row.get("references", []) if r.get("kind") == "jump_table_entry"), None)
                if not ref:
                    break
                targets.append(int(ref["offset"]) - int(self.packet.get("offset", 0)))
            count = len(targets)
        if not targets:
            return False
        lines.append("switch (bx >> 1) {")
        for i, target in enumerate(targets[:count]):
            lines.append(f"case {i}: goto L_{target:04x};")
        default = self._switch_default(ins, set(targets))
        lines.append(f"default: goto L_{default:04x};" if default is not None else "default: break;")
        lines.append("}")
        return True

    def _switch_default(self, ins: Ins, targets: set[int]) -> int | None:
        prev = [x for x in self.f.instructions if x.offset < ins.offset and x.mnemonic in JCC]
        for row in reversed(prev[-8:]):
            if row.operands and row.operands[0].type == analysis.cs.x86.X86_OP_IMM:
                dest = int(row.operands[0].imm)
                if dest not in targets:
                    return dest
        return None

    def _labelled_lines(self) -> list[str]:
        self.f.commutative_nodes = []
        instructions = self.f.instructions
        branch_targets = set()
        for ins in instructions:
            if ins.raw is None:
                continue
            if ins.mnemonic in JCC or ins.mnemonic == "jmp":
                if ins.operands and ins.operands[0].type == analysis.cs.x86.X86_OP_IMM:
                    branch_targets.add(int(ins.operands[0].imm))
        for t in self.f.tables:
            branch_targets.update(int(x) - int(self.packet.get("offset", 0)) for x in t.get("targets", []))
        byoff = {i.offset: i for i in instructions}
        lines: list[str] = []
        prologue = self.prologue
        body = [i for i in instructions if i.offset >= (instructions[prologue["body_start"]].offset if prologue["body_start"] < len(instructions) else 0)]
        # Drop the entry shell and final saved-register pops/leave; the compiler
        # owns those in the generated function frame.
        end_ret = max((i.offset for i in instructions if i.mnemonic in ("ret", "retf", "retn")), default=-1)
        epilogue_offsets = {i.offset for i in instructions if i.mnemonic in ("leave",)}
        if prologue["kind"] == "bp":
            epilogue_offsets.update(i.offset for i in instructions if i.mnemonic == "pop" and i.op_str in ("bp", "si", "di") and i.offset > end_ret - 10)
        result: list[str] = []
        for ins in body:
            if ins.offset in epilogue_offsets:
                continue
            if ins.mnemonic == "dw":
                continue
            if ins.offset in branch_targets:
                result.append(f"L_{ins.offset:04x}: ;")
            result.extend(self._translate(ins))
        # Labels at table/default targets which do not begin an instruction are
        # not representable; do not invent a byte stream at such a point.
        return Structurer().run(result)

    def _translate(self, ins: Ins) -> list[str]:
        m = ins.mnemonic
        o = ins.operands
        rows: list[str] = []
        if ins.raw is None:
            return rows
        if m in ("push",):
            if o and o[0].type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(o[0].reg) in ("bp", "ds", "es", "cs", "ss"):
                return rows
            if o and o[0].type == analysis.cs.x86.X86_OP_IMM:
                value = self._immediate_info(ins, o[0])
            else:
                value = {"text": self.operand(ins, o[0]) if o else "0", "width": int(o[0].size) if o else 2}
            self.pushes.append(value)
            return rows
        if m == "pop":
            if self.pushes and o and o[0].type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(o[0].reg) not in ("bp", "ds", "es", "ss"):
                value = self.pushes.pop()["text"]
                line = self._reg_write(ins.raw.reg_name(o[0].reg), value)
                if line:
                    rows.append(line)
            return rows
        if m in ("enter", "leave", "nop", "cld", "std", "wait", "fwait", "pushf", "popf", "cli", "sti"):
            return rows
        if m in ("ret", "retf", "retn"):
            if self.f.return_type != "void":
                value = "(((unsigned long)dx << 16) | ax)" if "long" in self.f.return_type else "ax"
                rows.append(f"return {value};")
            else:
                rows.append("return;")
            return rows
        if m in JCC:
            if o and o[0].type == analysis.cs.x86.X86_OP_IMM:
                dest = int(o[0].imm)
                rows.append(f"if ({self._branch_condition(m)}) goto L_{dest:04x};")
            else:
                self.f.unsupported[f"branch:{m}"] += 1
            return rows
        if m == "jmp":
            if o and o[0].type == analysis.cs.x86.X86_OP_IMM:
                dest = int(o[0].imm)
                rows.append(f"goto L_{dest:04x};")
            elif not self._switch_stmt(ins, rows):
                self.f.unsupported["indirect_jump"] += 1
                rows.append("__lift_flag = __lift_flag;")
            return rows
        if m in ("call", "lcall", "callf"):
            self._emit_call(ins, rows)
            return rows
        if m in ("mov", "movzx", "movsx") and len(o) == 2:
            dst = o[0]
            if dst.type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(dst.reg) == "es":
                self.es_object, self.es_offset = self._pool_symbol_for_selector(ins)
                if not self.es_object:
                    absolute = int(o[1].mem.disp) & 0xffff if o[1].type == analysis.cs.x86.X86_OP_MEM else 0
                    self.es_object = self._unknown_globals.setdefault(("es", absolute), f"__lift_far_{absolute:04x}")
                    self._global_decls[self.es_object] = f"extern unsigned char far {self.es_object}[];"
                    self.es_offset = None
                return rows
            val = self.operand(ins, o[1])
            if m == "movsx":
                val = f"(({signed_c_type(max(1, int(o[1].size)))})({val}))"
            elif m == "movzx":
                val = f"(({unsigned_c_type(max(1, int(o[1].size)))})({val}))"
            if dst.type == analysis.cs.x86.X86_OP_REG:
                reg = ins.raw.reg_name(dst.reg)
                if reg in ("ds", "ss"):
                    return rows
                line = self._reg_write(reg, val)
                if line:
                    rows.append(line)
            else:
                lhs = self.operand(ins, dst)
                rows.append(f"{lhs} = {val};")
            return rows
        if m in ("les", "lds") and len(o) == 2 and o[0].type == analysis.cs.x86.X86_OP_REG:
            name = ins.raw.reg_name(o[0].reg)
            mem = o[1]
            if mem.type == analysis.cs.x86.X86_OP_MEM:
                base, _ = self._name_for_mem(ins, mem.mem, 4)
                rows.append(self._reg_write(name, f"(unsigned int)(unsigned long)({base})"))
                if m == "les":
                    row_name = self._resolved_memory_name(ins, "es", int(mem.mem.disp) & 0xffff)
                    self.es_object = row_name or self.es_object
            return rows
        if m == "lea" and len(o) == 2:
            val = self.operand(ins, o[1], address=True)
            line = self._reg_write(ins.raw.reg_name(o[0].reg), val)
            if line:
                rows.append(line)
            return rows
        if m in ("cmp", "test") and len(o) == 2:
            left = self.operand(ins, o[0])
            right = self.operand(ins, o[1])
            width = max(1, int(o[0].size))
            signed = m == "cmp" and self._signed_compare(ins)
            if m == "test":
                self._set_flag(f"(({left}) & ({right}))", "0", width, False)
                if self.carry_needed and not any(op.type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(op.reg) in ("bp", "sp") for op in (o[0], o[1])):
                    rows.append("__lift_cf = 0;")
            else:
                self._set_flag(left, right, width, signed)
                if self.carry_needed and not any(x.type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(x.reg) in ("bp", "sp") for x in (o[0], o[1])):
                    rows.append(f"__lift_cf = ((unsigned long)({left}) < (unsigned long)({right}));")
            return rows
        if m in ("adc", "sbb") and len(o) == 2:
            return self._translate_carry(ins)
        if m in ("clc", "stc", "cmc"):
            rows.append("__lift_cf = 1 - __lift_cf;" if m == "cmc" else f"__lift_cf = {int(m == 'stc')};")
            return rows
        if m in BINOP and len(o) == 2:
            lhs = self.operand(ins, o[0])
            rhs = self.operand(ins, o[1])
            op = BINOP[m]
            if m in ("imul", "mul") and len(o) == 3:
                rhs = self.operand(ins, o[2])
            expr = Expr("", max(1, int(o[0].size)), False, op, Expr(lhs), Expr(rhs))
            for node in expr.swaps():
                if self._swap_at == len(self.f.commutative_nodes):
                    node.swapped = True
                self.f.commutative_nodes.append(node)
            dst = o[0]
            dst_is_frame_register = dst.type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(dst.reg) in ("bp", "sp")
            if self.carry_needed and not dst_is_frame_register:
                if m == "add":
                    limit = "0xffUL" if int(dst.size) == 1 else "0xffffUL"
                    rows.append(f"__lift_cf = ((unsigned long)({lhs}) + (unsigned long)({rhs}) > {limit});")
                elif m == "sub":
                    rows.append(f"__lift_cf = ((unsigned long)({lhs}) < (unsigned long)({rhs}));")
                elif m in ("and", "or", "xor"):
                    rows.append("__lift_cf = 0;")
            if dst.type == analysis.cs.x86.X86_OP_REG:
                reg = ins.raw.reg_name(dst.reg)
                line = self._reg_write(reg, expr.render())
                if line:
                    rows.append(line)
                self._set_flag(self._reg_read(reg), "0", max(1, int(dst.size)), False)
            else:
                lvalue = self.operand(ins, dst)
                rows.append(f"{lvalue} = {expr.render()};")
                self._set_flag(lvalue, "0", max(1, int(dst.size)), False)
            return rows
        if m in ("inc", "dec", "neg", "not") and o:
            val = self.operand(ins, o[0])
            op = {"inc": "+", "dec": "-", "neg": "-", "not": "^"}[m]
            expr = f"({val} {op} 1)" if m in ("inc", "dec") else f"(-({val}))" if m == "neg" else f"(~({val}))"
            if o[0].type == analysis.cs.x86.X86_OP_REG:
                line = self._reg_write(ins.raw.reg_name(o[0].reg), expr)
            else:
                line = f"{val} = {expr};"
            if line:
                rows.append(line)
            if m != "not":
                self._set_flag(self.operand(ins, o[0]), "0", max(1, int(o[0].size)), False)
            return rows
        if m in ("xchg",) and len(o) == 2:
            a, b = self.operand(ins, o[0]), self.operand(ins, o[1])
            tmp = f"__xchg_{ins.offset:x}"
            self._temp_decls.add(f"unsigned int {tmp};")
            rows.extend([f"{tmp} = {a};", f"{a} = {b};", f"{b} = {tmp};"])
            return rows
        if m in ("cbw", "cwde"):
            rows.append("ax = (unsigned int)(int)(signed char)ax;")
            return rows
        if m in ("cwd", "cdq"):
            rows.append("dx = ((int)ax < 0) ? 0xffffU : 0;")
            return rows
        if m in ("mul", "imul", "div", "idiv"):
            self._translate_muldiv(ins, rows)
            return rows
        if m in ("rep", "repe", "repne", "movsb", "movsw", "stosb", "stosw", "scasb", "scasw", "cmpsb", "cmpsw"):
            self.f.unsupported[f"string:{m}"] += 1
            rows.append("__lift_flag = __lift_flag;")
            return rows
        if m in ("int", "int3", "iret", "hlt"):
            self.f.unsupported[f"terminator:{m}"] += 1
            return rows
        if m in ("wait", "fwait", "fninit", "finit", "fld", "fstp", "fild", "fistp", "fadd", "fmul", "fdiv", "fsub", "fxch"):
            self.f.unsupported[f"fpu:{m}"] += 1
            rows.append("__lift_flag = __lift_flag;")
            return rows
        # Keep the draft compilable and complete while recording exactly which
        # instruction families still lack a faithful C idiom.
        self.f.unsupported[m] += 1
        rows.append(f"/* lifter residue: {m} {ins.op_str} */")
        return rows

    def _signed_compare(self, ins: Ins) -> bool:
        m = ins.mnemonic
        # The target's consumer branch is the best direct signedness witness.
        following = next((x for x in self.f.instructions if x.offset > ins.offset and x.offset < ins.offset + ins.size + 4), None)
        if following and following.mnemonic in {"jl", "jle", "jg", "jge", "js", "jns"}:
            return True
        if following and following.mnemonic in {"jb", "jbe", "ja", "jae"}:
            return False
        return False

    def _translate_carry(self, ins: Ins) -> list[str]:
        """Lower ADC/SBB through explicit width-limited values and carry state."""
        dst, src = ins.operands
        width = max(1, int(dst.size))
        mask = 0xff if width == 1 else 0xffff
        lhs = self.operand(ins, dst)
        rhs = self.operand(ins, src)
        old_name = f"__carry_l_{ins.offset:x}"
        rhs_name = f"__carry_r_{ins.offset:x}"
        wide_name = f"__carry_w_{ins.offset:x}"
        carry_name = f"__carry_c_{ins.offset:x}"
        self._temp_decls.update({
            f"unsigned long {old_name};", f"unsigned long {rhs_name};", f"unsigned long {wide_name};",
            f"unsigned long {carry_name};"
        })
        lines = [
            f"{old_name} = (unsigned long)({lhs}) & 0x{mask:x}UL;",
            f"{rhs_name} = (unsigned long)({rhs}) & 0x{mask:x}UL;",
            f"{carry_name} = __lift_cf;",
        ]
        if ins.mnemonic == "adc":
            lines.append(f"{wide_name} = {old_name} + {rhs_name} + {carry_name};")
            lines.append(f"__lift_cf = ({wide_name} > 0x{mask:x}UL);")
        else:
            lines.append(f"__lift_cf = ({old_name} < ({rhs_name} + {carry_name}));")
            lines.append(f"{wide_name} = {old_name} - {rhs_name} - {carry_name};")
        value = f"(unsigned char){wide_name}" if width == 1 else f"(unsigned int){wide_name}"
        if dst.type == analysis.cs.x86.X86_OP_REG:
            lines.append(self._reg_write(ins.raw.reg_name(dst.reg), value))
        else:
            lines.append(f"{lhs} = {value};")
        self._set_flag(value, "0", width, False)
        return lines

    def _translate_muldiv(self, ins: Ins, lines: list[str]):
        if not ins.operands:
            return
        op = ins.operands[-1]
        rhs = self.operand(ins, op)
        tmp = f"__wide_{ins.offset:x}"
        self._temp_decls.add(f"unsigned long {tmp};")
        dividend = "(((unsigned long)dx << 16) | ax)"
        if ins.mnemonic in ("mul", "imul"):
            lines.append(f"{tmp} = ((unsigned long)ax) * ((unsigned int)({rhs}));")
        else:
            lines.append(f"{tmp} = ({rhs}) ? ({dividend} / (unsigned int)({rhs})) : 0;")
        if ins.mnemonic in ("div", "idiv"):
            rem = f"__rem_{ins.offset:x}"
            self._temp_decls.add(f"unsigned int {rem};")
            lines.append(f"{rem} = ({rhs}) ? (unsigned int)({dividend} % (unsigned int)({rhs})) : 0;")
            lines.append(f"dx = {rem};")
        lines.append(f"ax = (unsigned int){tmp};")
        lines.append(f"dx = (unsigned int)({tmp} >> 16);")

    def _signature(self) -> tuple[str, str]:
        name = c_name(self.symbol)
        params = ", ".join(f"{p['type']} {p['name']}" for p in self.f.params) or "void"
        cc = "far " if self.f.far else "near "
        if self.f.pascal:
            cc += "pascal "
        return f"{self.f.return_type} {cc}{name}({params})", name

    _temp_decls: set[str]

    def source(self) -> str:
        self._temp_decls = set()
        body = self._labelled_lines()
        signature, name = self._signature()
        proto_names = {name}
        decls = []
        for cname, decl in sorted(self.calls.items()):
            if cname not in proto_names and decl not in decls:
                decls.append(decl)
        for gname, decl in sorted(self._global_decls.items()):
            if decl not in decls and gname not in proto_names:
                decls.append(decl)
        # All processor registers represented in the machine trace are ordinary
        # C locals; the compiler profile decides which values it keeps in SI/DI.
        regs = {ins.raw.reg_name(op.reg) for ins in self.f.instructions if ins.raw is not None
                for op in ins.operands if op.type == analysis.cs.x86.X86_OP_REG}
        roots = sorted({ROOT_REG.get(r, r) for r in regs if r in REG16 | REG8 and ROOT_REG.get(r, r) not in ("bp", "sp")})
        if any(i.mnemonic in ("mul", "imul", "div", "idiv") for i in self.f.instructions) and "dx" not in roots:
            roots.append("dx")
        if any(i.mnemonic in ("call", "lcall", "callf") for i in self.f.instructions) and "ax" not in roots:
            roots.append("ax")
        if self.f.return_type != "void" and "ax" not in roots:
            roots.append("ax")
        if "long" in self.f.return_type and "dx" not in roots:
            roots.append("dx")
        local_names = {x.name for x in self.f.locals}
        params = {x["name"] for x in self.f.params}
        decl_lines = [f"{s.type_name} {s.name};" for s in self.f.locals if s.name not in params]
        decl_lines.extend(f"unsigned int {r};" for r in roots if r not in local_names and r not in params)
        decl_lines.extend(sorted(self._temp_decls))
        if self.carry_needed:
            decl_lines.append("unsigned int __lift_cf = 0;")
        if self.f.unsupported:
            decl_lines.append("int __lift_flag;")
        out = []
        declaration_text = "\n".join([signature, *decls, *self._global_decls.values()])
        needed_structs = sorted(set(re.findall(r"\bstruct\s+([A-Za-z_]\w*)\b", declaration_text)))
        for tag in needed_structs:
            if tag in DECLS.structs:
                out.append(DECLS.structs[tag])
        if out:
            out.append("")
        if decls:
            out.extend(decls)
            out.append("")
        out.append(signature)
        out.append("{")
        out.extend("    " + x for x in decl_lines)
        if decl_lines and body:
            out.append("")
        if not body:
            out.append("    ;")
        else:
            out.extend("    " + x for x in body)
        if not any(re.match(r"\s*return\b", x) for x in body):
            out.append("    return;" if self.f.return_type == "void" else "    return ax;")
        out.append("}")
        return "\n".join(out) + "\n"

    def _prepare_globals(self):
        # Force declarations for globals discovered in direct data bindings, so
        # references and definitions cannot silently use invented addresses.
        for row in self.packet.get("direct_data_bindings", []):
            names = row.get("exact_mapsym_names", [])
            if not names and row.get("ds_state") == "ASSUMED_DGROUP":
                names = row.get("possible_dgroup_names", [])
            for public in names:
                name = c_name(public)
                self._global_decls[name] = DECLS.variables.get(name, f"extern unsigned char {name}[];")

    def lift(self) -> str:
        self._prepare_globals()
        return self.source()


@dataclass
class SExpr:
    """A value held symbolically while the 8086 instruction stream runs.

    The old lifter rendered every register write as a C assignment.  That made
    MSC allocate a C home for each machine register.  SExpr keeps expression
    shape and width until a store, call, branch, or ABI boundary needs a C
    statement.  `flip` is used by the bounded refinement pass.
    """
    op: str
    args: tuple["SExpr", ...] = ()
    text: str = ""
    width: int = 2
    signed: bool = False
    flip: bool = False
    side_effect: bool = False

    def render(self) -> str:
        if self.op == "leaf":
            return self.text
        if self.op == "cast":
            return f"(({self.text})({self.args[0].render()}))"
        if self.op == "call":
            return f"{self.text}({', '.join(x.render() for x in self.args)})"
        if self.op == "unary":
            return f"({self.text}{self.args[0].render()})"
        if self.op == "binary":
            a, b = self.args
            if self.flip:
                a, b = b, a
            return f"({a.render()} {self.text} {b.render()})"
        if self.op == "select":
            return f"({self.args[0].render()} ? {self.args[1].render()} : {self.args[2].render()})"
        if self.op == "join32":
            return f"(((unsigned long)({self.args[1].render()}) << 16) | (unsigned int)({self.args[0].render()}))"
        return self.text or "0"

    def walk(self):
        yield self
        for child in self.args:
            yield from child.walk()


def sx(text: str, width: int = 2, signed: bool = False) -> SExpr:
    return SExpr("leaf", text=text, width=width, signed=signed)


class SymbolicLifter(Lifter):
    """MSC 7 lifter whose registers carry expression trees instead of C names."""

    CALLEE_CLOBBERED = {"ax", "cx", "dx"}

    def __init__(self, symbol: str, pkt: dict[str, Any] | None = None):
        super().__init__(symbol, pkt)
        self._structure_options: dict[str, Any] = {}
        self._trees: dict[str, SExpr] = {}
        self._flags: tuple[str, SExpr, SExpr, int, bool] | None = None
        self._carry: SExpr = sx("0")
        self._symbolic_lines: list[str] = []
        self._tree_locals: dict[str, int] = {}
        self._root_uses: set[str] = set()
        self._swap_counter = 0
        self._rep_byte_count: SExpr | None = None
        self._rep_sequence = False
        self._active_merges: tuple[tuple[str, ...], ...] = ()
        self._declaration_mode = "locals-first"
        self._frame_merge_map: dict[int, tuple[str, int, str]] = {}
        self._frame_merge_decls: list[str] = []
        self._flow_live = self._compute_liveness()
        self.frame_solver = lift_frame.FrameSolver(self.f.locals, self.packet.get("disassembly", []))

    @staticmethod
    def _root(name: str) -> str:
        return ROOT_REG.get(name.lower(), name.lower())

    def _reg_tree(self, name: str) -> SExpr:
        name = name.lower()
        if name in ("es", "ds", "cs", "ss"):
            return sx("0", 2)
        root = self._root(name)
        if root in ("bp", "sp"):
            return sx(root, 2)
        self._root_uses.add(root)
        value = self._trees.get(root)
        if value is None:
            value = sx(f"reg_{root}", 2)
            self._trees[root] = value
            self._tree_locals.setdefault(f"reg_{root}", 2)
        if name in REG8:
            if name.endswith("h"):
                return SExpr("cast", (SExpr("binary", (value, sx("8")), " >> ", 2),), "unsigned char", 1)
            return SExpr("cast", (SExpr("binary", (value, sx("0xff")), "&", 2),), "unsigned char", 1)
        if name in REG16:
            return value
        return sx(name, 2)

    def _write_tree(self, name: str, value: SExpr) -> None:
        name = name.lower()
        root = self._root(name)
        if root in ("bp", "sp", "es", "ds", "cs", "ss"):
            return
        if name in REG8:
            old = self._reg_tree(root)
            low = name.endswith("l")
            mask = sx("0xff00U" if low else "0x00ffU")
            part = SExpr("binary", (value, sx("0xffU")), "&", 2)
            if not low:
                part = SExpr("binary", (part, sx("8")), "<<", 2)
            highpart = SExpr("binary", (old, mask), "&", 2)
            value = SExpr("binary", (highpart, part), "|", 2)
        self._trees[root] = value

    def _symbolic_name_for_mem(self, ins: Ins, mem, width: int) -> tuple[str, str | None]:
        base = ins.raw.reg_name(mem.base) if mem.base else ""
        index = ins.raw.reg_name(mem.index) if mem.index else ""
        seg = ins.raw.reg_name(mem.segment) if mem.segment else ""
        disp = int(mem.disp)
        # BP parameters and locals, and absolute MAPSYM operands, use the
        # established declaration resolver unchanged.
        if base == "bp" and disp in self._frame_merge_map:
            name, offset, ctype = self._frame_merge_map[disp]
            return f"(*(({ctype} near *)((unsigned char near *){name} + {offset})))", None
        if base == "bp" or (not base and not index):
            return super()._name_for_mem(ins, mem, width)
        base_expr = self._reg_tree(base).render() if base else ""
        index_expr = self._reg_tree(index).render() if index else ""
        if seg == "es" and self.es_object:
            return self._based_lvalue(self.es_object, self.es_offset, base_expr, index_expr, disp, width, True), None
        address = self._address_expr(base_expr, index_expr, disp)
        pty = "far" if seg == "es" else "near"
        return f"(*(({unsigned_c_type(width)} {pty}*)({address})))", None

    def _tree_operand(self, ins: Ins, op, address: bool = False) -> SExpr:
        cs = analysis.cs
        if op.type == cs.x86.X86_OP_REG:
            return self._reg_tree(ins.raw.reg_name(op.reg))
        if op.type == cs.x86.X86_OP_IMM:
            if ins.mnemonic in JCC or ins.mnemonic in ("jmp", "call", "lcall", "callf"):
                return sx(str(int(op.imm) - int(self.packet.get("offset", 0))), max(1, int(op.size)))
            info = self._immediate_info(ins, op)
            return sx(info["text"], max(1, int(op.size)), False)
        if op.type == cs.x86.X86_OP_MEM:
            lvalue, _ = self._symbolic_name_for_mem(ins, op.mem, max(1, int(op.size)))
            return sx(f"&({lvalue})" if address else lvalue, max(1, int(op.size)))
        return sx("0", 2)

    def _compute_liveness(self) -> dict[int, set[str]]:
        """Backward register liveness over the packet CFG, used at merge points."""
        insns = [x for x in self.f.instructions if x.raw is not None]
        if not insns:
            return {}
        byoff = {x.offset: n for n, x in enumerate(insns)}
        uses: list[set[str]] = []
        defs: list[set[str]] = []
        succ: list[set[int]] = []
        for n, ins in enumerate(insns):
            u: set[str] = set()
            d: set[str] = set()
            for j, op in enumerate(ins.operands):
                if op.type != analysis.cs.x86.X86_OP_REG:
                    continue
                r = ins.raw.reg_name(op.reg).lower()
                if r not in REG16 | REG8:
                    continue
                root = self._root(r)
                if ins.mnemonic in ("mov", "movzx", "movsx", "lea", "pop") and j == 0:
                    d.add(root)
                else:
                    u.add(root)
                    if j == 0 and ins.mnemonic not in ("cmp", "test", "push", "call", "jmp", *JCC):
                        d.add(root)
            if ins.mnemonic in ("mul", "imul", "div", "idiv"):
                u.update(("ax", "dx")); d.update(("ax", "dx"))
            if ins.mnemonic in ("call", "lcall", "callf"):
                d.update(self.CALLEE_CLOBBERED)
            nexts: set[int] = set()
            if ins.mnemonic in JCC and ins.operands and ins.operands[0].type == analysis.cs.x86.X86_OP_IMM:
                dest = int(ins.operands[0].imm)
                if dest in byoff: nexts.add(byoff[dest])
            elif ins.mnemonic == "jmp":
                if ins.operands and ins.operands[0].type == analysis.cs.x86.X86_OP_IMM:
                    dest = int(ins.operands[0].imm)
                    if dest in byoff: nexts.add(byoff[dest])
                else:
                    found = next((t for t in self.f.tables if int(t.get("source", -1)) ==
                                  int(self.packet.get("offset", 0)) + ins.offset), None)
                    if found:
                        nexts.update(byoff[t - int(self.packet.get("offset", 0))]
                                     for t in found["targets"] if t - int(self.packet.get("offset", 0)) in byoff)
            if ins.mnemonic not in ("jmp", "ret", "retf", "retn", "iret") and n + 1 < len(insns):
                nexts.add(n + 1)
            uses.append(u); defs.append(d); succ.append(nexts)
        live_in = [set() for _ in insns]
        live_out = [set() for _ in insns]
        changed = True
        while changed:
            changed = False
            for n in range(len(insns) - 1, -1, -1):
                out = set().union(*(live_in[k] for k in succ[n])) if succ[n] else set()
                incoming = uses[n] | (out - defs[n])
                if out != live_out[n] or incoming != live_in[n]:
                    live_out[n], live_in[n], changed = out, incoming, True
        return {ins.offset: live_out[n] for n, ins in enumerate(insns)}

    def _materialize(self, ins: Ins, clobbered: set[str] | None = None) -> None:
        roots = self._flow_live.get(ins.offset, set())
        if clobbered is not None:
            roots &= clobbered
        for root in sorted(roots):
            if root not in self._trees:
                continue
            # C names (parameters, globals, homes, and earlier call results)
            # already have stable storage semantics. Assigning them to an
            # artificial register local needlessly changes CodeView homes and
            # can alter MSC's SI/DI choice. Freeze only computed expressions.
            if self._trees[root].op == "leaf":
                continue
            name = f"reg_{root}"
            width = max(self._trees[root].width, 2)
            self._tree_locals[name] = width
            self._symbolic_lines.append(f"{name} = {self._trees[root].render()};")
            self._trees[root] = sx(name, width)

    def _condition_tree(self, mnemonic: str) -> SExpr:
        if mnemonic in ("jcxz", "jecxz"):
            return SExpr("binary", (self._reg_tree("cx"), sx("0")), "==", 2)
        if self._flags:
            kind, left, right, width, signed = self._flags
            op = COND.get(mnemonic)
            if op:
                if mnemonic in ("jb", "jc", "jnae"):
                    op = "<"
                elif mnemonic in ("jae", "jnb", "jnc"):
                    op = ">="
                elif mnemonic in ("ja", "jnbe"):
                    op = ">"
                elif mnemonic in ("jbe", "jna"):
                    op = "<="
                if signed and mnemonic in {"jb", "jc", "jnae", "jae", "jnb", "jnc", "ja", "jnbe", "jbe", "jna"}:
                    pass
                ctype = signed_c_type(width) if signed else unsigned_c_type(width)
                left = SExpr("cast", (left,), ctype, width, signed)
                right = SExpr("cast", (right,), ctype, width, signed)
                return SExpr("binary", (left, right), op, width, signed)
            if mnemonic in ("js", "jns"):
                pred = SExpr("binary", (left, sx("0")), "<", width, True)
                return SExpr("unary", (pred,), "!" if mnemonic == "jns" else "")
        return sx("0")

    @staticmethod
    def _constant(expr: SExpr) -> int | None:
        if expr.op != "leaf":
            return None
        try:
            return int(expr.text.rstrip("uUlL"), 0)
        except ValueError:
            return None

    def _simplify_integer_tree(self, op: str, left: SExpr, right: SExpr, width: int) -> SExpr:
        """Fold the branch-free CMP/SBB/NEG and constant-select idioms."""
        if left.op == "select" and right.op == "leaf":
            c = self._constant(right)
            if c is not None:
                yes, no = left.args[1], left.args[2]
                y, n = self._constant(yes), self._constant(no)
                if y is not None and n is not None:
                    if op == "and": return SExpr("select", (left.args[0], sx(str(y & c), width), sx(str(n & c), width)), width=width)
                    if op == "or": return SExpr("select", (left.args[0], sx(str(y | c), width), sx(str(n | c), width)), width=width)
                    if op == "+": return SExpr("select", (left.args[0], sx(str(y + c), width), sx(str(n + c), width)), width=width)
                    if op == "-": return SExpr("select", (left.args[0], sx(str(y - c), width), sx(str(n - c), width)), width=width)
        if op == "neg" and left.op == "select":
            yes, no = (self._constant(x) for x in left.args[1:])
            if yes == 0xffff and no == 0:
                return SExpr("select", (left.args[0], sx("1", width), sx("0", width)), width=width)
        if op == "neg":
            return SExpr("unary", (left,), "-", width)
        return SExpr("binary", (left, right), op, width, left.signed or right.signed)

    @staticmethod
    def _branch_text(expr: SExpr) -> str:
        return expr.render()

    def _mark_swap(self, expr: SExpr) -> None:
        if expr.op == "binary" and expr.text in COMMUTATIVE:
            if self._swap_at == self._swap_counter:
                expr.flip = True
            self._swap_counter += 1
            self.f.commutative_nodes.append(expr)  # type: ignore[arg-type]
        for child in expr.args:
            self._mark_swap(child)

    def _symbolic_call(self, ins: Ins) -> list[str]:
        name = self._call_name(ins)
        pushed = list(self.pushes)
        self.pushes.clear()
        if name:
            args = self._call_args(name, pushed)
            proto = _parse_decl_signature(self.calls.get(name, ""))
            if proto and proto.get("params") and proto["params"] != ["..."] and len(args) != len(proto["params"]):
                # A control-flow join can make the linear push tracker see a
                # different arm's arguments. Preserve each actual pushed word
                # and use MSC's old-style declaration so the draft compiles;
                # the ABI count remains visible in the diff.
                args = [x["text"] for x in reversed(pushed)]
                ret = " ".join(x for x in (proto.get("ret", ""),) if x)
                self.calls[name] = f"extern {ret} {name}();"
                proto = _parse_decl_signature(self.calls[name])
        else:
            name = f"__lift_indirect_{ins.offset:x}"
            args = [x["text"] for x in reversed(pushed)]
            self.calls[name] = f"extern unsigned int far {name}();"
            proto = None
        self._materialize(ins, self.CALLEE_CLOBBERED)
        preserved = {r: self._trees[r] for r in self.CALLEE_CLOBBERED
                     if r != "ax" and r in self._trees and self._trees[r].op == "leaf"
                     and self._trees[r].text == f"reg_{r}"}
        for root in self.CALLEE_CLOBBERED:
            self._trees.pop(root, None)
        call = SExpr("call", tuple(sx(x) for x in args), name, 2, False, side_effect=True)
        rows: list[str] = []
        result_live = "ax" in self._flow_live.get(ins.offset, set())
        if (proto and proto.get("void")) or not result_live:
            rows.append(call.render() + ";")
        else:
            cname = f"call_result_{ins.offset:x}"
            ret = proto.get("ret", "") if proto else ""
            wide = bool(re.search(r"\blong\b", ret))
            self._tree_locals[cname] = 4 if wide else 2
            rows.append(f"{cname} = {call.render()};")
            result = sx(cname, 4 if wide else 2, "unsigned" not in ret)
            if wide:
                self._trees["ax"] = SExpr("cast", (result,), "unsigned int", 2)
                self._trees["dx"] = SExpr("cast", (SExpr("binary", (result, sx("16")), ">>", 4),), "unsigned int", 2)
            else:
                self._trees["ax"] = result
        for root, value in preserved.items():
            self._trees[root] = value
        return rows

    def _rep_pointer(self, segment: str, register: str) -> str | None:
        offset = self._reg_tree(register).render()
        if segment == "es":
            if not self.es_object:
                return None
            name = self.es_object
            baseoff = self.es_offset or 0
            decl = DECLS.variables.get(name, self._global_decls.get(name, ""))
            if "[" in decl or "[]" in decl:
                return f"((void far *)(&{name}[({offset}) + {baseoff}]))"
            return f"((void far *)((unsigned char far *)&{name} + ({offset}) + {baseoff}))"
        # DS is the compiler's near data frame in the observed game context;
        # this is a run-time pointer conversion, never a numeric address.
        return f"((void far *)((void near *)({offset})))"

    def _emit_rep(self, kind: str, ins: Ins) -> list[str]:
        if kind.startswith("movs"):
            destination = self._rep_pointer("es", "di")
            source = self._rep_pointer("ds", "si")
            if not destination or not source:
                self.f.unsupported[f"unbound_rep:{kind}"] += 1
                return [f"/* lifter residue: {ins.mnemonic} {ins.op_str} */"]
            count = self._rep_byte_count
            if count is None:
                count = SExpr("binary", (self._reg_tree("cx"), sx("2")), "*", 2) if kind == "movsw" else self._reg_tree("cx")
            self.calls.setdefault("_fmemcpy", "extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);")
            return [f"_fmemcpy({destination}, {source}, {count.render()});"]
        if kind.startswith("stos"):
            destination = self._rep_pointer("es", "di")
            if not destination:
                self.f.unsupported[f"unbound_rep:{kind}"] += 1
                return [f"/* lifter residue: {ins.mnemonic} {ins.op_str} */"]
            factor = "2" if kind == "stosw" else "1"
            count = self._reg_tree("cx")
            value = self._reg_tree("ax")
            fill = f"(unsigned char)({value.render()})"
            self.calls.setdefault("memset", "extern void far *memset(void far *destination, int value, unsigned int count);")
            return [f"memset({destination}, {fill}, ({count.render()} * {factor}));"]
        self.f.unsupported[f"string:{kind}"] += 1
        return [f"/* lifter residue: {ins.mnemonic} {ins.op_str} */"]

    def _translate_symbolic(self, ins: Ins) -> list[str]:
        m, ops = ins.mnemonic, ins.operands
        if ins.raw is None:
            return []
        if m.startswith("rep "):
            kind = m.split(None, 1)[1].strip()
            if kind == "movsw":
                self._rep_sequence = True
                return []
            if kind == "movsb" and self._rep_sequence:
                self._rep_sequence = False
                result = self._emit_rep("movsb", ins)
                self._rep_byte_count = None
                return result
            result = self._emit_rep(kind, ins)
            self._rep_byte_count = None
            return result
        if self._rep_sequence and m == "adc" and len(ops) == 2 and ins.op_str.replace(" ", "").lower() == "cx,cx":
            # The compiler's word-copy + carry-byte tail: rep movsw; adc cx,cx;
            # rep movsb.  The original byte count was saved before SHR CX,1.
            return []
        if m == "push":
            if ops and ops[0].type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(ops[0].reg) in ("bp", "ds", "es", "cs", "ss"):
                return []
            info = self._immediate_info(ins, ops[0]) if ops and ops[0].type == analysis.cs.x86.X86_OP_IMM else None
            value = sx(info["text"], int(info.get("width", 2))) if info else (self._tree_operand(ins, ops[0]) if ops else sx("0"))
            row = {"text": value.render(), "width": value.width, "tree": value}
            if info and info.get("address_name"):
                row["address_name"] = info["address_name"]
            self.pushes.append(row)
            return []
        if m == "pop":
            if self.pushes and ops and ops[0].type == analysis.cs.x86.X86_OP_REG:
                row = self.pushes.pop()
                self._write_tree(ins.raw.reg_name(ops[0].reg), row.get("tree", sx(row["text"])))
            return []
        if m in ("enter", "leave", "nop", "cld", "std", "wait", "fwait", "pushf", "popf", "cli", "sti", "add_sp"):
            return []
        if m in ("ret", "retf", "retn"):
            if self.f.return_type == "void":
                return ["return;"]
            ret = self._reg_tree("ax")
            if "long" in self.f.return_type:
                ret = SExpr("join32", (ret, self._reg_tree("dx")), width=4)
            return [f"return {ret.render()};"]
        if m in JCC:
            if not ops or ops[0].type != analysis.cs.x86.X86_OP_IMM:
                self.f.unsupported[f"branch:{m}"] += 1
                return []
            cond = self._condition_tree(m)
            self._materialize(ins)
            self._mark_swap(cond)
            return [f"if ({self._branch_text(cond)}) goto L_{int(ops[0].imm):04x};"]
        if m == "jmp":
            if ops and ops[0].type == analysis.cs.x86.X86_OP_IMM:
                self._materialize(ins)
                return [f"goto L_{int(ops[0].imm):04x};"]
            # Use the verified CFG jump-table recognition already attached to
            # the packet.  The target index remains an expression, not BX.
            if self._switch_stmt(ins, []):
                # Rebuild because the legacy helper's output is register-level.
                table = next((t for t in self.f.tables if int(t.get("source", -1)) ==
                              int(self.packet.get("offset", 0)) + ins.offset), None)
                if table:
                    index = self._reg_tree("bx")
                    return ["switch (" + index.render() + ") {" + " ".join(
                        f"case {n}: goto L_{int(t)-int(self.packet.get('offset',0)):04x};"
                        for n, t in enumerate(table["targets"])) + " default: break; }"]
            self.f.unsupported["indirect_jump"] += 1
            return []
        if m in ("call", "lcall", "callf"):
            return self._symbolic_call(ins)
        if m in ("mov", "movzx", "movsx") and len(ops) == 2:
            dst, src = ops
            if dst.type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(dst.reg) == "es":
                self.es_object, self.es_offset = self._pool_symbol_for_selector(ins)
                if not self.es_object:
                    absolute = int(src.mem.disp) & 0xffff if src.type == analysis.cs.x86.X86_OP_MEM else 0
                    self.es_object = self._unknown_globals.setdefault(("es", absolute), f"__lift_far_{absolute:04x}")
                    self._global_decls[self.es_object] = f"extern unsigned char far {self.es_object}[];"
                    self.es_offset = None
                return []
            value = self._tree_operand(ins, src)
            if m in ("movsx", "movzx"):
                ctype = signed_c_type(value.width) if m == "movsx" else unsigned_c_type(value.width)
                value = SExpr("cast", (value,), ctype, max(2, int(dst.size)), m == "movsx")
            if dst.type == analysis.cs.x86.X86_OP_REG:
                self._write_tree(ins.raw.reg_name(dst.reg), value)
                return []
            lhs = self._tree_operand(ins, dst)
            return [f"{lhs.render()} = {value.render()};"]
        if m in ("les", "lds") and len(ops) == 2:
            value = self._tree_operand(ins, ops[1])
            self._write_tree(ins.raw.reg_name(ops[0].reg), SExpr("cast", (value,), "unsigned int", 2))
            if m == "les":
                self.es_object = self._resolved_memory_name(ins, "es", int(ops[1].mem.disp) & 0xffff) if ops[1].type == analysis.cs.x86.X86_OP_MEM else self.es_object
            return []
        if m == "lea" and len(ops) == 2:
            address = self._tree_operand(ins, ops[1], address=True)
            value = SExpr("cast", (address,), "unsigned int", 2)
            self._write_tree(ins.raw.reg_name(ops[0].reg), value)
            return []
        if m in ("cmp", "test") and len(ops) == 2:
            left, right = self._tree_operand(ins, ops[0]), self._tree_operand(ins, ops[1])
            if m == "test":
                left = SExpr("binary", (left, right), "&", max(left.width, right.width))
                right = sx("0")
                signed = False
                self._carry = sx("0")
            else:
                signed = self._signed_compare(ins)
                self._carry = SExpr("binary", (SExpr("cast", (left,), "unsigned long", 4),
                                                SExpr("cast", (right,), "unsigned long", 4)), "<", 4)
            self._flags = ("cmp", left, right, max(left.width, right.width), signed)
            return []
        if m in ("clc", "stc", "cmc"):
            self._carry = SExpr("unary", (self._carry,), "!", 2) if m == "cmc" else sx("1" if m == "stc" else "0")
            self._flags = ("carry", sx("0"), self._carry, 2, False)
            return []
        if m in BINOP and len(ops) >= 2:
            lhs = self._tree_operand(ins, ops[0])
            rhs = self._tree_operand(ins, ops[-1])
            op = BINOP[m]
            if m in ("imul", "mul") and len(ops) == 3:
                lhs, rhs = self._tree_operand(ins, ops[1]), self._tree_operand(ins, ops[2])
            width = max(lhs.width, rhs.width)
            if m in ("shr", "sar") and ops[0].type == analysis.cs.x86.X86_OP_REG and ins.raw.reg_name(ops[0].reg) == "cx" and self._constant(rhs) == 1:
                self._rep_byte_count = lhs
            carry_in = self._carry
            if m == "sbb" and lhs.render() == rhs.render() and self._flags and self._flags[0] == "cmp":
                _, a, b, cmp_width, _ = self._flags
                predicate = SExpr("binary", (SExpr("cast", (a,), "unsigned long", 4),
                                              SExpr("cast", (b,), "unsigned long", 4)), "<", cmp_width, False)
                expr = SExpr("select", (predicate, sx("0xffff", width), sx("0", width)), width=width)
            elif m in ("adc", "sbb"):
                expr = self._simplify_integer_tree("+" if m == "adc" else "-",
                                                   SExpr("binary", (lhs, rhs), op, width), carry_in, width)
            else:
                expr = self._simplify_integer_tree(op, lhs, rhs, width)
            self._mark_swap(expr)
            if m in ("add", "adc"):
                left_wide = SExpr("cast", (lhs,), "unsigned long", 4)
                right_wide = SExpr("cast", (rhs,), "unsigned long", 4)
                wide = SExpr("binary", (SExpr("binary", (left_wide, right_wide), "+", 4), carry_in), "+", 4) if m == "adc" else SExpr("binary", (left_wide, right_wide), "+", 4)
                mask = sx("0xffUL" if width == 1 else "0xffffUL", 4)
                self._carry = SExpr("binary", (wide, mask), ">", 4)
            elif m in ("sub", "sbb"):
                left_wide = SExpr("cast", (lhs,), "unsigned long", 4)
                right_wide = SExpr("cast", (rhs,), "unsigned long", 4)
                rhs_carry = SExpr("binary", (right_wide, carry_in), "+", 4) if m == "sbb" else right_wide
                self._carry = SExpr("binary", (left_wide, rhs_carry), "<", 4)
            elif m in ("and", "or", "xor"):
                self._carry = sx("0")
            if ops[0].type == analysis.cs.x86.X86_OP_REG:
                self._write_tree(ins.raw.reg_name(ops[0].reg), expr)
            else:
                return [f"{lhs.render()} = {expr.render()};"]
            if m in ("add", "sub", "adc", "sbb", "and", "or", "xor", "imul", "shl", "shr", "sar"):
                dest = self._tree_operand(ins, ops[0])
                self._flags = ("arith", dest, sx("0"), dest.width, dest.signed)
            return []
        if m in ("inc", "dec", "neg", "not") and ops:
            old = self._tree_operand(ins, ops[0])
            expr = self._simplify_integer_tree("neg", old, sx("0"), old.width) if m == "neg" else SExpr("unary", (old,), "~" if m == "not" else "", old.width)
            if m in ("inc", "dec"):
                expr = SExpr("binary", (old, sx("1")), "+" if m == "inc" else "-", old.width)
            if ops[0].type == analysis.cs.x86.X86_OP_REG:
                self._write_tree(ins.raw.reg_name(ops[0].reg), expr)
            else:
                return [f"{old.render()} = {expr.render()};"]
            self._flags = ("arith", expr, sx("0"), expr.width, expr.signed)
            return []
        if m in ("cbw", "cwde"):
            self._write_tree("ax", SExpr("cast", (self._reg_tree("al"),), "int", 2, True))
            return []
        if m in ("cwd", "cdq"):
            ax = self._reg_tree("ax")
            self._write_tree("dx", SExpr("cast", (SExpr("binary", (ax, sx("15")), ">>", 2, True),), "unsigned int", 2))
            return []
        if m in ("xchg",) and len(ops) == 2:
            a, b = self._tree_operand(ins, ops[0]), self._tree_operand(ins, ops[1])
            if ops[0].type == analysis.cs.x86.X86_OP_REG and ops[1].type == analysis.cs.x86.X86_OP_REG:
                self._write_tree(ins.raw.reg_name(ops[0].reg), b)
                self._write_tree(ins.raw.reg_name(ops[1].reg), a)
            else:
                return [f"{a.render()} = {b.render()};", f"{b.render()} = {a.render()};"]
            return []
        if m in ("mul", "imul", "div", "idiv") and ops:
            width = max(1, int(ops[-1].size))
            rhs = self._tree_operand(ins, ops[-1])
            pair = SExpr("join32", (self._reg_tree("ax"), self._reg_tree("dx")), width=4)
            if m in ("mul", "imul"):
                result = SExpr("binary", (self._reg_tree("ax"), rhs), "*", 4, m == "imul")
            else:
                op = "/" if m in ("div", "idiv") else "%"
                result = SExpr("binary", (pair, rhs), op, 4, m == "idiv")
                rem = SExpr("binary", (pair, rhs), "%", 4, m == "idiv")
                self._write_tree("dx", SExpr("cast", (rem,), "unsigned int", 2))
            self._write_tree("ax", SExpr("cast", (result,), "unsigned int", 2))
            self._write_tree("dx", SExpr("cast", (SExpr("binary", (result, sx("16")), ">>", 4),), "unsigned int", 2))
            return []
        if m in ("rep", "repe", "repne", "movsb", "movsw", "stosb", "stosw", "scasb", "scasw", "cmpsb", "cmpsw"):
            if m in ("rep", "repe", "repne"):
                return []
            self.f.unsupported[f"string:{m}"] += 1
            return []
        if m in ("int", "int3", "iret", "hlt"):
            self.f.unsupported[f"terminator:{m}"] += 1
            return []
        # Ignore recognized frame shell instructions. Retain unknown semantics
        # as comments so the diagnostic identifies the first unsupported idiom.
        self.f.unsupported[m] += 1
        return [f"/* lifter residue: {m} {ins.op_str} */"]

    def _labelled_lines(self) -> list[str]:
        self.f.commutative_nodes = []
        self._swap_counter = 0
        self._trees.clear(); self._flags = None; self._carry = sx("0"); self._symbolic_lines = []; self._tree_locals = {}; self._root_uses = set()
        self._rep_byte_count = None; self._rep_sequence = False
        insns = self.f.instructions
        targets = set()
        for ins in insns:
            if ins.raw is not None and ins.mnemonic in (*JCC, "jmp") and ins.operands and ins.operands[0].type == analysis.cs.x86.X86_OP_IMM:
                targets.add(int(ins.operands[0].imm))
        for table in self.f.tables:
            targets.update(int(x) - int(self.packet.get("offset", 0)) for x in table.get("targets", []))
        body_start = self.prologue["body_start"]
        startoff = insns[body_start].offset if body_start < len(insns) else 0
        end_ret = max((x.offset for x in insns if x.mnemonic in ("ret", "retf", "retn")), default=-1)
        skip = {x.offset for x in insns if x.mnemonic == "leave"}
        if self.prologue["kind"] == "bp":
            skip.update(x.offset for x in insns if x.mnemonic == "pop" and x.op_str in ("bp", "si", "di") and x.offset > end_ret - 10)
        for ins in insns:
            if ins.offset < startoff or ins.offset in skip or ins.mnemonic == "dw":
                continue
            if ins.offset in targets:
                self._symbolic_lines.append(f"L_{ins.offset:04x}: ;")
            # Flush on CFG edges so expressions from distinct paths share the
            # same source-level local; straight-line arithmetic stays fused.
            self._symbolic_lines.extend(self._translate_symbolic(ins))
        return Structurer(**self._structure_options).run(self._symbolic_lines)

    def source(self) -> str:
        self._temp_decls = set()
        self._configure_frame_merges()
        body = self._labelled_lines()
        signature, name = self._signature()
        decls = []
        for cname, decl in sorted(self.calls.items()):
            if cname != name and decl not in decls:
                decls.append(decl)
        for gname, decl in sorted(self._global_decls.items()):
            if gname != name and decl not in decls:
                decls.append(decl)
        local_names = {x.name for x in self.f.locals}
        param_names = {x["name"] for x in self.f.params}
        merged_names = {n for group in self._active_merges for n in group}
        home_decl_lines = [f"{s.type_name} {s.name};" for s in self.f.locals if s.name not in param_names | merged_names]
        home_decl_lines.extend(self._frame_merge_decls)
        tree_decl_lines = [f"{unsigned_c_type(width)} {n};" for n, width in sorted(self._tree_locals.items())
                           if n not in local_names and n not in param_names]
        if self._declaration_mode == "temps-first":
            decl_lines = tree_decl_lines + home_decl_lines
        elif self._declaration_mode == "temps-reverse":
            decl_lines = home_decl_lines + list(reversed(tree_decl_lines))
        else:
            decl_lines = home_decl_lines + tree_decl_lines
        needed_structs = sorted(set(re.findall(r"\bstruct\s+([A-Za-z_]\w*)\b", "\n".join([signature, *decls, *self._global_decls.values()]))))
        out = [DECLS.structs[tag] for tag in needed_structs if tag in DECLS.structs]
        if out: out.append("")
        if decls: out.extend(decls); out.append("")
        out.extend([signature, "{"])
        out.extend("    " + row for row in decl_lines)
        if decl_lines and body: out.append("")
        out.extend("    " + row for row in body)
        if not any(re.match(r"\s*return\b", row) for row in body):
            out.append("    return;" if self.f.return_type == "void" else "    return reg_ax;")
        out.append("}")
        return "\n".join(out) + "\n"

    def _configure_frame_merges(self) -> None:
        self._frame_merge_map = {}
        self._frame_merge_decls = []
        by_name = {x.name: x for x in self.f.locals}
        for group_index, names in enumerate(self._active_merges):
            slots = [by_name[n] for n in names if n in by_name]
            if len(slots) < 2:
                continue
            low = min(x.displacement for x in slots)
            high = max(x.displacement + x.width for x in slots)
            span = high - low
            array = f"__frame_merge_{abs(low):x}_{group_index}"
            self._frame_merge_decls.append(f"unsigned char {array}[{span}];")
            for slot in slots:
                offset = slot.displacement - low
                self._frame_merge_map[slot.displacement] = (array, offset, slot.type_name)

    def lift(self) -> str:
        self._prepare_globals()
        return self.source()


# Keep the original generator available for comparisons, while making the
# symbolic-expression implementation the default for the CLI and measurement.
RegisterTransliterationLifter = Lifter
Lifter = SymbolicLifter


def lift_symbol(symbol: str) -> tuple[str, Function]:
    lifter = Lifter(symbol)
    source = lifter.lift()
    return source, lifter.f


def open_symbols() -> list[str]:
    # Match context.py's ownership/recovery view rather than infer openness from
    # a missing preserved draft.
    return [c["symbol"] for c in cards() if c.get("ownership") == "GAME" and c.get("symbol") not in recipes()]


def control_symbols() -> list[str]:
    rec = recipes()
    return [c["symbol"] for c in cards()
            if c.get("ownership") == "GAME" and c.get("symbol") in rec
            and str(rec[c["symbol"]].get("source", "")).lower().endswith(".c")]


def output_filenames(symbols: list[str]) -> dict[str, str]:
    """Keep case-distinct MAPSYM names separate on case-insensitive filesystems."""
    groups: dict[str, list[str]] = defaultdict(list)
    for symbol in symbols:
        groups[symbol.lstrip("_").casefold()].append(symbol)
    result = {}
    for symbol in symbols:
        stem = symbol.lstrip("_")
        if len(set(groups[stem.casefold()])) > 1:
            suffix = hashlib.sha256(symbol.encode("ascii", errors="replace")).hexdigest()[:8]
            stem = f"{stem}__{suffix}"
        result[symbol] = stem + ".c"
    return result


def _search(source_path: Path, symbol: str) -> dict[str, Any]:
    command = [sys.executable, str(ROOT / "tools" / "search.py"), symbol, str(source_path)]
    run = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    try:
        payload = json.loads(run.stdout)
    except Exception:
        payload = {"error": run.stderr[-4000:], "stdout": run.stdout[-4000:], "returncode": run.returncode}
    payload.setdefault("returncode", run.returncode)
    return payload


def _score(report: dict[str, Any]) -> tuple[int, int, int, int]:
    rows = report.get("results", report.get("ranking", report.get("rows", [])))
    if isinstance(rows, dict):
        rows = rows.get("rows", [])
    best = (0, 0, 0, 0)
    for row in rows:
        c = row.get("comparison", row)
        d = c.get("diagnostic") or {}
        exact = int(c.get("result") in ("CONFIRMED_MEMBER", "STRONGLY_SUPPORTED_MEMBER",
                                         "CONFIRMED", "STRONGLY_SUPPORTED", "EXACT", "EXACT_MEMBER"))
        opcode_text = row.get("opcodes", "")
        bytes_text = row.get("bytes", "")
        op = int(d.get("opcode_matches") or (opcode_text.split("/", 1)[0] if "/" in opcode_text else 0))
        size = int(d.get("candidate_bytes") or (bytes_text.split("/", 1)[0] if "/" in bytes_text else 0))
        prefix = 0
        for step in d.get("aligned_asm", []):
            if step.get("differences"):
                break
            if step.get("target_offset") is None or step.get("candidate_offset") is None:
                break
            prefix += 1
        best = max(best, (exact, prefix, op, size))
    return best


def _search_frame(symbol: str, source_path: Path) -> dict[str, Any]:
    command = [sys.executable, str(ROOT / "tools" / "search.py"), symbol,
               str(source_path), "--frame", "--full"]
    run = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    try:
        payload = json.loads(run.stdout)
    except Exception:
        return {"returncode": run.returncode, "error": run.stderr[-3000:], "stdout": run.stdout[-1000:]}
    payload["returncode"] = run.returncode
    return payload


def refine_one(symbol: str, path: Path, lifter: Lifter, max_variants: int = 24) -> dict[str, Any]:
    """Search source variants, preferring exact opcode prefixes at first divergence."""
    candidates = [path]
    original = path.read_text(encoding="ascii", errors="replace")
    seen = {original}
    # Reserve room for frame, temporary, condition-polarity, and loop-form
    # experiments so a long arithmetic expression cannot crowd them all out.
    swap_limit = min(max(0, max_variants - 13), 8, len(lifter.f.commutative_nodes))
    for i in range(swap_limit):
        lifter._swap_at = i
        trial = lifter.source()
        lifter._swap_at = None
        if trial not in seen:
            seen.add(trial)
            p = path.with_name(path.stem + f"_swap{i:02d}.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
    # FrameSolver uses the target's BP accesses and observed use order to
    # generate declaration-order hypotheses. Search scores every source with
    # MSC and the aligned instruction prefix is the first-divergence guide.
    old = list(lifter.f.locals)
    budget = min(8, max(0, max_variants - len(candidates) - 6))
    all_frame_variants = lifter.frame_solver.variants(32)
    frame_variants = all_frame_variants[:min(4, budget)]
    merge_variants = [x for x in all_frame_variants if x.merges]
    frame_variants += merge_variants[:max(0, budget - len(frame_variants))]
    for variant in frame_variants:
        by_name = {row.name: row for row in old}
        lifter.f.locals[:] = [by_name[n] for n in variant.order]
        lifter._active_merges = variant.merges
        trial = lifter.source()
        if trial not in seen:
            seen.add(trial)
            p = path.with_name(path.stem + f"_frame_{variant.name}.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
    lifter.f.locals[:] = old
    lifter._active_merges = ()
    lifter._declaration_mode = "locals-first"
    temp_variants = []
    for mode in ("temps-first", "temps-reverse"):
        if len(candidates) >= max_variants:
            break
        lifter._declaration_mode = mode
        trial = lifter.source()
        if trial not in seen:
            seen.add(trial)
            p = path.with_name(path.stem + f"_{mode.replace('-', '_')}.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
            temp_variants.append(mode)
    lifter._declaration_mode = "locals-first"
    structure_variants = []
    for name, options in (
        ("condition_flip", {"condition_flip": True}),
        ("loops_while", {"loop_style": "while"}),
        ("loops_for", {"loop_style": "for"}),
        ("loops_forever", {"loop_style": "forever"}),
    ):
        if len(candidates) >= max_variants:
            break
        lifter._structure_options = options
        trial = lifter.source()
        lifter._structure_options = {}
        if trial not in seen:
            seen.add(trial)
            p = path.with_name(path.stem + f"_{name}.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
            structure_variants.append(name)
    # Keep one direct local-order contrast when the model had no useful
    # alternative and spare budget remains.
    if len(candidates) < max_variants and len(old) >= 2 and len(frame_variants) <= 1:
        lifter.f.locals.reverse()
        trial = lifter.source()
        lifter.f.locals[:] = old
        if trial not in seen:
            p = path.with_name(path.stem + "_locals.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
    command = [sys.executable, str(ROOT / "tools" / "search.py"), symbol, *[str(x) for x in candidates], "--full"]
    run = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    try:
        result = json.loads(run.stdout)
    except Exception:
        return {"returncode": run.returncode, "error": run.stderr[-4000:], "stdout": run.stdout[-4000:]}
    rows = result.get("results", result.get("ranking", []))
    report_path = result.get("report")
    if report_path:
        try:
            detail = read_json(ROOT / report_path)
            rows = detail.get("results", rows)
        except (OSError, FormatError, ValueError):
            pass
    base_row = next((row for row in rows if str(row.get("candidate", "")) == "0"), rows[0] if rows else {})
    baseline_score = _score({"results": [base_row]}) if base_row else (0, 0, 0, 0)
    opcode_prefix_floor = baseline_score[1]
    best_path = path
    best_score = baseline_score
    for row in rows:
        score = _score({"results": [row]})
        candidate = candidates[int(row.get("candidate", -1))] if str(row.get("candidate", "")).isdigit() and int(row["candidate"]) < len(candidates) else None
        if candidate is None:
            label = row.get("input", "")
            candidate = next((x for x in candidates if str(x) == label or x.name == Path(label).name), None)
        if candidate and score[1] >= opcode_prefix_floor and score > best_score:
            best_path, best_score = candidate, score

    # Compile selected frame alternatives with CodeView enabled. Exact ENTER
    # size plus matching target BP access homes takes precedence over opcode
    # count; among frame-exact variants the compiler diff's first divergence
    # and opcode prefix select the best source.
    frame_candidates = [path] + [x for x in candidates if "_frame_" in x.stem]
    if best_path not in frame_candidates:
        frame_candidates.append(best_path)
    frame_choices = []
    for candidate in frame_candidates:
        framed = _search_frame(symbol, candidate)
        fbest = framed.get("best", {})
        frame = fbest.get("frame") or {}
        access_exact = lift_frame.target_access_exact(frame)
        score = _score(framed)
        if score[1] < opcode_prefix_floor:
            continue
        rank = (int(fbest.get("result") in ("CONFIRMED_MEMBER", "STRONGLY_SUPPORTED_MEMBER")),
                int(access_exact), *score[1:])
        frame_choices.append((rank, candidate, access_exact, frame.get("candidate_enter"), frame.get("target_enter")))
    if frame_choices:
        _rank, best_path, _frame_exact, _cand_enter, _target_enter = max(frame_choices, key=lambda x: x[0])
        best_score = max(best_score, max((x[0] for x in frame_choices), default=best_score))
    if best_path != path and best_path.exists():
        path.write_text(best_path.read_text(encoding="ascii", errors="replace"), encoding="ascii", newline="\n")
    return {"returncode": run.returncode, "candidate_count": len(candidates), "best": str(best_path), "score": best_score,
            "frame_variants": [x.name for x in frame_variants], "temporary_variants": temp_variants,
            "structure_variants": structure_variants, "opcode_prefix_floor": opcode_prefix_floor,
            "frame_searches": [{"source": str(p), "rank": r, "frame_exact": exact,
                                "candidate_enter": cand_enter, "target_enter": target_enter}
                               for r, p, exact, cand_enter, target_enter in frame_choices],
            "result": result, "stderr": run.stderr[-2000:]}


def _write_one(symbol: str, outdir: Path, do_refine: bool = False, filename: str | None = None) -> dict[str, Any]:
    lifter = Lifter(symbol)
    path = outdir / (filename or f"{symbol.lstrip('_')}.c")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(lifter.lift(), encoding="ascii", newline="\n")
    refinement = refine_one(symbol, path, lifter) if do_refine else None
    return {"symbol": symbol, "source": str(path), "target_size": lifter.packet.get("extent", {}).get("size"),
            "frame_size": lifter.f.frame_size, "instructions": len(lifter.f.instructions),
            "unsupported": dict(lifter.f.unsupported), "switch_tables": len(lifter.f.tables), "refine": refinement}


def main(argv: list[str] | None = None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("symbols", nargs="*")
    ap.add_argument("--open", action="store_true", help="lift every open GAME function")
    ap.add_argument("--controls", action="store_true", help="lift admitted C functions as a regression set")
    ap.add_argument("--limit", type=int, help="maximum symbols for --open/--controls")
    ap.add_argument("--out", required=True, help="output directory (created if needed)")
    ap.add_argument("--refine", action="store_true",
                    help="search operand, frame, temporary, condition, and loop-form variants")
    args = ap.parse_args(argv)
    if bool(args.open) + bool(args.controls) + bool(args.symbols) != 1:
        ap.error("choose SYMBOLS, --open, or --controls")
    if args.open:
        names = open_symbols()
    elif args.controls:
        names = control_symbols()
    else:
        names = args.symbols
    if args.limit is not None:
        names = names[:max(0, args.limit)]
    outdir = Path(args.out)
    if not outdir.is_absolute():
        outdir = ROOT / outdir
    outdir.mkdir(parents=True, exist_ok=True)
    filenames = output_filenames(names)
    results = []
    for symbol in names:
        try:
            results.append(_write_one(symbol, outdir, args.refine, filenames[symbol]))
        except (FormatError, KeyError, ValueError, OSError) as exc:
            results.append({"symbol": symbol, "error": f"{type(exc).__name__}: {exc}"})
    summary = {"requested": len(names), "written": sum("source" in x for x in results),
               "failed": [x for x in results if "error" in x], "results": results}
    (outdir / "lift-report.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    try:
        main()
    except FormatError as exc:
        raise SystemExit(f"ERROR: {exc}")
