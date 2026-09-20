"""Bounded semantic-template exploration with authentic batch C7 and strict OMF scoring.

Templates explicitly list equivalence classes, assumptions and replacement sites.
No arbitrary token mutations, byte patching, or automatic source promotion.
"""
import argparse
import itertools
import time
from codegen_transforms import generate
from common import ROOT, FormatError, fixture, identity, read_json, write_json, sha256
from compiler import compile_batch
from analysis import decoder, extent
from library_match import compare_member, import_symbols
import ne, mapsym, omf

GOOD={'CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'}

def variants(spec):
    template=spec.get('template')
    if template is None:template=(ROOT/spec['source']).read_text()
    budget=spec.get('max_candidates',1000)
    axes=[dict(a,values=list(itertools.islice(generate(a),budget+1))) if 'generator' in a else a for a in spec.get('axes',[])]
    for axis in axes:
        if len(axis.get('values',[]))>budget:raise FormatError('axis exceeds candidate budget')
        if not axis.get('rationale') or not axis.get('values'):raise FormatError('axis needs semantic rationale and values')
        if template.count(axis['marker'])!=1:raise FormatError('replacement marker must occur exactly once')
    raw_count=1
    for axis in axes:
        raw_count*=len(axis['values'])
        if raw_count>budget*16:raise FormatError('raw transformation space exceeds bounded budget')
    seen=set()
    for values in itertools.product(*(a['values'] for a in axes)):
        source=template;choices={}
        for axis,value in zip(axes,values):
            source=source.replace(axis['marker'],value);choices[axis['name']]=value
        digest=sha256(source.encode())
        if digest not in seen:
            seen.add(digest);yield source,choices

def instruction_features(code):
    rows=list(decoder().disasm(code,0))
    return dict(frame=[i.mnemonic+' '+i.op_str for i in rows if i.mnemonic in ('enter','leave')],
                registers=sorted({decoder().reg_name(r) for i in rows for r in i.regs_access()[1]}),
                cleanup=[i.mnemonic+' '+i.op_str for j,i in enumerate(rows) if j>0 and rows[j-1].mnemonic in ('call','lcall') and (i.mnemonic=='pop' or (i.mnemonic=='add' and i.op_str.startswith('sp,')))],
                pointer_loads=[i.mnemonic+' '+i.op_str for i in rows if i.mnemonic in ('les','lds')],
                string_ops=[i.mnemonic for i in rows if any(x in i.mnemonic for x in ('stos','movs','scas','lods'))])

def score_object(m,raw,n,s,imports,symbol):
    pubs=[p for p in m['publics'] if p['name']==symbol]
    if len(pubs)!=1:raise FormatError('missing or ambiguous requested target public')
    pub=pubs[0]
    if not 1<=pub['segment']<=len(m['segments']):raise FormatError('requested target has no code segment')
    if m['segments'][pub['segment']-1]['class']!='CODE':raise FormatError('requested target is not code')
    result=compare_member(m,raw,n,s,imports) or {'result':'UNPLACED','issues':['no public anchors']}
    if pub:
        ss=m['segments'][pub['segment']-1]
        result['code_contribution_size']=ss['length']
        result['features']=instruction_features(bytes.fromhex(ss['data_hex']))
        code=bytes.fromhex(ss['data_hex']);begin=pub['offset']
        stop=min([p['offset'] for p in m['publics'] if p['segment']==pub['segment'] and p['offset']>begin]+[len(code)])
        result['candidate_function_extent']=extent(code,begin,stop)
        for seg in s['segments']:
            original=next((p for p in seg['symbols'] if p['name']==symbol),None)
            if original:
                ns=n['segments'][seg['number']-1];data=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
                start=original['offset'];bound=min([p['offset'] for p in seg['symbols'] if p['offset']>start]+[len(data)])
                result['target_function_extent']=extent(data,start,bound)
                result['target_features']=instruction_features(data[start:result['target_function_extent']['end'] or bound])
                break
    result['first_divergence']=next(({'segment':c['segment'],'offset':c['divergences'][0]} for c in result.get('contributions',[]) if c['divergences']),None)
    return result

def rank(row):
    r=row['comparison']
    return (r['result'] in GOOD,r.get('fixups_equal',0)/max(r.get('fixups_total',1),1),
            r.get('literal_equal',0)/max(r.get('literal_compared',1),1),-len(r.get('issues',[])))

