"""Allocation-inverse search: steer MSC 7.00's register/home allocation toward the target.

    python tools/alloc_search.py SYMBOL [DRAFT.c] [--time-limit 600] [--jobs 16] [--beam 4]
        [--max-neighbours 400] [--out build/workers/f-alloc-inverse/runs/SYMBOL]
    python tools/alloc_search.py SYMBOL DRAFT.c --score      # objective + location map, no search

A near-exact draft whose residue is register or stack-home allocation has a flat
opcode/first-divergence objective (docs/msc7-codegen.md MSC7-R0).  This tool scores
every variant with an ALLOCATION objective computed from the aligned diagnostic
(codegen_diff): for every aligned instruction pair of equal shape it compares the
register operands and the BP-relative home operands position by position, so a
single flipped register or moved home changes the score.

Candidates are compiled with the emulated MSC 7.00 passes (tools/c2_emu.py; byte-identical
to the DOSBox service on every admitted source, about 0.2 s per compile) in a pool of
worker processes, scored against the original bytes, and searched with a beam over the
COMPLETE single-mutation neighbourhood of each beam member (the permuter's semantics-
preserving catalogue, enumerated deterministically instead of sampled, plus allocation-
specific moves such as `decl_move`).  Ranking is lexicographic:

    strict exact, body exact, opcode matches, -allocation mismatches,
    -distinct mismatching location pairs, -|byte length difference|

and a variant may never lose opcode matches relative to the draft.

Diagnostic only: an exact result must be confirmed with `tools/search.py` (DOSBox
compiler service, strict member comparison) and admitted through promote.py.
"""
from __future__ import annotations

import argparse
import copy
import hashlib
import json
import os
import random
import re
import sys
import time
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

# ----------------------------------------------------------------------------- objective

GENERAL = ('ax', 'bx', 'cx', 'dx', 'si', 'di', 'al', 'ah', 'bl', 'bh', 'cl', 'ch', 'dl', 'dh', 'sp', 'bp')
SEGMENT = ('es', 'ds', 'ss', 'cs')
_REG = re.compile(r'\b(%s)\b' % '|'.join(GENERAL + SEGMENT))
_MEM = re.compile(r'\[([^\]]*)\]')
_DISP = re.compile(r'([+-])\s*(0x[0-9a-f]+|\d+)\s*$')


def location_tokens(asm):
    """Allocation-relevant operand tokens of one rendered instruction, in operand order.

    A register gives ('reg', name).  A BP-based memory operand gives ('home', displacement)
    followed by its index register, if any.  Other memory operands contribute only their
    base/index registers (their displacement is data layout, not allocation).
    """
    text = (asm or '').lower()
    parts = text.split(None, 1)
    if len(parts) < 2:
        return []
    operands = parts[1]
    tokens = []
    pos = 0
    for m in _MEM.finditer(operands):
        tokens += [('reg', r) for r in _REG.findall(operands[pos:m.start()])
                   if r not in ('byte', 'word')]
        inner = m.group(1)
        if ':' in inner:          # segment override inside brackets is not produced by capstone
            inner = inner.split(':', 1)[1]
        regs = _REG.findall(inner)
        if 'bp' in regs:
            d = _DISP.search(inner)
            disp = 0
            if d:
                disp = int(d.group(2), 0) * (-1 if d.group(1) == '-' else 1)
            tokens.append(('home', disp))
            tokens += [('reg', r) for r in regs if r != 'bp']
        else:
            tokens += [('reg', r) for r in regs]
        pos = m.end()
    tokens += [('reg', r) for r in _REG.findall(operands[pos:])]
    return tokens


def _frame_size(asm):
    m = re.match(r'\s*enter\s+(0x[0-9a-f]+|\d+)', (asm or '').lower())
    return int(m.group(1), 0) if m else None


def _fixup_row(row):
    target = (row.get('target') or '').lower()
    candidate = (row.get('candidate') or '').lower()
    return 'resolved fixup' in target or 'resolved fixup' in candidate


def _render(token):
    kind, value = token
    if kind == 'home':
        return '[bp%+d]' % value
    return value


def allocation_objective(aligned):
    """Count register/home operand agreement over aligned rows of equal instruction shape.

    Returns dict(reg_ok, reg_bad, home_ok, home_bad, bad, pairs) where `pairs` counts
    (candidate location -> target location) for every disagreeing operand.
    """
    reg_ok = reg_bad = home_ok = home_bad = 0
    pairs = Counter()
    for row in aligned:
        differences = set(row.get('differences') or [])
        if 'instruction_shape' in differences or row.get('target_offset') is None \
                or row.get('candidate_offset') is None or _fixup_row(row):
            continue
        left = location_tokens(row.get('target'))
        right = location_tokens(row.get('candidate'))
        frame = [_frame_size(row.get(side)) for side in ('target', 'candidate')]
        if frame[0] is not None and frame[1] is not None:
            # the frame size is the sum of the homes: count it as one home operand
            if frame[0] == frame[1]:
                home_ok += 1
            else:
                home_bad += 1
                pairs[('frame %d' % frame[1], 'frame %d' % frame[0])] += 1
            continue
        n = max(len(left), len(right))
        for k in range(n):
            t = left[k] if k < len(left) else None
            c = right[k] if k < len(right) else None
            home = (t and t[0] == 'home') or (c and c[0] == 'home')
            if t == c:
                if home:
                    home_ok += 1
                else:
                    reg_ok += 1
                continue
            if home:
                home_bad += 1
            else:
                reg_bad += 1
            pairs[(_render(c) if c else '-', _render(t) if t else '-')] += 1
    return dict(reg_ok=reg_ok, reg_bad=reg_bad, home_ok=home_ok, home_bad=home_bad,
                bad=reg_bad + home_bad, pairs=pairs)


def _noise(row):
    differences = set(row.get('differences') or [])
    if not differences:
        return True
    allowed = {'memory_operand', 'immediate_or_binding', 'alignment_uncertain'}
    target = (row.get('target') or '').lower()
    candidate = (row.get('candidate') or '').lower()
    return differences <= allowed and ('resolved fixup' in target or 'resolved fixup' in candidate
                                       or 'es:[' in target or 'es:[' in candidate
                                       or 'mov es, word ptr [0x' in target)


def summarize(diagnostic, comparison):
    """Score one compiled candidate from its codegen_diff diagnostic."""
    aligned = diagnostic.get('aligned_asm') or []
    objective = allocation_objective(aligned)
    body_exact = (diagnostic.get('target_bytes') == diagnostic.get('candidate_bytes')
                  and all(_noise(r) for r in aligned))
    strict = comparison.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')
    return dict(strict=strict, body_exact=body_exact,
                opcode_matches=diagnostic.get('opcode_matches', 0),
                opcode_total=diagnostic.get('opcode_total', 0),
                target_bytes=diagnostic.get('target_bytes'), candidate_bytes=diagnostic.get('candidate_bytes'),
                reg_ok=objective['reg_ok'], reg_bad=objective['reg_bad'],
                home_ok=objective['home_ok'], home_bad=objective['home_bad'],
                bad=objective['bad'], pair_kinds=len(objective['pairs']),
                pairs=sorted(([c, t, n] for (c, t), n in objective['pairs'].items()), key=lambda x: -x[2]),
                result=comparison.get('result'))


def rank(score):
    if score is None or score.get('failed'):
        return (-1,)
    return (int(score['strict']), int(score['body_exact']), -opcode_misses(score), score['opcode_matches'],
            -score['bad'], -score['pair_kinds'],
            -abs((score['candidate_bytes'] or 0) - (score['target_bytes'] or 0)))


