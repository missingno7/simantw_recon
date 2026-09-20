"""Recursive CFG evidence, independent of exact-recovery extent approval.

Alignment holes are retained explicitly. NE chain words are never decoded as
call addresses. Unknown indirect jumps are AMBIGUOUS_TABLE, not guessed tables.
"""
from collections import defaultdict, Counter
from common import ROOT, fixture, read_json, write_json
from analysis import decoder, cs, X86_OP_IMM
import ne, mapsym

def solve(code,start,limit,entries=(),relocations=(),segment=None):
    pending=[start];seen={};edges=[];returns=[];issues=[];indirect=[];occupied={}
    entries=set(entries);relocation_bytes={p for r in relocations for q in r['sites'] for p in range(q,q+r['width'])}
    while pending:
        pos=pending.pop()
        if pos in seen:continue
        if not start<=pos<limit:
            edges.append(dict(target=pos,kind='CROSS_BOUNDARY'));continue
        if pos in occupied:
            issues.append('overlapping instruction streams');continue
        ins=next(decoder().disasm(code[pos:min(pos+15,limit)],pos,count=1),None)
        if ins is None:issues.append('undecodable instruction');continue
        if any(p in occupied for p in range(pos,pos+ins.size)):
            issues.append('overlapping instruction streams');continue
        seen[pos]=ins
        for p in range(pos,pos+ins.size):occupied[p]=pos
        if ins.group(cs.CS_GRP_RET):returns.append(pos);continue
        if ins.mnemonic in ('int','int3','iret','iretw','hlt'):
            issues.append('non-return terminator');continue
        if ins.group(cs.CS_GRP_JUMP):
            if ins.mnemonic=='ljmp':
                relocation=next((r for r in relocations if pos+1 in r['sites'] or pos+3 in r['sites']),None)
                target=relocation.get('target',{}) if relocation else {}
                if target.get('kind')=='internal':
                    dest=target['offset'] if relocation['source_type']==3 else int.from_bytes(code[pos+1:pos+3],'little')
                    edge=dict(source=pos,target=dest,target_segment=target['segment'],kind='BRANCH' if target['segment']==segment else 'CROSS_BOUNDARY')
                    edges.append(edge)
                    if target['segment']==segment:pending.append(dest)
                    continue
            if len(ins.operands)!=1 or ins.operands[0].type!=X86_OP_IMM:
                indirect.append(pos);continue
            dest=ins.operands[0].imm
            edges.append(dict(source=pos,target=dest,kind='BRANCH'))
            pending.append(dest)
            if ins.mnemonic=='jmp':continue
        pending.append(pos+ins.size)
    end=max((i.address+i.size for i in seen.values()),default=start)
    gaps=[];pos=start
    for ins in sorted(seen.values(),key=lambda i:i.address):
        if pos<ins.address:
            data=code[pos:ins.address]
            # Only unreachable NOP padding without loader obligations is resolved.
            padding=all(b==0x90 for b in data) and not any(p in relocation_bytes for p in range(pos,ins.address))
            gaps.append(dict(start=pos,end=ins.address,hex=data.hex(),classification='ALIGNMENT_NOP' if padding else 'UNOWNED'))
        pos=ins.address+ins.size
    cross=[e for e in edges if e['kind']=='CROSS_BOUNDARY']
    overlapping=[p for p in entries if start<p<end]
    closed=bool(returns) and not issues and not indirect and not cross and all(g['classification']=='ALIGNMENT_NOP' for g in gaps)
    status='OVERLAPPING_ENTRY' if overlapping or 'overlapping instruction streams' in issues else 'AMBIGUOUS_TABLE' if indirect else 'SHARED_TAIL' if cross else 'PROBABLE'
    if not closed and status=='PROBABLE':issues.append('graph not closed or unowned gap')
    return dict(status=status,start=start,end=end if closed else None,size=end-start if closed else None,
                upper_bound=limit,reachable_end=end,return_offsets=sorted(returns),edges=edges,
                gaps=gaps,indirect_jumps=indirect,overlapping_entries=overlapping,reasons=sorted(set(issues)),
                instruction_starts=sorted(seen),proof='CFG_ONLY_NOT_RECOVERED_SOURCE')

def main():
    raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'))
    inventory=read_json(ROOT/'evidence/symbols/inventory.json')['symbols'];recipes=read_json(ROOT/'src/recovery.json')['targets']
    results={};owners=defaultdict(list);incoming=defaultdict(list)
    for x in inventory:
        if x['kind']=='DATA_SYMBOL':continue
        ns=n['segments'][x['segment']-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
        peers=[y['offset'] for y in s['segments'][x['segment']-1]['symbols']]
        r=solve(code,x['offset'],x['next_symbol_upper_bound'],peers,ns['relocations'],x['segment'])
        if x['name'] in recipes and r['size']==recipes[x['name']]['size']:r['status']='CONFIRMED'
        r.update(segment=x['segment'],symbol=x['name'])
        r['entry_aliases']=[y['name'] for y in s['segments'][x['segment']-1]['symbols'] if y['offset']==x['offset'] and y['name']!=x['name']]
        if r['entry_aliases'] and r['status']!='CONFIRMED':r['status']='OVERLAPPING_ENTRY'
        results[x['name']]=r
        for pos in r['instruction_starts']:owners[x['segment'],pos].append(x['name'])
        for edge in r['edges']:
            if edge.get('source') is not None:incoming[edge.get('target_segment',x['segment']),edge['target']].append(dict(symbol=x['name'],offset=edge['source']))
    for name,r in results.items():
        r['incoming_branches']=[dict(target=p,sources=incoming[r['segment'],p]) for p in r['instruction_starts'] if any(x['symbol']!=name for x in incoming[r['segment'],p])]
        if r['incoming_branches'] and r['status']!='CONFIRMED':r['status']='SHARED_TAIL'
    report=dict(exe_sha256=n['sha256'],sym_sha256=s['sha256'],status_counts=dict(Counter(r['status'] for r in results.values())),
                resolved_with_alignment_gaps=sum(r['end'] is not None and bool(r['gaps']) for r in results.values()),functions=results)
    write_json(ROOT/'evidence/disassembly/cfg-extents.json',report)
    print(report['status_counts'],'closed graphs with padding:',report['resolved_with_alignment_gaps'])

if __name__=='__main__':main()
