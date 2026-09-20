"""Attach an explicitly synthetic resource with the authentic Windows 3.0 SDK RC."""
import shutil, subprocess, os, tempfile
from pathlib import Path
from common import ROOT, read_json, write_json, identity, FormatError
from compiler import verify_lock
import ne

def main():
    lock=read_json(ROOT/'layout/toolchain.json');verify_lock(lock)
    src=ROOT/'build/PARTLINK/PARTIAL.EXE';report=read_json(ROOT/'evidence/experiments/partial-link/results.json')
    if identity(src)!=report['output']:raise FormatError('changed partial link')
    out=Path(tempfile.mkdtemp(prefix='RES',dir=ROOT/'build'))
    shutil.copyfile(src,out/'RESLINK.EXE')
    for name in ['RC.EXE','RCPP.EXE','RCPP.ERR']:shutil.copyfile(ROOT/'toolchain/sdk300/RESTOOLS'/name,out/name)
    (out/'SYNTH.RC').write_text('STRINGTABLE\nBEGIN\n1, "Structural scaffold only"\nEND\n')
    runs=[]
    (out/'GO.BAT').write_text('@echo off\nRC /r SYNTH.RC > COMPILE.LOG\nif errorlevel 1 goto failed\nRC SYNTH.RES RESLINK.EXE > BIND.LOG\nif errorlevel 1 goto failed\necho finished > DONE.TXT\ngoto end\n:failed\necho failed > FAILED.TXT\n:end\nexit\n')
    conf='[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=32\n[cpu]\ncycles=max\n[autoexec]\nmount w "'+str(out)+'"\nw:\nset PATH=W:\\\nGO.BAT\nexit\n'
    (out/'RUN.CONF').write_text(conf)
    command=[str(ROOT/'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'),'-conf',str(out/'RUN.CONF'),'-fastlaunch','-nogui','-nomenu','-noconsole']
    env=dict(os.environ,SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
    r=subprocess.run(command,cwd=out,env=env,capture_output=True,timeout=30)
    success=(out/'DONE.TXT').exists() and not (out/'FAILED.TXT').exists()
    runs.append(dict(command=command,exit_code=0 if success else 1,configuration_identity=identity(out/'RUN.CONF'),stdout='\n'.join(p.read_text(encoding='latin1') for p in [out/'COMPILE.LOG',out/'BIND.LOG'] if p.exists()),stderr=r.stderr.decode('latin1')))
    result=dict(scope='SYNTHETIC_RESOURCE_SCAFFOLDING_ONLY',recovery_credit=0,directory=out.relative_to(ROOT).as_posix(),input=identity(src),source=identity(out/'SYNTH.RC'),tools={name:identity(out/name) for name in ['RC.EXE','RCPP.EXE','RCPP.ERR']},runs=runs)
    if runs[-1]['exit_code']==0:
        image=ne.parse((out/'RESLINK.EXE').read_bytes());result.update(output=identity(out/'RESLINK.EXE'),resources=image['resources'],ne_header=image['header'])
    write_json(ROOT/'evidence/experiments/partial-link/resource-probe.json',result)
    print('Resource compiler exit:',runs[-1]['exit_code'],'resources:',len(result.get('resources',[])))
    return runs[-1]['exit_code']

if __name__=='__main__':raise SystemExit(main())
