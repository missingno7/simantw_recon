from pathlib import Path
import json,shutil,sys
ROOT=Path(__file__).resolve().parents[3]
HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT/'tools'))
from compiler import compile_batch
from omf import parse
FLAGS=['/AL','/G2','/Gs','/Oelw','/NTSIMANT1_MODULE']
base=(HERE/'treatment_zero_between_groups.c').read_text(encoding='ascii')
old='/* Fixture-only six-byte zero object; no historical owner is asserted. */\nconst unsigned char FixtureZeroGap[6] = {0,0,0,0,0,0};\n'
new='''/* Fixture-only, six-byte zero __segment array; no historical owner is asserted. */
static const __segment near FixtureZeroGap[3] = {0,0,0};
void far ProbeZeroGap(void);
#pragma alloc_text(POOLSTUB_TEXT, ProbeZeroGap)
void far ProbeZeroGap(void)
{
    volatile int sink;
    sink = FixtureZeroGap[0];
}
'''
assert base.count(old)==1
source=base.replace(old,new)
path=HERE/'followup2_zero_segment.c';path.write_text(source,encoding='ascii')
compiled=compile_batch([{'source':path.relative_to(ROOT).as_posix(),'flags':FLAGS}],compiler='msc700',session_limit=96)[0]
obj,receipt=compiled
row={'source':path.relative_to(ROOT).as_posix(),'receipt':receipt}
if obj is not None:
 dest=HERE/'followup_zero_segment.obj';shutil.copyfile(obj,dest);m=parse(dest.read_bytes())
 row.update(object_path=dest.relative_to(ROOT).as_posix(),object_sha256=m['sha256'])
 row['segments']=[{'index':s['index'],'name':s['name'],'class':s['class'],'length':s['length'],'data_hex':s['data_hex']} for s in m['segments']]
 row.update(fixups=m['fixups'],publics=m['publics'],externals=m['externals'])
report={'experiment':'simant1:75F4 zero __segment CONST object follow-up','scope':'one isolated MSC C7 compile; reserved synthetic POOLSTUB_TEXT code references the fixture object; no target body or owner identity','compiler':'msc700','flags':FLAGS,'toolchain_lock_sha256':receipt.get('toolchain_lock_sha256'),'source_sha256':receipt.get('source_identity',{}).get('sha256'),'admitted_form_evidence':'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c declares static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");','control_from_prior_batch':'control_no_gap in results.json, same source/profile and 74-byte CONST with 37 fixups','treatment':row}
(HERE/'followup2-results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'exit_code':receipt['exit_code'],'object_sha256':row.get('object_sha256'),'segments':[(s['name'],s['length']) for s in row.get('segments',[])]},indent=2))
