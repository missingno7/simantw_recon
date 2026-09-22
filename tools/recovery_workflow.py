"""Bounded recovery queue, work packets, durable attempts and exact promotion.

The model supplies semantics and C. This tool owns selection, budgets, receipts,
independent admission, manifest updates and escalation. It never patches bytes.
"""
import argparse
import base64
import copy
import json
import os
import re
import shutil
import itertools
from collections import Counter
from contextlib import contextmanager
from datetime import datetime, timezone
from pathlib import Path
from common import ROOT, FormatError, read_json, write_json, fixture, identity, sha256
from compiler import compile_source, validate_receipt
from codegen_grinder import run, GOOD, variants
from recovery_gate import admission_targets, check_member
from recovery_context import compact_packet, markdown
from library_match import import_symbols
from verify_recovery import verify
import compiler_profiles
import ne, mapsym, omf

STATE=ROOT/'evidence/recovery/workflow'
LOCKS=ROOT/'build/locks'
PROTECTED=['tools/matcher.py','tools/library_match.py','tools/recovery_gate.py','tools/verify_recovery.py',
           'tools/compiler.py','tools/cfg_solver.py','tools/ne.py','tools/omf.py',
           'tools/compiler_worker.py','tools/compiler_service.py','tools/compiler_wait.asm','layout/compiler-service.json','tools/grind.py','tools/factory_queue.py',
           'tools/recovery_workflow.py','tools/topology_diagnostics.py','tools/codegen_grinder.py','tools/codegen_transforms.py','tools/codegen_cache.py',
           'tools/compiler_profiles.py','tools/tu_assembly.py',
           'layout/toolchain.json','layout/fixtures.json','layout/runtime-ownership.json']
CORE=['src/recovery.json','build/recovered/manifest.json','evidence/recovery/verified-objects.json','docs/progress.json']
MAX_ATTEMPTS=8
MAX_CANDIDATES=96
MAX_TOTAL_CANDIDATES=192


def timestamp():return datetime.now(timezone.utc).isoformat()
def relative(path):return path.resolve().relative_to(ROOT).as_posix()
def protected():return {p:identity(ROOT/p) for p in PROTECTED}
def cards():return [json.loads(line) for line in (ROOT/'evidence/disassembly/cards.jsonl').read_text().splitlines()]
def recipes():return read_json(ROOT/'src/recovery.json')['targets']

def checked_job(job_id):
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}',job_id):raise FormatError('invalid job ID')
    directory=STATE/'jobs'/job_id
    job=read_json(directory/'job.json')
    if job['protected']!=protected():raise FormatError('proof/toolchain changed since task creation; expert must refresh the task')
    if job['fixture_identity']!=read_json(ROOT/'layout/fixtures.json'):raise FormatError('changed fixture identity')
    return directory,job

def jobs(include_units=False):
    rows=[read_json(p) for p in sorted((STATE/'jobs').glob('*/job.json'))]
    return rows if include_units else [j for j in rows if j.get('lane')!='TU_ASSEMBLY']

def unit_jobs():
    return [j for j in jobs(include_units=True) if j.get('lane')=='TU_ASSEMBLY']

def classify(card,ledger,job=None):
    extent=card['extent'];reasons=list(ledger.get(card['symbol'],{}).get('blockers',[]))
    if job and job['status']=='ESCALATED':return 'EXPERT',job.get('blockers',reasons)
    if extent['end'] is None or extent['status'] in ('SHARED_TAIL','OVERLAPPING_ENTRY','AMBIGUOUS_TABLE'):
        return 'EXPERT',sorted(set(reasons+['EXTENT_UNKNOWN']))
    if reasons:return 'EXPERT',reasons
    if any(any(op in r['mnemonic'] for op in ('stos','movs','scas','lods')) for r in card['disassembly']):return 'GUIDED',['STRING_INTRINSIC_IDIOM']
    if any(r['mnemonic'].startswith('f') and r['mnemonic'] not in ('fwait',) for r in card['disassembly']):return 'GUIDED',['FP_MODE']
    if extent['size']>384 or len(card['calls'])>12:return 'LARGE',['SEMANTIC_DECOMPOSITION']
    return 'READY',[]

