"""Compare complete library member contributions, with explicit link transformations.

No arbitrary mismatch masks. Placements come from all available publics, or a
consistent set of relocations to a private contribution, whose data is checked.
Constraint-derived private placement lowers proof strength. BSS is not bytes.
"""
from collections import Counter,defaultdict
from common import ROOT,fixture,write_json,identity,FormatError,Reader,read_json,sha256
import omf,ne,mapsym
SCAFFOLD_SEGMENT='POOLSTUB_TEXT'  # reserved code segment for pool-order stand-ins; never compared, never credited

LIBS=['sdk300/CLIB/LLIBCW.LIB','sdk300/CLIB/MLIBCW.LIB','sdk310/LIB/LLIBCW.LIB','sdk310/LIB/MLIBCW.LIB',
      'sdk300/CLIB/LLIBFPW.LIB','sdk310/LIB/LLIBFPW.LIB','msc6ax/LIB/LLIBCE.LIB','msc700/LIB/LLIBCW.LIB']

# LINK input order from the pinned runtime lane.  It matters for private
# contributions in one logical segment, which have no public to anchor them.
RUNTIME_LINK_LIBRARIES=(
 'toolchain/sdk300/CLIB/LLIBCW.LIB',
 'toolchain/sdk300/CLIB/LLIBFPW.LIB',
 'toolchain/sdk300/WLIB/LIBW.LIB',
 'toolchain/msc700/LIB/LIBH.LIB',
)
_RUNTIME_LAYOUT_MODULES=None
_VERIFIED_RUNTIME_LAYOUT=None

def _runtime_layout_modules():
 global _RUNTIME_LAYOUT_MODULES
 if _RUNTIME_LAYOUT_MODULES is None:
  rows=[]
  for lib_order,rel in enumerate(RUNTIME_LINK_LIBRARIES):
   path=ROOT/rel
   if not path.is_file():continue
   for ordinal,data in enumerate(omf.library_modules(path.read_bytes())):
    try:m=omf.parse(data)
    except FormatError:continue
    rows.append({'library':rel,'library_order':lib_order,'ordinal':ordinal,'module':m})
  _RUNTIME_LAYOUT_MODULES=rows
 return _RUNTIME_LAYOUT_MODULES

def _dgroup_segments(m):
 return {si for g in m['groups'] if g['name']=='DGROUP' for si in g['segments']}

def _mapped_bases(m,names):
 """Return bases derived only from MAPSYM publics, never from bytes."""
 bases=defaultdict(set);ambiguous=[]
 for p in m['publics']:
  if not p['segment'] or p.get('local'):continue
  locs=names.get(p['name'],set())
  if len(locs)==1:
   sg,off=next(iter(locs));bases[p['segment']].add((sg,off-p['offset']))
  elif len(locs)>1:ambiguous.append(p['name'])
 return bases,sorted(set(ambiguous))

def _runtime_member_metadata(m):
 if not isinstance(m,dict) or not m.get('sha256') or not m.get('name'):return []
 return [r for r in _runtime_layout_modules()
         if r['module']['sha256']==m['sha256'] and r['module']['name'].lower()==m['name'].lower()]

def _runtime_member_is_mapped(row,names):
 return any(not p.get('local') and p['name'] in names for p in row['module']['publics'])

def _runtime_code_base(row,names):
 m=row['module'];bases,_=_mapped_bases(m,names);options=[]
 for ss in m['segments']:
  if ss['class']=='CODE' and ss['name']=='_TEXT' and ss['length']:
   options.extend((sg,off,ss['index']) for sg,off in bases.get(ss['index'],set()))
 if not options:return None
 if len(set(options))!=1:return 'AMBIGUOUS'
 return options[0]

