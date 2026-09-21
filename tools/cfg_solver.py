"""Recursive CFG evidence, independent of exact-recovery extent approval.

Alignment holes are retained explicitly. NE chain words are never decoded as
call addresses. Unknown indirect jumps are AMBIGUOUS_TABLE, not guessed tables.
"""
from collections import defaultdict, Counter
from common import ROOT, fixture, read_json, write_json
from analysis import decoder, cs, X86_OP_IMM
import ne, mapsym

def switch_table(ins,chain,seen,code,start,limit,relocation_bytes):
    """Recognise the MSC 7 switch dispatch `cmp r,N ; ja default ; shl r,1 ;
    xchg bx,r|mov bx,r ; jmp word ptr cs:[bx+T]` and return its table.

    The table holds N+1 (`ja`) or N (`jae`/`jnb`) near code offsets stored
    directly after the jump (up to two alignment NOPs allowed). Every entry must lie
    inside the symbol bound and no table byte may carry a loader obligation.
    Anything else stays an unresolved indirect jump.
    """
    if ins.mnemonic!='jmp' or len(ins.operands)!=1 or ins.operands[0].type!=cs.x86.X86_OP_MEM:return None
    mem=ins.operands[0].mem
    if ins.reg_name(mem.segment)!='cs' or ins.reg_name(mem.base)!='bx' or mem.index:return None
    table=mem.disp&65535
    after=ins.address+ins.size
    if not (after<=table<=after+2 and all(b==0x90 for b in code[after:table])):return None
    # Walk backwards through the fall-through chain: index move, shift, then
    # the bound check. The shift may also be reached by the taken arm of
    # `jbe/jb` (`cmp ; jbe shift ; jmp default ; shift:`).
    back=[];pos=ins.address
    for _ in range(3):
        pos=chain.get(pos)
        if pos is None:break
        back.append(seen[pos])
    text=[(i.mnemonic,i.op_str) for i in back]
    if len(text)<2:return None
    prescaled=False
    if text[0] in (('xchg','bx, ax'),('xchg','ax, bx'),('mov','bx, ax')) and text[1]==('shl','ax, 1'):shift=back[1]
    elif text[0]==('shl','bx, 1'):shift=back[0]
    elif text[0] in (('xchg','bx, ax'),('xchg','ax, bx'),('mov','bx, ax')) and text[1][0] in ('ja','jae','jnb'):
        # Strength-reduced form: `and ax,M ; shr ax,k` already yields the
        # doubled index, so the bound is checked on even values and no
        # shift precedes the move. Only admitted when the mask proves that
        # every reachable index is even.
        shift=back[0];prescaled=True
    else:return None
    # Predecessor of the shift: fall-through, or a conditional branch targeting it.
    pred=chain.get(shift.address)
    branch=seen.get(pred) if pred is not None else None
    if branch is not None and branch.mnemonic=='mov' and branch.op_str.startswith('ax, '):
        pred=chain.get(branch.address);branch=seen.get(pred) if pred is not None else None
    if branch is None or branch.mnemonic not in ('ja','jae','jnb'):
        branch=next((i for i in seen.values() if i.mnemonic in ('jbe','jb','jna','jnae') and len(i.operands)==1 and i.operands[0].type==X86_OP_IMM and i.operands[0].imm==shift.address),None)
        if branch is None:return None
    cmp_pos=chain.get(branch.address)
    cmp_ins=seen.get(cmp_pos) if cmp_pos is not None else None
    if cmp_ins is None or cmp_ins.mnemonic!='cmp' or len(cmp_ins.operands)!=2 or cmp_ins.operands[1].type!=X86_OP_IMM:return None
    bound=cmp_ins.operands[1].imm
    count=bound+1 if branch.mnemonic in ('ja','jbe','jna') else bound
    if prescaled:
        pos=chain.get(cmp_ins.address);shr=seen.get(pos) if pos is not None else None
        if shr is None or shr.mnemonic!='shr' or not shr.op_str.startswith('ax, ') or shr.operands[1].type!=X86_OP_IMM:return None
        k=shr.operands[1].imm;mask=None
        for _ in range(4):
            pos=chain.get(pos)
            if pos is None:break
            prev=seen[pos]
            if prev.mnemonic=='and' and prev.op_str.startswith('ax, ') and prev.operands[1].type==X86_OP_IMM:mask=prev.operands[1].imm;break
            if prev.mnemonic not in ('test','cmp') and not prev.group(cs.CS_GRP_JUMP):break
        if mask is None or (mask>>k)&1 or bound%2 or branch.mnemonic not in ('ja','jbe','jna'):return None
        count=bound//2+1
    if not 1<=count<=256 or table+2*count>limit:return None
    if any(p in relocation_bytes for p in range(table,table+2*count)):return None
    targets=[int.from_bytes(code[table+2*i:table+2*i+2],'little') for i in range(count)]
    if any(not start<=t<limit for t in targets):return None
    return dict(source=ins.address,table=table,count=count,targets=targets,bound_check=cmp_ins.address)

