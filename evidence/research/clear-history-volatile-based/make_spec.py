import json
from pathlib import Path
p = Path('evidence/experiments/clear-history-based/extern-based-spec.json')
spec = json.loads(p.read_text(encoding='utf-8'))
spec['axes'][0]['name'] = 'volatile_private_based_storage'
spec['axes'][0]['rationale'] = 'Test whether volatile qualified, uniquely named based arrays prevent MSC7 from reusing the PACK selector across adjacent range clears while retaining plain based offsets. This is a new qualifier/lifetime hypothesis; prior static/extern and based/far representation classes are not repeated.'
spec['axes'][0]['values'] = ['\n'.join(f'static volatile int __based(__segname("PACK")) histBuf{i}[64];' for i in range(1, 10))]
Path('evidence/research/clear-history-volatile-based/spec.json').write_text(json.dumps(spec, indent=2), encoding='utf-8')
