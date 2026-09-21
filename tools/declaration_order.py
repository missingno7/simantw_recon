"""Derive private static declaration order from the original data word positions.

For a parked job whose body matches and whose only failing obligations are
offset fixups into one private segment (_DATA or _BSS), the original operand
values give the historical position of every private object. If those
positions form one block whose gaps equal the declared object sizes, the
candidate merely declared its statics in the wrong order: this tool rewrites
the declaration order, records the evidence and issues the reviewed replay
through the expert reissue path. Anything else (gaps for other functions'
statics, mixed segments, BSS words below _edata) is reported, not forced.
"""
import argparse
import json
import re
from common import ROOT, FormatError, read_json, write_json, identity
import recovery_workflow as wf
import omf

EVIDENCE = ROOT / 'evidence/topology/supervisor-declaration-order'
SIZES = {'char': 1, 'unsigned char': 1, 'signed char': 1, 'int': 2, 'unsigned': 2, 'unsigned int': 2, 'short': 2, 'unsigned short': 2,
         'long': 4, 'unsigned long': 4, 'float': 4, 'double': 8}


def static_declarations(source):
    """Top-level static data declarations in order, with size and byte extent."""
    text = re.sub(r'/\*.*?\*/|//[^\n]*', '', source, flags=re.S)
    rows = []
    for m in re.finditer(r'^\s*static\s+([^;{]*?)\b([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(=\s*[^;]*)?;', text, flags=re.M):
        spec, name, dims, init = m.group(1), m.group(2), m.group(3), m.group(4)
        if '(' in spec:
            continue  # function declaration
        base = re.sub(r'\b(near|far|huge|const|volatile|static)\b', ' ', spec)
        base = ' '.join(base.split())
        if '*' in base:
            size = 4 if 'far' in spec.split('*')[0] or spec.strip().endswith('far *') or re.search(r'far\s*\*', spec) else 2
            if re.search(r'\*\s*far\s*\*', spec):
                size = 4
        elif base.startswith('struct') or base.startswith('union'):
            return None  # struct sizes need the definition; not handled
        else:
            size = SIZES.get(base)
            if size is None:
                return None
        count = 1
        for dim in re.findall(r'\[([^\]]*)\]', dims):
            dim = dim.strip()
            if not dim:
                if init and init.strip().startswith('= "'):
                    count *= len(bytes(init.strip()[3:-1], 'latin1').decode('unicode_escape')) + 1
                else:
                    return None
            else:
                try:
                    count *= int(eval(dim, {}, {}))
                except Exception:
                    return None
        rows.append(dict(name=name, size=size * count, text=m.group(0).strip(), initialised=bool(init), span=(m.start(), m.end())))
    return rows