def queue(write=True):
    recovered=recipes();evidence=read_json(ROOT/'evidence/recovery/blockers.json');ledger={**evidence['drafts'],**evidence.get('workflow_cases',{})};history={j['symbol']:j for j in jobs()};items=[]
    for card in cards():
        if card['ownership']!='GAME' or card['symbol'] in recovered:continue
        job=history.get(card['symbol']);lane,reasons=classify(card,ledger,job)
        items.append(dict(symbol=card['symbol'],lane=lane,blockers=reasons,size=card['extent']['size'],segment=card['segment_name'],
                          call_count=len(card['calls']),incoming_count=len(card['incoming_references']),job=job['id'] if job else None,
                          status=job['status'] if job else 'UNASSIGNED'))
    order={'READY':0,'GUIDED':1,'LARGE':2,'EXPERT':3}
    items.sort(key=lambda r:(order[r['lane']],r['size'] or 65536,r['call_count'],r['symbol']))
    result=dict(generated=timestamp(),lane_counts=dict(Counter(r['lane'] for r in items)),policy=dict(max_attempts=MAX_ATTEMPTS,max_candidates_per_attempt=MAX_CANDIDATES,max_candidates_per_target=MAX_TOTAL_CANDIDATES),functions=items)
    if write:write_json(ROOT/'docs/recovery-queue.json',result)
    return result

def next_task(symbol=None,lane='READY'):
    work=queue();all_jobs=jobs()
    if symbol is None:
        active=next((j for j in all_jobs if j['status'] in ('OPEN','NEEDS_REVISION','EXACT_CANDIDATE') and j['symbol'] not in recipes()),None)
        if active:
            checked_job(active['id']);return dict(job=active['id'],packet=relative(STATE/'jobs'/active['id']/'packet.md'),status=active['status'])
        selected=next((r for r in work['functions'] if r['lane']==lane and r['status']=='UNASSIGNED'),None)
    else:selected=next((r for r in work['functions'] if r['symbol']==symbol),None)
    if selected is None:raise FormatError('no eligible unrecovered target in requested lane')
    if selected['lane']=='EXPERT':raise FormatError('target requires expert infrastructure work; inspect queue blockers')
    if selected['job']:return dict(job=selected['job'],status=selected['status'])
    card=next(c for c in cards() if c['symbol']==selected['symbol'])
    key=sha256((card['symbol']+card['exe_sha256']).encode())[:10]
    job_id=card['symbol'].lstrip('_')+'-'+key;directory=STATE/'jobs'/job_id;directory.mkdir(parents=True,exist_ok=True)
    packet=compact_packet(card,cards(),recipes(),read_json(ROOT/'evidence/recovery/blockers.json')['drafts'])
    profile=compiler_profiles.resolve(card['symbol']);flags=compiler_profiles.profile_flags(profile['name'],card['segment_name'])
    write_json(directory/'packet.json',packet);(directory/'packet.md').write_text(markdown(packet),encoding='utf-8')
    (directory/'candidate.c').write_text('/* TODO: write the semantic reconstruction described in packet.md. */\n')
    write_json(directory/'submission.json',dict(symbol=card['symbol'],source=relative(directory/'candidate.c'),compiler='msc700',flags=flags,
                max_candidates=MAX_CANDIDATES,axes=[],semantic_summary='',binding_evidence=[],publics=[card['symbol']]))
    job=dict(id=job_id,symbol=card['symbol'],status='OPEN',created=timestamp(),flags=flags,profile=profile,protected=protected(),fixture_identity=read_json(ROOT/'layout/fixtures.json'),attempts=[])
    atomic_json(directory/'job.json',job);queue()
    return dict(job=job_id,packet=relative(directory/'packet.md'),submission=relative(directory/'submission.json'),status='OPEN')

