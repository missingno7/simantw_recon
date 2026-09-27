"""Reusable MSC 7.00 code-generation probes: vary one source property at a time and see what changes.

    python tools/probe.py SPEC.json [--record FACT-ID] [--target]

SPEC (JSON):
    {"name": "e16-cast-cse",
     "symbol": "_MowerFall",          # a real function: its ASSIGNED profile and segment are enforced
       or "profile": "baseline",      # a toy probe: any catalogued profile name (never free-form flags)
     "segment": "_TEXT",              # toy probes only (default _TEXT)
     "function": "f",                 # C name of the function to measure (default: symbol without '_')
     "source": "path/to/base.c"  or  "text": "... {{AXIS}} ...",
     "axes": {"AXIS": {"label": "replacement text", ...}, ...},
     "mode": "product" | "one-at-a-time"}   # default one-at-a-time: first choice of every axis is the baseline

Every variant is compiled with the pinned MSC 7.00 through the compiler service/cache. For the measured
function the report gives: its bytes and SHA-256, instructions, ENTER size, [bp-N] homes (offset and
width), registers read or written, SI/DI saves, fixups (location and target), and relative to the
baseline variant: whether the object is identical, the instruction diff and the changed properties.
Variants that produce the same function bytes are grouped. With "symbol" and --target, each variant
is also compared with the original by the strict member matcher (tools/search.py); the result is a
diagnostic, never a promotion.

--record FACT-ID stores the spec and the report under evidence/codegen-facts/FACT-ID/ as the
reproducible evidence for docs/msc7-codegen.md. A spec for a real symbol whose "profile" differs from
the symbol's assigned profile is rejected: probes must be run with the profile the function is
compiled with.
"""
import argparse
import difflib
import hashlib
import itertools
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, read_json, relative, write_json
import compiler_profiles
import omf
from analysis import decoder
from codegen_cache import compile_cached

OUT = ROOT / 'build/probes'
FACTS = ROOT / 'evidence/codegen-facts'
REGS = ('ax', 'bx', 'cx', 'dx', 'si', 'di', 'al', 'ah', 'bl', 'bh', 'cl', 'ch', 'dl', 'dh', 'es', 'ds')
BP_HOME = re.compile(r'(byte|word|dword)? ?ptr (?:ss:)?\[bp - (0x[0-9a-f]+|\d+)\]')
WIDTH = {'byte': 1, 'word': 2, 'dword': 4, None: 2}
MAX_VARIANTS = 256


def resolve_flags(spec):
    """(profile name, flags) for the spec; a real symbol always uses its assigned profile."""
    if spec.get('symbol'):
        from promote import function_flags
        profile, flags = function_flags(spec['symbol'])
        if spec.get('profile') and spec['profile'] != profile['name']:
            raise FormatError('%s is compiled with profile %s, not %s: probes must use the assigned profile'
                              % (spec['symbol'], profile['name'], spec['profile']))
        return profile['name'], list(flags)
    if not spec.get('profile'):
        raise FormatError('a toy probe needs "profile" (a catalogued profile name) or a real "symbol"')
    return spec['profile'], compiler_profiles.profile_flags(spec['profile'], spec.get('segment', '_TEXT'))


def variants(spec):
    """[(label dict, source text)] with the baseline (first choice of every axis) first."""
    text = spec.get('text')
    if text is None:
        text = (ROOT / spec['source']).read_text(encoding='utf-8', errors='replace')
    axes = spec.get('axes') or {}
    for axis in axes:
        if '{{%s}}' % axis not in text:
            raise FormatError('axis %s has no {{%s}} placeholder in the source' % (axis, axis))
    names = list(axes)
    choices = [list(axes[a].items()) for a in names]
    combos = []
    if spec.get('mode', 'one-at-a-time') == 'product':
        combos = list(itertools.product(*choices)) if names else [()]
    else:
        base = tuple(c[0] for c in choices)
        combos = [base]
        for i, options in enumerate(choices):
            for option in options[1:]:
                combos.append(base[:i] + (option,) + base[i + 1:])
    if len(combos) > MAX_VARIANTS:
        raise FormatError('%d variants exceed the limit of %d; use one-at-a-time mode or fewer axes' % (len(combos), MAX_VARIANTS))
    result = []
    for combo in combos:
        label, body = {}, text
        for axis, (key, value) in zip(names, combo):
            label[axis] = key
            body = body.replace('{{%s}}' % axis, value)
        result.append((label, body))
    return result


