"""Canonical raw-OMF and strict-match oracle for persistent C7 workers."""
import argparse,time
from common import ROOT,read_json,write_json,identity,FormatError,fixture
from compiler import verify_lock
from compiler_worker import Win31Worker
from library_match import import_symbols,compare_member
from matcher import compare
import omf,ne,mapsym


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--workers',type=int,default=1);args=ap.parse_args()
    if not 1<=args.workers<=4:raise FormatError('worker count must be 1..4')
    inputs={p:identity(ROOT/p) for p in ['tools/compiler_worker.py','tools/compiler_wait.asm','layout/toolchain.json']}
    if args.workers>1:
        prior=read_json(ROOT/'evidence/experiments/runner/worker-1.json')
        if not prior['passed'] or prior['inputs']!=inputs:raise FormatError('prove unchanged single worker before concurrency')
    verify_lock(read_json(ROOT/'layout/toolchain.json'))
    oracle=read_json(ROOT/'evidence/experiments/toolchain/msc700-baseline-Oelw.json');jobs=oracle['results']*2
    raw=fixture('SIMANTW.EXE');image=ne.parse(raw);symbols=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');targets={r['symbol']:r for r in oracle['probes']}
    started=time.perf_counter()
    def run_worker(index):
        results=[]
        with Win31Worker(index) as worker:
            for position in range(index,len(jobs),args.workers):
                probe=jobs[position];obj,receipt=worker.compile(probe['receipt']['source'],probe['flags'])
                equal=bool(obj) and obj.read_bytes()==(ROOT/probe['receipt']['object']).read_bytes()
                if not equal:raise FormatError('raw canonical OMF differs: '+probe['probe'])
                m=omf.parse(obj.read_bytes());target=targets['_'+probe['probe']]
                comparison=compare_member(m,raw,image,symbols,imports) if probe['probe'] in ('CreateMonoSolidBrush','RandTurn','win_SetWinDrawHook') else compare(m,raw,image,symbols,target)
                passed=comparison['result']==probe['result']
                results.append(dict(position=position,probe=probe['probe'],canonical_omf_equal=equal,canonical_match_equal=passed,result=comparison['result'],receipt=receipt))
                print(index,probe['probe'],equal,passed,round(receipt['timing']['total_compile_request_seconds'],3),flush=True)
        return results
    if args.workers==1:results=run_worker(0)
    else:
        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=args.workers) as pool:results=[row for group in pool.map(run_worker,range(args.workers)) for row in group]
    report=dict(workers=args.workers,passed=all(r['canonical_omf_equal'] and r['canonical_match_equal'] for r in results),inputs=inputs,elapsed_seconds=time.perf_counter()-started,environment_launches=sum(r['receipt']['timing']['environment_launches'] for r in results),jobs=len(results),results=sorted(results,key=lambda r:r['position']))
    write_json(ROOT/('evidence/experiments/runner/worker-%d.json'%args.workers),report)
    if not report['passed']:raise FormatError('canonical worker oracle failed')
    print('PASS',args.workers,'workers',len(results),'jobs',report['elapsed_seconds'],'seconds',flush=True)

if __name__=='__main__':main()
