"""Mass, one-factor-at-a-time MSC 7.00 register/home allocation study.

Usage:
    python tools/alloc_lab.py generate
    python tools/alloc_lab.py run [--limit N] [--profiles baseline,og,oi,ogi]
    python tools/alloc_lab.py summarize

Generated sources, objects, observations and model reports are all kept under
build/alloc_lab.  The source grid is deliberately orthogonal: each row changes
one named allocation factor from its family control.  Compilation is performed
through the authentic compiler cache/service and catalogued profile flags.
"""
from __future__ import annotations

import argparse
import itertools
import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, read_json, relative, write_json
from codegen_cache import compile_cached
from compiler_profiles import profile_flags
import frame_map
import omf
from probe import measure

OUT = ROOT / 'build/alloc_lab'
SOURCE_DIR = OUT / 'sources'
OBSERVATIONS = OUT / 'observations.jsonl'
REPORT = OUT / 'model.json'
PROFILES = ('baseline', 'og', 'oi', 'ogi')


def _program(locals_, body, params='int seed'):
    decls = '\n'.join('    int %s = %s;' % (name, init) for name, init in locals_)
    return ('extern volatile int alloc_sink;\n'
            'int f(%s) {\n%s\n%s\n    return %s;\n}\n'
            % (params, decls, body, ' + '.join(name for name, _ in locals_) or 'seed'))


def _use_statements(names, counts=None, loop_depth=0):
    counts = counts or {n: 1 for n in names}
    lines = []
    if loop_depth:
        for d in range(loop_depth):
            lines.append('    ' * (d + 1) + 'for (int i%d = 0; i%d < 3; ++i%d) {' % (d, d, d))
    for name in names:
        for j in range(counts[name]):
            expr = name if j == 0 else '(%s + %d)' % (name, j)
            lines.append('    ' * (loop_depth + 1) + 'alloc_sink = %s;' % expr)
    for d in reversed(range(loop_depth)):
        lines.append('    ' * (d + 1) + '}')
    return '\n'.join(lines)


def _locals(n=3, typ='int', init='seed + {i}'):
    return [(chr(ord('a') + i), init.format(i=i)) for i in range(n)]


def _row(family, factor, value, text, baseline=''):
    return dict(family=family, factor=factor, value=value, source=text, control=baseline)


