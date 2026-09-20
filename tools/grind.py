"""Narrow cheap-model interface: inspect, test, accept, block and queue."""
import argparse,copy,json,re,shutil,time,sys
import mapsym,ne
from topology_context import direct_data_bindings
from contextlib import redirect_stdout
from pathlib import Path
from common import ROOT,FormatError,read_json,write_json,identity,fixture
import recovery_workflow as wf
from factory_queue import generate
from codegen_diff import blocks,instructions


def lookup(symbol):
    report=generate();row=next((r for r in report['functions'] if r['symbol']==symbol),None)
    if row is None:raise FormatError('unknown game-code symbol')
    return row


def inspect(symbol):
    state=lookup(symbol);all_cards=wf.cards();card=next(c for c in all_cards if c['symbol']==symbol)
    from recovery_context import compact_packet
    packet=compact_packet(card,all_cards,wf.recipes(),read_json(ROOT/'evidence/recovery/blockers.json')['drafts'])
    code=bytes.fromhex(''.join(r['bytes'] for r in card['disassembly']));packet.update(state=state['state'],structural_extent=state['extent'],target_bytes_hex=code.hex(),target_bytes_note='Raw target includes loader-chain words; use masked disassembly and semantic bindings for source inference',basic_blocks=blocks(instructions(code)),calls=card['calls'],globals=card['globals'],relocations=card['known_fixups'],compiler_profile=dict(compiler='msc700',flags=['/AL','/G2','/Gs','/Oelw','/NT'+card['segment_name']]))
    matching=[c for c in all_cards if c['source'] and c['ownership']=='GAME' and c['segment']==card['segment']]
    matching.sort(key=lambda c:abs((c['extent']['size'] or 65536)-(card['extent']['size'] or 65536)))
    packet['similar_matched_functions']=[dict(symbol=c['symbol'],source=c['source'],size=c['extent']['size'],basis='Same code group and nearest size; similarity is not semantic proof') for c in matching[:5]]
    packet['direct_data_bindings']=direct_data_bindings(card,mapsym.parse(fixture('SIMANTW.SYM')),ne.parse(fixture('SIMANTW.EXE')))
    packet['evidence_state']=state.get('evidence_state')
    packet['blocker_family_evidence']='evidence/recovery/blocker-families.json'
    family_path=ROOT/packet['blocker_family_evidence']
    family_report=read_json(family_path) if family_path.exists() else {}
    packet['blocker_family']=family_report.get('functions',{}).get(symbol)
    packet['family_evidence']='layout/translation-units.json'
    packet['known_families']=[{k:u[k] for k in ['id','status','publics','evidence']} for u in read_json(ROOT/'layout/translation-units.json')['units'] if symbol in u['publics']]
    from library_match import import_symbols
    known=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')
    packet['known_imported_symbols']=[dict(target=r['target'],symbols=[name for name,t in known.items() if t==r['target']]) for r in card['known_fixups'] if r['target']['kind']=='import']
    if state['state']=='MATCH_READY':
        task=wf.next_task(symbol);directory=wf.STATE/'jobs'/task['job'];write_json(directory/'factory-packet.json',packet)
        return dict(symbol=symbol,state=state['state'],job=task['job'],packet=wf.relative(directory/'factory-packet.json'),summary_packet=wf.relative(directory/'packet.md'),extent=state['extent'],working_packet=packet)
    out=ROOT/'build/factory-inspect';out.mkdir(parents=True,exist_ok=True);path=out/(symbol+'.json');write_json(path,packet)
    return dict(symbol=symbol,state=state['state'],blockers=state['blockers'],packet=wf.relative(path),source=wf.recipes().get(symbol,{}).get('source'),working_packet=packet)


