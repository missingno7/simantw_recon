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
from common import ROOT, FormatError, read_json, write_json, identity, sha256

UNITS = ROOT / 'evidence/recovery/units'
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
    m = re.match(r'extern\s+(.*?)\s*\b(near|far)\b\s*' + re.escape(name) + r'\s*((?:\[[^\]]*\]\s*)*);$', normalized)
    if not m:
        return None
    base = ' '.join(m.group(1).split())
    if base == 'char':
        base = 'signed char'
    dims = re.findall(r'\[([^\]]*)\]', m.group(3) or '')
    return dict(base=base, distance=m.group(2), dims=dims)


def view_macro(name, own, canonical):
    """A per-definition macro that lets a member written against one shape of a
    far/near object use the canonical declaration of the same object without
    changing its text or its code: element 0 for a scalar view of an array,
    the flattened element pointer for a 1-D view of an N-D array, the address
    for an array view of a scalar. The self-reference expands once."""
    if own['distance'] != canonical['distance']:
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


def compose(sources, order, unit_id, layout='preambles-first', overrides=None, extra_definitions=None, pragmas=None, rank_order=None, header_notes=None, exclude_definitions=()):
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
                tag_texts.setdefault(it['names'][0], {}).setdefault(it['normalized'], []).append(f['symbol'])
    tag_renames = {}
    for tag, variants in tag_texts.items():
        if len(variants) < 2:
            continue
        keyword, name = tag.split(' ', 1)
        for n, spelling in enumerate(list(variants)[1:], start=2):
            for symbol in variants[spelling]:
                tag_renames.setdefault(symbol, {})[tag] = '%s %s_%d' % (keyword, name, n)
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
        best = max(shapes, key=lambda s: (len(shapes[s]['dims']), sum(1 for d in shapes[s]['dims'] if d.strip()), len(variants[s]), -list(shapes).index(s)))
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
    header = ['/* Candidate translation unit %s: composed from preserved exact-body sources' % unit_id,
              ' * in MAPSYM order. Internal evidence id, not a historical filename.',
              ' * Members: %s' % ', '.join(order)] + [' * ' + n for n in (header_notes or [])]
    header[-1] += ' */'
    header.append('')
    lines = list(header)
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


def preserved_sources():
    """Best preserved source per symbol: admitted recipe, else body-solved / best job candidate."""
    result = {}
    recipes = read_json(ROOT / 'src/recovery.json')['targets']
    for symbol, target in recipes.items():
        result[symbol] = dict(source=target['source'], basis='ADMITTED', profile=target.get('profile', 'baseline'))
    families = ROOT / 'evidence/recovery/blocker-families.json'
    if families.exists():
        for symbol, f in read_json(families)['functions'].items():
            if symbol in result:
                continue
            if f.get('preserved_source'):
                result[symbol] = dict(source=f['preserved_source'], basis='BODY_MATCHED_BINDING_BLOCKED')
    for path in (ROOT / 'evidence/recovery/workflow/jobs').glob('*/job.json'):
        job = read_json(path)
        if job['symbol'] in result or job.get('lane') == 'TU_ASSEMBLY' or not job.get('attempts'):
            continue
        best = None
        for attempt in job['attempts']:
            report_path = ROOT / attempt['report']
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
                from topology_diagnostics import classify
                exact_body = classify(row['comparison']) is not None
                key = (exact_body, d['opcode_matches'], -abs(d.get('candidate_bytes', 0) - d.get('target_bytes', 0)))
                source = ROOT / row['receipt']['source']
                if source.exists() and (best is None or key > best[0]):
                    best = (key, source.relative_to(ROOT).as_posix(), exact_body)
        if best:
            result[job['symbol']] = dict(source=best[1], basis='EXACT_BODY_CANDIDATE' if best[2] else 'BEST_CANDIDATE_NOT_EXACT')
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
        usable = [m for m in members if have[m] and have[m]['basis'] in ('ADMITTED', 'BODY_MATCHED_BINDING_BLOCKED', 'EXACT_BODY_CANDIDATE')]
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
    """Strict GOOD result, or a body that differs only in unresolved offset bindings."""
    from topology_diagnostics import classify
    return comparison.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER') or classify(comparison) is not None


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


def scaffold_plan(component_id, members, flags, declared, card_list=None, declared_texts=None, folder=None):
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
    segments = slot_segments()
    symbols = mapsym.parse(fixture('SIMANTW.SYM'))
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
    block = sorted(int(x, 16) for x in comp.get('pool_words', [])) or sorted(introducer)
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
    return dict(component=component_id, claimed=claimed, stubs=stubs, runs=runs, unclaimed_after_last=publics[last + 1:], orphan_words=orphans, reattributed_words=reattributed,
                shared_words={'%04X' % k: sorted(v) for k, v in shared.items()}, symbol_overrides=symbol_overrides)


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
    for k, run in enumerate(plan['runs'][1:], start=2):
        names = [c_names.get(m, m.lstrip('_')) for m in run]
        for i in range(0, len(names), 4):
            pragmas.append('#pragma alloc_text(RUN%d_TEXT, %s)' % (k, ', '.join(names[i:i + 4])))
    return dict(declarations=decls, prototypes=prototypes, pragmas=pragmas, definitions=definitions)