def _legacy_generate_cases():
    """Return a sizeable orthogonal grid. Each source changes one factor."""
    cases = []

    # Candidate count (1..5), with one final observable read per word.
    for n in range(1, 6):
        ls = _locals(n)
        names = [n for n, _ in ls]
        cases.append(_row('competition', 'word_locals', n, _program(ls, _use_statements(names))))

    # Static use count for each of three equally-live candidates.
    for var in 'abc':
        for count in range(1, 161):
            ls = _locals(3)
            counts = {n: 1 for n, _ in ls}; counts[var] = count
            cases.append(_row('weight', 'static_uses:%s' % var, count,
                              _program(ls, _use_statements([n for n, _ in ls], counts))))

    # Loop depth 0/1/2 for the use of one candidate; the other two are outside.
    for var in 'abc':
        for depth in range(3):
            ls = _locals(3); names = [n for n, _ in ls]
            inside = _use_statements([var], loop_depth=depth)
            outside = _use_statements([n for n in names if n != var])
            body = '\n'.join(x for x in (inside, outside) if x)
            cases.append(_row('weight', 'loop_depth:%s' % var, depth, _program(ls, body)))

    # Definition/use order and declaration order, isolated from local identity.
    for order in itertools.permutations('abc'):
        ls = [(n, 'seed + %d' % (ord(n) - 96)) for n in order]
        cases.append(_row('order', 'declaration', ''.join(order), _program(ls, _use_statements('abc'))))
        statements = '\n'.join('    alloc_sink = %s;' % n for n in order)
        cases.append(_row('order', 'first_use', ''.join(order), _program(_locals(3), statements)))
    for order in itertools.permutations('abc'):
        assigns = '\n'.join('    %s = seed + %d;' % (n, ord(n) - 96) for n in order)
        ls = [(n, '0') for n in 'abc']
        cases.append(_row('order', 'first_definition', ''.join(order), _program(ls, assigns + '\n' + _use_statements('abc'))))

    # Call-crossing liveness. Keep the same `a` live around a declared far call.
    for across in (False, True):
        call = 'extern void alloc_far(void);\n' if across else ''
        body = '    alloc_sink = a;\n'
        if across:
            body += '    alloc_far();\n'
        body += '    alloc_sink = b;\n    alloc_sink = a + b;'
        cases.append(_row('lifetime', 'far_call_live', across,
                          call + _program([('a', 'seed + 1'), ('b', 'seed + 2')], body)))

    # Parameters, copied parameters, and ordinary locals.
    for mode in ('parameters', 'local_copies', 'mixed'):
        params = 'int p, int q, int r'
        if mode == 'parameters':
            text = 'extern volatile int alloc_sink;\nint f(%s) { alloc_sink=p; alloc_sink=q; alloc_sink=r; return p+q+r; }\n' % params
        elif mode == 'local_copies':
            text = 'extern volatile int alloc_sink;\nint f(%s) { int a=p,b=q,c=r; alloc_sink=a; alloc_sink=b; alloc_sink=c; return a+b+c; }\n' % params
        else:
            text = 'extern volatile int alloc_sink;\nint f(int p, int q) { int a=p,b=q; alloc_sink=a; alloc_sink=b; return a+b; }\n'
        cases.append(_row('storage', 'parameter_form', mode, text))
    for copied in range(4):
        params = 'int p, int q, int r'
        decl = ','.join('%s=%s' % (chr(97+i), 'pqr'[i] if i < copied else '0') for i in range(3))
        lines = ['    int %s;' % decl]
        for i, n in enumerate('abc'):
            if i >= copied:
                lines.append('    %s = %s;' % (n, 'pqr'[i]))
        lines.extend('    alloc_sink = %s;' % n for n in 'abc')
        cases.append(_row('storage', 'parameter_copies', copied,
                          'extern volatile int alloc_sink;\nint f(%s) {\n%s\n return a+b+c; }\n' % (params, '\n'.join(lines))))

    # Pointer address generation vs arithmetic, shift counts, and widths.
    for kind in ('pointer', 'arithmetic'):
        body = ('    int *p = &values[a & 7];\n    alloc_sink = *p + b + c;' if kind == 'pointer'
                else '    alloc_sink = (a << 3) + b + c;')
        prefix = 'extern volatile int alloc_sink;\nint values[8];\n'
        cases.append(_row('operation', 'pointer_vs_arithmetic', kind,
                          prefix + 'int f(int seed) { int a=seed+1,b=seed+2,c=seed+3;\n%s\n return a+b+c; }\n' % body))
    for shift in range(1, 9):
        ls = _locals(3)
        body = '    alloc_sink = (a << %d) + b + c;' % shift
        cases.append(_row('operation', 'shift_count', shift, _program(ls, body)))
    for typ in ('char', 'unsigned char', 'int', 'unsigned int'):
        ls = [(n, 'seed + %d' % i) for i, n in enumerate('abc', 1)]
        decl = '\n'.join('    %s %s = seed + %d;' % (typ, n, i) for i, n in enumerate('abc', 1))
        body = '\n'.join('    alloc_sink = %s;' % n for n in 'abc')
        cases.append(_row('width', 'scalar_type', typ,
                          'extern volatile int alloc_sink;\nint f(int seed) {\n%s\n%s\n return a+b+c; }\n' % (decl, body)))

    # Address-taking and two-purpose local reuse.
    for taken in 'abc':
        addr = '    alloc_sink = (int)&%s;\n' % taken
        cases.append(_row('lifetime', 'address_taken', taken,
                          _program(_locals(3), addr + _use_statements('abc'))))
    for reuse in ('separate', 'merged'):
        if reuse == 'separate':
            ls = [('a','seed+1'),('b','seed+2'),('c','seed+3')]
            body = '    alloc_sink=a+b;\n    c=a+b;\n    alloc_sink=c;'
        else:
            ls = [('a','seed+1'),('b','seed+2')]
            body = '    alloc_sink=a+b;\n    a=a+b;\n    alloc_sink=a;'
        cases.append(_row('lifetime', 'reuse_purpose', reuse, _program(ls, body)))

    # CSE-able values and asymmetric branch use pressure.
    for temp in (False, True):
        expr = 'a * 8 + b'
        body = ('    int t = %s;\n    alloc_sink = t + c;\n    alloc_sink = t - c;' % expr if temp else
                '    alloc_sink = (%s) + c;\n    alloc_sink = (%s) - c;' % (expr, expr))
        cases.append(_row('expression', 'cse_temporary', temp, _program(_locals(3), body)))
    for a_uses in range(1, 9):
        arms = ['        alloc_sink = a + %d;' % k for k in range(a_uses)]
        body = '    if (seed & 1) {\n%s\n    } else {\n        alloc_sink = b;\n    }\n    alloc_sink = c;' % '\n'.join(arms)
        cases.append(_row('control', 'if_arm_uses', a_uses, _program(_locals(3), body)))

    return cases