def solve(code,start,limit,entries=(),relocations=(),segment=None):
    pending=[start];seen={};edges=[];returns=[];issues=[];indirect=[];occupied={};chain={};tables=[]
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
            found=switch_table(ins,chain,seen,code,start,limit,relocation_bytes)
            if found:
                if any(p in occupied for p in range(found['table'],found['table']+2*found['count'])):
                    issues.append('overlapping instruction streams');continue
                for p in range(found['table'],found['table']+2*found['count']):occupied[p]='table'
                tables.append(found)
                for t in found['targets']:
                    edges.append(dict(source=pos,target=t,kind='TABLE'));pending.append(t)
                continue
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
        chain[pos+ins.size]=pos
        pending.append(pos+ins.size)
    end=max([i.address+i.size for i in seen.values()]+[t['table']+2*t['count'] for t in tables],default=start)
    gaps=[];pos=start
    table_spans={(t['table'],t['table']+2*t['count']) for t in tables}
    for ins in sorted(seen.values(),key=lambda i:i.address):
        if pos<ins.address:
            data=code[pos:ins.address]
            # Only unreachable NOP padding without loader obligations is resolved.
            padding=all(b==0x90 for b in data) and not any(p in relocation_bytes for p in range(pos,ins.address))
            inside=[(a,b) for a,b in table_spans if pos<=a and b<=ins.address]
            remainder=[code[q:q+1] for q in range(pos,ins.address) if not any(a<=q<b for a,b in inside)]
            table_gap=bool(inside) and all(x==b'\x90' for x in remainder) and not any(p in relocation_bytes for p in range(pos,ins.address))
            if table_gap:classification='JUMP_TABLE'
            elif padding:classification='ALIGNMENT_NOP'
            else:classification='UNOWNED'
            gaps.append(dict(start=pos,end=ins.address,hex=data.hex(),classification=classification))
        pos=ins.address+ins.size
    for a,b in table_spans:
        if a>=pos:gaps.append(dict(start=a,end=b,hex=code[a:b].hex(),classification='JUMP_TABLE'))
    cross=[e for e in edges if e['kind']=='CROSS_BOUNDARY']
    overlapping=[p for p in entries if start<p<end]
    closed=bool(returns) and not issues and not indirect and not cross and all(g['classification'] in ('ALIGNMENT_NOP','JUMP_TABLE') for g in gaps)
    status='OVERLAPPING_ENTRY' if overlapping or 'overlapping instruction streams' in issues else 'AMBIGUOUS_TABLE' if indirect else 'SHARED_TAIL' if cross else 'PROBABLE'
    if not closed and status=='PROBABLE':issues.append('graph not closed or unowned gap')
    return dict(status=status,start=start,end=end if closed else None,size=end-start if closed else None,
                upper_bound=limit,reachable_end=end,return_offsets=sorted(returns),edges=edges,
                gaps=gaps,indirect_jumps=indirect,jump_tables=tables,overlapping_entries=overlapping,reasons=sorted(set(issues)),
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
