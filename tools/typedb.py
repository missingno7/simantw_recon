"""Build and apply a program-wide declaration database for recovered SimAnt C.

The database treats source declarations as evidence only when a byte-matched
member body in that source actually uses the name.  Scaffold annotations and
POOLSTUB_TEXT functions are excluded.  Machine evidence is diagnostic and never
overrides a verified source declaration.
"""
from __future__ import annotations

import argparse
import copy
import json
import math
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

from pycparser import c_ast, c_generator, CParser

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))

import c_source
import mapsym
import ne
import permuter_mutations as mutations
from common import FormatError, fixture, read_json, write_json

DB_PATH = ROOT / 'build/typedb/typedb.json'
RECOVERY_PATH = ROOT / 'src/recovery.json'
CARDS_PATH = ROOT / 'evidence/disassembly/cards.jsonl'

SCAFFOLD_RE = re.compile(r'\b(scaffold|stand[- ]?in|poolstub|pool stub)\b', re.I)
IDENT = re.compile(r'\b[A-Za-z_]\w*\b')
_SOURCE_TARGETS_CACHE = None
SIGNED_JUMPS = {'jl', 'jle', 'jg', 'jge', 'jnl', 'jnle', 'jng', 'jnge'}
UNSIGNED_JUMPS = {'ja', 'jae', 'jb', 'jbe', 'jnbe', 'jnb', 'jna', 'jnae', 'jc', 'jnc'}


def _mask_directives(text: str) -> str:
    """Blank preprocessor lines while retaining every source offset and newline."""
    out = list(text)
    visible = c_source.mask_comments_and_strings(text)
    for m in re.finditer(r'(?m)^\s*#.*$', visible):
        for i in range(m.start(), m.end()):
            if out[i] != '\n':
                out[i] = ' '
    return ''.join(out)


def _strip_comments_preserve(text: str) -> str:
    """Blank comments and literal contents without changing offsets or lines."""
    return c_source.mask_comments_and_strings(text)


def _stub_bodies(text: str, funcs) -> str:
    """Replace function bodies with whitespace, keeping source coordinates stable."""
    out = list(text)
    for f in funcs:
        for i in range(f['body_start'] + 1, f['body_end'] - 1):
            if out[i] != '\n':
                out[i] = ' '
    return ''.join(out)


def _expand_object_macros(text, original):
    """Expand object-like macros needed in declaration types, not function macros."""
    macros = {}
    for line in original.splitlines():
        m = re.match(r'^\s*#\s*define\s+([A-Za-z_]\w*)(\s*)(.*)$', line)
        if not m or m.group(2) == '':
            continue
        name, _, value = m.groups()
        if name in ('defined',):
            continue
        if re.match(r'[A-Za-z_]\w*\s*\(', value):
            continue
        value = value.split('//', 1)[0].split('/*', 1)[0].strip()
        if value and name not in IDENT.findall(value):
            macros[name] = value
    out = text
    # Do a small fixed-point pass for aliases such as EXT -> WORD -> int.
    for _ in range(6):
        changed = False
        for name, value in macros.items():
            visible = c_source.mask_comments_and_strings(out)
            matches = list(re.finditer(r'\b' + re.escape(name) + r'\b', visible))
            if matches and value != name:
                parts, pos = [], 0
                for m in matches:
                    parts.extend((out[pos:m.start()], value))
                    pos = m.end()
                parts.append(out[pos:])
                out = ''.join(parts)
                changed = True
        if not changed:
            break
    return out


def _map_msc_for_parser(text, original):
    """Use the permuter mapper, with small grammar adapters for MSC-only forms."""
    text = _expand_object_macros(text, original)
    # MSC's __segment is a 16-bit selector type.  Give pycparser a scalar while
    # the source spelling remains available to the declaration evidence record.
    text = re.sub(r'\b__segment\b\s*(?:near|_near|far|_far)?', 'unsigned int', text)
    text = re.sub(r'\b(?:__export|_export|export|interrupt|_interrupt|fortran|_fortran|_loadds|_saveregs)\b', '', text)
    # The MSC function-pointer distance precedes '*'; in C grammar its nearest
    # equivalent is a pointer qualifier following '*'.
    text = re.sub(r'\(\s*(?:(?:pascal|cdecl)\s+)?(?:far|_far|__far)(?:\s+(?:pascal|cdecl))?\s+\*', '(* volatile ', text)
    return mutations.map_dialect(text)


def scan_externals(text: str):
    """Return top-level source spans, including function definitions and declarations."""
    masked = c_source.mask_comments_and_strings(text)
    funcs = c_source.top_level_functions(text)
    by_start = {f['header_start']: f for f in funcs}
    spans = []
    i, n = 0, len(text)
    while i < n:
        while i < n and text[i].isspace():
            i += 1
        if i >= n:
            break
        # Preprocessor lines are whitespace to the parser but stay in the user's file.
        if masked[i] == '#':
            e = text.find('\n', i)
            i = n if e < 0 else e + 1
            continue
        f = next((v for k, v in by_start.items() if k >= i and not masked[i:k].strip()), None)
        if f:
            spans.append({'start': f['header_start'], 'end': f['body_end'], 'body_start': f['body_start'], 'function': True})
            i = f['body_end']
            continue
        start = i
        paren = bracket = brace = 0
        quote = None
        escaped = False
        while i < n:
            ch = masked[i]
            if quote:
                if escaped:
                    escaped = False
                elif ch == '\\':
                    escaped = True
                elif ch == quote:
                    quote = None
            elif ch in ('"', "'"):
                quote = ch
            elif ch == '(':
                paren += 1
            elif ch == ')':
                paren = max(0, paren - 1)
            elif ch == '[':
                bracket += 1
            elif ch == ']':
                bracket = max(0, bracket - 1)
            elif ch == '{':
                brace += 1
            elif ch == '}':
                brace = max(0, brace - 1)
            elif ch == ';' and paren == bracket == brace == 0:
                i += 1
                spans.append({'start': start, 'end': i, 'body_start': None, 'function': False})
                break
            i += 1
        else:
            if masked[start:i].strip():
                spans.append({'start': start, 'end': i, 'body_start': None, 'function': False})
    return spans


def _declared_name_in_span(text, span, name):
    """Check the declaration portion before its initializer for this declarator name."""
    raw = text[span['start']:span['body_start'] if span['function'] else span['end']]
    masked = c_source.mask_comments_and_strings(raw)
    paren = bracket = brace = 0
    split = len(masked)
    for i, ch in enumerate(masked):
        if ch == '(': paren += 1
        elif ch == ')': paren = max(0, paren - 1)
        elif ch == '[': bracket += 1
        elif ch == ']': bracket = max(0, bracket - 1)
        elif ch == '{': brace += 1
        elif ch == '}': brace = max(0, brace - 1)
        elif ch == '=' and paren == bracket == brace == 0:
            split = i
            break
    return bool(re.search(r'\b' + re.escape(name) + r'\b', masked[:split]))


def _function_standin_names(text, funcs):
    names = set()
    for m in re.finditer(r'(?im)^\s*#\s*pragma\s+alloc_text\s*\(\s*POOLSTUB_TEXT\s*,([^)]*)\)', text):
        names.update(x for x in IDENT.findall(m.group(1)) if x.upper() != 'POOLSTUB_TEXT')
    for f in funcs:
        body = text[f['header_start']:f['body_end']]
        prefix = text[max(0, f['header_start'] - 240):f['header_start']]
        if f['name'].lower().startswith(('pool_stub', 'poolstub', 'scaffold_stub')) or SCAFFOLD_RE.search(body) or re.search(r'POOLSTUB_TEXT', prefix, re.I):
            names.add(f['name'])
    return names


