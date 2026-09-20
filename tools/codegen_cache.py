"""Content-addressed authentic compiler cache; comparisons are always rerun."""
import json, shutil
from common import ROOT, FormatError, identity, read_json, write_json, sha256
from compiler import compile_batch, validate_receipt

def compile_cached(jobs,compiler='msc700'):
    results=[None]*len(jobs);misses=[];keys=[];hits=0;validated_locks=set()
    tool_hash=sha256((ROOT/'layout/toolchain.json').read_bytes())
    wrapper_hash=sha256(b''.join((ROOT/p).read_bytes() for p in ['tools/compiler.py','tools/compiler_service.py','tools/compiler_worker.py','tools/compiler_wait.asm'])+(ROOT/'layout/compiler-service.json').read_bytes() if (ROOT/'layout/compiler-service.json').exists() else (ROOT/'tools/compiler.py').read_bytes())
    for i,job in enumerate(jobs):
        source=(ROOT/job['source']).read_bytes()
        key=sha256(json.dumps(dict(source=sha256(source),compiler=compiler,flags=job['flags'],toolchain=tool_hash,wrapper=wrapper_hash),sort_keys=True).encode())
        folder=ROOT/'build/codegen-cache'/key;folder.mkdir(parents=True,exist_ok=True)
        receipt_file=folder/'receipt.json';entry=None
        if receipt_file.exists():
            candidate=read_json(receipt_file)
            try:
                validate_receipt(candidate,validated_locks)
                if candidate['toolchain_lock_sha256']!=tool_hash or candidate['flags']!=job['flags'] or candidate['compiler']!=compiler or candidate['source_identity']['sha256']!=sha256(source):raise FormatError('cache identity differs')
                entry=(ROOT/candidate['object'],candidate)
            except (FormatError,FileNotFoundError):pass
        if entry:results[i]=entry;hits+=1;continue
        stable=folder/'INPUT.C';stable.write_bytes(source)
        misses.append(dict(source=stable.relative_to(ROOT).as_posix(),flags=job['flags']));keys.append((i,folder))
    compiled=compile_batch(misses,compiler) if misses else []
    for (i,folder),(obj,receipt) in zip(keys,compiled):
        if obj and not receipt['unsupported_option']:
            dest=folder/'OUTPUT.OBJ';shutil.copyfile(obj,dest)
            receipt=dict(receipt,object=dest.relative_to(ROOT).as_posix())
            write_json(folder/'receipt.json',receipt);obj=dest
        results[i]=(obj,receipt)
    return results,dict(hits=hits,misses=len(misses),environment_launches=sum(r['timing']['environment_launches'] for _,r in compiled) if compiled and all('environment_launches' in r.get('timing',{}) for _,r in compiled) else len({r['batch_directory'] for _,r in compiled}))