def opcode_misses(score):
    """Aligned rows that are not opcode matches (extra, missing or reshaped instructions)."""
    return score['opcode_total'] - score['opcode_matches']


# ----------------------------------------------------------------------------- scoring backend

class Scorer:
    """Compile a source with the emulated passes and score it against the original bytes."""

    def __init__(self, symbol):
        import ne
        import mapsym
        from common import fixture
        from library_match import import_symbols
        from promote import function_flags
        self.symbol = symbol
        self.profile, self.flags = function_flags(symbol)
        self.raw = fixture('SIMANTW.EXE')
        self.image = ne.parse(self.raw)
        self.symbols = mapsym.parse(fixture('SIMANTW.SYM'))
        self.imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')

    def compile(self, text):
        import c2_emu
        result = c2_emu.compile_c(text.encode('latin1'), self.flags)
        return result

    def score_object(self, obj):
        import omf
        from codegen_grinder import score_object
        from codegen_diff import diagnose
        from common import FormatError
        module = omf.parse(obj)
        try:
            comparison = score_object(module, self.raw, self.image, self.symbols, self.imports, self.symbol)
        except FormatError as exc:
            comparison = dict(result='UNSUPPORTED_COMPARISON', issues=[str(exc)])
        diagnostic = diagnose(module, self.raw, self.image, self.symbols, self.symbol, comparison)
        return summarize(diagnostic, comparison), diagnostic, module

    def evaluate(self, text, keep=False):
        started = time.perf_counter()
        try:
            result = self.compile(text)
        except Exception as exc:  # emulator fault on a pathological mutant
            return dict(failed='emulator: %s' % exc)
        if not result.obj:
            return dict(failed='compile: ' + (result.messages or '')[-300:])
        try:
            score, diagnostic, module = self.score_object(result.obj)
        except Exception as exc:
            return dict(failed='score: %s: %s' % (type(exc).__name__, exc))
        score['function_sha256'] = function_signature(module, self.symbol)
        score['seconds'] = round(time.perf_counter() - started, 3)
        if keep:
            score['aligned'] = diagnostic.get('aligned_asm')
        return score


def function_signature(module, symbol):
    """Hash of the function's own bytes (fixup fields masked) for output de-duplication."""
    pub = next((p for p in module['publics'] if p['name'] == symbol), None)
    if pub is None:
        return None
    seg = module['segments'][pub['segment'] - 1]
    code = bytearray(bytes.fromhex(seg['data_hex']))
    begin = pub['offset']
    stop = min([p['offset'] for p in module['publics'] if p['segment'] == pub['segment'] and p['offset'] > begin]
               + [len(code)])
    for f in module['fixups']:
        if f['segment'] == pub['segment'] and begin <= f['offset'] < stop:
            for k in range(f['offset'], min(f['offset'] + f['width'], stop)):
                code[k] = 0
    return hashlib.sha256(bytes(code[begin:stop])).hexdigest()


_WORKER = {}


def _worker_init():
    _WORKER['scorers'] = {}


def _worker_eval(task):
    symbol, text = task
    scorers = _WORKER.setdefault('scorers', {})
    if symbol not in scorers:
        scorers[symbol] = Scorer(symbol)
    return scorers[symbol].evaluate(text)


def make_pool(jobs):
    from multiprocessing import get_context
    return get_context('spawn').Pool(jobs, initializer=_worker_init)


# ----------------------------------------------------------------------------- neighbourhood

class ScriptRng(random.Random):
    """Random source whose first `depth` choice() calls follow a script (default index 0).

    Used to enumerate every site a mutation can pick instead of sampling one.
    """

    def __init__(self, script, seed=0, depth=2):
        super().__init__(seed)
        self.script = list(script)
        self.depth = depth
        self.sizes = []

    def choice(self, seq):
        n = len(seq)
        if n == 0:
            raise IndexError('choice from empty sequence')
        k = len(self.sizes)
        self.sizes.append(n)
        if k < len(self.script):
            index = self.script[k]
        elif k < self.depth:
            index = 0
        else:
            index = self._randbelow(n)
        return seq[index % n]


def enumerate_mutation(body, mutation, *, depth=2, cap=200, seed=0):
    """Yield (mutated body, description) for every script of the first `depth` choices."""
    pending = [[]]
    produced = 0
    while pending and produced < cap:
        script = pending.pop()
        work = copy.deepcopy(body)
        rng = ScriptRng(script, seed=seed, depth=depth)
        try:
            description = mutation(work, rng)
        except Exception:
            description = None
        for p in range(len(script), min(depth, len(rng.sizes))):
            for i in range(1, rng.sizes[p]):
                pending.append(script + [0] * (p - len(script)) + [i])
        if description:
            produced += 1
            yield work, description


def m_decl_move(body, rng):
    """Move one local declaration to another position inside its run of declarations.

    Changes only the symbol sequence numbers C1 assigns (MSC7-A11 operand-order key);
    the declared objects, their types and initialisers are unchanged.  A declaration whose
    initialiser reads another local of the same run keeps its relative order to it.
    """
    import permuter_mutations as M
    from pycparser import c_ast
    sites = []
    for comp in M.blocks(body):
        items = comp.block_items or []
        k = 0
        while k < len(items):
            if not isinstance(items[k], c_ast.Decl):
                k += 1
                continue
            start = k
            while k < len(items) and isinstance(items[k], c_ast.Decl):
                k += 1
            run = list(range(start, k))
            if len(run) < 2:
                continue
            for i in run:
                for j in run:
                    if i != j and abs(i - j) > 0:
                        sites.append((comp, i, j))
    if not sites:
        return None
    comp, i, j = rng.choice(sites)
    items = comp.block_items
    moved = items[i]
    order = items[:i] + items[i + 1:]
    order.insert(j, moved)
    lo, hi = min(i, j), max(i, j)
    names = [d.name for d in order[lo:hi + 1]]
    for pos, d in enumerate(order[lo:hi + 1]):
        if d.init is not None:
            used = M.ids_in(d.init)
            if any(n in used for n in names[pos + 1:]):
                return None
            if M.has_side_effects(d.init) and any(x.init is not None for x in order[lo:hi + 1] if x is not d):
                return None
    comp.block_items = order
    return 'decl_move: %s to position %d (from %d)' % (moved.name, j - lo if j > i else 0, i)


_BODY_TEXT = ['']      # the current parent's original body text (set by Neighbourhood)


def _real_volatile_decl(name):
    return re.search(r'\bvolatile\b[^;{}]*\b%s\b' % re.escape(name), _BODY_TEXT[0]) is not None


def _real_volatile_cast(name):
    # tolerant of the renderer's extra parentheses: *((volatile int *) (&x))
    return re.search(r'\bvolatile\b[^;{}()]*\*\s*\)\s*\(?\s*&\s*%s\b' % re.escape(name), _BODY_TEXT[0]) is not None


def _local_decls(body):
    import permuter_mutations as M
    from pycparser import c_ast
    return {n.name: n for n, *_ in M.walk(body) if isinstance(n, c_ast.Decl) and n.name
            and not isinstance(n.type, c_ast.FuncDecl) and 'extern' not in (n.storage or [])}


def _nonlocal_reads(expr, body):
    """Values `expr` reads that a call or a store through a pointer could change.

    Locals and parameters whose address is never taken are private to the function; the
    base array of an address expression `&g[i]` contributes only its (constant) address.
    """
    import permuter_mutations as M
    from pycparser import c_ast
    params = set(M.TYPE_ENV.params) if M.TYPE_ENV is not None else set()
    private = set(_local_decls(body)) | {p for p in params if not M.address_taken(body, p)}
    if isinstance(expr, c_ast.UnaryOp) and expr.op == '&' and isinstance(expr.expr, c_ast.ArrayRef)             and isinstance(expr.expr.name, c_ast.ID):
        return M.ids_in(expr.expr.subscript) - private
    return M.ids_in(expr) - private


