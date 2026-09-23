"""Translation-unit assembly lane: compile several preserved sources as one unit.

An isolated function cannot reproduce a historical object's private selector
pool, private DATA/BSS/CONST or string ordering. This lane composes the
preserved exact-body sources of a build-topology component (or a reviewed
explicit group) into one candidate translation unit, compiles it under the
context's compiler profile and compares every contribution with the strict
member matcher. Admission still goes through the workflow's fresh promotion.

Unit identities are internal evidence ids (topology component ids); no
historical filename is claimed. Function bodies are never rewritten here.
"""
import argparse
import json
import re
from datetime import datetime, timezone
from pathlib import Path
from common import ROOT, FormatError, read_json, write_json, identity, sha256

UNITS = ROOT / 'evidence/recovery/units'
REVIEWED = ROOT / 'evidence/topology/supervisor-unit-sources'
TOPOLOGY = ROOT / 'evidence/topology/build-topology.json'


def timestamp():
    return datetime.now(timezone.utc).isoformat()


def strip_comments(text):
    return re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)


def split_items(text):
    """Split a C file into top-level items: comments, declarations, definitions.

    Only the subset used by the recovered corpus is understood (no preprocessor,
    no assembly). Braces, parentheses and string/char literals are tracked so
    that declarations end at a top-level ';' and definitions at their closing
    brace.
    """
    items = []
    i = 0
    n = len(text)
    while i < n:
        c = text[i]
        if c.isspace():
            i += 1
            continue
        if text.startswith('/*', i):
            j = text.index('*/', i) + 2
            items.append(dict(kind='comment', text=text[i:j]))
            i = j
            continue
        if text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            items.append(dict(kind='comment', text=text[i:j]))
            i = j
            continue
        if c == '#':
            j = text.find('\n', i)
            j = n if j < 0 else j
            line = text[i:j].strip()
            if not line.startswith('#define'):
                raise FormatError('only #define directives are composable: ' + line[:40])
            name = re.match(r'#define\s+([A-Za-z_]\w*)', line)
            items.append(dict(kind='declaration', names=[name.group(1)] if name else [], text=line, normalized=' '.join(line.split())))
            i = j
            continue
        start = i
        depth_brace = depth_paren = 0
        seen_brace = False
        while i < n:
            c = text[i]
            if c in '"\'':
                q = c
                i += 1
                while i < n and text[i] != q:
                    i += 2 if text[i] == '\\' else 1
                i += 1
                continue
            if text.startswith('/*', i):
                i = text.index('*/', i) + 2
                continue
            if c == '(':
                depth_paren += 1
            elif c == ')':
                depth_paren -= 1
            elif c == '{':
                depth_brace += 1
                seen_brace = True
            elif c == '}':
                depth_brace -= 1
                if depth_brace == 0 and seen_brace:
                    i += 1
                    # An initialiser or struct/typedef ends with ';' after '}'.
                    k = i
                    while k < n and text[k].isspace():
                        k += 1
                    if k < n and text[k] == ';':
                        i = k + 1
                    break
            elif c == ';' and depth_brace == 0 and depth_paren == 0:
                i += 1
                break
            i += 1
        item_text = text[start:i].strip()
        code = strip_comments(item_text)
        if not code.strip():
            continue
        head = code.split('{', 1)[0]
        is_definition = seen_brace and '(' in head and not re.match(r'\s*(typedef|struct|union|enum)\b', head) and '=' not in head.split('(')[0]
        if is_definition:
            name = re.findall(r'([A-Za-z_]\w*)\s*\(', head)[-1] if re.findall(r'([A-Za-z_]\w*)\s*\(', head) else None
            items.append(dict(kind='definition', name=name, text=item_text))
        else:
            names = declared_names(code)
            items.append(dict(kind='declaration', names=names, text=item_text, normalized=signature_form(code)))
    return items


def signature_form(code):
    """Declaration text with parameter names removed, so prototypes that differ
    only in parameter naming compare equal."""
    code = ' '.join(code.split())
    def strip(m):
        params = [p.strip() for p in m.group(1).split(',')]
        out = []
        for p in params:
            tokens = p.replace('*', ' * ').split()
            if len(tokens) >= 2 and re.fullmatch(r'[A-Za-z_]\w*', tokens[-1]) and tokens[-1] not in ('void', 'int', 'char', 'long', 'short', 'unsigned', 'signed', 'far', 'near', 'double', 'float'):
                tokens = tokens[:-1]
            out.append(' '.join(tokens).replace(' * ', '*'))
        return '(' + ', '.join(out) + ')'
    return re.sub(r'\(([^()]*)\)(?=\s*;)', strip, code)


def declared_names(code):
    """Identifiers introduced by a declaration (extern, static, typedef, plain)."""
    code = ' '.join(code.split())
    # __based(__segname("X")) is a storage qualifier, never the declared name.
    code = re.sub(r'__based\s*\(\s*__segname\s*\(\s*"[^"]*"\s*\)\s*\)', ' ', code)
    if re.match(r'\s*typedef\b', code):
        m = re.search(r'([A-Za-z_]\w*)\s*(\[[^\]]*\])*\s*;\s*$', code)
        return [m.group(1)] if m else []
    if re.match(r'\s*(struct|union|enum)\s+[A-Za-z_]\w*\s*\{', code):
        m = re.match(r'\s*(struct|union|enum)\s+([A-Za-z_]\w*)', code)
        return [m.group(1) + ' ' + m.group(2)]
    head = code.split('=', 1)[0]
    head = re.sub(r'\([^()]*\)', '()', head)
    head = re.sub(r'\([^()]*\)', '()', head)
    names = re.findall(r'\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*(?:\(\)|,|;|$|\))', head)
    keywords = {'extern', 'static', 'far', 'near', 'int', 'char', 'long', 'short', 'unsigned', 'signed', 'void', 'pascal', 'const', 'struct', 'union', 'enum', 'float', 'double', 'huge', 'cdecl', 'volatile', 'register'}
    return [n for n in names if n not in keywords]


def declaration_shape(normalized, name):
    """(base type, distance keyword, dims) of `extern T [near|far] NAME[d]...;` or None.

    `char` and `signed char` are the same MSC 7 type (no /J in any profile)."""
    m = re.match(r'extern\s+(.*?)\s*\b(near|far)\b\s*((?:(?:const|volatile)\s+)*)' + re.escape(name) + r'\s*((?:\[[^\]]*\]\s*)*);$', normalized)
    if not m:
        return None
    base = ' '.join((m.group(1) + ' ' + (m.group(3) or '')).split())
    if base == 'char':
        base = 'signed char'
    dims = re.findall(r'\[([^\]]*)\]', m.group(4) or '')
    return dict(base=base, distance=m.group(2), dims=dims)


def view_macro(name, own, canonical):
    """A per-definition macro that lets a member written against one shape of a
    far/near object use the canonical declaration of the same object without
    changing its text or its code: element 0 for a scalar view of an array,
    the flattened element pointer for a 1-D view of an N-D array, the address
    for an array view of a scalar. The self-reference expands once."""
    if own['distance'] != canonical['distance']:
        return None
    strip = lambda b: ' '.join(w for w in b.split() if w not in ('volatile', 'const'))
    if strip(own['base']) == strip(canonical['base']) and own['base'] != canonical['base']:
        # volatile/const are object properties for the whole translation unit
        # in MSC 7: no per-member view can give one reader a different one.
        return None
    same = own['base'] == canonical['base']
    if not own['dims']:
        if same and canonical['dims']:
            return '#define %s ((%s)%s)' % (name, name, '[0]' * len(canonical['dims']))
        return '#define %s (*(%s %s *)&%s)' % (name, own['base'], own['distance'], name)
    # An array view: the member indexes through a pointer of its own element
    # type (and inner dimensions), which is the code its own declaration gave.
    inner = ''.join('[%s]' % d for d in own['dims'][1:])
    pointer = ('%s (%s *)%s' % (own['base'], own['distance'], inner)) if inner else ('%s %s *' % (own['base'], own['distance']))
    target = name if canonical['dims'] else '&' + name
    return '#define %s ((%s)%s)' % (name, pointer, target)


DECLARATION_ORDER = ROOT / 'layout/declaration-order.json'


def declaration_order_constraints(component_id):
    """Recorded object-level declaration-order facts for a component: pairs
    (before, after) with evidence. MSC 7 orders the operands of commutative
    expressions (and picks which of two symbols is the memory operand) by the
    declaration order of the symbols, so a byte-exact body can depend on the
    order two externs were declared in the original TU."""
    if not DECLARATION_ORDER.exists():
        return []
    return read_json(DECLARATION_ORDER).get('components', {}).get(component_id, [])


def apply_declaration_order(declarations, constraints):
    """Reorder unit declarations so every recorded (before, after) pair holds:
    the later-required declaration is moved to just after the earlier one."""
    def index_of(name):
        return next((i for i, d in enumerate(declarations) if name in (d.get('names') or []) and not d['text'].lstrip().startswith('#define')), None)
    for c in constraints:
        i, j = index_of(c['before']), index_of(c['after'])
        if i is None or j is None or i < j:
            continue
        item = declarations.pop(j)
        i = index_of(c['before'])
        declarations.insert(i + 1, item)
    return declarations


def struct_key(normalized):
    """Layout identity of a struct/union definition: the member sequence with
    comma declarator lists split (`int x, y;` == `int x; int y;`)."""
    m = re.match(r'(struct|union)\s+(\w+)\s*\{(.*)\}\s*;?\s*$', normalized)
    if not m:
        return normalized
    members = []
    for decl in m.group(3).split(';'):
        decl = decl.strip()
        if not decl:
            continue
        parts = [x.strip() for x in decl.split(',')]
        mm = re.match(r'(.*?)([*\s]*)(\w+)((?:\s*\[[^\]]*\])*)\s*$', parts[0])
        if not mm:
            return normalized
        base = ' '.join(mm.group(1).split())
        members.append('%s %s%s%s' % (base, mm.group(2).strip(), mm.group(3), mm.group(4).replace(' ', '')))
        for x in parts[1:]:
            members.append('%s %s' % (base, x.replace(' ', '')))
    return '%s %s {%s}' % (m.group(1), m.group(2), ';'.join(members))


