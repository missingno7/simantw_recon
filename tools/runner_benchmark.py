"""Measure reference C7 latency, parsing and matching with canonical probes."""
import statistics,time
from common import ROOT,fixture,read_json,write_json
from compiler import _compile_source as compile_source
from codegen_grinder import score_object
from library_match import import_symbols
import omf,ne,mapsym


def main():
    oracle=read_json(ROOT/'evidence/experiments/toolchain/msc700-baseline-Oelw.json');selected=[r for r in oracle['results'] if r['probe'] in ('ABS','WindowsMemCpy','MyPow','CreateMonoSolidBrush')]
    raw=fixture('SIMANTW.EXE');image=ne.parse(raw);symbols=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');results=[]
    for probe in selected:
        start=time.perf_counter();obj,receipt=compile_source(probe['receipt']['source'],probe['flags'],'msc700');parse_start=time.perf_counter();module=omf.parse(obj.read_bytes());parse_time=time.perf_counter()-parse_start
        compare_start=time.perf_counter();comparison=score_object(module,raw,image,symbols,imports,'_'+probe['probe']);compare_time=time.perf_counter()-compare_start
        row=dict(probe=probe['probe'],source_bytes=(ROOT/probe['receipt']['source']).stat().st_size,object_bytes=obj.stat().st_size,timing=dict(receipt['timing'],omf_parse_seconds=parse_time,match_diff_seconds=compare_time,total_candidate_seconds=time.perf_counter()-start),result=comparison['result'],receipt=receipt)
        results.append(row);print(probe['probe'],row['timing'],flush=True)
    # Empty translation unit calibrates the compiler's minimum complete-pass
    # cost. Internal pass initialization cannot be separated by external timing.
    empty=ROOT/'build/runner-baseline/empty.c';empty.parent.mkdir(parents=True,exist_ok=True);empty.write_text('/* Empty translation unit startup calibration. */\n')
    obj,driver=compile_source(empty.relative_to(ROOT).as_posix(),selected[0]['flags'],'msc700')
    for row in results:
        row['timing']['compiler_startup_estimate_seconds']=driver['timing']['compiler_execution_seconds']
        row['timing']['incremental_compilation_estimate_seconds']=max(0,row['timing']['compiler_execution_seconds']-driver['timing']['compiler_execution_seconds'])
    write_json(ROOT/'evidence/experiments/runner/reference-timing.json',dict(results=results,driver_probe=driver,limitations=['Compiler execution includes pass startup; no unsupported /Bt timing option is used.','Empty-TU startup and incremental compile figures are estimates, not pass-level profiling.']))

if __name__=='__main__':main()