def check_submission(spec,job):
    if spec.get('symbol')!=job['symbol'] or spec.get('compiler')!='msc700' or spec.get('flags')!=job['flags']:raise FormatError('submission changed target or baseline compiler profile')
    if job.get('lane')=='TU_ASSEMBLY':
        if sorted(spec.get('publics',[]))!=sorted(job['publics']):raise FormatError('unit submission must cover exactly the unit publics')
    elif spec.get('publics')!=[job['symbol']]:raise FormatError('single-function submission must name exactly its public')
    if not spec.get('semantic_summary','').strip():raise FormatError('write a concrete semantic summary before compilation')
    if not 1<=spec.get('max_candidates',0)<=MAX_CANDIDATES:raise FormatError('workflow candidate budget is 1..96')
    if job['symbol'] not in spec.get('publics',[]):raise FormatError('requested public must be included')
    if 'source' in spec and not (ROOT/spec['source']).resolve().is_relative_to(ROOT):raise FormatError('source must be inside the repository')
    candidates=list(itertools.islice(variants(spec),spec['max_candidates']+1))
    if len(candidates)>spec['max_candidates']:raise FormatError('submission exceeds candidate budget')
    for source,_ in candidates:
        code=re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S)
        if 'TODO' in source or not code.strip():raise FormatError('unfinished source')
        # A scaffolded unit may only carry `#pragma alloc_text(...)` placements
        # (stand-ins into the reserved segment, later code runs into RUNk_TEXT).
        allowed_pragmas=re.compile(r'#\s*pragma\s+alloc_text\s*\(\s*(?:POOLSTUB_TEXT|RUN\d+_TEXT)\s*,[^()]*\)') if job.get('lane')=='TU_ASSEMBLY' and job.get('scaffold') else None
        stripped=allowed_pragmas.sub('',code) if allowed_pragmas else code
        if re.search(r'\b(?:__asm|_asm|asm|_emit|__emit|incbin)\b|#\s*(?:include|pragma)',stripped,re.I):raise FormatError('handoff lane requires self-contained ordinary C, without assembly or compiler pragmas')
        if re.search(r'\([^)]*\*[^)]*\)\s*(?:0x[0-9a-f]+|[1-9][0-9]*)',code,re.I):raise FormatError('literal-address pointer cast requires expert review')
    # Only catalogued compiler profiles are admissible; no free flag search.
    compiler_profiles.identify_profile(job['flags'])

def experiment_digest(spec):
    # Administrative prose and axis ordering cannot turn an identical set of
    # compiler inputs into a new experiment.
    sources=sorted({sha256(source.encode()) for source,_ in variants(spec)})
    return sha256(json.dumps(dict(compiler=spec['compiler'],flags=spec['flags'],symbol=spec['symbol'],sources=sources),sort_keys=True).encode())


def attempt_limit(job):
    return MAX_ATTEMPTS+len(job.get('budget_extensions',[]))