def compose(sources, order, unit_id, layout='preambles-first', overrides=None, extra_definitions=None, pragmas=None, rank_order=None, header_notes=None, exclude_definitions=(), statics_with_definitions=False, fillers_before=None, statics_address_order=None, declaration_order=None):
    """Merge preserved sources into one unit; conflicts are reported, not resolved.

    `extra_definitions` (scaffold stand-ins) are emitted at their component
    rank between the members; `pragmas` follow the declarations."""
    overrides = overrides or {}
    extra_definitions = extra_definitions or []
    pragmas = pragmas or []
    files = []
    for symbol in order:
        path = ROOT / sources[symbol]
        items = split_items(path.read_text(encoding='latin1'))
        definitions = [it for it in items if it['kind'] == 'definition']
        # Pascal exports are upper-cased in MAPSYM (INDIRECTDLGPROC for IndirectDlgProc).
        if not any(it['name'] == symbol.lstrip('_') or (not symbol.startswith('_') and it['name'].upper() == symbol) for it in definitions):
            raise FormatError('source for %s does not define it: %s' % (symbol, sources[symbol]))
        files.append(dict(symbol=symbol, source=sources[symbol], identity=identity(path), items=items))
    # Two preserved sources may define the same struct tag with different
    # layouts (each exact for its own member). A tag has no object identity:
    # every later spelling is renamed, in that source's items only, to
    # `<tag>_<n>`; the member's text changes in type names alone.
    tag_texts = {}
    for f in files:
        for it in f['items']:
            if it['kind'] == 'declaration' and len(it['names']) == 1 and it['names'][0].startswith(('struct ', 'union ')):
                tag_texts.setdefault(it['names'][0], {}).setdefault(struct_key(it['normalized']), []).append(f['symbol'])
    tag_renames = {}
    for tag, variants in tag_texts.items():
        if len(variants) < 2:
            continue
        keyword, name = tag.split(' ', 1)
        for n, spelling in enumerate(list(variants)[1:], start=2):
            for symbol in variants[spelling]:
                tag_renames.setdefault(symbol, {})[tag] = '%s %s_%d' % (keyword, name, n)
    # The kept spelling of a tag is the first source's text; the same-layout
    # variants of the other sources are dropped (their members' text is unchanged).
    tag_first = {}
    for f in files:
        for it in f['items']:
            if it['kind'] == 'declaration' and len(it['names']) == 1 and it['names'][0].startswith(('struct ', 'union ')):
                key = (it['names'][0], struct_key(it['normalized']))
                if key in tag_first:
                    it['normalized'] = tag_first[key]['normalized']
                    it['text'] = tag_first[key]['text']
                else:
                    tag_first[key] = it
    for f in files:
        renames = tag_renames.get(f['symbol'])
        if not renames:
            continue
        for it in f['items']:
            for tag, new_tag in renames.items():
                pattern = re.compile(chr(92) + 'b' + re.escape(tag.split(' ', 1)[0]) + chr(92) + 's+' + re.escape(tag.split(' ', 1)[1]) + chr(92) + 'b')
                if 'text' in it:
                    it['text'] = pattern.sub(new_tag, it['text'])
                if 'normalized' in it:
                    it['normalized'] = pattern.sub(new_tag, it['normalized'])
                if it.get('names') == [tag]:
                    it['names'] = [new_tag]
    declarations = []
    seen = {}
    conflicts = []
    definitions = []
    emitted_overrides = set()
    # A macro spelled differently by two preserved sources is not a declaration
    # conflict: macros have no object identity, so each definition gets its own
    # `#undef` + `#define` right before it.
    macro_texts = {}
    for f in files:
        for it in f['items']:
            if it['kind'] == 'declaration' and it['text'].lstrip().startswith('#define') and it['names']:
                macro_texts.setdefault(it['names'][0], {}).setdefault(it['normalized'], []).append(f['symbol'])
    declared_objects = {n for f in files for it in f['items'] if it['kind'] == 'declaration' and not it['text'].lstrip().startswith('#define') for n in it['names']}
    # Spelled differently by two sources, or shadowing an object/override of
    # the same name: scoped to the definitions that use it.
    per_definition_macros = {name for name, spellings in macro_texts.items() if len(spellings) > 1 or name in declared_objects or name in overrides}
    for f in files:
        f['macros'] = [it for it in f['items'] if it['kind'] == 'declaration' and it['text'].lstrip().startswith('#define') and it['names'] and it['names'][0] in per_definition_macros]
    # Shape variants of one object (scalar/array, 1-D/N-D of the same base type)
    # are not conflicts either: the widest declaration is canonical and each
    # member written against another shape gets a per-definition view macro.
    spellings = {}
    for f in files:
        for it in f['items']:
            if it['kind'] == 'declaration' and not it['text'].lstrip().startswith('#define') and len(it['names']) == 1 and it['names'][0] not in overrides:
                spellings.setdefault(it['names'][0], {}).setdefault(it['normalized'], set()).add(f['symbol'])
    canonical = {}
    for name, variants in spellings.items():
        if len(variants) < 2:
            continue
        shapes = {s: declaration_shape(s, name) for s in variants}
        if any(v is None for v in shapes.values()):
            continue
        # Widest shape, explicit sizes, unqualified base (a volatile view is
        # applied per member; a volatile canonical would change every reader),
        # then the spelling most members use.
        best = max(shapes, key=lambda s: (len(shapes[s]['dims']), sum(1 for d in shapes[s]['dims'] if d.strip()), -sum(q in shapes[s]['base'].split() for q in ('volatile', 'const')), len(variants[s]), -list(shapes).index(s)))
        if all(s == best or view_macro(name, shapes[s], shapes[best]) for s in shapes):
            canonical[name] = dict(text=best, shape=shapes[best], views={s: view_macro(name, shapes[s], shapes[best]) for s in shapes if s != best})
    for f in files:
        f['views'] = []
        for it in f['items']:
            if it['kind'] == 'declaration' and len(it['names']) == 1 and it['names'][0] in canonical and it['normalized'] != canonical[it['names'][0]]['text']:
                f['views'].append(dict(name=it['names'][0], text=canonical[it['names'][0]]['views'][it['normalized']]))
    for f in files:
        for it in f['items']:
            if it['kind'] == 'declaration':
                if it['text'].lstrip().startswith('#define') and it['names'] and it['names'][0] in per_definition_macros:
                    continue
                if len(it['names']) == 1 and it['names'][0] in canonical and it['normalized'] != canonical[it['names'][0]]['text']:
                    continue
                key_names = it['names'] or [it['normalized']]
                # A function-like macro never clashes with an object of the same
                # name: it only expands before a parenthesis.
                if it['text'].lstrip().startswith('#define') and it['names'] and re.match(r'#define\s+' + re.escape(it['names'][0]) + r'\(', it['text'].lstrip()):
                    key_names = [it['names'][0] + '(']
                # A reviewed override replaces every declaration of that name
                # with one recorded spelling, emitted at its first occurrence.
                if any(name in overrides for name in key_names):
                    for name in key_names:
                        if name in overrides and name not in emitted_overrides:
                            emitted_overrides.add(name)
                            declarations.append(dict(kind='declaration', names=[name], text=overrides[name].strip(), normalized=' '.join(overrides[name].split()), origin='override'))
                    continue
                for name in key_names:
                    previous = seen.get(name)
                    if previous is None:
                        seen[name] = (it['normalized'], f['symbol'])
                    elif previous[0] != it['normalized']:
                        conflicts.append(dict(name=name, first=previous[0], first_from=previous[1], other=it['normalized'], other_from=f['symbol']))
                if any(seen[name][1] == f['symbol'] and seen[name][0] == it['normalized'] for name in key_names if name in seen):
                    if it['normalized'] not in [d['normalized'] for d in declarations]:
                        declarations.append(dict(it, origin=f['symbol']))
            elif it['kind'] == 'definition':
                # A preserved unit source may already define several members;
                # each definition is emitted once, in MAPSYM order below.
                # Unclaimed component members carried by a unit source are
                # dropped when the caller scaffolds them instead.
                if any(d['name'] == it['name'] for d in definitions) or it['name'] in exclude_definitions:
                    continue
                if it['name'] == f['symbol'].lstrip('_') or ('_' + it['name']) in sources or it['name'].upper() in sources:
                    definitions.append(dict(it, origin=f['symbol']))
                else:
                    # A helper (e.g. static function) defined by a preserved source.
                    definitions.append(dict(it, origin=f['symbol'], helper=True))
    if exclude_definitions:
        # Private statics that only the dropped definitions used would create
        # an unplaced data contribution; keep a static only if a kept
        # definition names it.
        kept = chr(10).join(d['text'] for d in definitions)
        declarations = [d for d in declarations if not (d['text'].lstrip().startswith('static') and d['names'] and not any(re.search(chr(92) + 'b' + re.escape(n) + chr(92) + 'b', kept) for n in d['names']))]
    # Unresolved conflicts stop composition: a reviewed override must choose.
    if conflicts:
        return dict(status='DECLARATION_CONFLICT', conflicts=conflicts, files=[{k: v for k, v in f.items() if k not in ('items', 'macros', 'views')} for f in files])
    if declaration_order:
        declarations = apply_declaration_order(declarations, declaration_order)
    header = ['/* Candidate translation unit %s: composed from preserved exact-body sources' % unit_id,
              ' * in MAPSYM order. Internal evidence id, not a historical filename.',
              ' * Members: %s' % ', '.join(order)] + [' * ' + n for n in (header_notes or [])]
    header[-1] += ' */'
    header.append('')
    lines = list(header)
    fillers_before = fillers_before or {}
    # Private data is emitted where the compiler meets it: a member's static
    # data definitions stay with its definition (in code order) when the unit
    # must reproduce an interleaved private-data layout.
    def is_static_data(d):
        text = d['text'].lstrip()
        head = text.split('=', 1)[0]
        return text.startswith('static') and '(' not in head and d.get('origin') not in (None, 'override', 'scaffold')
    held = {}
    if statics_with_definitions:
        for d in declarations:
            if is_static_data(d):
                held.setdefault(d['origin'], []).append(d)
        declarations = [d for d in declarations if not is_static_data(d)]
    elif statics_address_order is not None:
        # Statics declared at the top of the original source, in the order the
        # original data block shows; fillers for unclaimed members' data sit
        # between them. Members without private data keep their statics last.
        statics = [d for d in declarations if is_static_data(d)]
        declarations = [d for d in declarations if not is_static_data(d)]
        rank = {m: i for i, m in enumerate(statics_address_order)}
        ordered = []
        for m in sorted({d['origin'] for d in statics}, key=lambda m: (rank.get(m, len(rank)), m)):
            for text in fillers_before.get(m, []):
                ordered.append(dict(kind='declaration', names=[], text=text, normalized=text, origin='scaffold'))
            ordered += [d for d in statics if d['origin'] == m]
        ordered += [dict(kind='declaration', names=[], text=text, normalized=text, origin='scaffold') for text in fillers_before.get('__tail__', [])]
        declarations += ordered
        fillers_before = {}
    if layout == 'preambles-first':
        for d in declarations:
            lines.append(d['text'])
        lines.append('')
        for text in pragmas:
            lines.append(text)
        if pragmas:
            lines.append('')
        rank = {m.lstrip('_'): i for i, m in enumerate(rank_order or order)}
        for i, m in enumerate(rank_order or order):
            if not m.startswith('_'):
                rank.setdefault(m.upper(), i)
        placed = [dict(d, rank=rank.get(d['name'], rank.get(d['name'].upper(), len(rank)))) for d in definitions] + [dict(kind='definition', name=x['name'], text=x['text'], origin='scaffold', rank=x['rank'] if x.get('rank') is not None else rank.get(x['rank_name'].lstrip('_'), len(rank))) for x in extra_definitions]
        macros_of = {f['symbol']: f['macros'] for f in files}
        views_of = {f['symbol']: f['views'] for f in files}
        for d in sorted(placed, key=lambda d: d['rank']):
            for text in fillers_before.get(d.get('origin'), []):
                lines.append(text)
            for s in held.get(d.get('origin'), []):
                lines.append(s['text'])
            for it in macros_of.get(d.get('origin'), []):
                lines.append('#undef ' + it['names'][0])
                lines.append(it['text'])
            for v in views_of.get(d.get('origin'), []):
                lines.append(v['text'] + '  /* shape view of the unit declaration for this member only */')
            lines.append(d['text'])
            for v in views_of.get(d.get('origin'), []):
                lines.append('#undef ' + v['name'])
            for it in macros_of.get(d.get('origin'), []):
                lines.append('#undef ' + it['names'][0])
                if it['names'][0] in overrides and overrides[it['names'][0]].lstrip().startswith('#define'):
                    lines.append(overrides[it['names'][0]].strip())
            lines.append('')
    else:
        # Each file's declarations immediately precede its definition.
        emitted = set()
        for f in files:
            for it in f['items']:
                if it['kind'] == 'declaration' and it['normalized'] not in emitted and any(d['normalized'] == it['normalized'] for d in declarations):
                    lines.append(it['text'])
                    emitted.add(it['normalized'])
            for d in definitions:
                if d['origin'] == f['symbol']:
                    lines.append(d['text'])
                    lines.append('')
    return dict(status='COMPOSED', text='\n'.join(lines) + '\n', files=[{k: v for k, v in f.items() if k not in ('items', 'macros', 'views')} for f in files],
                declarations=len(declarations), definitions=[d['name'] for d in definitions], layout=layout, overrides=sorted(overrides), per_definition_macros=sorted(per_definition_macros),
                shape_views={name: sorted(set(c['views'].values())) for name, c in canonical.items()}, tag_renames=tag_renames,
                declaration_items=[dict(names=d['names'], text=d['text']) for d in declarations], definition_items=[dict(name=d['name'], text=d['text']) for d in definitions])