def _order_runtime_rows(rows,names):
 """Derive a unique member order from same-library order and MAPSYM code order."""
 ordered=list(rows);edges={i:set() for i in range(len(ordered))};indegree=[0]*len(ordered)
 code=[]
 for row in ordered:
  base=_runtime_code_base(row,names)
  if base=='AMBIGUOUS':return None,'ambiguous MAPSYM code anchors for '+row['module']['name']
  code.append(base)
 def add_edge(a,b):
  if b not in edges[a]:edges[a].add(b);indegree[b]+=1
 # LINK preserves member order within each archive. Cross-archive order is
 # recovered from mapped code contributions, since LINK's archive search
 # order need not be the final order of extracted contributions.
 for i,left in enumerate(ordered):
  for j,right in enumerate(ordered):
   if left['library']==right['library'] and left['ordinal']<right['ordinal']:
    add_edge(i,j)
 for i in range(len(ordered)):
  if code[i] is None:continue
  for j in range(i+1,len(ordered)):
   if code[j] is None or code[i][0]!=code[j][0]:continue
   if code[i][1]==code[j][1]:return None,'ambiguous MAPSYM code order for %s and %s'%(ordered[i]['module']['name'],ordered[j]['module']['name'])
   if code[i][1]<code[j][1]:add_edge(i,j)
   else:add_edge(j,i)
 result=[];remaining=set(range(len(ordered)))
 while remaining:
  ready=[i for i in remaining if indegree[i]==0]
  if len(ready)!=1:return None,'ambiguous or conflicting LINK order for DGROUP message members'
  i=ready[0];remaining.remove(i);result.append(ordered[i])
  for j in edges[i]:indegree[j]-=1
 return result,None

