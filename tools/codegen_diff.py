"""Instruction diagnostics for search. Never used as an acceptance oracle."""
from collections import Counter
from difflib import SequenceMatcher
from analysis import decoder,cs
from cfg_solver import solve
from matcher import unique_symbol


def instructions(code,bindings=None,tables=(),base=0):
    """Instruction rows; proven switch jump tables (relative span, entry
    count) become `dw` rows whose operand is the case target relative to the
    function start `base` (a bound word uses its resolved fixup target)."""
    bindings=bindings or {};rows=[];decoded=[];cursor=0
    for a,count in sorted(tables):
        decoded+=list(decoder().disasm(code[cursor:a],cursor))
        for pos in range(a,a+2*count,2):
            bound=[b for p,b in bindings.items() if pos<=p<pos+2 and isinstance(b,dict) and b.get('kind')=='internal']
            value=(bound[0]['offset'] if bound else int.from_bytes(code[pos:pos+2],'little'))-base
            rows.append(dict(offset=pos,size=2,mnemonic='dw',asm=f'dw offset {value:#x}',operands=[dict(kind='branch',size=2,value=value)],jump=False,ret=False))
        cursor=a+2*count
    decoded+=list(decoder().disasm(code[cursor:],cursor))
    for ins in decoded:
        local=[(p-ins.address,b) for p,b in bindings.items() if ins.address<=p<ins.address+ins.size]
        operands=[]
        for op in ins.operands:
            if op.type==cs.x86.X86_OP_REG:value=dict(kind='reg',size=op.size,register=ins.reg_name(op.reg))
            elif op.type==cs.x86.X86_OP_IMM:
                isbranch=ins.group(cs.CS_GRP_JUMP)
                value=dict(kind='branch' if isbranch else 'imm',size=op.size,value=op.imm)
                if local and not isbranch:value['value']={'binding':[b for _,b in local]}
            elif op.type==cs.x86.X86_OP_MEM:
                mem=op.mem;value=dict(kind='mem',size=op.size,base=ins.reg_name(mem.base),index=ins.reg_name(mem.index),segment=ins.reg_name(mem.segment),scale=mem.scale,displacement=mem.disp)
                if local:value['displacement']={'binding':[b for _,b in local]}
            else:value=dict(kind='unknown',size=op.size)
            operands.append(value)
        rows.append(dict(offset=ins.address,size=ins.size,mnemonic=ins.mnemonic,asm=ins.mnemonic+' '+('<resolved fixup> '+str([b for _,b in local]) if local else ins.op_str),operands=operands,jump=ins.group(cs.CS_GRP_JUMP),ret=ins.group(cs.CS_GRP_RET)))
    rows.sort(key=lambda r:r['offset']);return rows


def structure(row):return row['mnemonic'],tuple((op['kind'],op['size']) for op in row['operands'])
SEGMENT_REGISTERS={'cs','ds','es','ss','fs','gs'}
def without_registers(row):
    # Segment registers carry a selector, not an interchangeable value in a
    # general-purpose register.  Preserve their class and identity here.
    return [dict(op,**{k:('SEGMENT:'+op[k] if op[k] in SEGMENT_REGISTERS else 'REGISTER')
                       for k in ['register','base','index','segment'] if k in op and op[k]})
            for op in row['operands']]

def blocks(rows):
    if not rows:return []
    addresses={r['offset'] for r in rows};end=rows[-1]['offset']+rows[-1]['size'];leaders={0}
    for row in rows:
        if row['jump']:
            leaders.update(op['value'] for op in row['operands'] if op['kind']=='branch' and op['value'] in addresses)
        if row['jump'] or row['ret']:
            if row['offset']+row['size'] in addresses:leaders.add(row['offset']+row['size'])
    starts=sorted(leaders);result=[]
    for i,start in enumerate(starts):
        stop=starts[i+1] if i+1<len(starts) else end;part=[r for r in rows if start<=r['offset']<stop];last=part[-1];successors=[]
        if last['jump']:
            for op in last['operands']:
                if op['kind']=='branch':successors.append(starts.index(op['value']) if op['value'] in starts else 'EXTERNAL_OR_UNKNOWN')
        if not last['ret'] and last['mnemonic'] not in ('jmp','ljmp') and i+1<len(starts):successors.append(i+1)
        result.append(dict(id=i,start=start,end=stop,terminal='return' if last['ret'] else 'branch' if last['jump'] else 'flow',successors=successors))
    return result


