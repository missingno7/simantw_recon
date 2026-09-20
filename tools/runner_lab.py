"""Bounded lighter-runner screening. Failed hosts never replace the baseline."""
import json,os,shutil,subprocess,tempfile,time
from pathlib import Path
from common import ROOT,read_json,write_json,identity


def main():
    oracle=read_json(ROOT/'evidence/experiments/toolchain/msc700-baseline-Oelw.json');probe=oracle['results'][0];lock=read_json(ROOT/'layout/toolchain.json');results=[]
    for environment in ['player','dosbox']:
        for host in ['HDPMI32','CWSDPMI']:
            out=Path(tempfile.mkdtemp(prefix='HOST',dir=ROOT/'build'));(out/'INPUT.C').write_bytes((ROOT/probe['receipt']['source']).read_bytes())
            for p in (ROOT/'toolchain/msc700/BIN').iterdir():
                if p.is_file():shutil.copyfile(p,out/p.name)
            host_path=ROOT/('toolchain/dpmi/HDPMI32.EXE' if host=='HDPMI32' else 'toolchain/csdpmi7/bin/CWSDPMI.EXE');shutil.copyfile(host_path,out/(host+'.EXE'))
            command=['nasm','-f','bin',str(ROOT/'tools/runner_host.asm'),'-o',str(out/'HOSTRUN.COM')]+(['-DCWSDPMI=1'] if host=='CWSDPMI' else [])
            subprocess.run(command,check=True,capture_output=True)
            env={k:v for k,v in os.environ.items() if k.upper() in ('SYSTEMROOT','WINDIR','COMSPEC')};env.update(PATH=str(out),TMP=str(out),TEMP=str(out))
            args=['/c','/FoOUTPUT.OBJ']+probe['flags']+['INPUT.C']
            if environment=='player':command=[str(ROOT/lock['runner']),'-d','-x',str(out/'HOSTRUN.COM')]+args
            else:
                (out/'GO.BAT').write_text('@echo off\nset PATH=W:\\\nset TMP=W:\\\nset TEMP=W:\\\nHOSTRUN '+' '.join(args)+' > LOG.TXT\necho finished > DONE.TXT\nexit\n')
                conf='[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=128\n[cpu]\ncore=normal\ncputype=486\ncycles=200000\n[autoexec]\nmount w "'+str(out)+'"\nw:\nGO.BAT\nexit\n';(out/'RUN.CONF').write_text(conf)
                command=[str(ROOT/'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'),'-conf',str(out/'RUN.CONF'),'-fastlaunch','-nogui','-nomenu','-noconsole'];env.update(SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
            start=time.perf_counter()
            try:
                r=subprocess.run(command,cwd=out,env=env,capture_output=True,timeout=8);record=dict(exit_code=r.returncode,stdout=r.stdout.decode('latin1'),stderr=r.stderr.decode('latin1'))
            except subprocess.TimeoutExpired as e:record=dict(timeout=True,stdout=(e.stdout or b'').decode('latin1'),stderr=(e.stderr or b'').decode('latin1'))
            record.update(environment=environment,host=host,host_identity=identity(host_path),directory=out.relative_to(ROOT).as_posix(),command=command,elapsed_seconds=time.perf_counter()-start,object=identity(out/'OUTPUT.OBJ') if (out/'OUTPUT.OBJ').exists() else None,log=(out/'LOG.TXT').read_text(encoding='latin1')[:2000] if (out/'LOG.TXT').exists() else '')
            results.append(record);print(environment,host,'object',bool(record['object']),'timeout',record.get('timeout',False),flush=True)
    report=dict(scope='FIRST_CANONICAL_PROBE_SCREENING_ONLY',results=results,production_change=False,rule='Any successful host still requires all 18 canonical OMF probes before adoption.')
    write_json(ROOT/'evidence/experiments/runner/minimal-hosts.json',report)

if __name__=='__main__':main()