def _reads_memory_value(expr):
    """Like permuter_mutations.reads_memory, but `&g[i]` computes an address, reading nothing."""
    import permuter_mutations as M
    from pycparser import c_ast
    if isinstance(expr, c_ast.UnaryOp) and expr.op == '&' and isinstance(expr.expr, c_ast.ArrayRef)             and isinstance(expr.expr.name, c_ast.ID):
        return M.reads_memory(expr.expr.subscript)
    return M.reads_memory(expr)


def inline_local(body, name):
    """Replace every use of local `name` by its single pure defining expression.

    Conditions (conservative, semantics-preserving): `name` is declared once without an
    initialiser, never address-taken, written exactly once by a plain statement
    `name = e;` (optionally labelled) directly in a block; e has no side effects and does
    not read `name`; every other use lies in the following statements of that block; those
    statements (up to the last use) write none of e's variables, contain no labels, and, when
    e reads anything but locals, contain no call and no store through a pointer.
    Returns a description or None; `body` is modified only on success.
    """
    import permuter_mutations as M
    from pycparser import c_ast
    decls = [n for n, *_ in M.walk(body) if isinstance(n, c_ast.Decl) and n.name == name]
    if len(decls) != 1 or decls[0].init is not None or M.address_taken(body, name):
        return None
    for comp in M.blocks(body):
        items = comp.block_items or []
        for k, item in enumerate(items):
            stmt = item.stmt if isinstance(item, c_ast.Label) else item
            if not (isinstance(stmt, c_ast.Assignment) and stmt.op == '=' and isinstance(stmt.lvalue, c_ast.ID)
                    and stmt.lvalue.name == name):
                continue
            rvalue = stmt.rvalue
            if M.has_side_effects(rvalue) or name in M.ids_in(rvalue):
                return None
            later = items[k + 1:]
            total = M.count_uses(body, name)
            later_uses = sum(M.count_uses(x, name) for x in later)
            if later_uses == 0 or total != later_uses + 1:
                return None
            if name in set().union(*(M.written_ids(x) for x in later)):
                return None
            last = max(j for j, x in enumerate(later) if M.count_uses(x, name))
            deps = M.ids_in(rvalue)
            external = bool(_nonlocal_reads(rvalue, body)) or _reads_memory_value(rvalue)
            for x in later[:last + 1]:
                if M.contains(x, (c_ast.Label,)) or isinstance(x, c_ast.Label):
                    return None
                w = M.written_ids(x)
                if w & deps:
                    return None
                if external and (M.has_call(x) or '*mem*' in w):
                    return None
            for x in later[:last + 1]:
                for n, p, a, i in list(M.walk(x)):
                    if isinstance(n, c_ast.ID) and n.name == name and p is not None:
                        M.replace(p, a, i, copy.deepcopy(rvalue))
            if isinstance(item, c_ast.Label):
                if not later:
                    return None
                item.stmt = later[0]
                del items[k + 1]
            else:
                del items[k]
            for c2 in M.blocks(body):
                c2.block_items = [x for x in (c2.block_items or []) if x is not decls[0]]
            return 'inline_local: %s := %s' % (name, M.expr_text(rvalue)[:40])
    return None


def m_inline_local(body, rng):
    """inline_local on one eligible local (also handles labelled definitions)."""
    names = sorted(_local_decls(body))
    if not names:
        return None
    rng.shuffle(names)
    first = rng.choice(names)
    for name in [first] + names:
        work = copy.deepcopy(body)
        if inline_local(work, name):
            return inline_local(body, name)
    return None


def _follow_up(body, name, rng):
    """Optionally inline the freed local into its uses."""
    how = rng.choice(['none', 'inline'])
    if how == 'none':
        return ''
    description = inline_local(body, name)
    return None if description is None else ' + ' + description


def m_unvolatile_decl(body, rng):
    """Drop a spelled `volatile` from a local scalar declaration (a single-threaded local has
    no observable volatile semantics), optionally inlining the freed local afterwards.

    Earlier drafts use volatile locals as steering; this undoes one so natural forms can be
    re-tested."""
    from pycparser import c_ast
    sites = [d for name, d in sorted(_local_decls(body).items())
             if isinstance(d.type, c_ast.TypeDecl) and 'volatile' in (d.type.quals or [])
             and _real_volatile_decl(name)]
    if not sites:
        return None
    d = rng.choice(sites)
    d.type.quals = [q for q in d.type.quals if q != 'volatile']
    d.quals = [q for q in (d.quals or []) if q != 'volatile']
    tail = _follow_up(body, d.name, rng)
    if tail is None:
        return None
    return 'unvolatile_decl: %s%s' % (d.name, tail)


def m_strip_volatile_cast(body, rng):
    """Replace every `*(volatile T *)&x` of a non-volatile local x by `x`, optionally inlining x.

    The cast forces a memory access of an ordinary local; removing it has no runtime effect
    in a single-threaded program."""
    import permuter_mutations as M
    from pycparser import c_ast
    locals_ = _local_decls(body)
    by_name = {}
    for n, p, a, i in M.walk(body):
        if isinstance(n, c_ast.UnaryOp) and n.op == '*' and isinstance(n.expr, c_ast.Cast)                 and isinstance(n.expr.expr, c_ast.UnaryOp) and n.expr.expr.op == '&'                 and isinstance(n.expr.expr.expr, c_ast.ID):
            name = n.expr.expr.expr.name
            if name in locals_ and _real_volatile_cast(name):
                by_name.setdefault(name, []).append((p, a, i))
    if not by_name:
        return None
    name = rng.choice(sorted(by_name))
    for p, a, i in by_name[name]:
        M.replace(p, a, i, c_ast.ID(name))
    tail = _follow_up(body, name, rng)
    if tail is None:
        return None
    return 'strip_volatile_cast: %s (%d casts)%s' % (name, len(by_name[name]), tail)


def _pure_value(expr):
    """No side effects, no pointer dereference, no division: safe to evaluate early/late."""
    import permuter_mutations as M
    from pycparser import c_ast
    if M.has_side_effects(expr):
        return False
    for n, *_ in M.walk(expr):
        if isinstance(n, c_ast.ArrayRef) or (isinstance(n, c_ast.UnaryOp) and n.op == '*'):
            return False
        if isinstance(n, c_ast.StructRef) and n.type != '.':
            return False
        if isinstance(n, c_ast.BinaryOp) and n.op in ('/', '%'):
            return False
    return True


def _local_assignment(stmt, body):
    """`v = e;` with v a local, never address-taken, e pure: returns v or None."""
    import permuter_mutations as M
    from pycparser import c_ast
    if not (isinstance(stmt, c_ast.Assignment) and stmt.op == '=' and isinstance(stmt.lvalue, c_ast.ID)):
        return None
    name = stmt.lvalue.name
    if name not in _local_decls(body) or M.address_taken(body, name) or name in M.ids_in(stmt.rvalue):
        return None
    return name if _pure_value(stmt.rvalue) else None


def _branches(node):
    return [(attr, getattr(node, attr)) for attr in ('iftrue', 'iffalse') if getattr(node, attr) is not None]


