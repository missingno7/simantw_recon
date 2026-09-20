"""Reusable string-instruction, pointer-type and caller-cleanup fingerprints.

Type/calling-convention contrasts are hypotheses, NOT semantic equivalence claims.
All generated C, compiler receipts, parsed fixups and features are retained.
"""
import argparse, itertools
from collections import Counter
from common import ROOT, read_json, write_json, fixture, identity, FormatError
from compiler import compile_batch
from codegen_grinder import instruction_features, score_object
from library_match import import_symbols
from analysis import decoder
import omf, ne, mapsym

BASE=['/AL','/G2','/Gs','/Oelw']

def abi_cases():
    for convention,distance,prototype,returns,use in itertools.product(['cdecl','pascal'],['far','near'],[True,False],['void','int'],['ignore','assign','return']):
        if returns=='void' and use!='ignore':continue
        declaration=f'extern {returns} {distance} {convention} close('+('int handle' if prototype else '')+');\n'
        body={'ignore':'close(unpackHandle);','assign':'int result; result = close(unpackHandle);','return':'return close(unpackHandle);'}[use]
        source='extern int near unpackHandle;\n'+declaration+('int' if use=='return' else 'void')+' UnpackFileClose(void) { '+body+' }\n'
        yield dict(family='calling_convention',symbol='_UnpackFileClose',choices=dict(convention=convention,distance=distance,prototype=prototype,returns=returns,use=use),source=source,flags=BASE+['/NTSIMTWO_MODULE'])

def pointer_cases():
    for kind in ['char far *','void far *','unsigned char far *','char huge *']:
        for shape in ['array','structure','union_parameter','pointer_to_pointer']:
            prefix='typedef '+kind+' Buffer;\nextern int near unpackHandle;\n'
            param='union BufferValue buffer' if shape=='union_parameter' else 'Buffer buffer'
            if shape=='union_parameter':prefix+='union BufferValue { Buffer pointer; unsigned long representation; };\n'
            expression='buffer.pointer' if shape=='union_parameter' else 'buffer'
            if shape=='structure':
                prefix+='struct UnpackState { unsigned int size; Buffer buffer; int handle; };\n'
                body='struct UnpackState near *state; state=(struct UnpackState near *)((char near *)&unpackHandle-6); state->buffer=buffer; state->size=size;'
            elif shape=='pointer_to_pointer':body='Buffer near *slot; slot=(Buffer near *)&unpackHandle; slot[-1]=buffer; ((unsigned int near *)&unpackHandle)[-3]=size;'
            else:body='((Buffer near *)&unpackHandle)[-1]='+expression+'; ((unsigned int near *)&unpackHandle)[-3]=size;'
            yield dict(family='far_pointer_type',symbol='_UnpackSetBuf',choices=dict(type=kind,shape=shape),source=prefix+'void UnpackSetBuf('+param+', unsigned int size) { '+body+' }\n',flags=BASE+['/NTSIMTWO_MODULE'])

def string_cases():
    for pointer,intrinsic in itertools.product(['near','far','huge'],[False,True]):
        for operation in ['indexed_zero','pointer_zero','word_zero','copy','memset','memcpy','_fmemset','_fmemcpy','search','indexed_word_zero','strlen','_fstrlen','memchr','_fmemchr']:
            prefix=''
            if operation in ('strlen','_fstrlen','memchr','_fmemchr'):
                name=operation
                prefix=('extern unsigned int '+name+'(const char far *p);\n') if 'strlen' in name else ('extern void far *'+name+'(const void far *p, int value, unsigned int n);\n')
                if intrinsic:prefix+='#pragma intrinsic('+name+')\n'
                prefix+='extern unsigned int near observed;\n'
                body=('observed = '+name+'((const char far *)d);') if 'strlen' in name else ('observed = ('+name+'(d, 0, n) != 0);')
            elif operation in ('memset','memcpy','_fmemset','_fmemcpy'):
                far=operation.startswith('_f');memory='far';name=operation  # /AL memory functions use far data pointers
                prefix='extern void '+memory+' * '+name+'(void '+memory+' *d, '+('int v' if 'set' in name else 'const void '+memory+' *s')+', unsigned int n);\n'
                if intrinsic:prefix+='#pragma intrinsic('+name+')\n'
                body=name+'(d, '+('0' if 'set' in name else 's')+', n);'
            else:body={'indexed_zero':'unsigned int i; for(i=0;i<n;++i)d[i]=0;', 'pointer_zero':'while(n--) *d++=0;', 'indexed_word_zero':'unsigned int i; unsigned int '+pointer+' *w=(unsigned int '+pointer+' *)d; for(i=0;i<n;++i)w[i]=0;', 'word_zero':'unsigned int '+pointer+' *w=(unsigned int '+pointer+' *)d; while(n--) *w++=0;', 'copy':'while(n--) *d++=*s++;','search':'while(n-- && *d != 0) ++d;'}[operation]
            source=prefix+'void probe(unsigned char '+pointer+' *d, unsigned char '+pointer+' *s, unsigned int n) { '+body+' }\n'
            yield dict(family='string_idiom',symbol='_probe',choices=dict(pointer=pointer,intrinsic=intrinsic,operation=operation),source=source,flags=['/AL','/G2','/Gs','/Oelwi' if intrinsic else '/Oelw','/NTPROBE'])

