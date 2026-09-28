"""Semantics-preserving C source mutations for MSC 7.00 (pycparser AST based).

Only the target function body is parsed and regenerated. Its signature and the rest of
the translation unit stay byte-for-byte as supplied. MSC pointer words are represented
inside the AST with C qualifiers; source-position metadata keeps real ``volatile``
distinct from far-pointer markers.
"""
from __future__ import annotations

import copy
import json
import random
import re
from functools import lru_cache
from pathlib import Path

from pycparser import c_ast, c_generator, CParser

import c_source as csrc

UNSUPPORTED = re.compile(r'\b(interrupt|_interrupt|fortran|_asm|__asm)\b')


# ------------------------------------------------------------------ parse / generate

class BodyCodec:
    def __init__(self, full_text: str, function: str):
        self.text = full_text
        self.function = function
        self.loc = csrc.find_function(full_text, function)
        self.header = full_text[self.loc['header_start']:self.loc['body_start']]
        body = full_text[self.loc['body_start']:self.loc['body_end']]
        body = csrc.strip_comments(body)
        if UNSUPPORTED.search(body):
            raise ValueError('body uses an unsupported MSC keyword: ' + UNSUPPORTED.search(body).group(0))
        self.original_body = body
        mapped = map_dialect(body)
        self.typedefs = sorted(csrc.typedef_names(full_text))
        prelude = ''.join(f'typedef int {t};\n' for t in self.typedefs)
        src = prelude + 'void __permuter_target(void)\n' + mapped
        ast = CParser().parse(src, filename='<body>')
        fn = ast.ext[-1]
        assert isinstance(fn, c_ast.FuncDef)
        self.body = fn.body
        self.coord_line_offset = len(self.typedefs) + 2
        for node, *_ in walk(self.body):
            if isinstance(node, c_ast.Cast):
                for type_node, *_ in walk(node.to_type):
                    if isinstance(type_node, c_ast.TypeDecl) and type_node.coord is None:
                        type_node.coord = node.coord
        global TYPE_ENV
        TYPE_ENV = TypeEnv.build(full_text, function)
        self.types = TYPE_ENV

    def render(self, body) -> str:
        return FarGenerator.finish(FarGenerator(self.original_body, self.coord_line_offset).visit(body))

    def splice_fn(self, header: str, body_text: str, base_text: str | None = None) -> str:
        """Replace header+body of the function (header may carry register-param edits)."""
        text = base_text if base_text is not None else self.text
        loc = csrc.find_function(text, self.function) if base_text is not None else self.loc
        return text[:loc['header_start']] + header + body_text + text[loc['body_end']:]

    def splice(self, body_text: str, base_text: str | None = None) -> str:
        """Insert a rendered body into the full text (or into base_text at the same function)."""
        text = base_text if base_text is not None else self.text
        loc = csrc.find_function(text, self.function) if base_text is not None else self.loc
        return text[:loc['body_start']] + body_text + text[loc['body_end']:]


class FarGenerator(c_generator.CGenerator):
    def __init__(self, source='', line_offset=0):
        super().__init__(reduce_parentheses=True)
        self.source = source
        self.line_offset = line_offset
        self._visit_depth = 0

    def _source_window(self, n):
        coord = getattr(n, 'coord', None)
        if coord is None or not coord.line:
            return ''
        line = coord.line - self.line_offset
        lines = self.source.splitlines()
        if not 0 <= line < len(lines):
            return ''
        start = max(0, (coord.column or 1) - 1)
        current = lines[line]
        separators = [current.rfind(ch, 0, start) for ch in ';{}']
        statement_start = max(separators) + 1
        tail = current[statement_start:] + '\n' + '\n'.join(lines[line + 1:line + 3])
        stops = [p for p in (tail.find(';'), tail.find('}')) if p >= 0]
        return tail[:min(stops) + 1] if stops else tail

    def _generate_type(self, n, modifiers=[], emit_declname=True):
        if isinstance(n, c_ast.TypeDecl):
            window = self._source_window(n)
            marker = re.search(r'\b(far|_far|__far|near|_near|huge|__segment|__based|_based)\b', window)
            if marker and isinstance(n.type, (c_ast.IdentifierType, c_ast.Struct, c_ast.Union, c_ast.Enum)):
                word = marker.group(1)
                quals = list(n.quals or [])
                need = {'far': ['volatile'], '_far': ['volatile'], '__far': ['volatile'],
                        'near': ['const'], '_near': ['const'], 'huge': ['volatile', 'const'],
                        '__segment': ['volatile'], '__based': ['volatile'], '_based': ['volatile']}[word]
                for q in need:
                    if q in quals:
                        quals.remove(q)
                names = list(n.type.names) if isinstance(n.type, c_ast.IdentifierType) else [self.visit(n.type).strip()]
                if word in ('far', '_far', '__far', 'near', '_near', 'huge'):
                    names.append({'_far': 'far', '__far': 'far', '_near': 'near'}.get(word, word))
                elif word in ('__based', '_based'):
                    phrase = _based_phrase(window, marker.start())
                    names.append(phrase)
                else:
                    names.append('__segment')
                proxy = c_ast.TypeDecl(n.declname, quals, n.align, c_ast.IdentifierType(names))
                return super()._generate_type(proxy, modifiers, emit_declname)
        return super()._generate_type(n, modifiers, emit_declname)

    def visit(self, node):
        root = self._visit_depth == 0
        self._visit_depth += 1
        try:
            out = super().visit(node)
        finally:
            self._visit_depth -= 1
        if not root:
            return out
        visible = csrc.mask_comments_and_strings(self.source)
        conv = re.compile(r'\b(pascal|cdecl)\s*(\*)?\s*([A-Za-z_]\w*)?')
        for match in conv.finditer(visible):
            word, pointer, name = match.groups()
            if not name:
                continue
            if pointer:
                pattern = re.compile(r'(\(\s*)\*\s*(' + re.escape(name) + r'\b)')
                out, count = pattern.subn(lambda m: m.group(1) + word + ' *' + m.group(2), out, count=1)
            else:
                pattern = re.compile(r'\b' + re.escape(name) + r'\s*\(')
                out, count = pattern.subn(word + ' ' + name + '(', out, count=1)
        return out

    @staticmethod
    def finish(text):
        return text


TYPE_ENV = None
ROOT = Path(__file__).resolve().parents[1]
_DECL_AXIS_CHECKED = {}


def _based_phrase(text, start):
    """Extract a balanced based qualifier, including nested __segname calls."""
    m = re.search(r'(?:__based|_based)\s*\(', text[start:])
    if not m:
        return text[start:].split()[0]
    at = start + m.start()
    op = text.find('(', at)
    depth, quote, escaped = 0, None, False
    for i in range(op, len(text)):
        ch = text[i]
        if quote:
            if escaped:
                escaped = False
            elif ch == '\\':
                escaped = True
            elif ch == quote:
                quote = None
        elif ch in '\"\'':
            quote = ch
        elif ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
            if depth == 0:
                return text[at:i + 1]
    return text[at:]


def map_dialect(text: str) -> str:
    """Map MSC declarator words to C qualifiers accepted by pycparser."""
    words = {'far': 'volatile', '_far': 'volatile', '__far': 'volatile',
             'near': 'const', '_near': 'const', 'huge': 'volatile const',
             '__segment': 'volatile', 'pascal': '', 'cdecl': ''}
    def replace_words(value):
        visible = csrc.mask_comments_and_strings(value)
        pattern = re.compile(r'\b(?:far|_far|__far|near|_near|huge|__segment|pascal|cdecl)\b')
        matches = list(pattern.finditer(visible))
        if not matches:
            return value
        out, cursor = [], 0
        for match in matches:
            out.append(value[cursor:match.start()])
            out.append(words[match.group(0)])
            cursor = match.end()
        out.append(value[cursor:])
        return ''.join(out)

    visible = csrc.mask_comments_and_strings(text)
    based = re.compile(r'\b(__based|_based)\s*\(')
    out, pos = [], 0
    for m in based.finditer(visible):
        if m.start() < pos:
            continue
        out.append(replace_words(text[pos:m.start()]))
        phrase = _based_phrase(text, m.start())
        out.append('volatile')
        pos = m.start() + len(phrase)
    out.append(replace_words(text[pos:]))
    return ''.join(out)


def map_far(text: str) -> str:
    """Compatibility alias used by typed mutations."""
    return map_dialect(text)


def dialect_roundtrip(text: str) -> str:
    """Round-trip all MSC dialect words through unique parser placeholders.

    This lexical adapter is also used by tests. Body parsing uses ``map_dialect`` so
    qualifiers remain visible to pycparser while originals are retained separately.
    """
    names = ('__based', '_based', '__segname', '__segment', '__far', '_far', 'far',
             'near', '_near', 'huge', 'pascal', 'cdecl', 'register', 'volatile')
    marker = {}
    out = text
    for i, name in enumerate(names):
        token = f'__CODEX_DIALECT_{i}__'
        marker[token] = name
        out = re.sub(r'\b' + re.escape(name) + r'\b', token, out)
    return re.sub('|'.join(map(re.escape, marker)), lambda m: marker[m.group(0)], out)


class TypeEnv:
    """Best-effort C type information for the target function (globals, prototypes,
    struct fields, parameters).  Built from a pycparser parse of the whole file with all
    function bodies stubbed; None if the file does not parse (then typed mutations skip)."""

    def __init__(self):
        self.globals, self.params, self.structs, self.typedefs = {}, {}, {}, {}

    @classmethod
    def build(cls, full_text, function):
        env = cls()
        try:
            text = csrc.strip_comments(csrc.stub_other_functions(full_text, '\0none'))
            if re.search(r'\b(volatile|restrict)\b', text) or UNSUPPORTED.search(text):
                return None
            ast = CParser().parse(map_far(text), filename='<file>')
        except Exception:
            return None
        for ext in ast.ext:
            if isinstance(ext, c_ast.Typedef):
                env.typedefs[ext.name] = ext.type
                env._collect_structs(ext.type)
            elif isinstance(ext, c_ast.Decl):
                env._collect_structs(ext.type)
                if ext.name:
                    env.globals[ext.name] = ext.type
            elif isinstance(ext, c_ast.FuncDef):
                env.globals[ext.decl.name] = ext.decl.type
                if ext.decl.name == function and ext.decl.type.args is not None:
                    for p in ext.decl.type.args.params:
                        if isinstance(p, c_ast.Decl) and p.name:
                            env.params[p.name] = p.type
        return env

    def _collect_structs(self, t):
        for n, *_ in walk(t):
            if isinstance(n, (c_ast.Struct, c_ast.Union)) and n.name and n.decls:
                self.structs[n.name] = {d.name: d.type for d in n.decls if isinstance(d, c_ast.Decl)}

    def resolve(self, t):
        """Strip typedef indirection for TypeDecl(IdentifierType([typedefname]))."""
        for _ in range(8):
            if isinstance(t, c_ast.TypeDecl) and isinstance(t.type, c_ast.IdentifierType) and \
                    len(t.type.names) == 1 and t.type.names[0] in self.typedefs:
                t = self.typedefs[t.type.names[0]]
            else:
                break
        return t

    def lookup(self, name, body):
        for n, *_ in walk(body):
            if isinstance(n, c_ast.Decl) and n.name == name:
                return n.type
        return self.params.get(name) or self.globals.get(name)

    def type_of(self, e, body):
        t = self._type_of(e, body)
        return self.resolve(t) if t is not None else None

    def _type_of(self, e, body):
        if isinstance(e, c_ast.ID):
            return self.lookup(e.name, body)
        if isinstance(e, c_ast.Cast):
            return e.to_type.type
        if isinstance(e, c_ast.FuncCall) and isinstance(e.name, c_ast.ID):
            ft = self.resolve(self.lookup(e.name.name, body))
            if isinstance(ft, c_ast.FuncDecl):
                return ft.type
            return None
        if isinstance(e, c_ast.ArrayRef):
            bt = self.type_of(e.name, body)
            if isinstance(bt, (c_ast.ArrayDecl, c_ast.PtrDecl)):
                return bt.type
            return None
        if isinstance(e, c_ast.StructRef):
            bt = self.type_of(e.name, body)
            if e.type == '->':
                bt = self.resolve(bt.type) if isinstance(bt, (c_ast.PtrDecl, c_ast.ArrayDecl)) else None
            if isinstance(bt, c_ast.TypeDecl) and isinstance(bt.type, (c_ast.Struct, c_ast.Union)):
                fields = self.structs.get(bt.type.name) or {}
                return fields.get(e.field.name)
            return None
        if isinstance(e, c_ast.UnaryOp):
            if e.op == '*':
                bt = self.type_of(e.expr, body)
                return bt.type if isinstance(bt, (c_ast.PtrDecl, c_ast.ArrayDecl)) else None
            if e.op in ('-', '~', '+'):
                return self._promote(self.type_of(e.expr, body))
            if e.op == '!':
                return _int_type()
            return None
        if isinstance(e, c_ast.BinaryOp):
            if e.op in ('<', '>', '<=', '>=', '==', '!=', '&&', '||'):
                return _int_type()
            lt, rt = self.type_of(e.left, body), self.type_of(e.right, body)
            if isinstance(e.right, c_ast.Constant) and rt is None:
                rt = _int_type()
            if isinstance(e.left, c_ast.Constant) and lt is None:
                lt = _int_type()
            if lt is None or rt is None:
                return None
            lp = isinstance(lt, (c_ast.PtrDecl, c_ast.ArrayDecl))
            rp = isinstance(rt, (c_ast.PtrDecl, c_ast.ArrayDecl))
            if e.op in ('+', '-') and (lp or rp):
                if lp and rp:
                    return _int_type()
                pt = lt if lp else rt
                return c_ast.PtrDecl([], pt.type) if isinstance(pt, c_ast.ArrayDecl) else pt
            if lp or rp:
                return None
            if e.op in ('<<', '>>'):
                return self._promote(lt)
            return self._arith(lt, rt)
        if isinstance(e, c_ast.Constant):
            return _int_type() if e.type == 'int' else None
        return None

    @staticmethod
    def _names(t):
        return t.type.names if isinstance(t, c_ast.TypeDecl) and isinstance(t.type, c_ast.IdentifierType) else None

    def _promote(self, t):
        names = self._names(t)
        if names is None:
            return None
        if 'long' in names:
            return t
        if names == ['unsigned'] or names in (['unsigned', 'int'], ['unsigned', 'short']):
            return c_ast.TypeDecl(None, [], None, c_ast.IdentifierType(['unsigned', 'int']))
        return _int_type()

    def _arith(self, a, b):
        na, nb = self._names(a), self._names(b)
        if na is None or nb is None:
            return None
        for names in (na, nb):
            if 'long' in names and 'unsigned' in names:
                return c_ast.TypeDecl(None, [], None, c_ast.IdentifierType(['unsigned', 'long']))
        for names in (na, nb):
            if 'long' in names:
                return c_ast.TypeDecl(None, [], None, c_ast.IdentifierType(['long']))
        pa, pb = self._promote(a), self._promote(b)
        if 'unsigned' in (self._names(pa) or []) or 'unsigned' in (self._names(pb) or []):
            return c_ast.TypeDecl(None, [], None, c_ast.IdentifierType(['unsigned', 'int']))
        return _int_type()


