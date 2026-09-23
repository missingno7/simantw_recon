"""Move the common diagnostic label into switch-default code layout."""
import json
import subprocess
import sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
HERE=Path(__file__).resolve().parent
source=(HERE/'common-error.c').read_text()
tail='''show_error:
    MessageBox(rootWnd, errorMessage, "Message", 0x30);
    exit(1);
}'''.replace('+','')
inside='''show_error:
            MessageBox(rootWnd, errorMessage, "Message", 0x30);
            exit(1);'''.replace('+','')
if source.count(tail)!=1: raise SystemExit('expected one terminal common error label')
source=source.replace(tail,'}',1)
old='''            errorMessage = "Bad 'Display Mode' in configuration file";
            goto show_error;'''.replace('+','')
if source.count(old)!=1: raise SystemExit('expected one switch-default message assignment')
source=source.replace(old,'            errorMessage = "Bad \'Display Mode\' in configuration file";\n'+inside,1)
path=HERE/'inline-error.c';path.write_text(source)
spec=dict(symbol="_ReadConfig",source=path.relative_to(ROOT).as_posix(),compiler="msc700",
          flags=["/AL","/G2","/Gs","/Oelw","/NTGR_MODULE"],max_candidates=1,axes=[],
          semantic_summary="Isolated test placing the shared MessageBox/exit label at the switch-default block, which the target shares with the open-failure jump.",
          binding_evidence=["Target open failure initializes the error pointer then jumps to the same MessageBox sequence reached by the invalid display default.","The default target path loads the private literal Bad 'Display Mode' in configuration file; both use caption Message.","See the bounded far-object ABI evidence in README.md."],publics=["_ReadConfig"])
specpath=HERE/'inline-error-spec.json';specpath.write_text(json.dumps(spec,indent=2)+'\n')
out=HERE/'branch-run/inline-error'
subprocess.run([sys.executable,"tools/codegen_grinder.py",specpath.relative_to(ROOT).as_posix(),"--out",out.relative_to(ROOT).as_posix(),"--cache"],cwd=ROOT,check=True)
report=json.loads((out/'results.json').read_text());row=report['results'][0];c=row['comparison']
summary=dict(strict_result=c['result'],object_sha256=row['receipt']['object_identity']['sha256'],source_sha256=row['receipt']['source_identity']['sha256'],
             literal_compared=c.get('literal_compared'),literal_equal=c.get('literal_equal'),fixups_equal=c.get('fixups_equal'),fixups_total=c.get('fixups_total'),
             diagnostic={k:c.get('diagnostic',{}).get(k) for k in ['opcode_total','opcode_matches','immediate_differences','memory_operand_differences','branch_target_differences','stack_local_differences','score']},
             issues=c.get('issues',[]),
             opening_alignment=[x for x in c.get('diagnostic',{}).get('aligned_asm',[]) if x.get('target_offset') in [6,10,15,20,22,26,30,34,38,42,47,49,52,389,393,396,397,401,403]])
(HERE/'inline-error-summary.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps({k:summary[k] for k in ['strict_result','object_sha256','literal_equal','literal_compared','fixups_equal','fixups_total','diagnostic','opening_alignment']},indent=2))
