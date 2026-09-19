"""Microsoft paragraph-linked MAPSYM records, not a strings scan."""
from common import Reader, FormatError, sha256

def parse(data):
    q=Reader(data)
    next_map,abs_type,pad,entry_seg,abs_count,abs_table,num_seg,first_seg,max_name=q.unpack('HBBHHHHHB')
    module=q.name()
    end=next_map*16
    zero,minor,major=Reader(data,end).unpack('HBB')
    if zero or end+4!=len(data): raise FormatError('multi-map or invalid MAPSYM trailer')
    if (major,minor)!=(3,10): raise FormatError(f'unsupported MAPSYM version {major}.{minor}')
    def symbols(base,table,count,typ):
        if typ&~3: raise FormatError('unknown MAPSYM symbol flags')
        r=Reader(data,base+table); pointers=list(r.unpack('H'*count)); result=[]
        for order,p in enumerate(pointers):
            f=Reader(data,base+p); offset=f.u32() if typ&1 else f.u16()
            name=f.name()
            if not name or len(name)>max_name: raise FormatError('invalid symbol name length')
            if f.pos>end: raise FormatError('symbol outside MAPSYM body')
            result.append({'offset':offset,'name':name,'table_order':order,'record_offset':base+p})
        return result
    out={'format':'Microsoft MAPSYM','version':f'{major}.{minor:02d}','sha256':sha256(data),'size':len(data),
         'module':module,'next_map_paragraph':next_map,'entry_segment':entry_seg,'absolute_type':abs_type,
         'padding':pad,'absolute_count':abs_count,'absolute_table_offset':abs_table,'segment_count':num_seg,
         'first_segment_paragraph':first_seg,'maximum_name_length':max_name,
         'absolute_symbols':symbols(0,abs_table,abs_count,abs_type),'segments':[]}
    pos=first_seg*16; visited=set()
    for _ in range(num_seg):
        if pos in visited or pos>=end: raise FormatError('bad/cyclic segment chain')
        visited.add(pos); r=Reader(data,pos)
        nxt,count,table,load,p0,p1,p2,typ,pad,line,loaded,instance=r.unpack('7HBBHBB')
        name=r.name()
        if line: raise FormatError('MAPSYM line records require implementation')
        s={'number':load,'name':name,'file_offset':pos,'next_segment_paragraph':nxt,'symbol_count':count,
           'symbol_table_offset':table,'physical_addresses':[p0,p1,p2],'symbol_type':typ,'padding':pad,
           'line_number_paragraph':line,'loaded':loaded,'instance':instance,'symbols':symbols(pos,table,count,typ)}
        out['segments'].append(s); pos=nxt*16
    if pos not in (0,first_seg*16): raise FormatError('segment chain has unexpected tail')
    return out

def cross_check(sym,ne,executable_stem='SIMANTW'):
    if sym['segment_count']!=ne['header']['segment_count']: raise FormatError('SYM/NE segment count mismatch')
    if sym['entry_segment']!=ne['header']['cs']: raise FormatError('SYM/NE entry segment mismatch')
    module=next((x['name'] for x in ne['resident_names'] if x['ordinal']==0),None)
    if sym['module'].upper()!=executable_stem.upper(): raise FormatError('SYM/executable filename mismatch')
    for i,s in enumerate(sym['segments'],1):
        if s['number']!=i: raise FormatError('SYM segment numbering mismatch')
        ns=ne['segments'][i-1]
        # Data symbols include BSS and may name the end of the allocation.
        bound=max(ns['allocation_size'],ns['logical_size'])
        for item in s['symbols']:
            if item['offset']>bound: raise FormatError(f"SYM symbol outside NE allocation: {item['name']}")
    startup=[s for s in sym['segments'][sym['entry_segment']-1]['symbols'] if s['name']=='__astart']
    if len(startup)!=1 or startup[0]['offset']!=ne['header']['ip']: raise FormatError('SYM/NE __astart mismatch')
    exports=[]
    for item in ne['resident_names']+ne['nonresident_names']:
        if not item['ordinal']: continue
        entry=next(e for e in ne['entries'] if e['ordinal']==item['ordinal'])
        matches=[x for x in sym['segments'][entry['segment']-1]['symbols'] if x['name']==item['name'] and x['offset']==entry['offset']]
        if len(matches)!=1: raise FormatError(f"SYM/NE export mismatch: {item['name']}")
        exports.append(item['name'])
    return {'status':'STRUCTURALLY_CONSISTENT','ne_module':module,'sym_module':sym['module'],'exports_checked':exports,
            'checks':['filename_stem','segment_count','segment_numbers','allocation_bounds','entry_segment','__astart','export_addresses'],
            'limitation':'MAPSYM carries no executable checksum; exact fixture pair is enforced separately by SHA-256.'}