def _parse_unit(text: str, path=''):
    """Parse an MSC dialect source with the existing permuter dialect adapter."""
    preprocessed = _strip_comments_preserve(_mask_directives(text))
    funcs = c_source.top_level_functions(preprocessed)
    standins = _function_standin_names(text, funcs)
    actual_code = c_source.mask_comments_and_strings(preprocessed)
    uses = defaultdict(set)
    for f in funcs:
        if f['name'] in standins:
            continue
        code = actual_code[f['body_start']:f['body_end']]
        uses[f['name']].update(IDENT.findall(code))
    macro_refs = _macro_reference_map(text)
    for names in uses.values():
        pending = list(names)
        while pending:
            current = pending.pop()
            for dependency in macro_refs.get(current, ()):
                if dependency not in names:
                    names.add(dependency)
                    pending.append(dependency)
    parser_text = _stub_bodies(preprocessed, funcs)
    try:
        ast = CParser().parse(_map_msc_for_parser(parser_text, text), filename=path or '<source>')
    except Exception as exc:
        return {'path': path, 'source': text, 'parsed_text': preprocessed, 'ast': None,
                'funcs': funcs, 'standins': standins, 'uses': uses,
                'spans': scan_externals(preprocessed), 'error': str(exc)}
    spans = scan_externals(preprocessed)
    # AST and source scanner both preserve external declaration order.  Keep the
    # mapping explicit so resync can edit only file-scope ranges.
    ext_spans = []
    line_offsets = [0]
    line_offsets.extend(m.end() for m in re.finditer('\n', preprocessed))
    cursor = 0
    assigned = Counter()
    for ext in ast.ext:
        name = getattr(ext, 'name', None)
        if isinstance(ext, c_ast.FuncDef):
            name = ext.decl.name
        match = None
        coord = getattr(ext, 'coord', None)
        if coord and coord.line:
            line_start = line_offsets[min(coord.line - 1, len(line_offsets) - 1)]
            line_end = line_offsets[min(coord.line, len(line_offsets) - 1)] if coord.line < len(line_offsets) else len(preprocessed)
            for idx in range(cursor, len(spans)):
                span = spans[idx]
                in_line = span['start'] <= line_start < span['end'] or line_start <= span['start'] < line_end
                name_match = (not name) or _declared_name_in_span(preprocessed, span, name)
                if in_line and name_match and isinstance(ext, c_ast.FuncDef) == bool(span['function']):
                    if assigned[(idx, name)] == 0:
                        match = idx
                        break
        for idx in range(cursor, len(spans)):
            if match is not None:
                break
            span = spans[idx]
            raw = preprocessed[span['start']:span['end']]
            if name and re.search(r'\b' + re.escape(name) + r'\b', c_source.mask_comments_and_strings(raw)):
                if isinstance(ext, c_ast.FuncDef) == bool(span['function']):
                    match = idx
                    break
            elif not name and not span['function']:
                # Anonymous tag-only declarations have no useful name to match.
                match = idx
                break
        if match is None:
            ext_spans.append(None)
        else:
            ext_spans.append(spans[match])
            cursor = match
            assigned[(match, name)] += 1
    return {'path': path, 'source': text, 'parsed_text': preprocessed, 'ast': ast,
            'funcs': funcs, 'standins': standins, 'uses': uses, 'spans': spans,
            'ext_spans': ext_spans, 'error': None}


def _walk(node):
    if node is None:
        return
    yield node
    if isinstance(node, c_ast.Node):
        for _, child in node.children():
            yield from _walk(child)


def _decl_name(ext):
    if isinstance(ext, c_ast.FuncDef):
        return ext.decl.name
    return getattr(ext, 'name', None)


def _decl_node(ext):
    return ext.decl if isinstance(ext, c_ast.FuncDef) else ext


def _shape(node):
    """JSON-safe structural AST description; dialect markers are retained in text."""
    if node is None:
        return None
    if not isinstance(node, c_ast.Node):
        return node
    out = {'node': type(node).__name__}
    for key in getattr(node, 'attr_names', ()):
        value = getattr(node, key)
        if value is not None:
            out[key] = value
    for key, value in node.children():
        attr = key.split('[', 1)[0]
        if attr not in out:
            out[attr] = []
        out[attr].append(_shape(value))
    return out


def _clear_parameter_names(node):
    """Clear prototype parameter identifiers without changing field/member names."""
    if not isinstance(node, c_ast.Node):
        return
    if isinstance(node, c_ast.FuncDecl) and node.args:
        for param in node.args.params or []:
            if isinstance(param, c_ast.Decl):
                param.name = None
                for part in _walk(param.type):
                    if isinstance(part, c_ast.TypeDecl):
                        part.declname = None
    for _, child in node.children():
        _clear_parameter_names(child)


def _render_decl(ext, source, *, keep_storage=False, keep_initializer=False):
    decl = copy.deepcopy(_decl_node(ext))
    if not isinstance(decl, c_ast.Decl):
        return ''
    _clear_parameter_names(decl.type)
    if not keep_storage:
        decl.storage = []
        decl.funcspec = []
    if not keep_initializer:
        decl.init = None
    return c_generator.CGenerator().visit(decl).strip()


def _normalize(text):
    text = re.sub(r'\s+', ' ', text).strip()
    text = re.sub(r'\s*([*(),\[\]])\s*', r'\1', text)
    text = re.sub(r'\s*=\s*.*$', '', text)
    return text


def _dialect_tags(raw):
    """Keep MSC ABI/storage distinctions that the C grammar adapter erases."""
    visible = c_source.mask_comments_and_strings(raw)
    tags = []
    for word in ('pascal', '_pascal', 'cdecl', '_cdecl', 'interrupt', '_interrupt',
                 'fortran', '_fortran', '_loadds', '_saveregs', '__segment'):
        if re.search(r'\b' + re.escape(word) + r'\b', visible):
            tags.append(word.lstrip('_'))
    for m in re.finditer(r'\b(?:__based|_based)\s*\(', visible):
        phrase = mutations._based_phrase(raw, m.start())
        if phrase:
            tags.append(re.sub(r'\s+', '', phrase))
    return (' [msc:' + ','.join(sorted(set(tags))) + ']') if tags else ''


def _raw_for(parsed, ext_index):
    if not parsed.get('ast'):
        return ''
    span = parsed.get('ext_spans', [])[ext_index]
    if not span:
        return ''
    return parsed['source'][span['start']:span['end']].strip()


def _is_scaffold_decl(parsed, ext_index):
    raw = _raw_for(parsed, ext_index)
    span = parsed.get('ext_spans', [])[ext_index]
    if not span:
        return False
    start = span['start']
    context = parsed['source'][max(0, start - 220):span['end']]
    nearest = re.findall(r'/\*.*?\*/|//[^\r\n]*', context, re.S)
    marker = ' '.join(nearest[-2:])
    explicit = re.search(r'scaffold\s+reference|stand[- ]?in\s+reference|scaffold\s+only|pool\s+word', marker, re.I)
    named = bool(re.search(r'\bscaffold\w*\b', raw, re.I))
    return bool(explicit or named)