def m_hoist_over_if(body, rng):
    """Move `v = e;` from the head of an if-branch to just before the `if`.

    Changes v's live range (first block) and so C2's interference/degree.  Safe because e
    is pure (no call, store, dereference or division), the condition has no side effects and
    does not read v, and every use of v lies inside that branch (so the other path and the
    code after the `if` never observe the earlier assignment)."""
    import permuter_mutations as M
    from pycparser import c_ast
    sites = []
    for comp in M.blocks(body):
        for k, item in enumerate(comp.block_items or []):
            if not isinstance(item, c_ast.If) or M.has_side_effects(item.cond):
                continue
            for attr, branch in _branches(item):
                if not isinstance(branch, c_ast.Compound) or len(branch.block_items or []) < 2:
                    continue
                name = _local_assignment(branch.block_items[0], body)
                if not name or name in M.ids_in(item.cond):
                    continue
                if M.count_uses(branch, name) != M.count_uses(body, name):
                    continue
                if M.written_ids(item.cond) & M.ids_in(branch.block_items[0].rvalue):
                    continue
                sites.append((comp, k, attr))
    if not sites:
        return None
    comp, k, attr = rng.choice(sites)
    item = comp.block_items[k]
    branch = getattr(item, attr)
    stmt = branch.block_items.pop(0)
    comp.block_items.insert(k, stmt)
    return 'hoist_over_if: %s before if (%s)' % (M.expr_text(stmt)[:40], M.expr_text(item.cond)[:30])


def m_sink_into_if(body, rng):
    """Move `v = e;` that directly precedes an `if` into the only branch that uses v.

    Inverse of hoist_over_if, with the same safety conditions."""
    import permuter_mutations as M
    from pycparser import c_ast
    sites = []
    for comp in M.blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            stmt, item = items[k], items[k + 1]
            if not isinstance(item, c_ast.If) or M.has_side_effects(item.cond):
                continue
            name = _local_assignment(stmt, body)
            if not name or name in M.ids_in(item.cond):
                continue
            using = [(attr, b) for attr, b in _branches(item) if M.count_uses(b, name)]
            if len(using) != 1 or M.count_uses(using[0][1], name) + 1 != M.count_uses(body, name):
                continue
            sites.append((comp, k, using[0][0]))
    if not sites:
        return None
    comp, k, attr = rng.choice(sites)
    stmt = comp.block_items.pop(k)
    item = comp.block_items[k]
    branch = getattr(item, attr)
    if not isinstance(branch, c_ast.Compound):
        branch = M.as_block([branch])
        setattr(item, attr, branch)
    branch.block_items.insert(0, stmt)
    return 'sink_into_if: %s into if (%s) %s' % (M.expr_text(stmt)[:40], M.expr_text(item.cond)[:30], attr)



_IDENT = re.compile(r'[A-Za-z_]\w*')


def _struct_fields(body_text):
    """[(declaration text, [field names])] of a struct body `{ ... }` (text between braces)."""
    fields = []
    for part in body_text.split(';'):
        part = ' '.join(part.split())
        if not part:
            continue
        if '(' in part or '{' in part or ':' in part:
            return None           # function pointers, nested definitions, bit-fields: not handled
        names = []
        for declarator in part.split(','):
            idents = [m.group(0) for m in _IDENT.finditer(declarator.split('[')[0])]
            if not idents:
                return None
            names.append(idents[-1])
        fields.append((part, names))
    return fields


def split_aggregate_variants(text, function):
    """Replace a local struct used only through `.field` by one local per used field.

    Earlier drafts wrap locals into a struct to pin their stack layout; an aggregate is a
    single home to C2, separate scalars are separate allocation candidates.  Semantics are
    unchanged: the struct is never used as a whole (no assignment, no `&s`, no sizeof), so
    each member behaves exactly like an independent object.  Returns [(text, description)].
    """
    import c_source as csrc
    loc = csrc.find_function(text, function)
    body = text[loc['body_start']:loc['body_end']]
    visible = csrc.mask_comments_and_strings(body)
    out = []
    decl = re.compile(r'\n([ \t]*)struct\s*(\w+)?\s*(\{[^{}]*\})?\s*(\w+)\s*;')
    for m in decl.finditer(visible):
        indent, tag, inline, name = m.group(1), m.group(2), m.group(3), m.group(4)
        if inline:
            members = inline[1:-1]
        elif tag:
            d = re.search(r'struct\s+%s\s*\{([^{}]*)\}' % re.escape(tag), csrc.mask_comments_and_strings(text))
            if not d:
                continue
            members = text[d.start(1):d.end(1)]
        else:
            continue
        fields = _struct_fields(members)
        if not fields:
            continue
        rest = visible[:m.start()] + ' ' * (m.end() - m.start()) + visible[m.end():]
        uses = list(re.finditer(r'\b%s\b' % re.escape(name), rest))
        field_names = {f for _decl, names in fields for f in names}
        whole = [u for u in uses if not re.match(r'\s*\.\s*(\w+)', rest[u.end():])
                 or re.match(r'\s*\.\s*(\w+)', rest[u.end():]).group(1) not in field_names]
        if whole or not uses:
            continue
        used = {re.match(r'\s*\.\s*(\w+)', rest[u.end():]).group(1) for u in uses}
        # identifiers already meaning something else: ignore member names (inside struct
        # definitions and after `.`/`->`), which live in their own name space
        plain = re.sub(r'struct' + chr(92) + 's*' + chr(92) + 'w*' + chr(92) + 's*' + chr(92) + '{[^{}]*' + chr(92) + '}', ' ',
                       csrc.mask_comments_and_strings(text))
        plain = re.sub(r'(' + chr(92) + '.|->)' + chr(92) + 's*' + chr(92) + 'w+', ' ', plain)
        taken = set(_IDENT.findall(plain)) - {name}
        rename = {}
        for f in sorted(used):
            rename[f] = f if f not in taken else '%s_%s' % (name, f)
            if rename[f] in taken:
                break
        else:
            lines = []
            for declaration, names in fields:
                keep = [n for n in names if n in used]
                if not keep:
                    continue
                if len(names) == 1:
                    spelled = re.sub(r'\b%s\b(?!.*\b%s\b)' % (names[0], names[0]), rename[names[0]], declaration)
                    lines.append(indent + spelled + ';')
                else:
                    spec = declaration[:re.search(r'\b%s\b' % names[0], declaration).start()]
                    if any(ch in declaration for ch in '*['):
                        lines = None
                        break
                    for n in keep:
                        lines.append(indent + spec.rstrip() + ' ' + rename[n] + ';')
            if lines is None:
                continue
            new_body = body[:m.start()] + '\n' + '\n'.join(lines) + body[m.end():]
            new_visible = csrc.mask_comments_and_strings(new_body)
            pieces, pos = [], 0
            for u in re.finditer(r'\b%s\s*\.\s*(\w+)' % re.escape(name), new_visible):
                pieces.append(new_body[pos:u.start()])
                pieces.append(rename[u.group(1)])
                pos = u.end()
            pieces.append(new_body[pos:])
            new_text = text[:loc['body_start']] + ''.join(pieces) + text[loc['body_end']:]
            out.append((new_text, 'split_aggregate: %s -> %s' % (name, ', '.join(rename[f] for f in sorted(used)))))
    return out



