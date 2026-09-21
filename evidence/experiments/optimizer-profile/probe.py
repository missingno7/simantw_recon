"""Diagnostic only: recompile parked best candidates under alternative MSC7 optimizer
profiles and score them against the target with the search diagnostic (no proof,
no queue changes)."""
import sys,json,glob,os,shutil
sys.path.insert(0,'tools')
from compiler import compile_source
import omf, codegen_diff
ROOT='.'
CASES=[('DrawMapCursor-637580dae4','attempt01/candidate0000.c'),('SetCasteProd-95e6cfed26','attempt02/candidate0000.c'),
       ('CenterEdit-4781028f52','attempt02/candidate0000.c'),('win_DrawHBar-e417256fd5','attempt05/candidate0000.c'),
       ('AddRedAnts-9213beafe4','attempt01/candidate0000.c'),('SmoothAlarm-7dc5275417','attempt06/candidate0000.c'),
       ('DoRepoFly-076615193e','attempt05/candidate0005.c'),('SeparateFile-7ddbb3ac46','attempt03/candidate0000.c'),
       ('CarpetFloorL-1369f86e7a','attempt01/candidate0000.c'),('TryMoveDirR-6dd77c4f90','attempt02/candidate0000.c'),
       ('hanim_HideObject-579ae04c92','attempt05/candidate0000.c'),('IsPointInIsoTri-72e19122a6','attempt06/candidate0000.c')]
PROFILES={'Oelw':['/Oelw'],'Oeglw':['/Oeglw'],'Oegilw':['/Oegilw'],'Ox':['/Ox'],'Oegilwt':['/Oegilwt'],'Oaeglw':['/Oaeglw']}
out=[]
for job,cand in CASES:
    d=f'evidence/recovery/workflow/jobs/{job}'
    packet=json.load(open(f'{d}/packet.json'))
    seg=packet.get('code_segment') or packet.get('segment_name')
    target=bytes.fromhex(packet['target_bytes_hex']) if 'target_bytes_hex' in packet else bytes.fromhex(''.join(r['bytes'] for r in packet['disassembly']).replace('??','00'))
    src=f'{d}/{cand}'
    row={'job':job,'candidate':cand,'target_bytes':len(target)}
    for name,opt in PROFILES.items():
        flags=['/AL','/G2','/Gs']+opt+['/NT'+seg]
        tmp=f'evidence/experiments/optimizer-profile/{job}-{name}.c'; shutil.copy(src,tmp)
        try:
            obj,receipt=compile_source(tmp,flags,'msc700')
            m=omf.parse(obj if isinstance(obj,(bytes,bytearray)) else open(obj,'rb').read()); code=[s for s in m['segments'] if s['class']=='CODE'][0]
            cb=bytes.fromhex(code['data_hex'])
            cmp=codegen_diff.compare_code(target,cb)
            row[name]=dict(bytes=len(cb),opcodes=f"{cmp.get('opcode_matches')}/{cmp.get('opcode_total')}",layout=cmp.get('instruction_layout_match'),regdiff=cmp.get('register_only_differences'))
        except Exception as e:
            row[name]='ERR '+str(e)[:80]
    out.append(row); print(json.dumps(row))
json.dump(out,open('evidence/experiments/optimizer-profile/results.json','w'),indent=1)