def run_attempt(job_id):
    directory,job=checked_job(job_id)
    if job['status'] not in ('OPEN','NEEDS_REVISION'):raise FormatError('job is not accepting attempts')
    if len(job['attempts'])>=attempt_limit(job):raise FormatError('attempt budget exhausted; escalate')
    spec=read_json(directory/'submission.json');check_submission(spec,job)
    used=sum(a.get('candidates',1) for a in job['attempts']);planned=sum(1 for _ in variants(spec))
    if used+planned>MAX_TOTAL_CANDIDATES:raise FormatError('total target budget exceeded; shrink the variant set or defer')
    semantic_digest=experiment_digest(spec)
    if any(a['submission_digest']==semantic_digest for a in job['attempts']):raise FormatError('identical experiment already recorded; change the hypothesis or escalate')
    out=directory/('attempt%02d'%(len(job['attempts'])+1))
    job.update(status='RUNNING',pending_attempt=dict(submission_digest=semantic_digest,output=relative(out),owner=dict(pid=os.getpid(),started=timestamp())))
    atomic_json(directory/'job.json',job)
    try:result=run(spec,relative(out),cache=True)
    except Exception as exc:
        job.update(status='ESCALATED',blockers=['COMPILER_EXECUTION_FAILURE'],reason='Compiler workflow failed: '+str(exc),next_experiment='Expert: inspect pending attempt logs and restore worker before retrying')
        atomic_json(directory/'job.json',job)
        with global_lock():refresh()
        raise
    # Compare-and-commit: the job file must still carry this attempt's token.
    current=read_json(directory/'job.json')
    if current.get('status')!='RUNNING' or current.get('pending_attempt',{}).get('submission_digest')!=semantic_digest:
        raise FormatError('job state changed while the attempt ran; result not recorded')
    job.pop('pending_attempt',None)
    best=result['results'][0]
    attempt=dict(number=len(job['attempts'])+1,submission_digest=semantic_digest,report=relative(out/'results.json'),completed=result['completed_candidates'],candidates=result['candidates'],cache=result['cache'],best_candidate=best['candidate'],result=best['comparison']['result'])
    job['attempts'].append(attempt)
    from topology_diagnostics import classify as topology_classify
    topology = next((diagnosis for row in result['results'] if (diagnosis := topology_classify(row['comparison']))), None)
    if result['exact_candidates']:job['status']='EXACT_CANDIDATE'
    elif topology:
        job.update(status='ESCALATED', blockers=['DATA_LAYOUT'], evidence_state=topology['state'],
                   topology_diagnostic=topology, reason='Body matches outside unresolved offset bindings; ordinary shape search stopped automatically',
                   next_experiment='Expert: group shared binding sites, reconstruct complete private contributions and retest the preserved source')
    elif len(job['attempts'])>=attempt_limit(job) or used+result['candidates']>=MAX_TOTAL_CANDIDATES:
        comparison=best['comparison']
        cause=('SOURCE_COMPILATION_ERROR' if not result['completed_candidates'] else 'SEMANTICS_UNKNOWN' if comparison.get('fixups_equal',0)<comparison.get('fixups_total',0) else 'LOCAL_FRAME_LAYOUT' if comparison.get('features',{}).get('frame')!=comparison.get('target_features',{}).get('frame') else 'REGISTER_ALLOCATION' if comparison.get('diagnostic',{}).get('categories')==['REGISTER_ALLOCATION'] else 'EXPRESSION_SHAPE')
        job.update(status='ESCALATED',blockers=[cause],reason='Bounded candidate budget exhausted; best result: '+comparison['result'],next_experiment='Expert: inspect best divergence and choose a new semantic/type/TU family')
    else:job['status']='NEEDS_REVISION'
    atomic_json(directory/'job.json',job)
    with global_lock():
        if job['status']=='ESCALATED':refresh()
        else:queue()
    return dict(job=job_id,status=job['status'],attempt=attempt,exact_candidates=result['exact_candidates'])

def atomic_bytes(path,data):
    path.parent.mkdir(parents=True,exist_ok=True);temporary=path.with_name(path.name+'.workflow-tmp');temporary.write_bytes(data);temporary.replace(path)

def atomic_json(path,value):
    atomic_bytes(path,(json.dumps(value,indent=2)+'\n').encode())


def recover_transaction():
    path=STATE/'transaction.json'
    if not path.exists():return
    transaction=read_json(path)
    if transaction['status']=='COMMITTED' and transaction.get('job'):
        jobpath=STATE/'jobs'/transaction['job']/'job.json';job=read_json(jobpath)
        if job['status']!='PROMOTED':
            if any(sha256((ROOT/p).read_bytes())!=digest for p,digest in transaction['new'].items()):raise FormatError('committed promotion changed before job reconciliation; expert review required')
            job.update(status='PROMOTED',promotion_evidence=relative(jobpath.parent/'promotion.json'))
            atomic_json(jobpath,job)
        return
    if transaction['status']!='PREPARED':return
    if set(transaction['old'])!=set(CORE):raise FormatError('invalid recovery journal')
    for name,data in transaction['old'].items():atomic_bytes(ROOT/name,base64.b64decode(data))
    transaction['status']='ROLLED_BACK_AFTER_INTERRUPTION';atomic_json(path,transaction)

