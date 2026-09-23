import json
from pathlib import Path
here=Path(__file__).parent
report=json.loads((here/'retest/results.json').read_text())
row=report['results'][0]
c=row['comparison']
old_dir=Path('evidence/recovery/workflow/jobs/ReadConfig-09909209c9')
old={f'attempt{i:02d}':json.loads((old_dir/f'attempt{i:02d}/results.json').read_text())['results'][0]['receipt']['object_identity']['sha256'] for i in range(1,5)}
new=row['receipt']['object_identity']['sha256']
aligned=c.get('diagnostic',{}).get('aligned_asm',[])
out={
    'production_state':'ESCALATED; unchanged',
    'strict_result':c['result'],
    'profile':row['receipt']['flags'],
    'target_extent_bytes':c.get('target_function_extent',{}).get('size'),
    'candidate_code_bytes':c.get('code_contribution_size'),
    'literal_compared':c.get('literal_compared'),
    'literal_equal':c.get('literal_equal'),
    'fixups_equal':c.get('fixups_equal'),
    'fixups_total':c.get('fixups_total'),
    'diagnostic':{k:c.get('diagnostic',{}).get(k) for k in ['opcode_total','opcode_matches','immediate_differences','memory_operand_differences','branch_target_differences','stack_local_differences','score']},
    'candidate_object_sha256':new,
    'previous_attempt_object_sha256':old,
    'duplicate_of_previous_attempt':[name for name,digest in old.items() if digest==new],
    'opening_alignment':[r for r in aligned if r.get('target_offset') in [6,10,15,34,38,42,47,49]],
    'private_constraint_placements':c.get('private_constraint_placements'),
    'contributions':[{k:x.get(k) for k in ['segment','original_segment','original_offset','length','literal_compared','literal_equal']} for x in c.get('contributions',[])],
    'first_issues':c.get('issues',[])[:12],
}
(here/'retest-summary.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
