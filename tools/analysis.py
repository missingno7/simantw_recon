"""Conservative 16-bit control flow and symbol-aware research disassembly."""
import sys
from common import ROOT, FormatError
sys.path.insert(0,str(ROOT/'toolchain/analysis'))
try:
    import capstone as cs
    from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_DS, X86_REG_INVALID
except ImportError as e:
    raise FormatError('Install capstone==5.0.6 into toolchain/analysis (see README)') from e

def decoder():
    d=cs.Cs(cs.CS_ARCH_X86,cs.CS_MODE_16);d.detail=True;return d

def extent(code,start,limit):
    """Next symbol is only a hard upper bound. Traverse both conditional arms.

    A closed, contiguous graph with a reachable RET is PROBABLE, not automatically
    a historical function proof. Manifest review promotes selected extents.
    """
    d=decoder();pending=[start];seen={};returns=[];reasons=[]
    while pending:
        pos=pending.pop()
        if pos in seen:continue
        if not start<=pos<limit:reasons.append('control flow escapes symbol bound');continue
        ins=next(d.disasm(code[pos:min(limit,pos+15)],pos,count=1),None)
        if ins is None:reasons.append('undecodable instruction');continue
        seen[pos]=ins
        if ins.group(cs.CS_GRP_RET):returns.append(pos);continue
        if ins.mnemonic in ('int','int3','iret','iretw','hlt'):reasons.append('interrupt or non-return terminator');continue
        if ins.group(cs.CS_GRP_JUMP):
            if len(ins.operands)!=1 or ins.operands[0].type!=X86_OP_IMM:
                reasons.append('indirect/far jump');continue
            pending.append(ins.operands[0].imm)
            if ins.mnemonic=='jmp':continue
        pending.append(pos+ins.size)
    ordered=sorted(seen.values(),key=lambda i:i.address)
    end=start
    for i in ordered:
        if i.address!=end:reasons.append('gap or overlapping instruction stream')
        end=max(end,i.address+i.size)
    if not returns:reasons.append('no reachable return')
    return {'status':'PROBABLE' if not reasons else 'SYMBOL_ONLY_START','start':start,
            'end':end if not reasons else None,'size':end-start if not reasons else None,
            'upper_bound':limit,'return_offsets':returns,'reasons':sorted(set(reasons))}

def disassemble(code,start,end,segment,ne,symbols,tables=()):
    """Instruction rows for [start,end). Proven switch jump tables (from the
    CFG solver) are emitted as `dw` data rows so the bytes stay complete
    without decoding table words as instructions."""
    names={}
    for s in symbols['segments']:
        for x in s['symbols']:names.setdefault((s['number'],x['offset']),[]).append(x['name'])
    relocs={site:r for r in ne['segments'][segment-1]['relocations'] for site in r['sites']}
    rows=[];spans=sorted((t['table'],t['table']+2*t['count']) for t in tables if start<=t['table'] and t['table']+2*t['count']<=end)
    instructions=[];cursor=start
    for a,b in spans+[(end,end)]:
        instructions+=list(decoder().disasm(code[cursor:a],cursor))
        for pos in range(a,b,2):
            target=int.from_bytes(code[pos:pos+2],'little')
            rows.append({'offset':pos,'bytes':code[pos:pos+2].hex(),'mnemonic':'dw','operands':f'offset {target:#x}','references':[{'kind':'jump_table_entry','segment':segment,'offset':target,'names':[]}]})
        cursor=b
    for i in instructions:
        refs=[]
        operand_text=i.op_str
        for pos in range(i.address,i.address+i.size):
            if pos in relocs:
                r=relocs[pos];t=dict(r['target'])
                if t['kind']=='internal' and r['source_type']==2 and i.mnemonic=='lcall':
                    t['offset']=int.from_bytes(code[i.address+1:i.address+3],'little')
                t['names']=names.get((t.get('segment'),t.get('offset')),[]);refs.append(t)
        if i.group(cs.CS_GRP_CALL) and i.mnemonic=='call' and i.operands[0].type==X86_OP_IMM:
            # Capstone reports a linear target when the relative displacement
            # crosses the end of a 16-bit code segment. The CPU wraps IP.
            target=i.operands[0].imm & 0xffff
            refs.append({'kind':'near_call','segment':segment,'offset':target,'names':names.get((segment,target),[])})
            if target!=i.operands[0].imm:operand_text=f'{target:#x}'
        for op in i.operands:
            if op.type==X86_OP_MEM and op.mem.base==0 and op.mem.index==0 and op.mem.segment in (X86_REG_INVALID,X86_REG_DS):
                address=op.mem.disp&65535
                if (10,address) in names:refs.append({'kind':'global_ds_assumed','segment':10,'offset':address,'names':names[10,address]})
        rows.append({'offset':i.address,'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':operand_text,'references':refs})
    rows.sort(key=lambda r:r['offset']);return rows
