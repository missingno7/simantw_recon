"""Publish infrastructure evidence separately from recovered-source totals."""
from collections import Counter
import json
from common import ROOT, read_json, write_json, identity, FormatError


def main():
    phase=read_json(ROOT/'evidence/codegen/phase-baseline.json');frontier=read_json(ROOT/'docs/frontier.json')['functions'];ledger=read_json(ROOT/'evidence/recovery/blockers.json')
    corpus=read_json(ROOT/'evidence/codegen/corpus.json');baseline=read_json(ROOT/'evidence/codegen/corpus-results.json')
    queue=read_json(ROOT/'evidence/codegen/runs/db_GetObjectSize.json');fingerprints=read_json(ROOT/'evidence/codegen/fingerprints.json')
    linked=read_json(ROOT/'evidence/experiments/partial-link/results.json');packed=read_json(ROOT/'evidence/experiments/partial-link/packed-results.json')
    resources=read_json(ROOT/'evidence/experiments/partial-link/resource-probe.json')
    if identity(ROOT/'build/PARTLINK/PARTIAL.EXE')!=linked['output']:raise FormatError('partial executable changed')
    if identity(ROOT/resources['directory']/'RESLINK.EXE')!=resources['output']:raise FormatError('resource executable changed')
    calls=[]
    for r in fingerprints['results']:
        if r['family']=='calling_convention':calls += [tuple(x['cleanup']) for x in r.get('features',[])]
    summary=dict(phase='CODEGEN_INFRASTRUCTURE',recovery=read_json(ROOT/'docs/progress.json'),
      generic_toolchain_blockers=sum('original_toolchain_unresolved' in r['blockers'] for r in frontier),
      baseline_profile=dict(compiler='MSC C/C++ 7.00',flags=['/AL','/G2','/Gs','/Oelw']),
      extent_baseline=dict(unknown=phase['unknown_extents'],commit=phase['commit'],source='evidence/codegen/phase-baseline.json'),
      extent_current=dict(unknown=sum(r['size'] is None for r in frontier),statuses=dict(Counter(r['extent_status'] for r in frontier)),scope='NOP-only gaps resolved as PROBABLE; no automatic proof promotion'),
      regression_corpus=dict(cases=corpus['draft_count'],baseline_compiled=baseline['compiled'],remaining_unpromoted=ledger['unpromoted_count']),
      automatically_unblocked=['_DoWinHelp','_ProcMenuHelp','_SetMenuOptionState'],
      translation_unit=dict(status='STRONGLY_SUPPORTED_TU',publics=['_SetMenuItemState','_SetMenuOptionState'],code_bytes=104,private_const_bytes=2,fixups=7,historical_filename=None),
      compile_queue=dict(candidates=queue['candidates'],completed=queue['completed_candidates'],environment_launches=queue['environment_launches'],session_limit=96,
                         limitation='Unbounded sessions stopped around 160 jobs in local trials; queue rotates workers at 96. Root cause not established.'),
      fingerprints=dict(cases=len(fingerprints['results']),compiled=sum(r['receipt']['exit_code']==0 for r in fingerprints['results']),
                        cleanup_counts={','.join(k) or 'none':v for k,v in Counter(calls).items()},library_string_windows=len(fingerprints['libraries']['findings']),
                        unsupported_intrinsics=['memchr','_fmemchr']),
      partial_link=dict(linker='5.30',success=linked['exit_code']==0,objects=linked['recovered_objects'],runtime_members=linked['runtime_objects'],
                        generated_stubs=len(linked['stubs']),default_packed_segments=packed['ne_header']['segment_count'],no_pack_code_segments=linked['ne_header']['segment_count'],
                        synthetic_resources=len(resources['resources']),recovery_credit=0,whole_executable_build=False),
      remaining=['db_GetObjectSize register schedule: 61/68 ordinary bytes and 7/7 fixups after 384 variants',
                 'UnpackFileClose POP AX not reproduced; ADD SP,2 and POP BX fingerprints captured',
                 'UnpackSetBuf pointer ABI remains unresolved; no direct callers in mapped disassembly',
                 'Private-data initializer drafts and indirect-jump tables still need targeted TU/CFG evidence'])
    write_json(ROOT/'docs/codegen-progress.json',summary)
    print(json.dumps(summary,indent=2))

if __name__=='__main__':main()
