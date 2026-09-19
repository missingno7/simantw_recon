"""Strict 16-bit OMF module reader, including threaded FIXUPP semantics.

Unsupported records fail closed. No matching claim is made from an incomplete parse.
LIDATA is expanded, but FIXUPP referring to iterated encoding is rejected for now.
"""
from common import Reader, FormatError, sha256

RECORDS={0x80:'THEADR',0x82:'LHEADR',0x88:'COMENT',0x8a:'MODEND',0x8c:'EXTDEF',
         0x90:'PUBDEF',0x94:'LINNUM',0x96:'LNAMES',0x98:'SEGDEF',0x9a:'GRPDEF',
         0x9c:'FIXUPP',0xa0:'LEDATA',0xa2:'LIDATA',0xb0:'COMDEF',0xb4:'LEXTDEF',
         0xb6:'LPUBDEF',0xb8:'LCOMDEF',0x99:'SEGDEF32',0xb2:'BAKPAT',0xc6:'ALIAS'}
WIDTHS={0:1,1:2,2:2,3:4,4:1,5:2,9:4,11:6,13:4}

def records(data):
    r=Reader(data)
    while r.pos<len(data):
        start=r.pos; kind=r.u8(); length=r.u16()
        if not length: raise FormatError('zero OMF record length')
        payload=r.take(length)
        # OMF explicitly permits a zero checksum byte to mean unchecked.
        if payload[-1] and sum(data[start:r.pos])&255: raise FormatError(f'OMF checksum at {start:#x}')
        yield start,kind,payload[:-1],payload[-1]

