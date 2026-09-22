"""Exercise handoff infrastructure and preserve a reproducible readiness receipt."""
import json
import re
import subprocess
import sys
from common import ROOT, FormatError, read_json, write_json, identity
from codegen_grinder import run
from recovery_gate import admission_targets, check_member
from recovery_workflow import STATE, timestamp, workflow_lock, recover_transaction
from compiler import validate_receipt
from library_match import import_symbols
from common import fixture
import mapsym, ne, omf


def main():
    with workflow_lock():
        recover_transaction()
        output=ROOT/'build/handoff-validation';output.mkdir(parents=True,exist_ok=True)
        command=[sys.executable,'-m','unittest','discover','-s','tests','-v']
        tests=subprocess.run(command,cwd=ROOT,capture_output=True,timeout=600)
        log=(tests.stdout+tests.stderr).decode('utf-8',errors='replace');(output/'tests.log').write_text(log,encoding='utf-8')
        count=re.search(r'Ran (\d+) tests',log)
        receipt=dict(checked=timestamp(),passed=False,tests=dict(command=command,exit_code=tests.returncode,count=int(count.group(1)) if count else None,log='build/handoff-validation/tests.log',log_identity=identity(output/'tests.log')))
        if tests.returncode:
            write_json(STATE/'validation.json',receipt);raise FormatError('handoff tests failed; see '+receipt['tests']['log'])
        job=STATE/'jobs/IsItWall-da7d76733f'
        spec=read_json(job/'attempt01/results.json')['spec']
        first=run(spec,'build/handoff-validation/cache-first',cache=True)
        replay=run(spec,'build/handoff-validation/cache-replay',cache=True)
        if replay['cache']['hits']!=replay['candidates'] or replay['environment_launches'] or not replay['exact_candidates']:raise FormatError('cache replay did not retain exact matches without a compiler launch')
        if [r['comparison'] for r in first['results']]!=[r['comparison'] for r in replay['results']]:raise FormatError('fresh comparisons differ after cache replay')
        receipt['cache']=dict(first=first['cache'],replay=replay['cache'],candidates=replay['candidates'],comparisons_rechecked=True,exact_candidates=replay['exact_candidates'],evidence='build/handoff-validation/cache-replay/results.json')
        best=replay['results'][0];validate_receipt(best['receipt']);module=omf.parse((ROOT/best['receipt']['object']).read_bytes())
        raw=fixture('SIMANTW.EXE');image=ne.parse(raw);symbols=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
        targets=admission_targets(module,raw,image,symbols,['_'+'IsItWall'])
        receipt['pilot_revalidation']=check_member(module,raw,image,symbols,imports,targets)
        runner=read_json(ROOT/'evidence/experiments/runner/service-stress.json')
        if not runner['passed'] or runner['jobs']<400 or any(identity(ROOT/p)!=expected for p,expected in runner['inputs'].items()):raise FormatError('persistent service stress validation missing or stale')
        receipt['factory']=dict(runner_evidence='evidence/experiments/runner/service-stress.json',jobs=runner['jobs'],elapsed_seconds=runner['elapsed_seconds'],environment_launches=runner['environment_launches'])
        receipt['inputs']={p.relative_to(ROOT).as_posix():identity(p) for folder in ('tools','tests') for p in sorted((ROOT/folder).glob('*.py'))}
        for name in ['layout/toolchain.json','layout/fixtures.json','layout/runtime-ownership.json','layout/compiler-service.json','layout/compiler-profiles.json','tools/tu_assembly.py','tools/compiler_wait.asm','tools/runner_host.asm']:receipt['inputs'][name]=identity(ROOT/name)
        receipt['passed']=True;write_json(STATE/'validation.json',receipt)
        print(json.dumps(dict(passed=True,tests=receipt['tests']['count'],cache=receipt['cache'],pilot=receipt['pilot_revalidation']['result']),indent=2))

if __name__=='__main__':main()
