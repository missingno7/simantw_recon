"""Evidence-backed blocker ledger and immutable readable-draft regression corpus."""
import json
from common import ROOT, read_json, write_json, identity
from codegen_grinder import rank
from topology_diagnostics import classify as topology_classify

TAXONOMY=['SOURCE_NOT_RECOVERED','SEMANTICS_UNKNOWN','EXTENT_UNKNOWN','REGISTER_ALLOCATION',
          'LOCAL_FRAME_LAYOUT','EXPRESSION_SHAPE','TRANSLATION_UNIT_CONTEXT','PRIVATE_CONST_LAYOUT',
          'SHARED_TAIL','CALLING_CONVENTION','FAR_POINTER_TYPE','STRING_INTRINSIC_IDIOM',
          'IMPORT_ORDINAL','FP_MODE','DATA_LAYOUT','TOOLCHAIN_VARIANT_REQUIRED','OPTIMIZER_VARIANT_REQUIRED',
          'FP_MODE_UNRESOLVED','CALLING_CONVENTION_UNRESOLVED','TRANSLATION_UNIT_CONTEXT_REQUIRED','COMPILER_EXECUTION_FAILURE','SOURCE_COMPILATION_ERROR']
CAUSES={
 'REGISTER_ALLOCATION':['db_GetObjectSize','SRand1','PlacePillTile','NotMowed','ms_Delay','WaitHundredths'],
 'LOCAL_FRAME_LAYOUT':['SRand1','PlacePillTile','ms_Delay','WaitHundredths'],
 'TRANSLATION_UNIT_CONTEXT':['SetMenuOptionState','InitSpider','ResetYellowVars','MakeRedInitiator'],
 'PRIVATE_CONST_LAYOUT':['InitSpider','ResetYellowVars','MakeRedInitiator'],
 'FAR_POINTER_TYPE':['UnpackSetBuf'], 'CALLING_CONVENTION':['UnpackFileClose'],
 'STRING_INTRINSIC_IDIOM':['ClearBuffer','MemRChr','invert'], 'EXPRESSION_SHAPE':['DoWinHelp','ProcMenuHelp']}


def workflow_cases(root=ROOT):
    """Durable escalations are separate from the frozen readable-draft corpus."""
    cases={}
    for path in sorted((root/'evidence/recovery/workflow/jobs').glob('*/job.json')):
        job=read_json(path)
        if job['status']!='ESCALATED':continue
        reports=[read_json(root/a['report']) for a in job.get('attempts',[]) if a.get('report')]
        rows=[(row,report) for report in reports for row in report['results']]
        best,report=max(rows,key=lambda pair:(topology_classify(pair[0].get('comparison',{})) is not None,rank(pair[0]))) if rows else ({},{})
        spec=report.get('spec',read_json(path.parent/'submission.json'))
        score=best.get('comparison',{})
        cases[job['symbol']]=dict(topology_diagnostic=topology_classify(score), status='WORKFLOW_ESCALATED',job=job['id'],blockers=job['blockers'],
            source=best.get('receipt',{}).get('source',spec.get('source')),
            semantic_hypothesis=spec.get('semantic_summary','Unreviewed task; no semantic hypothesis submitted'),
            binding_evidence=spec.get('binding_evidence',[]),best_score=score or None,
            failed_variants=job.get('attempts',[]),pending_attempt=job.get('pending_attempt'),
            reason=job['reason'],next_experiment=job['next_experiment'])
    return cases


