"""Experimental authentic LINK 5.30 build. All missing code/data is marked scaffolding.

Construction reads source/object manifests and symbol inventory, never EXE bytes.
The output is structural research, never counted as recovered or runnable game.
"""
import argparse, os, re, shutil, subprocess
from collections import defaultdict
from common import ROOT, read_json, write_json, identity, FormatError
from compiler import compile_batch, verify_lock
import omf, ne

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--out',default='build/PARTLINK');args=ap.parse_args()
    out=ROOT/args.out;out.mkdir(parents=True,exist_ok=True)
    manifest=read_json(ROOT/'build/recovered/manifest.json');inventory=read_json(ROOT/'evidence/symbols/inventory.json')['symbols']
    lock=read_json(ROOT/'layout/toolchain.json');verify_lock(lock)
    objects=[];publics=set();externals=set();inputs={};object_hashes=set()
    for i,row in enumerate(manifest['game_objects']+manifest['runtime_objects']):
        src=ROOT/row['object']
        if identity(src)!=row['identity']:raise FormatError('changed recovered object')
        if row['identity']['sha256'] in object_hashes:continue
        object_hashes.add(row['identity']['sha256'])
        dest=out/('R%04d.OBJ'%i);shutil.copyfile(src,dest);objects.append(dest.name)
        m=omf.parse(dest.read_bytes());publics.update(p['name'] for p in m['publics']);externals.update(e['name'] for e in m['externals'])
    grouped=defaultdict(list);stubs=[]
    for item in inventory:
        name=item['name']
        if name in publics:continue
        data=item['kind']=='DATA_SYMBOL'
        if data and name not in externals:continue
        if not data and item['ownership']!='GAME' and not (item['ownership']=='UNKNOWN' and name in externals):continue
        if not re.fullmatch(r'[A-Za-z_]\w*',name):raise FormatError('non-C scaffold symbol '+name)
        ident=name[1:] if name.startswith('_') else name
        if data:
            size=max(1,item['next_symbol_upper_bound']-item['offset'])
            # These sizes are conservative scaffolding capacities, not recovered types.
            declaration='unsigned char '+('near ' if item['segment']==10 else 'far ')+ident+'[%d];'%size
            key=('DATA',item['segment_name'])
        else:
            declaration='int '+('far ' if name.startswith('_') else 'far pascal ')+ident+'(void) { return 0; }'
            if name=='WINMAIN':declaration='int far pascal WinMain(unsigned int a, unsigned int b, char far *c, int d) { return 0; }'
            key=('CODE',item['segment_name'])
        grouped[key].append(declaration);stubs.append(dict(symbol=name,kind='GENERATED_DATA_CAPACITY' if data else 'GENERATED_FUNCTION_STUB',segment=item['segment_name']))
    jobs=[]
    for i,((kind,segment),lines) in enumerate(sorted(grouped.items())):
        source=out/('S%04d.C'%i)
        source.write_text('/* STRUCTURAL SCAFFOLDING ONLY. No recovery credit. */\n'+'\n'.join(lines)+'\n')
        flags=['/AL','/G2','/Gs','/Oelw',('/NT' if kind=='CODE' else '/ND')+segment]
        jobs.append(dict(source=source.relative_to(ROOT).as_posix(),flags=flags))
    compiled=compile_batch(jobs)
    for i,(obj,receipt) in enumerate(compiled):
        if obj is None:raise FormatError('stub compile failed: '+receipt['stdout'])
        dest=out/('S%04d.OBJ'%i);shutil.copyfile(obj,dest);objects.append(dest.name)
    for name,path in [('CRT.LIB','toolchain/sdk300/CLIB/LLIBCW.LIB'),('FP.LIB','toolchain/sdk300/CLIB/LLIBFPW.LIB'),('HELPER.LIB','toolchain/sdk300/CLIB/LIBH.LIB'),('WIN.LIB','toolchain/sdk300/WLIB/LIBW.LIB')]:shutil.copyfile(ROOT/path,out/name)
    (out/'PARTIAL.DEF').write_text('NAME SIMPART WINDOWAPI\nDESCRIPTION \'STRUCTURAL SCAFFOLDING - NOT RECOVERED GAME\'\nEXETYPE WINDOWS 3.0\nCODE PRELOAD MOVEABLE DISCARDABLE\nDATA PRELOAD MOVEABLE MULTIPLE\nHEAPSIZE 1024\nSTACKSIZE 8192\n')
    # One input per continuation line avoids the historical response-line limit.
    (out/'PARTIAL.RSP').write_text('+\n'.join(objects)+',\nPARTIAL.EXE,\nPARTIAL.MAP,\nCRT.LIB+FP.LIB+HELPER.LIB+WIN.LIB,\nPARTIAL.DEF /NOD /NOI /MAP /NOPACKCODE;\n')
    command=[str(ROOT/lock['runner']),'-d',str(ROOT/'toolchain/msc700/BIN/LINK.EXE'),'@PARTIAL.RSP']
    result=subprocess.run(command,cwd=out,capture_output=True,timeout=120)
    log=(result.stdout+result.stderr).decode('latin1');(out/'link.log').write_text(log)
    for name in objects+['CRT.LIB','FP.LIB','HELPER.LIB','WIN.LIB','PARTIAL.DEF','PARTIAL.RSP']:inputs[name]=identity(out/name)
    report=dict(scope='STRUCTURAL_SCAFFOLDING_ONLY',recovered_source_credit=0,whole_executable_build=False,
                command=command,linker=identity(ROOT/'toolchain/msc700/BIN/LINK.EXE'),exit_code=result.returncode,
                inputs=inputs,stub_receipts=[r for _,r in compiled],stubs=stubs,log=log,
                recovered_functions=len(manifest['game_objects']),recovered_objects=len({r['identity']['sha256'] for r in manifest['game_objects']}),runtime_objects=len(manifest['runtime_objects']),
                limitations=['Generated code stubs have no game semantics or established ABI','Generated data capacities are not recovered types','No original resources injected','No executable equality claim'])
    output=out/'PARTIAL.EXE'
    if output.exists() and result.returncode==0:
        image=ne.parse(output.read_bytes());report.update(output=identity(output),ne_header=image['header'],segments=[{k:v for k,v in s.items() if k not in ('relocations',)} for s in image['segments']])
    write_json(out/'receipt.json',report);write_json(ROOT/'evidence/experiments/partial-link/results.json',report)
    print('\n'.join(log.splitlines()[-20:]));print('Structural link:',result.returncode,'stubs:',len(stubs),flush=True)
    return result.returncode

if __name__=='__main__':raise SystemExit(main())