def commit_core(values,job_id=None):
    if set(values)!=set(CORE):raise FormatError('incomplete promotion transaction')
    STATE.mkdir(parents=True,exist_ok=True)
    encoded={p:(json.dumps(v,indent=2)+'\n').encode() for p,v in values.items()}
    transaction=dict(status='PREPARED',created=timestamp(),job=job_id,new={p:sha256(data) for p,data in encoded.items()},old={p:base64.b64encode((ROOT/p).read_bytes()).decode() for p in CORE})
    atomic_json(STATE/'transaction.json',transaction)
    try:
        for path,data in encoded.items():atomic_bytes(ROOT/path,data)
        committed={k:v for k,v in transaction.items() if k!='old'};committed['status']='COMMITTED';atomic_json(STATE/'transaction.json',committed)
    except Exception:
        recover_transaction();raise


def prepare_promotion(job_id,candidate,audit_only,current_recipes,manifest):
    """Fresh compile and independent admission of one job; returns the manifest/recipe updates without committing."""
    directory,job=checked_job(job_id)
    if job['status']!='EXACT_CANDIDATE':raise FormatError('no exact candidate eligible for fresh admission')
    report=read_json(ROOT/job['attempts'][-1]['report']);candidate=report['exact_candidates'][0] if candidate is None else candidate
    row=next((r for r in report['results'] if r['candidate']==candidate),None)
    if row is None or row['comparison']['result'] not in GOOD:raise FormatError('selected candidate is not an exact member match')
    validate_receipt(row['receipt']);source=ROOT/row['receipt']['source']
    # Check admitted source text and frozen assumptions, not an edited submission.
    spec=copy.deepcopy(report['spec']);spec.pop('template',None);spec['axes']=[];spec['source']=relative(source);check_submission(spec,job)
    destination=ROOT/'src/recovered'/('wf_'+job_id+'.c') if not audit_only else directory/'audit-source.c'
    if destination.exists() and destination.read_bytes()!=source.read_bytes():raise FormatError('destination exists with different source; refusing overwrite')
    shutil.copyfile(source,destination)
    obj,receipt=compile_source(relative(destination),job['flags'],'msc700');validate_receipt(receipt)
    module=omf.parse(obj.read_bytes());raw=fixture('SIMANTW.EXE');image=ne.parse(raw);symbols=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
    # Pool scaffolding (stand-in functions in the reserved segment) is never part of the promotion scope.
    from library_match import SCAFFOLD_SEGMENT
    scaffold=[s['index'] for s in module['segments'] if s['name']==SCAFFOLD_SEGMENT and s['class']=='CODE']
    public_names={p['name'] for p in module['publics'] if p['segment'] and module['segments'][p['segment']-1]['class']=='CODE' and p['segment'] not in scaffold}
    if public_names!=set(spec['publics']):raise FormatError('compiled code publics differ from declared promotion scope')
    if scaffold and job.get('lane')!='TU_ASSEMBLY':raise FormatError('pool scaffolding is only admissible inside a unit assembly job')
    inventory={x['name']:x for x in read_json(ROOT/'evidence/symbols/inventory.json')['symbols']}
    if any(inventory.get(name,{}).get('ownership')!='GAME' for name in public_names):raise FormatError('runtime/unknown ownership cannot receive game-source promotion')
    # Already-admitted publics may only be re-admitted inside a unit job that
    # declares them; their previous recipes are superseded and archived.
    superseded={name:current_recipes['targets'][name] for name in public_names if name in current_recipes['targets']}
    if superseded and (job.get('lane')!='TU_ASSEMBLY' or set(superseded)-set(job.get('supersedes',[]))):raise FormatError('promotion would silently replace admitted recipes: '+', '.join(sorted(superseded)))
    profile_name,segment=compiler_profiles.identify_profile(job['flags']);profile=job.get('profile') or compiler_profiles.resolve(job['symbol'])
    if profile['name']!=profile_name:raise FormatError('job flags disagree with its recorded compiler profile')
    targets=admission_targets(module,raw,image,symbols,sorted(public_names),scaffold=bool(job.get('scaffold')));comparison=check_member(module,raw,image,symbols,imports,targets,scaffold=bool(job.get('scaffold')))
    proof=dict(job=job_id,candidate=candidate,admitted=True,audit_only=audit_only,semantic_summary=spec['semantic_summary'],binding_evidence=spec.get('binding_evidence',[]),receipt=receipt,comparison=comparison,targets=targets,
               compiler_profile=dict(profile,flags=job['flags']),unit=job.get('unit'),scaffold=job.get('scaffold'),superseded_recipes=superseded,scope='Exact readable reconstruction, not original text or filename')
    proof_path=directory/('audit.json' if audit_only else 'promotion.json');write_json(proof_path,proof)
    if audit_only:return dict(job=job_id,admission='PASSED',promotion='NONE',evidence=relative(proof_path))
    stored=ROOT/'build/recovered'/('wf_'+job_id+'.obj');shutil.copyfile(obj,stored)
    game={r['symbol']:r for r in manifest['game_objects']}
    for name,target in targets.items():
        target.update(source=relative(destination),compiler='msc700',flags=job['flags'],profile=profile['name'],profile_evidence=profile.get('assignment'),promotion_evidence=relative(proof_path))
        if job.get('unit'):target['unit']=job['unit']
        if job.get('scaffold'):target['scaffold']=job['scaffold']
        current_recipes['targets'][name]=target
        game[name]=dict(symbol=name,object=relative(stored),identity=identity(stored),receipt=receipt)
    manifest['game_objects']=list(game.values())
    return dict(job=job_id,directory=directory,record=job,proof_path=proof_path,targets=targets,superseded=sorted(superseded))

