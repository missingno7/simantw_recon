"""Deterministic function frontier and cards; unknown extents stay unknown."""
import json
from collections import Counter
from common import ROOT, fixture, read_json, write_json, sha256
from analysis import extent, disassemble
import ne, mapsym

def main():
    raw=fixture('SIMANTW.EXE');s=mapsym.parse(fixture('SIMANTW.SYM'));n=ne.parse(raw)
    inventory=read_json(ROOT/'evidence/symbols/inventory.json')['symbols']
    recipes=read_json(ROOT/'src/recovery.json')['targets'];cards=[]
    ledger_path=ROOT/'evidence/recovery/blockers.json'
    ledger=read_json(ledger_path) if ledger_path.exists() else {}
    drafts={**ledger.get('drafts',{}),**ledger.get('workflow_cases',{})}
    cfgpath=ROOT/'evidence/disassembly/cfg-extents.json'
    cfg=read_json(cfgpath) if cfgpath.exists() else {}
    if cfg and (cfg['exe_sha256']!=sha256(raw) or cfg['sym_sha256']!=s['sha256']):raise ValueError('stale CFG evidence')
    runtime_path=ROOT/'layout/runtime-ownership.json'
    runtime=read_json(runtime_path)['members'] if runtime_path.exists() else []
    provenance={'exe_sha256':sha256(raw),'sym_sha256':s['sha256']}
    for item in inventory:
        if item['kind']=='DATA_SYMBOL':continue
        seg=item['segment'];ns=n['segments'][seg-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
        start=item['offset'];limit=item['next_symbol_upper_bound']
        e=extent(code,start,limit)
        solved=cfg.get('functions',{}).get(item['name'])
        if solved and (solved['end'] is not None or solved['status'] in ('SHARED_TAIL','OVERLAPPING_ENTRY','AMBIGUOUS_TABLE')):e=solved.copy()
        recipe=recipes.get(item['name']);rows=disassemble(code,start,e['end'] or limit,seg,n,s)
        calls=[r for row in rows if 'call' in row['mnemonic'] for r in row['references']]
        globals_=[r for row in rows for r in row['references'] if r['kind']=='global_ds_assumed']
        if recipe and e['size']==recipe['size']:e['status']='CONFIRMED';e['review']=recipe['extent_evidence']
        card={**provenance,'symbol':item['name'],'segment':seg,'segment_name':item['segment_name'],
             'offset':start,'ownership':item['ownership'],'ownership_confidence':item['ownership_confidence'],
             'extent':e,'calls':calls,'globals':globals_,'incoming_references':[],
             'disassembly':rows,'source':recipe['source'] if recipe else None,'compiler_flags':recipe['flags'] if recipe else None,
             'known_fixups':[dict(r,sites=[p for p in r['sites'] if start<=p<limit]) for r in ns['relocations'] if any(start<=p<limit for p in r['sites'])],
             'proof':recipe.get('proof','SEMANTIC_CANDIDATE') if recipe else 'DISASSEMBLED',
             'blockers':[] if recipe else ['SOURCE_NOT_RECOVERED']+drafts.get(item['name'],{}).get('blockers',[])+([] if e['end'] else ['EXTENT_UNKNOWN'])}
        if not recipe and item['name'] in drafts:
            card.update(draft_source=drafts[item['name']]['source'],blocker_evidence='evidence/recovery/blockers.json')
        reuse=[m for m in runtime if any(c['segment']==seg and c['offset']<=start<c['offset']+c['size'] for c in m['code_ranges'])]
        if reuse:
            card.update(ownership='HISTORICAL_LIBRARY',ownership_confidence=reuse[0]['status'],proof='COMPLETE_MEMBER_MATCH',blockers=[],runtime_members=reuse,reconstruction_scope='EXCLUDED_REUSE_OBJECT')
        cards.append(card)
    by_address={(c['segment'],c['offset']):c for c in cards}
    for c in cards:
        for ref in c['calls']:
            dest=by_address.get((ref.get('segment'),ref.get('offset')))
            if dest:dest['incoming_references'].append({'symbol':c['symbol'],'segment':c['segment'],'offset':c['offset']})
    out=ROOT/'evidence/disassembly'
    (out/'cards.jsonl').write_text(''.join(json.dumps(c,sort_keys=True)+'\n' for c in cards),encoding='utf8')
    texts=[]
    for c in cards:
        text=[f"## {c['symbol']} — {c['segment_name']}:{c['offset']:04X}",
              f"Ownership: {c['ownership']} ({c['ownership_confidence']}). Extent: {c['extent']['status']}, {c['extent']['size']} bytes.",
              f"Source: {c['source'] or 'unrecovered'}. Flags: {c['compiler_flags'] or 'unresolved'}.",'','```asm']
        for row in c['disassembly']:
            labels=[name for r in row['references'] for name in r.get('names',[])]
            text.append(f"{row['offset']:04X}  {row['bytes']:<24} {row['mnemonic']} {row['operands']}"+(' ; '+', '.join(labels) if labels else ''))
        text.extend(['```','']);texts.append('\n'.join(text))
    (out/'cards.md').write_text('# Generated symbol cards\n\nFixture EXE SHA-256: '+provenance['exe_sha256']+'\n\nLinear decoding can include embedded data where extents remain unresolved. DS global labels assume the normal DGROUP context.\n\n'+'\n'.join(texts),encoding='utf8')
    frontier=sorted([{'symbol':c['symbol'],'segment':c['segment_name'],'offset':c['offset'],'size':c['extent']['size'],
                      'extent_status':c['extent']['status'],'ownership':c['ownership'],'source':c['source'],'blockers':c['blockers']}
                     for c in cards if c['ownership']=='GAME'],key=lambda c:(bool(c['source']),c['size'] is None,c['size'] or 65536,c['segment'],c['offset']))
    write_json(ROOT/'docs/frontier.json',dict(provenance,functions=frontier))
    write_json(out/'summary.json',dict(provenance,cards=len(cards),extent_status_counts=dict(Counter(c['extent']['status'] for c in cards))))
    print(f'Generated {len(cards)} symbol cards and {len(frontier)} game frontier entries')

if __name__=='__main__':main()
