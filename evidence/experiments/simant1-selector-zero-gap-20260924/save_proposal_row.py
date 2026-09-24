import json
from pathlib import Path
p=Path('evidence/recovery/units/proposals.json')
d=json.loads(p.read_text(encoding='utf-8'))
row=next(x for x in d['proposals'] if x['component']=='simant1:75F4')
out=Path('evidence/experiments/simant1-selector-zero-gap-20260924/proposal-simant1-75F4.json')
out.write_text(json.dumps(row,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'component':row['component'],'usable':row['usable'],'missing':row['missing'],'blocked':row['blocked']},indent=2))