def _controlled_source(cfg):
    """F2-style live, mutable values: unknown calls observe values each iteration."""
    count = cfg.get('word_locals', 3)
    names = list('abcde'[:count])
    decl_order = cfg.get('declaration_order', names)
    def_order = cfg.get('definition_order', names)
    use_order = cfg.get('use_order', names)
    width = cfg.get('width', 'int')
    params_mode = cfg.get('params_mode', 'locals')
    copy_set = set(cfg.get('copy_set', names if params_mode == 'locals' else []))
    value_name = {n: (n if n in copy_set else n + '0') for n in names}
    lines = ['extern void Touch(int);', 'extern void Gate(void);',
             'extern void Keep(int near *);', 'extern int values[16];',
             'extern volatile int alloc_i, alloc_j;',
             'int f(int n, int a0, int b0, int c0, int d0, int e0, int k) {']
    depth = cfg.get('loop_depth', 0) if cfg.get('loop_depth_for') else 0
    if cfg.get('definition_order'):
        for n in decl_order:
            if n in copy_set:
                lines.append('    %s %s;' % (width, n))
        for n in def_order:
            if n in copy_set:
                lines.append('    %s = %s0;' % (n, n))
    else:
        for n in decl_order:
            if n in copy_set:
                lines.append('    %s %s = %s0;' % (width, n, n))
    if cfg.get('address_taken') in names:
        lines.append('    Keep(&%s);' % cfg['address_taken'])
    lines.append('    while (n > 0) {')
    nested = cfg.get('loop_depth_for')
    depth = cfg.get('loop_depth', 0)
    if nested in use_order and depth:
        if depth == 1:
            lines.append('        for (alloc_i = 0; alloc_i < 2; ++alloc_i) {')
        else:
            lines.append('        for (alloc_i = 0; alloc_i < 2; ++alloc_i) {')
            lines.append('            for (alloc_j = 0; alloc_j < 2; ++alloc_j) {')
        indent = '            ' if depth == 1 else '                '
        for _ in range(cfg.get('uses', {}).get(nested, 1)):
            lines.append(indent + 'Touch(%s);' % value_name[nested])
        if depth == 1:
            lines.append('        }')
        else:
            lines.extend(['            }', '        }'])
    if cfg.get('if_uses'):
        a, b = names[:2]
        lines.append('        if (n & 1) {')
        lines.extend('            Touch(%s);' % value_name[a] for _ in range(cfg['if_uses']))
        lines.append('        } else {')
        lines.extend('            Touch(%s);' % value_name[b] for _ in range(cfg.get('else_uses', 1)))
        lines.append('        }')
    for n in use_order:
        if n == nested and depth:
            continue
        for _ in range(cfg.get('uses', {}).get(n, 1)):
            operand = value_name[n]
            if cfg.get('shift') is not None:
                operand = '(%s << %s)' % (operand, cfg['shift'])
            if cfg.get('dynamic_shift'):
                operand = '(%s << k)' % value_name[n]
            lines.append('        Touch(%s);' % operand)
    if cfg.get('call_live'):
        lines.append('        Gate();')
        # All values are consumed after this far call, so this changes the live
        # range while leaving the selected earlier uses fixed.
        for n in names:
            lines.append('        Touch(%s);' % value_name[n])
    if cfg.get('pointer'):
        ptr = names[0]
        lines.append('        Touch(values[%s & 15]);' % value_name[ptr])
    elif cfg.get('arithmetic'):
        x, y = names[:2]
        lines.append('        Touch((%s << 4) + %s);' % (value_name[x], value_name[y]))
    if cfg.get('cse'):
        x, y = names[:2]
        if cfg['cse'] == 'temporary':
            lines.append('        { int t = %s * 8 + %s; Touch(t); Touch(t); }' % (value_name[x], value_name[y]))
        else:
            lines.append('        Touch(%s * 8 + %s); Touch(%s * 8 + %s);' % (value_name[x], value_name[y], value_name[x], value_name[y]))
    if cfg.get('reuse'):
        x = names[0]
        if cfg['reuse'] == 'same_local':
            lines.append('        Touch(values[%s & 15]);' % value_name[x])
        else:
            lines.append('        { int index = %s & 15; Touch(values[index]); }' % value_name[x])
    for index, n in enumerate(names):
        name = value_name[n]
        src = chr(ord('a') + ((index + 1) % len(names))) + '0'
        lines.append('        %s += %s;' % (name, src))
    lines.extend(['        --n;', '    }'])
    if params_mode == 'locals':
        ret_names = [value_name[n] for n in names]
    elif params_mode == 'parameters':
        ret_names = [n+'0' for n in names]
    else:
        ret_names = [value_name[n] for n in names]
    lines.append('    return ' + ' + '.join(ret_names) + ';')
    lines.append('}')
    return '\n'.join(lines) + '\n'


def generate_cases():
    cases = []
    base = dict(word_locals=3, uses={n: 1 for n in 'abc'})

    def add(family, factor, value, **changes):
        cfg = dict(base)
        cfg.update(changes)
        case = _row(family, factor, value, _controlled_source(cfg))
        logical = list('abcde'[:cfg.get('word_locals', 3)])
        copies = set(cfg.get('copy_set', logical if cfg.get('params_mode', 'locals') == 'locals' else []))
        case['variables'] = [n if n in copies else n+'0' for n in logical]
        cases.append(case)

    for n in range(1, 6):
        add('competition', 'word_locals', n, word_locals=n,
            uses={x: 1 for x in 'abcde'[:n]})
    for variable in 'abc':
        for count in range(1, 161):
            uses = {n: 1 for n in 'abc'}; uses[variable] = count
            add('weight', 'static_uses:'+variable, count, uses=uses)
    for variable in 'abc':
        for depth in range(3):
            add('weight', 'loop_depth:'+variable, depth, loop_depth_for=variable,
                loop_depth=depth, uses={n: 1 for n in 'abc'})
    for order in itertools.permutations('abc'):
        add('order', 'declaration', ''.join(order), declaration_order=list(order))
        add('order', 'first_use', ''.join(order), use_order=list(order))
        add('order', 'first_definition', ''.join(order), definition_order=list(order))
    for across in (False, True):
        add('lifetime', 'far_call_live', across, call_live=across)
    for mode in ('parameters', 'locals', 'mixed'):
        copy_set = [] if mode == 'parameters' else list('abc') if mode == 'locals' else list('ac')
        add('storage', 'parameter_form', mode, params_mode=mode, copy_set=copy_set)
    for mask in range(8):
        copy_set = [n for i, n in enumerate('abc') if mask & (1 << i)]
        add('storage', 'parameter_copies', ''.join(copy_set) or 'none', copy_set=copy_set, params_mode='mixed')
    for form in ('pointer', 'arithmetic'):
        add('operation', 'pointer_vs_arithmetic', form, pointer=form == 'pointer', arithmetic=form == 'arithmetic')
    for shift in range(1, 9):
        add('operation', 'shift_count', shift, shift=shift)
    add('operation', 'shift_count', 'variable-CX', dynamic_shift=True)
    for typ in ('char', 'unsigned char', 'int', 'unsigned int'):
        add('width', 'scalar_type', typ, width=typ)
    for variable in 'abc':
        add('lifetime', 'address_taken', variable, address_taken=variable)
    for reuse in ('same_local', 'separate_temp'):
        add('lifetime', 'reuse_purpose', reuse, reuse=reuse)
    for form in ('inline', 'temporary'):
        add('expression', 'cse_temporary', form, cse=form)
    for uses in range(1, 9):
        add('control', 'if_arm_uses', uses, if_uses=uses, else_uses=1)
    return cases


