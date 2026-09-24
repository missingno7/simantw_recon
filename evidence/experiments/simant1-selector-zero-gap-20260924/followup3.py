from pathlib import Path
import json, shutil, sys
ROOT=Path(__file__).resolve().parents[3]
HERE=Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT/'tools'))
from compiler import compile_batch
from omf import parse
FLAGS=['/AL','/G2','/Gs','/Oelw','/NTSIMANT1_MODULE']
path=HERE/'followup3_zero_scalars.c'
obj,receipt=compile_batch([{'source':path.relative_to(ROOT).as_posix(),'flags':FLAGS}],compiler='msc700',session_limit=96)[0]
row={'source':path.relative_to(ROOT).as_posix(),'receipt':receipt}
if obj is not None:
    dest=HERE/'followup3_zero_scalars.obj'
    shutil.copyfile(obj,dest)
    m=parse(dest.read_bytes())
    row.update(object_path=dest.relative_to(ROOT).as_posix(),object_sha256=m['sha256'])
    row['segments']=[{'index':s['index'],'name':s['name'],'class':s['class'],'length':s['length'],'data_hex':s['data_hex']} for s in m['segments']]
    row.update(fixups=m['fixups'],publics=m['publics'],externals=m['externals'])
report={'experiment':'simant1:75F4 zero __segment scalar CONST interleaving follow-up','scope':'one isolated MSC C7 compile; three separately declared scalar __segment objects are read by reserved synthetic POOLSTUB_TEXT scaffold; no target body or owner identity','compiler':'msc700','flags':FLAGS,'toolchain_lock_sha256':receipt.get('toolchain_lock_sha256'),'source_sha256':receipt.get('source_identity',{}).get('sha256'),'admitted_form_evidence':'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c declares static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");','control_from_prior_batch':'control_no_gap in results.json, same source/profile and 74-byte CONST with 37 fixups','treatment':row}
(HERE/'followup3-results.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'exit_code':receipt['exit_code'],'source_sha256':report['source_sha256'],'object_sha256':row.get('object_sha256'),'segments':[(s['name'],s['length']) for s in row.get('segments',[])]},indent=2))