def _int_type():
    return c_ast.TypeDecl(None, [], None, c_ast.IdentifierType(['int']))


def decl_for(name, t):
    """Make a local Decl `name` of type t (a copy with the innermost declname set)."""
    t = copy.deepcopy(t)
    if isinstance(t, (c_ast.ArrayDecl, c_ast.FuncDecl)):
        return None
    inner = t
    while isinstance(inner, c_ast.PtrDecl):
        inner = inner.type
    if not isinstance(inner, c_ast.TypeDecl):
        return None
    if isinstance(inner.type, (c_ast.Struct, c_ast.Union)) and not isinstance(t, c_ast.PtrDecl):
        return None
    if isinstance(inner.type, c_ast.IdentifierType) and inner.type.names == ['void'] and t is inner:
        return None
    inner.declname = name
    if t is inner:
        # value type: drop const and MSC `far` (volatile-mapped) function/storage qualifiers
        inner.quals = [q for q in (inner.quals or []) if q not in ('const', 'volatile')]
    else:
        t.quals = [q for q in (t.quals or []) if q not in ('const', 'volatile', 'restrict')]
    return c_ast.Decl(name, [], None, [], [], t, None, None)


def local_hygiene(body):
    """Return a list of problems that would make a variant artificial: locals that are declared
    but never referenced (dummy locals) and names declared more than once (shadowing)."""
    decls = [n for n, *_ in walk(body) if isinstance(n, c_ast.Decl) and n.name
             and not isinstance(n.type, c_ast.FuncDecl) and 'extern' not in (n.storage or [])]
    uses = {}
    for n, *_ in walk(body):
        if isinstance(n, c_ast.ID):
            uses[n.name] = uses.get(n.name, 0) + 1
    problems = [f'unused local {d.name}' for d in decls if not uses.get(d.name)]
    names = [d.name for d in decls]
    problems += [f'duplicate/shadowed local {x}' for x in sorted({x for x in names if names.count(x) > 1})]
    return problems


def parse_function_text(ftext: str, typedefs):
    """Parse a function definition text (header + body) and return the body AST (for checks)."""
    loc = csrc.find_function(ftext, csrc.top_level_functions(ftext)[0]['name'])
    body = csrc.strip_comments(ftext[loc['body_start']:loc['body_end']])
    prelude = ''.join(f'typedef int {t};\n' for t in typedefs)
    ast = CParser().parse(prelude + 'void __permuter_target(void)\n' + map_far(body), filename='<fn>')
    return ast.ext[-1].body


def render_body(body, source='', line_offset=0) -> str:
    return FarGenerator.finish(FarGenerator(source, line_offset).visit(body))


def expr_text(node) -> str:
    try:
        return FarGenerator.finish(FarGenerator().visit(node)).strip()
    except Exception:
        return type(node).__name__


# ------------------------------------------------------------------ AST helpers

def walk(node, parent=None, attr=None, idx=None):
    """Yield (node, parent, attr, idx) depth-first (pre-order)."""
    yield node, parent, attr, idx
    for name, child in node.children():
        m = re.match(r'(\w+)\[(\d+)\]$', name)
        if m:
            a, i = m.group(1), int(m.group(2))
        else:
            a, i = name, None
        yield from walk(child, node, a, i)


def replace(parent, attr, idx, new):
    if idx is None:
        setattr(parent, attr, new)
    else:
        getattr(parent, attr)[idx] = new


def nodes_of(root, types):
    return [t for t in walk(root) if isinstance(t[0], types)]


def has_side_effects(node) -> bool:
    for n, *_ in walk(node):
        if isinstance(n, (c_ast.FuncCall, c_ast.Assignment)):
            return True
        if isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--', '++', '--'):
            return True
    return False


def ids_in(node):
    return {n.name for n, *_ in walk(node) if isinstance(n, c_ast.ID)}


def written_ids(node):
    out = set()
    for n, *_ in walk(node):
        target = None
        if isinstance(n, c_ast.Assignment):
            target = n.lvalue
        elif isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--', '++', '--'):
            target = n.expr
        if target is not None:
            if isinstance(target, c_ast.ID):
                out.add(target.name)
            else:
                out.add('*mem*')
    return out


def has_call(node):
    return any(isinstance(n, c_ast.FuncCall) for n, *_ in walk(node))


def contains(node, types, stop=()):
    """True if node contains a node of `types`, not descending into `stop` types."""
    for name, child in node.children():
        if isinstance(child, types):
            return True
        if isinstance(child, stop):
            continue
        if contains(child, types, stop):
            return True
    return False


LOOPS = (c_ast.For, c_ast.While, c_ast.DoWhile)


def loop_has_own_continue(stmt):
    return contains(stmt, (c_ast.Continue,), stop=LOOPS) or isinstance(stmt, c_ast.Continue)


def loop_has_own_break(stmt):
    return contains(stmt, (c_ast.Break,), stop=LOOPS + (c_ast.Switch,)) or isinstance(stmt, c_ast.Break)


def same(a, b):
    return expr_text(a) == expr_text(b)


def ends_in_jump(stmt):
    if isinstance(stmt, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto)):
        return True
    if isinstance(stmt, c_ast.Compound) and stmt.block_items:
        return ends_in_jump(stmt.block_items[-1])
    if isinstance(stmt, c_ast.If) and stmt.iffalse is not None:
        return ends_in_jump(stmt.iftrue) and ends_in_jump(stmt.iffalse)
    return False


def as_list(stmt):
    if isinstance(stmt, c_ast.Compound):
        return list(stmt.block_items or [])
    return [stmt]


def as_block(items):
    return c_ast.Compound(list(items))


INVERT = {'<': '>=', '>=': '<', '>': '<=', '<=': '>', '==': '!=', '!=': '=='}
MIRROR = {'<': '>', '>': '<', '<=': '>=', '>=': '<=', '==': '==', '!=': '!='}


def negate(e):
    if isinstance(e, c_ast.BinaryOp) and e.op in INVERT:
        return c_ast.BinaryOp(INVERT[e.op], e.left, e.right)
    if isinstance(e, c_ast.UnaryOp) and e.op == '!':
        return e.expr
    return c_ast.UnaryOp('!', e)


def cond_slots(root):
    """(parent, attr, idx) positions whose expression is used only for truth value."""
    out = []
    for n, p, a, i in walk(root):
        if isinstance(n, (c_ast.If, c_ast.While, c_ast.DoWhile)) and n.cond is not None:
            out.append((n, 'cond', None))
        elif isinstance(n, c_ast.For) and n.cond is not None:
            out.append((n, 'cond', None))
        elif isinstance(n, c_ast.TernaryOp):
            out.append((n, 'cond', None))
        elif isinstance(n, c_ast.BinaryOp) and n.op in ('&&', '||'):
            out.append((n, 'left', None))
            out.append((n, 'right', None))
        elif isinstance(n, c_ast.UnaryOp) and n.op == '!':
            out.append((n, 'expr', None))
    return out


def blocks(root):
    """All Compound nodes (statement lists)."""
    return [n for n, *_ in walk(root) if isinstance(n, c_ast.Compound)]


def stmt_positions(root):
    """(compound, index, stmt) for every statement directly inside a Compound."""
    out = []
    for comp in blocks(root):
        for k, s in enumerate(comp.block_items or []):
            out.append((comp, k, s))
    return out


def local_decls(root):
    out = []
    for comp in blocks(root):
        for k, s in enumerate(comp.block_items or []):
            if isinstance(s, c_ast.Decl) and not isinstance(s.type, c_ast.FuncDecl) and \
                    'extern' not in (s.storage or []) and 'static' not in (s.storage or []):
                out.append((comp, k, s))
    return out


def address_taken(root, name):
    for n, *_ in walk(root):
        if isinstance(n, c_ast.UnaryOp) and n.op == '&' and isinstance(n.expr, c_ast.ID) and n.expr.name == name:
            return True
    return False


def count_uses(root, name):
    return sum(1 for n, *_ in walk(root) if isinstance(n, c_ast.ID) and n.name == name)


def _volatile_type(t):
    return any(isinstance(n, (c_ast.TypeDecl, c_ast.PtrDecl, c_ast.ArrayDecl)) and
               'volatile' in (n.quals or []) for n, *_ in walk(t))


def volatile_names(body):
    names = {n.name for n, *_ in walk(body)
             if isinstance(n, c_ast.Decl) and n.name and _volatile_type(n.type)}
    if TYPE_ENV is not None:
        for name, t in TYPE_ENV.globals.items():
            if _volatile_type(t):
                names.add(name)
    return names


# ------------------------------------------------------------------ mutations
# Each takes (body, rng) and returns a description string or None.

def m_swap_commutative(body, rng):
    volatile = volatile_names(body)
    sites = [t for t in walk(body) if isinstance(t[0], c_ast.BinaryOp)
             # MSC7-E16/E17: addition association/order is folded before CSE;
             # spending C7 compiles on that spelling is a known no-op.
             and t[0].op in ('*', '&', '|', '^', '==', '!=')
             and not has_side_effects(t[0].left) and not has_side_effects(t[0].right)
             and not (ids_in(t[0].left) | ids_in(t[0].right)) & volatile]
    if not sites:
        return None
    n = rng.choice(sites)[0]
    before = expr_text(n)
    n.left, n.right = n.right, n.left
    return f'swap_commutative: {before}  ->  {expr_text(n)}'


def m_mirror_comparison(body, rng):
    volatile = volatile_names(body)
    sites = [t for t in walk(body) if isinstance(t[0], c_ast.BinaryOp) and t[0].op in MIRROR
             and not has_side_effects(t[0].left) and not has_side_effects(t[0].right)
             and not (ids_in(t[0].left) | ids_in(t[0].right)) & volatile]
    if not sites:
        return None
    n = rng.choice(sites)[0]
    before = expr_text(n)
    n.op = MIRROR[n.op]
    n.left, n.right = n.right, n.left
    return f'mirror_comparison: {before}  ->  {expr_text(n)}'


def m_invert_if(body, rng):
    sites = [t for t in walk(body) if isinstance(t[0], c_ast.If) and t[0].iffalse is not None
             and not isinstance(t[0].iffalse, c_ast.If)]
    sites += [t for t in walk(body) if isinstance(t[0], c_ast.If) and isinstance(t[0].iffalse, c_ast.If)
              and rng.random() < 0.3]
    if not sites:
        return None
    n = rng.choice(sites)[0]
    before = expr_text(n.cond)
    n.cond = negate(n.cond)
    t, f = n.iftrue, n.iffalse
    n.iftrue = f if isinstance(f, c_ast.Compound) else as_block([f])
    n.iffalse = t
    return f'invert_if: if ({before}) A else B  ->  if ({expr_text(n.cond)}) B else A'


def m_demorgan(body, rng):
    sites = [t for t in walk(body) if isinstance(t[0], c_ast.UnaryOp) and t[0].op == '!'
             and isinstance(t[0].expr, c_ast.BinaryOp) and t[0].expr.op in ('&&', '||')]
    sites += [t for t in walk(body) if isinstance(t[0], c_ast.BinaryOp) and t[0].op in ('&&', '||')
              and t[1] is not None]
    if not sites:
        return None
    n, p, a, i = rng.choice(sites)
    before = expr_text(n)
    if isinstance(n, c_ast.UnaryOp):
        inner = n.expr
        new = c_ast.BinaryOp('||' if inner.op == '&&' else '&&', negate(inner.left), negate(inner.right))
    else:
        new = c_ast.UnaryOp('!', c_ast.BinaryOp('||' if n.op == '&&' else '&&', negate(n.left), negate(n.right)))
    replace(p, a, i, new)
    return f'demorgan: {before}  ->  {expr_text(new)}'


def m_cond_zero(body, rng):
    slots = cond_slots(body)
    cands = []
    for parent, attr, idx in slots:
        e = getattr(parent, attr)
        if isinstance(e, c_ast.BinaryOp) and e.op in ('!=', '==') and isinstance(e.right, c_ast.Constant) \
                and e.right.value in ('0', '0L', '0x0', '0u', '0U'):
            cands.append((parent, attr, 'drop'))
        elif isinstance(e, c_ast.UnaryOp) and e.op == '!' and not (
                isinstance(e.expr, c_ast.BinaryOp) and e.expr.op in ('&&', '||', '<', '>', '<=', '>=', '==', '!=')) \
                and not (isinstance(e.expr, c_ast.UnaryOp) and e.expr.op == '!'):
            cands.append((parent, attr, 'not_to_eq'))   # only for value operands: `!x` -> `x == 0`
        elif isinstance(e, (c_ast.ID, c_ast.StructRef, c_ast.ArrayRef, c_ast.FuncCall)) or \
                (isinstance(e, c_ast.UnaryOp) and e.op == '*') or \
                (isinstance(e, c_ast.BinaryOp) and e.op in ('&', '|', '^', '+', '-')) or \
                (isinstance(e, c_ast.Assignment)):
            cands.append((parent, attr, 'add'))
    if not cands:
        return None
    parent, attr, kind = rng.choice(cands)
    e = getattr(parent, attr)
    before = expr_text(e)
    if kind == 'drop':
        new = e.left if e.op == '!=' else c_ast.UnaryOp('!', e.left)
    elif kind == 'not_to_eq':
        new = c_ast.BinaryOp('==', e.expr, c_ast.Constant('int', '0'))
    else:
        new = c_ast.BinaryOp('!=', e, c_ast.Constant('int', '0'))
    setattr(parent, attr, new)
    return f'cond_zero: {before}  ->  {expr_text(new)}'


