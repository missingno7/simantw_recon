"""Compare complete library member contributions, with explicit link transformations.

No arbitrary mismatch masks. Placements come from all available publics, or a
consistent set of relocations to a private contribution, whose data is checked.
Constraint-derived private placement lowers proof strength. BSS is not bytes.
"""
from collections import Counter,defaultdict
from common import ROOT,fixture,write_json,identity,FormatError,Reader
import omf,ne,mapsym

LIBS=['sdk300/CLIB/LLIBCW.LIB','sdk300/CLIB/MLIBCW.LIB','sdk310/LIB/LLIBCW.LIB','sdk310/LIB/MLIBCW.LIB',
      'sdk300/CLIB/LLIBFPW.LIB','sdk310/LIB/LLIBFPW.LIB','msc6ax/LIB/LLIBCE.LIB','msc700/LIB/LLIBCW.LIB']

def import_symbols(path):
 out={}
 for data in omf.library_modules(path.read_bytes()):
  m=omf.parse(data)
  for c in m['comments']:
   if c['class']!=160:continue
   r=Reader(bytes.fromhex(c['data_hex']))
   if r.u8()!=1:continue
   ordinal=r.u8();name=r.name();module=r.name()
   if ordinal:out[name]={'kind':'import','module':module,'ordinal':r.u16()}
 return out