def analyse(job_id):
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    if job['status'] != 'ESCALATED':
        raise FormatError('job is not parked')
    from compiler_profiles import best_candidate
    source_path, row = best_candidate(job)
    comparison = row['comparison']
    d = comparison.get('diagnostic') or {}
    if not (d.get('instruction_layout_match') and d.get('opcode_matches') == d.get('opcode_total') and d.get('register_only_differences') == 0):
        raise FormatError('body is not exact; declaration order cannot be the only problem')
    module = omf.parse((ROOT / row['receipt']['object']).read_bytes())
    pub = next(p for p in module['publics'] if p['name'] == job['symbol'])
    code = bytes.fromhex(module['segments'][pub['segment'] - 1]['data_hex'])
    card = next(c for c in wf.cards() if c['symbol'] == job['symbol'])
    target = bytes.fromhex(''.join(x['bytes'] for x in card['disassembly']))
    failing = []
    for con in comparison.get('contributions', []):
        for f in con['fixups']:
            o = f['omf']
            private = o['target'].get('kind') == 'segment' and o['target'].get('name') in ('_DATA', '_BSS') and o['location_type'] == 1
            if f['equal'] and not private:
                continue
            if not private:
                raise FormatError('failing fixup is not a private segment offset: ' + json.dumps(o['target']))
            p = f['offset']
            displacement = int.from_bytes(code[p:p + 2], 'little') + o['displacement']
            original = int.from_bytes(target[p - pub['offset']:p - pub['offset'] + 2], 'little')
            failing.append(dict(segment=o['target']['name'], displacement=displacement, original=original))
    segments = {f['segment'] for f in failing}
    if len(segments) != 1:
        raise FormatError('failing fixups span several private segments: ' + ', '.join(sorted(segments)))
    segment = segments.pop()
    source = source_path.read_text(encoding='latin1')
    statics = static_declarations(source)
    if statics is None:
        raise FormatError('static declarations use types this tool cannot size')
    wanted = {'_BSS': lambda s: not s['initialised'], '_DATA': lambda s: s['initialised']}
    if segment not in wanted:
        raise FormatError('unsupported private segment ' + segment)
    members = [s for s in statics if wanted[segment](s)]
    offset = 0
    for s in members:
        s['offset'] = offset
        offset += s['size'] + (s['size'] & 1)  # word alignment of the next object
    by_offset = {s['offset']: s for s in members}
    mapping = {}
    for f in failing:
        owner = next((s for s in members if s['offset'] <= f['displacement'] < s['offset'] + s['size']), None)
        if owner is None:
            raise FormatError('displacement %d has no static owner' % f['displacement'])
        base = f['original'] - (f['displacement'] - owner['offset'])
        if mapping.setdefault(owner['name'], base) != base:
            raise FormatError('inconsistent original positions for ' + owner['name'])
    if len(mapping) != len(members):
        raise FormatError('some statics are never referenced by a failing fixup; order cannot be derived for %s' % [s['name'] for s in members if s['name'] not in mapping])
    order = sorted(members, key=lambda s: mapping[s['name']])
    expected = mapping[order[0]['name']]
    gaps = []
    for s in order:
        if mapping[s['name']] != expected:
            gaps.append(dict(name=s['name'], expected=expected, original=mapping[s['name']]))
        expected = mapping[s['name']] + s['size'] + (s['size'] & 1)
    if segment == '_BSS':
        names = {p['name']: p['offset'] for p in wf.mapsym.parse(wf.fixture('SIMANTW.SYM'))['segments'][9]['symbols']}
        if mapping[order[0]['name']] < names['_edata']:
            raise FormatError('original words lie below _edata: the statics are initialised data or another object; not a BSS order problem')
    result = dict(job=job_id, symbol=job['symbol'], segment=segment, source=str(source_path.relative_to(ROOT).as_posix()),
                  positions={s['name']: '%04X' % mapping[s['name']] for s in order}, order=[s['name'] for s in order], gaps=gaps, statics=[dict(name=s['name'], size=s['size'], initialised=s['initialised']) for s in statics])
    if gaps:
        result['status'] = 'GAPS_REQUIRE_UNIT'
        return result, None
    if [s['name'] for s in order] == [s['name'] for s in members]:
        result['status'] = 'ORDER_ALREADY_MATCHES'
        return result, None
    # Rewrite: replace the block of member declarations by the same texts in the new order.
    spans = sorted(s['span'] for s in members)
    first, last = spans[0][0], spans[-1][1]
    block = source[first:last]
    for s in members:
        block = block.replace(s['text'], '@@' + s['name'] + '@@', 1)
    if block.count('@@') != 2 * len(members):
        raise FormatError('could not isolate the static declarations for rewriting')
    texts = [s['text'] for s in order]
    for s, text in zip(members, texts):
        block = block.replace('@@' + s['name'] + '@@', text, 1)
    rewritten = source[:first] + block + source[last:]
    result['status'] = 'REORDERED'
    return result, rewritten


def reissue(job_id):
    result, rewritten = analyse(job_id)
    if rewritten is None:
        return result
    EVIDENCE.mkdir(parents=True, exist_ok=True)
    path = EVIDENCE / (result['symbol'].lstrip('_') + '.c')
    header = '/* Private %s declaration order derived from the original word positions %s (tools/declaration_order.py). */\n' % (result['segment'], ', '.join('%s=%s' % kv for kv in result['positions'].items()))
    path.write_text(header + rewritten, encoding='latin1')
    directory = wf.STATE / 'jobs' / job_id
    job = read_json(directory / 'job.json')
    spec = dict(symbol=result['symbol'], source=path.relative_to(ROOT).as_posix(), compiler='msc700', flags=job['flags'], max_candidates=1, axes=[],
                semantic_summary=read_json(directory / 'submission.json').get('semantic_summary', 'Preserved body with derived static order'),
                binding_evidence=['original private %s words %s; candidate statics reordered to reproduce them' % (result['segment'], ', '.join(result['positions'].values()))], publics=[result['symbol']])
    spec_path = EVIDENCE / (result['symbol'].lstrip('_') + '-spec.json')
    write_json(spec_path, spec)
    write_json(EVIDENCE / (result['symbol'].lstrip('_') + '-analysis.json'), result)
    import topology_retest
    outcome = topology_retest.reissue(job_id, spec_path.relative_to(ROOT).as_posix(), 'Private %s declaration order derived from the original word positions' % result['segment'])
    result['outcome'] = dict(status=outcome['status'], result=outcome['attempt']['result'])
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('job')
    ap.add_argument('--reissue', action='store_true')
    args = ap.parse_args()
    if args.reissue:
        with wf.global_lock():
            wf.recover_transaction()
        with wf.job_lock(args.job):
            print(json.dumps(reissue(args.job), indent=2))
    else:
        result, rewritten = analyse(args.job)
        print(json.dumps(result, indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