def measure(obj_path, function):
    """Bytes, instructions and frame/register/fixup facts of one function in an OMF object."""
    module = omf.parse(Path(obj_path).read_bytes())
    public = next((p for p in module['publics'] if p['name'] in ('_' + function, function)), None)
    if public is None:
        raise FormatError('function %s not found in the object' % function)
    seg = module['segments'][public['segment'] - 1]
    code = bytes.fromhex(seg['data_hex'])
    start = public['offset']
    later = [p['offset'] for p in module['publics'] if p['segment'] == public['segment'] and p['offset'] > start]
    body = code[start:min(later) if later else len(code)]
    ins = [(i.address, i.mnemonic, i.op_str, i.size) for i in decoder().disasm(body, 0)]
    fixups = [dict(offset=f['offset'] - start, width=f['width'], target=f['target'].get('name') or f['target'].get('kind'),
                   kind=f['location_type'], self_relative=f['self_relative'])
              for f in module['fixups'] if f['segment'] == public['segment'] and start <= f['offset'] < start + len(body)]
    masked = bytearray(body)
    for f in fixups:
        for q in range(f['offset'], min(len(body), f['offset'] + f['width'])):
            masked[q] = 0
    covered = set(q for f in fixups for q in range(f['offset'], f['offset'] + f['width']))
    masked_ins = []
    for a, mnem, ops, size in ins:
        text = ops
        if any(q in covered for q in range(a, a + size)):
            text = re.sub(r'0x[0-9a-f]+|\d+', 'FIX', ops)
        masked_ins.append('%s %s' % (mnem, text))
    homes, regs = {}, set()
    for _, mnem, ops, _ in ins:
        for m in BP_HOME.finditer(ops):
            n = int(m.group(2), 0)
            homes[n] = max(homes.get(n, 0), WIDTH[m.group(1)])
        for r in re.findall(r'\b(%s)\b' % '|'.join(REGS), ops):
            regs.add(r)
    enter = next((int(o.split(',')[0], 0) for _, m, o, _ in ins[:2] if m == 'enter'), None)
    if enter is None:
        subs = [int(o.split(',')[1], 0) for _, m, o, _ in ins[:4] if m == 'sub' and o.startswith('sp,')]
        enter = subs[0] if subs else 0
    saves = [o for _, m, o, _ in ins[:4] if m == 'push' and o in ('si', 'di')]
    return dict(bytes=body.hex(), sha256=hashlib.sha256(body).hexdigest(), masked_sha256=hashlib.sha256(bytes(masked)).hexdigest(),
                masked_instructions=masked_ins, size=len(body), frame=enter,
                homes={'-%d' % k: v for k, v in sorted(homes.items())}, registers=sorted(regs), saves=saves,
                fixups=fixups, instructions=['%04x %s %s' % (a, m, o) for a, m, o, _ in ins])


def normalize(line):
    return line.split(' ', 1)[1] if ' ' in line else line


def compare(base, other):
    changed = [k for k in ('size', 'frame', 'homes', 'registers', 'saves') if base[k] != other[k]]
    if [(f['target'], f['kind']) for f in base['fixups']] != [(f['target'], f['kind']) for f in other['fixups']]:
        changed.append('fixups')
    diff = [d for d in difflib.unified_diff(base['masked_instructions'], other['masked_instructions'],
                                            'baseline', 'variant', n=1, lineterm='') if not d.startswith(('---', '+++'))]
    same_code = base['masked_sha256'] == other['masked_sha256'] and not [c for c in changed if c != 'fixups']
    return dict(identical=base['sha256'] == other['sha256'], same_code_modulo_fixups=same_code, changed=changed, diff=diff[:80])


def target_result(symbol, path):
    p = subprocess.run([sys.executable, str(ROOT / 'tools/search.py'), symbol, str(path)], cwd=ROOT, capture_output=True, text=True)
    try:
        report = json.loads(p.stdout[p.stdout.index('{'):])
        rows = read_json(ROOT / report['report'])['results']
        comparison = rows[0]['comparison']
        diag = comparison.get('diagnostic') or {}
        return dict(result=comparison.get('result'), opcodes='%s/%s' % (diag.get('opcode_matches'), diag.get('opcode_total')),
                    bytes='%s/%s' % (comparison.get('literal_equal'), comparison.get('literal_compared')))
    except (ValueError, KeyError, IndexError):
        return dict(result='ERROR', detail=(p.stderr or p.stdout)[-300:])