def _source_targets():
    global _SOURCE_TARGETS_CACHE
    if _SOURCE_TARGETS_CACHE is not None:
        return _SOURCE_TARGETS_CACHE
    targets = read_json(RECOVERY_PATH)['targets']
    by_source = defaultdict(set)
    for symbol, row in targets.items():
        if row.get('proof') not in ('BYTE_MATCHED_RECONSTRUCTION', 'BYTE_MATCHED_DATA_RECONSTRUCTION'):
            continue
        source = row.get('source')
        if source and source.lower().endswith('.c') and source.replace('\\', '/').startswith('src/recovered/'):
            if row.get('proof') == 'BYTE_MATCHED_RECONSTRUCTION' and row.get('comparison') in ('member', 'function'):
                by_source[source.replace('\\', '/')].add(symbol)
            else:
                by_source.setdefault(source.replace('\\', '/'), set())
    _SOURCE_TARGETS_CACHE = by_source
    return _SOURCE_TARGETS_CACHE


def _macro_reference_map(text):
    keywords = set(c_source.KEYWORDS) | {'__export', '_export', 'export'}
    result = {}
    for line in text.splitlines():
        m = re.match(r'^\s*#\s*define\s+([A-Za-z_]\w*)(?:\(([^)]*)\))?\s*(.*)$', line)
        if not m:
            continue
        name, params, value = m.groups()
        args = set(IDENT.findall(params or ''))
        refs = set(IDENT.findall(value)) - keywords - args - {name}
        if refs:
            result[name] = refs
    return result


def _admitted_body_names(parsed, admitted_symbols):
    available = {f['name']: f for f in parsed['funcs']}
    wanted = set()
    for sym in admitted_symbols:
        for name in (sym, sym.lstrip('_'), '_' + sym.lstrip('_')):
            if name in available and name not in parsed['standins']:
                wanted.add(name)
    return wanted


def _decl_record(parsed, idx, ext, body_symbols):
    name = _decl_name(ext)
    if not name or _is_scaffold_decl(parsed, idx):
        return None
    # A declaration counts only if an admitted body in this source mentions it.
    used = any(name in parsed['uses'].get(fn, set()) for fn in body_symbols)
    if isinstance(ext, c_ast.FuncDef) and name in body_symbols:
        used = True
    if not used:
        return None
    if isinstance(ext, c_ast.Typedef):
        rendered = c_generator.CGenerator().visit(ext).strip()
        signature = rendered
        kind = 'typedef'
    else:
        rendered = _render_decl(ext, parsed['parsed_text'], keep_storage=True, keep_initializer=False)
        signature = _render_decl(ext, parsed['parsed_text'], keep_storage=False, keep_initializer=False)
        kind = 'function' if isinstance(_decl_node(ext).type, c_ast.FuncDecl) else 'data'
    raw = _raw_for(parsed, idx)
    span = parsed.get('ext_spans', [])[idx]
    if span and span['function']:
        raw = parsed['source'][span['start']:span['body_start']].strip()
        raw = c_source.strip_comments(raw).strip().rstrip('{').rstrip() + ';'
    else:
        raw = c_source.strip_comments(raw).strip()
    if not raw:
        raw = rendered.rstrip(';') + ';'
    signature = _normalize(signature + _dialect_tags(raw))
    dependencies = _dependencies_for(parsed, ext)
    return {'name': name, 'kind': kind,
            'signature': _normalize(signature), 'declaration': raw,
            'shape': _shape(_decl_node(ext).type), 'dependencies': dependencies,
            'source': parsed['path'], 'raw': _raw_for(parsed, idx),
            'source_index': idx, 'span': parsed['ext_spans'][idx]}


def _available_type_definitions(parsed):
    result = {}
    if not parsed.get('ast'):
        return result
    for idx, ext in enumerate(parsed['ast'].ext):
        span = parsed.get('ext_spans', [None] * len(parsed['ast'].ext))[idx]
        if not span:
            continue
        if isinstance(ext, c_ast.Typedef):
            result[ext.name] = {'name': ext.name, 'kind': 'typedef', 'declaration': _raw_for(parsed, idx), '_node': ext}
        for node in _walk(ext):
            if isinstance(node, (c_ast.Struct, c_ast.Union)) and node.name and node.decls:
                raw = _raw_for(parsed, idx)
                # A typedef may carry the tag definition in its declaration;
                # keep the typedef, which is the complete source form.
                if isinstance(ext, c_ast.Typedef):
                    result[node.name] = {'name': node.name, 'kind': 'struct', 'declaration': raw, '_node': ext}
                elif _decl_name(ext) is None:
                    result[node.name] = {'name': node.name, 'kind': 'struct', 'declaration': raw, '_node': ext}
    return result


def _dependencies_for(parsed, ext):
    available = _available_type_definitions(parsed)
    needed, visiting = {}, set()

    def references(root):
        refs = set()
        for node in _walk(root):
            if isinstance(node, c_ast.IdentifierType):
                refs.update(name for name in node.names if name in available)
            elif isinstance(node, (c_ast.Struct, c_ast.Union)) and node.name and node.name in available:
                refs.add(node.name)
        return refs

    def visit(name):
        if name in needed or name in visiting or name not in available:
            return
        visiting.add(name)
        row = available[name]
        for dependency in sorted(references(row['_node'])):
            if dependency != name:
                visit(dependency)
        visiting.remove(name)
        needed[name] = {k: v for k, v in row.items() if k != '_node'}

    for name in sorted(references(_decl_node(ext).type)):
        visit(name)
    return list(needed.values())


def _confidence(n):
    return round(1.0 - math.exp(-n / 3.0), 3)


def _choose_canonical(rows):
    """Select the majority verified form, with a stable lexical tie-break."""
    return sorted(rows, key=lambda x: (-x['source_count'], x['signature']))[0]


def _width_from_row(row):
    t = (row.get('operands') or '').lower()
    for word, width in (('byte ptr', 1), ('word ptr', 2), ('dword ptr', 4), ('qword ptr', 8)):
        if word in t:
            return width
    # Register-only operands often reveal the memory width on MOV/TEST/CMP.
    if re.search(r'\b(?:al|ah|bl|bh|cl|ch|dl|dh)\b', t):
        return 1
    if re.search(r'\b(?:ax|bx|cx|dx|si|di)\b', t):
        return 2
    return None


