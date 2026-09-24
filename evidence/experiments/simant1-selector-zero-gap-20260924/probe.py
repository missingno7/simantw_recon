from pathlib import Path
import json,shutil,sys
ROOT=Path(__file__).resolve().parents[3]
HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT/'tools'))
from compiler import compile_batch
from omf import parse
FLAGS=['/AL','/G2','/Gs','/Oelw','/NTSIMANT1_MODULE']
def refs(prefix,n): return ''.join(f'extern int far {prefix}{i:02d}[];\n' for i in range(n))
def readfn(name,prefix,n):
 lines=[f'void far {name}(void) {{','    volatile int sink;']
 lines += [f'    sink = {prefix}{i:02d}[0];' for i in range(n)]
 lines.append('}')
 return '\n'.join(lines)+'\n'
zero='/* Fixture-only six-byte zero object; no historical owner is asserted. */\nconst unsigned char FixtureZeroGap[6] = {0,0,0,0,0,0};\n'
prefix=refs('FixturePrefix',27); exitrefs=refs('FixtureExit',3); disrefs=refs('FixtureDis',4); nextrefs=refs('FixtureNext',1); initrefs=refs('FixtureInitial',2)
functions=readfn('ProbePrefix','FixturePrefix',27)+readfn('ProbeExit','FixtureExit',3)+readfn('ProbeDis','FixtureDis',4)+readfn('ProbeNext','FixtureNext',1)+readfn('ProbeInitial','FixtureInitial',2)
sources={
 'control_no_gap':'/* Synthetic-only C7 selector-allocation microfixture. */\n'+prefix+exitrefs+disrefs+nextrefs+initrefs+functions,
 'treatment_zero_between_groups':'/* Synthetic-only C7 selector-allocation microfixture. */\n'+prefix+exitrefs+disrefs+nextrefs+initrefs+readfn('ProbePrefix','FixturePrefix',27)+readfn('ProbeExit','FixtureExit',3)+zero+readfn('ProbeDis','FixtureDis',4)+readfn('ProbeNext','FixtureNext',1)+readfn('ProbeInitial','FixtureInitial',2)
}
jobs=[]
for name,source in sources.items():
 path=HERE/(name+'.c');path.write_text(source,encoding='ascii')
 jobs.append({'source':path.relative_to(ROOT).as_posix(),'flags':FLAGS})
compiled=compile_batch(jobs,compiler='msc700',session_limit=96)
rows=[]
for (name,_),(obj,receipt) in zip(sources.items(),compiled):
 row={'name':name,'receipt':receipt}
 if obj is None: row['error']=receipt.get('stdout','compile failed');rows.append(row);continue
 dest=HERE/(name+'.obj');shutil.copyfile(obj,dest);m=parse(dest.read_bytes())
 row.update(object_path=dest.relative_to(ROOT).as_posix(),object_sha256=m['sha256'])
 row['segments']=[{'index':s['index'],'name':s['name'],'class':s['class'],'length':s['length'],'data_hex':s['data_hex']} for s in m['segments']]
 row.update(fixups=m['fixups'],publics=m['publics'],externals=m['externals'])
 rows.append(row)
report={'experiment':'simant1:75F4 six-zero CONST interleaving microfixture','scope':'isolated MSC C7 compile and OMF layout inspection; no production source, unit, reissue, or admission','compiler':'msc700','flags':FLAGS,'toolchain_lock_sha256':next((r['receipt'].get('toolchain_lock_sha256') for r in rows if r.get('receipt')),None),'predicted_target_layout':['baseline preceding 54-byte CONST block','_ExitNest selector words C3E2/C3E4/C3E6 -> segment 8','six zero bytes C3E8/C3EA/C3EC with no relocations','_GetMyDis selector words C3EE/C3F0/C3F2/C3F4 -> segment 8','_GetMyNextRandDirs C3F6 -> segment 9','_GetMyInitialRandDir C3F8/C3FA -> segment 9'],'fixture_design':['27 synthetic prefix selector references (54B)','3 synthetic selector references in first group','treatment-only fixture-local six-byte zero const object between first and second groups','4 synthetic selector references in second group','3 synthetic selector references in final group'],'synthetic_names_only':True,'candidates':rows}
(HERE/'results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'candidates':len(rows),'outcomes':[{'name':r['name'],'exit_code':r['receipt']['exit_code'],'object_sha256':r.get('object_sha256'),'segments':[(s['name'],s['length']) for s in r.get('segments',[])]} for r in rows]},indent=2))