def run(spec, record=None, with_target=False):
    profile, flags = resolve_flags(spec)
    function = spec.get('function') or (spec['symbol'].lstrip('_') if spec.get('symbol') else 'f')
    name = spec.get('name') or 'probe'
    work = OUT / name
    work.mkdir(parents=True, exist_ok=True)
    vs = variants(spec)
    jobs = []
    for i, (label, text) in enumerate(vs):
        path = work / ('v%03d.c' % i)
        path.write_text(text, encoding='latin-1', errors='replace')
        jobs.append(dict(source=relative(path), flags=list(flags)))
    compiled, _ = compile_cached(jobs, 'msc700')
    rows, base = [], None
    groups = {}
    for i, ((label, _), (obj, receipt)) in enumerate(zip(vs, compiled)):
        row = dict(variant='v%03d' % i, label=label)
        if obj is None or receipt.get('exit_code'):
            row['compile'] = 'FAILED'
            row['log'] = (receipt.get('stdout') or '')[-400:]
            rows.append(row)
            continue
        m = measure(obj, function)
        row.update(size=m['size'], frame=m['frame'], homes=m['homes'], registers=m['registers'], saves=m['saves'],
                   sha256=m['sha256'], fixups=m['fixups'])
        if base is None:
            base = m
            row['baseline'] = True
            row['instructions'] = m['instructions']
        else:
            row['versus_baseline'] = compare(base, m)
        groups.setdefault(m['masked_sha256'], []).append(row['variant'])
        if with_target and spec.get('symbol'):
            row['target'] = target_result(spec['symbol'], work / ('v%03d.c' % i))
        rows.append(row)
    report = dict(name=name, profile=profile, flags=flags, function=function, symbol=spec.get('symbol'), mode=spec.get('mode', 'one-at-a-time'),
                  variants=len(rows), distinct_outputs=len(groups), same_output=[v for v in groups.values() if len(v) > 1], rows=rows,
                  note='distinct outputs and same_output compare code with fixup fields masked')
    write_json(work / 'report.json', report)
    if record:
        dest = FACTS / record
        dest.mkdir(parents=True, exist_ok=True)
        write_json(dest / (name + '.spec.json'), spec)
        write_json(dest / (name + '.report.json'), report)
        report['recorded'] = relative(dest)
    return report


def summary(report):
    lines = ['%s  profile=%s  flags=%s  variants=%d  distinct code (fixups masked)=%d' % (report['name'], report['profile'], ' '.join(report['flags']),
                                                                         report['variants'], report['distinct_outputs'])]
    for r in report['rows']:
        if r.get('compile') == 'FAILED':
            lines.append('  %s %s COMPILE FAILED' % (r['variant'], r['label']))
            continue
        v = r.get('versus_baseline')
        state = 'BASELINE' if r.get('baseline') else ('same object' if v['identical'] else
                 'same code (fixup fields differ)' if v['same_code_modulo_fixups'] else 'changed: ' + ','.join(v['changed'] or ['code']))
        target = (' target %s %s' % (r['target'].get('result'), r['target'].get('opcodes'))) if r.get('target') else ''
        lines.append('  %s %-40s size %4d frame %3d saves %-8s %s%s' % (r['variant'], json.dumps(r['label'])[:40], r['size'], r['frame'],
                                                                     ','.join(r['saves']) or '-', state, target))
    return '\n'.join(lines)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('spec')
    ap.add_argument('--record', metavar='FACT-ID', help='store spec and report as evidence under evidence/codegen-facts/FACT-ID/')
    ap.add_argument('--target', action='store_true', help='also compare each variant with the original (real symbols only)')
    ap.add_argument('--json', action='store_true', help='print the full JSON report instead of the summary')
    args = ap.parse_args()
    report = run(read_json(Path(args.spec)), args.record, args.target)
    print(json.dumps(report, indent=1) if args.json else summary(report))
    print('report: ' + relative(OUT / report['name'] / 'report.json'))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
