"""Compiler-in-the-loop matching CLI. Verification explicitly requires fixtures."""
import argparse
import itertools
import json
import sys
from common import ROOT, FormatError, fixture, read_json, write_json, sha256
from compiler import compile_source, validate_receipt
import ne, mapsym, omf
from matcher import compare
from library_match import compare_member,import_symbols

def main():
    ap=argparse.ArgumentParser();ap.add_argument('symbol');ap.add_argument('--matrix',action='store_true');ap.add_argument('--json',action='store_true')
    args=ap.parse_args();name=args.symbol if args.symbol.startswith('_') else '_'+args.symbol
    targets=read_json(ROOT/'src/recovery.json')['targets']
    if name not in targets:raise FormatError(f'no source recipe for {name}; inspect evidence/symbols and function cards')
    target=dict(targets[name],symbol=name);exe=fixture('SIMANTW.EXE');sym=fixture('SIMANTW.SYM');n=ne.parse(exe);s=mapsym.parse(sym);mapsym.cross_check(s,n)
    configurations=[target['flags']]
    if args.matrix:
        configurations=[[model,cpu,'/Gs',opt,'/NT'+target['code_segment']] for model,cpu,opt in itertools.product(['/AM','/AL'],['/G0','/G2'],['/Od','/Oe','/Oes','/Oeg','/Ox'])]
    results=[]
    for flags in configurations:
        path,receipt=compile_source(target['source'],flags,target.get('compiler','msc600a'));validate_receipt(receipt)
        parsed=omf.parse(path.read_bytes())
        result=compare_member(parsed,exe,n,s,import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB')) if target.get('comparison')=='member' else compare(parsed,exe,n,s,target)
        result.update(exe_sha256=sha256(exe),sym_sha256=sha256(sym),receipt=receipt,
                      recipe_sha256=sha256((ROOT/'src/recovery.json').read_bytes()))
        results.append(result)
    good={'FUNCTION_MATCH','CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'}
    results.sort(key=lambda r:(r['result'] in good,r.get('fixups_equal',0)),reverse=True)
    output={'symbol':name,'matrix':args.matrix,'results':results}
    write_json(ROOT/'build'/f'{name}-latest.json',output)
    if args.json:print(json.dumps(output,indent=2))
    else:
        if target.get('comparison')=='member':
            for r in results:print(r['result'],name,'|',' '.join(r['receipt']['flags']))
            return 0 if results[0]['result'] in good else 1
        for r in results:
            print(f"{r['result']}: {name} | length {r['candidate_size']}/{r['original_size']} | bytes {r['ordinary_bytes_equal']}/{r['ordinary_bytes_total']} | fixups {r['fixups_equal']}/{r['fixups_total']} | {' '.join(r['receipt']['flags'])}")
        r=results[0]
        if r['result']!='FUNCTION_MATCH':
            print('First divergence:',r['first_divergence'],'Issues:',', '.join(r['issues']))
            print('Original: ',r['original_hex']);print('Candidate:',r['candidate_hex'])
    return 0 if results[0]['result']=='FUNCTION_MATCH' else 1

if __name__=='__main__':
    try:sys.exit(main())
    except (FormatError,FileNotFoundError) as e:print('ERROR:',e,file=sys.stderr);sys.exit(2)
