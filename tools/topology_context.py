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
    return result + far_data_bindings(card,symbols,image)


def far_data_bindings(card, symbols, image):
    """Local ES evidence only; no CFG, object-boundary or placement proof."""
    instructions = [ins for row in card['disassembly']
                    for ins in decoder().disasm(bytes.fromhex(row['bytes']), row['offset'])]
    # A branch may enter after the selector load. Never carry evidence over it.
    entries = {op.imm for ins in instructions if ins.group(cs.CS_GRP_JUMP)
               for op in ins.operands if op.type == cs.x86.X86_OP_IMM}
    selectors = {site: r['target'] for r in image['segments'][9]['relocations']
                 if r['source_type'] == 2 and not r.get('additive', False)
                 and r['target'].get('kind') == 'internal'
                 and r['target'].get('offset') == 0 for site in r['sites']}
    names = {(i + 1, symbol['offset']): [] for i, segment in enumerate(symbols['segments'])
             for symbol in segment.get('symbols', [])}
    for i, segment in enumerate(symbols['segments']):
        for symbol in segment.get('symbols', []):
            names[(i + 1, symbol['offset'])].append(symbol['name'])
    result = []
    selector = None
    previous_end = None
    for ins in instructions:
        if ins.address != previous_end or ins.address in entries:
            selector = None
        if selector:
            slot, target, load = selector
            for operand in ins.operands:
                if operand.type != cs.x86.X86_OP_MEM or ins.reg_name(operand.mem.segment) != 'es':
                    continue
                mem = operand.mem
                address = mem.disp & 65535
                exact = names.get((target['segment'], address), [])
                result.append(dict(instruction=ins.address, operand=ins.op_str,
                    observed_displacement=address, exact_mapsym_names=exact,
                    selector_loader_target=target, selector_slot=slot,
                    selector_load_instruction=load, addressed_segment=target['segment'],
                    index_registers=[ins.reg_name(r) for r in (mem.base, mem.index) if r],
                    frame_assumption='Local ES load from an NE selector slot; assumes DS=DGROUP and no unlisted incoming entry',
                    scope='Far operand evidence only; indexed displacement names do not establish bounds or object size'))
        # Inspect reads before invalidating LES or another write to ES.
        _, writes = ins.regs_access()
        if (ins.mnemonic in ('les', 'lds')
                or any(ins.reg_name(reg) in ('es', 'ds') for reg in writes)):
            selector = None
        if ins.mnemonic == 'mov' and len(ins.operands) == 2:
            dest, source = ins.operands
            if (dest.type == cs.x86.X86_OP_REG and ins.reg_name(dest.reg) == 'es'
                    and source.type == cs.x86.X86_OP_MEM
                    and not source.mem.base and not source.mem.index
                    and ins.reg_name(source.mem.segment) in (None, '', 'ds')):
                slot = source.mem.disp & 65535
                if slot in selectors:
                    selector = (slot, selectors[slot], ins.address)
        if (any(ins.group(group) for group in (cs.CS_GRP_CALL, cs.CS_GRP_JUMP, cs.CS_GRP_RET))
                or ins.mnemonic.startswith(('int', 'iret'))):
            selector = None
        previous_end = ins.address + ins.size
    return result
