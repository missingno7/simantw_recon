"""Record bounded switch-dispatch hypotheses; never certify or change extents."""
from collections import Counter
from common import ROOT,fixture,read_json,write_json
from analysis import decoder,cs
import ne
import json


def generate():
    raw=fixture('SIMANTW.EXE');image=ne.parse(raw)
    cards={c['symbol']:c for c in map(json.loads,(ROOT/'evidence/disassembly/cards.jsonl').read_text().splitlines())}
    rows=[]
    for task in read_json(ROOT/'docs/production-queue.json')['functions']:
        if task['state']!='STRUCTURE_BLOCKED':continue
        c=cards[task['symbol']];e=c['extent'];ns=image['segments'][c['segment']-1]
        code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
        starts=e.get('instruction_starts',[])
        for address in e.get('indirect_jumps',[]):
            before=[p for p in starts if p<=address][-7:]
            instructions=[next(decoder().disasm(code[p:p+15],p,count=1)) for p in before]
            jump=instructions[-1];cmp=next((i for i in reversed(instructions[:-1]) if i.mnemonic=='cmp'),None)
            shape=[i.mnemonic for i in instructions]
            family='BYTE_OFFSET_TABLE_REQUIRES_PARITY_PROOF' if 'shr' in shape else 'UNRECOGNIZED_DISPATCH'
            if shape[-5:]==['cmp','ja','shl','xchg','jmp']:family='UNSIGNED_BOUND_DIRECT_DEFAULT'
            if shape[-6:]==['cmp','jbe','jmp','shl','xchg','jmp']:family='UNSIGNED_BOUND_LONG_DEFAULT'
            bound=cmp.operands[1].imm if cmp and len(cmp.operands)==2 and cmp.operands[1].type==cs.x86.X86_OP_IMM else None
            memory=jump.operands[0].mem if jump.operands and jump.operands[0].type==cs.x86.X86_OP_MEM else None
            base=(memory.disp & 65535) if memory else None
            count=(bound+1) if family.startswith('UNSIGNED_BOUND') and bound is not None and 0<=bound<=255 else None
            targets=[int.from_bytes(code[base+i*2:base+i*2+2],'little') for i in range(count)] if count and base is not None and base+count*2<=len(code) else []
            relocations=[site for r in ns['relocations'] for site in r['sites'] if count and base<=site<base+count*2]
            rows.append(dict(symbol=c['symbol'],segment=c['segment'],dispatch=address,family=family,
                window=[dict(offset=i.address,asm=i.mnemonic+' '+i.op_str) for i in instructions],
                table_base=base,hypothesized_entries=count,targets=targets,
                targets_within_public_bound=bool(targets) and all(c['offset']<=t<e['upper_bound'] for t in targets),
                loader_sites_in_table=relocations,status='HYPOTHESIS_NOT_CERTIFICATE',
                required_proof=['Guard dominates every dispatch entry','All table entries are true code boundaries outside embedded data','All paths close including other dispatches','No aliases, cross-entry tails or loader-chain words used as targets']))
    result=dict(schema_version=1,dispatch_count=len(rows),family_counts=dict(Counter(r['family'] for r in rows)),dispatches=rows,recovery_credit=0,structural_promotions=0)
    write_json(ROOT/'evidence/topology/structural-dispatch.json',result)
    print(result['family_counts'])
    return result


if __name__=='__main__':generate()