def promote(job_id,candidate=None,audit_only=False):
    return promote_many([job_id],candidate,audit_only)

def promote_many(job_ids,candidate=None,audit_only=False):
    """One exclusive transaction admits every listed exact candidate and commits the core manifest once.

    The pre-verification excludes only recipes explicitly superseded by the
    listed unit jobs (a strengthened proof rule may reject exactly those);
    the final verification covers the complete replaced manifest.
    """
    if len(job_ids)!=len(set(job_ids)):raise FormatError('duplicate job in promotion batch')
    superseding=set()
    for job_id in job_ids:
        _,job=checked_job(job_id)
        if job['status']!='EXACT_CANDIDATE':raise FormatError('no exact candidate eligible for fresh admission')
        report=read_json(ROOT/job['attempts'][-1]['report']);chosen=report['exact_candidates'][0] if candidate is None else candidate
        row=next((r for r in report['results'] if r['candidate']==chosen),None)
        if row is None or row['comparison']['result'] not in GOOD:raise FormatError('selected candidate is not an exact member match')
        if job.get('lane')=='TU_ASSEMBLY':superseding.update(job.get('supersedes',[]))
    current_recipes=read_json(ROOT/'src/recovery.json');manifest=read_json(ROOT/'build/recovered/manifest.json')
    verify(dict(manifest,game_objects=[g for g in manifest['game_objects'] if g['symbol'] not in superseding]),{k:v for k,v in current_recipes['targets'].items() if k not in superseding},publish=False)
    prepared=[prepare_promotion(job_id,candidate,audit_only,current_recipes,manifest) for job_id in job_ids]
    if audit_only:return prepared[0] if len(prepared)==1 else prepared
    verified=verify(manifest,current_recipes['targets'],publish=False)
    progress={k:v for k,v in verified.items() if k not in ('game','runtime')}
    commit_core(dict(zip(CORE,[current_recipes,manifest,verified,progress])),job_ids[0] if len(job_ids)==1 else None)
    for item in prepared:
        item['record'].update(status='PROMOTED',promotion_evidence=relative(item['proof_path']));atomic_json(item['directory']/'job.json',item['record'])
    refresh()
    symbols=sorted(name for item in prepared for name in item['targets'])
    return dict(job=job_ids[0] if len(job_ids)==1 else job_ids,status='PROMOTED',symbols=symbols,superseded=sorted({s for item in prepared for s in item['superseded']}),progress=progress)