def m_for_to_while(body, rng):
    sites = [(c, k, s) for c, k, s in stmt_positions(body) if isinstance(s, c_ast.For)
             and not isinstance(s.init, c_ast.DeclList) and not loop_has_own_continue(s.stmt)]
    if not sites:
        return None
    comp, k, f = rng.choice(sites)
    items = as_list(f.stmt)
    if f.next is not None:
        items.append(f.next)
    cond = f.cond if f.cond is not None else c_ast.Constant('int', '1')
    loop = c_ast.While(cond, as_block(items))
    new = ([f.init] if f.init is not None else []) + [loop]
    comp.block_items[k:k + 1] = new
    return f'for_to_while: for ({expr_text(f.init) if f.init else ""}; {expr_text(cond)}; ...)'


def m_while_to_for(body, rng):
    sites = []
    for c, k, s in stmt_positions(body):
        if isinstance(s, c_ast.While):
            sites.append((c, k, s))
    if not sites:
        return None
    comp, k, w = rng.choice(sites)
    items = as_list(w.stmt)
    init = nxt = None
    # absorb the preceding assignment and the trailing step when they concern the same variable
    prev = comp.block_items[k - 1] if k > 0 else None
    last = items[-1] if items else None
    if prev is not None and isinstance(prev, c_ast.Assignment) and isinstance(prev.lvalue, c_ast.ID) and \
            last is not None and not loop_has_own_continue(w.stmt) and rng.random() < 0.8:
        v = prev.lvalue.name
        lw = written_ids(last)
        if (isinstance(last, c_ast.UnaryOp) and last.op in ('p++', 'p--', '++', '--')
                or isinstance(last, c_ast.Assignment)) and lw == {v}:
            init, nxt = prev, last
            items = items[:-1]
    cond = w.cond
    if isinstance(cond, c_ast.Constant) and cond.value == '1':
        cond = None
    loop = c_ast.For(init, cond, nxt, as_block(items))
    if init is not None:
        comp.block_items[k - 1:k + 1] = [loop]
    else:
        comp.block_items[k] = loop
    return f'while_to_for: while ({expr_text(w.cond)}) -> for ({expr_text(init) if init else ""};...;{expr_text(nxt) if nxt else ""})'


def m_while_to_dowhile(body, rng):
    sites = [(c, k, s) for c, k, s in stmt_positions(body) if isinstance(s, c_ast.While)
             and not (isinstance(s.cond, c_ast.Constant))]
    if not sites:
        return None
    comp, k, w = rng.choice(sites)
    comp.block_items[k] = c_ast.If(copy.deepcopy(w.cond), c_ast.DoWhile(w.cond, w.stmt), None)
    return f'while_to_dowhile: while ({expr_text(w.cond)}) S -> if (c) do S while (c)'


def m_dowhile_to_while(body, rng):
    sites = []
    for c, k, s in stmt_positions(body):
        if isinstance(s, c_ast.If) and s.iffalse is None:
            inner = s.iftrue
            if isinstance(inner, c_ast.Compound) and len(inner.block_items or []) == 1:
                inner = inner.block_items[0]
            if isinstance(inner, c_ast.DoWhile) and same(inner.cond, s.cond):
                sites.append((c, k, s, inner))
    if not sites:
        return None
    comp, k, s, inner = rng.choice(sites)
    comp.block_items[k] = c_ast.While(inner.cond, inner.stmt)
    return f'dowhile_to_while: if (c) do S while (c) -> while ({expr_text(s.cond)}) S'


def _incdec_forms(e):
    """For a statement-level ++/--/+=1/-=1/x=x+1 expression, return (var, delta) or None."""
    if isinstance(e, c_ast.UnaryOp) and e.op in ('p++', '++', 'p--', '--'):
        return e.expr, (1 if '+' in e.op else -1)
    if isinstance(e, c_ast.Assignment) and e.op in ('+=', '-=') and isinstance(e.rvalue, c_ast.Constant) \
            and e.rvalue.value == '1':
        return e.lvalue, (1 if e.op == '+=' else -1)
    if isinstance(e, c_ast.Assignment) and e.op == '=' and isinstance(e.rvalue, c_ast.BinaryOp) and \
            e.rvalue.op in ('+', '-') and isinstance(e.rvalue.right, c_ast.Constant) and \
            e.rvalue.right.value == '1' and same(e.rvalue.left, e.lvalue):
        return e.lvalue, (1 if e.rvalue.op == '+' else -1)
    return None


def m_incdec_style(body, rng):
    sites = []
    for c, k, s in stmt_positions(body):
        if _incdec_forms(s) and not has_side_effects(_incdec_forms(s)[0]):
            sites.append((c, 'block_items', k, s))
    for n, *_ in walk(body):
        if isinstance(n, c_ast.For) and n.next is not None and _incdec_forms(n.next) \
                and not has_side_effects(_incdec_forms(n.next)[0]):
            sites.append((n, 'next', None, n.next))
    if not sites:
        return None
    parent, attr, idx, e = rng.choice(sites)
    var, d = _incdec_forms(e)
    forms = [c_ast.UnaryOp('p++' if d > 0 else 'p--', var), c_ast.UnaryOp('++' if d > 0 else '--', var),
             c_ast.Assignment('+=' if d > 0 else '-=', var, c_ast.Constant('int', '1')),
             c_ast.Assignment('=', var, c_ast.BinaryOp('+' if d > 0 else '-', copy.deepcopy(var),
                                                       c_ast.Constant('int', '1')))]
    before = expr_text(e)
    forms = [f for f in forms if expr_text(f) != before]
    new = rng.choice(forms)
    replace(parent, attr, idx, new)
    return f'incdec_style: {before} -> {expr_text(new)}'


def m_compound_assign(body, rng):
    sites = []
    for n, p, a, i in walk(body):
        if isinstance(n, c_ast.Assignment) and n.op == '=' and isinstance(n.rvalue, c_ast.BinaryOp) and \
                n.rvalue.op in ('+', '-', '*', '&', '|', '^', '<<', '>>', '/', '%') and \
                isinstance(n.lvalue, c_ast.ID) and same(n.rvalue.left, n.lvalue) and \
                not has_side_effects(n.lvalue) and not has_side_effects(n.rvalue.right):
            sites.append(('to_compound', n))
        elif isinstance(n, c_ast.Assignment) and n.op in ('+=', '-=', '*=', '&=', '|=', '^=', '<<=', '>>=', '/=', '%=') \
                and isinstance(n.lvalue, c_ast.ID) and not has_side_effects(n.lvalue) \
                and not has_side_effects(n.rvalue):
            sites.append(('to_plain', n))
    if not sites:
        return None
    kind, n = rng.choice(sites)
    before = expr_text(n)
    if kind == 'to_compound':
        n.op = n.rvalue.op + '='
        n.rvalue = n.rvalue.right
    else:
        op = n.op[:-1]
        n.rvalue = c_ast.BinaryOp(op, copy.deepcopy(n.lvalue), n.rvalue)
        n.op = '='
    return f'compound_assign: {before} -> {expr_text(n)}'


def m_decl_order(body, rng):
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            a, b = items[k], items[k + 1]
            if isinstance(a, c_ast.Decl) and isinstance(b, c_ast.Decl):
                if b.init is not None and a.name in ids_in(b.init):
                    continue
                if a.init is not None and b.init is not None and (has_side_effects(a.init) or has_side_effects(b.init)):
                    continue
                sites.append((comp, k))
    if not sites:
        return None
    comp, k = rng.choice(sites)
    items = comp.block_items
    items[k], items[k + 1] = items[k + 1], items[k]
    return f'decl_order: swap {items[k + 1].name} <-> {items[k].name}'


def _is_scalar_decl(d):
    return isinstance(d.type, (c_ast.TypeDecl, c_ast.PtrDecl)) and \
        not (isinstance(d.type, c_ast.TypeDecl) and isinstance(d.type.type, (c_ast.Struct, c_ast.Union)))


def m_register_toggle(body, rng):
    sites = []
    for c, k, d in local_decls(body):
        t = d.type
        while isinstance(t, c_ast.ArrayDecl):
            t = t.type
        if not isinstance(t, c_ast.TypeDecl) or 'long' in getattr(t.type, 'names', []) or \
                not _is_scalar_decl(d) or address_taken(body, d.name):
            continue
        sites.append((c, k, d))
    if not sites:
        return None
    _, _, d = rng.choice(sites)
    st = list(d.storage or [])
    if 'register' in st:
        st.remove('register')
        d.storage = st
        return f'register_toggle: remove register from {d.name}'
    d.storage = st + ['register']
    return f'register_toggle: add register to {d.name}'


TYPE_SAFE = [(['int'], ['short']), (['unsigned', 'int'], ['unsigned', 'short']),
             (['unsigned', 'int'], ['unsigned']), (['unsigned', 'short'], ['unsigned']),
             (['short'], ['short', 'int']), (['long'], ['long', 'int'])]
TYPE_RISKY = [(['int'], ['unsigned', 'int']), (['short'], ['unsigned', 'short']), (['char'], ['unsigned', 'char']),
              (['int'], ['char']), (['unsigned', 'int'], ['unsigned', 'char']), (['short'], ['char']),
              (['unsigned', 'short'], ['unsigned', 'char']), (['long'], ['unsigned', 'long']),
              (['int'], ['unsigned']), (['char'], ['int']), (['unsigned', 'char'], ['unsigned', 'int'])]


def _type_change(body, rng, table, tag):
    sites = []
    for c, k, d in local_decls(body):
        t = d.type
        while isinstance(t, (c_ast.PtrDecl, c_ast.ArrayDecl)):
            if isinstance(t, c_ast.PtrDecl):
                t = None  # pointee type changes are not local-value type changes
                break
            t = t.type
        if isinstance(t, c_ast.TypeDecl) and isinstance(t.type, c_ast.IdentifierType):
            names = t.type.names
            for a, b in table:
                if names == a:
                    sites.append((d, t.type, b))
                elif names == b:
                    sites.append((d, t.type, a))
    if not sites:
        return None
    d, it, new = rng.choice(sites)
    before = ' '.join(it.names)
    it.names = list(new)
    return f'{tag}: {d.name}: {before} -> {" ".join(new)}'


def m_type_safe(body, rng):
    return _type_change(body, rng, TYPE_SAFE, 'type_spelling')


def m_type_risky(body, rng):
    return _type_change(body, rng, TYPE_RISKY, 'type_change(RISKY)')


def m_sink_decl(body, rng):
    """Move an uninitialised top-level local into the single nested block that uses it."""
    sites = []
    top = body.block_items or []
    for k, d in enumerate(top):
        if not isinstance(d, c_ast.Decl) or d.init is not None or not _is_scalar_decl(d):
            continue
        name = d.name
        users = [s for s in top if s is not d and name in ids_in(s)]
        if len(users) != 1:
            continue
        # innermost compound containing all uses where first use is a plain assignment statement
        inner = [n for n, *_ in walk(users[0]) if isinstance(n, c_ast.Compound) and name in ids_in(n)]
        for comp in inner:
            if count_uses(comp, name) != count_uses(users[0], name):
                continue
            first = next((s for s in comp.block_items or [] if name in ids_in(s)), None)
            if isinstance(first, c_ast.Assignment) and first.op == '=' and isinstance(first.lvalue, c_ast.ID) \
                    and first.lvalue.name == name and name not in ids_in(first.rvalue):
                sites.append((k, d, comp))
    if not sites:
        return None
    k, d, comp = rng.choice(sites)
    body.block_items.remove(d)
    items = comp.block_items
    pos = 0
    while pos < len(items) and isinstance(items[pos], c_ast.Decl):
        pos += 1
    items.insert(pos, d)
    return f'sink_decl: {d.name} into nested block'


def m_hoist_decl(body, rng):
    top_names = {d.name for d in body.block_items or [] if isinstance(d, c_ast.Decl)}
    all_decl_names = [n.name for n, *_ in walk(body) if isinstance(n, c_ast.Decl)]
    sites = []
    for comp in blocks(body):
        if comp is body:
            continue
        for d in comp.block_items or []:
            if isinstance(d, c_ast.Decl) and d.init is None and d.name not in top_names and \
                    all_decl_names.count(d.name) == 1 and 'static' not in (d.storage or []):
                sites.append((comp, d))
    if not sites:
        return None
    comp, d = rng.choice(sites)
    comp.block_items.remove(d)
    items = body.block_items
    pos = 0
    while pos < len(items) and isinstance(items[pos], c_ast.Decl):
        pos += 1
    items.insert(rng.randint(0, pos), d)
    return f'hoist_decl: {d.name} to function scope'


def m_const_bound(body, rng):
    sites = []
    for n, *_ in walk(body):
        if isinstance(n, c_ast.BinaryOp) and n.op in ('<', '<=', '>', '>=') and isinstance(n.right, c_ast.Constant) \
                and n.right.type == 'int' and re.fullmatch(r'(0x[0-9a-fA-F]+|\d+)', n.right.value):
            v = int(n.right.value, 0)
            if 0 < v < 0x7fff:
                sites.append(n)
    if not sites:
        return None
    n = rng.choice(sites)
    before = expr_text(n)
    v = int(n.right.value, 0)
    hexa = n.right.value.lower().startswith('0x')
    fmt = (lambda x: hex(x)) if hexa else str
    if n.op == '<':
        n.op, v = '<=', v - 1
    elif n.op == '<=':
        n.op, v = '<', v + 1
    elif n.op == '>':
        n.op, v = '>=', v + 1
    else:
        n.op, v = '>', v - 1
    n.right = c_ast.Constant('int', fmt(v))
    return f'const_bound(RISKY): {before} -> {expr_text(n)}'


def _case_groups(sw):
    comp = sw.stmt
    if not isinstance(comp, c_ast.Compound):
        return None
    items = comp.block_items or []
    if not all(isinstance(x, (c_ast.Case, c_ast.Default)) for x in items):
        return None
    groups, cur = [], []
    for x in items:
        cur.append(x)
        if x.stmts:
            groups.append(cur)
            cur = []
    if cur:
        groups.append(cur)
    return groups