def compare_code(target,candidate,target_bindings=None,candidate_bindings=None,closure=None,target_tables=(),candidate_tables=(),base=0):
    left=instructions(target,target_bindings,target_tables,base);right=instructions(candidate,candidate_bindings,candidate_tables,base);a=[structure(r) for r in left];b=[structure(r) for r in right]
    align=[]
    for tag,i,j,k,l in SequenceMatcher(a=a,b=b,autojunk=False).get_opcodes():
        for n in range(max(j-i,l-k)):align.append((left[i+n] if i+n<j else None,right[k+n] if k+n<l else None))
    counters=dict(opcode_matches=0,register_only_differences=0,immediate_differences=0,memory_operand_differences=0,branch_target_differences=0,stack_local_differences=0);first=None;display=[]
    left_ord={r['offset']:i for i,r in enumerate(left)};right_ord={r['offset']:i for i,r in enumerate(right)}
    for x,y in align:
        changes=[]
        if x is None or y is None or structure(x)!=structure(y):
            changes.append('instruction_shape')
            if first is None:first=dict(target_offset=x['offset'] if x else None,candidate_offset=y['offset'] if y else None)
        else:
            counters['opcode_matches']+=1
            if x['operands']!=y['operands'] and without_registers(x)==without_registers(y):counters['register_only_differences']+=1;changes.append('register_allocation')
            else:
                for p,q in zip(x['operands'],y['operands']):
                    if p==q:continue
                    if p['kind']==q['kind']=='reg' and p['register']!=q['register']:
                        changes.append('call_frame_or_segment_register' if p['register'] in SEGMENT_REGISTERS or q['register'] in SEGMENT_REGISTERS else 'register_role')
                        continue
                    if p['kind']=='imm':counters['immediate_differences']+=1;changes.append('immediate_or_binding')
                    elif p['kind']=='branch':
                        if left_ord.get(p['value'],p['value'])!=right_ord.get(q['value'],q['value']):counters['branch_target_differences']+=1;changes.append('branch_target')
                    elif p['kind']=='mem':
                        counters['memory_operand_differences']+=1;changes.append('memory_operand')
                        if p['base']==q['base']=='bp' and p['displacement']!=q['displacement']:counters['stack_local_differences']+=1;changes.append('stack_local_layout')
        display.append(dict(target_offset=x['offset'] if x else None,target=x['asm'] if x else '',candidate_offset=y['offset'] if y else None,candidate=y['asm'] if y else '',differences=changes))
    structural={i for i,row in enumerate(display) if 'instruction_shape' in row['differences']}
    for i,row in enumerate(display):
        if (set(row['differences']) & {'register_allocation','call_frame_or_segment_register'}
                and any(abs(i-j)<=2 for j in structural)):
            row['differences'].append('alignment_uncertain')
    lb,rb=blocks(left),blocks(right);graph=lambda bb:[(r['terminal'],r['successors']) for r in bb]
    closure=closure or [solve(code,0,len(code)) for code in (target,candidate)]
    known=all(r['end'] is not None and r['status']=='PROBABLE' for r in closure)
    graph_match=graph(lb)==graph(rb) if known else None
    ordering=a!=b and Counter(a)==Counter(b)
    categories=[]
    if graph_match is False:categories.append('CONTROL_FLOW')
    if first:categories.append('INSTRUCTION_ORDER' if ordering else 'EXPRESSION_SHAPE')
    if counters['register_only_differences']:categories.append('REGISTER_ALLOCATION')
    if any('call_frame_or_segment_register' in r['differences'] for r in display):categories.append('CALL_FRAME_OR_SEGMENT_REGISTER')
    if any('alignment_uncertain' in r['differences'] for r in display):categories.append('ALIGNMENT_UNCERTAIN')
    if counters['stack_local_differences']:categories.append('LOCAL_FRAME_LAYOUT')
    if counters['memory_operand_differences']:categories.append('MEMORY_OPERAND')
    if counters['immediate_differences']:categories.append('IMMEDIATE_OR_BINDING')
    if counters['branch_target_differences']:categories.append('BRANCH_TARGET')
    total=max(len(left),len(right),1);equal=sum(not r['differences'] for r in display)
    return dict(target_bytes=len(target),candidate_bytes=len(candidate),instruction_layout_match=[(r['offset'],r['size']) for r in left]==[(r['offset'],r['size']) for r in right],cfg_shape_match=graph_match,opcode_total=max(len(left),len(right)),**counters,first_structural_difference=first,categories=categories,score=round((equal+.5*(counters['opcode_matches']-equal))/total,6),aligned_asm=display,target_blocks=lb,candidate_blocks=rb,scope='SEARCH_DIAGNOSTIC_ONLY; semantic equivalence and recovery acceptance are not inferred from this score')


def unresolved_member_obligations(comparison, image):
    """Expose whole-member failures even when the instruction body aligns."""
    failures=[]
    for contribution in comparison.get('contributions', []):
        failed=[]
        segment=contribution['original_segment']
        base=contribution['original_offset']
        for fixup in contribution['fixups']:
            if fixup['equal']:
                continue
            offset=fixup['offset'];width=fixup['omf']['width']
            loaders=[dict(site=site,source_type=r['source_type'],target=r['target'],
                          additive=r.get('additive',False))
                     for r in image['segments'][segment-1]['relocations']
                     for site in r['sites'] if base+offset<=site<base+offset+width]
            failed.append(dict(offset=offset,candidate_target=fixup['target'] or fixup['omf']['target'],
                               original_loader_bindings=loaders,reason=fixup['reason']))
        compared=contribution.get('literal_compared');equal=contribution.get('literal_equal')
        different=compared-equal if compared is not None and equal is not None else None
        if failed or different != 0:
            failures.append(dict(segment=contribution.get('segment','UNKNOWN'),original_segment=segment,
                                 original_offset=base,literal_differences=different,failed_fixups=failed))
    return dict(strict_member_result=comparison['result'],issues=comparison.get('issues',[]),
                contributions=failures,
                scope='Whole-member obligations; instruction alignment does not discharge private data or selector failures')