def _machine_evidence():
    evidence = defaultdict(lambda: {'access_widths': Counter(), 'sign_extension': Counter(),
                                    'zero_extension': Counter(), 'jumps': Counter(),
                                    'far_loads': Counter(), 'strides': Counter(),
                                    'functions': set(), 'examples': []})
    functions = defaultdict(lambda: {'param_accesses': defaultdict(Counter), 'calls': Counter(),
                                     'arg_bytes': Counter(), 'returns': Counter(),
                                     'call_distance': Counter(), 'argument_pushes': Counter(),
                                     'far_pointer_push_pairs': Counter(), 'unextended_byte_pushes': Counter(),
                                     'examples': []})
    executable = fixture('SIMANTW.EXE')
    ne_image = ne.parse(executable)
    sym_image = mapsym.parse(fixture('SIMANTW.SYM'))
    sym_check = mapsym.cross_check(sym_image, ne_image)
    sym_at = defaultdict(list)
    for seg in sym_image['segments']:
        for item in seg['symbols']:
            sym_at[(seg['number'], item['offset'])].append(item['name'])
    verified_rows = 0
    byte_mismatches = []
    cards = [json.loads(line) for line in CARDS_PATH.read_text(encoding='utf-8').splitlines() if line.strip()]
    for card in cards:
        sym = card.get('symbol')
        segment_number = card.get('segment')
        segment = ne_image['segments'][segment_number - 1] if isinstance(segment_number, int) and 1 <= segment_number <= len(ne_image['segments']) else None
        rows = card.get('disassembly') or []
        reg_source = {}
        for i, row in enumerate(rows):
            # The existing symbolized disassembly is accepted only when it names
            # the exact locked NE/MAPSYM pair and its bytes match the NE segment.
            if card.get('exe_sha256') != ne_image['sha256'] or segment is None or segment.get('file_offset') is None:
                continue
            try:
                encoded = bytes.fromhex(row.get('bytes') or '')
                start = segment['file_offset'] + int(row['offset'])
                actual = executable[start:start + len(encoded)]
            except (ValueError, KeyError, TypeError):
                continue
            if not encoded or actual != encoded:
                if len(byte_mismatches) < 20:
                    byte_mismatches.append({'symbol': sym, 'offset': row.get('offset')})
                continue
            verified_rows += 1
            refs = [name for ref in row.get('references', []) if ref.get('kind') == 'global_ds_assumed'
                    for name in (sym_at.get((ref.get('segment'), ref.get('offset')))
                                 or ref.get('names', []))]
            mn = row.get('mnemonic', '').lower()
            operands = (row.get('operands') or '').lower()
            for name in refs:
                ev = evidence[name]
                width = _width_from_row(row)
                if width:
                    ev['access_widths'][str(width)] += 1
                ev['functions'].add(sym)
                if mn in ('les', 'lds'):
                    ev['far_loads'][mn] += 1
                if mn == 'mov' and ',' in operands:
                    dst = operands.split(',', 1)[0].strip()
                    if dst in ('al', 'ax', 'bx', 'cx', 'dx', 'si', 'di'):
                        reg_source[dst] = name
                if mn in ('cmp', 'test'):
                    compare_name = name
                    for reg, origin in reg_source.items():
                        if re.search(r'\b' + re.escape(reg) + r'\b', operands):
                            compare_name = origin
                    nxt = rows[i + 1] if i + 1 < len(rows) else {}
                    jmn = (nxt.get('mnemonic') or '').lower()
                    if jmn in SIGNED_JUMPS | UNSIGNED_JUMPS:
                        evidence[compare_name]['jumps']['signed' if jmn in SIGNED_JUMPS else 'unsigned'] += 1
                if mn == 'mov' and width == 1 and i + 1 < len(rows):
                    ext = (rows[i + 1].get('mnemonic') or '').lower()
                    ext_ops = (rows[i + 1].get('operands') or '').lower().replace(' ', '')
                    if ext in ('cbw', 'cwd'):
                        ev['sign_extension'][ext] += 1
                    elif ext == 'sub' and ext_ops in ('ah,ah', 'ah,0'):
                        ev['zero_extension']['sub ah,ah'] += 1
                if len(ev['examples']) < 3:
                    ev['examples'].append({'function': sym, 'offset': row.get('offset'), 'instruction': mn + ' ' + operands})
                # Scaled-index clues are supporting evidence only; 16-bit x86 has
                # no scaled addressing mode, so look for a nearby shift/multiply.
                for prev in rows[max(0, i - 4):i]:
                    pm = (prev.get('mnemonic') or '').lower()
                    po = (prev.get('operands') or '').lower()
                    m = re.search(r'\b(?:shl|sal)\s+\w+\s*,\s*(\d+)', pm + ' ' + po)
                    if m:
                        ev['strides'][str(1 << int(m.group(1)))] += 1
                        break
            # Callee-side stack parameter evidence.
            m = re.search(r'\[bp\s*\+\s*(0x[\da-f]+|\d+)\]', operands)
            if m:
                try:
                    off = int(m.group(1), 0)
                except ValueError:
                    off = int(m.group(1))
                functions[sym]['param_accesses'][str(off)][str(_width_from_row(row) or 0)] += 1
                if mn == 'mov' and re.search(r',\s*al\b', operands) and i + 1 < len(rows):
                    nxt = (rows[i + 1].get('mnemonic') or '').lower()
                    if nxt in ('cbw', 'cwd'):
                        functions[sym]['param_accesses'][str(off)]['signed'] += 1
            # Call-site argument cleanup and distance, keyed by target.
            for ref in row.get('references', []):
                if ref.get('kind') not in ('near_call', 'internal', 'import') and 'call' not in mn:
                    continue
                if 'call' not in mn:
                    continue
                for target in ref.get('names', []):
                    functions[target]['calls'][sym] += 1
                    functions[target]['call_distance']['far' if mn in ('lcall', 'callf') else 'near'] += 1
                    prior = rows[max(0, i - 10):i]
                    push_indexes = [j for j in range(max(0, i - 10), i)
                                    if (rows[j].get('mnemonic') or '').lower() == 'push']
                    push_rows = [rows[j] for j in push_indexes]
                    pushes = len(push_indexes)
                    functions[target]['argument_pushes'][str(pushes)] += 1
                    push_ops = [(x.get('operands') or '').lower() for x in push_rows]
                    if any(x.strip() in ('ds', 'es', 'ss') for x in push_ops) and any(
                            re.search(r'\b(?:offset|0x[\da-f]+|\d+)\b', x) for x in push_ops):
                        functions[target]['far_pointer_push_pairs']['observed'] += 1
                    for push_index, push in zip(push_indexes, push_rows):
                        poper = (push.get('operands') or '').lower()
                        if poper.strip() in ('ax', 'bx', 'cx', 'dx'):
                            near = rows[max(0, push_index - 3):push_index]
                            loaded_byte = any((x.get('mnemonic') or '').lower() == 'mov' and
                                              re.search(r'\b(?:al|ah|bl|bh|cl|ch|dl|dh)\b', x.get('operands') or '')
                                              for x in near)
                            extended = any((x.get('mnemonic') or '').lower() in ('cbw', 'cwd') or
                                           re.search(r'\b(?:xor|sub)\s+[abcd]h\s*,\s*[abcd]h\b',
                                                     (x.get('mnemonic') or '') + ' ' + (x.get('operands') or ''), re.I)
                                           for x in near)
                            if loaded_byte and not extended:
                                functions[target]['unextended_byte_pushes']['observed'] += 1
                    after = rows[i + 1:i + 4]
                    cleanup = next((x for x in after if (x.get('mnemonic') or '').lower() == 'add'
                                    and 'sp' in (x.get('operands') or '').lower()), None)
                    if cleanup:
                        mbytes = re.search(r'\bsp\s*,\s*(0x[\da-f]+|\d+)', cleanup.get('operands', '').lower())
                        if mbytes:
                            try:
                                functions[target]['arg_bytes'][str(int(mbytes.group(1), 0))] += 1
                            except ValueError:
                                pass
                    elif pushes:
                        functions[target]['arg_bytes'][str(pushes * 2)] += 1
        # Return-value shape at function exits.
        for i, row in enumerate(rows):
            if (row.get('mnemonic') or '').lower() not in ('ret', 'retf', 'retn'):
                continue
            before = rows[max(0, i - 5):i]
            regs = ' '.join((x.get('operands') or '').lower() for x in before)
            shape = 'DX:AX' if re.search(r'\bdx\b', regs) and re.search(r'\bax\b', regs) else \
                    'AX' if re.search(r'\bax\b', regs) else 'AL' if re.search(r'\bal\b', regs) else 'unknown'
            functions[sym]['returns'][shape] += 1
    output = {}
    for name, row in evidence.items():
        row['access_widths'] = dict(row['access_widths'])
        for key in ('sign_extension', 'zero_extension', 'jumps', 'far_loads', 'strides'):
            row[key] = dict(row[key])
        row['functions'] = sorted(row['functions'])
        row['confidence'] = _confidence(sum(row['access_widths'].values()) + sum(row['sign_extension'].values()) + sum(row['far_loads'].values()))
        output[name] = row
    funcs_out = {}
    for name, row in functions.items():
        row['param_accesses'] = {k: dict(v) for k, v in row['param_accesses'].items()}
        for key in ('calls', 'arg_bytes', 'returns', 'call_distance', 'argument_pushes',
                    'far_pointer_push_pairs', 'unextended_byte_pushes'):
            row[key] = dict(row[key])
        row['confidence'] = _confidence(sum(row['calls'].values()) + sum(row['param_accesses'].get(k, {}).get('signed', 0) for k in row['param_accesses']))
        funcs_out[name] = row
    return {'globals': output, 'functions': funcs_out,
            'metadata': {'ne_sha256': ne_image['sha256'], 'mapsym_sha256': sym_image['sha256'],
                         'mapsym_ne_status': sym_check['status'], 'disassembly_rows_verified': verified_rows,
                         'disassembly_row_byte_mismatches': byte_mismatches}}