def m_switch_reorder(body, rng):
    sites = []
    for n, *_ in walk(body):
        if isinstance(n, c_ast.Switch):
            g = _case_groups(n)
            if not g or len(g) < 2:
                continue
            for k in range(len(g) - 1):
                a, b = g[k], g[k + 1]
                if a[-1].stmts and b[-1].stmts and ends_in_jump(as_block(a[-1].stmts)) and \
                        (ends_in_jump(as_block(b[-1].stmts)) or k + 1 == len(g) - 1):
                    if k + 1 == len(g) - 1 and not ends_in_jump(as_block(b[-1].stmts)):
                        continue
                    sites.append((n, g, k))
    if not sites:
        return None
    sw, g, k = rng.choice(sites)
    g[k], g[k + 1] = g[k + 1], g[k]
    sw.stmt.block_items = [x for grp in g for x in grp]
    labels = lambda grp: ','.join(expr_text(x.expr) if isinstance(x, c_ast.Case) else 'default' for x in grp)
    return f'switch_reorder: swap case {labels(g[k + 1])} <-> {labels(g[k])}'


def m_index_pointer(body, rng):
    def e22_scaled_index(expr):
        """MSC7-E22's scaled 2-D address spellings are one canonical tree."""
        for node, *_ in walk(expr):
            if isinstance(node, c_ast.BinaryOp) and node.op == '*':
                if ((isinstance(node.left, c_ast.Constant) and node.left.value in ('8', '0x8') or
                     isinstance(node.right, c_ast.Constant) and node.right.value in ('8', '0x8'))):
                    return True
            if isinstance(node, c_ast.BinaryOp) and node.op == '<<' and \
                    isinstance(node.right, c_ast.Constant) and node.right.value in ('3', '0x3'):
                return True
        return False

    sites = []
    for n, p, a, i in walk(body):
        if p is None:
            continue
        if isinstance(n, c_ast.ArrayRef) and not (e22_scaled_index(n.subscript) or e22_scaled_index(n.name)):
            sites.append(('arr_to_ptr', n, p, a, i))
        elif isinstance(n, c_ast.UnaryOp) and n.op == '*' and isinstance(n.expr, c_ast.BinaryOp) \
                and n.expr.op == '+' and not e22_scaled_index(n.expr):
            sites.append(('ptr_to_arr', n, p, a, i))
        elif isinstance(n, c_ast.UnaryOp) and n.op == '&' and isinstance(n.expr, c_ast.ArrayRef):
            sites.append(('addr_to_sum', n, p, a, i))
        elif isinstance(n, c_ast.UnaryOp) and n.op == '*' and isinstance(n.expr, (c_ast.ID,)):
            sites.append(('deref_to_index0', n, p, a, i))
        if isinstance(n, c_ast.ArrayRef) and isinstance(n.subscript, c_ast.Constant) and n.subscript.value == '0':
            sites += [('index0_to_deref', n, p, a, i)] * 3
    if not sites:
        return None
    kind, n, p, a, i = rng.choice(sites)
    before = expr_text(n)
    if kind == 'arr_to_ptr':
        new = c_ast.UnaryOp('*', c_ast.BinaryOp('+', n.name, n.subscript))
    elif kind == 'ptr_to_arr':
        new = c_ast.ArrayRef(n.expr.left, n.expr.right)
    elif kind == 'addr_to_sum':
        new = c_ast.BinaryOp('+', n.expr.name, n.expr.subscript)
    elif kind == 'index0_to_deref':
        new = c_ast.UnaryOp('*', n.name)
    else:
        new = c_ast.ArrayRef(n.expr, c_ast.Constant('int', '0'))
    replace(p, a, i, new)
    return f'index_pointer: {before} -> {expr_text(new)}'


def m_split_merge_and(body, rng):
    sites = []
    for c, k, s in stmt_positions(body):
        if isinstance(s, c_ast.If) and s.iffalse is None:
            if isinstance(s.cond, c_ast.BinaryOp) and s.cond.op == '&&':
                sites.append(('split', c, k, s))
            inner = s.iftrue
            if isinstance(inner, c_ast.Compound) and len(inner.block_items or []) == 1:
                inner = inner.block_items[0]
            if isinstance(inner, c_ast.If) and inner.iffalse is None:
                sites.append(('merge', c, k, s))
    if not sites:
        return None
    kind, comp, k, s = rng.choice(sites)
    before = expr_text(s.cond)
    if kind == 'split':
        comp.block_items[k] = c_ast.If(s.cond.left, as_block([c_ast.If(s.cond.right, s.iftrue, None)]), None)
        return f'split_and: if ({before}) -> nested ifs'
    inner = s.iftrue
    if isinstance(inner, c_ast.Compound):
        inner = inner.block_items[0]
    comp.block_items[k] = c_ast.If(c_ast.BinaryOp('&&', s.cond, inner.cond), inner.iftrue, None)
    return f'merge_and: nested ifs -> if ({before} && {expr_text(inner.cond)})'


def m_ternary(body, rng):
    sites = []
    for c, k, s in stmt_positions(body):
        if isinstance(s, c_ast.If) and s.iffalse is not None:
            a = as_list(s.iftrue)
            b = as_list(s.iffalse)
            if len(a) == 1 and len(b) == 1:
                x, y = a[0], b[0]
                if isinstance(x, c_ast.Assignment) and isinstance(y, c_ast.Assignment) and x.op == y.op == '=' \
                        and same(x.lvalue, y.lvalue) and not has_side_effects(x.lvalue):
                    sites.append(('if_to_ternary_assign', c, k, s))
                elif isinstance(x, c_ast.Return) and isinstance(y, c_ast.Return) and x.expr is not None \
                        and y.expr is not None:
                    sites.append(('if_to_ternary_return', c, k, s))
        elif isinstance(s, c_ast.Assignment) and s.op == '=' and isinstance(s.rvalue, c_ast.TernaryOp) \
                and not has_side_effects(s.lvalue):
            sites.append(('ternary_to_if_assign', c, k, s))
        elif isinstance(s, c_ast.Return) and isinstance(s.expr, c_ast.TernaryOp):
            sites.append(('ternary_to_if_return', c, k, s))
    if not sites:
        return None
    kind, comp, k, s = rng.choice(sites)
    if kind == 'if_to_ternary_assign':
        x, y = as_list(s.iftrue)[0], as_list(s.iffalse)[0]
        comp.block_items[k] = c_ast.Assignment('=', x.lvalue, c_ast.TernaryOp(s.cond, x.rvalue, y.rvalue))
    elif kind == 'if_to_ternary_return':
        x, y = as_list(s.iftrue)[0], as_list(s.iffalse)[0]
        comp.block_items[k] = c_ast.Return(c_ast.TernaryOp(s.cond, x.expr, y.expr))
    elif kind == 'ternary_to_if_assign':
        t = s.rvalue
        comp.block_items[k] = c_ast.If(t.cond, c_ast.Assignment('=', s.lvalue, t.iftrue),
                                       c_ast.Assignment('=', copy.deepcopy(s.lvalue), t.iffalse))
    else:
        t = s.expr
        comp.block_items[k] = c_ast.If(t.cond, c_ast.Return(t.iftrue), c_ast.Return(t.iffalse))
    return f'ternary: {kind}'


def m_else_layout(body, rng):
    """if (c) {..jump} else E; <-> if (c) {..jump} E;"""
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k, s in enumerate(items):
            if isinstance(s, c_ast.If) and ends_in_jump(s.iftrue):
                if s.iffalse is not None and not isinstance(s.iffalse, c_ast.If):
                    # E's declarations would change scope; skip when E declares locals
                    if not any(isinstance(x, c_ast.Decl) for x in as_list(s.iffalse)):
                        sites.append(('drop_else', comp, k, s))
                elif s.iffalse is None and k + 1 < len(items) and \
                        not any(isinstance(x, (c_ast.Decl, c_ast.Label)) for x in items[k + 1:]):
                    sites.append(('add_else', comp, k, s))
    if not sites:
        return None
    kind, comp, k, s = rng.choice(sites)
    if kind == 'drop_else':
        rest = as_list(s.iffalse)
        s.iffalse = None
        comp.block_items[k + 1:k + 1] = rest
        return f'else_layout: drop else after jumping branch of if ({expr_text(s.cond)})'
    rest = comp.block_items[k + 1:]
    del comp.block_items[k + 1:]
    s.iffalse = as_block(rest)
    return f'else_layout: wrap following statements into else of if ({expr_text(s.cond)})'


def _effects(stmt):
    return ids_in(stmt), written_ids(stmt), has_call(stmt)


def m_stmt_swap(body, rng):
    volatile = volatile_names(body)
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            a, b = items[k], items[k + 1]
            if isinstance(a, (c_ast.Decl, c_ast.Label, c_ast.Case, c_ast.Default)) or \
                    isinstance(b, (c_ast.Decl, c_ast.Label, c_ast.Case, c_ast.Default)):
                continue
            if contains(a, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto, c_ast.Label)) or \
                    isinstance(a, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto)) or \
                    contains(b, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto, c_ast.Label)) or \
                    isinstance(b, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto)):
                continue
            ra, wa, ca = _effects(a)
            rb, wb, cb = _effects(b)
            if ca or cb:
                continue
            if (ra | wa | rb | wb) & volatile:
                continue
            if wa & (rb | wb) or wb & ra:
                continue
            if '*mem*' in wa | wb:
                continue
            sites.append((comp, k))
    if not sites:
        return None
    comp, k = rng.choice(sites)
    items = comp.block_items
    items[k], items[k + 1] = items[k + 1], items[k]
    return f'stmt_swap: {expr_text(items[k + 1])[:40]!r} <-> {expr_text(items[k])[:40]!r}'


def m_inline_temp(body, rng):
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            s, nxt = items[k], items[k + 1]
            if isinstance(s, c_ast.Assignment) and s.op == '=' and isinstance(s.lvalue, c_ast.ID):
                name = s.lvalue.name
                if count_uses(body, name) != 2 or count_uses(nxt, name) != 1 or address_taken(body, name):
                    continue
                if has_side_effects(s.rvalue):
                    continue
                if (written_ids(nxt) & ids_in(s.rvalue)) or ('*mem*' in written_ids(nxt) and
                                                             not isinstance(s.rvalue, (c_ast.ID, c_ast.Constant))):
                    continue
                sites.append((comp, k, name))
    if not sites:
        return None
    comp, k, name = rng.choice(sites)
    s = comp.block_items[k]
    nxt = comp.block_items[k + 1]
    for n, p, a, i in walk(nxt):
        if isinstance(n, c_ast.ID) and n.name == name:
            replace(p, a, i, s.rvalue)
            break
    del comp.block_items[k]
    # drop the now-unused declaration
    for c2 in blocks(body):
        c2.block_items = [x for x in (c2.block_items or [])
                          if not (isinstance(x, c_ast.Decl) and x.name == name and x.init is None)]
    return f'inline_temp: {name} = {expr_text(s.rvalue)[:40]}'


def reads_memory(e):
    return any(isinstance(n, (c_ast.ArrayRef, c_ast.StructRef)) or
               (isinstance(n, c_ast.UnaryOp) and n.op == '*') for n, *_ in walk(e))


def _conditional_positions(stmt):
    """ids of nodes evaluated conditionally inside stmt (right of &&/||, ternary arms, sizeof)."""
    out = set()
    for n, *_ in walk(stmt):
        subs = []
        if isinstance(n, c_ast.BinaryOp) and n.op in ('&&', '||'):
            subs = [n.right]
        elif isinstance(n, c_ast.TernaryOp):
            subs = [n.iftrue, n.iffalse]
        elif isinstance(n, c_ast.UnaryOp) and n.op == 'sizeof':
            subs = [n.expr]
        for s in subs:
            out.update(id(x) for x, *_ in walk(s))
    return out


TEMP_NAMES = {'call': ['result', 'value', 'status'], 'ptr': ['ptr', 'entry', 'item', 'base'],
              'index': ['index', 'offset', 'pos', 'value'], 'value': ['value', 'item', 'entry', 'temp']}


def m_introduce_temp(body, rng):
    """Hoist a typed subexpression of a statement into a new, naturally named local."""
    env = TYPE_ENV
    if env is None:
        return None
    used_names = {n.name for n, *_ in walk(body) if isinstance(n, (c_ast.ID, c_ast.Decl)) and getattr(n, 'name', None)}
    used_names |= set(env.globals) | set(env.params)
    sites = []
    for comp, k, s in stmt_positions(body):
        if isinstance(s, (c_ast.Assignment, c_ast.FuncCall, c_ast.UnaryOp, c_ast.Return)):
            region = s
        elif isinstance(s, (c_ast.If, c_ast.Switch)):
            region = s.cond
        else:
            continue
        if region is None:
            continue
        cond_ids = _conditional_positions(region)
        top_target = s.lvalue if isinstance(s, c_ast.Assignment) else None
        for e, p, a, i in walk(region):
            if p is None:
                if region is s:
                    continue  # the statement itself
                p, a, i = s, 'cond', None
            if id(e) in cond_ids or e is top_target:
                continue
            if not isinstance(e, (c_ast.FuncCall, c_ast.ArrayRef, c_ast.StructRef, c_ast.BinaryOp)):
                continue
            if isinstance(p, c_ast.UnaryOp) and p.op in ('&', '++', '--', 'p++', 'p--', 'sizeof'):
                continue
            if isinstance(p, c_ast.Assignment) and a == 'lvalue':
                continue
            if p is s and isinstance(s, c_ast.Assignment) and a == 'rvalue':
                continue  # `t = E; v = t;` is a pure copy temp, not a natural rewrite
            if isinstance(e, c_ast.BinaryOp) and e.op in ('&&', '||', '<', '>', '<=', '>=', '==', '!='):
                continue
            if isinstance(p, c_ast.ExprList) and isinstance(e, c_ast.BinaryOp) and rng.random() < 0.5:
                continue
            t = env.type_of(e, body)
            if t is None:
                continue
            if isinstance(e, c_ast.FuncCall):
                rest_effects = has_side_effects_except(s, e, top_target)
                if rest_effects:
                    continue
            else:
                if has_side_effects(e):
                    continue
                w = written_ids_except(s, top_target)
                if w & ids_in(e) or ('*mem*' in w and reads_memory(e)):
                    continue
            sites.append((comp, k, s, e, p, a, i, t))
    if not sites:
        return None
    comp, k, s, e, p, a, i, t = rng.choice(sites)
    kind = 'call' if isinstance(e, c_ast.FuncCall) else ('ptr' if isinstance(t, c_ast.PtrDecl) else
                                                        ('index' if isinstance(e, c_ast.BinaryOp) else 'value'))
    names = [n for n in TEMP_NAMES[kind] if n not in used_names]
    if not names:
        return None
    name = rng.choice(names)
    decl = decl_for(name, t)
    if decl is None:
        return None
    text_e = expr_text(e)
    replace(p, a, i, c_ast.ID(name))
    count = 1
    if not isinstance(e, c_ast.FuncCall) and rng.random() < 0.5:
        for n2, p2, a2, i2 in list(walk(s)):
            if p2 is not None and not isinstance(n2, c_ast.ID) and expr_text(n2) == text_e:
                replace(p2, a2, i2, c_ast.ID(name))
                count += 1
    comp.block_items.insert(k, c_ast.Assignment('=', c_ast.ID(name), e))
    items = body.block_items
    pos = 0
    while pos < len(items) and isinstance(items[pos], c_ast.Decl):
        pos += 1
    items.insert(rng.randint(0, pos), decl)
    return f'introduce_temp: {name} = {text_e[:50]} (x{count})'


