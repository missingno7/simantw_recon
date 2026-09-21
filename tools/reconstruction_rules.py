"""Attach established reconstruction rules to worker packets by observed triggers."""
from common import ROOT, read_json

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
    if any(r['mnemonic'] in ('shl', 'sal') or (r['mnemonic'] == 'add' and r['operands'].split(', ')[0] == r['operands'].split(', ')[-1]) for r in rows) or '+ si' in text or '+ di' in text or '+ bx' in text:
        found.add('indexed_access')
    if any(b.get('exact_mapsym_names') == [] and b.get('observed_displacement', 0) >= 0x40 for b in packet.get('direct_data_bindings', [])):
        found.add('private_data')
    if any(c.get('kind') == 'near_call' for c in card.get('calls', [])) or any(c.get('segment') == card.get('segment') for c in card.get('calls', [])):
        found.add('same_segment_call')
    if packet.get('evidence_state') == 'BODY_MATCHED_BINDING_BLOCKED' or set(card.get('blockers', [])) & {'DATA_LAYOUT', 'PRIVATE_CONST_LAYOUT'}:
        found.add('body_matched')
    if 'List' in card.get('symbol', '') or 'Dx8' in text:
        found.add('ant_list')
    return sorted(found)


def relevant_rules(card, packet=None):
    active = set(triggers(card, packet))
    rules = read_json(RULES)['rules']
    return [dict(id=r['id'], rule=r['rule'], evidence=r['evidence'], matched=sorted(set(r['triggers']) & active)) for r in rules if set(r['triggers']) & active]