def generate(path=None):
    path = path or SOURCE_DIR
    path.mkdir(parents=True, exist_ok=True)
    cases = generate_cases()
    manifest = []
    for i, case in enumerate(cases):
        filename = '%04d_%s_%s.c' % (i, case['family'], case['factor'].replace(':','_'))
        dest = path / filename
        dest.write_text(case['source'], encoding='ascii')
        manifest.append(dict(id='A%04d' % i, source=relative(dest), family=case['family'],
                             factor=case['factor'], value=case['value'], variables=case.get('variables', []),
                             control=case['control']))
    write_json(OUT / 'manifest.json', manifest)
    return manifest


def _home_map(obj, function='f'):
    segs = frame_map.segments(obj.read_bytes())
    homes, regs = frame_map.codeview_locals(segs.get('$$SYMBOLS', b''), function)
    return homes, regs


def source_features(text, function='f'):
    """Extract transparent source-side features for simple scalar locals."""
    match = re.search(r'\b' + re.escape(function) + r'\s*\(([^)]*)\)\s*\{', text)
    if not match:
        return {}
    params = match.group(1)
    open_brace = match.end() - 1
    depth, close_brace = 0, None
    for index in range(open_brace, len(text)):
        if text[index] == '{':
            depth += 1
        elif text[index] == '}':
            depth -= 1
            if depth == 0:
                close_brace = index
                break
    if close_brace is None:
        return {}
    body = text[open_brace+1:close_brace]
    names = {}
    # Explicit declaration matcher, followed by identifier-level use counts.
    for decl in re.finditer(r'\b(?:(?:unsigned|signed)\s+)?(?:char|int)\s+([^;]+);', body):
        for piece in decl.group(1).split(','):
            m = re.match(r'\s*\*?\s*(\w+)\s*(?:\[[^]]*\])?\s*(?:=\s*(.*)|$)', piece)
            if m:
                names[m.group(1)] = dict(kind='local', decl_line=body.count('\n', 0, decl.start()) + 1,
                                         initializer=(m.group(2) or '').strip())
    for name in re.findall(r'\b(?:(?:unsigned|signed)\s+)?(?:char|int)\s+(\w+)\b', params):
        names[name] = dict(kind='parameter', decl_line=0, initializer='')
    # Mark loop-body lines by brace depth. These templates use braced counted
    # loops; the stack records loop opens separately from ordinary blocks.
    lines = body.splitlines()
    loop_stack = []
    depth_by_line = {}
    brace_depth = 0
    for line_no, line in enumerate(lines, 1):
        opens_loop = bool(re.search(r'\b(?:for|while)\s*\(', line))
        depth_by_line[line_no] = len(loop_stack) + int(opens_loop)
        opens = line.count('{')
        closes = line.count('}')
        if opens and opens_loop:
            loop_stack.append(brace_depth + opens)
        elif opens and loop_stack and brace_depth + opens >= loop_stack[-1]:
            # Nested ordinary block remains within the active loop.
            pass
        brace_depth += opens - closes
        while loop_stack and brace_depth < loop_stack[-1]:
            loop_stack.pop()
    result = {}
    for name, info in names.items():
        refs, loop_refs, first_ref, first_def, last_ref = 0, 0, None, None, None
        addressed = bool(re.search(r'&\s*' + re.escape(name) + r'\b', body))
        max_depth = 0
        for line_no, line in enumerate(lines, 1):
            if name in line and re.search(r'\b' + re.escape(name) + r'\b', line):
                count = len(re.findall(r'\b' + re.escape(name) + r'\b', line))
                is_decl = line_no == info['decl_line']
                if is_decl:
                    count = max(0, count - 1)
                # A pure write is a definition, not a read. Compound updates
                # are reads; ordinary uses and indexed/address uses are reads.
                write_only = bool(re.search(r'\b' + re.escape(name) + r'\s*=(?!=)', line)) and not bool(re.search(r'\b' + re.escape(name) + r'\s*(?:\+=|-=|\+\+|--)', line))
                if write_only:
                    count = max(0, count - 1)
                    if first_def is None:
                        first_def = line_no
                if count:
                    refs += count
                    if depth_by_line.get(line_no, 0):
                        loop_refs += count
                        max_depth = max(max_depth, depth_by_line[line_no])
                    if first_ref is None:
                        first_ref = line_no
                    last_ref = line_no
        result[name] = dict(kind=info['kind'], lexical_reads=refs, loop_reads=loop_refs,
                            loop_weight_3x=refs + 2*loop_refs, max_loop_depth=max_depth,
                            first_reference=first_ref, first_definition=first_def,
                            last_reference=last_ref, address_taken=addressed,
                            declaration_line=info['decl_line'])
    return result


