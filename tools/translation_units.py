"""Infer candidate compilation groups without inventing historical filenames.

Exact complete-member matches support a grouping but cannot uniquely prove the
historical filename or object boundary. CONFIRMED_TU requires original-object
provenance; this tool never assigns it from matching source alone.
"""
import argparse, json
from common import ROOT, read_json, write_json
from codegen_grinder import run, GOOD

def infer():
    cards=[json.loads(x) for x in (ROOT/'evidence/disassembly/cards.jsonl').read_text().splitlines()]
    candidates=[]
    for a,b in zip(cards,cards[1:]):
        if a['segment']!=b['segment'] or a['ownership']!='GAME' or b['ownership']!='GAME':continue
        reasons=['MAPSYM adjacency'];score=1
        refs=lambda c,key:{(r.get('kind'),r.get('segment'),r.get('offset'),r.get('module'),r.get('ordinal')) for r in c[key]}
        common_calls=refs(a,'calls') & refs(b,'calls');common_globals=refs(a,'globals') & refs(b,'globals')
        if common_calls:reasons.append('shared resolved call targets');score+=2
        if common_globals:reasons.append('shared named globals');score+=2
        if a['symbol'].split('_')[1:2]==b['symbol'].split('_')[1:2]:reasons.append('naming cluster');score+=1
        edges=a['extent'].get('edges',[])+b['extent'].get('edges',[])
        shared=[e for e in edges if e.get('source') is not None and ((e['source']<b['offset']<=e['target']) or (e['target']<b['offset']<=e['source']))]
        if shared:reasons.append('cross-entry direct branch requires joint CFG review');score+=5
        near=[r for r in a['calls']+b['calls'] if r.get('kind')=='near_call' and r.get('offset') in (a['offset'],b['offset'])]
        if near:reasons.append('near-call relationship');score+=3
        if score>1:candidates.append(dict(symbols=[a['symbol'],b['symbol']],status='CANDIDATE_TU',historical_filename=None,score=score,evidence=reasons,cross_entry_branches=shared))
    candidates.sort(key=lambda x:(-x['score'],x['symbols']))
    write_json(ROOT/'evidence/codegen/candidate-tus.json',dict(confidence_levels=['CANDIDATE_TU','STRONGLY_SUPPORTED_TU','CONFIRMED_TU'],groups=candidates))
    print('Candidate TU groups:',len(candidates))

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--spec');ap.add_argument('--out',default='build/tu');args=ap.parse_args()
    if args.spec:
        spec=read_json(ROOT/args.spec)
        if spec.get('tu_confidence') not in ('CANDIDATE_TU','STRONGLY_SUPPORTED_TU'):raise ValueError('explicit candidate TU provenance required')
        result=run(spec,args.out)
        write_json(ROOT/args.out/'tu-evidence.json',dict(status='STRONGLY_SUPPORTED_TU' if result['exact_candidates'] else 'CANDIDATE_TU',historical_filename=None,complete_member_results=str(args.out)+'/results.json',evidence=spec.get('grouping_evidence',[])))
    else:infer()

if __name__=='__main__':main()
