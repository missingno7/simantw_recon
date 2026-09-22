"""Paired reconstruction of mirrored (black/red) colony functions.

The black and red colony objects are structural mirrors: for most functions
the source differs only in colony-specific symbols (BlistX/RlistX, LifeB/LifeR,
HoleMapB/HoleMapR, BAntsExpired/RAntsExpired, ...). Solving one side should
therefore constrain the other mechanically.

`derive` rewrites a preserved source of one side into the other: every
identifier that has a MAPSYM twin differing by exactly one B<->R (or
Blk/Red, Black/Red) substitution is swapped, together with the function name.
Constants are left alone; where the pair is not a pure mirror the strict
matcher shows exactly which literal or branch differs, which is evidence
about the real asymmetry rather than a guess.

`run` compiles the derived candidate under the target's object profile with
the strict matcher, records the result under evidence/recovery/mirror-pairs
and, when the body is exact, registers it on the target's workflow job as an
ordinary attempt (same budget rules) so the scaffolded-unit lane can admit it.
Nothing here grants credit.
"""
import argparse
import json
import re
from datetime import datetime, timezone
from common import ROOT, FormatError, read_json, write_json, identity

OUT = ROOT / 'evidence/recovery/mirror-pairs'
RULES = [('B', 'R'), ('Blk', 'Red'), ('Black', 'Red'), ('BLK', 'RED'), ('BLACK', 'RED')]
IDENT = re.compile(r'[A-Za-z_]\w*')


def mapsym_names():
    import mapsym
    from common import fixture
    s = mapsym.parse(fixture('SIMANTW.SYM'))
    return {x['name'] for seg in s['segments'] for x in seg['symbols']}


def mapsym_locations():
    import mapsym
    from common import fixture
    s = mapsym.parse(fixture('SIMANTW.SYM'))
    return {x['name'].lstrip('_'): (seg['number'], x['offset']) for seg in s['segments'] for x in seg['symbols']}


def constant_map(mapping, locations):
    """Colony list fields are often spelled as byte offsets into the one Dx8
    object (`AT((i) + 0x3d18)` for BlistT): the twin's offset replaces the
    literal when both names live in the same segment and the offset is large
    enough not to be an ordinary small constant."""
    out = {}
    for a, b in mapping.items():
        la, lb = locations.get(a), locations.get(b)
        if la and lb and la[0] == lb[0] and la[1] != lb[1] and la[1] >= 0x100:
            out[la[1]] = lb[1]
    return out


def twin_map(names, direction):
    """identifier -> mirrored identifier for every MAPSYM name whose single
    B/R (Blk/Red, Black/Red) substitution is also a MAPSYM name."""
    c_names = {n.lstrip('_') for n in names}
    out = {}
    for name in c_names:
        for a, b in RULES:
            src, dst = (a, b) if direction == 'B->R' else (b, a)
            if src not in name:
                continue
            # exactly one occurrence swapped, every position tried
            for m in re.finditer(re.escape(src), name):
                cand = name[:m.start()] + dst + name[m.end():]
                if cand != name and cand in c_names:
                    out.setdefault(name, cand)
    return out


def derive(text, mapping, from_symbol, to_symbol, constants=None):
    """Swap identifiers (and mirrored object offsets) in code, not inside
    comments or strings, together with the function name."""
    mapping = dict(mapping)
    constants = constants or {}
    mapping[from_symbol.lstrip('_')] = to_symbol.lstrip('_')
    pieces = re.split(r'(/\*.*?\*/|"(?:\\.|[^"\\])*")', text, flags=re.S)
    def literal(m):
        value = int(m.group(0), 16 if m.group(0).lower().startswith('0x') else 10)
        if value in constants:
            return ('0x%X' if m.group(0).lower().startswith('0x') else '%d') % constants[value]
        return m.group(0)
    out = []
    for i, piece in enumerate(pieces):
        if i % 2 == 1:
            out.append(piece)
        else:
            piece = IDENT.sub(lambda m: mapping.get(m.group(0), m.group(0)), piece)
            out.append(re.sub(r'(?<![\w.])(?:0[xX][0-9A-Fa-f]+|[1-9]\d{2,})(?![\w.])', literal, piece))
    text = ''.join(out)
    note = ('/* Derived mechanically from the mirrored colony function %s (tools/mirror_pairs.py):\n'
            ' * colony-specific MAPSYM identifiers swapped %s; constants and structure unchanged.\n'
            ' * Verified only by the strict matcher; where the pair is not a pure mirror the\n'
            ' * diagnostic names the asymmetry. */\n') % (from_symbol, ', '.join('%s->%s' % kv for kv in sorted(mapping.items()) if kv[0] in text or kv[1] in text)[:400])
    return note + text