def parse(data):
    out={'sha256':sha256(data),'name':None,'records':[],'names':[],'segments':[],
         'groups':[],'externals':[],'publics':[],'fixups':[],'comments':[],'commons':[],'backpatches':[],'aliases':[]}
    buffers={}; initialized={}; threads=[{},{}]; last=None; ended=False
    def lookup(items,i,what):
        if not 1<=i<=len(items): raise FormatError(f'invalid OMF {what} index {i}')
        return items[i-1]
    def name(i): return lookup(out['names'],i,'name')
    def datum(r,method,is_frame):
        if method in (0,1,2): return r.index()
        if method==3: return r.u16()
        if is_frame and method in (4,5): return None
        raise FormatError(f'unsupported OMF reference method {method}')
    def expand(r,depth=0):
        if depth>32: raise FormatError('LIDATA nesting limit')
        repeat,blocks=r.unpack('HH')
        content=b''.join(expand(r,depth+1) for _ in range(blocks)) if blocks else r.take(r.u8())
        if len(content)*repeat>65536: raise FormatError('LIDATA expansion exceeds segment')
        return content*repeat
    for pos,kind,body,checksum in records(data):
        if ended: raise FormatError('trailing records after MODEND')
        if kind not in RECORDS: raise FormatError(f'unsupported OMF record {kind:#x} at {pos:#x}')
        r=Reader(body)
        out['records'].append({'offset':pos,'type':RECORDS[kind],'length':len(body)+1,'checksum':checksum})
        if kind in (0x80,0x82):
            if out['name'] is not None: raise FormatError('multiple modules')
            out['name']=r.name()
        elif kind==0x88:
            out['comments'].append({'attribute':r.u8(),'class':r.u8(),'data_hex':r.take(len(body)-2).hex()})
        elif kind==0x96:
            while r.pos<len(body): out['names'].append(r.name())
        elif kind in (0x98,0x99):
            acbp=r.u8(); align=acbp>>5; frame=offset=None
            if not align: frame=r.u16(); offset=r.u8()
            size=r.u32() if kind==0x99 else r.u16()
            if acbp&2:
                if size: raise FormatError('big segment has nonzero length')
                size=65536
            if size>65536:raise FormatError('OMF segment exceeds 16-bit range')
            if acbp&1 and size: raise FormatError('nonempty USE32 segment unsupported')
            s={'index':len(out['segments'])+1,'acbp':acbp,'alignment':align,'combine':(acbp>>2)&7,
               'length':size,'name':name(r.index()),'class':name(r.index()),'overlay':name(r.index()),
               'absolute_frame':frame,'absolute_offset':offset}
            out['segments'].append(s); buffers[s['index']]=bytearray(size);initialized[s['index']]=bytearray(size)
        elif kind==0x9a:
            g={'index':len(out['groups'])+1,'name':name(r.index()),'segments':[]}
            while r.pos<len(body):
                if r.u8()!=255: raise FormatError('unsupported GRPDEF component')
                i=r.index();lookup(out['segments'],i,'segment');g['segments'].append(i)
            out['groups'].append(g)
        elif kind in (0x8c,0xb4):
            while r.pos<len(body): out['externals'].append({'name':r.name(),'type_index':r.index(),'local':kind==0xb4})
        elif kind in (0x90,0xb6):
            group=r.index();seg=r.index();frame=r.u16() if not seg else None
            if seg: lookup(out['segments'],seg,'segment')
            if group:lookup(out['groups'],group,'group')
            while r.pos<len(body):
                p={'name':r.name(),'offset':r.u16(),'type_index':r.index(),'segment':seg,'group':group,'frame':frame,'local':kind==0xb6}
                if seg and p['offset']>out['segments'][seg-1]['length']: raise FormatError('public outside segment')
                out['publics'].append(p)
        elif kind in (0xb0,0xb8):
            def numeric():
                leaf=r.u8()
                if leaf<=128:return leaf
                if leaf in (129,132,136):return int.from_bytes(r.take({129:2,132:3,136:4}[leaf]),'little')
                raise FormatError('unsupported communal size')
            while r.pos<len(body):
                c={'name':r.name(),'type_index':r.index(),'kind':r.u8(),'local':kind==0xb8}
                if c['kind']==0x61: c['count']=numeric();c['element_size']=numeric()
                elif c['kind']==0x62:c['count']=1;c['element_size']=numeric()
                else:raise FormatError('unsupported communal kind')
                out['commons'].append(c);out['externals'].append(c)
        elif kind in (0xa0,0xa2):
            seg=r.index();offset=r.u16();lookup(out['segments'],seg,'segment')
            if kind==0xa0:payload=r.take(len(body)-r.pos)
            else:
                chunks=[]
                while r.pos<len(body):chunks.append(expand(r))
                payload=b''.join(chunks)
            if offset+len(payload)>len(buffers[seg]): raise FormatError('OMF data exceeds segment')
            if any(initialized[seg][offset:offset+len(payload)]):raise FormatError('overlapping OMF data')
            buffers[seg][offset:offset+len(payload)]=payload
            initialized[seg][offset:offset+len(payload)]=b'\1'*len(payload)
            last=(seg,offset,len(payload),kind)
        elif kind==0x9c:
            while r.pos<len(body):
                first=r.u8()
                if not first&128:
                    is_frame=(first>>6)&1;method=(first>>2)&7;slot=first&3
                    if not is_frame:method &= 3
                    threads[is_frame][slot]=(method,datum(r,method,is_frame))
                    continue
                if last is None or last[3]!=0xa0:raise FormatError('FIXUPP requires preceding LEDATA; iterated fixups unsupported')
                locat=(first<<8)|r.u8(); loc=(locat>>10)&15;offset=locat&1023
                if loc not in WIDTHS:raise FormatError('unknown OMF fixup location')
                fd=r.u8();fm=(fd>>4)&7;tm=fd&3
                if fd&128:
                    if fm&3 not in threads[1]:raise FormatError('undefined frame thread')
                    frame=threads[1][fm&3]
                else:frame=(fm,datum(r,fm,True))
                if fd&8:
                    if tm not in threads[0]:raise FormatError('undefined target thread')
                    target=threads[0][tm]
                else:target=(tm,datum(r,tm,False))
                displacement=0 if fd&4 else r.u16()
                if offset+WIDTHS[loc]>last[2]:raise FormatError('fixup outside preceding LEDATA')
                out['fixups'].append({'segment':last[0],'offset':last[1]+offset,'location_type':loc,'width':WIDTHS[loc],
                    'self_relative':not bool(first&64),'frame_method':frame[0],'frame_index':frame[1],
                    'target_method':target[0],'target_index':target[1],'displacement':displacement})
        elif kind==0x94:
            group=r.index();seg=r.index();rows=[]
            while r.pos<len(body):rows.append(r.unpack('HH'))
            out.setdefault('line_numbers',[]).append({'group':group,'segment':seg,'rows':rows})
        elif kind==0xb2:
            seg=r.index();lookup(out['segments'],seg,'segment');location=r.u8()
            if location not in (0,1,2):raise FormatError('unsupported BAKPAT location')
            while r.pos<len(body):out['backpatches'].append({'segment':seg,'width':1<<location,'offset':r.u16(),'value':r.u16()})
        elif kind==0xc6:
            while r.pos<len(body):out['aliases'].append({'alias':r.name(),'substitute':r.name()})
        elif kind==0x8a:
            out['modend_hex']=body.hex();r.take(len(body));ended=True
        if r.pos!=len(body):raise FormatError(f'unparsed bytes in {RECORDS[kind]}')
    if not ended or out['name'] is None:raise FormatError('incomplete OMF module')
    for b in out['backpatches']:
        buf=buffers[b['segment']];p=b['offset'];w=b['width']
        if p+w>len(buf) or not all(initialized[b['segment']][p:p+w]):raise FormatError('BAKPAT outside initialized data')
        if any(f['segment']==b['segment'] and max(p,f['offset'])<min(p+w,f['offset']+f['width']) for f in out['fixups']):raise FormatError('BAKPAT overlaps relocation')
        value=(int.from_bytes(buf[p:p+w],'little')+b['value'])&((1<<(w*8))-1)
        buf[p:p+w]=value.to_bytes(w,'little')
    for s in out['segments']:
        s['data_hex']=buffers[s['index']].hex()
        # Keep uninitialized holes distinguishable from emitted zeroes.
        runs=[];start=None
        for i,b in enumerate(initialized[s['index']]+b'\0'):
            if b and start is None:start=i
            if not b and start is not None:runs.append([start,i]);start=None
        s['initialized_ranges']=runs
    for f in out['fixups']:
        tm,ti=f['target_method'],f['target_index']
        if tm==0:t={'kind':'segment','name':lookup(out['segments'],ti,'target segment')['name']}
        elif tm==1:t={'kind':'group','name':lookup(out['groups'],ti,'target group')['name']}
        elif tm==2:t={'kind':'external','name':lookup(out['externals'],ti,'external')['name']}
        else:t={'kind':'absolute','frame':ti}
        f['target']=t
        fm,fi=f['frame_method'],f['frame_index']
        if fm in (0,1,2):lookup([out['segments'],out['groups'],out['externals']][fm],fi,'frame')
    return out

def library_modules(data):
    """Yield raw OMF members of a page-aligned Microsoft library."""
    if data[0]!=0xf0:raise FormatError('not OMF library')
    page=Reader(data,1).u16()+3;pos=page
    while pos<len(data) and data[pos]!=0xf1:
        start=pos;r=Reader(data,pos)
        while True:
            kind=r.u8();length=r.u16();r.take(length)
            if kind in (0x8a,0x8b):break
        yield data[start:r.pos]
        pos=((r.pos+page-1)//page)*page
