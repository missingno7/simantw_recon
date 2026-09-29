"""Compare emulated C1/C2/C3 OBJ bytes with the DOSBox compiler service for every admitted msc700 source."""
import sys, json, time, hashlib
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools'))
from c2_emu import compile_c

targets = json.load(open(ROOT / 'src/recovery.json'))['targets']
jobs = {}
for k, v in targets.items():
    if v.get('compiler') == 'msc700' and v.get('proof') == 'BYTE_MATCHED_RECONSTRUCTION':
        jobs[(v['source'], tuple(v['flags']))] = k
jobs = sorted(jobs)
limit = int(sys.argv[1]) if len(sys.argv) > 1 else len(jobs)
jobs = jobs[:limit]
from compiler_service import compile_jobs
t = time.time()
ref = compile_jobs([dict(source=s, flags=list(f)) for s, f in jobs])
t_ref = time.time() - t
out = []
t = time.time()
for (s, f), (obj, rec) in zip(jobs, ref):
    refb = Path(obj).read_bytes() if obj else None
    try:
        r = compile_c((ROOT / s).read_bytes(), list(f))
        emb = r.obj
        err = None
    except Exception as ex:
        emb, err = None, repr(ex)[:300]
    out.append(dict(source=s, flags=list(f), same=(refb is not None and refb == emb),
                    ref=hashlib.sha256(refb).hexdigest()[:16] if refb else None,
                    emu=hashlib.sha256(emb).hexdigest()[:16] if emb else None, err=err))
t_emu = time.time() - t
same = sum(o['same'] for o in out)
print('jobs', len(out), 'identical', same, 'ref s', round(t_ref, 1), 'emu s', round(t_emu, 1))
for o in out:
    if not o['same']:
        print('DIFF', o)
json.dump(dict(identical=same, total=len(out), ref_seconds=t_ref, emu_seconds=t_emu, rows=out),
          open(ROOT / 'build/workers/f-alloc-emu/corpus_validation.json', 'w'), indent=1)