def _build_database():
    src_targets = _source_targets()
    variants = defaultdict(lambda: defaultdict(lambda: {'sources': set(), 'declaration': '', 'shape': None, 'kind': None}))
    parse_errors = []
    files_used = set()
    for relpath, symbols in sorted(src_targets.items()):
        path = ROOT / relpath
        if not path.is_file():
            parse_errors.append({'source': relpath, 'error': 'missing admitted source'})
            continue
        source = path.read_text(encoding='latin1')
        parsed = _parse_unit(source, relpath)
        if parsed['error']:
            parse_errors.append({'source': relpath, 'error': parsed['error']})
            continue
        files_used.add(relpath)
        body_symbols = _admitted_body_names(parsed, symbols)
        if not body_symbols:
            continue
        for idx, ext in enumerate(parsed['ast'].ext):
            record = _decl_record(parsed, idx, ext, body_symbols)
            if record is None:
                continue
            v = variants[record['name']][record['signature']]
            v['sources'].add(relpath)
            v['declaration'] = record['declaration']
            v['shape'] = record['shape']
            v['kind'] = record['kind']
            v['dependencies'] = record['dependencies']
    machine = _machine_evidence()
    names = {}
    conflicts = []
    for name, found in sorted(variants.items()):
        rows = []
        for signature, item in found.items():
            rows.append({'signature': signature, 'declaration': item['declaration'],
                         'shape': item['shape'], 'kind': item['kind'],
                         'dependencies': item.get('dependencies', []),
                         'source_count': len(item['sources']), 'sources': sorted(item['sources'])})
        chosen = _choose_canonical(rows)
        record = {'canonical': chosen, 'variants': rows,
                  'conflicts': rows[1:], 'machine_evidence': machine['globals'].get(name)}
        names[name] = record
        if len(rows) > 1:
            conflicts.append({'name': name, 'canonical': chosen['signature'],
                              'alternatives': [x['signature'] for x in rows[1:]],
                              'sources': {x['signature']: x['sources'] for x in rows}})
    return {'version': 1, 'sources_scanned': len(files_used), 'source_count': len(src_targets),
            'parse_errors': parse_errors, 'names': names, 'functions': machine['functions'],
            'machine_names_without_verified_declaration': sorted(set(machine['globals']) - set(names)),
            'machine_globals': machine['globals'], 'machine_metadata': machine['metadata'], 'conflicts': conflicts}


def build_database(out=DB_PATH):
    data = _build_database()
    write_json(out, data)
    return data


def _decl_signature(parsed, idx, ext):
    if isinstance(ext, c_ast.Typedef):
        span = parsed.get('ext_spans', [None] * len(parsed['ast'].ext))[idx]
        raw = parsed['source'][span['start']:span['end']] if span else ''
        return _normalize(c_generator.CGenerator().visit(ext) + _dialect_tags(raw))
    if not isinstance(_decl_node(ext), c_ast.Decl):
        return None
    span = parsed.get('ext_spans', [None] * len(parsed['ast'].ext))[idx]
    raw = ''
    if span:
        end = span['body_start'] if span['function'] else span['end']
        raw = parsed['source'][span['start']:end]
    signature = _render_decl(ext, parsed['parsed_text'], keep_storage=False, keep_initializer=False)
    return _normalize(signature + _dialect_tags(raw))


def _type_soft_conflicts(signature, evidence):
    if not evidence:
        return []
    lower = signature.lower()
    findings = []
    if evidence.get('sign_extension', {}).get('cbw') and re.search(r'\bunsigned\s+char\b', lower):
        findings.append('byte loads are sign-extended with cbw; declaration is unsigned char')
    if evidence.get('zero_extension', {}).get('sub ah,ah') and re.search(r'(?<!unsigned )\bchar\b', lower):
        findings.append('byte loads are zero-extended; declaration spells plain char')
    if evidence.get('far_loads') and not re.search(r'\bfar\s*\*|\bfar\b', lower):
        findings.append('LES/LDS evidence suggests a far pointer view')
    if evidence.get('jumps', {}).get('signed') and re.search(r'\bunsigned\b', lower):
        findings.append('signed conditional jumps use this value; declaration is unsigned')
    if evidence.get('jumps', {}).get('unsigned') and not re.search(r'\bunsigned\b', lower) and re.search(r'\b(?:int|short|long|char)\b', lower):
        findings.append('unsigned conditional jumps use this value; declaration is signed or plain char')
    return findings


def check_source(path, database=None):
    db = database or read_json(DB_PATH)
    p = Path(path)
    text = p.read_text(encoding='latin1')
    parsed = _parse_unit(text, str(p))
    if parsed['error']:
        return {'source': str(path), 'parse_error': parsed['error'], 'hard_conflicts': [], 'soft_conflicts': []}
    own_path = None
    try:
        own_path = p.resolve().relative_to(ROOT).as_posix()
    except ValueError:
        pass
    source_targets = _source_targets() if own_path else {}
    is_admitted_source = own_path in source_targets if own_path else False
    admitted_targets = source_targets.get(own_path, set()) if is_admitted_source else set()
    admitted_bodies = _admitted_body_names(parsed, admitted_targets) if admitted_targets else set()
    hard, soft = [], []
    for idx, ext in enumerate(parsed['ast'].ext):
        name = _decl_name(ext)
        if not name:
            continue
        if _is_scaffold_decl(parsed, idx):
            continue
        if is_admitted_source:
            body_used = any(name in parsed['uses'].get(fn, set()) for fn in admitted_bodies)
            if isinstance(ext, c_ast.FuncDef) and name in admitted_bodies:
                body_used = True
            if not body_used:
                continue
        signature = _decl_signature(parsed, idx, ext)
        verified = db['names'].get(name)
        if verified:
            canonical = verified['canonical']['signature']
            if signature != canonical:
                own_form = any(v['signature'] == signature and own_path in v['sources'] for v in verified['variants'])
                if not own_form:
                    hard.append({'name': name, 'draft': signature, 'verified': canonical,
                                 'supported_variants': [v['signature'] for v in verified['variants']]})
        else:
            ev = db.get('machine_globals', {}).get(name)
            for finding in _type_soft_conflicts(signature or '', ev):
                soft.append({'name': name, 'draft': signature, 'machine_evidence': finding,
                             'confidence': (ev or {}).get('confidence', 0)})
    return {'source': str(path), 'parse_error': None, 'hard_conflicts': hard, 'soft_conflicts': soft}