_WORD_REGS = {'ax','bx','cx','dx','si','di'}


def _value_expr(expr, env):
    """Small symbolic domain for the affine values used by the generated grid."""
    expr = expr.strip().strip('()')
    expr = re.sub(r'\b(?:unsigned|signed|int|char)\b', '', expr).strip()
    if expr in env:
        return env[expr]
    if re.fullmatch(r'\d+', expr):
        return ('const', int(expr))
    m = re.fullmatch(r'(\w+)\s*([+-])\s*(\d+)', expr)
    if m and m.group(1) in env:
        base = env[m.group(1)]
        if base and base[0] in ('param', 'const'):
            amount = int(m.group(3)) * (1 if m.group(2) == '+' else -1)
            return (base[0], base[1], base[2] + amount) if base[0] == 'param' else ('const', base[1] + amount)
    m = re.fullmatch(r'(\d+)\s*\+\s*(\w+)', expr)
    if m and m.group(2) in env:
        base = env[m.group(2)]
        if base and base[0] == 'param':
            return ('param', base[1], base[2] + int(m.group(1)))
    return None


def symbolic_allocations(source, instructions, named_homes, named_registers, observed_homes):
    """Map generated scalar values to the registers that actually carry them.

    This is a deliberately narrow, transparent value-flow parser, not an x86
    emulator. It handles the compiler idioms emitted by the affine control grid
    (`mov`, `lea`, `add`, `sub`, `inc`, `dec`, shifts and `xchg`) and reports
    unresolved values explicitly.
    """
    sig = re.search(r'\bint\s+f\s*\(([^)]*)\)\s*\{(.*)\}', source, re.S)
    if not sig:
        return {}
    params, body = sig.groups()
    param_names = re.findall(r'\b(?:(?:unsigned|signed)\s+)?(?:char|int)\s+(\w+)\b', params)
    env = {name: ('param', name, 0) for name in param_names}
    param_offsets = {name: 6 + 2 * i for i, name in enumerate(param_names)}
    local_initializers = {}
    for decl in re.finditer(r'\b(?:(?:unsigned|signed)\s+)?(?:char|int)\s+([^;]+);', body):
        for piece in decl.group(1).split(','):
            m = re.match(r'\s*\*?\s*(\w+)\s*(?:\[[^]]*\])?\s*(?:=\s*(.*)|$)', piece)
            if m:
                name, initializer = m.group(1), (m.group(2) or '').strip()
                value = _value_expr(initializer, env) if initializer else None
                local_initializers[name] = value
                if value is not None:
                    env[name] = value
    named_values = dict(env)
    named_values.update(local_initializers)
    values = defaultdict(list)
    for name, value in named_values.items():
        if value is not None:
            values[value].append(name)
    flow_regs = defaultdict(list)
    cv_regs = defaultdict(list)
    homes_used = {int(k): v for k, v in observed_homes.items()}
    for register in named_registers:
        if register['name'] in local_initializers or register['name'] in param_names:
            cv_regs[register['name']].append(register['register'])
    homes_by_offset = defaultdict(list)
    for h in named_homes:
        if h['offset'] in homes_used and h['name'] in local_initializers:
            homes_by_offset[h['offset']].append(h['name'])
    state = {}
    for line in instructions:
        m = re.match(r'^[0-9a-f]+\s+(\w+)\s*(.*)$', line)
        if not m:
            continue
        op, operand_text = m.groups()
        operands = [x.strip() for x in operand_text.split(',')]
        if not operands:
            continue
        dest = operands[0].lower()
        src = operands[1].lower() if len(operands) > 1 else ''
        # Every register source that carries a named initial value is direct
        # evidence of that value's current register allocation.
        for reg in re.findall(r'\b(ax|bx|cx|dx|si|di)\b', operand_text.lower()):
            if reg in state:
                for name in values.get(state[reg], []):
                    if reg not in flow_regs[name]:
                        flow_regs[name].append(reg)
        if dest not in _WORD_REGS:
            continue
        new_value = None
        if op == 'mov':
            rm = re.search(r'\[bp\s*\+\s*(0x[0-9a-f]+|\d+)\]', src)
            if rm:
                offset = int(rm.group(1), 0)
                pname = next((n for n, off in param_offsets.items() if off == offset), None)
                new_value = env.get(pname) if pname else None
            elif src in state:
                new_value = state[src]
            elif re.fullmatch(r'(?:0x[0-9a-f]+|\d+)', src):
                new_value = ('const', int(src, 0))
        elif op == 'lea':
            br = re.search(r'\[(ax|bx|cx|dx|si|di)(?:\s*\+\s*(\d+))?\]', src)
            if br and state.get(br.group(1)) is not None:
                base = state[br.group(1)]
                if base[0] == 'param':
                    new_value = ('param', base[1], base[2] + int(br.group(2) or 0))
                elif base[0] == 'const':
                    new_value = ('const', base[1] + int(br.group(2) or 0))
        elif op in ('add', 'sub'):
            left = state.get(dest)
            right = state.get(src)
            if right is None and re.fullmatch(r'(?:0x[0-9a-f]+|\d+)', src):
                right = ('const', int(src, 0))
            if left and right and left[0] == 'param' and right[0] == 'const':
                amount = right[1] if op == 'add' else -right[1]
                new_value = ('param', left[1], left[2] + amount)
            elif left and right and left[0] == 'const' and right[0] == 'param' and op == 'add':
                new_value = ('param', right[1], right[2] + left[1])
        elif op in ('inc', 'dec'):
            old = state.get(dest)
            if old and old[0] == 'param':
                new_value = ('param', old[1], old[2] + (1 if op == 'inc' else -1))
        elif op in ('shl', 'sal'):
            old = state.get(dest)
            if old and old[0] == 'const':
                n = int(src, 0) if src else 1
                new_value = ('const', old[1] << n)
        elif op == 'xchg' and src in _WORD_REGS:
            state[dest], state[src] = state.get(src), state.get(dest)
            continue
        state[dest] = new_value
    result = {}
    for name, value in named_values.items():
        if cv_regs.get(name):
            placement, status, basis = cv_regs[name], 'MAPPED', 'CodeView register record'
        else:
            matching_offsets = [offset for offset, group in homes_by_offset.items() if name in group]
            if matching_offsets:
                offset = matching_offsets[0]
                peers = homes_by_offset[offset]
                if len(peers) == 1:
                    placement, status, basis = ['bp%d' % offset], 'MAPPED', 'unique CodeView home touched by code'
                else:
                    placement, status, basis = ['ambiguous-bp%d' % offset], 'AMBIGUOUS_HOME', 'overlapping CodeView names at one touched offset: ' + ','.join(peers)
            elif flow_regs.get(name):
                placement, status, basis = flow_regs[name], 'VALUE_FLOW', 'symbolic register operands'
            else:
                placement, status, basis = [], 'UNRESOLVED', None
        result[name] = dict(initializer=value, placement=placement, status=status, basis=basis)
    return result


