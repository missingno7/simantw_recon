"""Diagnostic sweep: every escalated job whose cause is a code-shape family gets its best
candidate recompiled under /Oelw (control), /Oeglw and /Oegilw; scores are the search
diagnostic only (no proof, no queue changes)."""
import sys,json,glob,shutil,os
sys.path.insert(0,'tools')
from compiler import compile_source
import omf, codegen_diff
FAM={'REGISTER_ALLOCATION','EXPRESSION_SHAPE','OPTIMIZER_VARIANT_REQUIRED','LOCAL_FRAME_LAYOUT'}
rows=[]
for jf in sorted(glob.glob('evidence/recovery/workflow/jobs/*/job.json')):
    j=json.load(open(jf)); d=os.path.dirname(jf)
    if j.get('status')!='ESCALATED' or not (set(j.get('blockers') or [])&FAM): continue
    best=None
    for rf in glob.glob(f'{d}/attempt*/results.json'):
        r=json.load(open(rf))
        for x in r.get('results',[]):
            g=(x.get('comparison') or {}).get('diagnostic') or {}
            if g.get('opcode_matches') is None: continue
            key=(g['opcode_matches'],-abs(g.get('candidate_bytes',0)-g.get('target_bytes',0)))
            if best is None or key>best[0]: best=(key,os.path.join(os.path.dirname(rf),f"candidate{x['candidate']:04d}.c"),g)
    if not best: continue
    packet=json.load(open(f'{d}/packet.json')); seg=packet.get('code_segment') or packet.get('segment_name')
    target=bytes.fromhex(''.join(r['bytes'] for r in packet['disassembly']).replace('??','00'))
    row={'job':os.path.basename(d),'cause':j['blockers'],'target':len(target),'best':best[1]}
    for name,opt in {'Oelw':['/Oelw'],'Oeglw':['/Oeglw'],'Oegilw':['/Oegilw']}.items():
        tmp=f'evidence/experiments/optimizer-profile/sweep-{row["job"]}-{name}.c'; shutil.copy(best[1],tmp)
        try:
            obj,rc=compile_source(tmp,['/AL','/G2','/Gs']+opt+['/NT'+seg],'msc700')
            m=omf.parse(obj if isinstance(obj,(bytes,bytearray)) else open(obj,'rb').read())
            cb=bytes.fromhex([s for s in m['segments'] if s['class']=='CODE'][0]['data_hex'])
            c=codegen_diff.compare_code(target,cb); row[name]=[len(cb),c.get('opcode_matches'),c.get('opcode_total')]
        except Exception as e: row[name]=str(e)[:60]
        os.remove(tmp)
    rows.append(row); print(json.dumps(row),flush=True)
json.dump(rows,open('evidence/experiments/optimizer-profile/sweep.json','w'),indent=1)