def _canonical_ast(record, name):
    canonical = record['canonical']['declaration']
    # First parse the declaration alone. Incomplete struct pointer views are valid
    # declarations, and unrelated typedefs from the complete dependency closure
    # can otherwise make pycparser reject a perfectly usable prototype.
    dependencies = record['canonical'].get('dependencies', [])
    prefixes = ['', '\n'.join(x['declaration'] for x in dependencies) + '\n']
    for prefix in prefixes:
        try:
            src = _mask_directives(prefix + canonical)
            ast = CParser().parse(_map_msc_for_parser(src, canonical), filename='<typedb-canonical>')
            for ext in ast.ext:
                if isinstance(ext, c_ast.Typedef) and ext.name == name:
                    return copy.deepcopy(ext), src
                if isinstance(ext, c_ast.Decl) and ext.name == name:
                    return copy.deepcopy(ext), src
                if isinstance(ext, c_ast.FuncDef) and ext.decl.name == name:
                    return copy.deepcopy(ext.decl), src
        except Exception:
            pass
    return None, canonical


def _render_function_header(candidate, canonical, canonical_source, declaration_source):
    """Render verified parameter types while retaining body parameter names."""
    canonical = copy.deepcopy(canonical)
    canonical.storage = list(candidate.storage or [])
    canonical.funcspec = list(candidate.funcspec or [])
    candidate_type, canonical_type = candidate.type, canonical.type
    while isinstance(candidate_type, c_ast.PtrDecl) and isinstance(canonical_type, c_ast.PtrDecl):
        candidate_type, canonical_type = candidate_type.type, canonical_type.type
    if isinstance(candidate_type, c_ast.FuncDecl) and isinstance(canonical_type, c_ast.FuncDecl):
        candidate_args = candidate_type.args.params if candidate_type.args else []
        canonical_args = canonical_type.args.params if canonical_type.args else []
        if len(candidate_args) == 1 and isinstance(candidate_args[0], c_ast.Typename) and isinstance(candidate_args[0].type, c_ast.TypeDecl) and isinstance(candidate_args[0].type.type, c_ast.IdentifierType) and candidate_args[0].type.type.names == ['void']:
            candidate_args = []
        if len(canonical_args) == 1 and isinstance(canonical_args[0], c_ast.Typename) and isinstance(canonical_args[0].type, c_ast.TypeDecl) and isinstance(canonical_args[0].type.type, c_ast.IdentifierType) and canonical_args[0].type.type.names == ['void']:
            canonical_args = []
        if len(candidate_args) != len(canonical_args):
            return ''
        for current, verified in zip(candidate_args, canonical_args):
            if isinstance(current, c_ast.Decl) and isinstance(verified, c_ast.Decl) and current.name:
                verified.name = current.name
                type_decl = next((n for n in _walk(verified.type) if isinstance(n, c_ast.TypeDecl)), None)
                if type_decl is not None:
                    type_decl.declname = current.name
    rendered = mutations.FarGenerator(source=canonical_source).visit(canonical).strip()
    rendered = re.sub(r';\s*$', '', rendered)
    # The replacement starts at the function header; function bodies and their
    # parameter references remain byte-for-byte as authored in the draft.
    return rendered


def _body_member_fields(parsed, name):
    visible = c_source.mask_comments_and_strings(parsed['source'])
    pattern = r'\b' + re.escape(name) + r'\s*(?:\.|->)\s*([A-Za-z_]\w*)'
    return {m.group(1) for m in re.finditer(pattern, visible)}


def _body_array_access(parsed, name):
    pattern = re.compile(r'\b' + re.escape(name) + r'\s*\[')
    directives = '\n'.join(line for line in parsed['source'].splitlines()
                            if re.match(r'^\s*#\s*define\b', line))
    if pattern.search(c_source.mask_comments_and_strings(directives)):
        return True
    for func in parsed['funcs']:
        if func['name'] in parsed['standins']:
            continue
        body = parsed['source'][func['body_start']:func['body_end']]
        if pattern.search(c_source.mask_comments_and_strings(body)):
            return True
    return False


def _body_pointer_arithmetic(parsed, name):
    pattern = re.compile(r'\b' + re.escape(name) + r'\s*[+-]\s*')
    directives = '\n'.join(line for line in parsed['source'].splitlines()
                            if re.match(r'^\s*#\s*define\b', line))
    if pattern.search(c_source.mask_comments_and_strings(directives)):
        return True
    for func in parsed['funcs']:
        if func['name'] in parsed['standins']:
            continue
        body = c_source.mask_comments_and_strings(parsed['source'][func['body_start']:func['body_end']])
        if pattern.search(body):
            return True
    return False


def _body_scalar_lvalue(parsed, name):
    identifier = r'\b' + re.escape(name) + r'\b'
    writes = re.compile(identifier + r'(?!\s*(?:\[|\.|->))\s*(?:\+=|-=|\*=|/=|%=|(?<![=!<>])=(?!=)|\+\+|--)')
    prefix = re.compile(r'(?:\+\+|--)\s*' + identifier)
    for func in parsed['funcs']:
        if func['name'] in parsed['standins']:
            continue
        body = c_source.mask_comments_and_strings(parsed['source'][func['body_start']:func['body_end']])
        if writes.search(body) or prefix.search(body):
            return True
    return False


def _body_call_arities(parsed, name):
    arities = set()
    pattern = re.compile(r'\b' + re.escape(name) + r'\s*\(')
    for func in parsed['funcs']:
        if func['name'] in parsed['standins']:
            continue
        body = c_source.mask_comments_and_strings(parsed['source'][func['body_start']:func['body_end']])
        for match in pattern.finditer(body):
            opening = body.find('(', match.start(), match.end())
            depth = bracket = brace = 0
            commas = 0
            for i in range(opening + 1, len(body)):
                ch = body[i]
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    if depth == bracket == brace == 0:
                        content = body[opening + 1:i].strip()
                        arities.add(0 if not content else commas + 1)
                        break
                    depth = max(0, depth - 1)
                elif ch == '[':
                    bracket += 1
                elif ch == ']':
                    bracket = max(0, bracket - 1)
                elif ch == '{':
                    brace += 1
                elif ch == '}':
                    brace = max(0, brace - 1)
                elif ch == ',' and depth == bracket == brace == 0:
                    commas += 1
    return arities


