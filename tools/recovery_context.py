"""Compact, relocation-aware work packets for bounded source recovery."""
import re
from common import ROOT, read_json
from call_abi_audit import linker_lowered_far_calls


def declaration_index(recipes):
    """Verified source declarations are examples, not universal ABI proof."""
    result={}
    for source in sorted({t['source'] for t in recipes.values()}):
        text=(ROOT/source).read_text()
        text=re.sub(r'/\*.*?\*/|//[^\n]*','',text,flags=re.S)
        for declaration in re.findall(r'\bextern\s+[^;{}]+;',text,re.S):
            statement=' '.join(declaration.split())
            for name in re.findall(r'\b[A-Za-z_]\w*\b',statement):
                result.setdefault(name,[]).append(dict(declaration=statement,source=source,scope='Declaration used in a verified source; cross-TU type identity not proven'))
    return result


def compact_packet(card,cards,recipes,ledger):
    from library_match import import_symbols
    from compiler_profiles import component_of
    imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
    imported_names={}
    for name,target in imports.items():imported_names.setdefault((target['module'],target['ordinal']),[]).append(name)
    rows=[];names=set()
    for row in card['disassembly']:
        relative=row['offset']-card['offset'];raw=bytes.fromhex(row['bytes']);tokens=['%02x'%b for b in raw];bindings=[]
        for reloc in card['known_fixups']:
            for site in reloc['sites']:
                if row['offset']<=site<row['offset']+len(raw):
                    for p in range(site,min(site+reloc['width'],row['offset']+len(raw))):tokens[p-row['offset']]='??'
                    target=reloc['target'];bindings.append(dict(operand_offset=site-card['offset'],type=reloc['source_type'],target=target))
                    if target['kind']=='import':names.update(imported_names.get((target['module'],target['ordinal']),[]))
        for ref in row['references']:names.update(ref.get('names',[]))
        operand=row['operands']
        if bindings:
            # Do not present relocation-chain words as source-level call/selector constants.
            operand='<resolved loader operand; see bindings>'
        rows.append(dict(offset=relative,bytes=' '.join(tokens),mnemonic=row['mnemonic'],operands=operand,bindings=bindings,references=row['references']))
    index=declaration_index(recipes);declarations=[];seen=set()
    for name in sorted(names):
        for spelling in [name,name[1:] if name.startswith('_') else name]:
            for declaration in index.get(spelling,[])[:3]:
                key=(declaration['declaration'],declaration['source'])
                if key not in seen:seen.add(key);declarations.append(declaration)
    siblings=[c for c in cards if c['segment']==card['segment']]
    pos=next(i for i,c in enumerate(siblings) if c['symbol']==card['symbol'])
    neighbors=[dict(symbol=c['symbol'],offset=c['offset'],source=c['source'],size=c['extent']['size']) for c in siblings[max(0,pos-2):pos+3] if c['symbol']!=card['symbol']]
    far_calls=linker_lowered_far_calls(card)
    notes=['?? bytes belong to NE loader relocation chains, never literal C addresses.',
           'Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.',
           'Next MAPSYM public is an upper bound, not the function end.',
           'Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.']
    if far_calls:
        notes.append('Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.')
    component_id=(component_of(card['symbol']) or {}).get('id')
    unit_declaration_order=read_json(ROOT/'layout/declaration-order.json')['components'].get(component_id,[])
    return dict(symbol=card['symbol'],segment=card['segment'],code_segment=card['segment_name'],offset=card['offset'],extent=card['extent'],
                disassembly=rows,referenced_declarations=declarations,neighbors=neighbors,incoming_references=card['incoming_references'],
                linker_lowered_far_calls=far_calls,prior_draft=ledger.get(card['symbol']),
                unit_declaration_order=unit_declaration_order,
                interpretation_notes=notes)


def markdown(packet):
    lines=['# Recovery task '+packet['symbol'],'',
           'Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.','',
           'Code group: `'+packet['code_segment']+'`. Closed extent: '+str(packet['extent']['size'])+' bytes.','',
           '```asm']
    for row in packet['disassembly']:
        bindings=' ; '+str(row['bindings']) if row['bindings'] else ''
        refs=' ; '+','.join(name for ref in row['references'] for name in ref.get('names',[]))
        lines.append(f"{row['offset']:04x} {row['mnemonic']} {row['operands']}"+bindings+(refs if refs!=' ; ' else ''))
    lines+=['```','','## Known declaration examples','']
    for declaration in packet['referenced_declarations']:lines+=['- `'+declaration['declaration']+'` — '+declaration['source']]
    lines+=['','## Interpretation','']+['- '+n for n in packet['interpretation_notes']]
    if packet.get('linker_lowered_far_calls'):
        lines+=['','## LINK-lowered far-call evidence','']
        for call in packet['linker_lowered_far_calls']:
            lines+=['- '+str(call)]
    lines+=['','## Neighbors','']+['- '+str(n) for n in packet['neighbors']]
    return '\n'.join(lines)+'\n'