def has_side_effects_except(stmt, skip, top_target):
    for n, *_ in walk(stmt):
        if n is skip:
            continue
        if any(n is x for x, *_ in walk(skip)):
            continue
        if isinstance(n, c_ast.FuncCall):
            return True
        if isinstance(n, c_ast.Assignment) and n is not stmt:
            return True
        if isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--', '++', '--'):
            return True
    return False


def written_ids_except(stmt, top_target):
    w = set()
    for n, *_ in walk(stmt):
        target = None
        if isinstance(n, c_ast.Assignment) and n.lvalue is not top_target:
            target = n.lvalue
        elif isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--', '++', '--'):
            target = n.expr
        if target is not None:
            w.add(target.name if isinstance(target, c_ast.ID) else '*mem*')
    return w


def m_inline_temp_multi(body, rng):
    """Replace every use of a once-assigned temp by its (pure) defining expression."""
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k, s in enumerate(items):
            if not (isinstance(s, c_ast.Assignment) and s.op == '=' and isinstance(s.lvalue, c_ast.ID)):
                continue
            name = s.lvalue.name
            if has_side_effects(s.rvalue) or name in ids_in(s.rvalue) or address_taken(body, name):
                continue
            decls = [n for n, *_ in walk(body) if isinstance(n, c_ast.Decl) and n.name == name]
            if len(decls) != 1 or decls[0].init is not None:
                continue
            total = count_uses(body, name)
            # all other uses must lie in the following statements of this block, which must not
            # write the temp, the expression's variables, or memory the expression reads
            later = items[k + 1:]
            later_uses = sum(count_uses(x, name) for x in later)
            if later_uses == 0 or total != later_uses + 1:
                continue
            ok = True
            deps = ids_in(s.rvalue) | {name}
            last = max(j for j, x in enumerate(later) if count_uses(x, name))
            for x in later[:last + 1]:
                w = written_ids(x)
                if w & deps or ('*mem*' in w and reads_memory(s.rvalue)) or \
                        isinstance(x, LOOPS) and count_uses(x, name) and has_call(x) and reads_memory(s.rvalue):
                    ok = False
                    break
                if has_call(x) and reads_memory(s.rvalue) and x is not later[last]:
                    ok = False
                    break
            if ok:
                sites.append((comp, k, name, decls[0]))
    if not sites:
        return None
    comp, k, name, decl = rng.choice(sites)
    s = comp.block_items[k]
    n_rep = 0
    for x in comp.block_items[k + 1:]:
        for n, p, a, i in list(walk(x)):
            if isinstance(n, c_ast.ID) and n.name == name and p is not None:
                replace(p, a, i, copy.deepcopy(s.rvalue))
                n_rep += 1
    del comp.block_items[k]
    for c2 in blocks(body):
        c2.block_items = [x for x in (c2.block_items or []) if x is not decl]
    return f'inline_temp_multi: {name} := {expr_text(s.rvalue)[:40]} ({n_rep} uses)'


def m_chain_assign(body, rng):
    def plain_distinct(a, b):
        if not (isinstance(a, c_ast.ID) and isinstance(b, c_ast.ID)) or a.name == b.name:
            return False
        if TYPE_ENV is not None:
            for name in (a.name, b.name):
                t = TYPE_ENV.lookup(name, body)
                if t is not None and _volatile_type(t):
                    return False
        for node, *_ in walk(body):
            if isinstance(node, c_ast.Decl) and node.name in (a.name, b.name):
                if 'volatile' in (node.quals or []):
                    return False
                t = node.type
                while isinstance(t, (c_ast.PtrDecl, c_ast.ArrayDecl)):
                    if 'volatile' in (t.quals or []):
                        return False
                    t = t.type
                if isinstance(t, c_ast.TypeDecl) and 'volatile' in (t.quals or []):
                    return False
        return True

    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            a, b = items[k], items[k + 1]
            if isinstance(a, c_ast.Assignment) and isinstance(b, c_ast.Assignment) and a.op == b.op == '=' \
                    and isinstance(a.rvalue, c_ast.Constant) and isinstance(b.rvalue, c_ast.Constant) \
                    and a.rvalue.value == b.rvalue.value and plain_distinct(a.lvalue, b.lvalue):
                sites.append(('chain', comp, k))
        for k, a in enumerate(items):
            if isinstance(a, c_ast.Assignment) and a.op == '=' and isinstance(a.rvalue, c_ast.Assignment) \
                    and a.rvalue.op == '=' and plain_distinct(a.lvalue, a.rvalue.lvalue):
                sites.append(('split', comp, k))
    if not sites:
        return None
    kind, comp, k = rng.choice(sites)
    if kind == 'chain':
        a, b = comp.block_items[k], comp.block_items[k + 1]
        comp.block_items[k:k + 2] = [c_ast.Assignment('=', a.lvalue, c_ast.Assignment('=', b.lvalue, b.rvalue))]
        return f'chain_assign: {expr_text(a)}; {expr_text(b)} -> chained'
    a = comp.block_items[k]
    inner = a.rvalue
    comp.block_items[k:k + 1] = [c_ast.Assignment('=', inner.lvalue, inner.rvalue),
                                 c_ast.Assignment('=', a.lvalue, copy.deepcopy(inner.rvalue))]
    return f'chain_assign: split {expr_text(a)}'


def m_return_layout(body, rng):
    """`if (c) return X; return Y;` <-> `if (!c) return Y; return X;` at end of a block."""
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        if len(items) >= 2 and isinstance(items[-1], c_ast.Return) and isinstance(items[-2], c_ast.If) \
                and items[-2].iffalse is None:
            t = as_list(items[-2].iftrue)
            if len(t) == 1 and isinstance(t[0], c_ast.Return):
                sites.append(comp)
    if not sites:
        return None
    comp = rng.choice(sites)
    s, r = comp.block_items[-2], comp.block_items[-1]
    t = as_list(s.iftrue)[0]
    comp.block_items[-2:] = [c_ast.If(negate(s.cond), r, None), t]
    return f'return_layout: swap final returns around if ({expr_text(s.cond)})'


def _is_null(e):
    if isinstance(e, c_ast.Constant) and e.value in ('0', '0L', '0l'):
        return True
    return isinstance(e, c_ast.Cast) and isinstance(e.to_type.type, c_ast.PtrDecl) and _is_null(e.expr)


def m_null_spelling(body, rng):
    """Spell a null-pointer comparison constant as 0, 0L or a pointer cast of 0."""
    sites = []
    casts = [n for n, *_ in walk(body) if isinstance(n, c_ast.Cast) and isinstance(n.to_type.type, c_ast.PtrDecl)
             and _is_null(n.expr)]
    for n, *_ in walk(body):
        if isinstance(n, c_ast.BinaryOp) and n.op in ('==', '!='):
            for side, other in (('left', 'right'), ('right', 'left')):
                if not _is_null(getattr(n, side)):
                    continue
                o = getattr(n, other)
                if isinstance(getattr(n, side), c_ast.Cast):
                    sites.append((n, side))
                elif TYPE_ENV is not None and isinstance(TYPE_ENV.type_of(o, body), c_ast.PtrDecl):
                    sites.append((n, side))
    if not sites:
        return None
    n, side = rng.choice(sites)
    cur = getattr(n, side)
    options = [c_ast.Constant('int', '0'), c_ast.Constant('long', '0L')]
    if casts:
        options.append(copy.deepcopy(rng.choice(casts)))
    options = [o for o in options if expr_text(o) != expr_text(cur)]
    new = rng.choice(options)
    before = expr_text(n)
    setattr(n, side, new)
    return f'null_spelling: {before} -> {expr_text(n)}'


def m_assign_in_cond(body, rng):
    """`x = E; if (x OP k)` <-> `if ((x = E) OP k)` (also bare `if (x)` / `if (!x)`)."""
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            a, b = items[k], items[k + 1]
            if isinstance(a, c_ast.Assignment) and a.op == '=' and isinstance(a.lvalue, c_ast.ID) and \
                    isinstance(b, c_ast.If):
                c = b.cond
                if isinstance(c, c_ast.ID) and c.name == a.lvalue.name:
                    sites.append(('fold', comp, k, None))
                elif isinstance(c, c_ast.UnaryOp) and c.op == '!' and isinstance(c.expr, c_ast.ID) and \
                        c.expr.name == a.lvalue.name:
                    sites.append(('fold', comp, k, 'not'))
                elif isinstance(c, c_ast.BinaryOp) and c.op in INVERT and isinstance(c.left, c_ast.ID) and \
                        c.left.name == a.lvalue.name and not has_side_effects(c.right) and \
                        a.lvalue.name not in ids_in(c.right):
                    sites.append(('fold', comp, k, 'bin'))
        for k, b in enumerate(items):
            if isinstance(b, c_ast.If):
                c = b.cond
                inner = None
                if isinstance(c, c_ast.Assignment):
                    inner = c
                elif isinstance(c, c_ast.UnaryOp) and c.op == '!' and isinstance(c.expr, c_ast.Assignment):
                    inner = c.expr
                elif isinstance(c, c_ast.BinaryOp) and isinstance(c.left, c_ast.Assignment):
                    inner = c.left
                if inner is not None and inner.op == '=' and isinstance(inner.lvalue, c_ast.ID):
                    sites.append(('unfold', comp, k, None))
    if not sites:
        return None
    kind, comp, k, form = rng.choice(sites)
    if kind == 'fold':
        a, b = comp.block_items[k], comp.block_items[k + 1]
        c = b.cond
        if form is None:
            b.cond = a
        elif form == 'not':
            c.expr = a
        else:
            c.left = a
        del comp.block_items[k]
        return f'assign_in_cond: fold {expr_text(a)[:40]} into if condition'
    b = comp.block_items[k]
    c = b.cond
    if isinstance(c, c_ast.Assignment):
        inner = c
        b.cond = c_ast.ID(inner.lvalue.name)
    elif isinstance(c, c_ast.UnaryOp):
        inner = c.expr
        c.expr = c_ast.ID(inner.lvalue.name)
    else:
        inner = c.left
        c.left = c_ast.ID(inner.lvalue.name)
    comp.block_items.insert(k, inner)
    return f'assign_in_cond: unfold {expr_text(inner)[:40]} before if'


def _loop_bodies(root):
    for n, *_ in walk(root):
        if isinstance(n, (c_ast.For, c_ast.While, c_ast.DoWhile)) and isinstance(n.stmt, c_ast.Compound):
            yield n, n.stmt


def m_continue_else(body, rng):
    """In a loop body: `if (c) { A; continue; } B...` <-> `if (c) { A } else { B... }` (tail of body).

    For do-while the continue jumps to the condition, which is also the end of the body,
    so the rewrite is valid for every loop kind."""
    sites = []
    for loop, comp in _loop_bodies(body):
        items = comp.block_items or []
        for k, s in enumerate(items):
            if not isinstance(s, c_ast.If):
                continue
            t = as_list(s.iftrue)
            rest = items[k + 1:]
            if s.iffalse is None and t and isinstance(t[-1], c_ast.Continue) and rest and \
                    not any(isinstance(x, (c_ast.Decl, c_ast.Label)) for x in rest):
                sites.append(('to_else', comp, k))
            if s.iffalse is not None and k == len(items) - 1 and \
                    not contains(s.iftrue, (c_ast.Label,)) and not ends_in_jump(s.iftrue) and \
                    not any(isinstance(x, c_ast.Decl) for x in as_list(s.iffalse)):
                sites.append(('to_continue', comp, k))
    if not sites:
        return None
    kind, comp, k = rng.choice(sites)
    s = comp.block_items[k]
    if kind == 'to_else':
        rest = comp.block_items[k + 1:]
        del comp.block_items[k + 1:]
        s.iftrue = as_block(as_list(s.iftrue)[:-1])
        s.iffalse = as_block(rest)
        return f'continue_else: if ({expr_text(s.cond)}) {{..continue}} rest -> if/else'
    rest = as_list(s.iffalse)
    s.iftrue = as_block(as_list(s.iftrue) + [c_ast.Continue()])
    s.iffalse = None
    comp.block_items[k + 1:] = rest
    return f'continue_else: if ({expr_text(s.cond)}) A else B at loop tail -> if {{A; continue;}} B'


# ------------------------------------------------------------------ structural allocation axes