def _form_function_arity(form, name):
    decl, _ = _canonical_ast({'canonical': form}, name)
    if decl is None:
        return None
    node = decl.type
    while isinstance(node, c_ast.PtrDecl):
        node = node.type
    if not isinstance(node, c_ast.FuncDecl):
        return None
    params = node.args.params if node.args else []
    if len(params) == 1 and isinstance(params[0], c_ast.Typename) and isinstance(params[0].type, c_ast.TypeDecl) and isinstance(params[0].type.type, c_ast.IdentifierType) and params[0].type.type.names == ['void']:
        return (0, False)
    variadic = any(isinstance(p, c_ast.EllipsisParam) for p in params)
    return (sum(not isinstance(p, c_ast.EllipsisParam) for p in params), variadic)


def _function_parameter_fields(parsed, name):
    for ext in parsed['ast'].ext:
        if not isinstance(ext, c_ast.FuncDef) or ext.decl.name != name:
            continue
        node = ext.decl.type
        while isinstance(node, c_ast.PtrDecl):
            node = node.type
        if not isinstance(node, c_ast.FuncDecl) or not node.args:
            return {}
        return {i: _body_member_fields(parsed, param.name)
                for i, param in enumerate(node.args.params)
                if isinstance(param, c_ast.Decl) and param.name and _body_member_fields(parsed, param.name)}
    return {}


def _declaration_is_indexable(parsed, name):
    for ext in parsed['ast'].ext:
        if _decl_name(ext) == name and isinstance(_decl_node(ext), c_ast.Decl):
            return isinstance(ext.type, (c_ast.ArrayDecl, c_ast.PtrDecl))
    return False


def _form_is_array(form, name):
    prefix = '\n'.join(x['declaration'] for x in form.get('dependencies', []))
    src = _mask_directives(prefix + '\n' + form.get('declaration', ''))
    try:
        ast = CParser().parse(_map_msc_for_parser(src, form.get('declaration', '')), filename='<typedb-form>')
    except Exception:
        return False
    for ext in ast.ext:
        if _decl_name(ext) == name and isinstance(_decl_node(ext), c_ast.Decl):
            return isinstance(ext.type, c_ast.ArrayDecl)
    return False


def _struct_fields_for_variant(variant):
    prefix = '\n'.join(x['declaration'] for x in variant.get('dependencies', []))
    src = _mask_directives(prefix + '\n' + variant['declaration'])
    try:
        ast = CParser().parse(_map_msc_for_parser(src, variant['declaration']), filename='<typedb-variant>')
    except Exception:
        return set()
    result = set()
    for node in _walk(ast):
        if isinstance(node, (c_ast.Struct, c_ast.Union)) and node.decls:
            result.update(d.name for d in node.decls if d.name)
    return result


def _resync_form(record, signature, parsed, name):
    """Use an already verified TU view when the member's operations support it."""
    variants = record.get('variants', [])
    exact = next((v for v in variants if v['signature'] == signature), None)
    if exact:
        return exact
    if _body_array_access(parsed, name) and _declaration_is_indexable(parsed, name):
        # Array notation can be a source view over the first scalar word. If the
        # member indexes it, keep a compilable draft view when no admitted array
        # variant exists; resync must not turn its body into invalid C.
        return {'signature': signature, 'declaration': '', 'dependencies': []}
    canonical_is_struct = bool(re.search(r'\b(?:struct|union)\s+\w+', record['canonical']['signature']))
    canonical_is_array = any(_form_is_array(v, name) for v in variants
                              if v['signature'] == record['canonical']['signature'])
    if (_body_scalar_lvalue(parsed, name) and not _declaration_is_indexable(parsed, name)
            and (canonical_is_array or canonical_is_struct)):
        # A direct assignment requires an object lvalue. Preserve a scalar/pointer
        # view when the majority form is an array or struct, which is not assignable.
        return {'signature': signature, 'declaration': '', 'dependencies': []}
    used_fields = _body_member_fields(parsed, name)
    if used_fields:
        compatible = [v for v in variants if used_fields <= _struct_fields_for_variant(v)]
        if compatible:
            return sorted(compatible, key=lambda v: (-v['source_count'], v['signature']))[0]
        return {'signature': signature, 'declaration': '', 'dependencies': []}
    if _body_pointer_arithmetic(parsed, name) and _declaration_is_indexable(parsed, name):
        return {'signature': signature, 'declaration': '', 'dependencies': []}
    parameter_fields = _function_parameter_fields(parsed, name)
    if parameter_fields:
        compatible = [v for v in variants if all(
            not fields or fields <= _struct_fields_for_variant(v)
            for fields in parameter_fields.values())]
        if compatible:
            return sorted(compatible, key=lambda v: (-v['source_count'], v['signature']))[0]
        return {'signature': signature, 'declaration': '', 'dependencies': []}
    call_arities = _body_call_arities(parsed, name)
    if call_arities:
        compatible = []
        for v in variants:
            arity = _form_function_arity(v, name)
            if arity and all(n >= arity[0] if arity[1] else n == arity[0] for n in call_arities):
                compatible.append(v)
        if compatible:
            return sorted(compatible, key=lambda v: (-v['source_count'], v['signature']))[0]
        return {'signature': signature, 'declaration': '', 'dependencies': []}
    return record['canonical']


def _top_level_initializer(raw):
    """Return the initializer suffix at the declarator's outermost '='."""
    index = _top_level_initializer_index(raw)
    return raw[index:].strip().rstrip(';') if index is not None else ''


def _top_level_initializer_index(raw):
    masked = c_source.mask_comments_and_strings(raw)
    paren = bracket = brace = 0
    for i, ch in enumerate(masked):
        if ch == '(': paren += 1
        elif ch == ')': paren = max(0, paren - 1)
        elif ch == '[': bracket += 1
        elif ch == ']': bracket = max(0, bracket - 1)
        elif ch == '{': brace += 1
        elif ch == '}': brace = max(0, brace - 1)
        elif ch == '=' and paren == bracket == brace == 0:
            return i
    return None


def _replace_declaration_text(candidate_raw, canonical_raw, storage):
    """Use the verified spelling while retaining candidate storage and initializer."""
    canonical = c_source.strip_comments(canonical_raw).strip().rstrip(';').strip()
    if _has_outer_comma(canonical):
        return ''
    # The canonical source may be a function definition header, which the record
    # stores as a prototype.  For data, drop only the leading storage class.
    canonical = re.sub(r'^(?:(?:extern|static|register|auto|typedef)\s+)+', '', canonical)
    # When the verified object declaration carries its own initializer (notably
    # typed overlay structs), it is part of the declaration's required layout.
    # Otherwise preserve an initializer supplied by the candidate TU.
    candidate_init = _top_level_initializer(canonical_raw) or _top_level_initializer(candidate_raw)
    init_at = _top_level_initializer_index(canonical)
    if init_at is not None:
        canonical = canonical[:init_at].strip()
    storage_text = ' '.join(storage or [])
    return (storage_text + ' ' if storage_text else '') + canonical + (' ' + candidate_init if candidate_init else '') + ';'


def _has_outer_comma(text):
    masked = c_source.mask_comments_and_strings(text)
    paren = bracket = brace = 0
    for ch in masked:
        if ch == '(': paren += 1
        elif ch == ')': paren = max(0, paren - 1)
        elif ch == '[': bracket += 1
        elif ch == ']': bracket = max(0, bracket - 1)
        elif ch == '{': brace += 1
        elif ch == '}': brace = max(0, brace - 1)
        elif ch == ',' and paren == bracket == brace == 0:
            return True
    return False


