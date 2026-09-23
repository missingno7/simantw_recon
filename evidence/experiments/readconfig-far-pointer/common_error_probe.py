"""Test a shared local far-string diagnostic path matching target control flow."""
import json
import subprocess
import sys
from pathlib import Path

ROOT=Path(__file__).resolve().parents[3]
HERE=Path(__file__).resolve().parent
base=(HERE/'candidate.c').read_text()
head,tail=base.split('    if (fd > 0) {',1)
success,closing=tail.rsplit('\n    }\n}\n',1)
if closing.strip(): raise SystemExit('unexpected source tail')
old='''            MessageBox(rootWnd, configFileMissingStr, "Missing config", 0x30);
            exit(1);'''.replace('+','')
new='''            errorMessage = "Bad 'Display Mode' in configuration file";
            goto show_error;'''.replace('+','')
if success.count(old)!=1: raise SystemExit('invalid-display error block changed')
success=success.replace(old,new)
if 'Missing config' in success: raise SystemExit('old error string remains')
head=head.replace('    char digit;\n','    char digit;\n    char far *errorMessage;\n')
body='''    if (fd <= 0) {
        errorMessage = configFileMissingStr;
        goto show_error;
    }
'''.replace('+','')+success+'''
show_error:
    MessageBox(rootWnd, errorMessage, "Message", 0x30);
    exit(1);
}
'''.replace('+','')
source=HERE/'common-error.c'
source.write_text(head+body)
spec=dict(symbol="_ReadConfig",source=source.relative_to(ROOT).as_posix(),compiler="msc700",
          flags=["/AL","/G2","/Gs","/Oelw","/NTGR_MODULE"],max_candidates=1,axes=[],
          semantic_summary="Isolated test of the shared error path observed in the target: both nonpositive _lopen and invalid display-mode cases set a far message pointer and branch to MessageBox/exit.",
          binding_evidence=["The target's _lopen failure path loads _configFileMissingStr, sets its offset and segment, then jumps to the MessageBox call block.","The invalid display-mode path sets a local pointer to the private literal Bad 'Display Mode' in configuration file and reaches the same call block.","Both paths pass caption 'Message' and call exit(1).", "Far-object declarations were tested under the assigned profile in README.md."],publics=["_ReadConfig"])
specpath=HERE/'common-error-spec.json';specpath.write_text(json.dumps(spec,indent=2)+'\n')
out=HERE/'branch-run/common-error'
subprocess.run([sys.executable,"tools/codegen_grinder.py",specpath.relative_to(ROOT).as_posix(),"--out",out.relative_to(ROOT).as_posix(),"--cache"],cwd=ROOT,check=True)
report=json.loads((out/'results.json').read_text());row=report['results'][0];c=row['comparison']
summary=dict(strict_result=c['result'],object_sha256=row['receipt']['object_identity']['sha256'],
             source_sha256=row['receipt']['source_identity']['sha256'],literal_compared=c.get('literal_compared'),literal_equal=c.get('literal_equal'),
             fixups_equal=c.get('fixups_equal'),fixups_total=c.get('fixups_total'),
             diagnostic={k:c.get('diagnostic',{}).get(k) for k in ['opcode_total','opcode_matches','immediate_differences','memory_operand_differences','branch_target_differences','stack_local_differences','score']},
             issues=c.get('issues',[]),
             opening_alignment=[x for x in c.get('diagnostic',{}).get('aligned_asm',[]) if x.get('target_offset') in [6,10,15,20,22,26,30,34,38,42,47,49,52,389,393,396,397,401,403]])
(HERE/'common-error-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps({k:summary[k] for k in ['strict_result','object_sha256','literal_compared','literal_equal','fixups_equal','fixups_total','diagnostic','opening_alignment']},indent=2))