def compare_member(m,raw,n,s,imports):
 names=defaultdict(set)
 absolute={p['name']:p['offset'] for p in s['absolute_symbols']}
 for seg in s['segments']:
  for p in seg['symbols']:names[p['name']].add((seg['number'],p['offset']))
 placements={};anchors=defaultdict(list);issues=[];derived=[]
 for p in m['publics']:
  if not p['segment'] or len(names[p['name']])!=1:continue
  sg,off=next(iter(names[p['name']]))
  anchors[p['segment']].append((sg,off-p['offset'],p['name']))
 for si,aa in anchors.items():
  if len({x[:2] for x in aa})!=1:issues.append('inconsistent public placements for '+m['segments'][si-1]['name'])
  else:placements[si]=aa[0][:2]
 if issues:return {'result':'RULED_OUT_MEMBER','issues':issues,'anchors':dict(anchors)}
 if not placements:return None
 def reference(si):
  sg,off=placements[si];ss=m['segments'][si-1];ns=n['segments'][sg-1]
  if off<0 or off+ss['length']>ns['logical_size']:raise FormatError('contribution outside original')
  return raw[ns['file_offset']+off:ns['file_offset']+off+ss['length']]
 # Private DGROUP contribution constraints, never a guessed relocation value.
 pending=defaultdict(set)
 for f in m['fixups']:
  if f['segment'] not in placements or f['target_method']!=0 or f['target_index'] in placements:continue
  if f['location_type']!=1 or f['self_relative']:continue
  target_seg=m['segments'][f['target_index']-1]
  if f['frame_method']==1 and m['groups'][f['frame_index']-1]['name']=='DGROUP':original_segment=10
  elif (f['frame_method']==0 and f['frame_index']==f['target_index']) or f['frame_method']==5:
   # OMF F5 uses the target SEGDEF as its frame (TIS 1.1, OMF p45).
   # Still require a unique independently named original segment; no guesses.
   options=[seg['number'] for seg in s['segments'] if seg['name']==target_seg['name']]
   if len(options)!=1:continue
   original_segment=options[0]
  else:continue
  ss=m['segments'][f['segment']-1];p=f['offset'];ref=reference(f['segment']);cb=bytes.fromhex(ss['data_hex'])
  pending[f['target_index']].add((original_segment,(int.from_bytes(ref[p:p+2],'little')-int.from_bytes(cb[p:p+2],'little')-f['displacement'])&65535))
 for si,poss in pending.items():
  if len(poss)==1:placements[si]=next(iter(poss));derived.append(si)
  else:issues.append('conflicting private placement constraints '+m['segments'][si-1]['name'])
 # A BSS contribution carries no bytes, so its derived placement is only
 # meaningful inside the original BSS region: LINK places class BSS after every
 # DATA/CONST class, between the runtime's _edata and _end. A candidate static
 # placed below _edata is initialised data (or another object's data) in the
 # original and must be declared with its initialiser so its bytes are checked.
 for si in list(derived):
  ss=m['segments'][si-1]
  if ss['class']!='BSS':continue
  sg,off=placements[si]
  lo=next(iter(names['_edata']))[1] if names['_edata'] else absolute.get('_edata')
  hi=next(iter(names['_end']))[1] if names['_end'] else absolute.get('_end')
  if sg!=10 or lo is None or hi is None or off<lo or off+ss['length']>hi:
   issues.append(ss['name']+' contribution placed outside the original BSS region')
 if not any(m['segments'][si-1]['class']=='CODE' for si in placements):return None
 details=[];total=equal=fixequal=0;selectors_ok=set();pending_far_offsets=[]
 for ss in m['segments']:
  si=ss['index']
  if not ss['length']:continue
  if si not in placements:
   issues.append('unplaced contribution '+ss['name']);continue
  sg,off=placements[si];candidate=bytearray.fromhex(ss['data_hex']);ref=reference(si)
  # Common/BSS ranges may be initialized by another member; only this member's
  # initialized contribution owns loader obligations here.
  rel={q-off:r for r in n['segments'][sg-1]['relocations'] for q in r['sites'] if any(a<=q-off<b for a,b in ss['initialized_ranges'])}
  covered=set();mask=set();fixrows=[];transforms=[];far_offsets=[]
  for f in [f for f in m['fixups'] if f['segment']==si]:
   p=f['offset'];w=f['width'];target=None;ok=False;why='unsupported or unresolved target/frame'
   add=f['displacement']+int.from_bytes(candidate[p:p+min(w,2)],'little')
   if f['target_method']==2:
    name=f['target']['name']
    if len(names[name])==1:
     ts,to=next(iter(names[name]));target={'kind':'internal','segment':ts,'offset':to+add}
    elif name in imports and add==0:target=imports[name]
    elif name in absolute:target={'kind':'absolute','offset':absolute[name]+add}
   elif f['target_method']==0 and f['target_index'] in placements:
    ts,to=placements[f['target_index']];target={'kind':'internal','segment':ts,'offset':to+add}
   elif f['target_method']==0 and not m['segments'][f['target_index']-1]['length']:
    # An empty named segment (extern __based(__segname("X")) declarations
    # only) stands for the original segment of that unique MAPSYM name; its
    # selector obligation is checked like any other independently named target.
    options=[seg['number'] for seg in s['segments'] if seg['name']==m['segments'][f['target_index']-1]['name']]
    if len(options)==1:target={'kind':'internal','segment':options[0],'offset':add}
   frame_ok=f['frame_method']==5 or (f['frame_method']==2 and f['frame_index']==f['target_index'] and f['target_method']==2)
   if f['target_method']==2 and f['target'].get('name') in ('FIDRQQ','FIERQQ','FIWRQQ','FICRQQ','FJCRQQ'):
    # LINK5.30 calibration covers compiler frame5 and SDK runtime frame4.
    # Paired CS-prefix fixups share one NE obligation; retain both OMF checks.
    # Do not treat the instruction word as an ordinary absolute addend.
    fpname=f['target']['name'];site=p-1 if fpname=='FJCRQQ' else p
    expected={'kind':'os_fixup','type':{'FIDRQQ':5,'FIERQQ':4,'FIWRQQ':6,'FICRQQ':3,'FJCRQQ':3}[fpname],'reserved':0}
    shape=(candidate[p]==0x9b and 0xd8<=candidate[p+1]<=0xdf) if fpname=='FIDRQQ' else candidate[p:p+2]==bytes.fromhex('909b') if fpname=='FIWRQQ' else candidate[site:site+2]==bytes.fromhex('9b26' if fpname=='FIERQQ' else '9b2e') and site+2<len(candidate) and 0xd8<=candidate[site+2]<=0xdf
    partner=True
    if fpname in ('FICRQQ','FJCRQQ'):
     partner=any(g['segment']==si and g['offset']==(p+1 if fpname=='FICRQQ' else p-1) and
         g['target_method']==2 and g['target'].get('name')==('FJCRQQ' if fpname=='FICRQQ' else 'FICRQQ') and
         g['location_type']==1 and not g['self_relative'] and g['frame_method']==f['frame_method'] and
         g['displacement']==0 for g in m['fixups'])
    ok=(f['location_type']==1 and w==2 and not f['self_relative'] and
        f['frame_method'] in (4,5) and f['displacement']==0 and
        site in rel and rel[site]['source_type']==5 and rel[site]['flags']==7 and
        rel[site]['additive'] and rel[site]['target']==expected and
        candidate[p:p+2]==ref[p:p+2] and shape and partner)
    target=expected;why='calibrated '+fpname+' to NE OS fixup; instruction bytes unchanged'
    if ok:covered.add(site)
   elif target and target['kind']=='internal' and f['location_type']==2 and not f['self_relative'] and frame_ok and add==0:
    expected={'kind':'internal','segment':target['segment'],'offset':0}
    ok=p in rel and rel[p]['source_type']==2 and not rel[p]['additive'] and rel[p]['target']==expected;why='NE selector for independently named target'
    if ok:
     covered.add(p)
     if f['target_method']==2:selectors_ok.add((f['target']['name'],target['segment']))
   elif target and f['location_type']==3 and not f['self_relative'] and frame_ok and candidate[p+2:p+4]==b'\0\0':
    if p in rel and rel[p]['source_type']==3:
     ok=not rel[p]['additive'] and target==rel[p]['target'];why='NE pointer relocation'
     if ok:covered.add(p)
    elif p+2 in rel and rel[p+2]['source_type']==2:
     actual=dict(rel[p+2]['target'],offset=int.from_bytes(ref[p:p+2],'little'))
     ok=not rel[p+2]['additive'] and actual==target;why='NE selector relocation + offset'
     if ok:covered.add(p+2)
    elif target['kind']=='internal' and target['segment']==sg and p>=1:
     # LINK /FARCALLTRANSLATION preserves five bytes, including padding.
     opcode=candidate[p-1];dest=target['offset']
     if opcode==0x9a:expected=b'\x90\x0e\xe8'+((dest-(off+p+4))&65535).to_bytes(2,'little')
     elif opcode==0xea:expected=b'\xe9'+((dest-(off+p+2))&65535).to_bytes(2,'little')+b'\x90\x90'
     else:expected=b''
     ok=bool(expected) and ref[p-1:p+4]==expected and not any(p-1<=q<p+4 for q in rel)
     why='LINK same-segment far call/jump translation'
     if ok:candidate[p-1:p+4]=expected;transforms.append({'offset':p-1,'kind':why,'target':target})
    if ok and f['target_method']==2 and target['kind']=='internal':selectors_ok.add((f['target']['name'],target['segment']))
   elif target and target['kind']=='import' and f['location_type'] in (1,5) and not f['self_relative'] and frame_ok:
    ok=p in rel and rel[p]['source_type']==5 and not rel[p]['additive'] and target==rel[p]['target'];why='NE imported offset/absolute value'
    if ok:covered.add(p)
   elif target and target['kind']=='absolute' and f['location_type']==1 and not f['self_relative'] and frame_ok:
    ok=int.from_bytes(ref[p:p+2],'little')==target['offset'] and not any(p<=q<p+2 for q in rel);why='MAPSYM absolute symbol'
   elif target and target['kind']=='internal' and f['location_type']==5 and not f['self_relative'] and f['target_method']==2 and n['segments'][target['segment']-1]['kind']=='CODE' and frame_ok:
    # OMF LOC 5 (TIS 1.1 "16-bit loader-resolved offset"): the offset half of a
    # far code pointer, framed by the target symbol's own segment (F5, or F2
    # naming the same external). Win16 LINK resolves the segment-relative
    # offset statically when the target's segment is known at link time; the
    # NE image then carries no loader obligation at the site. The selector
    # half is a separate LOC 2 fixup which must independently validate the
    # segment identity (checked after all contributions, below).
    ok=int.from_bytes(ref[p:p+2],'little')==target['offset']&65535 and not any(p<=q<p+2 for q in rel)
    why='far code symbol offset in its own segment frame; selector half required'
    if ok:far_offsets.append((len(fixrows),f['target']['name'],target['segment']))
   elif target and target['kind']=='internal' and f['location_type']==1:
    if f['self_relative']:
     ok=target['segment']==sg and int.from_bytes(ref[p:p+2],'little')==(target['offset']-(off+p+2))&65535
     why='same-segment relative offset'
    else:
     valid_frame=(f['frame_method']==1 and m['groups'][f['frame_index']-1]['name']=='DGROUP' and target['segment']==10) or (f['frame_method']==0 and f['frame_index'] in placements and placements[f['frame_index']][0]==target['segment']) or (frame_ok and f['target_method'] in (0,2))
     ok=valid_frame and int.from_bytes(ref[p:p+2],'little')==target['offset']&65535;why='resolved offset and frame'
    ok=ok and not any(p<=q<p+2 for q in rel)
   if ok:mask.update(range(p,p+w));fixequal+=1
   else:issues.append(ss['name']+' unresolved/mismatched fixup at '+hex(p))
   fixrows.append({'offset':p,'target':target,'equal':ok,'reason':why,'omf':f})
  if set(rel)!=covered:issues.append(ss['name']+' uncovered NE relocations')
  pending_far_offsets.append((ss['name'],si,fixrows,far_offsets,mask))
  positions=[i for a,b in ss['initialized_ranges'] for i in range(a,b) if i not in mask]
  diffs=[i for i in positions if candidate[i]!=ref[i]];total+=len(positions);equal+=len(positions)-len(diffs)
  if diffs:issues.append(ss['name']+' literal bytes differ')
  details.append({'segment':ss['name'],'original_segment':sg,'original_offset':off,'length':ss['length'],'initialized_ranges':ss['initialized_ranges'],
    'literal_compared':len(positions),'literal_equal':len(positions)-len(diffs),'divergences':diffs[:512],'fixups':fixrows,'transformations':transforms})
 # A LOC 5 offset cannot establish which segment it addresses: equal offsets in
 # different segments are indistinguishable. Require a validated LOC 2 selector
 # fixup to the same external symbol somewhere in the member (immediate or
 # pooled CONST slot), whose NE obligation independently names the segment.
 for name,si,fixrows,far_offsets,mask in pending_far_offsets:
  for row_index,symbol,segment in far_offsets:
   if (symbol,segment) not in selectors_ok:
    row=fixrows[row_index];row['equal']=False;row['reason']='far code symbol offset without a validated selector fixup to the same symbol'
    issues.append(name+' unpaired far code offset fixup at '+hex(row['offset']))
 if any(not r['equal'] for name,si,fixrows,far_offsets,mask in pending_far_offsets for r in fixrows):
  # Recount after the pairing pass: unpaired offsets lose their masked bytes.
  fixequal=sum(r['equal'] for name,si,fixrows,far_offsets,mask in pending_far_offsets for r in fixrows)
 return {'result':'STRONGLY_SUPPORTED_MEMBER' if not issues and derived else 'CONFIRMED_MEMBER' if not issues else 'NO_COMPLETE_MATCH',
  'issues':issues,'placements':{str(k):list(v) for k,v in placements.items()},'private_constraint_placements':derived,'anchors':dict(anchors),'contributions':details,
  'literal_compared':total,'literal_equal':equal,'fixups_equal':fixequal,'fixups_total':len(m['fixups']),
  'publics':[p['name'] for p in m['publics']]}

def main():
 raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
 results=[]
 for lib in LIBS:
  path=ROOT/'toolchain'/lib
  if not path.exists():continue
  rows=[];errors=Counter()
  for b in omf.library_modules(path.read_bytes()):
   try:m=omf.parse(b);r=compare_member(m,raw,n,s,imports)
   except FormatError as ex:errors[str(ex)]+=1;continue
   if r:
    r.update(module=m['name'],module_sha256=m['sha256']);rows.append(r)
  results.append({'library':path.relative_to(ROOT).as_posix(),'identity':identity(path),'members':rows,'parse_or_placement_errors':dict(errors)})
  matches=[r for r in rows if r['result'] in ('CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER')]
  print(lib,Counter(r['result'] for r in rows),'bytes',sum(r['literal_compared'] for r in matches),flush=True)
  print('Matched:',', '.join(r['module'] for r in matches),flush=True)
 write_json(ROOT/'evidence/experiments/toolchain/library-members.json',{'exe_sha256':n['sha256'],'sym_sha256':s['sha256'],'import_library':identity(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB'),'results':results})

if __name__=='__main__':main()