def run(profiles=PROFILES, limit=None, chunk=128):
    manifest = read_json(OUT / 'manifest.json') if (OUT / 'manifest.json').exists() else generate()
    if limit is not None:
        manifest = manifest[:limit]
    jobs = []
    rows = []
    for item in manifest:
        for profile in profiles:
            flags = profile_flags(profile, '_TEXT')
            # /Zi records source-name to register/home assignments. It belongs
            # before /NT so the segment switch remains the final compiler flag.
            zi_flags = flags[:-1] + ['/Zi', flags[-1]]
            jobs.append(dict(source=item['source'], flags=flags))
            jobs.append(dict(source=item['source'], flags=zi_flags))
            rows.append((item, profile, flags))
    # Chunking bounds service requests and leaves resumable observations.
    if OBSERVATIONS.exists():
        OBSERVATIONS.unlink()
    compiled_rows = []
    for start in range(0, len(jobs), chunk):
        compiled, cache = compile_cached(jobs[start:start+chunk], 'msc700')
        compiled_rows.extend(compiled)
        print('compiled %d/%d (cache hits %d, misses %d)' %
              (min(start+chunk, len(jobs)), len(jobs), cache['hits'], cache['misses']), file=sys.stderr)
    with OBSERVATIONS.open('w', encoding='utf-8', newline='\n') as out:
        for i, (item, profile, plain_flags) in enumerate(rows):
            obj, receipt = compiled_rows[i*2]
            debug_obj, debug_receipt = compiled_rows[i*2+1]
            if obj is None or receipt.get('exit_code'):
                observation = dict(id=item['id'], family=item['family'], factor=item['factor'], value=item['value'], variables=item.get('variables', []),
                                   profile=profile, status='COMPILE_FAILED', error=receipt.get('stdout','')[-500:])
            elif debug_obj is None or debug_receipt.get('exit_code'):
                observation = dict(id=item['id'], family=item['family'], factor=item['factor'], value=item['value'], variables=item.get('variables', []),
                                   profile=profile, status='CODEVIEW_COMPILE_FAILED', error=debug_receipt.get('stdout','')[-500:])
            else:
                metric = measure(obj, 'f')
                homes, regs = _home_map(debug_obj)
                debug_segments = frame_map.segments(debug_obj.read_bytes())
                plain_module = omf.parse(obj.read_bytes())
                plain_public = next(p for p in plain_module['publics'] if p['name'].lstrip('_') == 'f')
                plain_code = bytes.fromhex(plain_module['segments'][plain_public['segment']-1]['data_hex'])
                debug_code = next((data for name, data in debug_segments.items()
                                   if not name.startswith(chr(36)*2) and data == plain_code), None)
                observation = dict(id=item['id'], family=item['family'], factor=item['factor'], value=item['value'], variables=item.get('variables', []),
                                   profile=profile, status='OK', flags=plain_flags, frame=metric['frame'],
                                   homes=metric['homes'], registers=metric['registers'], saves=metric['saves'],
                                   named_homes=homes, named_registers=regs,
                                   byte_sha256=metric['sha256'], byte_size=metric['size'], instructions=metric['instructions'],
                                   codeview_identical=(plain_code == debug_code), debug_code_sha256=__import__('hashlib').sha256(debug_code or b'').hexdigest(),
                                   features=source_features((ROOT / item['source']).read_text(encoding='ascii')),
                                   allocations=symbolic_allocations((ROOT / item['source']).read_text(encoding='ascii'),
                                                                    metric['instructions'], homes, regs, metric['homes']))
            out.write(json.dumps(observation, sort_keys=True) + '\n')
    return len(rows)


