"""Attach established reconstruction rules to worker packets by observed triggers."""
from common import ROOT, read_json
import re

RULES = ROOT / 'layout/reconstruction-rules.json'


def triggers(card, packet=None):
    """Observed, semantics-free triggers for a target function."""
    packet = packet or {}
    found = {'always'}
    rows = card.get('disassembly', [])
    text = ' '.join(r['mnemonic'] + ' ' + r['operands'] for r in rows)
    if 'es:' in text or 'mov es,' in text or any(b.get('addressed_segment') for b in packet.get('direct_data_bindings', [])):
        found.add('far_data')
    if any(x in text for x in ('stos', 'movs', 'scas', 'lods', 'cmps')):
        found.add('string_ops')
    if any(r['mnemonic'] == 'dw' for r in rows):
        found.add('jump_table')
    if any(r['mnemonic'] == 'mov' and r['operands'].startswith(('si, word ptr [bp', 'di, word ptr [bp')) for r in rows):
        found.add('si_di_home')
    if any(r['mnemonic'] == 'mov' and r['operands'] in ('dx, 1', 'dx, 0') for r in rows):
        found.add('result_tail')
    call_names = {
        name
        for call in packet.get('calls', card.get('calls', []))
        for name in call.get('names', [])
    }
    cx_flag = (
        any(r['mnemonic'] == 'xor' and r['operands'] == 'cx, cx' for r in rows)
        and any(r['mnemonic'] == 'mov' and r['operands'] == 'cx, 1' for r in rows)
        and any(r['mnemonic'] == 'or' and r['operands'] == 'cx, cx' for r in rows)
    )
    if {'_IsValidA', '_GoInNest'} <= call_names and cx_flag:
        found.add('inline_hole_flag_join')
    if any(r['mnemonic'] in ('shl', 'sal') or (r['mnemonic'] == 'add' and r['operands'].split(', ')[0] == r['operands'].split(', ')[-1]) for r in rows) or '+ si' in text or '+ di' in text or '+ bx' in text:
        found.add('indexed_access')
    if any(b.get('exact_mapsym_names') == [] and b.get('observed_displacement', 0) >= 0x40 for b in packet.get('direct_data_bindings', [])):
        found.add('private_data')
    if any(c.get('kind') == 'near_call' for c in card.get('calls', [])) or any(c.get('segment') == card.get('segment') for c in card.get('calls', [])):
        found.add('same_segment_call')
    if packet.get('evidence_state') == 'BODY_MATCHED_BINDING_BLOCKED' or set(card.get('blockers', [])) & {'DATA_LAYOUT', 'PRIVATE_CONST_LAYOUT'}:
        found.add('body_matched')
    # Some ant routines do not mention the Dx8 symbol in the disassembly:
    # the linker has reduced each access to an ES selector slot plus a field
    # displacement.  Attach the shared-object rule only when named segment-8
    # list fields independently show that they reuse one selector slot.
    list_slots = {}
    for binding in packet.get('direct_data_bindings', []):
        if binding.get('addressed_segment') != 8 or binding.get('selector_slot') is None:
            continue
        for name in binding.get('exact_mapsym_names', []):
            if re.fullmatch(r'_?[ABR]list[XYMTS]', name, re.IGNORECASE):
                list_slots.setdefault(binding['selector_slot'], set()).add(name.lstrip('_').lower())
    if any(len(names) >= 2 for names in list_slots.values()):
        found.add('ant_list_shared_dx8')
    named_list_field = any(
        re.fullmatch(r'_?[ABR]list[XYMTS]', name, re.IGNORECASE)
        for binding in packet.get('direct_data_bindings', [])
        for name in binding.get('exact_mapsym_names', [])
    )
    if named_list_field or 'List' in card.get('symbol', '') or 'Dx8' in text:
        found.add('ant_list')
    return sorted(found)


def relevant_rules(card, packet=None):
    packet = packet or {}
    active = set(triggers(card, packet))
    rules = read_json(RULES)['rules']
    context = (packet.get('unit_context') or {}).get('id')
    return [dict(id=r['id'], rule=r['rule'], evidence=r['evidence'], matched=sorted(set(r['triggers']) & active))
            for r in rules if set(r['triggers']) & active
            and (not r.get('contexts') or context in r['contexts'])]
