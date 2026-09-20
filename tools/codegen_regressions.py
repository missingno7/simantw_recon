"""Compile and score every frozen readable draft through the infrastructure."""
from common import ROOT, read_json, write_json, fixture, identity, FormatError
from compiler import compile_batch
from codegen_grinder import score_object
from library_match import import_symbols
import omf, ne, mapsym

def main():
    corpus=read_json(ROOT/'evidence/codegen/corpus.json')['drafts'];inventory={r['name']:r for r in read_json(ROOT/'evidence/symbols/inventory.json')['symbols']}
    jobs=[]
    for row in corpus:
        if identity(ROOT/row['source'])!=row['identity']:raise FormatError('frozen draft changed')
        jobs.append(dict(source=row['source'],flags=['/AL','/G2','/Gs','/Oelw','/NT'+inventory[row['symbol']]['segment_name']]))
    compiled=compile_batch(jobs);raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');rows=[]
    for case,(obj,receipt) in zip(corpus,compiled):
        result=dict(result='COMPILE_FAILED',issues=[receipt['stdout']])
        if obj:
            try:result=score_object(omf.parse(obj.read_bytes()),raw,n,s,imports,case['symbol'])
            except FormatError as e:result=dict(result='UNSUPPORTED_COMPARISON',issues=[str(e)])
        rows.append(dict(symbol=case['symbol'],receipt=receipt,comparison=result))
    write_json(ROOT/'evidence/codegen/corpus-results.json',dict(cases=len(rows),compiled=sum(r['receipt']['exit_code']==0 for r in rows),results=rows))
    print('Regression drafts compiled:',sum(r['receipt']['exit_code']==0 for r in rows),'/',len(rows),flush=True)

if __name__=='__main__':main()