def _runtime_message_layout(m,names,s):
 """Place DGROUP MSG/PAD/EPAD from MAPSYM names and LINK5.30 order.

    The structural LINK 5.30 map puts HDR, MSG, PAD, and EPAD in that class order.
    __caption anchors HDR; linked message members are ordered by their pinned
    library/member sequence; _edata bounds the initialized group after LINK's
    paragraph alignment.  No raw-byte scan is used to choose a placement.
    """
 candidate_rows=_runtime_member_metadata(m)
 if len(candidate_rows)!=1:return {},[],[]
 candidate_row=candidate_rows[0];cm=candidate_row['module'];dgroup=_dgroup_segments(cm)
 targets=[ss for ss in cm['segments'] if ss['length'] and ss['class']=='MSG' and
          ss['name'] in ('HDR','MSG','PAD','EPAD') and ss['index'] in dgroup]
 if not targets:return {},[],[]
 contributing=[]
 for row in _runtime_layout_modules():
  rm=row['module'];dg=_dgroup_segments(rm)
  parts=[ss for ss in rm['segments'] if ss['length'] and ss['class']=='MSG' and
         ss['name'] in ('HDR','MSG','PAD','EPAD') and ss['index'] in dg]
  if not parts:continue
  linked=(rm['sha256']==cm['sha256'] and rm['name'].lower()==cm['name'].lower()) or _runtime_member_is_mapped(row,names)
  if linked:contributing.append(dict(row,parts=parts))
 if not any(row['module']['sha256']==cm['sha256'] for row in contributing):
  contributing.append(dict(candidate_row,parts=targets))
 for row in contributing:
  for ss in row['parts']:
   if ss['name'] not in ('HDR','MSG','PAD','EPAD'):
    return {},[],['unreviewed DGROUP message segment name']
   if ss['name'] in ('HDR','MSG') and ss['combine']!=2:
    return {},[],['unexpected combine mode for DGROUP '+ss['name']]
   if ss['name'] in ('PAD','EPAD') and ss['combine']!=6:
    return {},[],['unexpected combine mode for DGROUP '+ss['name']]
 ordered,order_issue=_order_runtime_rows(contributing,names)
 if order_issue:return {},[],[order_issue]
 hdr=[];msg=[];pads=[];epads=[]
 for row in ordered:
  for ss in sorted(row['parts'],key=lambda x:x['index']):
   {'HDR':hdr,'MSG':msg,'PAD':pads,'EPAD':epads}[ss['name']].append(dict(row,segment=ss))
 if not hdr or not msg:return {},[],['incomplete DGROUP HDR/MSG class inventory']
 hdr_prefix=0;hdr_starts={};anchor_bases=[]
 for row in hdr:
  rm=row['module'];ss=row['segment'];bases,ambiguous=_mapped_bases(rm,names)
  if ambiguous:return {},[],['ambiguous HDR MAPSYM public: '+', '.join(ambiguous)]
  hdr_starts[(rm['sha256'],ss['index'])]=hdr_prefix
  for sg,off in bases.get(ss['index'],set()):
   if sg!=10:return {},[],['HDR public is outside DGROUP']
   anchor_bases.append(off-hdr_prefix)
  hdr_prefix+=ss['length']
 if not anchor_bases or len(set(anchor_bases))!=1:
  return {},[],['HDR contribution has no unique __caption MAPSYM anchor']
 hdr_base=anchor_bases[0]
 caption=names.get('__caption',set())
 if len(caption)!=1 or next(iter(caption))[0]!=10:
  return {},[],['__caption MAPSYM anchor is missing or ambiguous']
 caption_publics=[(row,ss,p) for row in hdr for p in row['module']['publics']
                  for ss in [row['segment']] if p['name']=='__caption' and p['segment']==ss['index'] and not p.get('local')]
 if len(caption_publics)!=1:
  return {},[],['__caption OMF definition is missing or ambiguous in DGROUP HDR']
 caption_row,caption_segment,caption_public=caption_publics[0]
 if next(iter(caption))[1]!=hdr_base+hdr_starts[(caption_row['module']['sha256'],caption_segment['index'])]+caption_public['offset']:
  return {},[],['__caption OMF definition disagrees with MAPSYM HDR anchor']
 for row in hdr:
  rm=row['module'];ss=row['segment'];bases,_=_mapped_bases(rm,names)
  expected=(10,hdr_base+hdr_starts[(rm['sha256'],ss['index'])])
  if any(base!=expected for base in bases.get(ss['index'],set())):
   return {},[],['inconsistent HDR MAPSYM placement']
 msg_base=hdr_base+hdr_prefix;msg_starts={};cursor=msg_base
 for row in msg:
  ss=row['segment'];key=(row['module']['sha256'],ss['index'])
  if key in msg_starts:return {},[],['duplicate DGROUP MSG member contribution']
  msg_starts[key]=cursor;cursor+=ss['length']
 pad_base=cursor
 pad_length=max([row['segment']['length'] for row in pads] or [0])
 epad_base=pad_base+pad_length
 epad_length=max([row['segment']['length'] for row in epads] or [0])
 edata=names.get('_edata',set())
 if len(edata)!=1 or next(iter(edata))[0]!=10:
  return {},[],['_edata MAPSYM anchor is missing or ambiguous for DGROUP message layout']
 # LINK 5.30 aligns the following BSS class to a paragraph (see LIBNOPACK.MAP).
 aligned_end=(epad_base+epad_length+15)&~15
 if next(iter(edata))[1]!=aligned_end:
  return {},[],['DGROUP message class order does not reach MAPSYM _edata']
 inferred={};evidence=[]
 for ss in targets:
  key=(cm['sha256'],ss['index'])
  if ss['name']=='HDR':base=hdr_base+hdr_starts.get(key,0)
  elif ss['name']=='MSG':
   if key not in msg_starts:return {},[],['target MSG contribution is absent from LINK order']
   base=msg_starts[key]
  elif ss['name']=='PAD':base=pad_base
  else:base=epad_base
  inferred[ss['index']]=(10,base)
  evidence.append(dict(segment=ss['name'],segment_index=ss['index'],original_segment=10,original_offset=base,
   basis=['DGROUP class order HDR, MSG, PAD, EPAD (build/PARTLINK/PARTIAL.MAP, LINK 5.30)',
          'linked member order from pinned library sequence and MAPSYM public anchors',
          '__caption MAPSYM anchors HDR; _edata bounds paragraph-aligned initialized DGROUP']))
 return inferred,evidence,[]