def run(from_symbol, to_symbol, register=True):
    import tu_assembly as tu
    import compiler_profiles as cp
    from codegen_grinder import run as grind
    preserved = tu.preserved_sources()
    if from_symbol not in preserved:
        raise FormatError('no preserved source for ' + from_symbol)
    names = mapsym_names()
    direction = 'B->R' if from_symbol.endswith('B') or 'Blk' in from_symbol or 'Black' in from_symbol else 'R->B'
    mapping = twin_map(names, direction)
    constants = constant_map(mapping, mapsym_locations())
    source = (ROOT / preserved[from_symbol]['source']).read_text(encoding='latin1')
    derived = derive(source, mapping, from_symbol, to_symbol, constants)
    OUT.mkdir(parents=True, exist_ok=True)
    path = OUT / (to_symbol.lstrip('_') + '.c')
    path.write_text(derived, encoding='latin1')
    comp = cp.component_of(to_symbol) or {}
    profile = cp.resolve(to_symbol)
    flags = cp.profile_flags(profile['name'], comp.get('segment') or cp.component_of(from_symbol)['segment'])
    report = grind(dict(symbol=to_symbol, source=path.relative_to(ROOT).as_posix(), compiler='msc700', flags=flags, max_candidates=1, axes=[], publics=[to_symbol]),
                   (OUT / ('test_' + to_symbol.lstrip('_'))).relative_to(ROOT).as_posix(), cache=True)
    row = report['results'][0]
    comparison = row['comparison']
    d = comparison.get('diagnostic') or {}
    exact = tu.body_exact(comparison)
    changed = [dict(offset=r['target_offset'], target=r['target'], candidate=r['candidate'], differences=r['differences']) for r in d.get('aligned_asm', []) if r['differences'] and set(r['differences']) - {'memory_operand'}]
    record = dict(source_symbol=from_symbol, target_symbol=to_symbol, source_basis=preserved[from_symbol]['basis'], derived=path.relative_to(ROOT).as_posix(), flags=flags,
                  result=comparison.get('result'), exact_body=exact, opcode_matches=d.get('opcode_matches'), opcode_total=d.get('opcode_total'),
                  candidate_bytes=d.get('candidate_bytes'), target_bytes=d.get('target_bytes'), asymmetries=changed[:40], issues=(comparison.get('issues') or [])[:6],
                  checked=datetime.now(timezone.utc).isoformat(), registered=None)
    if exact and register:
        record['registered'] = register_attempt(to_symbol, path, flags, from_symbol)
    write_json(OUT / (to_symbol.lstrip('_') + '.json'), record)
    return record


def register_attempt(symbol, path, flags, from_symbol):
    """Record the derived exact body on the target's job through the ordinary
    reissue path (escalated job) or a test (open job)."""
    import subprocess, sys
    import recovery_workflow as wf
    job = next((j for j in wf.jobs() if j['symbol'] == symbol), None)
    if job is None:
        return 'no job'
    spec = dict(symbol=symbol, source=path.relative_to(ROOT).as_posix(), compiler='msc700', flags=job['flags'], max_candidates=1, axes=[],
                semantic_summary='Mirrored derivation from %s (tools/mirror_pairs.py): colony-specific identifiers swapped, structure unchanged' % from_symbol,
                binding_evidence=['tools/mirror_pairs.py twin map over MAPSYM names'], publics=[symbol])
    spec_path = OUT / (symbol.lstrip('_') + '-spec.json')
    write_json(spec_path, spec)
    if job['flags'] != flags:
        return 'job flags %s differ from the context profile %s; profile reissue needed first' % (job['flags'], flags)
    if job['status'] == 'ESCALATED':
        r = subprocess.run([sys.executable, 'tools/topology_retest.py', job['id'], spec_path.relative_to(ROOT).as_posix(), '--reason', 'mirrored derivation from ' + from_symbol], capture_output=True, text=True)
    else:
        r = subprocess.run([sys.executable, 'tools/grind.py', 'test', symbol, path.relative_to(ROOT).as_posix()], capture_output=True, text=True)
    out = r.stdout + r.stderr
    return [l.strip() for l in out.splitlines() if '"status"' in l or 'ERROR' in l or 'Error' in l][:3] or out[-200:]


def pairs(universe):
    from blocked_reclassification import mirror_partner
    seen = set()
    for s in sorted(universe):
        p = mirror_partner(s, universe)
        if p and (p, s) not in seen:
            seen.add((s, p))
            yield s, p


def main(args):
    import tu_assembly as tu
    import recovery_workflow as wf
    preserved = tu.preserved_sources()
    recipes = wf.recipes()
    queue = {f['symbol']: f['state'] for f in read_json(ROOT / 'docs/production-queue.json')['functions']}
    solved = {s for s, v in preserved.items() if v['basis'] in ('ADMITTED', 'BODY_MATCHED_BINDING_BLOCKED', 'EXACT_BODY_CANDIDATE')}
    results = []
    if args.pair:
        results.append(run(args.pair[0], args.pair[1], register=not args.no_register))
    else:
        for a, b in pairs(set(queue) | set(recipes)):
            for src, dst in ((a, b), (b, a)):
                if src in solved and dst not in recipes and queue.get(dst) in ('MATCH_BLOCKED', 'MATCH_READY'):
                    print(src, '->', dst, flush=True)
                    try:
                        results.append(run(src, dst, register=not args.no_register))
                    except FormatError as exc:
                        results.append(dict(source_symbol=src, target_symbol=dst, error=str(exc)))
                elif args.all and src in preserved and dst not in recipes and queue.get(dst) in ('MATCH_BLOCKED', 'MATCH_READY'):
                    # Both sides open: derive from the better-matching side as evidence only.
                    print(src, '->', dst, '(evidence)', flush=True)
                    try:
                        results.append(run(src, dst, register=False))
                    except FormatError as exc:
                        results.append(dict(source_symbol=src, target_symbol=dst, error=str(exc)))
    write_json(OUT / 'summary.json', dict(generated=datetime.now(timezone.utc).isoformat(), results=results))
    for r in results:
        print(r.get('source_symbol'), '->', r.get('target_symbol'), r.get('result'), 'exact' if r.get('exact_body') else '', r.get('opcode_matches'), '/', r.get('opcode_total'), r.get('registered') or r.get('error') or '')


if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('--pair', nargs=2, metavar=('FROM', 'TO'))
    p.add_argument('--all', action='store_true', help='also derive across pairs where both sides are open (evidence only)')
    p.add_argument('--no-register', action='store_true')
    main(p.parse_args())
