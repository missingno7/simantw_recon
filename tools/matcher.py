"""Strict comparison for the implemented 16-bit OMF relocation subset.

No bytes are masked merely because they differ. Every excluded operand must have
an independently resolved symbol, supported frame, and matching NE obligations.
"""
from common import FormatError
from analysis import extent, decoder

def unique_symbol(symbols,name):
    matches=[(s['number'],x['offset']) for s in symbols['segments'] for x in s['symbols'] if x['name']==name]
    if len(set(matches))!=1:raise FormatError(f'unknown or ambiguous symbol: {name}')
    return matches[0]

def compare(obj,original,ne,symbols,target):
    segment,offset=unique_symbol(symbols,target['symbol'])
    if segment!=target['segment'] or offset!=target['offset']:raise FormatError('target symbol/segment mismatch')
    ns=ne['segments'][segment-1]
    pubs=[p for p in obj['publics'] if p['name']==target['symbol']]
    if len(pubs)!=1:raise FormatError('wrong or ambiguous candidate public')
    pub=pubs[0];ss=obj['segments'][pub['segment']-1]
    if ss['name']!=target['code_segment'] or ss['class']!='CODE':raise FormatError('wrong candidate segment/class')
    code=bytes.fromhex(ss['data_hex']);begin=pub['offset']
    next_public=min([p['offset'] for p in obj['publics'] if p['segment']==pub['segment'] and p['offset']>begin]+[len(code)])
    ce=extent(code,begin,next_public)
    if ce['end'] is None:raise FormatError('candidate extent not closed: '+str(ce['reasons']))
    size=ce['size'];candidate=code[begin:begin+size]
    reference=original[ns['file_offset']+offset:ns['file_offset']+offset+target['size']]
    oe=extent(original[ns['file_offset']:ns['file_offset']+ns['logical_size']],offset,offset+target['size'])
    if oe['size']!=target['size'] or target.get('extent_status')!='CONFIRMED':raise FormatError('unproven original extent')
    if not any(a<=begin and begin+size<=b for a,b in ss['initialized_ranges']):raise FormatError('candidate includes uninitialized code')
    required={site-offset:r for r in ns['relocations'] for site in r['sites'] if offset<=site<offset+len(reference)}
    covered=set();masked=set();fix_results=[];issues=[]
    for f in obj['fixups']:
        if f['segment']!=pub['segment']:continue
        p=f['offset']-begin
        if p<0 or p>=size:
            if p+f['width']>0 and p<0:raise FormatError('fixup crosses function boundary')
            continue
        width=f['width'];ok=False;why='unsupported fixup';target_address=None
        if p+width>size:raise FormatError('fixup crosses function end')
        if any(x in masked for x in range(p,p+width)):raise FormatError('overlapping fixups')
        instructions=list(decoder().disasm(candidate,0))
        owner=next((i for i in instructions if i.address<=p<i.address+i.size),None)
        if owner is None or p+width>owner.address+owner.size:raise FormatError('fixup crosses instruction boundary')
        if f['location_type']==3 and not (owner.mnemonic=='lcall' and p==owner.address+1 and owner.size==5):
            raise FormatError('far pointer fixup is not a supported call operand')
        if f['location_type']==1 and p not in (owner.address+owner.disp_offset,owner.address+owner.imm_offset):
            raise FormatError('offset fixup is not an instruction operand')
        if f['target']['kind']=='external' and f['target']['name']=='__AHINCR' and not f['self_relative']:
            # Symbol/ordinal binding is independently supplied by SDK LIBW.LIB.
            from common import ROOT
            from library_match import import_symbols
            imported=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')['__AHINCR']
            rr=required.get(p)
            ok=f['location_type'] in (1,5) and f['frame_method']==5 and f['displacement']==0 and candidate[p:p+2]==b'\0\0' and rr is not None and rr['source_type']==5 and not rr['additive'] and rr['target']==imported
            why='SDK import binding + NE imported offset' if ok else 'wrong imported offset fixup'
            if ok:covered.add(p)
        elif f['target']['kind']=='external' and not f['self_relative']:
            ts,to=unique_symbol(symbols,f['target']['name']);target_address=[ts,to]
            addend=f['displacement']+int.from_bytes(candidate[p:p+2],'little')
            if f['location_type']==3 and width==4 and f['frame_method']==5:
                if candidate[p+2:p+4]!=b'\0\0':raise FormatError('nonzero far-pointer segment addend')
                expected={'kind':'internal','segment':ts,'offset':to+addend}
                if p in required and required[p]['source_type']==3:
                    rr=required[p];actual=rr['target'];site=p
                elif p+2 in required and required[p+2]['source_type']==2:
                    rr=required[p+2];actual=dict(rr['target'],offset=int.from_bytes(reference[p:p+2],'little'));site=p+2
                else:rr=None;actual=None;site=None
                ok=rr is not None and not rr['additive'] and actual==expected
                why='far pointer target + loader relocation' if ok else 'wrong far target or missing NE relocation'
                if ok:covered.add(site)
            elif f['location_type']==1 and width==2:
                # Near DS data needs a DGROUP frame and an independently named target.
                frame_ok=(f['frame_method']==1 and obj['groups'][f['frame_index']-1]['name']=='DGROUP') or f['frame_method']==5
                ok=frame_ok and ts==ne['header']['automatic_data_segment'] and int.from_bytes(reference[p:p+2],'little')==to+addend and not any(p<=q<p+2 for q in required)
                why='DGROUP offset resolved from symbol' if ok else 'wrong near data target/frame'
        if ok:masked.update(range(p,p+width))
        else:issues.append(why)
        fix_results.append({'offset':p,'width':width,'type':f['location_type'],'target':f['target'],
                            'resolved_address':target_address,'equal':ok,'reason':why})
    if set(required)!=covered:issues.append('unrepresented original NE relocations')
    ordinary=[i for i in range(min(len(reference),len(candidate))) if i not in masked]
    divergent=[i for i in ordinary if reference[i]!=candidate[i]]
    if len(reference)!=len(candidate):issues.append('wrong function length')
    # Independently compare instruction boundaries, including fields excluded above.
    original_layout=[(i.address-offset,i.size) for i in decoder().disasm(reference,offset)]
    candidate_layout=[(i.address-begin,i.size) for i in decoder().disasm(candidate,begin)]
    if original_layout!=candidate_layout:issues.append('instruction layout differs')
    exact=not issues and not divergent
    similar=not any(not f['equal'] for f in fix_results) and (len(ordinary)-len(divergent))/max(len(reference),len(candidate),1)>=0.5
    return {'symbol':target['symbol'],'result':'FUNCTION_MATCH' if exact else 'CODEGEN_SIMILAR' if similar else 'MISMATCH',
        'original_segment':segment,'original_offset':offset,'original_size':len(reference),'candidate_size':len(candidate),
        'ordinary_bytes_equal':len(ordinary)-len(divergent),'ordinary_bytes_total':len(reference)-len(masked),
        'fixups_equal':sum(f['equal'] for f in fix_results),'fixups_total':len(fix_results),'fixups':fix_results,
        'ne_sites_required':len(required),'ne_sites_represented':len(covered),
        'first_divergence':divergent[0] if divergent else min(len(reference),len(candidate)) if len(reference)!=len(candidate) else None,
        'issues':sorted(set(issues)),'original_hex':reference.hex(),'candidate_hex':candidate.hex(),
        'original_extent':oe,'candidate_extent':ce}