def _verified_runtime_contribution(member_name,segment_name):
 """Read one current admitted runtime proof and verify its object identity."""
 global _VERIFIED_RUNTIME_LAYOUT
 if _VERIFIED_RUNTIME_LAYOUT is None:
  try:
   manifest=read_json(ROOT/'build/recovered/manifest.json')
   verified=read_json(ROOT/'build/recovery/verified-objects.json')
   ownership=read_json(ROOT/'layout/runtime-ownership.json')
  except (FileNotFoundError,FormatError):
   _VERIFIED_RUNTIME_LAYOUT=False
  else:
   verified_by_object={r.get('object'):r for r in verified.get('runtime',[])}
   manifest_by_object={r.get('object'):r for r in manifest.get('runtime_objects',[])}
   owner_rows=[r for r in ownership.get('members',[]) if r.get('member','').lower()==member_name.lower()]
   matching=[r for r in manifest.get('runtime_objects',[]) if r.get('member','').lower()==member_name.lower()]
   if (len(owner_rows)!=1 or len(matching)!=1 or len(verified_by_object)!=len(verified.get('runtime',[])) or
       set(verified_by_object)-set(manifest_by_object)):
    _VERIFIED_RUNTIME_LAYOUT=False
   else:
    row=matching[0];proof=verified_by_object.get(row.get('object'))
    valid=(proof is not None and proof.get('identity')==row.get('identity') and
           identity(ROOT/row['object'])==row.get('identity') and
           owner_rows[0].get('member_sha256')==row.get('member_sha256') and
           proof.get('comparison',{}).get('result') in ('CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'))
    _VERIFIED_RUNTIME_LAYOUT=(manifest,verified,ownership,verified_by_object) if valid else False
 if not _VERIFIED_RUNTIME_LAYOUT:return None
 manifest,verified,ownership,verified_by_object=_VERIFIED_RUNTIME_LAYOUT
 rows=[r for r in manifest['runtime_objects'] if r.get('member','').lower()==member_name.lower()]
 if len(rows)!=1:return None
 proof=verified_by_object.get(rows[0].get('object'))
 if not proof or proof.get('member','').lower()!=member_name.lower():return None
 contributions=[c for c in proof.get('comparison',{}).get('contributions',[])
                if c.get('segment')==segment_name and c.get('original_segment')==10]
 return contributions[0] if len(contributions)==1 else None