def _counted_for(loop):
    """Return a simple `for (i = start; i OP bound; i++)` induction description."""
    if not isinstance(loop, c_ast.For) or not isinstance(loop.init, c_ast.Assignment) or \
            loop.init.op != '=' or not isinstance(loop.init.lvalue, c_ast.ID) or \
            not isinstance(loop.cond, c_ast.BinaryOp) or loop.cond.op not in ('<', '<=', '>', '>='):
        return None
    name = loop.init.lvalue.name
    if not isinstance(loop.cond.left, c_ast.ID) or loop.cond.left.name != name:
        return None
    if not _pure_scalar_expr(loop.init.rvalue) or not _pure_scalar_expr(loop.cond.right):
        return None
    step_value = _for_step_value(loop.next, name)
    if step_value is None or step_value == 0:
        return None
    if loop.cond.op in ('<', '<=') and step_value < 0 or \
            loop.cond.op in ('>', '>=') and step_value > 0:
        return None
    return {'name': name, 'init_value': loop.init.rvalue, 'bound': loop.cond.right,
            'step': step_value, 'header_ids': ids_in(loop.init.rvalue) | ids_in(loop.cond.right)}


def _constant_int(node):
    if not isinstance(node, c_ast.Constant) or node.type not in ('int', 'char'):
        return None
    value = node.value.strip().rstrip('uUlL')
    try:
        return int(value, 0)
    except ValueError:
        try:
            return int(value, 10)
        except ValueError:
            return None


def _for_step_value(step, name):
    if isinstance(step, c_ast.UnaryOp) and step.op in ('p++', '++', 'p--', '--') and \
            isinstance(step.expr, c_ast.ID) and step.expr.name == name:
        return -1 if '--' in step.op else 1
    if isinstance(step, c_ast.Assignment) and isinstance(step.lvalue, c_ast.ID) and step.lvalue.name == name:
        if step.op == '=' and isinstance(step.rvalue, c_ast.BinaryOp) and \
                isinstance(step.rvalue.left, c_ast.ID) and step.rvalue.left.name == name:
            amount = _constant_int(step.rvalue.right)
            if amount is None:
                return None
            if step.rvalue.op == '+':
                return amount
            if step.rvalue.op == '-':
                return -amount
        amount = _constant_int(step.rvalue)
        if amount is None:
            return None
        if step.op == '+=':
            return amount
        if step.op == '-=':
            return -amount
    return None


def _constant_for_range(loop, info):
    start, bound = _constant_int(info['init_value']), _constant_int(info['bound'])
    if start is None or bound is None:
        return None
    op, step = loop.cond.op, info['step']
    if op in ('<', '<=') and step > 0:
        last_bound = bound if op == '<=' else bound - 1
        count = 0 if start > last_bound else (last_bound - start) // step + 1
    elif op in ('>', '>=') and step < 0:
        last_bound = bound if op == '>=' else bound + 1
        count = 0 if start < last_bound else (start - last_bound) // (-step) + 1
    else:
        return None
    if count > 65536:
        return None
    last = start + (count - 1) * step if count else start
    return start, last, count


def _local_counted_index(body, name):
    if TYPE_ENV is None:
        return False
    decls = [d for d in body.block_items or [] if isinstance(d, c_ast.Decl) and d.name == name]
    if len(decls) != 1 or set(decls[0].storage or []) & {'static', 'extern'} or \
            _volatile_type(decls[0].type) or address_taken(body, name):
        return False
    if name in TYPE_ENV.params or name in TYPE_ENV.globals:
        return False
    return True


def _counted_range_no_overflow(loop, info, body):
    if TYPE_ENV is None:
        return False
    value_range = _constant_for_range(loop, info)
    typ = TYPE_ENV.type_of(c_ast.ID(info['name']), body)
    if value_range is None or not isinstance(typ, c_ast.TypeDecl) or \
            not isinstance(typ.type, c_ast.IdentifierType):
        return False
    names = set(typ.type.names)
    if names - {'unsigned', 'signed', 'char', 'short', 'int', 'long'}:
        return False
    if 'long' in names:
        bits = 32
    elif 'char' in names:
        bits = 8
    else:
        bits = 16
    unsigned = 'unsigned' in names
    low, high = (0, (1 << bits) - 1) if unsigned else (-(1 << (bits - 1)), (1 << (bits - 1)) - 1)
    start, last, count = value_range
    following = last + info['step'] if count else start
    return low <= start <= high and low <= last <= high and low <= following <= high


def _pure_scalar_expr(expr):
    """Conservative side-effect-free expression with no memory or function access."""
    if expr is None:
        return False
    for n, *_ in walk(expr):
        if not isinstance(n, (c_ast.ID, c_ast.Constant, c_ast.BinaryOp, c_ast.UnaryOp, c_ast.Cast)):
            return False
        if isinstance(n, c_ast.BinaryOp) and n.op not in (
                '+', '-', '*', '&', '|', '^', '<<', '>>', '<', '<=', '>', '>=', '==', '!=', '&&', '||'):
            return False
        if isinstance(n, c_ast.UnaryOp) and n.op not in ('+', '-', '~', '!'):
            return False
    return not has_side_effects(expr)


def _array_write_axes(target, first, second):
    """Recognize exactly M[first][second] or M[second][first]."""
    if not isinstance(target, c_ast.ArrayRef) or not isinstance(target.name, c_ast.ArrayRef):
        return None
    inner = target.name
    if not isinstance(inner.name, c_ast.ID) or not isinstance(inner.subscript, c_ast.ID) or \
            not isinstance(target.subscript, c_ast.ID):
        return None
    indices = (inner.subscript.name, target.subscript.name)
    if set(indices) != {first, second}:
        return None
    return (inner.name.name, indices,
            {id(target), id(inner), id(inner.name), id(inner.subscript), id(target.subscript)})


def _interchange_body_safe(body, outer_name, inner_name):
    """Prove disjoint, independent 2-D array writes with no escaping control effects."""
    if contains(body, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto,
                       c_ast.Label, c_ast.Switch, c_ast.For, c_ast.While, c_ast.DoWhile)):
        return False
    if has_call(body):
        return False
    writes = []
    allowed_array_nodes = set()
    roots = set()
    orientations = set()
    for n, *_ in walk(body):
        if isinstance(n, c_ast.Assignment):
            if n.op != '=' or has_side_effects(n.rvalue) or reads_memory(n.rvalue):
                return False
            found = _array_write_axes(n.lvalue, outer_name, inner_name)
            if found is None:
                return False
            root, orientation, nodes = found
            roots.add(root)
            orientations.add(orientation)
            allowed_array_nodes.update(nodes)
            writes.append(n)
        elif isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--', '++', '--'):
            return False
        elif isinstance(n, (c_ast.If, c_ast.While, c_ast.DoWhile, c_ast.For)):
            cond = getattr(n, 'cond', None)
            if cond is not None and (not _pure_scalar_expr(cond) or reads_memory(cond)):
                return False
        elif isinstance(n, (c_ast.ArrayRef, c_ast.StructRef)) and id(n) not in allowed_array_nodes:
            # ArrayRef children may be encountered before the containing Assignment's
            # lvalue in preorder, so validate these again after collecting all writes.
            continue
    if not writes or len(roots) != 1 or len(orientations) != 1:
        return False
    # No memory read is permitted anywhere.  ArrayRef nodes in store lvalues are the only
    # memory-shaped nodes accepted; all of them must belong to those exact stores.
    for n, *_ in walk(body):
        if isinstance(n, (c_ast.ArrayRef, c_ast.StructRef)) and id(n) not in allowed_array_nodes:
            return False
        if isinstance(n, c_ast.UnaryOp) and n.op == '*':
            return False
    return True


def _flat_add_terms(expr):
    if isinstance(expr, c_ast.BinaryOp) and expr.op == '+':
        return _flat_add_terms(expr.left) + _flat_add_terms(expr.right)
    return [expr]


def _pure_pointer_condition(expr, pointer):
    for node, *_ in walk(expr):
        if isinstance(node, c_ast.UnaryOp) and node.op == '*':
            if not isinstance(node.expr, c_ast.ID) or node.expr.name != pointer:
                return False
        elif not isinstance(node, (c_ast.ID, c_ast.Constant, c_ast.BinaryOp, c_ast.UnaryOp, c_ast.Cast)):
            return False
        if isinstance(node, c_ast.BinaryOp) and node.op not in (
                '+', '-', '*', '&', '|', '^', '<', '<=', '>', '>=', '==', '!=', '&&', '||'):
            return False
        if isinstance(node, c_ast.UnaryOp) and node.op not in ('*', '+', '-', '~', '!'):
            return False
    return not has_side_effects(expr)


def _interchange_flat_pointer_safe(body, outer, inner, outer_info, inner_info, function_body):
    """Prove a flat-array nest through one per-iteration pointer and disjoint row ranges."""
    if TYPE_ENV is None or not isinstance(body, c_ast.Compound):
        return False
    if contains(body, (c_ast.Return, c_ast.Break, c_ast.Continue, c_ast.Goto,
                       c_ast.Label, c_ast.Switch, c_ast.For, c_ast.While, c_ast.DoWhile)) or has_call(body):
        return False
    outer_range = _constant_for_range(outer, outer_info)
    inner_range = _constant_for_range(inner, inner_info)
    if outer_range is None or inner_range is None:
        return False
    outer_step = outer_info['step']
    if outer_step <= 0 or inner_info['step'] != 1 or inner_range[2] > outer_step:
        return False
    items = body.block_items or []
    if len(items) < 2 or not isinstance(items[0], c_ast.Assignment) or items[0].op != '=' or \
            not isinstance(items[0].lvalue, c_ast.ID):
        return False
    pointer = items[0].lvalue.name
    ptype = TYPE_ENV.type_of(c_ast.ID(pointer), function_body)
    if not isinstance(ptype, c_ast.PtrDecl) or _volatile_type(ptype):
        return False
    pdecls = [n for n, *_ in walk(function_body) if isinstance(n, c_ast.Decl) and n.name == pointer]
    if len(pdecls) != 1 or 'static' in (pdecls[0].storage or []) or _volatile_type(pdecls[0].type):
        return False
    terms = _flat_add_terms(items[0].rvalue)
    outer_terms = [n for n in terms if isinstance(n, c_ast.ID) and n.name == outer_info['name']]
    inner_terms = [n for n in terms if isinstance(n, c_ast.ID) and n.name == inner_info['name']]
    other_ids = [n for n in terms if isinstance(n, c_ast.ID) and n.name not in
                 (outer_info['name'], inner_info['name'])]
    constants = [_constant_int(n) for n in terms if isinstance(n, c_ast.Constant)]
    if len(outer_terms) != 1 or len(inner_terms) != 1 or len(other_ids) != 1 or \
            any(value is None for value in constants) or len(other_ids) != 1:
        return False
    base = other_ids[0]
    basetype = TYPE_ENV.type_of(base, function_body)
    if not isinstance(basetype, c_ast.ArrayDecl) or _type_spelling(ptype.type) != _type_spelling(basetype.type):
        return False
    # Every pointer use is either this iteration's defining assignment or a direct `*p`.
    memory_nodes = set()
    for node, parent, attr, _ in walk(body):
        if isinstance(node, (c_ast.ArrayRef, c_ast.StructRef)):
            return False
        if isinstance(node, c_ast.UnaryOp) and node.op == '*':
            if not isinstance(node.expr, c_ast.ID) or node.expr.name != pointer:
                return False
            memory_nodes.add(id(node))
        if isinstance(node, c_ast.ID) and node.name == pointer:
            if parent is items[0] and attr == 'lvalue':
                continue
            if isinstance(parent, c_ast.UnaryOp) and parent.op == '*' and attr == 'expr':
                continue
            return False
        if isinstance(node, c_ast.FuncCall):
            return False
        if isinstance(node, c_ast.UnaryOp) and node.op in ('p++', 'p--', '++', '--'):
            return False
    if not memory_nodes:
        return False
    # One unconditional load into a private scalar may feed the branch conditions.
    value_loads = [s for s in items[1:] if isinstance(s, c_ast.Assignment) and s.op == '=' and
                   isinstance(s.lvalue, c_ast.ID) and isinstance(s.rvalue, c_ast.UnaryOp) and
                   s.rvalue.op == '*' and isinstance(s.rvalue.expr, c_ast.ID) and
                   s.rvalue.expr.name == pointer]
    for stmt in walk(body):
        node = stmt[0]
        if isinstance(node, c_ast.Assignment):
            if node is items[0] or any(node is s for s in value_loads):
                continue
            if isinstance(node.lvalue, c_ast.UnaryOp) and node.lvalue.op == '*' and \
                    isinstance(node.lvalue.expr, c_ast.ID) and node.lvalue.expr.name == pointer and \
                    node.op in ('=', '+=', '-=') and not has_call(node.rvalue):
                continue
            return False
        if isinstance(node, c_ast.If) and not _pure_pointer_condition(node.cond, pointer):
            return False
        if isinstance(node, c_ast.Decl) and node.init is not None:
            return False
    if len(value_loads) != 1:
        return False
    load = value_loads[0]
    if items.index(load) >= items.index(next((s for s in items if isinstance(s, c_ast.If)), load)):
        return False
    value_name = load.lvalue.name
    value_decls = [n for n, *_ in walk(function_body) if isinstance(n, c_ast.Decl) and n.name == value_name]
    if len(value_decls) != 1 or 'static' in (value_decls[0].storage or []) or \
            _volatile_type(value_decls[0].type) or address_taken(function_body, value_name):
        return False
    for name in (pointer, value_name):
        if count_uses(function_body, name) != sum(isinstance(n, c_ast.ID) and n.name == name
                                                  for n, *_ in walk(outer)):
            return False
    # Pointer expression arithmetic must stay in the same no-wrap 16-bit signed range.
    offset = sum(constants)
    total_values = [outer_range[0] + inner_range[0] + offset,
                    outer_range[0] + inner_range[1] + offset,
                    outer_range[1] + inner_range[0] + offset,
                    outer_range[1] + inner_range[1] + offset]
    if min(total_values) < -32768 or max(total_values) > 32767:
        return False
    return True