def record_reviewed_source(symbol, path, note=''):
    """Verify a reviewed isolated source strictly under the symbol's object
    profile and record the outcome in the reviewed-source ledger. Only an exact
    body (see body_exact) is offered to units; nothing is admitted here."""
    import compiler_profiles as cp
    from codegen_grinder import run
    path = Path(path) if not isinstance(path, Path) else path
    rel = path.relative_to(ROOT).as_posix() if path.is_absolute() else path.as_posix()
    comp = cp.component_of(symbol) or {}
    flags = cp.profile_flags(cp.resolve(symbol)['name'], comp.get('segment'))
    report = run(dict(symbol=symbol, source=rel, compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[symbol]), 'build/experiments/reviewed/' + symbol.lstrip('_'), cache=True)
    c = report['results'][0]['comparison']
    row = dict(source=rel, identity=identity(ROOT / rel), flags=flags, result=c['result'], exact_body=body_exact(c), issues=[i for i in c.get('issues', []) if 'CONST' not in i][:4], note=note, checked=timestamp())
    ledger = REVIEWED / 'reviewed.json'
    rows = read_json(ledger) if ledger.exists() else {}
    rows[symbol] = row
    REVIEWED.mkdir(parents=True, exist_ok=True)
    write_json(ledger, dict(sorted(rows.items())))
    return row


def preserved_sources():
    """Best preserved source per symbol: admitted recipe, else body-solved / best job candidate."""
    result = {}
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    for symbol, target in recipes.items():
        if target.get('scaffold'):
            # A scaffolded unit source carries stand-ins and per-member macros;
            # the member's own text is its superseded isolated recipe or its
            # exact body candidate (searched below).
            # Units supersede units: walk the chain of superseded recipes back
            # to the member's last isolated (non-scaffold) source.
            old = target
            seen = set()
            while old and old.get('scaffold') and old.get('promotion_evidence') and old['promotion_evidence'] not in seen and (ROOT / old['promotion_evidence']).exists():
                seen.add(old['promotion_evidence'])
                proof = read_json(ROOT / old['promotion_evidence'])
                old = (proof.get('superseded_recipes') or {}).get(symbol)
            if old and not old.get('scaffold') and (ROOT / old['source']).exists():
                result[symbol] = dict(source=old['source'], basis='ADMITTED', profile=target.get('profile', 'baseline'), unit=target.get('unit'))
            continue
        result[symbol] = dict(source=target['source'], basis='ADMITTED', profile=target.get('profile', 'baseline'))
    families = ROOT / 'evidence/recovery/blocker-families.json'
    if families.exists():
        for symbol, f in read_json(families)['functions'].items():
            if symbol in result:
                continue
            if f.get('preserved_source'):
                result[symbol] = dict(source=f['preserved_source'], basis='ADMITTED' if symbol in recipes else 'BODY_MATCHED_BINDING_BLOCKED')
    # Reviewed sources: isolated candidates rewritten by the supervisor tools
    # (rebind_pack_index, rebind_based_fields, review_source) and verified as
    # exact bodies under the object profile; the ledger records the check.
    ledger = REVIEWED / 'reviewed.json'
    if ledger.exists():
        for symbol, row in read_json(ledger).items():
            if symbol in result or not row.get('exact_body') or not (ROOT / row['source']).exists():
                continue
            if identity(ROOT / row['source']) != row.get('identity'):
                continue
            result[symbol] = dict(source=row['source'], basis='REVIEWED_EXACT_BODY', note=row.get('note'))
    for path in (ROOT / 'evidence/recovery/workflow/jobs').glob('*/job.json'):
        job = read_json(path)
        if job['symbol'] in result or job.get('lane') == 'TU_ASSEMBLY' or not job.get('attempts'):
            continue
        admitted_in_unit = job['symbol'] in recipes
        best = None
        # Fresh recompilations under the current object profile
        # (blocked_reclassification) count like attempts: same strict matcher.
        fresh = ROOT / 'build/reclassify' / job['symbol'].lstrip('_') / 'results.json'
        reports = [ROOT / a['report'] for a in job['attempts']] + ([fresh] if fresh.exists() else [])
        for report_path in reports:
            if not report_path.exists():
                continue
            report = read_json(report_path)
            for row in report['results']:
                d = (row.get('comparison') or {}).get('diagnostic') or {}
                if d.get('opcode_matches') is None:
                    continue
                # An exact body is one the binding classifier accepts: every
                # differing literal is an unresolved offset binding. A resolved
                # fixup with a wrong literal (e.g. Dx8/Dy8 swapped) is a
                # semantic difference even when the instruction layout aligns.
                exact_body = body_exact(row['comparison'])
                strict = row['comparison'].get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')
                # A strict isolated success outranks an exact body whose data
                # or bindings still differ (e.g. an earlier attempt with the
                # same code but a wrong string literal).
                key = (strict, exact_body, d['opcode_matches'], -abs(d.get('candidate_bytes', 0) - d.get('target_bytes', 0)))
                source = ROOT / row['receipt']['source']
                if source.exists() and (best is None or key > best[0]):
                    best = (key, source.relative_to(ROOT).as_posix(), exact_body)
        if best:
            result[job['symbol']] = dict(source=best[1], basis=('ADMITTED' if admitted_in_unit and best[2] else 'EXACT_BODY_CANDIDATE' if best[2] else 'BEST_CANDIDATE_NOT_EXACT'))
    # Ledger drafts without a workflow job: only their fresh recompilation counts.
    for fresh in (ROOT / 'build/reclassify').glob('*/results.json') if (ROOT / 'build/reclassify').exists() else []:
        report = read_json(fresh)
        symbol = report.get('spec', {}).get('symbol')
        if not symbol or symbol in result:
            continue
        row = report['results'][0]
        source = ROOT / row['receipt']['source']
        if source.exists() and (row.get('comparison') or {}).get('diagnostic'):
            result[symbol] = dict(source=source.relative_to(ROOT).as_posix(), basis='EXACT_BODY_CANDIDATE' if body_exact(row['comparison']) else 'BEST_CANDIDATE_NOT_EXACT')
    # A member first admitted inside a unit has no isolated recipe; its
    # isolated text (reviewed source or exact candidate) still stands for it,
    # and the member is admitted.
    for symbol, target in recipes.items():
        if symbol in result and result[symbol]['basis'] != 'ADMITTED' and target.get('scaffold'):
            result[symbol] = dict(result[symbol], basis='ADMITTED', profile=target.get('profile', 'baseline'), unit=target.get('unit'), isolated_basis=result[symbol]['basis'])
    return result


def topology_units():
    if not TOPOLOGY.exists():
        raise FormatError('run tools/build_topology.py first')
    report = read_json(TOPOLOGY)
    result = {}
    for unit in report['units']:
        for component in unit['components']:
            result[component['id']] = dict(component, segment=unit['segment'], range=unit['candidate_unit'])
    return result


def pool_words_in_code_order(symbol, functions):
    """Selector-pool words a function loads, in code (first-use) order."""
    return [int(w, 16) if isinstance(w, str) else w for w in functions[symbol]['slots']]


def predicted_pool(order, functions):
    """First-use order of pool words when the given functions are compiled together in this order."""
    seen = []
    for symbol in order:
        for w in pool_words_in_code_order(symbol, functions):
            if w not in seen:
                seen.append(w)
    return seen


def assemblable(group, functions):
    """A subset reproduces its pool only if its words are one contiguous original
    block in the same order as the composed first-use order (predicted from code)."""
    words = predicted_pool(group, functions)
    if not words:
        return True, 'no pool words'
    expected = sorted(words)
    if any(b - a != 2 for a, b in zip(expected, expected[1:])):
        return False, 'pool words are not contiguous in the original: %s' % ' '.join('%04X' % w for w in expected)
    if words != expected:
        return False, 'composed first-use order %s differs from the original pool order' % ' '.join('%04X' % w for w in words)
    return True, 'contiguous pool block %04X-%04X' % (expected[0], expected[-1])


def propose(min_functions=1):
    """Candidate unit groups per component: usable preserved sources whose selector
    pool is predicted to reproduce, plus the missing introducers that block the rest."""
    sources = preserved_sources()
    functions = read_json(TOPOLOGY)['functions']
    rows = []
    for cid, comp in topology_units().items():
        members = comp['publics']
        if len(members) < min_functions:
            continue
        have = {m: sources.get(m) for m in members}
        usable = [m for m in members if have[m] and have[m]['basis'] in ('ADMITTED', 'BODY_MATCHED_BINDING_BLOCKED', 'EXACT_BODY_CANDIDATE', 'REVIEWED_EXACT_BODY')]
        missing = [m for m in members if m not in usable]
        # Greedy scan in code order: extend the group while the predicted pool
        # still reproduces; a member that breaks it is skipped and its blocking
        # words attributed to their original introducers.
        # A composed unit's code is contiguous, so a group must be a run of
        # consecutive members (a missing member ends the run) whose predicted
        # pool block is contiguous and in order.
        groups = []
        current = []
        blocked = {}
        for m in members:
            if m not in usable:
                if current:
                    groups.append(current)
                current = []
                continue
            ok, why = assemblable(current + [m], functions)
            if ok:
                current.append(m)
            else:
                if current:
                    groups.append(current)
                current = [m] if assemblable([m], functions)[0] else []
                introducers = sorted({functions[x]['symbol'] for x in members for w in pool_words_in_code_order(m, functions) if w in pool_words_in_code_order(x, functions) and x in missing})
                blocked[m] = dict(reason=why, missing_introducers=introducers)
        if current:
            groups.append(current)
        groups = [g for g in groups if any(have[m]['basis'] != 'ADMITTED' for m in g)]
        unlock = sum(1 for g in groups for m in g if have[m]['basis'] != 'ADMITTED')
        rows.append(dict(component=cid, segment=comp['segment'], range=comp['range'], members=members, usable=usable, missing=missing,
                         groups=groups, blocked=blocked, unlock=unlock, join_evidence=comp.get('join_evidence'), complete=not missing))
    rows.sort(key=lambda r: (-r['unlock'], r['component']))
    return rows


SCAFFOLD_SEGMENT = 'POOLSTUB_TEXT'


def body_exact(comparison):
    """Strict GOOD result, a body the binding classifier accepts, or an opcode-
    and byte-exact body with zero register/branch/frame differences whose
    only failures are unresolved (not wrongly resolved) bindings and private
    placement: everything a scaffolded unit can still prove."""
    from topology_diagnostics import classify
    if comparison.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER') or classify(comparison) is not None:
        return True
    d = comparison.get('diagnostic') or {}
    if not d or d.get('opcode_total') is None:
        return False
    if not (d.get('opcode_matches') == d.get('opcode_total') and d.get('candidate_bytes') == d.get('target_bytes') and d.get('instruction_layout_match') is True):
        return False
    if any(d.get(k, 1) != 0 for k in ('register_only_differences', 'branch_target_differences', 'stack_local_differences')):
        return False
    # A plain immediate that differs at a site without a fixup is a semantic
    # difference (swapped switch-case bodies, a wrong constant), not a binding.
    for r in d.get('aligned_asm', []):
        if 'immediate_or_binding' in r.get('differences', []) and 'fixup' not in r.get('candidate', '') and 'fixup' not in r.get('target', ''):
            return False
    if any('instruction_shape' in r['differences'] for r in d.get('aligned_asm', [])):
        return False
    failed = [f for c in comparison.get('contributions', []) for f in c.get('fixups', []) if not f['equal']]
    if any(f.get('target') is not None and f.get('reason') in ('resolved offset and frame', 'same-segment relative offset') for f in failed):
        return False
    # An external the linker model cannot locate is an invented name, not an
    # unresolved binding: no unit can ever resolve it.
    for f in failed:
        omf_target = (f.get('omf') or {}).get('target') or {}
        if f.get('target') is None and omf_target.get('kind') == 'external' and not known_symbol(omf_target.get('name', '')):
            return False
    return True