def m_split_web(body, rng):
    """Give a later, independent use-web of a local its own variable.

    Picks a function-body-level statement `v = e;` (e does not read v) that follows earlier
    references to v and precedes later ones, and renames v in that statement and every later
    body-level statement to a fresh local.  Safe because the statement is at the top level
    of the function (always executed before the later statements, never inside a loop) and
    the function has no labels/gotos, so every later read sees the new definition or a later
    one.  Separate variables are separate C2 allocation candidates with their own homes; the
    same effect as the permuter's split_var, without its straight-line-only restriction.
    """
    import permuter_mutations as M
    from pycparser import c_ast
    if any(isinstance(n, (c_ast.Label, c_ast.Goto)) for n, *_ in M.walk(body)):
        return None
    items = body.block_items or []
    locals_ = _local_decls(body)
    sites = []
    for k, stmt in enumerate(items):
        name = _plain_def(stmt)
        if not name or name not in locals_ or M.address_taken(body, name):
            continue
        decl = locals_[name]
        if decl not in items or decl.init is not None:
            continue
        before = sum(M.count_uses(x, name) for x in items[:k] if x is not decl)
        after = sum(M.count_uses(x, name) for x in items[k + 1:])
        if before and after:
            sites.append((k, name))
    if not sites:
        return None
    k, name = rng.choice(sites)
    fresh = M._fresh_name(body, name)
    if not fresh:
        return None
    for stmt in items[k:]:
        M._rename_ids(stmt, name, fresh)
    decl = locals_[name]
    new_decl = copy.deepcopy(decl)
    new_decl.name = fresh
    inner = new_decl.type
    while isinstance(inner, (c_ast.PtrDecl, c_ast.ArrayDecl)):
        inner = inner.type
    if isinstance(inner, c_ast.TypeDecl):
        inner.declname = fresh
    body.block_items.insert(items.index(decl) + 1, new_decl)
    return 'split_web: %s from statement %d -> %s' % (name, k, fresh)


def _plain_def(stmt):
    import permuter_mutations as M
    from pycparser import c_ast
    if isinstance(stmt, c_ast.Assignment) and stmt.op == '=' and isinstance(stmt.lvalue, c_ast.ID) \
            and stmt.lvalue.name not in M.ids_in(stmt.rvalue):
        return stmt.lvalue.name
    return None


# Kinds whose variants almost never change the compiled function (measured over 68,069
# variants on the 57 allocation targets, 2026-09-30: introduce_temp 1.0% distinct outputs,
# decl_move 0.3%, index_pointer 0.1%, mirror_comparison 0.7%, register_toggle 0%,
# swap_commutative 0.03%, incdec_style/compound_assign/cond_zero/demorgan ~0.1%, sink_decl,
# else_layout, for_to_while, assign_in_cond 0%).  C1/C2 canonicalise these spellings; a
# small sample per member keeps them in play without spending the compile budget.
LOW_YIELD = {'introduce_temp', 'decl_move', 'index_pointer', 'mirror_comparison', 'register_toggle',
             'swap_commutative', 'incdec_style', 'compound_assign', 'cond_zero', 'demorgan', 'sink_decl',
             'else_layout', 'for_to_while', 'assign_in_cond', 'split_merge_and', 'while_to_for',
             'continue_else', 'decl_order'}
LOW_YIELD_KEEP = 8

TEXT_MUTATIONS = {'split_aggregate': split_aggregate_variants}


def all_kinds(allow=None):
    kinds = sorted(set(catalogue()) | set(TEXT_MUTATIONS))
    return [k for k in kinds if not allow or k in allow]


def catalogue(allow=None):
    """Mutation functions used for the neighbourhood: the permuter's safe catalogue plus decl_move."""
    import permuter_mutations as M
    table = {name: fn for name, (fn, _weight, safe) in M.MUTATIONS.items() if safe}
    table['decl_order'] = M.m_decl_order
    table['decl_move'] = m_decl_move
    table['unvolatile_decl'] = m_unvolatile_decl
    table['strip_volatile_cast'] = m_strip_volatile_cast
    table['inline_local'] = m_inline_local
    table['hoist_over_if'] = m_hoist_over_if
    table['sink_into_if'] = m_sink_into_if
    table['split_web'] = m_split_web
    if allow:
        table = {k: v for k, v in table.items() if k in allow}
    return table


STEERING = {'register_toggle', 'introduce_temp', 'assign_in_cond', 'param_copy'}   # redundant alias / no-op hint (AGENTS.md EXACT_STEERED examples)


class Neighbourhood:
    """Children of one source text for one mutation kind (runs inside a worker process)."""

    def __init__(self, source, function):
        import permuter
        import permuter_mutations as M
        self.M = M
        self.permuter = permuter
        self.function = function
        self.codec = M.BodyCodec(source, function)
        self.reference = self.codec.splice(self.codec.render(copy.deepcopy(self.codec.body)))

    def activate(self):
        import permuter_mutations as M
        M.TYPE_ENV = self.codec.types
        _BODY_TEXT[0] = self.codec.original_body

    def render(self, body):
        text = self.codec.splice(self.codec.render(body))
        self.M.BodyCodec(text, self.function)   # the variant must re-parse
        return text

    def children(self, kind, *, base_problems=(), reference=None, cap_per_kind=200, keep_per_kind=60, seed=0):
        """Single-mutation children of this source for mutation `kind`.

        Every site is enumerated (up to `cap_per_kind`); a kind with more than
        `keep_per_kind` sites is sampled so that one prolific kind (typically
        introduce_temp) cannot crowd the others out of a bounded neighbourhood.
        Children must keep local hygiene (no new unused/shadowed locals) and may not
        add `volatile` or drop `far` relative to `reference` (permuter.qualifier_drift).
        """
        if kind in TEXT_MUTATIONS:
            out = []
            for text, description in TEXT_MUTATIONS[kind](self.codec.text, self.function):
                try:
                    self.M.BodyCodec(text, self.function)
                except Exception:
                    continue
                if not self.permuter.qualifier_drift(reference or self.reference, text):
                    out.append((text, description))
            return out
        fn = catalogue()[kind]
        rng = random.Random(seed)
        self.activate()
        found = list(enumerate_mutation(self.codec.body, fn, cap=cap_per_kind, seed=seed))
        if kind in LOW_YIELD:
            keep_per_kind = min(keep_per_kind, LOW_YIELD_KEEP)
        if len(found) > keep_per_kind:
            found = rng.sample(found, keep_per_kind)
        out = []
        base = set(base_problems)
        for work, description in found:
            if set(self.M.local_hygiene(work)) - base:
                continue
            try:
                text = self.render(work)
            except Exception:
                continue
            if self.permuter.qualifier_drift(reference or self.reference, text):
                continue
            if any(text == t for t, _d in out):
                continue
            out.append((text, description))
        return out


def _worker_expand(task):
    text, function, kind, seed, base_problems, reference = task
    cache = _WORKER.setdefault('hoods', {})
    key = hashlib.sha256(text.encode('latin1')).hexdigest()
    hood = cache.get(key)
    try:
        if hood is None:
            if len(cache) > 8:
                cache.clear()
            hood = cache[key] = Neighbourhood(text, function)
        return hood.children(kind, base_problems=base_problems, reference=reference, seed=seed)
    except Exception:
        return []


# ----------------------------------------------------------------------------- search

def backlog_entry(symbol):
    path = ROOT / 'build/triage/backlog.json'
    if not path.is_file():
        raise SystemExit('run python tools/triage.py --open first (build/triage/backlog.json)')
    data = json.loads(path.read_text(encoding='utf-8'))
    for entry in data['functions']:
        if entry['symbol'] == symbol:
            return entry
    raise SystemExit('no backlog entry for ' + symbol)


def draft_for(symbol):
    """The triage backlog's best current draft for SYMBOL."""
    entry = backlog_entry(symbol)
    draft = (entry.get('current') or {}).get('draft')
    if not draft:
        raise SystemExit('no current draft for ' + symbol)
    return ROOT / draft