def library_idioms():
    findings=[];errors=Counter()
    for path in ['toolchain/sdk300/CLIB/LLIBCW.LIB','toolchain/msc700/LIB/LLIBCW.LIB','toolchain/sdk300/CLIB/LIBH.LIB']:
        for b in omf.library_modules((ROOT/path).read_bytes()):
            try:m=omf.parse(b)
            except FormatError as e:errors[str(e)]+=1;continue
            for seg in m['segments']:
                if seg['class']!='CODE':continue
                code=bytes.fromhex(seg['data_hex']);rows=list(decoder().disasm(code,0))
                for i,ins in enumerate(rows):
                    if any(x in ins.mnemonic for x in ['stos','movs','scas']):
                        findings.append(dict(library=path,member=m['name'],member_sha256=m['sha256'],offset=ins.address,instruction=ins.mnemonic+' '+ins.op_str,window=[x.bytes.hex()+' '+x.mnemonic+' '+x.op_str for x in rows[max(0,i-2):i+3]]))
    return dict(findings=findings,unsupported_members=dict(errors))

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--suite',choices=['all','abi','pointer','string'],default='all');ap.add_argument('--out',default='build/fingerprints');args=ap.parse_args()
    cases=[]
    if args.suite in ('all','abi'):
        original=list(abi_cases());cases+=original
        for case in original:
            cases.append(dict(case,choices=dict(case['choices'],optimizer='/Oelws'),flags=['/AL','/G2','/Gs','/Oelws','/NTSIMTWO_MODULE']))
    if args.suite in ('all','pointer'):cases+=list(pointer_cases())
    if args.suite in ('all','string'):cases+=list(string_cases())
    out=ROOT/args.out;out.mkdir(parents=True,exist_ok=True);jobs=[]
    for i,case in enumerate(cases):
        dest=out/('probe%04d.c'%i);dest.write_text(case.pop('source'))
        jobs.append(dict(source=dest.relative_to(ROOT).as_posix(),flags=case['flags']))
    print('Fingerprint cases:',len(cases),flush=True);compiled=compile_batch(jobs)
    raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'));imports=import_symbols(ROOT/'toolchain/sdk300/WLIB/LIBW.LIB');results=[]
    for case,(obj,receipt) in zip(cases,compiled):
        row=dict(case,receipt=receipt)
        if obj:
            m=omf.parse(obj.read_bytes());row['features']=[dict(segment=ss['name'],length=ss['length'],**instruction_features(bytes.fromhex(ss['data_hex']))) for ss in m['segments'] if ss['class']=='CODE']
            row['fixups']=m['fixups']
            if case['family']!='string_idiom':
                try:row['comparison']=score_object(m,raw,n,s,imports,case['symbol'])
                except FormatError as e:row['comparison']=dict(result='UNSUPPORTED_COMPARISON',issues=[str(e)])
        results.append(row)
    report=dict(scope='ABI/type hypotheses and string compiler fingerprints; no source promotion',results=results,libraries=library_idioms())
    write_json(out/'results.json',report);write_json(ROOT/'evidence/codegen/fingerprints.json',report)
    print('Compiled',sum(obj is not None for obj,_ in compiled),'of',len(cases))
    print('Exact candidate cases:',[(i,r['symbol']) for i,r in enumerate(results) if r.get('comparison',{}).get('result') in ('CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER')])

if __name__=='__main__':main()
