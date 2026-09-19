"""Native Windows NE reader. All offsets remain in their original coordinate systems."""
from common import Reader, FormatError, sha256

SEG_FLAGS = {1:'DATA', 2:'ALLOCATED', 4:'LOADED', 8:'ITERATED', 16:'MOVABLE',
             32:'SHARED', 64:'PRELOAD', 128:'EXECUTE_ONLY_OR_READ_ONLY',
             256:'RELOCATIONS', 512:'CONFORMING', 1024:'DPL_1', 2048:'DPL_2',
             4096:'DISCARDABLE', 8192:'32BIT', 16384:'HUGE', 32768:'GDT'}
RESOURCE_TYPES = {1:'CURSOR',2:'BITMAP',3:'ICON',4:'MENU',5:'DIALOG',6:'STRING',
                  7:'FONTDIR',8:'FONT',9:'ACCELERATOR',10:'RCDATA',
                  12:'GROUP_CURSOR',14:'GROUP_ICON',15:'NAMETABLE',16:'VERSION'}
RELOC_WIDTH = {0:1,2:2,3:4,5:2,11:6,13:4}

def flags(value, names): return [s for mask,s in names.items() if value & mask]

def parse(data):
    r = Reader(data)
    if r.take(2) != b'MZ': raise FormatError('not MZ')
    dos = dict(zip(('last_page_bytes','pages','relocation_count','header_paragraphs',
                    'min_extra_paragraphs','max_extra_paragraphs','ss','sp','checksum',
                    'ip','cs','relocation_table_offset','overlay'), r.unpack('13H')))
    n = Reader(data,60).u32()
    r = Reader(data,n)
    if r.take(2) != b'NE': raise FormatError('not NE')
    h = dict(zip(('linker_major','linker_minor','entry_table_offset','entry_table_size',
                 'crc','flags','automatic_data_segment','heap_size','stack_size',
                 'ip','cs','sp','ss','segment_count','module_count','nonresident_size',
                 'segment_table_offset','resource_table_offset','resident_table_offset',
                 'module_table_offset','import_table_offset','nonresident_table_offset',
                 'movable_entry_count','alignment_shift','resource_segment_count',
                 'target_os','other_flags','return_thunk_offset','segment_reference_offset',
                 'minimum_code_swap','expected_windows_version'),
                 r.unpack('BBHHI'+'H'*16+'IHHHBBHHHH')))
    h['file_offset'] = n
    h['raw_hex'] = Reader(data,n).take(64).hex()
    h['linker_version'] = f"{h['linker_major']}.{h['linker_minor']:02d}"
    h['target_os_name'] = {0:'UNKNOWN',1:'OS2',2:'WINDOWS',3:'DOS4',4:'WINDOWS386'}.get(h['target_os'],'UNKNOWN')
    h['application_type']={0:'UNKNOWN',1:'NOT_WINDOW_COMPATIBLE',2:'WINDOW_COMPATIBLE',3:'WINDOW_API'}[(h['flags']>>8)&3]
    h['other_flag_names']=flags(h['other_flags'],{1:'LONG_FILENAME',2:'PROTECTED_MODE_2',4:'PROPORTIONAL_FONT',8:'FASTLOAD'})
    h['fastload_sector']=h['return_thunk_offset'] if h['other_flags']&8 else None
    h['fastload_length_sectors']=h['segment_reference_offset'] if h['other_flags']&8 else None
    h['flag_names'] = flags(h['flags'],{1:'SINGLE_DATA',2:'MULTIPLE_DATA',8:'PROTECTED_MODE',
        16:'8086',32:'80286',64:'80386',128:'X87',
        2048:'BIND',8192:'LINK_ERRORS',16384:'NONCONFORMING',32768:'LIBRARY'})
    if h['alignment_shift'] > 16: raise FormatError('implausible NE alignment')
    dr = Reader(data,dos['relocation_table_offset'])
    dos['relocations'] = [dict(zip(('offset','segment'),dr.unpack('HH'))) for _ in range(dos['relocation_count'])]
    dos['header_hex'] = Reader(data,0).take(dos['header_paragraphs']*16).hex()
    stub_start = dos['header_paragraphs']*16
    dos['stub'] = {'offset':stub_start,'size':n-stub_start,'hex':Reader(data,stub_start).take(n-stub_start).hex()}
    out = {'format':'NE','size':len(data),'sha256':sha256(data),'dos':dos,'header':h}
    def names(pos, end):
        q = Reader(data,pos); result=[]
        while q.pos < end:
            start=q.pos; name=q.name()
            if not name: return result
            result.append({'name':name,'ordinal':q.u16(),'file_offset':start})
        raise FormatError('unterminated NE name table')
    out['resident_names'] = names(n+h['resident_table_offset'],n+h['module_table_offset'])
    out['nonresident_names'] = names(h['nonresident_table_offset'],h['nonresident_table_offset']+h['nonresident_size'])
    impbase=n+h['import_table_offset']
    def imp(offset): return Reader(data,impbase+offset).name()
    q=Reader(data,n+h['module_table_offset'])
    out['modules']=[{'number':i+1,'name_offset':o,'name':imp(o)} for i,o in enumerate(q.unpack('H'*h['module_count']))]
    q=Reader(data,impbase); out['imported_names']=[]
    # The imported-name table ends at the entry table in this NE layout.
    if h['entry_table_offset'] >= h['import_table_offset']:
        while q.pos < n+h['entry_table_offset']:
            start=q.pos; name=q.name()
            out['imported_names'].append({'offset':start-impbase,'name':name})
        if q.pos != n+h['entry_table_offset']: raise FormatError('import name exceeds table')
    q=Reader(Reader(data,n+h['entry_table_offset']).take(h['entry_table_size']))
    entries=[]; ordinal=1
    while q.pos<len(q.data):
        count=q.u8()
        if not count: break
        bundle=q.u8()
        for _ in range(count):
            e={'ordinal':ordinal,'bundle':bundle}; ordinal+=1
            if bundle:
                e['flags']=q.u8()
                if bundle==255:
                    e['int3f']=q.u16(); e['segment']=q.u8()
                else: e['segment']=bundle
                e['offset']=q.u16()
            entries.append(e)
    out['entries']=entries
    out['segments']=[]; imports=[]
    q=Reader(data,n+h['segment_table_offset'])
    for number in range(1,h['segment_count']+1):
        sector,size,fl,alloc=q.unpack('HHHH')
        start=sector<<h['alignment_shift']; logical=size or 65536
        s={'number':number,'sector':sector,'file_offset':start if sector else None,
           'length_word':size,'logical_size':logical,'allocation_word':alloc,'allocation_size':alloc or 65536,
           'flags':fl,'flag_names':flags(fl,SEG_FLAGS),'kind':'DATA' if fl&1 else 'CODE','relocations':[]}
        if sector:
            if fl&8: raise FormatError('iterated NE segments not implemented')
            content=Reader(data,start).take(logical); s['sha256']=sha256(content)
            if fl&256:
                f=Reader(data,start+logical); s['relocation_table_offset']=f.pos
                for ri in range(f.u16()):
                    record=f.pos; typ,rf,source,t1,t2=f.unpack('BBHHH')
                    kind=rf&3
                    if typ not in RELOC_WIDTH: raise FormatError(f'unsupported NE relocation source {typ}')
                    if kind==0:
                        if t1&255==255: target={'kind':'entry','ordinal':t2}
                        else: target={'kind':'internal','segment':t1&255,'offset':t2}
                    elif kind in (1,2):
                        if not 1<=t1<=len(out['modules']): raise FormatError('bad import module index')
                        target={'kind':'import','module':out['modules'][t1-1]['name']}
                        target.update({'ordinal':t2} if kind==1 else {'name':imp(t2),'name_offset':t2})
                        imports.append(target)
                    else: target={'kind':'os_fixup','type':t1,'reserved':t2}
                    sites=[]; site=source
                    while True:
                        if site in sites: raise FormatError('cyclic relocation chain')
                        if site+RELOC_WIDTH[typ]>logical: raise FormatError('relocation outside segment')
                        sites.append(site)
                        if rf&4: break
                        nxt=Reader(content,site).u16()
                        if nxt==65535: break
                        site=nxt
                    s['relocations'].append({'index':ri,'file_offset':record,'source_type':typ,
                       'width':RELOC_WIDTH[typ],'flags':rf,'additive':bool(rf&4),'source_offset':source,
                       'target_words':[t1,t2],'target':target,'sites':sites})
        out['segments'].append(s)
    out['imports']=sorted({str(x):x for x in imports}.values(),key=lambda x:(x['module'],str(x.get('ordinal',x.get('name')))))
    base=n+h['resource_table_offset']; q=Reader(data,base)
    has_resources=h['resource_table_offset']!=h['resident_table_offset']
    shift=q.u16() if has_resources else 0
    if shift>16: raise FormatError('bad resource alignment')
    out['resource_alignment_shift']=shift; resources=[]
    def rid(value): return {'id':value&32767} if value&32768 else {'name':Reader(data,base+value).name(),'name_offset':value}
    while has_resources:
        typ=q.u16()
        if not typ: break
        count=q.u16(); reserved=q.u32()
        for _ in range(count):
            pos=q.pos; sector,length,fl,rn,handle,usage=q.unpack('6H')
            offset=sector<<shift; size=length<<shift
            payload=Reader(data,offset).take(size)
            resources.append({'table_offset':pos,'type':rid(typ),'type_name':RESOURCE_TYPES.get(typ&32767) if typ&32768 else None,
                'identity':rid(rn),'offset':offset,'size':size,'flags':fl,'flag_names':flags(fl,{16:'MOVABLE',32:'PURE',64:'PRELOAD',4096:'DISCARDABLE'}),
                'handle':handle,'usage':usage,'type_reserved':reserved,'sha256':sha256(payload)})
    out['resources']=resources
    if q.pos>n+h['resident_table_offset']:raise FormatError('resource records overlap resident names')
    for e in entries:
        if e.get('segment',0) not in (0,254) and (e['segment']>len(out['segments']) or e['offset']>=out['segments'][e['segment']-1]['logical_size']):
            raise FormatError('entry outside segment')
    regions=[{'start':0,'end':n,'kind':'DOS_HEADER_AND_STUB'},
             {'start':n,'end':n+64,'kind':'NE_HEADER'},
             {'start':n+h['segment_table_offset'],'end':n+h['segment_table_offset']+8*h['segment_count'],'kind':'SEGMENT_TABLE'},
             {'start':n+h['resource_table_offset'],'end':n+h['resident_table_offset'],'kind':'RESOURCE_TABLE'},
             {'start':n+h['resident_table_offset'],'end':n+h['module_table_offset'],'kind':'RESIDENT_NAMES'},
             {'start':n+h['module_table_offset'],'end':n+h['module_table_offset']+2*h['module_count'],'kind':'MODULE_REFERENCES'},
             {'start':impbase,'end':n+h['entry_table_offset'],'kind':'IMPORTED_NAMES'},
             {'start':n+h['entry_table_offset'],'end':n+h['entry_table_offset']+h['entry_table_size'],'kind':'ENTRY_TABLE'},
             {'start':h['nonresident_table_offset'],'end':h['nonresident_table_offset']+h['nonresident_size'],'kind':'NONRESIDENT_NAMES'}]
    for s in out['segments']:
        if s['file_offset'] is None:continue
        start=s['file_offset'];regions.append({'start':start,'end':start+s['logical_size'],'kind':'SEGMENT','number':s['number']})
        if s['flags']&256:regions.append({'start':start+s['logical_size'],'end':start+s['logical_size']+2+8*len(s['relocations']),'kind':'RELOCATION_TABLE','number':s['number']})
    for i,res in enumerate(resources):regions.append({'start':res['offset'],'end':res['offset']+res['size'],'kind':'RESOURCE','index':i})
    regions.sort(key=lambda x:x['start']);cursor=0;gaps=[]
    for region in regions:
        if region['start']<cursor:raise FormatError('overlapping NE file regions')
        if region['start']>cursor:gaps.append({'start':cursor,'end':region['start'],'kind':'UNASSIGNED_OR_PADDING'})
        cursor=region['end']
    if cursor<len(data):gaps.append({'start':cursor,'end':len(data),'kind':'UNASSIGNED_OR_PADDING'})
    for region in regions+gaps:
        payload=Reader(data,region['start']).take(region['end']-region['start'])
        region['sha256']=sha256(payload);region['all_zero']=not any(payload)
    out['file_regions']=sorted(regions+gaps,key=lambda x:x['start'])
    return out
