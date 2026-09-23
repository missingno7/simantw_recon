"""Small branch-layout batch for the isolated ReadConfig candidate."""
import json
import subprocess
import sys
from pathlib import Path

ROOT=Path(__file__).resolve().parents[3]
HERE=Path(__file__).resolve().parent
base=(HERE/'candidate.c').read_text()
head,tail=base.split('    if (fd > 0) {',1)
success,closing=tail.rsplit('\n    }\n}\n',1)
if closing.strip():
    raise SystemExit('unexpected source tail')
success=success.replace(
    'MessageBox(rootWnd, configFileMissingStr, "Missing config", 0x30);',
    'MessageBox(rootWnd, "Bad \'Display Mode\' in configuration file", "Message", 0x30);'
)
if 'Missing config' in success:
    raise SystemExit('failed to replace previous invalid-token message hypothesis')
fail='''        MessageBox(rootWnd, configFileMissingStr, "Message", 0x30);
        exit(1);'''.replace('+','')
forms={
    'failure_first': '    if (fd <= 0) {\n'+fail+'\n    } else {\n'+success+'\n    }\n}\n',
    'success_first_else': '    if (fd > 0) {\n'+success+'\n    } else {\n'+fail+'\n    }\n}\n',
}
flags=["/AL","/G2","/Gs","/Oelw","/NTGR_MODULE"]
for label,body in forms.items():
    source=HERE/f'{label}.c'
    source.write_text(head+body)
    spec=dict(symbol="_ReadConfig",source=source.relative_to(ROOT).as_posix(),compiler="msc700",flags=flags,
              max_candidates=1,axes=[],semantic_summary="Isolated test of the target-evidenced nonpositive _lopen failure branch and two equivalent source layouts; preserve the current parser hypothesis.",
              binding_evidence=["Target branches to parsing only when the _lopen result is positive.","Target failure path reads the far pointer object _configFileMissingStr, calls USER MessageBox with caption 'Message', then calls exit(1).","Far-object declaration ABI is recorded in README.md."],publics=["_ReadConfig"])
    specpath=HERE/f'{label}-spec.json'
    specpath.write_text(json.dumps(spec,indent=2)+'\n')
    out=HERE/'branch-run'/label
    subprocess.run([sys.executable,"tools/codegen_grinder.py",specpath.relative_to(ROOT).as_posix(),"--out",out.relative_to(ROOT).as_posix(),"--cache"],cwd=ROOT,check=True)

# Summarize strict comparisons and deduplicate by actual C7 OMF identity.
rows=[]
for label in forms:
    result=json.loads((HERE/'branch-run'/label/'results.json').read_text())
    row=result['results'][0]
    c=row['comparison']
    rows.append(dict(label=label,strict_result=c['result'],object_sha256=row['receipt']['object_identity']['sha256'],
                     source_sha256=row['receipt']['source_identity']['sha256'],literal_compared=c.get('literal_compared'),
                     literal_equal=c.get('literal_equal'),fixups_equal=c.get('fixups_equal'),fixups_total=c.get('fixups_total'),
                     diagnostic={k:c.get('diagnostic',{}).get(k) for k in ['opcode_total','opcode_matches','immediate_differences','memory_operand_differences','branch_target_differences','stack_local_differences','score']},
                     issues=c.get('issues',[]),
                     opening_alignment=[x for x in c.get('diagnostic',{}).get('aligned_asm',[]) if x.get('target_offset') in [6,10,15,20,22,27,30,32,34,38,42,47,49,52]]))
classes={}
for row in rows: classes.setdefault(row['object_sha256'],[]).append(row['label'])
summary=dict(profile=flags,production_job="ReadConfig-09909209c9 remains ESCALATED and unchanged",forms=rows,
             effective_object_classes=list(classes.values()))
(HERE/'branch-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps(dict(forms=[dict(label=r['label'],strict_result=r['strict_result'],literal_equal=r['literal_equal'],literal_compared=r['literal_compared'],fixups_equal=r['fixups_equal'],fixups_total=r['fixups_total'],opcode_matches=r['diagnostic']['opcode_matches'],score=r['diagnostic']['score']) for r in rows],effective_object_classes=list(classes.values())),indent=2))
