"""Recovery admission checks in addition to complete OMF relocation comparison.

A matching member prefix is not proof of the requested function. Promotion must
cover each requested public's independently established original extent.
"""
from common import FormatError
from matcher import unique_symbol
from cfg_solver import solve
from library_match import compare_member

GOOD={'CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'}

def check_coverage(module, symbols, targets, scaffold=False):
    # A scaffolded unit compiles later runs of claimed members into RUNk_TEXT;
    # their placement is still fixed by the MAPSYM anchors of every public.
    import re
    for name,target in targets.items():
        segment,offset=unique_symbol(symbols,name)
        if (segment,offset)!=(target['segment'],target['offset']):raise FormatError('recipe address differs from MAPSYM: '+name)
        if target.get('extent_status')!='CONFIRMED' or not isinstance(target.get('size'),int) or target['size']<=0:raise FormatError('unreviewed or invalid extent: '+name)
        pubs=[p for p in module['publics'] if p['name']==name]
        if len(pubs)!=1 or not 1<=pubs[0]['segment']<=len(module['segments']):raise FormatError('requested public missing/ambiguous: '+name)
        pub=pubs[0];seg=module['segments'][pub['segment']-1]
        if seg['class']!='CODE' or not (seg['name']==target['code_segment'] or (scaffold and re.fullmatch(r'RUN\d+_TEXT',seg['name']))):raise FormatError('wrong code group: '+name)
        begin=pub['offset'];end=begin+target['size']
        if end>seg['length'] or not any(a<=begin and end<=b for a,b in seg['initialized_ranges']):raise FormatError('incomplete requested function coverage: '+name)

def check_member(module, raw, image, symbols, imports, targets, scaffold=False):
    check_coverage(module,symbols,targets,scaffold)
    result=compare_member(module,raw,image,symbols,imports)
    if not result or result['result'] not in GOOD:raise FormatError('complete member comparison failed: '+str(result and result.get('issues')))
    return result

def admission_targets(module,raw,image,symbols,names,scaffold=False):
    """Derive bounded promotion scopes only for closed original AND candidate CFGs.

    This does not claim a historical filename or uniquely prove TU boundaries.
    Unknown jump tables/shared tails are reserved for explicit expert evidence.
    """
    targets={}
    for name in names:
        segment,offset=unique_symbol(symbols,name);original_segment=symbols['segments'][segment-1]
        ns=image['segments'][segment-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
        entries=[p['offset'] for p in original_segment['symbols']]
        if entries.count(offset)!=1:raise FormatError('overlapping/alias entry needs expert review: '+name)
        upper=min([p for p in entries if p>offset]+[len(code)])
        original=solve(code,offset,upper,entries,ns['relocations'],segment)
        if original['end'] is None or original['status']!='PROBABLE':raise FormatError('original CFG needs expert extent review: '+name)
        pubs=[p for p in module['publics'] if p['name']==name]
        if len(pubs)!=1 or not pubs[0]['segment']:raise FormatError('requested candidate public missing: '+name)
        pub=pubs[0];ss=module['segments'][pub['segment']-1];candidate=bytes.fromhex(ss['data_hex'])
        next_public=min([p['offset'] for p in module['publics'] if p['segment']==pub['segment'] and p['offset']>pub['offset']]+[len(candidate)])
        ce=solve(candidate,pub['offset'],next_public)
        if ce['end'] is None or ce['status']!='PROBABLE' or ce['size']!=original['size']:raise FormatError('candidate CFG does not cover full original function: '+name)
        targets[name]=dict(segment=segment,offset=offset,size=original['size'],code_segment=original_segment['name'],extent_status='CONFIRMED',
                           extent_evidence='Closed original and candidate recursive CFGs, explicit NOP gaps, full initialized coverage and exact complete-member comparison',comparison='member',historical_filename=None,proof='BYTE_MATCHED_RECONSTRUCTION')
    check_coverage(module,symbols,targets,scaffold)
    # Recompute cross-entry branch evidence from the original; a closed local
    # graph alone cannot establish that a tail has a single owner.
    for source_segment in symbols['segments']:
        ns=image['segments'][source_segment['number']-1]
        if ns['kind']!='CODE':continue
        code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
        entries=sorted({p['offset'] for p in source_segment['symbols']})
        for index,start in enumerate(entries):
            graph=solve(code,start,entries[index+1] if index+1<len(entries) else len(code),entries,ns['relocations'],source_segment['number'])
            for edge in graph['edges']:
                if edge.get('source') is None:continue
                for name,target in targets.items():
                    dest_segment=edge.get('target_segment',source_segment['number'])
                    if dest_segment==target['segment'] and target['offset']<=edge['target']<target['offset']+target['size'] and (source_segment['number'],start)!=(target['segment'],target['offset']):
                        raise FormatError('incoming cross-entry branch requires expert TU/extent review: '+name)
    return targets
