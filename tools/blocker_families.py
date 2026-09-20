"""Reproducible blocker families from actual failed fixup sites and CFG evidence.

Offsets are observations, never construction constants. A shared address is
reference evidence, not proof of a unique object boundary or historical TU.
"""
import json
from collections import defaultdict, Counter
from common import ROOT, read_json, write_json, identity, fixture
import mapsym
from topology_diagnostics import classify
from codegen_grinder import rank
from analysis import decoder, cs
import omf


def observations(row, card):
    comparison = row.get('comparison', {})
    if comparison.get('diagnostic', {}).get('instruction_layout_match') is not True:
        return []
    receipt = row.get('receipt', {})
    path = ROOT / receipt.get('object', '__missing__')
    if not path.is_file() or identity(path) != receipt.get('object_identity'):
        return []
    module = omf.parse(path.read_bytes())
    pub = next((p for p in module['publics'] if p['name'] == card['symbol']), None)
    if not pub:
        return []
    segment = module['segments'][pub['segment'] - 1]
    code = bytes.fromhex(segment['data_hex'])
    target = bytes.fromhex(''.join(r['bytes'] for r in card['disassembly']))
    result = []
    for contribution in comparison.get('contributions', []):
        if contribution['segment'] != segment['name']:
            continue
        for f in contribution.get('fixups', []):
            o = f['omf']; p = f['offset'] - pub['offset']
            if f['equal'] or o['location_type'] != 1 or o['self_relative'] or not 0 <= p < len(target)-1:
                continue
            ins = next((i for i in decoder().disasm(target, 0) if i.address <= p < i.address+i.size), None)
            if ins is None or ins.group(cs.CS_GRP_CALL) or ins.group(cs.CS_GRP_JUMP):
                continue
            # Require an actual displacement/immediate field, not an opcode.
            if p not in (ins.address+ins.disp_offset, ins.address+ins.imm_offset):
                continue
            region = 'DGROUP'
            for operand in ins.operands:
                if operand.type == cs.x86.X86_OP_MEM and ins.reg_name(operand.mem.segment) in ('es','cs','ss'):
                    region = ins.reg_name(operand.mem.segment).upper() + '_UNRESOLVED'
            value = int.from_bytes(target[p:p+2], 'little')
            addend = int.from_bytes(code[f['offset']:f['offset']+2], 'little') + o['displacement']
            base = (value-addend) & 65535
            # Far offsets cannot be identified across functions until selector
            # ownership is independently established; retain function scope.
            key = '%s:%04X' % (region, value)
            if region != 'DGROUP':
                key += ':' + card['symbol']
            result.append(dict(key=key, region=region, observed_operand=value,
                inferred_base=base, candidate_addend=addend,
                instruction=card['offset']+ins.address,
                instruction_text=ins.mnemonic+' '+ins.op_str,
                candidate_target=o['target'], confidence='REFERENCE_CONSTRAINT',
                size=None, source_order_reproduced=False))
    return result


def direct_references(card, named):
    refs=[]
    for row in card['disassembly']:
        for ins in decoder().disasm(bytes.fromhex(row['bytes']), row['offset']):
            for operand in ins.operands:
                if operand.type != cs.x86.X86_OP_MEM:
                    continue
                mem=operand.mem
                if ins.reg_name(mem.base) in ('bp','sp') or ins.reg_name(mem.segment) not in (None,'','ds'):
                    continue
                address=mem.disp & 65535
                if address < 256 or address in named:
                    continue
                refs.append(dict(key='DGROUP:%04X'%address, region='DGROUP',
                    observed_operand=address,inferred_base=address,candidate_addend=None,
                    instruction=ins.address,instruction_text=ins.mnemonic+' '+ins.op_str,
                    candidate_target=None,confidence='DIRECT_OPERAND_NOT_OBJECT_BOUNDARY',
                    size=None,source_order_reproduced=False))
    return refs