def main():
    recovered=read_json(ROOT/'src/recovery.json')['targets']
    inventory={x['name']:x for x in read_json(ROOT/'evidence/symbols/inventory.json')['symbols']}
    cards={r['symbol']:r for r in map(json.loads,(ROOT/'evidence/disassembly/cards.jsonl').read_text().splitlines())}
    history={}
    for p in sorted((ROOT/'evidence/recovery').glob('batch*/results.json'),key=lambda p:int(p.parent.name[5:])):
        data=read_json(p)
        if not isinstance(data,dict):continue
        for failure in data.get('failed_hypotheses',[]):
            if isinstance(failure,str):names=[name for name in inventory if name.lstrip('_') in failure];reason=failure
            else:names=failure.get('symbols',[failure.get('symbol')]);reason=failure.get('reason',failure.get('blocker',''))
            for name in names:
                if name:history.setdefault(name,[]).append(dict(evidence=p.relative_to(ROOT).as_posix(),reason=reason))
    corpuspath=ROOT/'evidence/codegen/corpus.json'
    cases={r['symbol']:r for r in read_json(corpuspath)['drafts']} if corpuspath.exists() else {}
    for source in sorted((ROOT/'src/recovered').glob('*.c')):
        name='_'+source.stem
        if name in inventory and name not in recovered and name not in cases:cases[name]=dict(working_source=source.relative_to(ROOT).as_posix())
    observations={}
    baseline=ROOT/'evidence/codegen/corpus-results.json'
    if baseline.exists():
        for row in read_json(baseline)['results']:observations[row['symbol']]=(row,baseline.relative_to(ROOT).as_posix())
    for name,filename in [('_db_GetObjectSize','db_GetObjectSize.json'),('_DoWinHelp','DoWinHelp-typed.json'),('_ProcMenuHelp','ProcMenuHelp.json'),('_SetMenuOptionState','menu-tu.json')]:
        path=ROOT/'evidence/codegen/runs'/filename
        if path.exists():observations[name]=(read_json(path)['results'][0],path.relative_to(ROOT).as_posix())
    fingerprints=ROOT/'evidence/codegen/fingerprints.json'
    if fingerprints.exists():
        probes=read_json(fingerprints)['results']
        for name in ['_UnpackFileClose','_UnpackSetBuf']:
            candidates=[r for r in probes if r['symbol']==name and 'comparison' in r]
            if candidates:observations[name]=(max(candidates,key=rank),'evidence/codegen/fingerprints.json')
    drafts={}
    for name,case in cases.items():
        source=recovered.get(name,{}).get('source',case['working_source']);failures=history.get(name,[]);causes=[k for k,v in CAUSES.items() if name[1:] in v]
        text=' '.join(x['reason'] for x in failures).lower()
        for word,cause in [('frame','LOCAL_FRAME_LAYOUT'),('register','REGISTER_ALLOCATION'),('private','PRIVATE_CONST_LAYOUT'),('selector','DATA_LAYOUT'),('calling','CALLING_CONVENTION'),('opcode','EXPRESSION_SHAPE')]:
            if word in text and cause not in causes:causes.append(cause)
        row,evidence=observations.get(name,({},None));score=row.get('comparison',{})
        fixups=[f for c in score.get('contributions',[]) for f in c['fixups'] if f['equal']]
        best=dict(ordinary_bytes_equal=score.get('literal_equal'),ordinary_bytes_total=score.get('literal_compared'),fixups_equal=score.get('fixups_equal'),fixups_total=score.get('fixups_total'),candidate_contribution_size=score.get('code_contribution_size'),target_function_size=cards[name]['extent']['size'],first_divergence=score.get('first_divergence'),result=score.get('result'),evidence=evidence) if score else None
        promoted=name in recovered
        drafts[name]=dict(source=source,source_identity=identity(ROOT/source),frozen_regression_source=case.get('source'),
            status='PROMOTED_EXACT_RECONSTRUCTION' if promoted else 'READABLE_UNPROMOTED',blockers=[] if promoted else causes or ['EXPRESSION_SHAPE'],
            semantic_hypothesis={
                '_db_GetObjectSize':'Return the first recalled object size, freeing its recalled handle; return zero when no database handle finds it.',
                '_UnpackFileClose':'Close the current unpackHandle through the C runtime close routine.',
                '_UnpackSetBuf':'Store the four-byte input buffer and word size in the unpacker state preceding unpackHandle.',
                '_DoWinHelp':'Call WinHelp(rootWnd, helpFile, HELP_CONTEXT, context & 0xff00), zero-extending the word to DWORD.',
                '_ProcMenuHelp':'Call WinHelp(rootWnd, helpFile, HELP_CONTEXT, context), zero-extending the word to DWORD.',
                '_SetMenuOptionState':'Check the selected menu item when state is nonzero; menu handle comes from the shared Scycle-relative table.'
            }.get(name,failures[-1]['reason'] if failures else 'Readable source is the current hypothesis; semantic review still required'),
            known_correct_calls=[f['target'] for f in fixups if f['omf']['location_type']==3],
            known_correct_globals=[f['target'] for f in fixups if f['omf']['location_type']!=3],
            known_correct_fixups=dict(equal=score.get('fixups_equal'),total=score.get('fixups_total')) if score else None,
            best_score=best,failed_variants=failures,next_experiment='Regression: independent full-member verification' if promoted else {
                '_db_GetObjectSize':'Change induction/pointer representation; 384 declaration/test variants exhausted',
                '_UnpackFileClose':'Baseline emits ADD SP,2; size optimization emits POP BX; Pascal emits no cleanup. Investigate AX/BX liveness/context; no POP AX match yet',
                '_UnpackSetBuf':'Compare pointer and aggregate ABI fingerprints, then validate all caller argument layouts',
                '_InitSpider':'Use selector references and adjacent initializers to constrain private CONST contribution'
            }.get(name,'Use specific blocker family against frozen baseline; compare complete OMF contributions'))
    write_json(ROOT/'evidence/recovery/blockers.json',dict(schema_version=2,baseline=dict(compiler='msc700',flags=['/AL','/G2','/Gs','/Oelw']),
        taxonomy=TAXONOMY,draft_count=len(drafts),unpromoted_count=sum(r['status']=='READABLE_UNPROMOTED' for r in drafts.values()),drafts=drafts,workflow_cases=workflow_cases()))
    print('Indexed',len(drafts),'regression drafts')

if __name__=='__main__':main()