def m_loop_interchange(body, rng):
    """Swap two perfectly nested counted loops after a conservative dependence proof."""
    if TYPE_ENV is None:
        return None
    sites = []
    for outer, *_ in walk(body):
        if not isinstance(outer, c_ast.For):
            continue
        outer_info = _counted_for(outer)
        if outer_info is None:
            continue
        inner = None
        if isinstance(outer.stmt, c_ast.For):
            inner = outer.stmt
        elif isinstance(outer.stmt, c_ast.Compound) and len(outer.stmt.block_items or []) == 1 and \
                isinstance(outer.stmt.block_items[0], c_ast.For):
            inner = outer.stmt.block_items[0]
        if inner is None:
            continue
        inner_info = _counted_for(inner)
        if inner_info is None or inner_info['name'] == outer_info['name']:
            continue
        oi, ii = outer_info['name'], inner_info['name']
        if not (_local_counted_index(body, oi) and _local_counted_index(body, ii) and
                _counted_range_no_overflow(outer, outer_info, body) and
                _counted_range_no_overflow(inner, inner_info, body)):
            continue
        if ii in outer_info['header_ids'] or oi in inner_info['header_ids']:
            continue
        if not isinstance(inner.stmt, c_ast.Compound):
            continue
        array_safe = _interchange_body_safe(inner.stmt, oi, ii)
        pointer_safe = not array_safe and _interchange_flat_pointer_safe(
            inner.stmt, outer, inner, outer_info, inner_info, body)
        if not array_safe and not pointer_safe:
            continue
        # The induction variables must not be observed after the nest: changing which
        # loop exits last would otherwise change their final values.
        nest_ids = ids_in(outer)
        if count_uses(body, oi) != sum(isinstance(n, c_ast.ID) and n.name == oi
                                       for n, *_ in walk(outer)) or \
                count_uses(body, ii) != sum(isinstance(n, c_ast.ID) and n.name == ii
                                            for n, *_ in walk(outer)):
            continue
        sites.append((outer, inner, oi, ii))
    if not sites:
        return None
    outer, inner, oi, ii = rng.choice(sites)
    outer.init, inner.init = inner.init, outer.init
    outer.cond, inner.cond = inner.cond, outer.cond
    outer.next, inner.next = inner.next, outer.next
    return f'loop_interchange: swap counted nest {oi} <-> {ii}'


def _local_flat_accesses(body, name):
    """Return ordered (statement index, is_def, reads_old_value) accesses, or None."""
    if any(isinstance(n, (c_ast.If, c_ast.Switch, c_ast.For, c_ast.While, c_ast.DoWhile,
                         c_ast.Goto, c_ast.Label, c_ast.Return)) for n, *_ in walk(body)):
        return None
    items = body.block_items or []
    out = []
    for pos, stmt in enumerate(items):
        if isinstance(stmt, c_ast.Decl):
            if stmt.name == name:
                continue
        ids = [n for n, p, a, _ in walk(stmt)
               if isinstance(n, c_ast.ID) and n.name == name and
               not (isinstance(p, c_ast.StructRef) and a == 'field')]
        if not ids:
            continue
        if isinstance(stmt, c_ast.Assignment) and stmt.op == '=' and \
                isinstance(stmt.lvalue, c_ast.ID) and stmt.lvalue.name == name:
            old_read = any(n is not stmt.lvalue for n in ids)
            out.append((pos, True, old_read))
            continue
        # Any hidden write, address use, pointer target or compound assignment makes the
        # segment boundary ambiguous.
        for n, p, a, _ in walk(stmt):
            if isinstance(n, c_ast.UnaryOp) and n.op in ('&', 'p++', 'p--', '++', '--') and \
                    isinstance(n.expr, c_ast.ID) and n.expr.name == name:
                return None
            if isinstance(n, c_ast.Assignment) and isinstance(n.lvalue, c_ast.ID) and \
                    n.lvalue.name == name:
                return None
            if isinstance(n, c_ast.ID) and n.name == name and isinstance(p, c_ast.StructRef) and a == 'field':
                continue
        out.append((pos, False, True))
    return out


def _simple_local_decls(body):
    return [(k, d) for k, d in enumerate(body.block_items or [])
            if isinstance(d, c_ast.Decl) and d.name and d.init is None and _is_scalar_decl(d) and
            'extern' not in (d.storage or []) and 'static' not in (d.storage or []) and
            not _volatile_type(d.type) and not address_taken(body, d.name)]


def _fresh_name(body, base):
    used = {n.name for n, *_ in walk(body) if isinstance(n, c_ast.ID)} | \
           {n.name for n, *_ in walk(body) if isinstance(n, c_ast.Decl) and n.name}
    stem = re.sub(r'\W', '_', base)[:16] or 'value'
    for i in range(2, 1000):
        name = f'perm_{stem}_{i}'
        if name not in used:
            return name
    return None


def _rename_ids(root, old, new):
    count = 0
    for node, parent, attr, idx in list(walk(root)):
        if isinstance(node, c_ast.ID) and node.name == old and not \
                (isinstance(parent, c_ast.StructRef) and attr == 'field'):
            node.name = new
            count += 1
    return count


def _type_spelling(t):
    clone = copy.deepcopy(t)
    inner = clone
    while isinstance(inner, c_ast.PtrDecl):
        inner = inner.type
    if isinstance(inner, c_ast.TypeDecl):
        inner.declname = '__permuter_type__'
    return FarGenerator.finish(FarGenerator().visit(clone)).strip()


def m_split_var(body, rng):
    """Split one later straight-line lifetime after a dead old value is overwritten."""
    sites = []
    decls = _simple_local_decls(body)
    for _, decl in decls:
        name = decl.name
        accesses = _local_flat_accesses(body, name)
        if not accesses:
            continue
        defs = [(i, item) for i, item in enumerate(accesses) if item[1]]
        for di, (pos, _is_def, reads_old) in defs:
            if reads_old:
                continue
            prev = accesses[:di]
            if not any(read for _p, _d, read in prev):
                continue
            next_def = next((j for j, item in defs if j > di), len(accesses))
            later = accesses[di:next_def]
            next_reads_old = next_def < len(accesses) and accesses[next_def][2]
            if not any(read for _p, _d, read in later) and not next_reads_old:
                continue
            end_pos = accesses[next_def][0] if next_def < len(accesses) else len(body.block_items or [])
            if any(p >= pos and p < end_pos for p, _d, read in accesses[di:next_def] if not read and p != pos):
                continue
            sites.append((decl, pos, end_pos, name))
    if not sites:
        return None
    decl, start, end, name = rng.choice(sites)
    fresh = _fresh_name(body, name)
    if not fresh:
        return None
    new_decl = copy.deepcopy(decl)
    new_decl.name = fresh
    # Update the declarator name at the innermost TypeDecl as well.
    inner = new_decl.type
    while isinstance(inner, c_ast.PtrDecl):
        inner = inner.type
    if isinstance(inner, c_ast.TypeDecl):
        inner.declname = fresh
    for stmt in (body.block_items or [])[start:end]:
        _rename_ids(stmt, name, fresh)
    # A compound self-update at the following definition reads the just-split value
    # before writing the original variable. Rename that read while keeping its lvalue.
    if end < len(body.block_items or []):
        following = body.block_items[end]
        if isinstance(following, c_ast.Assignment) and following.op == '=' and \
                isinstance(following.lvalue, c_ast.ID) and following.lvalue.name == name and \
                any(isinstance(n, c_ast.ID) and n.name == name for n, *_ in walk(following.rvalue)):
            _rename_ids(following.rvalue, name, fresh)
    insert = 0
    while insert < len(body.block_items or []) and isinstance(body.block_items[insert], c_ast.Decl):
        insert += 1
    body.block_items.insert(insert, new_decl)
    if insert <= start:
        start += 1
    return f'split_var: {name} later range -> {fresh} at statement {start}'


def m_merge_vars(body, rng):
    """Merge equal scalar locals whose single straight-line live ranges do not overlap."""
    decls = _simple_local_decls(body)
    sites = []
    for ai, (ka, a) in enumerate(decls):
        aa = _local_flat_accesses(body, a.name)
        if not aa or not aa[0][1] or aa[0][2]:
            continue
        for _kb, b in decls[ai + 1:]:
            if _type_spelling(a.type) != _type_spelling(b.type):
                continue
            bb = _local_flat_accesses(body, b.name)
            if not bb or not bb[0][1] or bb[0][2]:
                continue
            if max(x[0] for x in aa) < min(x[0] for x in bb):
                first, second = a, b
            elif max(x[0] for x in bb) < min(x[0] for x in aa):
                first, second = b, a
            else:
                continue
            # Prove every reference to the second name starts with its first defining
            # statement and that the first name is dead before that statement.
            sites.append((first, second))
    if not sites:
        return None
    first, second = rng.choice(sites)
    count = _rename_ids(body, second.name, first.name)
    body.block_items = [s for s in (body.block_items or [])
                        if not (isinstance(s, c_ast.Decl) and s is second)]
    if not count:
        return None
    return f'merge_vars: {second.name} disjoint range into {first.name}'


def _pure_admitted_function(body, params, globals_):
    """Prove a leaf function writes only its own by-value locals/parameters."""
    locals_ = {n.name for n, *_ in walk(body) if isinstance(n, c_ast.Decl) and n.name}
    locals_ |= set(params)
    if any(isinstance(n, c_ast.Decl) and set(n.storage or []) & {'static', 'extern'}
           for n, *_ in walk(body)):
        return False
    for n, parent, attr, _ in walk(body):
        if isinstance(n, c_ast.FuncCall) or isinstance(n, (c_ast.ArrayRef, c_ast.StructRef)):
            return False
        if isinstance(n, c_ast.UnaryOp) and n.op == '*':
            return False
        if isinstance(n, c_ast.UnaryOp) and n.op == '&':
            return False
        if isinstance(n, c_ast.Assignment):
            if not isinstance(n.lvalue, c_ast.ID) or n.lvalue.name not in locals_:
                return False
        if isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--', '++', '--'):
            if not isinstance(n.expr, c_ast.ID) or n.expr.name not in locals_:
                return False
    if globals_:
        for name in globals_:
            typ = globals_[name]
            if _volatile_type(typ) and count_uses(body, name):
                return False
    return True


@lru_cache(maxsize=1)
def admitted_pure_callees():
    """Names of admitted byte-matched leaf functions with no shared-state writes."""
    global TYPE_ENV
    path = ROOT / 'src' / 'recovery.json'
    try:
        records = json.loads(path.read_text(encoding='utf-8')).get('targets', {})
    except Exception:
        return frozenset()
    candidates = {}
    for symbol, record in records.items():
        if record.get('proof') != 'BYTE_MATCHED_RECONSTRUCTION' or not record.get('source'):
            continue
        candidates.setdefault(record['source'], []).append(symbol)
    result = set()
    target_types = TYPE_ENV
    try:
        for rel, symbols in candidates.items():
            source_path = (ROOT / rel).resolve()
            try:
                source = source_path.read_text(encoding='ascii')
                funcs = csrc.top_level_functions(source)
                for symbol in symbols:
                    wanted = symbol.lstrip('_')
                    f = next((x for x in funcs if x['name'] in (wanted, symbol)), None)
                    if f is None:
                        continue
                    codec = BodyCodec(source, f['name'])
                    params = set(codec.types.params) if codec.types else set()
                    globals_ = codec.types.globals if codec.types else {}
                    if codec.types and _pure_admitted_function(codec.body, params, globals_):
                        result.add(f['name'])
            except Exception:
                continue
    finally:
        # BodyCodec installs a process-global type environment.  The purity proof scans many
        # admitted sources, but must leave the active target's environment in place.
        TYPE_ENV = target_types
    return frozenset(result)


def _call_name(stmt):
    if isinstance(stmt, c_ast.FuncCall) and isinstance(stmt.name, c_ast.ID):
        return stmt.name.name
    return None


def _independent_call_args(stmt):
    args = stmt.args.exprs if isinstance(stmt.args, c_ast.ExprList) else ([] if stmt.args is None else [stmt.args])
    return all(_pure_scalar_expr(arg) and not reads_memory(arg) for arg in args)


def m_reorder_independent_calls(body, rng, *, allow_risky=False):
    """Swap adjacent direct calls only with admitted purity proof or explicit risky mode."""
    proven = admitted_pure_callees()
    sites = []
    for comp in blocks(body):
        items = comp.block_items or []
        for k in range(len(items) - 1):
            left, right = items[k:k + 2]
            a, b = _call_name(left), _call_name(right)
            if not a or not b or not _independent_call_args(left) or not _independent_call_args(right):
                continue
            if (a in proven and b in proven) or allow_risky:
                sites.append((comp, k, a, b, a in proven and b in proven))
    if not sites:
        return None
    comp, k, a, b, safe = rng.choice(sites)
    comp.block_items[k], comp.block_items[k + 1] = comp.block_items[k + 1], comp.block_items[k]
    tag = 'SAFE' if safe else 'RISKY'
    return f'reorder_independent_calls({tag}): {a} <-> {b}'


def _safe_loop_scalar_expr(expr, body, loop_info, *, require_unsigned=True):
    if not _pure_scalar_expr(expr) or not isinstance(expr, (c_ast.BinaryOp, c_ast.UnaryOp)):
        return False
    if loop_info['name'] in ids_in(expr):
        return False
    if TYPE_ENV is None:
        return False
    t = TYPE_ENV.type_of(expr, body)
    if t is None or not isinstance(t, c_ast.TypeDecl) or not isinstance(t.type, c_ast.IdentifierType):
        return False
    if require_unsigned and 'unsigned' not in t.type.names:
        return False
    if any(_volatile_type(TYPE_ENV.type_of(c_ast.ID(name), body) or c_ast.TypeDecl(None, [], None,
            c_ast.IdentifierType(['volatile']))) for name in ids_in(expr)):
        return False
    return True


def _deps_unchanged_in_loop(expr, loop):
    deps = ids_in(expr)
    writes = written_ids(loop.stmt)
    return not ('*mem*' in writes or deps & writes) and not has_call(loop.stmt)


def _new_temp_decl(body, expr, base):
    if TYPE_ENV is None:
        return None, None
    typ = TYPE_ENV.type_of(expr, body)
    name = _fresh_name(body, base)
    if typ is None or name is None:
        return None, None
    decl = decl_for(name, typ)
    return name, decl


def _insert_top_decl(body, decl):
    pos = 0
    while pos < len(body.block_items or []) and isinstance(body.block_items[pos], c_ast.Decl):
        pos += 1
    body.block_items.insert(pos, decl)