def _rank_model(observations):
    """Fit small use-rank rules on controlled mutable-word competition cases."""
    ok = [x for x in observations if x.get('status') == 'OK']
    study = [x for x in ok if x['family'] in ('competition', 'weight') and x.get('variables')]
    tie_fields = ('first_reference', 'first_definition', 'declaration_line', 'last_reference')
    candidates = []
    for multiplier in (0, 1, 2, 3, 4, 6, 8, 12):
        for tie in tie_fields:
            for tie_direction in ('ascending', 'descending'):
                for role_order in ('SI_then_DI', 'DI_then_SI'):
                    correct = total = 0
                    errors = []
                    for row in study:
                        feats, allocs = row.get('features', {}), row.get('allocations', {})
                        names = [n for n in row['variables'] if n in feats and n in allocs]
                        if len(names) != len(row['variables']):
                            continue
                        def sortkey(name):
                            f = feats[name]
                            score = f.get('lexical_reads', 0) + multiplier * f.get('loop_reads', 0)
                            tieval = f.get(tie)
                            tieval = (10**9 if tieval is None else tieval)
                            if tie_direction == 'descending':
                                tieval = -tieval
                            return (-score, tieval, name)
                        ranked = sorted(names, key=sortkey)
                        predicted = {n: 'home' for n in names}
                        if ranked:
                            predicted[ranked[0]] = 'si' if role_order == 'SI_then_DI' else 'di'
                        if len(ranked) > 1:
                            predicted[ranked[1]] = 'di' if role_order == 'SI_then_DI' else 'si'
                        for name in names:
                            actual = allocation_class(allocs[name])
                            if actual is None:
                                continue
                            total += 1
                            if predicted[name] == actual:
                                correct += 1
                            else:
                                errors.append(dict(id=row['id'], profile=row['profile'], factor=row['factor'],
                                                   value=row['value'], variable=name, expected=predicted[name], actual=actual,
                                                   feature=feats[name]))
                    candidates.append(dict(correct=correct, total=total, errors=errors,
                                           rule=dict(score='lexical_reads + %d * loop_reads' % multiplier,
                                                     tie=tie+' '+tie_direction, role_order=role_order)))
    best = max(candidates, key=lambda c: (c['correct'] / max(c['total'], 1), -int(c['rule']['score'].split('*')[0].split('+')[1].strip()), c['rule']['tie'], c['rule']['role_order']))
    per_profile = {}
    counterexamples = []
    for profile in PROFILES:
        rows = [x for x in study if x['profile'] == profile]
        matched = [e for e in best['errors'] if e['profile'] == profile]
        total = sum(1 for row in rows for name in row.get('variables', [])
                    if name in row.get('allocations', {}) and allocation_class(row['allocations'][name]) is not None)
        per_profile[profile] = dict(correct=total-len(matched), total=total,
                                    accuracy=round((total-len(matched))/max(total,1), 4), counterexamples=len(matched))
    counterexamples = best['errors']
    home_candidates = []
    for score_multiplier in (0, 1, 2, 3, 4, 6, 8, 12):
        for tie in tie_fields:
            for tie_direction in ('ascending', 'descending'):
                for slot_direction in ('deepest_first', 'nearest_first'):
                    correct = total = 0
                    errors = []
                    for row in study:
                        feats, allocs = row.get('features', {}), row.get('allocations', {})
                        home_names = []
                        actual_offsets = {}
                        for name in row['variables']:
                            alloc = allocs.get(name, {})
                            place = alloc.get('placement', [])
                            if allocation_class(alloc) == 'home' and len(place) == 1 and place[0].startswith('bp-'):
                                home_names.append(name)
                                actual_offsets[name] = int(place[0][2:])
                        if not home_names:
                            continue
                        def homekey(name):
                            f = feats[name]
                            score = f.get('lexical_reads', 0) + score_multiplier * f.get('loop_reads', 0)
                            t = f.get(tie)
                            t = (10**9 if t is None else t) * (1 if tie_direction == 'ascending' else -1)
                            return (-score, t, name)
                        ordered = sorted(home_names, key=homekey)
                        if slot_direction == 'nearest_first':
                            predicted_offsets = {name: -2*(i+1) for i, name in enumerate(ordered)}
                        else:
                            predicted_offsets = {name: -2*(len(ordered)-i) for i, name in enumerate(ordered)}
                        for name in home_names:
                            total += 1
                            if actual_offsets[name] == predicted_offsets[name]:
                                correct += 1
                            else:
                                errors.append(dict(id=row['id'], profile=row['profile'], factor=row['factor'],
                                                   value=row['value'], variable=name, expected='bp%d' % predicted_offsets[name],
                                                   actual='bp%d' % actual_offsets[name], feature=feats[name]))
                    home_candidates.append(dict(correct=correct, total=total, errors=errors,
                                               rule=dict(score='lexical_reads + %d * loop_reads' % score_multiplier,
                                                         tie=tie+' '+tie_direction, order=slot_direction)))
    best_home = max(home_candidates, key=lambda c: (c['correct']/max(c['total'],1),
                                                    -int(c['rule']['score'].split('*')[0].split('+')[1].strip()),
                                                    c['rule']['tie'], c['rule']['order']))
    return dict(observations=len(observations), successful=len(ok), compile_failures=len(observations)-len(ok),
                profiles=dict(Counter(x['profile'] for x in ok)),
                frame_sizes=dict(Counter(str(x['frame']) for x in ok)),
                codeview_code_identity=sum(bool(x.get('codeview_identical')) for x in ok),
                named_register_local_observations=sum(len(x.get('named_registers', [])) for x in ok),
                fit_scope=dict(name='mutable word locals in candidate-count, static-use and loop-depth families',
                               cases=len(study), values=sum(len(x.get('variables', [])) for x in study)),
                fitted_rule=best['rule'], correct=best['correct'], total=best['total'],
                accuracy=round(best['correct']/max(best['total'], 1), 4), per_profile=per_profile,
                counterexamples=len(counterexamples), counterexample_rows=counterexamples,
                home_order_rule=best_home['rule'], home_order_correct=best_home['correct'],
                home_order_total=best_home['total'],
                home_order_accuracy=round(best_home['correct']/max(best_home['total'],1), 4),
                home_order_counterexamples=len(best_home['errors']),
                home_order_counterexample_rows=best_home['errors'],
                factor_coverage=dict(Counter('%s:%s' % (x['family'], x['factor']) for x in ok)),
                limitation='Prediction is restricted to SI/DI/home class for the controlled mutable-word competition cases. Home byte offsets and the other requested factors are separately reported and are not silently claimed by this rule.')