def harmonize(component_id, members, flags, folder, layout='preambles-first', overrides=None):
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
    overrides = dict(overrides or {})
    result = compose(chosen, order, 'harmonize', layout, overrides)
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


def build_unit(component_id, members=None, layout='preambles-first', overrides=None, reason='', source_overrides=None, unit_source=None, scaffold=False, harmonize_conflicts=False):
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
    unit_id = re.sub(r'[^A-Za-z0-9]+', '_', component_id) + ('' if members == comp['publics'] else '_%s_%d' % (members[0].lstrip('_'), len(members))) + ('_scaffold' if scaffold else '')
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
    if harmonize_conflicts:
        harmonized = harmonize(component_id, members, flags, folder, layout, overrides)
        overrides = dict(harmonized['overrides'])
    plan = None
    if scaffold:
        if layout != 'preambles-first':
            raise FormatError('scaffolding requires the preambles-first layout')
        unclaimed = [m.lstrip('_') for m in comp['publics'] if m not in members]
        first = compose(chosen, order, unit_id, layout, overrides, exclude_definitions=unclaimed)
        if first['status'] != 'COMPOSED':
            plan_declared = []
        else:
            plan_declared = [n for d in first['declaration_items'] for n in d['names']]
        if first['status'] == 'COMPOSED':
            declared_texts = {}
            for d in sorted(first['declaration_items'], key=lambda d: d['text'].lstrip().startswith('#define')):
                for n in d['names']:
                    declared_texts.setdefault(n, d['text'])
            plan = scaffold_plan(component_id, members, flags, plan_declared, declared_texts=declared_texts, folder=folder)
            if plan['symbol_overrides']:
                overrides = dict(overrides or {}, **plan['symbol_overrides'])
            # MAPSYM name -> C definition name (Pascal exports are upper-cased in MAPSYM).
            c_names = {}
            for m in members:
                c_names[m] = m.lstrip('_') if m.startswith('_') else next((d['name'] for d in first['definition_items'] if d['name'].upper() == m), m)
            parts = scaffold_text(plan, declared_texts, c_names)
            later = {c_names[m] for run in plan['runs'][1:] for m in run}
            prototypes = parts['prototypes'] + [re.sub(chr(92) + 's+', ' ', d['text'][:d['text'].index('{')]).strip() + ';' for d in first['definition_items'] if d['name'] in later]
            result = compose(chosen, order, unit_id, layout, overrides, extra_definitions=parts['definitions'], exclude_definitions=unclaimed,
                             pragmas=parts['declarations'] + [''] + prototypes + [''] + parts['pragmas'], rank_order=comp['publics'],
                             header_notes=['SCAFFOLDED: unclaimed members %s are stand-ins in %s (pool order only, never compared).' % (', '.join(s['function'] for s in plan['stubs']), SCAFFOLD_SEGMENT)] if plan['stubs'] else ['SCAFFOLDED: claimed members in %d code runs; no pool stand-ins were needed.' % len(plan['runs'])])
        else:
            result = first
    else:
        result = compose(chosen, order, unit_id, layout, overrides)
    spec = dict(unit=unit_id, component=component_id, segment=segment, members=members, sources={m: dict(sources[m], identity=identity(ROOT / sources[m]['source'])) for m in members},
                profile=profile, flags=flags, layout=layout, overrides=overrides or {}, reason=reason, created=timestamp(),
                topology=dict(join_evidence=comp.get('join_evidence'), range=comp['range']), status=result['status'])
    if harmonized is not None:
        spec['harmonization'] = dict(overrides=harmonized['overrides'], unresolved=harmonized.get('unresolved', []), trials=len(harmonized['trials']), evidence=(folder / 'harmonize.json').relative_to(ROOT).as_posix())
    if plan is not None:
        spec['scaffold'] = dict(segment=SCAFFOLD_SEGMENT, stubs=plan['stubs'], runs=plan['runs'], unclaimed_after_last=plan['unclaimed_after_last'], shared_words=plan['shared_words'], symbol_overrides=plan['symbol_overrides'], orphan_words=plan['orphan_words'],
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
        raise FormatError('unit job already exists: ' + job_id)
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
    p = sub.add_parser('build'); p.add_argument('component'); p.add_argument('--members'); p.add_argument('--layout', default='preambles-first', choices=['preambles-first', 'interleaved']); p.add_argument('--override', action='append', default=[]); p.add_argument('--source', action='append', default=[], help='SYMBOL=path reviewed source override'); p.add_argument('--unit-source', help='reviewed hand-written unit source (publics plus static helpers)'); p.add_argument('--scaffold', action='store_true', help='stand-ins for unclaimed members reproduce the pool order'); p.add_argument('--harmonize', action='store_true', help='resolve declaration conflicts by isolated exact-body verification'); p.add_argument('--reason', default='')
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
        result = build_unit(args.component, args.members.split(',') if args.members else None, args.layout, overrides, args.reason, source_overrides, args.unit_source, args.scaffold, args.harmonize)
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