def run(spec,path,limit=None,cache=False):
    output=ROOT/path;output.mkdir(parents=True,exist_ok=True)
    budget=spec.get('max_candidates',1000)
    if not isinstance(budget,int) or not 1<=budget<=10000:raise FormatError('invalid candidate budget')
    candidates=list(itertools.islice(variants(spec),min(budget,limit) + 1 if limit is not None and limit>0 else budget+1))
    if limit is not None:
        if limit<1:raise FormatError('candidate limit must be positive')
        candidates=candidates[:limit]
    if len(candidates)>spec.get('max_candidates',1000):raise FormatError('explicit candidate budget exceeded')
    jobs=[]
    for i,(source,choices) in enumerate(candidates):
        dest=output/('candidate%04d.c'%i);dest.write_text(source)
        jobs.append(dict(source=dest.relative_to(ROOT).as_posix(),flags=spec['flags']))
    print('Compiling',len(jobs),'controlled variants in bounded historical sessions',flush=True)
    if cache:
        from codegen_cache import compile_cached
        compiled,cache_stats=compile_cached(jobs,spec.get('compiler','msc700'))
    else:
        compiled=compile_batch(jobs,spec.get('compiler','msc700'))
        cache_stats=dict(hits=0,misses=len(jobs),environment_launches=sum(r['timing']['environment_launches'] for _,r in compiled) if compiled and all('environment_launches' in r.get('timing',{}) for _,r in compiled) else len({r['batch_directory'] for _,r in compiled}))
    raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'))
    imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');results=[]
    for i,(obj,receipt) in enumerate(compiled):
        stage_timing={}
        if obj and not receipt['unsupported_option']:
            if identity(ROOT/receipt['source'])!=receipt['source_identity'] or identity(obj)!=receipt['object_identity']:raise FormatError('changed batch input/output')
            try:
                parse_started=time.perf_counter();module=omf.parse(obj.read_bytes());parse_seconds=time.perf_counter()-parse_started
                match_started=time.perf_counter();r=score_object(module,raw,n,s,imports,spec['symbol']);match_seconds=time.perf_counter()-match_started
                from codegen_diff import diagnose,render
                diff_started=time.perf_counter();r['diagnostic']=diagnose(module,raw,n,s,spec['symbol'],r)
                (output/('candidate%04d.diff.txt'%i)).write_text(render(r['diagnostic']),encoding='utf-8')
                stage_timing=dict(omf_parse_seconds=parse_seconds,strict_match_seconds=match_seconds,diagnostic_diff_seconds=time.perf_counter()-diff_started)
            except FormatError as e:r=dict(result='UNSUPPORTED_COMPARISON',issues=[str(e)])
        else:r=dict(result='COMPILE_FAILED',issues=[receipt['stdout']])
        results.append(dict(candidate=i,choices=candidates[i][1],receipt=receipt,comparison=r,timing=stage_timing))
    results.sort(key=rank,reverse=True)
    report=dict(symbol=spec['symbol'],spec=spec,exe_sha256=sha256(raw),sym_sha256=s['sha256'],
                candidates=len(jobs),completed_candidates=sum(r['receipt']['exit_code']==0 for r in results),environment_launches=cache_stats['environment_launches'],cache=cache_stats,exact_candidates=[r['candidate'] for r in results if r['comparison']['result'] in GOOD],
                promotion='NONE: independent rebuild and recipe review required',results=results)
    write_json(output/'results.json',report)
    print('Completed',report['completed_candidates'],'of',len(jobs),'candidates',flush=True)
    for row in results[:10]:
        r=row['comparison'];print(row['candidate'],r['result'],'bytes',r.get('literal_equal'),r.get('literal_compared'),'fixups',r.get('fixups_equal'),r.get('fixups_total'),'size',r.get('code_contribution_size'),flush=True)
    return report

def archive_report(report,destination):
    """Keep full evidence for each distinct comparison, index every candidate.

    Build-local results retain all raw logs/receipts. The committed index records
    source and object identities for every candidate, and one full representative
    of each distinct code/fixup result to avoid megabytes of repeated JSON.
    """
    import json
    representatives=[];groups={};index=[]
    for row in report['results']:
        digest=sha256(json.dumps(row['comparison'],sort_keys=True).encode())
        if digest not in groups:
            groups[digest]=len(representatives);representatives.append(row)
        receipt=row['receipt']
        index.append(dict(candidate=row['candidate'],source_identity=receipt['source_identity'],object_identity=receipt.get('object_identity'),
                          exit_code=receipt['exit_code'],result=row['comparison']['result'],representative=groups[digest],
                          batch_directory=receipt['batch_directory'],batch_index=receipt['batch_index']))
    compact={k:v for k,v in report.items() if k!='results'}
    compact.update(results=representatives,candidate_index=index,distinct_comparisons=len(representatives))
    write_json(ROOT/destination,compact)


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('spec');ap.add_argument('--out',required=True);ap.add_argument('--limit',type=int);ap.add_argument('--evidence');ap.add_argument('--cache',action='store_true')
    args=ap.parse_args();report=run(read_json(ROOT/args.spec),args.out,args.limit,args.cache)
    if args.evidence:archive_report(report,args.evidence)

if __name__=='__main__':main()
