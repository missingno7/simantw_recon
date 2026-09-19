"""Re-verify recorded fresh objects after extending supported OMF semantics.

Receipts, source hashes and tool lock must still validate. Nothing is inferred
from previous scores. Compile errors with no current object remain errors.
"""
import argparse
from common import ROOT,read_json,write_json,fixture,FormatError
from compiler import validate_receipt
from matcher import compare
from library_match import compare_member,import_symbols
import ne,mapsym,omf

def main():
 ap=argparse.ArgumentParser();ap.add_argument('file');args=ap.parse_args();path=ROOT/args.file;x=read_json(path)
 raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'));im=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
 receipts={}
 for p in sorted((ROOT/'build').glob('C*/receipt.json'),key=lambda p:p.stat().st_mtime):
  r=read_json(p);receipts[(r['compiler'],r['source'],tuple(r['flags']))]=r
 compiler=path.name.split('-')[0];rows=[]
 for old in x['results']:
  t=next(t for t in x['probes'] if t['symbol']=='_'+old['probe'])
  r=receipts.get((compiler,t['source'],tuple(old['flags'])))
  row={k:old[k] for k in ('configuration','flags','probe')}
  try:
   if not r or 'object_identity' not in r:raise FormatError('no successful compile receipt')
   validate_receipt(r);m=omf.parse((ROOT/r['object']).read_bytes())
   if old['probe'] in ('CreateMonoSolidBrush','RandTurn','win_SetWinDrawHook','ed_MoveTo'):
    result=compare_member(m,raw,n,s,im)
   else:result=compare(m,raw,n,s,t)
   row.update(result,receipt=r,object_omf=m)
  except FormatError as ex:row.update(result='VERIFIER_UNSUPPORTED',reason=str(ex),receipt=r)
  if (r and r.get('unsupported_option')) or '/G3' in old['flags']:
   row['ignored_option_comparison']=row['result'];row['result']='UNSUPPORTED_COMPILER_OPTION'
   row['reason']='Requested option is invalid/ignored by this 16-bit compiler; fallback bytes do not test that setting.'
  if old['configuration'] in ('pascal','fastcall') and row.get('result')=='VERIFIER_UNSUPPORTED':row['result']='ABI_MISMATCH'
  rows.append(row)
 x['results']=rows;x['rechecked']=True;write_json(path,x)
 from collections import Counter
 print(path.name,Counter(r['result'] for r in rows))

if __name__=='__main__':main()
