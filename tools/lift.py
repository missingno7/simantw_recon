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
BINOP = {"add": "+", "sub": "-", "and": "&", "or": "|", "xor": "^",
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
    n = name.lower()
    if "flmul" in n or "flmul" in n.replace("_", ""):
        return "mul"
    if "fldiv" in n or "flmod" in n:
        return "div"
    if "flshl" in n:
        return "shl"
    if "flshr" in n or "flsar" in n:
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
                    self.calls[cname] = got[0]
                elif cname not in self.calls:
                    self.calls[cname] = self._generic_prototype(cname, ins)

    def _generic_prototype(self, name: str, ins: Ins) -> str:
        # The packet's push stream is the reliable argument-count evidence only
        # when it is local to the call; an unprototyped C declaration avoids
        # inventing parameter semantics and remains accepted by MSC 7.00.
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


def _score(report: dict[str, Any]) -> tuple[int, int, int]:
    rows = report.get("results", report.get("ranking", report.get("rows", [])))
    if isinstance(rows, dict):
        rows = rows.get("rows", [])
    best = (0, 0, 0)
    for row in rows:
        c = row.get("comparison", row)
        d = c.get("diagnostic") or {}
        exact = int(c.get("result") in ("CONFIRMED_MEMBER", "STRONGLY_SUPPORTED_MEMBER",
                                         "CONFIRMED", "STRONGLY_SUPPORTED", "EXACT", "EXACT_MEMBER"))
        opcode_text = row.get("opcodes", "")
        bytes_text = row.get("bytes", "")
        op = int(d.get("opcode_matches") or (opcode_text.split("/", 1)[0] if "/" in opcode_text else 0))
        size = int(d.get("candidate_bytes") or (bytes_text.split("/", 1)[0] if "/" in bytes_text else 0))
        best = max(best, (exact, op, size))
    return best


def refine_one(symbol: str, path: Path, lifter: Lifter, max_variants: int = 24) -> dict[str, Any]:
    """Search the source and bounded one-at-a-time commutative/declaration swaps."""
    candidates = [path]
    original = path.read_text(encoding="ascii", errors="replace")
    seen = {original}
    for i in range(min(max_variants, len(lifter.f.commutative_nodes))):
        lifter._swap_at = i
        trial = lifter.source()
        lifter._swap_at = None
        if trial not in seen:
            seen.add(trial)
            p = path.with_name(path.stem + f"_swap{i:02d}.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
    # One declaration-order contrast reverses independent frame locals.
    if len(lifter.f.locals) >= 2:
        old = list(lifter.f.locals)
        lifter.f.locals.reverse()
        trial = lifter.source()
        lifter.f.locals[:] = old
        if trial not in seen:
            p = path.with_name(path.stem + "_locals.c")
            p.write_text(trial, encoding="ascii", newline="\n")
            candidates.append(p)
    command = [sys.executable, str(ROOT / "tools" / "search.py"), symbol] + [str(x) for x in candidates]
    run = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    try:
        result = json.loads(run.stdout)
    except Exception:
        return {"returncode": run.returncode, "error": run.stderr[-4000:], "stdout": run.stdout[-4000:]}
    rows = result.get("results", result.get("ranking", []))
    best_path = path
    best_score = (0, 0, 0)
    for row in rows:
        score = _score({"results": [row]})
        label = row.get("input", "")
        candidate = next((x for x in candidates if str(x) == label or x.name == Path(label).name), None)
        if candidate and score > best_score:
            best_path, best_score = candidate, score
    if best_path != path and best_path.exists():
        path.write_text(best_path.read_text(encoding="ascii", errors="replace"), encoding="ascii", newline="\n")
    return {"returncode": run.returncode, "candidate_count": len(candidates), "best": str(best_path), "score": best_score,
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
    ap.add_argument("--refine", action="store_true", help="search the draft and bounded source-order variants")
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