_KNOWN_SYMBOLS = None


def known_symbol(name):
    """MAPSYM public (any segment, absolute) or import-library name."""
    global _KNOWN_SYMBOLS
    if _KNOWN_SYMBOLS is None:
        import mapsym
        from common import fixture
        from library_match import import_symbols
        s = mapsym.parse(fixture('SIMANTW.SYM'))
        names = {x['name'] for seg in s['segments'] for x in seg['symbols']} | {x['name'] for x in s['absolute_symbols']}
        names |= set(import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB'))
        names |= {'FIDRQQ', 'FIERQQ', 'FIWRQQ', 'FICRQQ', 'FJCRQQ'}
        _KNOWN_SYMBOLS = names
    return name in _KNOWN_SYMBOLS


def slot_segments():
    """Original selector-pool word -> addressed original segment, from the NE
    loader relocations of DGROUP (source type 2, offset 0)."""
    import ne
    from common import fixture
    image = ne.parse(fixture('SIMANTW.EXE'))
    return {site: r['target']['segment'] for r in image['segments'][9]['relocations']
            if r['source_type'] == 2 and r['target'].get('kind') == 'internal' and r['target'].get('offset') == 0 for site in r['sites']}


def far_sites(card_list=None):
    """Original selector-pool word -> exact MAPSYM names observed at its ES sites."""
    import ne, mapsym
    from common import fixture
    from recovery_workflow import cards
    from topology_context import far_data_bindings
    image = ne.parse(fixture('SIMANTW.EXE'))
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    result = {}
    for card in card_list or cards():
        if card['ownership'] != 'GAME':
            continue
        for b in far_data_bindings(card, symbols, image):
            slot = b.get('selector_slot')
            if slot is None:
                continue
            entry = result.setdefault(slot, dict(segment=b.get('addressed_segment'), names=set(), functions=set()))
            entry['names'].update(b.get('exact_mapsym_names') or [])
            entry['functions'].add(card['symbol'])
    return result


def member_slot_symbols(member, source, flags, target_bytes, folder=None):
    """Original pool word -> far symbol the preserved source uses for it.

    The preserved body is byte-exact except for its `mov es,[slot]`
    displacements, so each CONST-targeted code fixup of the isolated object
    aligns with the original slot literal at the same body offset; the CONST
    word it addresses names the symbol through its selector fixup."""
    import omf
    from codegen_grinder import run
    out = (folder or (UNITS / '_slots')) / ('slots_' + member.lstrip('_'))
    report = run(dict(symbol=member, source=source, compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[member]), out.relative_to(ROOT).as_posix(), cache=True)
    row = report['results'][0]
    # The alignment argument only holds for an exact body: refuse to derive a
    # slot map from a candidate whose literals differ from the original.
    if not body_exact(row['comparison']):
        raise FormatError('%s is not an exact body under the unit profile; no slot map can be derived from %s' % (member, source))
    m = omf.parse((ROOT / row['receipt']['object']).read_bytes())
    pub = next((p for p in m['publics'] if p['name'] == member), None)
    const = next((s for s in m['segments'] if s['name'] == 'CONST'), None)
    if pub is None or const is None:
        return {}
    code_seg = m['segments'][pub['segment'] - 1]
    code = bytes.fromhex(code_seg['data_hex'])
    # A pool word is a selector of an external symbol (T2) or, for
    # `__based(__segname("X"))` objects, of the named segment itself (T0).
    words = {}
    for f in m['fixups']:
        if f['segment'] != const['index'] or f['location_type'] != 2:
            continue
        if f['target_method'] == 2:
            words[f['offset']] = f['target']['name']
        elif f['target_method'] == 0 and f['target'].get('kind') == 'segment':
            words[f['offset']] = '__segname:' + f['target']['name']
    mapping = {}
    for f in m['fixups']:
        if f['segment'] != code_seg['index'] or f['target_method'] != 0 or f['target_index'] != const['index'] or f['location_type'] != 1:
            continue
        p = f['offset'] - pub['offset']
        k = f['displacement'] + int.from_bytes(code[f['offset']:f['offset'] + 2], 'little')
        if 0 <= p < len(target_bytes) - 1 and k in words:
            mapping.setdefault(int.from_bytes(target_bytes[p:p + 2], 'little'), set()).add(words[k])
    return mapping


def reference_expression(name, declaration):
    """An expression that reads the named far object by value (a pool load, not an address)."""
    if declaration is None:
        return name
    text = ' '.join(declaration.split())
    dims = text.count('[')
    aggregate = bool(re.search(r'\bstruct\b|\bunion\b', text)) and '*' not in text.split(name)[0][-4:]
    if dims:
        # An aggregate element cannot be assigned to int: read its first word
        # through the decayed array pointer (a value read, so a pool load).
        return ('*(int far *)' + name + '[0]' * (dims - 1)) if aggregate else name + '[0]' * dims
    if aggregate:
        return '*(int far *)&' + name
    return '(int)' + name


def unify_pool_symbols(shared, declared_texts, symbols):
    """Two claimed members naming the same original pool word through different
    symbols would allocate two words in one unit. The word proves one object;
    the spelling with the lowest MAPSYM offset (the enclosing object) is kept
    and every other name becomes a macro over it with its byte displacement,
    which compiles to the same displacement literal and the same pool word."""
    located = {}
    for seg in symbols['segments']:
        for x in seg['symbols']:
            located.setdefault(x['name'], (seg['number'], x['offset']))
    overrides = {}
    for word, names in shared.items():
        names = {n for n in names if not n.startswith('__segname:')}
        if len(names) < 2:
            continue
        # Two names on one word are one object only if neither name also
        # owns another word of this block; otherwise one member binds the
        # wrong symbol (simtwo:3EF8: Dx8 and Dy8 each have their own word).
        elsewhere = {n for w2, ns in shared.items() if w2 != word for n in ns}
        if names & elsewhere:
            raise FormatError('pool word %04X is named %s by claimed members while %s also own other words: a member binds the wrong symbol (review the sources, do not merge)' % (word, sorted(names), sorted(names & elsewhere)))
        rows = []
        for n in sorted(names):
            if n not in located:
                raise FormatError('pool word %04X is named through %s, which MAPSYM does not locate' % (word, n))
            rows.append((located[n][1], located[n][0], n))
        if len({r[1] for r in rows}) != 1:
            raise FormatError('pool word %04X is named through symbols of different segments' % word)
        rows.sort()
        base_off, _, base = rows[0]
        for off, _, other in rows[1:]:
            c_name = other.lstrip('_')
            decl = declared_texts.get(c_name)
            if decl is None:
                raise FormatError('no declaration text for ' + c_name)
            text = ' '.join(decl.split())
            m = re.match(r'extern\s+(.*?)\s+far\s+' + re.escape(c_name) + r'\s*((?:\[[^\]]*\]\s*)*);$', text)
            if not m:
                raise FormatError('cannot express %s over %s from declaration: %s' % (c_name, base.lstrip('_'), text))
            elem = m.group(1).strip()
            dims = re.findall(r'\[([^\]]*)\]', m.group(2) or '')
            # A pointer to the element type (or, for a multi-dimensional array,
            # to its inner array type) so the original index expressions keep
            # their meaning.
            pointer = '%s (far *)%s' % (elem, ''.join('[%s]' % d for d in dims[1:])) if len(dims) > 1 else '%s far *' % elem
            base_decl = ' '.join((declared_texts.get(base.lstrip('_')) or '').split())
            base_ref = ('%s' if '[' in base_decl else '&%s') % base.lstrip('_')
            overrides[c_name] = '#define %s ((%s)((unsigned char far *)%s + 0x%X))  /* pool word %04X: one object, MAPSYM %s+%d */' % (c_name, pointer, base_ref, off - base_off, word, base, off - base_off)
    return overrides


def member_data_pieces(member, source, flags, folder=None):
    """Private DATA/BSS contributions of a claimed member with their original
    placement: from its promotion proof when admitted, else from its exact
    isolated object."""
    from codegen_grinder import run
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    proof = {}
    recipe = recipes.get(member)
    if recipe and recipe.get('promotion_evidence') and (ROOT / recipe['promotion_evidence']).exists():
        proof = read_json(ROOT / recipe['promotion_evidence'])
        if not isinstance(proof, dict):
            proof = {}  # an older proof format (a list of rows) carries no comparison
        if recipe.get('scaffold'):
            # A unit proof describes the whole unit's data; the member's own
            # piece is in its superseded isolated proof, else its isolated object.
            old = (proof.get('superseded_recipes') or {}).get(member) or {}
            proof = read_json(ROOT / old['promotion_evidence']) if old.get('promotion_evidence') and (ROOT / old['promotion_evidence']).exists() and not old.get('scaffold') else {}
            if not isinstance(proof, dict):
                proof = {}
    if proof.get('comparison'):
        comparison = proof['comparison']
    else:
        out = (folder or (UNITS / '_slots')) / ('slots_' + member.lstrip('_'))
        report = run(dict(symbol=member, source=source, compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[member]), out.relative_to(ROOT).as_posix(), cache=True)
        comparison = report['results'][0]['comparison']
    return [dict(segment=c['segment'], offset=c['original_offset'], length=c['length'], member=member)
            for c in comparison.get('contributions', []) if c['segment'] in ('_DATA', '_BSS') and c.get('length')]


def member_data_anchors(member, source, flags, target_bytes, folder=None):
    """Fine-grained private DATA/BSS pieces of a claimed member from its exact
    isolated object: every code fixup into _DATA/_BSS gives (candidate offset
    k, original address A) through the original literal at the same site;
    runs of constant A-k are one contiguous piece. A piece whose bytes are a
    NUL-terminated printable string is a body literal (emitted while the
    function is compiled); everything else is a static (emitted where it is
    declared). This is how an object whose data was split between top-level
    statics and body literals is reproduced."""
    import omf
    from codegen_grinder import run
    out = (folder or (UNITS / '_slots')) / ('slots_' + member.lstrip('_'))
    report = run(dict(symbol=member, source=source, compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[member]), out.relative_to(ROOT).as_posix(), cache=True)
    row = report['results'][0]
    if not body_exact(row['comparison']):
        raise FormatError('%s is not an exact body under the unit profile; no data anchors can be derived from %s' % (member, source))
    m = omf.parse((ROOT / row['receipt']['object']).read_bytes())
    pub = next((p for p in m['publics'] if p['name'] == member), None)
    if pub is None:
        return []
    code_seg = m['segments'][pub['segment'] - 1]
    code = bytes.fromhex(code_seg['data_hex'])
    pieces = []
    for cls in ('_DATA', '_BSS'):
        seg = next((s for s in m['segments'] if s['name'] == cls and s['length']), None)
        if seg is None:
            continue
        anchors = {}
        for f in m['fixups']:
            if f['segment'] != code_seg['index'] or f['target_method'] != 0 or f['target_index'] != seg['index'] or f['location_type'] != 1 or f['self_relative']:
                continue
            p = f['offset'] - pub['offset']
            if not 0 <= p < len(target_bytes) - 1:
                continue
            k = (f['displacement'] + int.from_bytes(code[f['offset']:f['offset'] + 2], 'little')) & 0xFFFF
            a = int.from_bytes(target_bytes[p:p + 2], 'little')
            anchors.setdefault(k, set()).add((a - k) & 0xFFFF)
        if not anchors or any(len(v) > 1 for v in anchors.values()):
            continue
        ks = sorted(anchors)
        runs = []
        for k in ks:
            delta = next(iter(anchors[k]))
            if runs and runs[-1]['delta'] == delta:
                continue
            runs.append(dict(start=k, delta=delta))
        runs[0]['start'] = 0
        data = bytes.fromhex(seg['data_hex']) if cls == '_DATA' else b''
        for i, r in enumerate(runs):
            end = runs[i + 1]['start'] if i + 1 < len(runs) else seg['length']
            chunk = data[r['start']:end] if cls == '_DATA' else b''
            literal = private_data_is_literal(chunk) if cls == '_DATA' else False
            pieces.append(dict(segment=cls, offset=(r['start'] + r['delta']) & 0xFFFF, length=end - r['start'], member=member, kind='literal' if literal else 'static', candidate_start=r['start']))
    return pieces


def private_data_is_literal(chunk):
    """Infer a printable string only when bytes distinguish it from zero statics.

    All-zero bytes can encode an empty string, but also an initialized word or
    byte array. A speculative literal would move a real static past other data.
    """
    return (len(chunk) > 1 and chunk[-1:] == b'\x00' and any(chunk[:-1])
            and all(32 <= b < 127 or b in (0, 9, 10, 13) for b in chunk))


def reviewed_scaffold(text, members, component_publics):
    """Record explicit stand-ins in a reviewed unit; never credit their code."""
    slots = re.findall(r'#\s*pragma\s+alloc_text\s*\(\s*POOLSTUB_TEXT\s*,\s*([^()]*)\)', text)
    names = [name.strip() for slot in slots for name in slot.split(',')]
    if not names or any(not re.fullmatch(r'[A-Za-z_]\w*', name) for name in names):
        raise FormatError('reviewed scaffold requires named POOLSTUB_TEXT functions')
    if len(names) != len(set(names)):
        raise FormatError('duplicate reviewed scaffold stand-in')
    all_publics = {p.lstrip('_').upper() for p in component_publics}
    if any(name.upper() in all_publics for name in names):
        raise FormatError('a real component public cannot be a scaffold stand-in')
    for name in names:
        if not re.search(r'\b' + re.escape(name) + r'\s*\([^;]*\)\s*\{', text):
            raise FormatError('reviewed scaffold stand-in lacks a definition: ' + name)
    return dict(segment=SCAFFOLD_SEGMENT, stubs=[dict(function=name) for name in names],
                runs=[members], scope='Reviewed stand-ins occupy reserved code only; their private contributions remain strictly compared')


def data_fillers(pieces, comp, functions, mode='definitions'):
    """Fillers that reproduce the private DATA/BSS layout between the claimed
    members' pieces: each gap between consecutive pieces of one class is the
    unclaimed members' data, emitted right before the following member as a
    static array carrying the original bytes (DATA; no loader obligation may
    lie inside) or only its size (BSS). Pieces must follow code order and lie
    inside the component's data block."""
    import ne
    from common import fixture
    raw = fixture('SIMANTW.EXE')
    image = ne.parse(raw)
    dg = image['segments'][9]
    data = raw[dg['file_offset']:dg['file_offset'] + dg['logical_size']]
    relocated = {site for r in dg['relocations'] for site in r['sites']}
    words = sorted(comp.get('data_words', []))
    fillers = {}
    literals = []
    excluded = []
    kept = []
    seen_pieces = set()
    for piece in pieces:
        key = (piece['segment'], piece['offset'], piece['length'])
        if key in seen_pieces:
            # The same private object reached from several members (one
            # shared static in the unit): owned by the first member in code order.
            continue
        seen_pieces.add(key)
        if piece['segment'] == '_DATA' and words and not (words[0] <= piece['offset'] <= words[-1] + 4096):
            excluded.append(dict(piece, reason='private DATA placed outside the component data block'))
        else:
            kept.append(piece)
    kept.sort(key=lambda p: (functions[p['member']]['offset'], p['offset']))
    if mode == 'split':
        return split_layout(kept, data, relocated, functions, excluded)
    for cls in ('_DATA', '_BSS'):
        rows = sorted([p for p in kept if p['segment'] == cls], key=lambda p: p['offset'])
        for a, b in zip(rows, rows[1:]):
            if mode == 'definitions' and functions[a['member']]['offset'] > functions[b['member']]['offset']:
                raise FormatError('%s pieces of %s and %s are not in code order' % (cls, a['member'], b['member']))
            gap_lo, gap_hi = a['offset'] + a['length'], b['offset']
            if gap_hi < gap_lo:
                raise FormatError('%s pieces of %s and %s overlap' % (cls, a['member'], b['member']))
            if gap_hi == gap_lo:
                continue
            name = 'pool_%s_fill_%04X' % ('data' if cls == '_DATA' else 'bss', gap_lo)
            if cls == '_DATA':
                if any(gap_lo <= s < gap_hi for s in relocated):
                    raise FormatError('DGROUP %04X-%04X carries loader obligations; no data filler' % (gap_lo, gap_hi))
                chunk = data[gap_lo:gap_hi]
                note = 'the %d bytes of private data between %s and %s (DGROUP %04X-%04X, unclaimed members), copied from the image so the claimed pieces keep their layout' % (len(chunk), a['member'], b['member'], gap_lo, gap_hi)
                if mode == 'definitions' and (gap_lo % 2 or chunk[-1:] == b'\x00'):
                    # Statics are word aligned but string literals are not: an
                    # unaligned or string-terminated gap is reproduced as a
                    # literal referenced from a stand-in function (its data is
                    # emitted while that function is compiled). Bytes after the
                    # last NUL become a word-aligned static filler.
                    cut = chunk.rfind(b'\x00') + 1
                    if cut == 0 or (cut < len(chunk) and (gap_lo + cut) % 2):
                        raise FormatError('DGROUP %04X-%04X: unaligned private data that is not a string cannot be reproduced' % (gap_lo, gap_hi))
                    literal = ''.join('\\%03o' % x for x in chunk[:cut - 1])
                    text = ['/* SCAFFOLD, not recovered source: %s. */' % note, 'void far %s(void)' % name, '{', '    volatile char far *p;', '', '    p = "%s";' % literal, '}']
                    literals.append(dict(name=name, text=chr(10).join(text), before=b['member'], rank_member=b['member']))
                    if cut < len(chunk):
                        rest = chunk[cut:]
                        fillers.setdefault(b['member'], []).append('/* SCAFFOLD, not recovered source: %s (word-aligned tail). */\n' % note + 'static unsigned char %s_tail[%d] = {%s};' % (name, len(rest), ', '.join('0x%02X' % x for x in rest)))
                    continue
                body = ', '.join('0x%02X' % x for x in chunk)
                text = '/* SCAFFOLD, not recovered source: %s. */\n' % note + 'static unsigned char %s[%d] = {%s};' % (name, len(chunk), body)
            else:
                text = '/* SCAFFOLD, not recovered source: %d bytes of uninitialised private data between %s and %s (DGROUP %04X-%04X, unclaimed members). */\n' % (gap_hi - gap_lo, a['member'], b['member'], gap_lo, gap_hi) + 'static unsigned char %s[%d];' % (name, gap_hi - gap_lo)
            fillers.setdefault(b['member'], []).append(text)
    order = [p['member'] for cls in ('_DATA', '_BSS') for p in sorted([p for p in kept if p['segment'] == cls], key=lambda p: p['offset'])]
    return dict(fillers=fillers, excluded=excluded, pieces=kept, literals=literals, mode=mode, address_order=list(dict.fromkeys(order)))


def split_layout(kept, data, relocated, functions, excluded):
    """Layout for pieces with kinds: statics are emitted in the preamble in
    address order (member groups, static fillers between them; the tail of the
    static region before the first literal too), body literals follow in code
    order with string stand-ins for the unclaimed members' literals between
    them."""
    def filler_static(lo, hi, note):
        if any(lo <= s < hi for s in relocated):
            raise FormatError('DGROUP %04X-%04X carries loader obligations; no data filler' % (lo, hi))
        if lo % 2:
            raise FormatError('DGROUP %04X-%04X: unaligned static gap cannot be reproduced by a static filler' % (lo, hi))
        chunk = data[lo:hi]
        return '/* SCAFFOLD, not recovered source: %s (DGROUP %04X-%04X), copied from the image so the claimed pieces keep their layout. */\n' % (note, lo, hi) + 'static unsigned char pool_data_fill_%04X[%d] = {%s};' % (lo, len(chunk), ', '.join('0x%02X' % x for x in chunk))
    def filler_literal(lo, hi, note, before):
        if any(lo <= s < hi for s in relocated):
            raise FormatError('DGROUP %04X-%04X carries loader obligations; no data filler' % (lo, hi))
        chunk = data[lo:hi]
        if chunk[-1:] != b'\x00':
            raise FormatError('DGROUP %04X-%04X: literal gap does not end in NUL' % (lo, hi))
        name = 'pool_literal_fill_%04X' % lo
        text = ['/* SCAFFOLD, not recovered source: %s (DGROUP %04X-%04X), unclaimed members\' body literals. */' % (note, lo, hi), 'void far %s(void)' % name, '{', '    volatile char far *p;', '', '    p = "%s";' % ''.join('\\%03o' % x for x in chunk[:-1]), '}']
        return dict(name=name, text=chr(10).join(text), before=before, rank_member=before)
    fillers = {}
    literals = []
    address_order = []
    for cls in ('_DATA', '_BSS'):
        statics = sorted([p for p in kept if p['segment'] == cls and p['kind'] == 'static'], key=lambda p: p['offset'])
        lits = sorted([p for p in kept if p['segment'] == cls and p['kind'] == 'literal'], key=lambda p: p['offset'])
        for a, b in zip(statics, statics[1:]):
            lo, hi = a['offset'] + a['length'], b['offset']
            if hi < lo:
                raise FormatError('%s statics of %s and %s overlap' % (cls, a['member'], b['member']))
            if hi > lo:
                if cls == '_DATA':
                    fillers.setdefault(b['member'], []).append(filler_static(lo, hi, 'static data of unclaimed members between %s and %s' % (a['member'], b['member'])))
                else:
                    fillers.setdefault(b['member'], []).append('/* SCAFFOLD, not recovered source: %d bytes of uninitialised private data between %s and %s (DGROUP %04X-%04X). */\n' % (hi - lo, a['member'], b['member'], lo, hi) + 'static unsigned char pool_bss_fill_%04X[%d];' % (lo, hi - lo))
        for a, b in zip(lits, lits[1:]):
            if functions[a['member']]['offset'] > functions[b['member']]['offset']:
                raise FormatError('%s literals of %s and %s are not in code order' % (cls, a['member'], b['member']))
            lo, hi = a['offset'] + a['length'], b['offset']
            if hi < lo:
                raise FormatError('%s literals of %s and %s overlap' % (cls, a['member'], b['member']))
            if hi > lo:
                literals.append(filler_literal(lo, hi, 'body literals between %s and %s' % (a['member'], b['member']), b['member']))
        if statics and lits and cls == '_DATA':
            last = statics[-1]
            lo, hi = last['offset'] + last['length'], lits[0]['offset']
            if hi < lo:
                raise FormatError('static and literal regions of %s overlap' % cls)
            if hi > lo:
                # the tail of the static region and the first unclaimed literals
                chunk = data[lo:hi]
                cut = chunk.rfind(b'\x00') + 1
                head_end = lo + cut if cut else hi
                # bytes before the last NUL are literals (unaligned), the rest statics
                first_static_nul = chunk.find(b'\x00')
                if first_static_nul >= 0 and (lo % 2 == 0):
                    # try: everything up to the first literal-looking run as static filler
                    pass
                if lo % 2 == 0 and cut and all(32 <= x < 127 or x == 0 for x in chunk[:cut]):
                    literals.append(filler_literal(lo, lo + cut, 'unclaimed body literals before %s' % lits[0]['member'], lits[0]['member']))
                    if lo + cut < hi:
                        raise FormatError('DGROUP %04X-%04X: bytes after the last NUL between statics and literals' % (lo + cut, hi))
                elif lo % 2 == 0:
                    fillers.setdefault('__tail__', []).append(filler_static(lo, hi, 'static data of unclaimed members after %s' % last['member']))
                else:
                    literals.append(filler_literal(lo, hi, 'unclaimed body literals before %s' % lits[0]['member'], lits[0]['member']))
        address_order += [p['member'] for p in statics]
    return dict(fillers=fillers, excluded=excluded, pieces=kept, literals=literals, mode='split', address_order=list(dict.fromkeys(address_order)))


def scaffold_plan(component_id, members, flags, declared, card_list=None, declared_texts=None, folder=None, data_layout='definitions', chosen_sources=None):
    """Stand-in functions that reproduce the selector-pool allocation order of the
    component members the unit does not claim (evidence: original pool words,
    their NE selector relocations, the claimed members' own slot usage).

    A stand-in is generated for every unclaimed member before the last claimed
    member that introduces pool words; each word is referenced through the
    symbol a claimed member uses for it, else an exact MAPSYM name observed
    at its sites, else a representative public data symbol of the addressed
    segment. Stand-ins are compiled into the reserved code segment and are
    never compared or credited."""
    import mapsym
    from common import fixture
    from recovery_workflow import cards
    comp = topology_units()[component_id]
    functions = read_json(TOPOLOGY)['functions']
    publics = comp['publics']
    claimed = [m for m in publics if m in members]
    if not claimed:
        raise FormatError('no claimed members')
    card_list = card_list or cards()
    by_symbol = {c['symbol']: c for c in card_list}
    sources = preserved_sources()
    for m, path in (chosen_sources or {}).items():
        # Reviewed overrides replace the preserved source for slot and data maps too.
        sources[m] = dict(sources.get(m, {}), source=path, basis='REVIEWED_SOURCE_OVERRIDE')
    segments = slot_segments()
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    # A member whose original calls an unnamed static helper (a near call to
    # code no MAPSYM public owns) needs that helper recovered as a static
    # function of the unit; until then it cannot be claimed.
    helper_blocked = {}
    for m in list(claimed):
        if sources[m].get('basis') == 'ADMITTED':
            continue  # already byte-exact in an admitted unit
        targets = [c for c in by_symbol[m].get('calls', []) if c.get('kind') == 'near_call' and not c.get('names') and 0 <= c.get('offset', -1) < 0x10000]
        if targets:
            helper_blocked[m] = sorted({'%04X' % c['offset'] for c in targets})
    if helper_blocked:
        claimed = [m for m in claimed if m not in helper_blocked]
        if not claimed:
            raise FormatError('every claimed member calls an unrecovered static helper: %s' % helper_blocked)
    pieces = []
    for m in claimed:
        target = bytes.fromhex(''.join(r['bytes'] for r in by_symbol[m]['disassembly']))
        try:
            anchored = member_data_anchors(m, sources[m]['source'], flags, target, folder)
        except FormatError:
            anchored = []
        if data_layout == 'split':
            pieces += anchored
        elif anchored:
            # One piece per contiguous run of the member's data (statics and
            # literals of one member are adjacent in the definitions layout).
            for cls in ('_DATA', '_BSS'):
                rows = sorted([x for x in anchored if x['segment'] == cls], key=lambda x: x['offset'])
                merged = []
                for x in rows:
                    if merged and merged[-1]['offset'] + merged[-1]['length'] == x['offset']:
                        merged[-1]['length'] += x['length']
                    else:
                        merged.append(dict(segment=cls, offset=x['offset'], length=x['length'], member=m))
                pieces += merged
        else:
            pieces += member_data_pieces(m, sources[m]['source'], flags, folder)
    data = data_fillers(pieces, comp, functions, data_layout)
    dropped = sorted({p['member'] for p in data['excluded']})
    excluded_pieces = list(data['excluded'])
    if dropped:
        claimed = [m for m in claimed if m not in dropped]
        if not claimed:
            raise FormatError('every claimed member places private data outside the component block')
        data = data_fillers([p for p in pieces if p['member'] not in dropped], comp, functions, data_layout)
        data['excluded'] = excluded_pieces
    shared = {}
    for m in claimed:
        target = bytes.fromhex(''.join(r['bytes'] for r in by_symbol[m]['disassembly']))
        for slot, names in member_slot_symbols(m, sources[m]['source'], flags, target, folder).items():
            shared.setdefault(slot, set()).update(names)
    used = set(declared) | {n.lstrip('_') for s in shared.values() for n in s if not n.startswith('__segname:')}
    symbol_overrides = unify_pool_symbols(shared, declared_texts or {}, symbols)
    located = {}
    for seg in symbols['segments']:
        for x in seg['symbols']:
            located.setdefault(x['name'], (seg['number'], x['offset']))
    sites = far_sites(card_list)
    last = publics.index(claimed[-1])
    def reference(w, f):
        seg = segments.get(w)
        if seg is None:
            raise FormatError('pool word %04X of %s has no selector relocation' % (w, f))
        if w in shared:
            based = [n for n in shared[w] if n.startswith('__segname:')]
            if based:
                # The claimed member addresses this word as a based segment:
                # the stand-in reads through the same based segment.
                name, basis = based[0], 'CLAIMED_MEMBER_SEGMENT'
            else:
                name = min(shared[w], key=lambda n: (located.get(n, (0, 1 << 16))[1], n)).lstrip('_')
                basis = 'CLAIMED_MEMBER_NAME'
        else:
            site_names = sorted(n.lstrip('_') for n in sites.get(w, {}).get('names', ()) if n.startswith('_'))
            site_names = [n for n in site_names if n not in used and sites[w]['segment'] == seg]
            if site_names:
                name, basis = site_names[0], 'MAPSYM_SITE_NAME'
            else:
                pool = [x['name'].lstrip('_') for x in sorted(symbols['segments'][seg - 1]['symbols'], key=lambda x: x['offset']) if x['name'].startswith('_')]
                pool = [n for n in pool if n not in used and re.fullmatch(r'[A-Za-z_]\w*', n)]
                if not pool:
                    raise FormatError('no representative symbol for segment %d' % seg)
                name, basis = pool[0], 'SEGMENT_REPRESENTATIVE'
            used.add(name)
        return dict(word=w, segment=seg, name=name, basis=basis)

    # Walk the object's pool block in order. A word introduced by an unclaimed
    # public goes into that public's stand-in; a word no public's ES sites
    # introduce (a static helper's, or one loaded through another register)
    # is an orphan and is attached, in block order, to the stand-in of the
    # most recent introducer, or to a filler stand-in right after the claimed
    # member that precedes it in code. A stand-in's references are in word
    # order because first-use allocation is sequential.
    introducer = {}
    for f in publics:
        if f in functions:
            for w in functions[f]['introduced']['pool']:
                introducer.setdefault(w, f)
    listed = sorted(int(x, 16) for x in comp.get('pool_words', [])) or sorted(introducer)
    # The block is contiguous: words the topology could not attribute to any
    # public (static helpers, other load forms) are still allocated in it.
    block = list(range(listed[0], listed[-1] + 2, 2)) if listed else []
    stop = max(w for m in claimed for w in functions[m]['slots']) if any(functions[m]['slots'] for m in claimed) else None
    reattributed = []
    # Allocation is sequential, so introducer code positions never decrease
    # along the block. A recorded introducer later than a following word's
    # introducer saw the word at a site the extractor missed earlier: the
    # word is an orphan of the preceding introducer.
    position_of = {f: i for i, f in enumerate(publics)}
    recorded = [position_of.get(introducer.get(w)) for w in block]
    suffix_min = [None] * len(block)
    running = None
    for i in range(len(block) - 1, -1, -1):
        if recorded[i] is not None and (running is None or recorded[i] < running):
            running = recorded[i]
        suffix_min[i] = running
    for i, w in enumerate(block):
        if recorded[i] is not None and i + 1 < len(block) and suffix_min[i + 1] is not None and recorded[i] > suffix_min[i + 1]:
            reattributed.append(dict(word='%04X' % w, recorded=introducer[w], owner=None))
            del introducer[w]
    # A function's words are one contiguous range of the block (they are
    # allocated while it is compiled). A word inside another public's range
    # whose visible ES sites belong to a later public was in fact first used
    # by the range owner through a load the site extractor does not see.
    ranges = {}
    for w, f in introducer.items():
        lo, hi = ranges.get(f, (w, w))
        ranges[f] = (min(lo, w), max(hi, w))
    def owner(w):
        inside = [f for f, (lo, hi) in ranges.items() if lo < w < hi]
        return min(inside, key=lambda f: ranges[f][1] - ranges[f][0]) if inside else None
    stubs = {}
    current = None
    orphans = []
    for w in block:
        if stop is not None and w > stop:
            break
        f = introducer.get(w)
        o = owner(w)
        if o is not None and o != f:
            if o in claimed:
                raise FormatError('pool word %04X lies inside the block range of the claimed member %s but its source does not allocate it' % (w, o))
            reattributed.append(dict(word='%04X' % w, recorded=f, owner=o))
            f = o
        if f is not None:
            current = f
            if f in claimed:
                continue
            stubs.setdefault(f, dict(function=f, position=float(publics.index(f)), references=[], filler=False))['references'].append(reference(w, f))
        else:
            orphans.append('%04X' % w)
            if current is None or current in claimed:
                key = 'after_' + (current or 'start')
                position = publics.index(current) + 0.5 if current else -0.5
                stubs.setdefault(key, dict(function=key, position=position, references=[], filler=True, after=current))['references'].append(reference(w, key))
            else:
                stubs[current]['references'].append(reference(w, current))
    for s in stubs.values():
        s['references'].sort(key=lambda r: r['word'])
    stubs = sorted(stubs.values(), key=lambda s: s['position'])
    # Code runs must be physically contiguous in the original: an unclaimed
    # public or an unnamed static helper between two claimed members ends a run.
    runs = []
    for m in claimed:
        prev = runs[-1][-1] if runs else None
        end = functions[prev]['offset'] + functions[prev]['size'] if prev is not None and functions[prev].get('size') is not None else None
        # MSC pads an odd-sized function with one NOP so the next starts even.
        if end is not None and functions[m]['offset'] in (end, end + (end & 1)):
            runs[-1].append(m)
        else:
            runs.append([m])
    return dict(component=component_id, claimed=claimed, stubs=stubs, runs=runs, unclaimed_after_last=publics[last + 1:], orphan_words=orphans, reattributed_words=reattributed, publics_order=publics, helper_blocked=helper_blocked,
                shared_words={'%04X' % k: sorted(v) for k, v in shared.items()}, symbol_overrides=symbol_overrides,
                data_pieces=data['pieces'], data_fillers=data['fillers'], data_excluded=data['excluded'], data_literals=data['literals'], data_layout=data['mode'], data_address_order=data['address_order'])


def scaffold_text(plan, declared_texts, c_names=None):
    """Declarations, alloc_text pragmas and stand-in definitions for a plan."""
    decls = []
    prototypes = []
    pragmas = []
    definitions = []
    for stub in plan['stubs']:
        fname = 'pool_stub_' + stub['function'].lstrip('_')
        body = []
        for r in stub['references']:
            if r['basis'] == 'CLAIMED_MEMBER_SEGMENT':
                seg = r['name'].split(':', 1)[1]
                ref = 'pool_segment_ref_' + re.sub(r'[^A-Za-z0-9]', '_', seg)
                decl = 'extern int __based(__segname("%s")) %s;  /* scaffold reference for pool word %04X (based segment) */' % (seg, ref, r['word'])
                if decl not in decls:
                    decls.append(decl)
                body.append('    t = %s;' % ref)
                continue
            if r['basis'] != 'CLAIMED_MEMBER_NAME':
                decls.append('extern int far %s;  /* scaffold reference for pool word %04X (segment %d, %s) */' % (r['name'], r['word'], r['segment'], r['basis']))
            body.append('    t = %s;' % reference_expression(r['name'], declared_texts.get(r['name'])))
        prototypes.append('void far %s(void);' % fname)
        pragmas.append('#pragma alloc_text(%s, %s)' % (SCAFFOLD_SEGMENT, fname))
        what = ('stand-in for the pool words a static helper introduces after %s' % stub.get('after')) if stub.get('filler') else ('stand-in for the unclaimed member %s' % stub['function'])
        text = ['/* SCAFFOLD, not recovered source: %s.' % what,
                ' * It only reproduces the object\'s selector-pool allocation order for the',
                ' * words %s; its code is compiled into the reserved' % ' '.join('%04X' % r['word'] for r in stub['references']),
                ' * segment %s, which the matcher never compares or credits. */' % SCAFFOLD_SEGMENT,
                'void far %s(void)' % fname, '{', '    volatile int t;', ''] + body + ['}']
        definitions.append(dict(name=fname, text='\n'.join(text), rank_name=stub['function'], rank=stub['position']))
    c_names = c_names or {}
    publics_rank = {m: i for i, m in enumerate(plan.get('publics_order', []))}
    for lit in plan.get('data_literals', []):
        prototypes.append('void far %s(void);' % lit['name'])
        pragmas.append('#pragma alloc_text(%s, %s)' % (SCAFFOLD_SEGMENT, lit['name']))
        definitions.append(dict(name=lit['name'], text=lit['text'], rank_name=lit['rank_member'], rank=publics_rank.get(lit['rank_member'], 0) - 0.25))
    for k, run in enumerate(plan['runs'][1:], start=2):
        names = [c_names.get(m, m.lstrip('_')) for m in run]
        for i in range(0, len(names), 4):
            pragmas.append('#pragma alloc_text(RUN%d_TEXT, %s)' % (k, ', '.join(names[i:i + 4])))
    return dict(declarations=decls, prototypes=prototypes, pragmas=pragmas, definitions=definitions)


def harmonize(component_id, members, flags, folder, layout='preambles-first', overrides=None, source_overrides=None):
    """Resolve declaration conflicts by verification, never by preference.

    For a name spelled differently by the claimed sources, a spelling is
    admissible only if every claimed member whose definition uses the name
    keeps its exact body when its own source is recompiled in isolation with
    that spelling substituted. The first admissible spelling (most users
    first) becomes a recorded override; a name with no admissible spelling
    stays a conflict. Every trial compile is kept under the unit folder."""
    from codegen_grinder import run
    from recovery_workflow import cards
    sources = preserved_sources()
    comp = topology_units()[component_id]
    order = [m for m in comp['publics'] if m in members]
    chosen = {m: sources[m]['source'] for m in order}
    for m, path in (source_overrides or {}).items():
        if m in chosen:
            chosen[m] = path  # reviewed sources take part in harmonization like any member text
    overrides = dict(overrides or {})
    result = compose(chosen, order, 'harmonize', layout, overrides, declaration_order=declaration_order_constraints(component_id))
    if result['status'] == 'COMPOSED':
        return dict(status='COMPOSED', overrides=overrides, trials=[])
    parsed = {m: split_items((ROOT / chosen[m]).read_text(encoding='latin1')) for m in order}
    definition_text = {m: '\n'.join(it['text'] for it in parsed[m] if it['kind'] == 'definition') for m in order}
    by_name = {}
    for c in result['conflicts']:
        entry = by_name.setdefault(c['name'], {})
        entry.setdefault(c['first'], set()).add(c['first_from'])
        entry.setdefault(c['other'], set()).add(c['other_from'])
    trials = []
    unresolved = []
    trial_dir = folder / 'harmonize'
    trial_dir.mkdir(parents=True, exist_ok=True)
    for name, spellings in by_name.items():
        if name in overrides:
            continue
        users = [m for m in order if re.search(r'(?<![A-Za-z0-9_])' + re.escape(name) + r'(?![A-Za-z0-9_])', definition_text[m])]
        own = {}
        for m in order:
            for it in parsed[m]:
                if it['kind'] == 'declaration' and name in (it['names'] or []):
                    own[m] = it
        ranked = sorted(spellings, key=lambda s: -len(spellings[s]))
        accepted = None
        for spelling in ranked:
            text = next(it['text'] for m in order for it in parsed[m] if it['kind'] == 'declaration' and it['normalized'] == spelling)
            ok = True
            for u in users:
                if u not in own or own[u]['normalized'] == spelling:
                    continue
                source = (ROOT / chosen[u]).read_text(encoding='latin1').replace(own[u]['text'], text, 1)
                key = sha256((u + spelling).encode())[:8]
                path = trial_dir / ('%s_%s_%s.c' % (u.lstrip('_'), re.sub(r'[^A-Za-z0-9]+', '_', name), key))
                path.write_text(source, encoding='latin1')
                report = run(dict(symbol=u, source=path.relative_to(ROOT).as_posix(), compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[u]),
                             (trial_dir / ('%s_%s_%s' % (u.lstrip('_'), re.sub(r'[^A-Za-z0-9]+', '_', name), key))).relative_to(ROOT).as_posix(), cache=True)
                comparison = report['results'][0]['comparison']
                exact = body_exact(comparison)
                trials.append(dict(name=name, spelling=spelling, member=u, source=path.relative_to(ROOT).as_posix(), exact=exact, result=comparison['result']))
                if not exact:
                    ok = False
                    break
            if ok:
                accepted = text
                break
        if accepted is None:
            unresolved.append(dict(name=name, spellings={s: sorted(v) for s, v in spellings.items()}))
        else:
            overrides[name] = accepted
    write_json(folder / 'harmonize.json', dict(component=component_id, members=order, overrides=overrides, unresolved=unresolved, trials=trials,
                                                scope='Declaration spellings chosen only when every user keeps its exact body in isolation; trial sources and reports are kept'))
    return dict(status='COMPOSED' if not unresolved else 'DECLARATION_CONFLICT', overrides=overrides, unresolved=unresolved, trials=trials)


def build_unit(component_id, members=None, layout='preambles-first', overrides=None, reason='', source_overrides=None, unit_source=None, scaffold=False, harmonize_conflicts=False, data_layout='definitions'):
    """Compose a candidate unit from preserved sources and write its evidence folder."""
    import compiler_profiles
    from recovery_workflow import cards
    comps = topology_units()
    if component_id not in comps:
        raise FormatError('unknown build-topology component ' + component_id)
    comp = comps[component_id]
    members = members or comp['publics']
    if any(m not in comp['publics'] for m in members):
        raise FormatError('members must belong to the component')
    order = [m for m in comp['publics'] if m in members]
    if order != members:
        raise FormatError('members must be given in MAPSYM order')
    if unit_source is not None:
        # A reviewed hand-written unit (publics plus static helpers between them).
        path = ROOT / unit_source
        if not path.exists() or not path.resolve().is_relative_to(ROOT):
            raise FormatError('unit source must be a repository file')
        text = path.read_text(encoding='latin1')
        for m in members:
            if not re.search(r'\b' + re.escape(m.lstrip('_')) + r'\s*\(', text):
                raise FormatError('unit source does not define ' + m)
        import compiler_profiles
        names = {compiler_profiles.resolve(m)['name'] for m in members}
        if len(names) != 1:
            raise FormatError('members resolve to different compiler profiles: ' + str(names))
        profile = next(iter(names))
        unit_id = re.sub(r'[^A-Za-z0-9]+', '_', component_id) + '_%s_%d_reviewed' % (members[0].lstrip('_'), len(members))
        folder = UNITS / unit_id
        folder.mkdir(parents=True, exist_ok=True)
        (folder / 'unit.c').write_text(text, encoding='latin1')
        spec = dict(unit=unit_id, component=component_id, segment=comp['segment'], members=members, sources={'*': dict(source=unit_source, basis='REVIEWED_UNIT_SOURCE', identity=identity(path))},
                    profile=profile, flags=compiler_profiles.profile_flags(profile, comp['segment']), layout='reviewed', overrides={}, reason=reason, created=timestamp(),
                    topology=dict(join_evidence=comp.get('join_evidence'), range=comp['range']), status='COMPOSED', source=(folder / 'unit.c').relative_to(ROOT).as_posix(), source_identity=identity(folder / 'unit.c'))
        if scaffold:
            spec['scaffold'] = reviewed_scaffold(text, members, comp['publics'])
        write_json(folder / 'unit.json', spec)
        return spec
    sources = preserved_sources()
    for m, path in (source_overrides or {}).items():
        if not (ROOT / path).exists() or not (ROOT / path).resolve().is_relative_to(ROOT):
            raise FormatError('reviewed source override must be a repository file: ' + path)
        sources[m] = dict(source=path, basis='REVIEWED_SOURCE_OVERRIDE')
    chosen = {}
    for m in members:
        if m not in sources:
            raise FormatError('no preserved source for ' + m)
        chosen[m] = sources[m]['source']
    unit_id = re.sub(r'[^A-Za-z0-9]+', '_', component_id) + ('' if members == comp['publics'] else '_%s_%d' % (members[0].lstrip('_'), len(members))) + ('_scaffold' if scaffold else '') + ('_pre' if scaffold and data_layout == 'preamble' else '_split' if scaffold and data_layout == 'split' else '')
    folder = UNITS / unit_id
    folder.mkdir(parents=True, exist_ok=True)
    profiles = {m: compiler_profiles.resolve(m) for m in members}
    names = {p['name'] for p in profiles.values()}
    if len(names) != 1:
        raise FormatError('members resolve to different compiler profiles: ' + str(names))
    profile = next(iter(names))
    segment = comp['segment']
    flags = compiler_profiles.profile_flags(profile, segment)
    harmonized = None
    excluded_by_conflict = []
    if harmonize_conflicts:
        harmonized = harmonize(component_id, members, flags, folder, layout, overrides, source_overrides)
        overrides = dict(harmonized['overrides'])
        if scaffold and harmonized.get('unresolved'):
            # A genuine conflict (no spelling keeps every user exact) excludes
            # the members of the minority spelling from this unit; they stay
            # exact bodies for a later, separately reviewed unit.
            for c in harmonized['unresolved']:
                users = sorted(c['spellings'].items(), key=lambda kv: -len(kv[1]))
                for spelling, syms in users[1:]:
                    excluded_by_conflict += [s for s in syms if s not in excluded_by_conflict]
            members = [m for m in members if m not in excluded_by_conflict]
            if not members:
                raise FormatError('declaration conflicts exclude every member')
            order = [m for m in comp['publics'] if m in members]
            chosen = {m: chosen[m] for m in members}
    plan = None
    if scaffold:
        if layout != 'preambles-first':
            raise FormatError('scaffolding requires the preambles-first layout')
        unclaimed = [m.lstrip('_') for m in comp['publics'] if m not in members]
        first = compose(chosen, order, unit_id, layout, overrides, declaration_order=declaration_order_constraints(component_id), exclude_definitions=unclaimed)
        if first['status'] != 'COMPOSED':
            plan_declared = []
        else:
            plan_declared = [n for d in first['declaration_items'] for n in d['names']]
        if first['status'] == 'COMPOSED':
            declared_texts = {}
            for d in sorted(first['declaration_items'], key=lambda d: d['text'].lstrip().startswith('#define')):
                for n in d['names']:
                    declared_texts.setdefault(n, d['text'])
            plan = scaffold_plan(component_id, members, flags, plan_declared, declared_texts=declared_texts, folder=folder, data_layout=data_layout, chosen_sources=chosen)
            for _ in range(4):
                if plan['claimed'] == members:
                    break
                # Members whose private data lies outside the component block,
                # or whose original calls an unrecovered static helper, cannot
                # be claimed by this unit (their isolated binding is under
                # review). Their sources leave the unit entirely: the
                # declarations they carried must not shape the claimed members.
                members = plan['claimed']
                order = [m for m in comp['publics'] if m in members]
                chosen = {m: chosen[m] for m in members}
                unclaimed = [m.lstrip('_') for m in comp['publics'] if m not in members]
                first = compose(chosen, order, unit_id, layout, overrides, declaration_order=declaration_order_constraints(component_id), exclude_definitions=unclaimed)
                if first['status'] != 'COMPOSED':
                    break
                plan_declared = [n for d in first['declaration_items'] for n in d['names']]
                declared_texts = {}
                for d in sorted(first['declaration_items'], key=lambda d: d['text'].lstrip().startswith('#define')):
                    for n in d['names']:
                        declared_texts.setdefault(n, d['text'])
                plan = scaffold_plan(component_id, members, flags, plan_declared, declared_texts=declared_texts, folder=folder, data_layout=data_layout, chosen_sources=chosen)
            if plan['symbol_overrides']:
                overrides = dict(overrides or {}, **plan['symbol_overrides'])
        if first['status'] == 'COMPOSED':
            # MAPSYM name -> C definition name (Pascal exports are upper-cased in MAPSYM).
            c_names = {}
            for m in members:
                c_names[m] = m.lstrip('_') if m.startswith('_') else next((d['name'] for d in first['definition_items'] if d['name'].upper() == m), m)
            parts = scaffold_text(plan, declared_texts, c_names)
            later = {c_names[m] for run in plan['runs'][1:] for m in run}
            prototypes = parts['prototypes'] + [re.sub(chr(92) + 's+', ' ', d['text'][:d['text'].index('{')]).strip() + ';' for d in first['definition_items'] if d['name'] in later]
            result = compose(chosen, order, unit_id, layout, overrides, declaration_order=declaration_order_constraints(component_id), extra_definitions=parts['definitions'], exclude_definitions=unclaimed,
                             pragmas=parts['declarations'] + [''] + prototypes + [''] + parts['pragmas'], rank_order=comp['publics'],
                             statics_with_definitions=(data_layout == 'definitions'), fillers_before=plan['data_fillers'],
                             statics_address_order=(plan['data_address_order'] if data_layout in ('preamble', 'split') else None),
                             header_notes=['SCAFFOLDED: unclaimed members %s are stand-ins in %s (pool order only, never compared).' % (', '.join(s['function'] for s in plan['stubs']), SCAFFOLD_SEGMENT)] if plan['stubs'] else ['SCAFFOLDED: claimed members in %d code runs; no pool stand-ins were needed.' % len(plan['runs'])])
        else:
            result = first
    else:
        result = compose(chosen, order, unit_id, layout, overrides, declaration_order=declaration_order_constraints(component_id))
    spec = dict(unit=unit_id, component=component_id, segment=segment, members=members, sources={m: dict(sources[m], identity=identity(ROOT / sources[m]['source'])) for m in members},
                profile=profile, flags=flags, layout=layout, overrides=overrides or {}, reason=reason, created=timestamp(),
                topology=dict(join_evidence=comp.get('join_evidence'), range=comp['range']), status=result['status'])
    if harmonized is not None:
        spec['harmonization'] = dict(overrides=harmonized['overrides'], unresolved=harmonized.get('unresolved', []), trials=len(harmonized['trials']), excluded_members=excluded_by_conflict, evidence=(folder / 'harmonize.json').relative_to(ROOT).as_posix())
    if plan is not None:
        spec['members'] = plan['claimed']
        spec['scaffold'] = dict(segment=SCAFFOLD_SEGMENT, stubs=plan['stubs'], runs=plan['runs'], unclaimed_after_last=plan['unclaimed_after_last'], shared_words=plan['shared_words'], symbol_overrides=plan['symbol_overrides'], orphan_words=plan['orphan_words'],
                                data_pieces=plan['data_pieces'], data_fillers={k: len(v) for k, v in plan['data_fillers'].items()}, data_excluded=plan['data_excluded'],
                                scope='Stand-ins reproduce only the selector-pool allocation order of unclaimed members; they are not recovered source and are never compared or credited')
    if result['status'] != 'COMPOSED':
        spec['conflicts'] = result['conflicts']
        write_json(folder / 'unit.json', spec)
        return spec
    (folder / 'unit.c').write_text(result['text'], encoding='latin1')
    spec.update(source=(folder / 'unit.c').relative_to(ROOT).as_posix(), source_identity=identity(folder / 'unit.c'), declarations=result['declarations'], definitions=result['definitions'])
    write_json(folder / 'unit.json', spec)
    return spec


def test_unit(unit_id):
    """Compile the composed unit and compare all contributions; diagnostic only."""
    from codegen_grinder import run
    folder = UNITS / unit_id
    spec = read_json(folder / 'unit.json')
    if spec['status'] != 'COMPOSED':
        raise FormatError('unit is not composed: ' + spec['status'])
    if identity(ROOT / spec['source']) != spec['source_identity']:
        raise FormatError('unit source changed since composition')
    grinder_spec = dict(symbol=spec['members'][0], source=spec['source'], compiler='msc700', flags=spec['flags'], max_candidates=1, axes=[],
                        semantic_summary='Unit assembly of preserved sources: ' + unit_id, publics=spec['members'])
    report = run(grinder_spec, (folder / 'test').relative_to(ROOT).as_posix(), cache=True)
    best = report['results'][0]
    comparison = best['comparison']
    summary = dict(unit=unit_id, result=comparison['result'], issues=comparison.get('issues', []), placements=comparison.get('placements'),
                   private_constraint_placements=comparison.get('private_constraint_placements'), literal_equal=comparison.get('literal_equal'), literal_compared=comparison.get('literal_compared'),
                   fixups_equal=comparison.get('fixups_equal'), fixups_total=comparison.get('fixups_total'),
                   contributions=[dict(segment=c['segment'], original_offset=c['original_offset'], length=c['length'], divergences=len(c['divergences']), failed_fixups=sum(1 for f in c['fixups'] if not f['equal'])) for c in comparison.get('contributions', [])],
                   compiler_log=best['receipt']['stdout'][-600:] if comparison['result'] == 'COMPILE_FAILED' else None, report=(folder / 'test/results.json').relative_to(ROOT).as_posix(), tested=timestamp())
    spec['last_test'] = summary
    write_json(folder / 'unit.json', spec)
    return summary


def unit_job(unit_id, reason):
    """Create a TU_ASSEMBLY workflow job so admission uses the ordinary fresh promotion path."""
    import recovery_workflow as wf
    folder = UNITS / unit_id
    spec = read_json(folder / 'unit.json')
    if spec['status'] != 'COMPOSED':
        raise FormatError('unit is not composed')
    if not spec.get('last_test') or spec['last_test']['result'] not in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
        raise FormatError('unit has no exact test result; a job is only issued for an exact unit')
    if not reason.strip():
        raise FormatError('reviewed reason required')
    recipes = wf.recipes()
    members = spec['members']
    supersedes = [m for m in members if m in recipes]
    key = sha256((unit_id + spec['source_identity']['sha256']).encode())[:10]
    job_id = 'tu_' + unit_id + '-' + key
    directory = wf.STATE / 'jobs' / job_id
    if directory.exists():
        previous = read_json(directory / 'job.json')
        if previous['status'] == 'PROMOTED':
            raise FormatError('unit job already exists: ' + job_id)
        # Same unit source, different admission context (e.g. members admitted
        # since): archive the stale job and issue a fresh one.
        import shutil
        archive = wf.STATE / 'superseded-unit-jobs' / ('%s-%s' % (job_id, wf.timestamp().replace(':', '').replace('-', '')[:15]))
        archive.parent.mkdir(parents=True, exist_ok=True)
        shutil.move(str(directory), str(archive))
    directory.mkdir(parents=True)
    candidate = directory / 'candidate.c'
    candidate.write_bytes((ROOT / spec['source']).read_bytes())
    submission = dict(symbol=members[0], source=wf.relative(candidate), compiler='msc700', flags=spec['flags'], max_candidates=1, axes=[],
                      semantic_summary='Unit assembly %s: %s' % (unit_id, reason), binding_evidence=['evidence/topology/build-topology.json', wf.relative(folder / 'unit.json')], publics=members)
    write_json(directory / 'submission.json', submission)
    job = dict(id=job_id, symbol=members[0], lane='TU_ASSEMBLY', unit=unit_id, component=spec['component'], publics=members, supersedes=supersedes,
               status='OPEN', created=wf.timestamp(), flags=spec['flags'], profile=__import__('compiler_profiles').resolve(members[0]), protected=wf.protected(),
               fixture_identity=read_json(ROOT / 'layout/fixtures.json'), attempts=[], reason=reason, unit_evidence=wf.relative(folder / 'unit.json'))
    if spec.get('scaffold'):
        job['scaffold'] = dict(unit=unit_id, segment=spec['scaffold']['segment'], stand_ins=[s['function'] for s in spec['scaffold']['stubs']], runs=spec['scaffold']['runs'])
    wf.atomic_json(directory / 'job.json', job)
    (directory / 'packet.md').write_text('# Unit assembly job %s\n\nMembers: %s\n\nEvidence: %s\n' % (job_id, ', '.join(members), wf.relative(folder / 'unit.json')), encoding='utf-8')
    return dict(job=job_id, publics=members, supersedes=supersedes)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest='action', required=True)
    p = sub.add_parser('propose'); p.add_argument('--min', type=int, default=1); p.add_argument('--limit', type=int, default=40)
    p = sub.add_parser('build'); p.add_argument('component'); p.add_argument('--members'); p.add_argument('--layout', default='preambles-first', choices=['preambles-first', 'interleaved']); p.add_argument('--override', action='append', default=[]); p.add_argument('--source', action='append', default=[], help='SYMBOL=path reviewed source override'); p.add_argument('--unit-source', help='reviewed hand-written unit source (publics plus static helpers)'); p.add_argument('--scaffold', action='store_true', help='stand-ins for unclaimed members reproduce the pool order'); p.add_argument('--harmonize', action='store_true', help='resolve declaration conflicts by isolated exact-body verification'); p.add_argument('--data-layout', default='definitions', choices=['definitions', 'preamble', 'split'], help='where a scaffolded unit emits claimed statics: with their definitions or at the top in address order'); p.add_argument('--reason', default='')
    p = sub.add_parser('test'); p.add_argument('unit')
    p = sub.add_parser('job'); p.add_argument('unit'); p.add_argument('--reason', required=True)
    args = ap.parse_args()
    if args.action == 'propose':
        rows = propose(args.min)
        for r in rows[:args.limit]:
            print('%-14s unlock=%2d usable=%2d/%2d groups=%s blocked=%d' % (r['component'], r['unlock'], len(r['usable']), len(r['members']), [len(g) for g in r['groups']], len(r['blocked'])))
        write_json(UNITS / 'proposals.json', dict(generated=timestamp(), proposals=rows))
    elif args.action == 'build':
        overrides = {}
        for item in args.override:
            name, text = item.split('=', 1)
            overrides[name] = text
        source_overrides = dict(item.split('=', 1) for item in args.source)
        result = build_unit(args.component, args.members.split(',') if args.members else None, args.layout, overrides, args.reason, source_overrides, args.unit_source, args.scaffold, args.harmonize, args.data_layout)
        print(json.dumps({k: v for k, v in result.items() if k not in ('sources',)}, indent=2))
    elif args.action == 'test':
        print(json.dumps(test_unit(args.unit), indent=2))
    else:
        print(json.dumps(unit_job(args.unit, args.reason), indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