def targets(minimum=0.90, classes=('REGISTER_ALLOCATION', 'HOME_ORDER')):
    """Open REGISTER_ALLOCATION/HOME_ORDER functions with opcodes >= minimum, best first."""
    data = json.loads((ROOT / 'build/triage/backlog.json').read_text(encoding='utf-8'))
    rows = []
    for entry in data['functions']:
        if entry.get('state') != 'OPEN' or entry.get('blocker_class') not in classes:
            continue
        current = entry.get('current') or {}
        try:
            a, b = map(int, current['opcodes'].split('/'))
        except (KeyError, ValueError, AttributeError):
            continue
        if b and a / b >= minimum and current.get('draft'):
            rows.append((a / b, entry['symbol']))
    return [s for _r, s in sorted(rows, key=lambda x: (-x[0], x[1]))]


def describe(score):
    if score is None or score.get('failed'):
        return 'FAILED %s' % (score or {}).get('failed', '')[:80]
    return ('%s%sopc %d/%d alloc-bad %d (reg %d/%d home %d/%d) pairs %d bytes %s/%s' % (
        'STRICT ' if score['strict'] else '', 'BODY-EXACT ' if score['body_exact'] else '',
        score['opcode_matches'], score['opcode_total'], score['bad'],
        score['reg_bad'], score['reg_ok'] + score['reg_bad'], score['home_bad'], score['home_ok'] + score['home_bad'],
        score['pair_kinds'], score['candidate_bytes'], score['target_bytes']))


class Node:
    __slots__ = ('ident', 'body', 'text', 'score', 'chain', 'parent')

    def __init__(self, ident, body, text, score, chain, parent):
        self.ident, self.body, self.text, self.score, self.chain, self.parent = ident, body, text, score, chain, parent


def provenance(chain):
    kinds = {c.split(':', 1)[0].strip() for c in chain}
    steering = sorted(kinds & STEERING)
    return ('STEERED' if steering else 'NATURAL'), steering


