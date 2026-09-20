"""Production/research states with source-independent structural certificates."""
from collections import Counter
import json
from common import ROOT,fixture,read_json,write_json,sha256
from recovery_workflow import cards,jobs,recipes
from cfg_solver import solve
from analysis import decoder
import ne,mapsym


def certify(card,raw,image,symbols):
    e=card['extent'];reasons=[]
    if e['end'] is None or e['status'] in ('SHARED_TAIL','OVERLAPPING_ENTRY','AMBIGUOUS_TABLE'):reasons.append('UNCLOSED_OR_SHARED_CFG')
    if e.get('incoming_branches') or e.get('entry_aliases'):reasons.append('CROSS_ENTRY_OR_ALIAS')
    if reasons:return dict(status='UNCONFIRMED',reasons=reasons)
    ns=image['segments'][card['segment']-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']];entries=[p['offset'] for p in symbols['segments'][card['segment']-1]['symbols']]
    proof=solve(code,card['offset'],e['upper_bound'],entries,ns['relocations'],card['segment'])
    if proof['end']!=e['end'] or proof['status']!='PROBABLE' or proof['reasons']:reasons.append('RECURSIVE_SCOPE_NOT_CLOSED')
    decoded=list(decoder().disasm(code[card['offset']:e['end']],card['offset']))
    if sum(i.size for i in decoded)!=e['size']:reasons.append('INCOMPLETE_LINEAR_DECODE')
    starts={i.address:i for i in decoded}
    if not set(proof['instruction_starts']).issubset(starts):reasons.append('OVERLAPPING_INSTRUCTION_STREAMS')
    for r in ns['relocations']:
        for site in r['sites']:
            if card['offset']<=site<e['end']:
                if site+r['width']>e['end'] or r['source_type'] not in (2,3,5):reasons.append('UNEVALUABLE_FIXUP_SCOPE')
    return dict(status='CONFIRMED' if not reasons else 'UNCONFIRMED',reasons=sorted(set(reasons)),start=card['offset'],size=e['size'],cfg_status=e['status'],target_sha256=sha256(code[card['offset']:e['end']]),scope='Closed structural test extent, checked recursively and linearly; not source-recovery proof or a historical OMF/TU boundary',basis=['Unique MAPSYM entry','Closed recursive CFG with explicit NOP-only gaps','Independent linear instruction-boundary coverage','No known incoming cross-entry branch or alias','Contained evaluable NE relocation obligations'])


def generate():
    raw=fixture('SIMANTW.EXE');image=ne.parse(raw);symbols=mapsym.parse(fixture('SIMANTW.SYM'));recovered=recipes();history={j['symbol']:j for j in jobs()};ledger=read_json(ROOT/'evidence/recovery/blockers.json');blocked={**ledger['drafts'],**ledger.get('workflow_cases',{})};items=[]
    cachepath=ROOT/'docs/production-queue.json';prior=read_json(cachepath) if cachepath.exists() else {};tool_hash=sha256(b''.join((ROOT/p).read_bytes() for p in ['tools/factory_queue.py','tools/cfg_solver.py','tools/analysis.py','tools/ne.py','tools/mapsym.py']));cache={r['symbol']:r for r in prior.get('functions',[])} if prior.get('exe_sha256')==image['sha256'] and prior.get('sym_sha256')==symbols['sha256'] and prior.get('certificate_tool')==tool_hash else {}
    for card in cards():
        if card['ownership']!='GAME':continue
        name=card['symbol'];job=history.get(name)
        extent_key=sha256(json.dumps(card['extent'],sort_keys=True).encode());old=cache.get(name,{})
        certificate=(old['extent'] if old.get('extent_input')==extent_key else certify(card,raw,image,symbols)) if name not in recovered else dict(status='CONFIRMED',start=recovered[name]['offset'],size=recovered[name]['size'],scope='Existing independently verified source recipe')
        if name in recovered:state='MATCHED';reasons=[]
        elif certificate['status']!='CONFIRMED':state='STRUCTURE_BLOCKED';reasons=certificate['reasons']
        elif job and job['status']=='ESCALATED':state='MATCH_BLOCKED';reasons=job['blockers']
        elif name in blocked and blocked[name]['status']!='PROMOTED_EXACT_RECONSTRUCTION':state='MATCH_BLOCKED';reasons=blocked[name]['blockers']
        else:state='MATCH_READY';reasons=[]
        items.append(dict(symbol=name,state=state,blockers=reasons,extent=certificate,extent_input=extent_key,size=card['extent']['size'],segment=card['segment_name'],job=job['id'] if job else None,job_status=job['status'] if job else None,attempts=len(job.get('attempts',[])) if job else 0))
    items.sort(key=lambda r:({'MATCH_READY':0,'MATCH_BLOCKED':1,'STRUCTURE_BLOCKED':2,'MATCHED':3}[r['state']],r['size'] or 65536,r['symbol']))
    result=dict(schema_version=1,exe_sha256=image['sha256'],sym_sha256=symbols['sha256'],certificate_tool=sha256(b''.join((ROOT/p).read_bytes() for p in ['tools/factory_queue.py','tools/cfg_solver.py','tools/analysis.py','tools/ne.py','tools/mapsym.py'])),states=dict(Counter(r['state'] for r in items)),functions=items,proof_boundary='Structural certificates authorize candidate testing only. Strict recovery admission remains mandatory.')
    write_json(ROOT/'docs/production-queue.json',result);return result

if __name__=='__main__':print(generate()['states'])