def allocation_class(placement):
    places = placement.get('placement', [])
    if placement.get('status') == 'UNRESOLVED':
        return None
    for reg in ('si', 'di'):
        if reg in places:
            return reg
    if any(p.startswith('bp') or p.startswith('ambiguous-bp') for p in places):
        return 'home'
    if places:
        return 'other'
    return None


def summarize():
    if not OBSERVATIONS.exists():
        raise FormatError('no observations; run alloc_lab.py run')
    observations = read_observations(OBSERVATIONS)
    report = _rank_model(observations)
    counterexamples = report.pop('counterexample_rows')
    home_errors = report.pop('home_order_counterexample_rows')
    with (OUT / 'counterexamples.jsonl').open('w', encoding='utf-8', newline='\n') as stream:
        for row in counterexamples:
            stream.write(json.dumps(row, sort_keys=True) + '\n')
    with (OUT / 'home_counterexamples.jsonl').open('w', encoding='utf-8', newline='\n') as stream:
        for row in home_errors:
            stream.write(json.dumps(row, sort_keys=True) + '\n')
    report['counterexample_file'] = 'build/alloc_lab/counterexamples.jsonl'
    report['home_order_counterexample_file'] = 'build/alloc_lab/home_counterexamples.jsonl'
    write_json(REPORT, report)
    print(json.dumps(report, indent=2))


def read_observations(path=OBSERVATIONS):
    """Read JSONL observations strictly; reject truncated or malformed rows."""
    rows = []
    for number, line in enumerate(path.read_text(encoding='utf-8').splitlines(), 1):
        try:
            row = json.loads(line)
        except json.JSONDecodeError as exc:
            raise FormatError('invalid observation JSON at line %d: %s' % (number, exc))
        required = {'id', 'family', 'factor', 'value', 'profile', 'status'}
        missing = required - row.keys()
        if missing:
            raise FormatError('observation line %d missing fields: %s' % (number, ', '.join(sorted(missing))))
        if row['status'] == 'OK' and not {'frame', 'homes', 'registers', 'named_homes', 'named_registers', 'byte_sha256'} <= row.keys():
            raise FormatError('successful observation line %d lacks allocation fields' % number)
        rows.append(row)
    return rows


def main():
    p = argparse.ArgumentParser(description=__doc__)
    sub = p.add_subparsers(dest='command', required=True)
    sub.add_parser('generate')
    r = sub.add_parser('run'); r.add_argument('--profiles', default=','.join(PROFILES)); r.add_argument('--limit', type=int); r.add_argument('--chunk', type=int, default=128)
    sub.add_parser('summarize')
    args = p.parse_args()
    if args.command == 'generate':
        rows = generate(); print(json.dumps(dict(cases=len(rows), profiles=PROFILES, manifest=relative(OUT/'manifest.json')), indent=2))
    elif args.command == 'run':
        profiles = tuple(args.profiles.split(','))
        if any(p not in PROFILES for p in profiles):
            raise FormatError('profiles must be selected from ' + ', '.join(PROFILES))
        count = run(profiles, args.limit, args.chunk); print(json.dumps(dict(observations=count, path=relative(OBSERVATIONS))))
    else:
        summarize()


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