def diagnose(module,raw,image,symbols,symbol,comparison):
    segment,start=unique_symbol(symbols,symbol);ns=image['segments'][segment-1];data=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
    upper=min([p['offset'] for p in symbols['segments'][segment-1]['symbols'] if p['offset']>start]+[len(data)])
    extent=solve(data,start,upper,relocations=ns['relocations'],segment=segment);end=extent['end'] or upper
    pub=next(p for p in module['publics'] if p['name']==symbol);ss=module['segments'][pub['segment']-1];code=bytes.fromhex(ss['data_hex']);begin=pub['offset']
    limit=min([p['offset'] for p in module['publics'] if p['segment']==pub['segment'] and p['offset']>begin]+[len(code)])
    ce=solve(code,begin,limit);stop=ce['end'] or limit
    tb={site-start:r['target'] for r in ns['relocations'] for site in r['sites'] if start<=site<end};cb={}
    for contribution in comparison.get('contributions',[]):
        for fixup in contribution['fixups']:
            f=fixup['omf']
            if f['segment']!=pub['segment'] or not begin<=f['offset']<stop:continue
            value=fixup['target'] or f['target'];cb[f['offset']-begin]=value
            if fixup['equal']:
                original=contribution['original_offset']+f['offset']-start
                for p in list(tb):
                    if original<=p<original+f['width']:tb.pop(p)
                tb[original]=value
    # Normalize only linker transformations already proven by the strict
    # matcher, in a separate diagnostic view. Never modify the OMF object.
    view=bytearray(code[begin:stop]);normalizations=[]
    for contribution in comparison.get('contributions',[]):
        if contribution['original_segment']!=segment or contribution['original_offset']+begin!=start:continue
        for transform in contribution['transformations']:
            pos=transform['offset']-begin
            if not 0<=pos<=len(view)-5:continue
            dest=transform['target']['offset'];base=contribution['original_offset'];absolute=transform['offset']
            if view[pos]==0x9a:linked=b'\x90\x0e\xe8'+((dest-(base+absolute+5))&65535).to_bytes(2,'little')
            elif view[pos]==0xea:linked=b'\xe9'+((dest-(base+absolute+3))&65535).to_bytes(2,'little')+b'\x90\x90'
            else:continue
            view[pos:pos+5]=linked
            for bindings in [tb,cb]:
                for site in list(bindings):
                    if pos<=site<pos+5:bindings.pop(site)
            normalizations.append(dict(offset=pos,reason='Strictly validated LINK far-call/jump translation'))
    # Jump tables proven by the CFG solver on both sides: their words are
    # compared as case targets relative to the function, not as opcodes.
    target_tables=[(x['table']-start,x['count']) for x in extent.get('jump_tables',[])]
    candidate_tables=[(x['table']-begin,x['count']) for x in ce.get('jump_tables',[])]
    result=compare_code(data[start:end],bytes(view),tb,cb,closure=[extent,ce],target_tables=target_tables,candidate_tables=candidate_tables,base=start)
    result['diagnostic_normalizations']=normalizations
    result['unresolved_member_obligations']=unresolved_member_obligations(comparison,image)
    result.update(exact_match=comparison['result'] in ('CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER') and extent['size'] is not None and extent['size']==ce['size'],strict_member_result=comparison['result'],fixups_equal=comparison.get('fixups_equal'),fixups_total=comparison.get('fixups_total'),extent_known=extent['end'] is not None,contribution_bytes=ss['length'],linker_transformations=[t for c in comparison.get('contributions',[]) for t in c['transformations']])
    return result


def render(result,limit=100):
    obligations=result.get('unresolved_member_obligations',{})
    lines=[]
    if obligations.get('issues'):
        lines.append('Whole-member issues: '+'; '.join(obligations['issues']))
        for contribution in obligations.get('contributions',[]):
            for fixup in contribution['failed_fixups']:
                lines.append('  '+contribution['segment']+'+'+hex(fixup['offset'])+': candidate '+str(fixup['candidate_target'])+'; original loader '+str(fixup['original_loader_bindings']))
    lines.append('Target | Candidate | Difference')
    for row in result['aligned_asm'][:limit]:
        left=('%04x '%row['target_offset']+row['target']) if row['target_offset'] is not None else ''
        right=('%04x '%row['candidate_offset']+row['candidate']) if row['candidate_offset'] is not None else ''
        lines.append(left+' | '+right+' | '+','.join(row['differences']))
    if len(result['aligned_asm'])>limit:lines.append('... see structured diagnostic for remaining instructions')
    return '\n'.join(lines)+'\n'
