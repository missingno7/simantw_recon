"""Expose direct data operands to the grinder without inventing private names."""
from analysis import decoder,cs


def ds_states(instructions):
    """Conservative local DS knowledge; never infer a value through a join."""
    entries={op.imm for ins in instructions if ins.group(cs.CS_GRP_JUMP)
             for op in ins.operands if op.type==cs.x86.X86_OP_IMM}
    state='ASSUMED_DGROUP';previous_end=None;states={}
    for ins in instructions:
        if previous_end is not None and (ins.address!=previous_end or ins.address in entries):
            state='UNKNOWN'
        states[ins.address]=state
        _,writes=ins.regs_access()
        if (ins.mnemonic=='lds' or ins.mnemonic=='pop' and ins.op_str.strip()=='ds'
                or any(ins.reg_name(reg)=='ds' for reg in writes)
                or any(ins.group(group) for group in (cs.CS_GRP_CALL,cs.CS_GRP_JUMP,cs.CS_GRP_RET))
                or ins.mnemonic.startswith(('int','iret'))):
            state='UNKNOWN'
        previous_end=ins.address+ins.size
    return states


def inside_public(address,starts,names,reach=64):
    """Nearest preceding DGROUP public within `reach` bytes: an element or field of it, or a private static placed after it."""
    import bisect
    i=bisect.bisect_right(starts,address)-1
    if i<0 or address-starts[i]>reach:return None
    return dict(names=names[starts[i]],offset=address-starts[i],
                hint='unnamed word %d bytes into a named public; check admitted sources that index it (e.g. name[%d] for a word array) before inventing a private static'
                     %(address-starts[i],(address-starts[i])//2))


def codegen_shape(card):
    """Entry/exit shapes MSC 7.00 C never produces: a hint that the original is assembly or inline _asm."""
    rows = card.get('disassembly') or []
    text = [('%s %s' % (r['mnemonic'], r['operands'])).strip() for r in rows]
    if text[:2] != ['push bp', 'mov bp, sp']:
        return None
    exits = [i for i, r in enumerate(rows) if r['mnemonic'] in ('ret', 'retf') and i]
    if exits and all(text[i - 1] == 'pop bp' for i in exits):
        return dict(shape='PUSH BP; MOV BP,SP ... POP BP without LEAVE',
                    hint='every admitted MSC 7.00 C function with this prologue exits through LEAVE; '
                         'this exit is a MASM PROC shape: the original is probably assembly (ask the supervisor for a GAME_ASM review)')
    return None


INTRINSIC_ONLY = ('repne scas', 'repe cmps')


def intrinsic_hint(card, profile_flags):
    """String-intrinsic fingerprints in the target while the object's profile lacks /Oi."""
    rows = ['%s %s' % (r['mnemonic'], r['operands']) for r in card.get('disassembly') or []]
    sites = sorted({r.split(' ')[0] + ' ' + r.split(' ')[1] for r in rows if r.startswith(INTRINSIC_ONLY)})
    copies = any(r.startswith('adc cx, cx') for r in rows) and any(r.startswith('rep movs') for r in rows)
    if copies:
        sites.append('rep movsw; adc cx, cx; rep movsb')
    optimise = next((f for f in profile_flags if f.startswith('/O')), '')
    if not sites or 'i' in optimise[2:]:
        return None
    return dict(fingerprints=sites, profile_optimisation=optimise,
                hint='these inline string sequences come only from /Oi intrinsics (strlen/strcat/strcmp/memcmp/memcpy) in admitted C, '
                     'but this object\'s profile has no /Oi: no source can reproduce them. Write the natural library calls, run '
                     'python tools/compiler_profiles.py probe SYMBOL --source FILE.c and ask the supervisor for a profile assignment')


def direct_data_bindings(card,symbols,image):
    names={}
    for symbol in symbols['segments'][9]['symbols']:
        names.setdefault(symbol['offset'],[]).append(symbol['name'])
    starts=sorted(names)
    selectors={site:r['target'] for r in image['segments'][9]['relocations']
               if r['source_type']==2 for site in r['sites']}
    result=[]
    decoded=[ins for row in card['disassembly'] if row.get('mnemonic')!='dw'
             for ins in decoder().disasm(bytes.fromhex(row['bytes']),row['offset'])]
    states=ds_states(decoded)
    for ins in decoded:
        for operand in ins.operands:
            if operand.type!=cs.x86.X86_OP_MEM:continue
            mem=operand.mem
            if ins.reg_name(mem.base) in ('bp','sp') or ins.reg_name(mem.segment) not in (None,'','ds'):continue
            address=mem.disp & 65535
            if not address:continue
            known=states[ins.address]=='ASSUMED_DGROUP'
            result.append(dict(instruction=ins.address,operand=ins.op_str,
                observed_displacement=address,exact_mapsym_names=names.get(address,[]) if known else [],
                possible_dgroup_names=[] if known else names.get(address,[]),
                inside_public=inside_public(address,starts,names) if not names.get(address) else None,
                selector_loader_target=selectors.get(address) if known else None,
                ds_state=states[ins.address],
                frame_assumption='Name lookup assumes DS=DGROUP only along the uninterrupted entry path; UNKNOWN after DS writes, calls or joins',
                scope='Operand evidence only; an unnamed offset does not prove a private object boundary'))
    return result + far_data_bindings(card,symbols,image,states=states)


def far_data_bindings(card, symbols, image, states=None):
    """Local ES evidence only; no CFG, object-boundary or placement proof."""
    instructions = [ins for row in card['disassembly'] if row.get('mnemonic') != 'dw'
                    for ins in decoder().disasm(bytes.fromhex(row['bytes']), row['offset'])]
    states=states or ds_states(instructions)
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
            slot, target, load, trusted = selector
            for operand in ins.operands:
                if operand.type != cs.x86.X86_OP_MEM or ins.reg_name(operand.mem.segment) != 'es':
                    continue
                mem = operand.mem
                address = mem.disp & 65535
                possible = names.get((target['segment'], address), [])
                result.append(dict(instruction=ins.address, operand=ins.op_str,
                    observed_displacement=address, exact_mapsym_names=possible if trusted else [],
                    possible_mapsym_names=[] if trusted else possible,
                    selector_loader_target=target if trusted else None,
                    possible_selector_loader_target=None if trusted else target,
                    selector_slot=slot if trusted else None,
                    observed_selector_offset=slot,
                    selector_load_instruction=load,
                    addressed_segment=target['segment'] if trusted else None,
                    possible_addressed_segment=None if trusted else target['segment'],
                    ds_state=states.get(load,'UNKNOWN'),
                    index_registers=[ins.reg_name(r) for r in (mem.base, mem.index) if r],
                    frame_assumption='Local ES load from an NE selector offset; exact target requires DS=DGROUP at the load',
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
                    selector = (slot, selectors[slot], ins.address,
                                states.get(ins.address)=='ASSUMED_DGROUP')
        if (any(ins.group(group) for group in (cs.CS_GRP_CALL, cs.CS_GRP_JUMP, cs.CS_GRP_RET))
                or ins.mnemonic.startswith(('int', 'iret'))):
            selector = None
        previous_end = ins.address + ins.size
    return result
