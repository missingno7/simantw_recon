"""Diagnostic: recompile every admitted game source under alternative MSC7 profiles and
count how many stay opcode/size-identical to the original (invariance test for a
project-wide profile hypothesis). Search diagnostic only; no proof, no queue changes."""
import sys,json,os,shutil,collections
sys.path.insert(0,'tools')
import recovery_workflow as rw, omf, codegen_diff
from compiler import compile_batch
from common import fixture
import ne, mapsym
raw=fixture('SIMANTW.EXE'); image=ne.parse(raw)
rec=rw.recipes()
PROFILES={'Oeglw':['/Oeglw'],'Oegilw':['/Oegilw'],'Ox':['/Ox']}
jobs=[];meta=[]
for sym,r in rec.items():
    if r.get('compiler')!='msc700' or not r.get('source'): continue
    seg=r['code_segment']; ns=image['segments'][r['segment']-1]
    target=raw[ns['file_offset']+r['offset']:ns['file_offset']+r['offset']+r['size']]
    for name,opt in PROFILES.items():
        tmp=f'evidence/experiments/optimizer-profile/inv-{sym.strip("_")}-{name}.c'; shutil.copy(r['source'],tmp)
        jobs.append(dict(source=tmp,flags=['/AL','/G2','/Gs']+opt+['/NT'+seg])); meta.append((sym,seg,name,target,tmp))
print(len(jobs),'compiles',file=sys.stderr)
res=compile_batch(jobs,'msc700')
out=collections.defaultdict(dict); byseg=collections.defaultdict(lambda:collections.Counter())
for (sym,seg,name,target,tmp),(obj,rc) in zip(meta,res):
    try:
        m=omf.parse(obj if isinstance(obj,(bytes,bytearray)) else open(obj,'rb').read())
        cb=bytes.fromhex([s for s in m['segments'] if s['class']=='CODE'][0]['data_hex'])
        c=codegen_diff.compare_code(target,cb); same=(len(cb)==len(target) and c.get('opcode_matches')==c.get('opcode_total'))
        out[sym][name]=[len(cb),c.get('opcode_matches'),c.get('opcode_total'),same]
        byseg[seg][name+('_same' if same else '_diff')]+=1
    except Exception as e: out[sym][name]='ERR '+str(e)[:50]; byseg[seg][name+'_err']+=1
    try: os.remove(tmp)
    except OSError: pass
json.dump(out,open('evidence/experiments/optimizer-profile/invariance.json','w'),indent=1)
for seg,c in sorted(byseg.items()): print(seg, dict(c))
