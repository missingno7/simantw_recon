"""Near-exact source-shape lane: TRUE_SOURCE_SHAPE_MISMATCH rows whose fresh
strict comparison under the current object profile agrees on >= 95% of the
opcodes. They are usually one idiom away from exact (frame home order, local
width, branch form, field/index binding), so they are grouped by *residual
signature* and worked as families rather than as isolated functions.

Families (by the fresh diagnostic):
- FRAME: exact opcodes, only stack-home (frame slot) differences
- BINDING: exact opcodes, resolved displacement/index differs (wrong field,
  table, or index expression)
- REGISTER: exact opcodes, register colouring differs
- BRANCH: exact opcodes, branch layout differs
- NEAR_SHAPE: 1-2 opcode differences (a single idiom)

Output: evidence/recovery/near-exact-lane.json (rows with the residual
aligned-asm rows and the family), docs/near-exact-lane.md.
"""
import argparse
from collections import Counter, defaultdict
from datetime import datetime, timezone
from common import ROOT, read_json, write_json

OUT = ROOT / 'evidence/recovery/near-exact-lane.json'
DOC = ROOT / 'docs/near-exact-lane.md'
THRESHOLD = 0.95


def family(evidence, residual):
    exact = evidence.get('opcode_matches') == evidence.get('opcode_total')
    reg, br, st = evidence.get('register_only') or 0, evidence.get('branch') or 0, evidence.get('stack') or 0
    if exact:
        if reg == 0 and br == 0 and st == 0:
            return 'BINDING'
        if st and reg == 0 and br == 0:
            return 'FRAME'
        if reg and br == 0:
            return 'REGISTER' if not st else 'REGISTER_FRAME'
        if br and reg == 0:
            return 'BRANCH'
        return 'MIXED'
    return 'NEAR_SHAPE'


def main():
    report = read_json(ROOT / 'evidence/recovery/blocked-reclassification.json')
    rows = []
    for r in report['rows']:
        e = r.get('evidence') or {}
        if r['category'] != 'TRUE_SOURCE_SHAPE_MISMATCH' or not e.get('opcode_total'):
            continue
        ratio = e['opcode_matches'] / e['opcode_total']
        if ratio < THRESHOLD:
            continue
        fresh = ROOT / 'build/reclassify' / r['symbol'].lstrip('_') / 'results.json'
        residual = []
        wrong = []
        if fresh.exists():
            comparison = read_json(fresh)['results'][0]['comparison']
            d = comparison.get('diagnostic') or {}
            residual = [dict(offset=x['target_offset'], target=x['target'], candidate=x['candidate'], differences=x['differences'])
                        for x in d.get('aligned_asm', []) if x['differences'] and set(x['differences']) - {'memory_operand'}]
            wrong = [dict(offset=f['offset'], symbol=(f.get('omf') or {}).get('target', {}).get('name'), resolved=f.get('target'))
                     for c in comparison.get('contributions', []) for f in c.get('fixups', [])
                     if not f['equal'] and f.get('target') is not None and f.get('reason') in ('resolved offset and frame', 'same-segment relative offset')]
        rows.append(dict(symbol=r['symbol'], component=r['component'], profile=r['profile'], job=r['job'], size=r['size'], source=r['source'],
                         ratio=round(ratio, 4), opcode_matches=e['opcode_matches'], opcode_total=e['opcode_total'], candidate_bytes=e['candidate_bytes'], target_bytes=e['target_bytes'],
                         register_only=e.get('register_only'), branch=e.get('branch'), stack=e.get('stack'), categories=e.get('categories', []),
                         family=family(e, residual), residual=residual[:30], wrong_bindings=wrong[:20], mirror_partner=r.get('mirror_partner')))
    # Siblings: same component, same target size and same family.
    groups = defaultdict(list)
    for r in rows:
        groups[(r['component'], r['family'], r['target_bytes'])].append(r['symbol'])
    for r in rows:
        r['siblings'] = [s for s in groups[(r['component'], r['family'], r['target_bytes'])] if s != r['symbol']]
    rows.sort(key=lambda r: (-r['ratio'], r['family'], r['component'], r['symbol']))
    out = dict(schema_version=1, generated=datetime.now(timezone.utc).isoformat(), threshold=THRESHOLD, counts=dict(Counter(r['family'] for r in rows)), rows=rows,
               scope='Search lane only; admission stays with the strict matcher. Residual rows come from the fresh recompilation under the current object profile.')
    write_json(OUT, out)
    lines = ['# Near-exact source-shape lane (>= %d%% opcode agreement)' % int(THRESHOLD * 100), '', 'Generated %s. %d functions. Families: %s' % (out['generated'], len(rows), ', '.join('%s %d' % kv for kv in out['counts'].items())), '',
             '| symbol | context | family | opcodes | bytes | reg/br/stack | siblings | first residual |', '|---|---|---|---|---|---|---|---|']
    for r in rows:
        first = r['residual'][0] if r['residual'] else (r['wrong_bindings'][0] if r['wrong_bindings'] else {})
        lines.append('| %s | %s | %s | %d/%d | %s/%s | %s/%s/%s | %s | %s |' % (r['symbol'], r['component'], r['family'], r['opcode_matches'], r['opcode_total'], r['candidate_bytes'], r['target_bytes'], r['register_only'], r['branch'], r['stack'], ', '.join(r['siblings']), str(first).replace('|', '/')[:120]))
    DOC.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print(out['counts'], len(rows))
    return out


if __name__ == '__main__':
    main()