def _local_inputs_initialized_before(body, loop_index, expr):
    if TYPE_ENV is None:
        return False
    deps = ids_in(expr)
    items = body.block_items or []
    assigned = set(TYPE_ENV.params) | set(TYPE_ENV.globals)
    for stmt in items[:loop_index]:
        if isinstance(stmt, c_ast.If) or isinstance(stmt, (c_ast.For, c_ast.While, c_ast.DoWhile, c_ast.Switch)):
            return False
        if isinstance(stmt, c_ast.Decl) and stmt.name and stmt.init is not None:
            assigned.add(stmt.name)
        if isinstance(stmt, c_ast.Assignment) and isinstance(stmt.lvalue, c_ast.ID) and stmt.op == '=':
            assigned.add(stmt.lvalue.name)
    for name in deps:
        typ = TYPE_ENV.lookup(name, body)
        local = any(isinstance(n, c_ast.Decl) and n.name == name for n, *_ in walk(body))
        if local and name not in assigned:
            return False
        if typ is None:
            return False
    return True


def _replace_matching_expr(root, text, name):
    count = 0
    for node, parent, attr, idx in list(walk(root)):
        if parent is not None and expr_text(node) == text and isinstance(node, (c_ast.BinaryOp, c_ast.UnaryOp)):
            replace(parent, attr, idx, c_ast.ID(name))
            count += 1
    return count


def m_hoist_invariant(body, rng):
    """Cache an unsigned scalar expression invariant across a top-level counted loop."""
    sites = []
    for k, loop in enumerate(body.block_items or []):
        info = _counted_for(loop)
        if info is None or not isinstance(loop.stmt, c_ast.Compound) or has_call(loop.stmt) or \
                '*mem*' in written_ids(loop.stmt):
            continue
        # No writes through memory: the expression may read any scalar object, including one
        # reached indirectly by an alias, so array stores cannot be crossed conservatively.
        if '*mem*' in written_ids(loop.stmt):
            continue
        candidates = []
        for node, *_ in walk(loop.stmt):
            if not isinstance(node, (c_ast.BinaryOp, c_ast.UnaryOp)) or not _safe_loop_scalar_expr(node, body, info):
                continue
            if not _deps_unchanged_in_loop(node, loop) or not _local_inputs_initialized_before(body, k, node):
                continue
            candidates.append(node)
        for node in candidates:
            sites.append((k, loop, node))
    if not sites:
        return None
    k, loop, expr = rng.choice(sites)
    name, decl = _new_temp_decl(body, expr, 'invariant')
    if decl is None:
        return None
    text = expr_text(expr)
    n = _replace_matching_expr(loop.stmt, text, name)
    if not n:
        return None
    _insert_top_decl(body, decl)
    # Insertion of the declaration may shift this position when all declarations precede it.
    pos = body.block_items.index(loop)
    body.block_items.insert(pos, c_ast.Assignment('=', c_ast.ID(name), expr))
    return f'hoist_invariant: {text[:40]} -> {name} before counted loop ({n} uses)'


def m_sink_invariant(body, rng):
    """Inline a pure unsigned invariant temporary from immediately before a counted loop."""
    sites = []
    items = body.block_items or []
    decls = {d.name: d for _, d in _simple_local_decls(body)}
    for k in range(1, len(items)):
        assign, loop = items[k - 1], items[k]
        if not isinstance(assign, c_ast.Assignment) or assign.op != '=' or \
                not isinstance(assign.lvalue, c_ast.ID) or not isinstance(loop, c_ast.For):
            continue
        name = assign.lvalue.name
        decl = decls.get(name)
        info = _counted_for(loop)
        if decl is None or info is None or not isinstance(loop.stmt, c_ast.Compound):
            continue
        expr = assign.rvalue
        if not _safe_loop_scalar_expr(expr, body, info) or not _deps_unchanged_in_loop(expr, loop):
            continue
        if any(isinstance(n, c_ast.ID) and n.name == name for n, *_ in walk(assign.rvalue)):
            continue
        if written_ids(loop.stmt) & {name}:
            continue
        outside = False
        for pos, stmt in enumerate(items):
            if pos in (k - 1, k):
                continue
            if count_uses(stmt, name):
                outside = True
                break
        if outside or count_uses(loop.stmt, name) == 0:
            continue
        # The temp must not be written or addressed inside the loop; all of its uses are reads.
        if address_taken(loop.stmt, name) or any(isinstance(n, c_ast.Assignment) and
                isinstance(n.lvalue, c_ast.ID) and n.lvalue.name == name for n, *_ in walk(loop.stmt)):
            continue
        sites.append((k - 1, loop, assign, decl, name, expr))
    if not sites:
        return None
    pos, loop, assign, decl, name, expr = rng.choice(sites)
    text = expr_text(expr)
    n = 0
    for node, parent, attr, idx in list(walk(loop.stmt)):
        if isinstance(node, c_ast.ID) and node.name == name and parent is not None and \
                not (isinstance(parent, c_ast.StructRef) and attr == 'field'):
            replace(parent, attr, idx, copy.deepcopy(expr))
            n += 1
    del body.block_items[pos]
    body.block_items = [s for s in (body.block_items or []) if s is not decl]
    return f'sink_invariant: {name} -> {text[:40]} inside counted loop ({n} uses)'


def m_param_copy(body, rng):
    """Copy a scalar by-value parameter to a local, or undo such an entry copy."""
    if TYPE_ENV is None:
        return None
    items = body.block_items or []
    # Reverse form first: `local = parameter;` as the first executable statement.
    first_exec = next((i for i, s in enumerate(items) if not isinstance(s, c_ast.Decl)), len(items))
    if first_exec < len(items):
        stmt = items[first_exec]
        if isinstance(stmt, c_ast.Assignment) and stmt.op == '=' and isinstance(stmt.lvalue, c_ast.ID) and \
                isinstance(stmt.rvalue, c_ast.ID) and stmt.rvalue.name in TYPE_ENV.params:
            local, param = stmt.lvalue.name, stmt.rvalue.name
            decls = [d for _, d in local_decls(body) if d.name == local]
            if len(decls) == 1 and decls[0].init is None and _is_scalar_decl(decls[0]) and \
                    not _volatile_type(decls[0].type) and \
                    _type_spelling(decls[0].type) == _type_spelling(TYPE_ENV.params[param]) and \
                    not address_taken(body, local) and not address_taken(body, param):
                # The copy itself must define local before any other use.
                if count_uses(body, local) >= 2:
                    for s in items[first_exec + 1:]:
                        _rename_ids(s, local, param)
                    del body.block_items[first_exec]
                    body.block_items = [s for s in body.block_items if not
                                         (isinstance(s, c_ast.Decl) and s is decls[0])]
                    return f'param_copy: inline {local} back to parameter {param}'
    sites = []
    for name, typ in TYPE_ENV.params.items():
        resolved = TYPE_ENV.resolve(typ)
        if not isinstance(resolved, c_ast.TypeDecl) or not isinstance(resolved.type, c_ast.IdentifierType) or \
                _volatile_type(typ) or set(resolved.type.names) - {
                    'signed', 'unsigned', 'char', 'short', 'int', 'long'}:
            continue
        if address_taken(body, name):
            continue
        # Do not rewrite declaration initializers, since the copy is placed after them.
        if any(isinstance(n, c_ast.Decl) and n.init is not None and count_uses(n.init, name)
               for n, *_ in walk(body)):
            continue
        if count_uses(body, name) == 0:
            continue
        sites.append((name, typ))
    if not sites:
        return None
    name, typ = rng.choice(sites)
    fresh = _fresh_name(body, name)
    if not fresh:
        return None
    decl = decl_for(fresh, typ)
    if decl is None:
        return None
    _insert_top_decl(body, decl)
    pos = 0
    while pos < len(body.block_items) and isinstance(body.block_items[pos], c_ast.Decl):
        pos += 1
    body.block_items.insert(pos, c_ast.Assignment('=', c_ast.ID(fresh), c_ast.ID(name)))
    for stmt in body.block_items[pos + 1:]:
        _rename_ids(stmt, name, fresh)
    return f'param_copy: copy parameter {name} -> {fresh} at entry'


def m_decl_axis(source, rng, function):
    """Replace one file-scope extern with a different admitted typedb variant."""
    db_path = ROOT / 'build' / 'typedb' / 'typedb.json'
    if not db_path.is_file():
        return None, None
    try:
        import typedb
        database = json.loads(db_path.read_text(encoding='utf-8'))
        spans = typedb.scan_externals(source)
        variants = []
        for name, entry in database.get('names', {}).items():
            for span in spans:
                if span['function'] or not typedb._declared_name_in_span(source, span, name):
                    continue
                raw = source[span['start']:span['end']]
                if not re.search(r'\bextern\b', raw):
                    continue
                current = raw.strip()
                for variant in entry.get('variants', []):
                    declaration = variant.get('declaration', '').strip()
                    if not declaration or declaration == current or name not in declaration:
                        continue
                    if not re.match(r'extern\b', declaration):
                        continue
                    variants.append((span, raw, name, current, declaration))
        if not variants:
            return None, None
        rng.shuffle(variants)
        for span, raw, name, before, after in variants[:8]:
            key = (function, name, before, after)
            valid = _DECL_AXIS_CHECKED.get(key)
            replacement = after + ('\n' if raw.endswith('\n') else '')
            candidate = source[:span['start']] + replacement + source[span['end']:]
            if valid is None:
                parsed = typedb._parse_unit(candidate, '<decl-axis>')
                valid = parsed.get('ast') is not None
                if valid:
                    try:
                        BodyCodec(candidate, function)
                    except Exception:
                        valid = False
                _DECL_AXIS_CHECKED[key] = valid
            if valid:
                return candidate, f'decl_axis: {name}: {before[:36]} -> {after[:36]}'
        return None, None
    except Exception:
        return None, None


def mutate_source_axis(source, rng, *, only=None, function=None):
    """Apply one full-translation-unit mutation, separate from body AST mutations."""
    names = [name for name in SOURCE_MUTATIONS if only is None or name in only]
    for name in names:
        if name == 'decl_axis':
            candidate, desc = m_decl_axis(source, rng, function)
            if candidate is not None:
                return candidate, desc
    return source, None


HEADER_REG = re.compile(r'\bregister\s+')


def header_params(header: str):
    """Return list of (start, end) spans of parameters in a function header text."""
    open_i = header.find('(', header.find(re.search(r'\w+\s*\(', header).group(0)))
    depth, spans, start = 0, [], open_i + 1
    for i in range(open_i, len(header)):
        c = header[i]
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
            if depth == 0:
                spans.append((start, i))
                break
        elif c == ',' and depth == 1:
            spans.append((start, i))
            start = i + 1
    return spans


def mutate_header(header: str, rng):
    """Toggle `register` on one scalar parameter (MSC copies register params into SI/DI)."""
    spans = []
    for s, e in header_params(header):
        text = header[s:e]
        if not text.strip() or text.strip() in ('void', '...') or '(' in text or '[' in text:
            continue
        if re.search(r'\b(struct|union)\b', text) and '*' not in text:
            continue
        if re.search(r'\bfar\s*\*|\blong\b', text):
            continue  # far pointers / longs do not fit SI/DI
        spans.append((s, e))
    if not spans:
        return None, None
    s, e = rng.choice(spans)
    text = header[s:e]
    lead = len(text) - len(text.lstrip())
    if HEADER_REG.search(text):
        new = HEADER_REG.sub('', text, count=1)
        desc = f'register_param: remove register from `{text.strip()}`'
    else:
        new = text[:lead] + 'register ' + text[lead:]
        desc = f'register_param: add register to `{text.strip()}`'
    return header[:s] + new + header[e:], desc


MUTATIONS = {
    'swap_commutative': (m_swap_commutative, 3, True),
    'mirror_comparison': (m_mirror_comparison, 3, True),
    'invert_if': (m_invert_if, 3, True),
    'demorgan': (m_demorgan, 1, True),
    'cond_zero': (m_cond_zero, 3, True),
    'for_to_while': (m_for_to_while, 2, True),
    'while_to_for': (m_while_to_for, 2, True),
    'while_to_dowhile': (m_while_to_dowhile, 2, True),
    'dowhile_to_while': (m_dowhile_to_while, 2, True),
    'incdec_style': (m_incdec_style, 2, True),
    'compound_assign': (m_compound_assign, 2, True),
    'register_toggle': (m_register_toggle, 3, True),
    'sink_decl': (m_sink_decl, 1, True),
    'hoist_decl': (m_hoist_decl, 1, True),
    'switch_reorder': (m_switch_reorder, 2, True),
    'index_pointer': (m_index_pointer, 2, True),
    'split_merge_and': (m_split_merge_and, 2, True),
    'ternary': (m_ternary, 2, True),
    'else_layout': (m_else_layout, 2, True),
    'return_layout': (m_return_layout, 1, True),
    'stmt_swap': (m_stmt_swap, 3, True),
    'inline_temp': (m_inline_temp, 1, True),
    'assign_in_cond': (m_assign_in_cond, 2, True),
    'continue_else': (m_continue_else, 2, True),
    'introduce_temp': (m_introduce_temp, 2, True),
    'inline_temp_multi': (m_inline_temp_multi, 1, True),
    'type_change': (m_type_risky, 2, False),
    'const_bound': (m_const_bound, 1, False),
    'chain_assign': (m_chain_assign, 1, True),
    'loop_interchange': (m_loop_interchange, 2, True),
    'split_var': (m_split_var, 2, True),
    'merge_vars': (m_merge_vars, 2, True),
    'reorder_independent_calls': (m_reorder_independent_calls, 2, True),
    'hoist_invariant': (m_hoist_invariant, 2, True),
    'sink_invariant': (m_sink_invariant, 2, True),
    'param_copy': (m_param_copy, 2, True),
}


SOURCE_MUTATIONS = {
    'decl_axis': (m_decl_axis, 1, True),
}


def mutate(body, rng, *, allow_risky=False, only=None, tries=12):
    """Apply one random applicable mutation in place; return description or None."""
    names = [k for k, (_, w, safe) in MUTATIONS.items()
             if (safe or allow_risky) and (only is None or k in only)]
    if not names:
        return None
    weights = [MUTATIONS[k][1] for k in names]
    for _ in range(tries):
        name = rng.choices(names, weights)[0]
        try:
            mutation = MUTATIONS[name][0]
            if name == 'reorder_independent_calls':
                desc = mutation(body, rng, allow_risky=allow_risky)
            else:
                desc = mutation(body, rng)
        except Exception as error:  # a bug in one mutation must not stop the search
            desc = None
        if desc:
            return desc
    return None