def defer(job_id,cause,reason,next_experiment):
    from blocker_ledger import TAXONOMY
    if cause not in TAXONOMY:raise FormatError('unknown blocker taxonomy')
    if cause=='SOURCE_NOT_RECOVERED' or not reason.strip() or not next_experiment.strip():raise FormatError('defer needs a concrete cause, evidence and next experiment')
    directory,job=checked_job(job_id)
    if job['status']=='PROMOTED':raise FormatError('cannot defer a promoted task')
    job.update(status='ESCALATED',blockers=[cause],reason=reason,next_experiment=next_experiment)
    atomic_json(directory/'job.json',job)
    with global_lock():refresh()
    return dict(job=job_id,status='ESCALATED')

def refresh():
    from cfg_solver import main as cfg
    from blocker_ledger import main as ledger
    from cards import main as update_cards
    cfg();ledger();update_cards();queue()
    from factory_queue import generate as factory_generate
    from blocker_families import generate as family_generate
    from structural_families import generate as structural_generate
    factory_generate();structural_generate();family_generate()


def recover_interrupted_attempts():
    # A RUNNING job whose per-job lock is free has no live owner: its attempt
    # was interrupted. A held lock means another process is still compiling.
    changed=False
    for job in jobs(include_units=True):
        if job['status']!='RUNNING':continue
        try:
            with job_lock(job['id']):
                current=read_json(STATE/'jobs'/job['id']/'job.json')
                if current['status']!='RUNNING':continue
                current.update(status='ESCALATED',blockers=['COMPILER_EXECUTION_FAILURE'],reason='Attempt interrupted before its result was recorded',next_experiment='Expert: inspect pending output and compiler receipts; do not silently repeat the experiment')
                atomic_json(STATE/'jobs'/job['id']/'job.json',current);changed=True
        except FormatError:continue
    if changed:refresh()

def doctor():
    report=verify(publish=False);work=queue();problems=[]
    from factory_queue import generate
    factory=generate()
    validation_path=STATE/'validation.json'
    validation=read_json(validation_path) if validation_path.exists() else {}
    if not validation.get('passed'):problems.append('Run tools/handoff_validate.py to establish infrastructure readiness')
    elif any(not (ROOT/p).exists() or identity(ROOT/p)!=expected for p,expected in validation['inputs'].items()):problems.append('Infrastructure changed since handoff validation; rerun tools/handoff_validate.py')
    if sum(r['status']=='EXACT_CANDIDATE' for r in work['functions']) or any(j['status']=='EXACT_CANDIDATE' for j in unit_jobs()):problems.append('Exact candidates awaiting independent promotion')
    try:compiler_profiles.validate()
    except FormatError as exc:problems.append(str(exc))
    current=protected()
    for job in jobs(include_units=True):
        if job['status'] in ('OPEN','NEEDS_REVISION','EXACT_CANDIDATE','RUNNING') and job.get('protected')!=current:
            problems.append('Active job has stale proof/tool context: '+job['id']+'; expert review required')
    completed=[j for j in jobs() if j['status']=='PROMOTED'];escalated=[j for j in jobs() if j['status']=='ESCALATED']
    result=dict(status='READY_FOR_BOUNDED_HANDOFF' if completed and not problems else 'PILOT_REQUIRED' if not completed else 'ATTENTION',
                checked=timestamp(),verified_functions=report['game_functions'],verified_runtime_members=report['runtime_members'],lane_counts=work['lane_counts'],
                production_states=factory['states'],pilot_promotions=[j['symbol'] for j in completed],durable_escalations=len(escalated),problems=problems,
                infrastructure_validation=dict(evidence=relative(validation_path),passed=validation.get('passed',False),tests=validation.get('tests'),cache=validation.get('cache')),
                limits=dict(attempts_per_target=MAX_ATTEMPTS,candidates_per_attempt=MAX_CANDIDATES,candidates_per_target=MAX_TOTAL_CANDIDATES),
                scope='Ready lane is eligible for bounded attempts, not a prediction that a particular model will solve all tasks. Expert lane remains separate.')
    write_json(ROOT/'docs/handoff-readiness.json',result);return result

