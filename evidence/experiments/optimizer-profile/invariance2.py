"""Diagnostic: for every admitted msc700 source, compile under the locked profile and
under alternatives; count sources whose CODE segment bytes are identical to the locked
profile's object (true profile invariance). No proof, no queue changes."""
import sys,json,os,shutil,collections
sys.path.insert(0,'tools')
import recovery_workflow as rw, omf
from compiler import compile_batch
rec=rw.recipes()
PROFILES={'Oelw':['/Oelw'],'Oeglw':['/Oeglw'],'Oegilw':['/Oegilw'],'GA':['/Oelw','/GA']}
jobs=[];meta=[]
for sym,r in rec.items():
    if r.get('compiler')!='msc700' or not r.get('source'): continue
    for name,opt in PROFILES.items():
        tmp=f'evidence/experiments/optimizer-profile/inv2-{sym.strip("_")}-{name}.c'; shutil.copy(r['source'],tmp)
        jobs.append(dict(source=tmp,flags=['/AL','/G2','/Gs']+opt+['/NT'+r['code_segment']])); meta.append((sym,r['code_segment'],name,tmp))
res=compile_batch(jobs,'msc700')
code=collections.defaultdict(dict)
for (sym,seg,name,tmp),(obj,rc) in zip(meta,res):
    try:
        m=omf.parse(obj if isinstance(obj,(bytes,bytearray)) else open(obj,'rb').read())
        code[sym][name]=[s for s in m['segments'] if s['class']=='CODE'][0]['data_hex']
    except Exception as e: code[sym][name]=None
    try: os.remove(tmp)
    except OSError: pass
byseg=collections.defaultdict(collections.Counter); changed=collections.defaultdict(list)
for sym,r in rec.items():
    if sym not in code: continue
    base=code[sym].get('Oelw'); seg=r['code_segment']
    for name in PROFILES:
        if name=='Oelw': continue
        same=(code[sym].get(name)==base and base is not None)
        byseg[seg][name+('_same' if same else '_diff')]+=1
        if not same: changed[name].append(sym)
json.dump({'changed':changed},open('evidence/experiments/optimizer-profile/invariance2.json','w'),indent=1)
for seg,c in sorted(byseg.items()): print(seg, dict(sorted(c.items())))
print({k:len(v) for k,v in changed.items()}, 'of', len(code))