def generate():
    cards = {c['symbol']:c for c in map(json.loads, (ROOT/'evidence/disassembly/cards.jsonl').read_text().splitlines())}
    symbols=mapsym.parse(fixture('SIMANTW.SYM'))
    named={p['offset'] for p in symbols['segments'][9]['symbols']}
    ledger = read_json(ROOT/'evidence/recovery/blockers.json')
    queue = read_json(ROOT/'docs/production-queue.json')
    states = {r['symbol']:r['state'] for r in queue['functions']}
    cases = {**ledger['drafts'], **ledger.get('workflow_cases', {})}
    results = defaultdict(list)
    for path in sorted((ROOT/'evidence/recovery/workflow/jobs').glob('*/attempt*/results.json')):
        report = read_json(path)
        for row in report['results']:
            results[report['symbol']].append((row, path.relative_to(ROOT).as_posix()))
    baseline = ROOT/'evidence/codegen/corpus-results.json'
    for row in read_json(baseline)['results']:
        results[row['symbol']].append((row, baseline.relative_to(ROOT).as_posix()))
    solved=read_json(ROOT/'evidence/topology/solved-families.json')['families']
    solved_names={n for f in solved for n in f['members']}
    for name in solved_names:
        cases.setdefault(name,dict(blockers=[],next_experiment='Strictly promoted; regression only'))
    objects = {}; functions = {}; owners = defaultdict(set)
    for name in sorted(n for n in cases if n in cards and (states.get(n) != 'MATCHED' or n in solved_names)):
        candidates = sorted(results[name], key=lambda pair:(classify(pair[0].get('comparison', {})) is not None, rank(pair[0])), reverse=True)
        row, evidence = candidates[0] if candidates else ({}, None)
        diagnosis = classify(row.get('comparison', {}))
        refs = observations(row, cards[name]) + direct_references(cards[name], named)
        for ref in refs:
            key = ref['key']; owners[key].add(name)
            obj = objects.setdefault(key, dict(id=key, region=ref['region'], observed_base=ref['observed_operand'], size=None,
                near_far='near' if ref['region']=='DGROUP' else 'far selector unresolved',
                historical_name=None, candidate_tu=None, confidence='REFERENCE_CONSTRAINT',
                source_order_reproduced=False, references=[]))
            obj['references'].append(dict(symbol=name, evidence=evidence, **ref))
        functions[name] = dict(evidence_state='SOLVED_STRICT' if name in solved_names and states.get(name)=='MATCHED' else diagnosis['state'] if diagnosis else 'BODY_UNRESOLVED_OR_UNMEASURED',
            diagnosis=diagnosis, evidence=evidence, candidate=row.get('candidate'),
            source=row.get('receipt', {}).get('source', cases[name].get('source')),
            source_identity=row.get('receipt', {}).get('source_identity'),
            objects=sorted({r['key'] for r in refs}), blockers=cases[name]['blockers'],
            next_experiment=cases[name].get('next_experiment'), recovery_credit=0)
    for name, function in functions.items():
        source=ROOT/(function.get('source') or '__missing__')
        if function['diagnosis'] and source.is_file() and identity(source)==function.get('source_identity'):
            destination=ROOT/'evidence/recovery/body-solved'/(name+'-'+identity(source)['sha256'][:12]+'.c')
            destination.parent.mkdir(parents=True,exist_ok=True)
            if not destination.exists():destination.write_bytes(source.read_bytes())
            if identity(destination)!=identity(source):raise ValueError('preserved body identity changed')
            function['preserved_source']=destination.relative_to(ROOT).as_posix()
    for family in solved:
        for item in family['objects']:
            obj=objects.setdefault(item['id'],dict(id=item['id'],references=[]))
            obj.update(item,confidence='STRICT_MEMBER_CONSTRAINT',candidate_tu=family['id'],evidence=family['evidence'])
    mm_path=ROOT/'evidence/topology/mm-state.json'
    if mm_path.exists():
        mm=read_json(mm_path)
        obj=objects.setdefault('DGROUP:BF78',dict(id='DGROUP:BF78',references=[]))
        obj.update(selector_slot=mm['selector_slot'],all_observed_users=mm['users'],
                   confidence='NE_SELECTOR_AND_SHARED_LOADS',evidence='evidence/topology/mm-state.json',
                   source_order_reproduced=False)
        objects['SIMANT_DATA_GROUP:8D06..8D1D']=dict(id='SIMANT_DATA_GROUP:8D06..8D1D',
            region='SIMANT_DATA_GROUP',segment=8,observed_range=[0x8d06,0x8d1e],size=None,
            minimum_span=24,near_far='far',selector_slot='DGROUP:BF78',
            candidate_tu='sound-availability-candidate',confidence='OBSERVED_FIELDS_NOT_OBJECT_BOUNDARY',
            source_order_reproduced=False,evidence='evidence/topology/mm-state.json')
    # Connected components use shared observed object bindings, not taxonomy.
    remaining=set(functions); families=[]
    while remaining:
        todo=[min(remaining)]; members=set(); keys=set()
        while todo:
            name=todo.pop()
            if name in members:continue
            members.add(name);remaining.discard(name)
            for key in functions[name]['objects']:
                keys.add(key);todo.extend(sorted(owners[key]-members))
        family_id='binding-'+min(members).lstrip('_')
        family=dict(id=family_id, members=sorted(members), objects=sorted(keys),
            confidence='SHARED_REFERENCE_FAMILY' if len(members)>1 else 'SINGLETON_REQUIRES_REVIEW',
            evidence_state_counts=dict(Counter(functions[n]['evidence_state'] for n in members)),
            historical_filename=None, recovery_credit=0)
        families.append(family)
        for name in members:functions[name]['family']=family_id
    dispatch_path=ROOT/'evidence/topology/structural-dispatch.json'
    dispatches=read_json(dispatch_path)['dispatches'] if dispatch_path.exists() else []
    structural=[]
    for name,state in sorted(states.items()):
        if state!='STRUCTURE_BLOCKED':continue
        card=cards[name];e=card['extent']
        structural.append(dict(dispatch_evidence=[r for r in dispatches if r['symbol']==name], symbol=name, segment=card['segment_name'], offset=card['offset'],
            family='INDIRECT_DISPATCH_TABLE' if e.get('indirect_jumps') else 'INTERRUPT_OR_NONRETURN' if any('interrupt' in r for r in e.get('reasons',[])) else 'UNCLOSED_SCOPE',
            cfg_status=e['status'], indirect_jumps=e.get('indirect_jumps',[]), reasons=e.get('reasons',[]),
            gaps=e.get('gaps',[]), incoming_branches=e.get('incoming_branches',[]),
            next_experiment='Prove bounded table span, every target instruction boundary and closure; preserve embedded data' if e.get('indirect_jumps') else 'Review interrupt/return ABI; do not assume ordinary far-return scope'))
    families.sort(key=lambda f:(-len(f['members']),f['id']))
    report=dict(schema_version=1, proof_boundary='Routing only; no recovery credit or new structural certificate',
        inputs={p:identity(ROOT/p) for p in ['docs/production-queue.json','evidence/recovery/blockers.json','evidence/disassembly/cards.jsonl']},
        families=families, solved_families=solved, functions=functions, structural=structural,
        summary=dict(families=len(families), shared_families=sum(len(f['members'])>1 for f in families),
            evidence_states=dict(Counter(f['evidence_state'] for f in functions.values())),
            structural_families=dict(Counter(f['family'] for f in structural))))
    write_json(ROOT/'evidence/recovery/blocker-families.json',report)
    write_json(ROOT/'layout/private-data-topology.json',dict(schema_version=1, scope='Observed bindings; offsets are not source constants or proven object boundaries',objects=list(objects.values())))
    lines=['# Blocker families','', 'Generated by `python tools/blocker_families.py`. No recovery credit.','',json.dumps(report['summary'],sort_keys=True),'',
           '| Family | Members | Observed shared bindings |','| --- | --- | --- |']
    for f in families:
        lines.append('| '+f['id']+' | '+', '.join(f['members'])+' | '+', '.join(f['objects'])+' |')
    lines += ['', 'Structural cases retain their original scopes. Dispatch-table cases require a table-aware certificate; interrupts need ABI review. No extent is widened here.', '',
              'A body classification requires complete layout/CFG/opcode agreement, zero register/stack/branch differences, and all literal differences covered by failing two-byte offset fixups. It does not assert correct data identity or semantics.', '',
              'Far references retain an unresolved segment label: identical offsets alone do not establish the same far object. Singleton families and unmeasured frozen bodies require expert review.']
    (ROOT/'docs/blocker-families.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
    print(report['summary'])
    return report


if __name__=='__main__':generate()