def _runtime_private_data_layout(m,names,placements,raw,n,s,imports):
 """Place strgtod _DATA only in its MAPSYM/link-order-bounded gap."""
 candidate_rows=_runtime_member_metadata(m)
 if len(candidate_rows)!=1 or m['name'].lower()!='\\mrt6\\common\\strgtod.asm':return {},[],[]
 row=candidate_rows[0];cm=row['module'];dgroup=_dgroup_segments(cm)
 targets=[ss for ss in cm['segments'] if ss['length'] and ss['name']=='_DATA' and
          ss['class']=='DATA' and ss['index'] in dgroup]
 if len(targets)!=1:return {},[],['strgtod private _DATA shape is ambiguous']
 target=targets[0]
 previous=_verified_runtime_contribution('\\mrt6\\common\\x8fout.ASM','_DATA')
 if not previous:return {},[],['missing fresh admitted x8fout _DATA placement evidence']
 previous_rows=[r for r in _runtime_layout_modules()
                if r['module']['name'].lower()=='\\mrt6\\common\\x8fout.asm' and _runtime_member_is_mapped(r,names)]
 if len(previous_rows)!=1:return {},[],['x8fout MAPSYM code anchor is missing or ambiguous']
 prev_bases,_=_mapped_bases(previous_rows[0]['module'],names)
 prev_text=[]
 for ss in previous_rows[0]['module']['segments']:
  if ss['name']=='_TEXT' and ss['class']=='CODE':
   prev_text.extend(prev_bases.get(ss['index'],set()))
 target_text=[]
 for ss in cm['segments']:
  if ss['name']=='_TEXT' and ss['class']=='CODE' and ss['index'] in placements:
   sg,off=placements[ss['index']]
   if sg==4:target_text.append(off)
 if len(prev_text)!=1 or len(target_text)!=1 or prev_text[0][0]!=4 or target_text[0]<=prev_text[0][1]:
  return {},[],['strgtod and x8fout LINK code order is missing or ambiguous']
 end_before=previous['original_offset']+previous['length']
 public=names.get('__lastiob',set())
 if len(public)!=1 or next(iter(public))[0]!=10:return {},[],['__lastiob MAPSYM boundary is missing or ambiguous']
 upper=next(iter(public))[1]
 alignment={1:1,2:2,3:16,4:256,5:4}.get(target['alignment'])
 if alignment is None:return {},[],['unsupported strgtod _DATA alignment']
 start=((end_before+alignment-1)//alignment)*alignment
 if start+target['length']!=upper:
  return {},[],['strgtod _DATA does not uniquely tile the x8fout/__lastiob DGROUP gap']
 # Existing verified contributions and MAPSYM public names may not overlap or
 # split this gap. New, unverified private members are screened below by their
 # independently mapped code positions and DGROUP _DATA declarations.
 if _VERIFIED_RUNTIME_LAYOUT:
  for section in ('game','runtime'):
   for objrow in _VERIFIED_RUNTIME_LAYOUT[1].get(section,[]):
    for c in objrow.get('comparison',{}).get('contributions',[]):
     if c.get('original_segment')==10:
      a=c.get('original_offset',0);b=a+c.get('length',0)
      if max(a,start)<min(b,upper):return {},[],['admitted contribution intersects inferred strgtod _DATA gap']
 for other in _runtime_layout_modules():
  om=other['module']
  if om['sha256']==cm['sha256'] or not _runtime_member_is_mapped(other,names):continue
  for ss in om['segments']:
   if ss['length'] and ss['name']=='_DATA' and ss['class']=='DATA' and ss['index'] in _dgroup_segments(om):
    cb=_runtime_code_base(other,names)
    if cb=='AMBIGUOUS':return {},[],['ambiguous code placement for intervening DGROUP _DATA member']
    if cb and cb[0]==4 and prev_text[0][1]<cb[1]<target_text[0]:
     return {},[],['another linked DGROUP _DATA member lies between x8fout and strgtod']
 if any(start<=off<upper for sg,off in names.get('_DATA',set())):
  return {},[],['MAPSYM public lies inside inferred strgtod _DATA gap']
 return {target['index']:(10,start)},[dict(segment='_DATA',segment_index=target['index'],original_segment=10,original_offset=start,
   basis=['admitted x8fout _DATA contribution is reference-derived and ends at %04X'%(end_before&0xffff),
          '__lastiob MAPSYM public anchors the next initialized _DATA contribution at %04X'%(upper&0xffff),
          'strgtod code follows x8fout in MAPSYM _TEXT order; WORD alignment and ten-byte contribution uniquely fill the gap'])],[]

def _link_order_placements(m,names,placements,raw,n,s,imports):
 inferred={};evidence=[];issues=[]
 rows,proof,problems=_runtime_message_layout(m,names,s)
 inferred.update(rows);evidence.extend(proof);issues.extend(problems)
 rows,proof,problems=_runtime_private_data_layout(m,names,placements,raw,n,s,imports)
 inferred.update(rows);evidence.extend(proof);issues.extend(problems)
 return inferred,evidence,issues

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

def compare_member(m,raw,n,s,imports,allow_data=False):
 names=defaultdict(set)
 absolute={p['name']:p['offset'] for p in s['absolute_symbols']}
 for seg in s['segments']:
  for p in seg['symbols']:names[p['name']].add((seg['number'],p['offset']))
 placements={};anchors=defaultdict(list);issues=[];derived=[]
 # Module-local symbols: a local external binds only to the unique local
 # public of the same name in this module; anything else stays unresolved.
 local_externals=[e['name'] for e in m['externals'] if e.get('local')]
 local_defs=defaultdict(list)
 for q in m['publics']:
  if q.get('local') and q['segment']:local_defs[q['name']].append(q)
 local_publics={k:v[0] for k,v in local_defs.items() if len(v)==1 and local_externals.count(k)==1 and
                sum(e['name']==k for e in m['externals'])==1 and not any(q['name']==k and not q.get('local') for q in m['publics'])}
 for p in m['publics']:
  if not p['segment'] or p.get('local') or len(names[p['name']])!=1:continue
  sg,off=next(iter(names[p['name']]))
  anchors[p['segment']].append((sg,off-p['offset'],p['name']))
 for si,aa in anchors.items():
  if len({x[:2] for x in aa})!=1:
   # Name the disagreeing publics: usually code that lies between them in the
   # original is missing from this candidate segment (split the run into
   # separate RUNk_TEXT segments or add the members/stand-ins in between).
   by=sorted(aa,key=lambda x:x[1])
   issues.append('inconsistent public placements for %s: %s; either a member before them in this segment compiles to a different size than the original (only exact bodies may share a run) or code that lies between them in the original is missing (split the run or add the members in between)'
                 %(m['segments'][si-1]['name'],', '.join('%s implies base %d:%04X'%(nm,sg,off&0xFFFF) for sg,off,nm in by)))
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
 link_placements,link_evidence,link_issues=_link_order_placements(m,names,placements,raw,n,s,imports)
 for si,position in link_placements.items():
  if si in placements:
   if placements[si]!=position:
    issues.append('link-order placement conflicts with independent anchor for '+m['segments'][si-1]['name'])
  else:
   placements[si]=position
 issues.extend(link_issues)
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
 # Library scanning only considers members with code; the data lane asks for data-only members explicitly.
 if not allow_data and not any(m['segments'][si-1]['class']=='CODE' for si in placements):return None
 details=[];total=equal=fixequal=0;selectors_ok=set();pending_far_offsets=[];scaffold=[]
 for ss in m['segments']:
  si=ss['index']
  if not ss['length']:continue
  if si not in placements:
   # A unit may carry pool scaffolding: stand-in functions in the reserved
   # code segment that only reproduce the selector-pool allocation order of
   # members not claimed by the unit. Their code asserts nothing and is not
   # compared; the pool words they allocate are still validated below through
   # the CONST contribution's selector fixups, and claimed members are
   # anchored and compared byte for byte as always.
   if ss['name']==SCAFFOLD_SEGMENT and ss['class']=='CODE' and not any(p['segment']==si and len(names[p['name']])==1 for p in m['publics']):
    scaffold.append(ss['name']);continue
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
    if name in local_publics:
     # LEXTDEF resolved by LINK to the LPUBDEF of the same module (a static
     # function called before its definition); its bytes are this candidate's own.
     lp=local_publics[name]
     if lp['segment'] in placements:
      ts,to=placements[lp['segment']];target={'kind':'internal','segment':ts,'offset':to+lp['offset']+add}
    elif len(names[name])==1:
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
   # A selector through the DGROUP group frame (`mov ax, DGROUP`, e.g. an
   # interrupt function's DS load) is DGROUP's selector: accepted only for a
   # selector fixup whose SEGDEF target is a member of DGROUP placed in the
   # original DGROUP segment.
   group=m['groups'][f['frame_index']-1] if f['frame_method']==1 and f['frame_index'] and f['frame_index']<=len(m['groups']) else None
   if (group and group['name']=='DGROUP' and f['location_type']==2 and f['target_method']==0 and f['target_index'] in group['segments']
       and target and target['kind']=='internal' and target['segment']==10):
    frame_ok=True
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
     if not valid_frame and f['frame_method']==0 and f['target_method']==2 and not m['segments'][f['frame_index']-1]['length']:
      # An empty named SEGDEF frame (an assembly module's `X SEGMENT ... EXTRN
      # sym ... X ENDS` block) stands for the unique MAPSYM segment of that
      # name, as for empty target segments above: valid only when the
      # external target lies in exactly that segment.
      frames=[seg['number'] for seg in s['segments'] if seg['name']==m['segments'][f['frame_index']-1]['name']]
      valid_frame=len(frames)==1 and frames[0]==target['segment']
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
 return {'result':'STRONGLY_SUPPORTED_MEMBER' if not issues and (derived or link_evidence) else 'CONFIRMED_MEMBER' if not issues else 'NO_COMPLETE_MATCH',
  'issues':issues,'placements':{str(k):list(v) for k,v in placements.items()},'private_constraint_placements':derived,'link_order_placements':link_evidence,'anchors':dict(anchors),'contributions':details,
  'literal_compared':total,'literal_equal':equal,'fixups_equal':fixequal,'fixups_total':len(m['fixups']),
  'publics':[p['name'] for p in m['publics']],'scaffold_segments':scaffold}

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
