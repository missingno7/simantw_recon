"""Bounded, discriminating experiments; these are hypotheses, not recovered sources.

One-factor contrasts are applied only to probes that can discriminate that factor.
The original is read by the verifier only, never by the compiler.
"""
import argparse
from common import ROOT, fixture, read_json, write_json, identity, FormatError
from compiler import compile_source
from analysis import extent
from matcher import compare
import ne, mapsym, omf

BASE=['/AL','/G2','/Gs','/Oe']
STRUCT='struct H { void far *data; unsigned short reserved; unsigned long size; unsigned long age; unsigned short type; };\n'
PROBES={
 'ABS':('int ABS(int x) { if(x<0) return -x; return x; }', ['cpu','optimizer','convention','windows']),
 'GPicSize':('int GPicSize(int a,int b,int c,int d) { return (((c-a+8)/8)*(d-b+1)+1)*4; }',['cpu','optimizer']),
 'GImgSize':('int GImgSize(int a,int b,int c,int d) { return ((c-a+8)/8)*(d-b+1)+4; }',['cpu','optimizer']),
 'BitmapImageSize':('long BitmapImageSize(int w,int h,int planes) { return (((long)w*planes+31)/32)*h*4; }',['cpu','optimizer']),
 'RRand':('extern int rand(void);\nint RRand(int limit) { int v=rand(); if(v<0) v=-v; return v%limit; }',['cpu','optimizer','model','windows']),
 'RallocType':(STRUCT+'int RallocType(struct H *p) { return p->type; }',['model','windows']),
 'RallocSize':(STRUCT+'unsigned long RallocSize(struct H *p) { return p->size; }',['model']),
 'RallocFreed':(STRUCT+'int RallocFreed(struct H *p) { return p->data==0; }',['model','optimizer']),
 'RallocSetType':(STRUCT+'void RallocSetType(struct H *p,int type) { p->type=type; }',['model']),
 'win_SortRect':('struct R { int left,top,right,bottom; };\nvoid win_SortRect(struct R *p) { int t; t=p->left; if(t>p->right) { p->left=p->right;p->right=t; } t=p->top; if(t>p->bottom) { p->top=p->bottom;p->bottom=t; } }',['model','optimizer','windows']),
 'win_WinAddr':('extern void far * near win_handles[];\nvoid far *win_WinAddr(int id) { return win_handles[id>>8]; }',['model','cpu']),
 'WindowsMemCpy':('void WindowsMemCpy(char huge *d,char huge *s,unsigned long n) { unsigned long i; for(i=0;i<n;i++) *d++=*s++; }',['model','optimizer','cpu']),
 'ExtractWord':('extern unsigned short FlipWord(unsigned short);\nvoid ExtractWord(void far * far *p,unsigned short far *out) { *out=*(unsigned short far *)*p; *out=FlipWord(*out); *p=(void far *)((unsigned long)*p+2); }',['model','optimizer']),
 'MyPow':('unsigned long MyPow(unsigned long b,unsigned long n) { unsigned long v,i; if(n==0) return 1; v=1; for(i=1;i<=n;i++) v*=b; return v; }',['optimizer','cpu','stack']),
 'RandTurn':('extern int far SRand8(void);\nextern char far TurnTab[8][8];\nint near RandTurn(int d) { return TurnTab[d][SRand8()]; }',['model','optimizer','cpu']),
 'win_SetWinDrawHook':('typedef void (far *Hook)(void);\nextern Hook far win_drawHooks[];\nvoid win_SetWinDrawHook(int id,Hook f) { win_drawHooks[id>>8]=f; }',['model','cpu','optimizer']),
 'CreateMonoSolidBrush':('extern unsigned far pascal CreateSolidBrush(unsigned long);\nunsigned CreateMonoSolidBrush(unsigned char c) { switch(c&0x70) { case 0: return CreateSolidBrush(0L); case 0x10: return CreateSolidBrush(0x606060L); case 0x20: return CreateSolidBrush(0x808080L); case 0x30: return CreateSolidBrush(0xa0a0a0L); case 0x50: return CreateSolidBrush(0xc0c0c0L); case 0x60: return CreateSolidBrush(0x202020L); default: return CreateSolidBrush(0xffffffL); } }',['optimizer','cpu']),
 'IsValidSLoc':('int IsValidSLoc(int x,int y) { if(x>=0 && x<=63 && y>=0 && y<=31) return 1; return 0; }',['optimizer','cpu']),
}
CONTRASTS={
 'cpu':[('8086',['/G0']),('186',['/G1']),('386',['/G3'])],
 'optimizer':[('no-opt',['/Od']),('size',['/Oes']),('global',['/Oeg']),('loop',['/Oel']),('max',['/Ox']),('no-reg',['/O']),('no-alias',['/Oea'])],
 'model':[('small',['/AS']),('medium',['/AM']),('compact',['/AC']),('huge',['/AH'])],
 'windows':[('Gw',['/Gw']),('GW',['/GW'])],
 'convention':[('pascal',['/Gc']),('fastcall',['/Gr'])],
 'stack':[('stack-check',['/Ge'])],
}

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--baseline',action='store_true');ap.add_argument('--only');ap.add_argument('--compiler',default='msc600a');ap.add_argument('--optimization');args=ap.parse_args()
 raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'))
 directory=ROOT/'evidence/experiments/toolchain/probes';directory.mkdir(parents=True,exist_ok=True)
 manifest=[];results=[]
 for name,(source,axes) in PROBES.items():
  if args.only and name not in args.only.split(','):continue
  path=directory/(name+'.c');path.write_text('/* Toolchain diagnostic hypothesis; historical source unavailable. */\n'+source+'\n')
  seg,sym=next((seg,x) for seg in s['segments'] for x in seg['symbols'] if x['name']=='_'+name)
  ns=n['segments'][seg['number']-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
  limit=min([x['offset'] for x in seg['symbols'] if x['offset']>sym['offset']]+[len(code)])
  e=extent(code,sym['offset'],limit)
  if not e['size'] and name=='CreateMonoSolidBrush':
   e.update(size=100,end=sym['offset']+100,status='REVIEWED_SWITCH',jump_table=[0x191e,0x192c],evidence='7 word case targets, six explicit cases, default, common GDI call and RETF at 1965h; table separated from instructions')
  if not e['size']:raise FormatError('unclosed diagnostic '+name)
  target={'symbol':'_'+name,'segment':seg['number'],'offset':sym['offset'],'size':e['size'],'code_segment':seg['name'],'extent_status':'CONFIRMED'}
  manifest.append(dict(target,source=path.relative_to(ROOT).as_posix(),source_identity=identity(path),axes=axes,source_status='HYPOTHESIS',extent_evidence='Reviewed disassembly and closed contiguous CFG',extent=e))
  base=BASE if not args.optimization else [f for f in BASE if not f.startswith('/O')]+[args.optimization]
  configs=[('baseline' if not args.optimization else args.optimization,base)]
  if not args.baseline:
   for axis in axes:
    for label,opts in CONTRASTS[axis]:
     flags=[f for f in BASE if not (axis=='cpu' and f.startswith('/G2') or axis=='optimizer' and f.startswith('/O') or axis=='model' and f.startswith('/A') or axis=='stack' and f=='/Gs')]+opts
     configs.append((label,flags))
  for label,flags in configs:
   flags=flags+['/NT'+seg['name']]
   try:
    obj,receipt=compile_source(path.relative_to(ROOT).as_posix(),flags,args.compiler)
    parsed=omf.parse(obj.read_bytes())
    try:
     if name in ('CreateMonoSolidBrush','RandTurn','win_SetWinDrawHook'):
      from library_match import compare_member,import_symbols
      result=compare_member(parsed,raw,n,s,import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB'))
      result['comparison_scope']='complete object contributions including reviewed switch table'
     else:result=compare(parsed,raw,n,s,target)
    except FormatError as ex:result={'result':'VERIFIER_UNSUPPORTED','reason':str(ex)}
    result.update(configuration=label,flags=flags,probe=name,receipt=receipt,object_omf=parsed)
    if receipt.get('unsupported_option'):
     result['ignored_option_comparison']=result['result'];result['result']='UNSUPPORTED_COMPILER_OPTION'
   except FormatError as ex:result={'result':'COMPILE_ERROR','configuration':label,'flags':flags,'probe':name,'reason':str(ex)}
   results.append(result)
   print(name,label,result['result'],str(result.get('candidate_size',''))+'/'+str(target['size']),flush=True)
 stem=(args.compiler+'-')+(args.only.replace(',','-') if args.only else 'baseline' if args.baseline else 'matrix')+('-'+args.optimization.lstrip('/') if args.optimization else '')
 write_json(ROOT/f'evidence/experiments/toolchain/{stem}.json',{'exe_sha256':n['sha256'],'sym_sha256':s['sha256'],'probes':manifest,'results':results,'interpretation':'An unsuccessful source hypothesis does not rule out a compiler globally. Equivalent byte outputs do not distinguish settings.'})

if __name__=='__main__':main()