def test(symbol,candidate,summary=None):
    began=time.perf_counter();task=inspect(symbol)
    path=(ROOT/candidate).resolve()
    if not path.is_relative_to(ROOT):raise FormatError('candidate must be inside repository')
    if task['state']=='MATCHED':
        target=wf.recipes()[symbol]
        if path.read_bytes()!=(ROOT/target['source']).read_bytes():raise FormatError('matched-symbol test only replays its unchanged verified source')
        from codegen_grinder import run
        report=run(dict(symbol=symbol,source=wf.relative(path),compiler=target['compiler'],flags=target['flags'],max_candidates=1,axes=[]),'build/factory-regression/'+symbol,cache=True)
        best=report['results'][0]
        return dict(symbol=symbol,status='REGRESSION_ONLY',cache=report['cache'],diagnostic=best['comparison'].get('diagnostic'),timing=dict(best['receipt'].get('timing',{}),**best.get('timing',{}),total_test_api_seconds=time.perf_counter()-began),recovery_credit=0)
    if task['state']!='MATCH_READY':raise FormatError('target is '+task['state']+'; use its research evidence instead of retrying')
    directory,job=wf.checked_job(task['job'])
    source=path.read_text();comment=re.search(r'/\*(.*?)\*/',source,re.S)
    semantics=summary or (comment.group(1).strip() if comment else None)
    if not semantics:raise FormatError('add a semantic summary comment to C or supply --summary')
    destination=directory/'candidate.c'
    if path!=destination.resolve():shutil.copyfile(path,destination)
    spec=dict(symbol=symbol,source=wf.relative(destination),compiler='msc700',flags=job['flags'],max_candidates=96,axes=[],semantic_summary=semantics,binding_evidence=['Candidate declarations and source comments; inspect packet bindings before acceptance'],publics=[symbol])
    write_json(directory/'submission.json',spec);outcome=wf.run_attempt(task['job']);report=read_json(ROOT/outcome['attempt']['report']);best=report['results'][0];comparison=best['comparison'];diagnostic=comparison.get('diagnostic',{})
    generate()
    return dict(symbol=symbol,job=task['job'],status=outcome['status'],cache=report['cache'],strict_member_result=comparison['result'],compiler_log=best['receipt']['stdout'] if comparison['result']=='COMPILE_FAILED' else None,diagnostic={k:v for k,v in diagnostic.items() if k not in ('aligned_asm','target_blocks','candidate_blocks')},aligned_asm=diagnostic.get('aligned_asm',[])[:60],full_evidence=outcome['attempt']['report'],timing=dict(best['receipt'].get('timing',{}),**best.get('timing',{}),total_test_api_seconds=time.perf_counter()-began),acceptance='NONE: use accept for fresh independent proof')


def accept(symbol,candidate):
    job=next((j for j in wf.jobs() if j['symbol']==symbol),None)
    if not job:raise FormatError('inspect and test this symbol first')
    directory,job=wf.checked_job(job['id']);report=read_json(ROOT/job['attempts'][-1]['report']) if job.get('attempts') else {}
    digest=identity((ROOT/candidate).resolve());row=next((r for r in report.get('results',[]) if r['candidate'] in report.get('exact_candidates',[]) and r['receipt']['source_identity']==digest),None)
    if row is None:raise FormatError('candidate source is not an immutable exact tested candidate')
    result=wf.promote(job['id'],row['candidate']);generate();return result


def main():
    ap=argparse.ArgumentParser(description=__doc__);sub=ap.add_subparsers(dest='action',required=True)
    sub.add_parser('queue');sub.add_parser('next')
    p=sub.add_parser('inspect');p.add_argument('symbol')
    for name in ['test','accept']:
        p=sub.add_parser(name);p.add_argument('symbol');p.add_argument('candidate')
        if name=='test':p.add_argument('--summary')
    p=sub.add_parser('block');p.add_argument('symbol');p.add_argument('reason');p.add_argument('--cause',required=True);p.add_argument('--next-experiment',required=True)
    args=ap.parse_args()
    with wf.workflow_lock(),redirect_stdout(sys.stderr):
        wf.recover_transaction();wf.recover_interrupted_attempts()
        if args.action=='queue':result=generate()['states']
        elif args.action=='next':
            report=generate();eligible=[r for r in report['functions'] if r['state']=='MATCH_READY'];active=next((r for r in eligible if r['job_status'] in ('OPEN','NEEDS_REVISION','EXACT_CANDIDATE')),None);row=active or next(iter(eligible),None)
            if row is None:raise FormatError('no MATCH_READY tasks remain')
            result=inspect(row['symbol'])
        elif args.action=='inspect':result=inspect(args.symbol)
        elif args.action=='test':result=test(args.symbol,args.candidate,args.summary)
        elif args.action=='accept':result=accept(args.symbol,args.candidate)
        else:
            job=next((j for j in wf.jobs() if j['symbol']==args.symbol),None)
            if not job:raise FormatError('inspect this symbol first')
            result=wf.defer(job['id'],args.cause,args.reason,args.next_experiment);generate()
    print(json.dumps(result,indent=2))

if __name__=='__main__':
    try:main()
    except (FormatError,FileNotFoundError) as exc:raise SystemExit('ERROR: '+str(exc))