def search(symbol, draft, *, out, jobs=16, beam=4, max_neighbours=400, time_limit=600,
           patience=3, seed=1, allow=None, pool=None, explore=1, log=None):
    log = log or (lambda message: print(message, flush=True))
    import permuter
    started = time.perf_counter()
    import permuter_mutations as M
    source = Path(draft).read_text(encoding='latin1')
    function = permuter.source_function(source, symbol)
    hood = Neighbourhood(source, function)
    base_problems = sorted(M.local_hygiene(hood.codec.body))
    kinds = all_kinds(allow)
    out.mkdir(parents=True, exist_ok=True)
    rng = random.Random(seed)
    own_pool = pool is None
    if own_pool:
        pool = make_pool(jobs)
    trajectory = (out / 'trajectory.jsonl').open('w', encoding='utf-8')
    try:
        baseline, regenerated = pool.map(_worker_eval, [(symbol, source), (symbol, hood.reference)])
        log('[alloc] %s draft %s' % (symbol, Path(draft).relative_to(ROOT).as_posix() if Path(draft).is_relative_to(ROOT) else draft))
        log('[alloc] baseline    ' + describe(baseline))
        log('[alloc] round-trip  ' + describe(regenerated))
        if baseline.get('failed'):
            raise RuntimeError('baseline failed: ' + baseline['failed'])
        floor = opcode_misses(baseline)
        root = Node(0, None, hood.reference, regenerated, [], None)
        best = root if rank(regenerated) >= rank(baseline) else Node(0, None, source, baseline, [], None)
        best_origin = 'regenerated' if best is root else 'original'
        frontier = [root]
        seen_text = {source, hood.reference}
        seen_output = {s.get('function_sha256') for s in (baseline, regenerated)}
        evaluations = 2
        stale = 0
        step = 0
        next_id = 1
        history = []
        while frontier and time.perf_counter() - started < time_limit:
            step += 1
            batch = []
            tasks = [(member.text, function, kind, rng.randrange(1 << 30), base_problems, source)
                     for member in frontier for kind in kinds]
            expanded = pool.map(_worker_expand, tasks, chunksize=1)
            per_member = {}
            for (text0, *_rest), kids in zip(tasks, expanded):
                per_member.setdefault(text0, []).extend(kids)
            for member in frontier:
                kids = per_member.get(member.text, [])
                rng.shuffle(kids)
                taken = 0
                for text, description in kids:
                    if text in seen_text:
                        continue
                    seen_text.add(text)
                    batch.append(Node(next_id, None, text, None, member.chain + [description], member.ident))
                    next_id += 1
                    taken += 1
                    if taken >= max_neighbours:
                        break
            if not batch:
                log('[alloc] step %d: neighbourhood exhausted' % step)
                break
            scores = []
            chunk = max(jobs * 4, 32)
            for k in range(0, len(batch), chunk):
                if time.perf_counter() - started > time_limit and scores:
                    batch = batch[:len(scores)]
                    break
                scores += pool.map(_worker_eval, [(symbol, n.text) for n in batch[k:k + chunk]])
            evaluations += len(scores)
            fresh = []
            neutral = []
            below = []
            for node, score in zip(batch, scores):
                node.score = score
                trajectory.write(json.dumps(dict(id=node.ident, parent=node.parent, step=step, chain=node.chain,
                                                 score={k: v for k, v in score.items() if k != 'pairs'},
                                                 top_pairs=(score.get('pairs') or [])[:4])) + '\n')
                if score.get('failed'):
                    continue
                if opcode_misses(score) > floor:
                    below.append(node)
                    continue
                signature = score.get('function_sha256')
                if signature in seen_output:
                    if rank(score) >= rank(best.score):
                        neutral.append(node)   # same object, different source: a plateau move
                    continue
                seen_output.add(signature)
                fresh.append(node)
            trajectory.flush()
            fresh.sort(key=lambda n: rank(n.score), reverse=True)
            improved = bool(fresh) and rank(fresh[0].score) > rank(best.score)
            if improved:
                best = fresh[0]
                best_origin = 'search'
                (out / 'best.c').write_text(best.text, encoding='latin1')
                stale = 0
            else:
                stale += 1
            log('[alloc] step %d: %d variants (%d new outputs), best %s%s' % (
                step, len(scores), len(fresh), describe(best.score), '  <- ' + best.chain[-1][:70] if improved else ''))
            history.append(dict(step=step, variants=len(scores), new_outputs=len(fresh), best=describe(best.score),
                                elapsed=round(time.perf_counter() - started, 1)))
            if best.score['strict'] or (best.score['body_exact'] and best.score['bad'] == 0):
                break
            if stale >= patience:
                break
            # next frontier: best distinct outputs, always keep the incumbent's lineage alive
            pool_nodes = fresh + [n for n in frontier]
            pool_nodes.sort(key=lambda n: rank(n.score), reverse=True)
            nxt = []
            for n in pool_nodes:
                if n in nxt:
                    continue
                nxt.append(n)
                if len(nxt) >= beam:
                    break
            if best not in nxt:
                nxt[-1:] = [best]
            # a little diversity: one random fresh plateau member
            plateau = [n for n in fresh if n not in nxt and opcode_misses(n.score) <= opcode_misses(best.score)]
            if plateau:
                nxt.append(rng.choice(plateau))
            # neutral source moves keep the walk going across output plateaus, where a second
            # mutation may only become effective after a first, output-neutral one
            if neutral:
                nxt += rng.sample(neutral, min(len(neutral), max(1, beam // 2)))
            # exploration: the best below-floor variants may be one move away from a gain
            # (e.g. un-steering a volatile local loses opcodes until the local is inlined)
            below.sort(key=lambda n: (-opcode_misses(n.score), -n.score['bad']), reverse=True)
            nxt += [n for n in below[:explore] if n.chain and len(n.chain) <= 3]
            frontier = nxt
        prov, steering = provenance(best.chain)
        summary = dict(symbol=symbol, draft=str(draft), evaluations=evaluations,
                       elapsed=round(time.perf_counter() - started, 1), steps=step,
                       baseline=baseline, regenerated=regenerated, best=best.score, best_origin=best_origin,
                       chain=best.chain, provenance=prov, steering=steering, history=history)
        if best.text != source:
            (out / 'best.c').write_text(best.text, encoding='latin1')
        (out / 'summary.json').write_text(json.dumps(summary, indent=1, default=str), encoding='utf-8')
        log('[alloc] done: %d evaluations in %.0fs; best %s' % (evaluations, summary['elapsed'], describe(best.score)))
        if best.chain:
            log('[alloc] chain: ' + ' | '.join(best.chain))
        return summary
    finally:
        trajectory.close()
        if own_pool:
            pool.terminate()
            pool.join()


def run_all(a):
    """Search every open REGISTER_ALLOCATION/HOME_ORDER target (>= 90% opcodes) in turn."""
    base = Path(a.out) if a.out else ROOT / 'build/workers/f-alloc-inverse/runs'
    symbols = [s for s in (a.draft.split(',') if a.draft else targets())]
    pool = make_pool(a.jobs)
    table = []
    try:
        for symbol in symbols:
            out = base / symbol.lstrip('_')
            if (out / 'summary.json').is_file() and not a.seed == -1:
                table.append(json.loads((out / 'summary.json').read_text(encoding='utf-8')))
                continue
            start = draft_for(symbol)
            for folder in (a.start or '').split(','):
                if not folder:
                    continue
                for candidate in (Path(folder) / symbol.lstrip('_') / 'best.c', Path(folder) / (symbol.lstrip('_') + '.c')):
                    if candidate.is_file():
                        start = candidate
            try:
                summary = search(symbol, start, out=out, jobs=a.jobs, beam=a.beam,
                                 max_neighbours=a.max_neighbours, time_limit=a.time_limit, patience=a.patience,
                                 seed=max(a.seed, 1), explore=a.explore, pool=pool,
                                 allow=set(a.only.split(',')) if a.only else None)
            except Exception as exc:
                print('[alloc] %s: %s: %s' % (symbol, type(exc).__name__, exc), flush=True)
                continue
            table.append(summary)
    finally:
        pool.terminate()
        pool.join()
    for summary in table:
        print('%-28s %-8s %s  <-  %s' % (summary['symbol'], summary.get('provenance', ''),
                                         describe(summary['best']), describe(summary['baseline'])))
    return 0


def home_records(text, flags, function):
    """C2's colour-allocated stack homes of `function`: dicts name/weight/size/disp/list_pos."""
    import regalloc_model
    _res, funcs = regalloc_model.capture_homes(text.encode('latin1'), flags)
    out = []
    for f in funcs:
        if f['name'] != function.lstrip('_') or not f['before']:
            continue
        slots = regalloc_model.predict_homes(f['before'])
        for pos, d in enumerate(f['before']):
            size = d['size'] or 2
            out.append(dict(name=d['name'], weight=d['weight'], size=size, list_pos=pos,
                            disp=-(slots[d['id']] + size), interferes=len(d['interf'])))
    return out


def home_names(text, flags, function, records=None):
    """{bp displacement: [names]} of the C2 stack homes of `function` (regalloc_model)."""
    out = {}
    for d in records if records is not None else home_records(text, flags, function):
        for k in range(0, d['size'], 2):
            out.setdefault(d['disp'] + k, []).append(d['name'] + ('+%d' % k if k else ''))
    return out


def home_order_table(records, pairs):
    """Where each colour-allocated home sits and where the target wants it.

    The target displacement of a home is the majority target location of its base word
    among the disagreeing operands (unchanged when it never disagrees).  Homes are listed
    nearest-BP-first in TARGET order with their C2 weight: the allocator places heavier
    homes nearer BP (A10), so an inversion names the weight relation the source must flip.
    Homes the target has but the model does not list (late CSE/far temporaries) show as
    target locations with no row.
    """
    votes = {}
    for c, t, n in pairs:
        m = re.match(r'\[bp([+-]\d+)\]$', c)
        k = re.match(r'\[bp([+-]\d+)\]$', t)
        if m and k:
            votes.setdefault(int(m.group(1)), Counter())[int(k.group(1))] += n
    rows = []
    for d in records:
        want = votes.get(d['disp'])
        target = want.most_common(1)[0][0] if want else d['disp']
        rows.append(dict(d, target=target))
    rows.sort(key=lambda r: -r['target'])
    lines = []
    heaviest_below = None
    for r in reversed(rows):   # farthest from BP first, to flag inversions
        r['inverted'] = heaviest_below is not None and r['weight'] < heaviest_below
        heaviest_below = r['weight'] if heaviest_below is None else max(heaviest_below, r['weight'])
    for r in rows:
        lines.append('  home %-16s weight %6x size %2d  candidate [bp%+d]  target [bp%+d]%s' % (
            r['name'][:16], r['weight'], r['size'], r['disp'], r['target'],
            '   <- lighter than a home the target places farther from BP' if r['inverted'] else ''))
    return lines


def register_names(text, flags, function):
    """{register: [range names]} from C2's own allocation table (alloc_trace)."""
    import alloc_trace
    _res, funcs = alloc_trace.trace_source(text.encode('latin1'), flags)
    out = {}
    for f in funcs:
        if f['function'] != function.lstrip('_'):
            continue
        for r in alloc_trace.candidate_table(f):
            if r.get('regname') and r['regname'] not in ('-', 'ds') and r.get('name'):
                out.setdefault(r['regname'], [])
                if r['name'] not in out[r['regname']]:
                    out[r['regname']].append(r['name'])
    return out


def explain(symbol, text, scorer=None):
    """Location map (candidate -> target) annotated with the variables C2 put there."""
    import permuter
    scorer = scorer or Scorer(symbol)
    score = scorer.evaluate(text, keep=True)
    lines = [describe(score)]
    if score.get('failed'):
        return lines
    function = permuter.source_function(text, symbol)
    records = home_records(text, scorer.flags, function)
    homes = home_names(text, scorer.flags, function, records)
    regs = register_names(text, scorer.flags, function)

    def who(loc):
        m = re.match(r'\[bp([+-]\d+)\]$', loc)
        if m:
            return ','.join(homes.get(int(m.group(1)), ['?']))
        return ','.join(regs.get(loc, [])) or '?'
    for c, t, n in score.get('pairs', []):
        lines.append('  candidate %-8s (%s) -> target %-8s (candidate occupant %s)  x%d'
                     % (c, who(c)[:40], t, who(t)[:40], n))
    if records:
        lines.append('home order (target, nearest BP first):')
        lines += home_order_table(records, score.get('pairs', []))
    return lines


# ----------------------------------------------------------------------------- model what-if

REG_CODES = {1: 'cx', 2: 'dx', 3: 'bx', 6: 'si', 7: 'di'}


def register_permutation(aligned):
    """Candidate register -> target register implied by the aligned rows.

    A register maps to T when its operands disagree with T more often than they agree with
    themselves; otherwise it maps to itself.
    """
    agree = Counter()
    move = {}
    for row in aligned:
        differences = set(row.get('differences') or [])
        if 'instruction_shape' in differences or row.get('target_offset') is None \
                or row.get('candidate_offset') is None or _fixup_row(row):
            continue
        left = location_tokens(row.get('target'))
        right = location_tokens(row.get('candidate'))
        for t, c in zip(left, right):
            if c[0] != 'reg' or t[0] != 'reg':
                continue
            if t == c:
                agree[c[1]] += 1
            else:
                move.setdefault(c[1], Counter())[t[1]] += 1
    out = {}
    for reg, targets in move.items():
        best, n = targets.most_common(1)[0]
        if n > agree[reg]:
            out[reg] = best
    return out


def whatif(symbol, text, scorer=None, deltas=(-4, -2, -1, 1, 2, 4)):
    """Which single change of C2's candidate table would give the target's registers?

    Captures the class-2 (word) allocation inputs of the draft, derives the target's
    variable -> register wish from the aligned rows (register_permutation), and re-runs
    the recovered allocator model (regalloc_model.Model.run_full) under single
    perturbations:
      * one range's use count changed by `deltas` (weight rescaled with A6), and the same
        for every range of one variable;
      * one range moved ahead of / behind an equal-weight range (creation order, A8).
    Returns (wish, rows) where each row names the perturbation and the variables whose
    predicted register then matches / misses the wish.  Diagnostic guidance for choosing
    source edits (a use more or less, first reference earlier or later); the model covers
    registers, not homes.
    """
    import alloc_trace
    import permuter
    import regalloc_model as R
    scorer = scorer or Scorer(symbol)
    score = scorer.evaluate(text, keep=True)
    if score.get('failed'):
        return {}, []
    perm = register_permutation(score['aligned'])
    function = permuter.source_function(text, symbol).lstrip('_')
    _res, traced = alloc_trace.trace_source(text.encode('latin1'), scorer.flags)
    names = {}
    for f in traced:
        if f['function'] == function:
            for r in alloc_trace.candidate_table(f):
                names[r['id']] = r.get('name') or '?'
    _res, funcs = R.capture(text.encode('latin1'), scorer.flags)
    record = next((f for f in funcs if f['name'] == function and 2 in f['inputs']), None)
    if record is None:
        return perm, []
    state = record['inputs'][2]
    ids = [i for i in set(state['lists']['work2']) | set(state['lists']['alloc2'])]

    def run(st):
        model = R.Model(st)
        _split, _repick, final = model.run_full(st.get('g471f28', 0), st.get('fkind', 0))
        by_var = {}
        for cid in ids:
            reg = REG_CODES.get(final.get(cid))
            if reg:
                by_var.setdefault(names.get(cid, '?'), set()).add(reg)
        return by_var

    base = run(state)
    wish = {v: {perm.get(r, r) for r in regs} for v, regs in base.items()}
    wanted = {v for v in wish if wish[v] != base[v]}
    if not wanted:
        return dict(permutation=perm, base=base, wish=wish), []

    def judge(pred):
        hit = sorted(v for v in wanted if pred.get(v) == wish[v])
        broke = sorted(v for v in wish if v not in wanted and pred.get(v, set()) != base.get(v, set()))
        return hit, broke

    def reweighted(st, cids, delta):
        st = copy.deepcopy(st)
        for cid in cids:
            c = st['cands'][cid]
            if c['uses'] <= 0 or c['weight'] < 0x8000:
                continue
            uses = max(0, c['uses'] + delta)
            c['weight'] = ((c['weight'] - 0x8000) * uses) // c['uses'] + 0x8000 if uses else 0
            c['uses'] = uses
        return st

    rows = []
    variables = {}
    for cid in ids:
        variables.setdefault(names.get(cid, '?'), []).append(cid)
    for cid in ids:
        for d in deltas:
            hit, broke = judge(run(reweighted(state, [cid], d)))
            if hit:
                rows.append(dict(change='range %d (%s) uses %+d' % (cid, names.get(cid), d), hit=hit, broke=broke))
    for var, cids in variables.items():
        if len(cids) < 2:
            continue
        for d in deltas:
            hit, broke = judge(run(reweighted(state, cids, d)))
            if hit:
                rows.append(dict(change='every range of %s uses %+d' % (var, d), hit=hit, broke=broke))
    for lst in ('work2', 'alloc2'):
        order = state['lists'][lst]
        for i, a in enumerate(order):
            for j, b in enumerate(order):
                if j <= i or state['cands'][a]['weight'] != state['cands'][b]['weight']:
                    continue
                st = copy.deepcopy(state)
                o = st['lists'][lst]
                o[i], o[j] = o[j], o[i]
                hit, broke = judge(run(st))
                if hit:
                    rows.append(dict(change='creation order: %s(%d) <-> %s(%d) (equal weight %x)' % (
                        names.get(a), a, names.get(b), b, state['cands'][a]['weight']), hit=hit, broke=broke))
    rows.sort(key=lambda r: (-len(r['hit']), len(r['broke'])))
    return dict(permutation=perm, base=base, wish=wish), rows



def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('symbol')
    ap.add_argument('draft', nargs='?')
    ap.add_argument('--score', action='store_true', help='score the draft only and print the location map')
    ap.add_argument('--explain', action='store_true', help='--score plus the variables C2 placed at each location')
    ap.add_argument('--whatif', action='store_true', help='allocator-model what-if: single table changes giving the target registers')
    ap.add_argument('--jobs', type=int, default=16)
    ap.add_argument('--beam', type=int, default=4)
    ap.add_argument('--max-neighbours', type=int, default=400)
    ap.add_argument('--time-limit', type=float, default=600)
    ap.add_argument('--patience', type=int, default=3)
    ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('--only', help='comma-separated mutation names')
    ap.add_argument('--out')
    ap.add_argument('--explore', type=int, default=1)
    ap.add_argument('--start', help='ALL mode: comma-separated folders whose SYMBOL/best.c or SYMBOL.c seeds the search')
    a = ap.parse_args(argv)
    if a.symbol in ('ALL', '--all'):
        return run_all(a)
    draft = Path(a.draft) if a.draft else draft_for(a.symbol)
    if a.whatif:
        info, rows = whatif(a.symbol, draft.read_text(encoding='latin1'))
        print('register permutation (candidate -> target):', info.get('permutation'))
        for var in sorted(info.get('base', {})):
            if info['base'][var] != info['wish'][var]:
                print('  %-16s now %-10s target %s' % (var, ','.join(sorted(info['base'][var])),
                                                      ','.join(sorted(info['wish'][var]))))
        for r in rows[:25]:
            print('  %-60s fixes %s%s' % (r['change'], ','.join(r['hit']),
                                          ('  but moves ' + ','.join(r['broke'])) if r['broke'] else ''))
        if not rows:
            print('  no single use-count or creation-order change of the word-class table gives the wish')
        return 0
    if a.explain:
        print(chr(10).join(explain(a.symbol, draft.read_text(encoding='latin1'))))
        return 0
    if a.score:
        scorer = Scorer(a.symbol)
        score = scorer.evaluate(draft.read_text(encoding='latin1'), keep=True)
        print(describe(score))
        for c, t, n in score.get('pairs', []):
            print('  candidate %-10s target %-10s x%d' % (c, t, n))
        return 0
    out = Path(a.out) if a.out else ROOT / 'build/workers/f-alloc-inverse/runs' / a.symbol.lstrip('_')
    summary = search(a.symbol, draft, out=out, jobs=a.jobs, beam=a.beam, max_neighbours=a.max_neighbours,
                     time_limit=a.time_limit, patience=a.patience, seed=a.seed, explore=a.explore,
                     allow=set(a.only.split(',')) if a.only else None)
    return 0 if summary['best'].get('strict') else 1


if __name__ == '__main__':
    raise SystemExit(main())
