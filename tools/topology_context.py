"""Expose direct data operands to the grinder without inventing private names."""
from analysis import decoder,cs


def direct_data_bindings(card,symbols,image):
    names={}
    for symbol in symbols['segments'][9]['symbols']:
        names.setdefault(symbol['offset'],[]).append(symbol['name'])
    selectors={site:r['target'] for r in image['segments'][9]['relocations']
               if r['source_type']==2 for site in r['sites']}
    result=[]
    for row in card['disassembly']:
        for ins in decoder().disasm(bytes.fromhex(row['bytes']),row['offset']):
            for operand in ins.operands:
                if operand.type!=cs.x86.X86_OP_MEM:continue
                mem=operand.mem
                if ins.reg_name(mem.base) in ('bp','sp') or ins.reg_name(mem.segment) not in (None,'','ds'):continue
                address=mem.disp & 65535
                if not address:continue
                result.append(dict(instruction=ins.address,operand=ins.op_str,
                    observed_displacement=address,exact_mapsym_names=names.get(address,[]),
                    selector_loader_target=selectors.get(address),
                    frame_assumption='Name lookup assumes DS=DGROUP; confirm segment-register liveness before declaring source',
                    scope='Operand evidence only; an unnamed offset does not prove a private object boundary'))
    return result