@contextmanager
def file_lock(path,timeout,message):
    """Exclusive OS file lock; waits up to timeout seconds (0 = non-blocking)."""
    import time
    path.parent.mkdir(parents=True,exist_ok=True)
    with path.open('a+b') as handle:
        handle.seek(0);handle.write(b'0');handle.flush()
        deadline=time.monotonic()+timeout
        while True:
            handle.seek(0)
            try:
                if os.name=='nt':
                    import msvcrt
                    msvcrt.locking(handle.fileno(),msvcrt.LK_NBLCK,1)
                else:
                    import fcntl
                    fcntl.flock(handle.fileno(),fcntl.LOCK_EX|fcntl.LOCK_NB)
                break
            except OSError as exc:
                if time.monotonic()>=deadline:raise FormatError(message) from exc
                time.sleep(0.05)
        try:yield
        finally:
            handle.seek(0)
            if os.name=='nt':msvcrt.locking(handle.fileno(),msvcrt.LK_UNLCK,1)
            else:fcntl.flock(handle.fileno(),fcntl.LOCK_UN)

def global_lock(timeout=120):
    """Short exclusive section for shared state: queue allocation, shared evidence rebuilds, core manifest transactions."""
    return file_lock(ROOT/'build/recovery-workflow.lock',timeout,'another recovery workflow command holds the shared-state lock')

def job_lock(job_id,timeout=0):
    """Exclusive per-job section for attempts, deferral and promotion; compilation runs under it, not under the global lock."""
    if not re.fullmatch(r'[A-Za-z0-9_]+-[a-f0-9]{10}',job_id):raise FormatError('invalid job ID')
    return file_lock(LOCKS/'jobs'/(job_id+'.lock'),timeout,'job '+job_id+' is being worked on by another process')

def workflow_lock():
    """Whole-workflow exclusive section (validation and maintenance only)."""
    return global_lock()

def job_for_symbol(symbol):
    return next((j for j in jobs() if j['symbol']==symbol),None)

def main():
    ap=argparse.ArgumentParser(description=__doc__);sub=ap.add_subparsers(dest='action',required=True)
    sub.add_parser('queue');sub.add_parser('doctor');sub.add_parser('refresh')
    p=sub.add_parser('next');p.add_argument('--symbol');p.add_argument('--lane',choices=['READY','GUIDED','LARGE'],default='READY')
    p=sub.add_parser('attempt');p.add_argument('job')
    p=sub.add_parser('promote');p.add_argument('job',nargs='+');p.add_argument('--candidate',type=int);p.add_argument('--audit-only',action='store_true')
    p=sub.add_parser('defer');p.add_argument('job');p.add_argument('--cause',required=True);p.add_argument('--reason',required=True);p.add_argument('--next-experiment',required=True)
    args=ap.parse_args()
    with global_lock():
        recover_transaction()
        recover_interrupted_attempts()
    if args.action=='attempt':
        with job_lock(args.job):result=run_attempt(args.job)
    elif args.action=='promote':
        from contextlib import ExitStack
        with ExitStack() as stack:
            for job_id in args.job:stack.enter_context(job_lock(job_id))
            stack.enter_context(global_lock())
            result=promote_many(args.job,args.candidate,args.audit_only)
    elif args.action=='defer':
        with job_lock(args.job):result=defer(args.job,args.cause,args.reason,args.next_experiment)
    else:
        with global_lock():
            if args.action=='queue':result=queue();result={k:v for k,v in result.items() if k!='functions'}
            elif args.action=='next':result=next_task(args.symbol,args.lane)
            elif args.action=='refresh':refresh();result=dict(status='REFRESHED')
            else:result=doctor()
    print(json.dumps(result,indent=2))

if __name__=='__main__':
    try:main()
    except (FormatError,FileNotFoundError) as exc:raise SystemExit('ERROR: '+str(exc))