def resync_source(path, out, database=None):
    db = database or read_json(DB_PATH)
    p = Path(path)
    original = p.read_text(encoding='latin1')
    parsed = _parse_unit(original, str(p))
    if parsed['error']:
        raise FormatError('cannot parse draft: ' + parsed['error'])
    changed = {}
    needed_definitions = {}
    try:
        own_path = p.resolve().relative_to(ROOT).as_posix()
    except ValueError:
        own_path = None
    source_targets = _source_targets()
    is_admitted_source = bool(own_path and own_path in source_targets)
    admitted_bodies = _admitted_body_names(parsed, source_targets.get(own_path, set())) if is_admitted_source else set()

    def used_by_real_body(idx, ext):
        if _is_scaffold_decl(parsed, idx):
            return False
        name = _decl_name(ext)
        if is_admitted_source:
            if isinstance(ext, c_ast.FuncDef) and name in admitted_bodies:
                return True
            return any(name in parsed['uses'].get(fn, set()) for fn in admitted_bodies)
        if isinstance(ext, c_ast.FuncDef) and name in parsed['standins']:
            return False
        real_references = any(name in names for fn, names in parsed['uses'].items()
                              if fn not in parsed['standins'])
        if real_references:
            return True
        # Keep unused draft declarations eligible for verified resync, but never
        # let a POOLSTUB-only use supply evidence or pull a stand-in into a draft.
        standin_references = any(name in names for fn, names in parsed['uses'].items()
                                 if fn in parsed['standins'])
        return not standin_references
    nodes_by_span = defaultdict(list)
    for idx, ext in enumerate(parsed['ast'].ext):
        span = parsed['ext_spans'][idx]
        if span:
            nodes_by_span[(span['start'], span['end'])].append((idx, ext))
    replacements = []
    for span_key, ext_rows in nodes_by_span.items():
        start, end = span_key
        span = next(s for s in parsed['spans'] if s['start'] == start and s['end'] == end)
        # Function bodies are never generated: only a conflicting header is replaced.
        if span['function']:
            idx, ext = ext_rows[0]
            name = _decl_name(ext)
            if not used_by_real_body(idx, ext):
                continue
            if name not in db['names']:
                continue
            sig = _decl_signature(parsed, idx, ext)
            verified = db['names'][name]
            canonical = _resync_form(verified, sig, parsed, name)
            if sig == canonical['signature']:
                continue
            can_ast, can_source = _canonical_ast(dict(verified, canonical=canonical), name)
            if can_ast is None:
                continue
            head = _render_function_header(ext.decl, can_ast, can_source, parsed['parsed_text'])
            if not head:
                continue
            old = original[start:span['body_start']]
            # Keep leading whitespace/comments from the source header, but replace
            # the declaration itself and leave the opening brace/body byte-for-byte.
            prefix = re.match(r'\s*', old, re.S).group(0)
            header = prefix + head + '\n'
            replacements.append((start, span['body_start'], header))
            changed[name] = {'from': sig, 'to': canonical['signature']}
            for dep in canonical.get('dependencies', []):
                needed_definitions[dep['name']] = dep
            continue
        # A grouped declaration needs a token-aware split before individual
        # types can safely be changed. Leave it intact and report via `check`.
        if len(ext_rows) > 1:
            continue
        new_parts = []
        did_change = False
        for idx, ext in ext_rows:
            if isinstance(ext, c_ast.Typedef):
                name = ext.name
                if not used_by_real_body(idx, ext):
                    new_parts.append(original[start:end].strip())
                    continue
                verified = db['names'].get(name)
                sig = _decl_signature(parsed, idx, ext)
                if verified:
                    canonical = _resync_form(verified, sig, parsed, name)
                else:
                    canonical = None
                if canonical and sig != canonical['signature']:
                    replacement = canonical['declaration']
                    if not _has_outer_comma(replacement):
                        new_parts.append(replacement)
                        changed[name] = {'from': sig, 'to': canonical['signature']}
                        for dep in canonical.get('dependencies', []):
                            needed_definitions[dep['name']] = dep
                        did_change = True
                        continue
                new_parts.append(original[start:end].strip())
                continue
            if not isinstance(ext, c_ast.Decl):
                new_parts.append(original[start:end].strip())
                continue
            name = ext.name
            if not used_by_real_body(idx, ext):
                new_parts.append(original[start:end].strip())
                continue
            verified = db['names'].get(name)
            sig = _decl_signature(parsed, idx, ext)
            if verified:
                canonical = _resync_form(verified, sig, parsed, name)
            else:
                canonical = None
            if canonical and sig != canonical['signature']:
                can_ast, can_source = _canonical_ast(dict(verified, canonical=canonical), name)
                if can_ast is not None:
                    rendered = _replace_declaration_text(original[start:end], canonical['declaration'], ext.storage)
                    if not rendered:
                        new_parts.append(original[start:end].strip())
                        continue
                    new_parts.append(rendered)
                    changed[name] = {'from': sig, 'to': canonical['signature']}
                    for dep in canonical.get('dependencies', []):
                        needed_definitions[dep['name']] = dep
                    did_change = True
                    continue
            new_parts.append(mutations.FarGenerator(source=parsed['parsed_text']).visit(ext).strip() + ';')
        if did_change:
            prefix = re.match(r'\s*', original[start:end], re.S).group(0)
            replacements.append((start, end, prefix + '\n'.join(new_parts) + '\n'))
    result = original
    for start, end, value in sorted(replacements, reverse=True):
        result = result[:start] + value + result[end:]
    existing_types = _available_type_definitions(parsed)
    additions = [item['declaration'].strip() for name, item in sorted(needed_definitions.items())
                 if name not in existing_types and item.get('declaration')]
    if additions:
        result = '\n'.join(additions) + '\n' + result
    out_path = Path(out)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(result, encoding='latin1')
    return {'source': str(path), 'output': str(out), 'changed': changed, 'change_count': len(changed)}


def _machine_signed_type(evidence):
    """Toy-facing inference: direct CBW after byte loads is signed char evidence."""
    if evidence.get('sign_extension', {}).get('cbw'):
        return 'signed char'
    if evidence.get('zero_extension', {}).get('sub ah,ah'):
        return 'unsigned char'
    widths = evidence.get('access_widths') or {}
    if widths.get('2') and not widths.get('1'):
        return 'int'
    return None


def _cli():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest='command', required=True)
    b = sub.add_parser('build', help='build build/typedb/typedb.json')
    b.add_argument('-o', '--output', default=str(DB_PATH))
    c = sub.add_parser('check', help='check a C source against verified declarations and machine evidence')
    c.add_argument('draft')
    c.add_argument('--database', default=str(DB_PATH))
    r = sub.add_parser('resync', help='rewrite conflicting file-scope declarations to verified forms')
    r.add_argument('draft')
    r.add_argument('-o', '--output', required=True)
    r.add_argument('--database', default=str(DB_PATH))
    args = ap.parse_args()
    if args.command == 'build':
        data = build_database(Path(args.output))
        print(json.dumps({'output': args.output, 'names': len(data['names']), 'conflicts': len(data['conflicts']),
                          'sources_scanned': data['sources_scanned'], 'parse_errors': len(data['parse_errors'])}, indent=2))
    elif args.command == 'check':
        print(json.dumps(check_source(args.draft, read_json(args.database)), indent=2))
    else:
        print(json.dumps(resync_source(args.draft, args.output, read_json(args.database)), indent=2))


if __name__ == '__main__':
    _cli()
