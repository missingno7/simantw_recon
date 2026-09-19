"""Fresh isolated compile. Construction never opens assets/ or evidence/."""
import os
import shutil
import subprocess
import tempfile
import time
from common import ROOT, FormatError, identity, read_json, write_json, sha256

def verify_lock(lock):
    for path,expected in lock['files'].items():
        p=ROOT/path
        if not p.is_file() or identity(p)!=expected:raise FormatError(f'tool hash mismatch: {path}')

def compile_source(source,flags,compiler='msc600a'):
    lock=read_json(ROOT/'layout/toolchain.json');verify_lock(lock)
    config=lock['compilers'][compiler]
    out=ROOT/'build';out.mkdir(exist_ok=True)
    directory=__import__('pathlib').Path(tempfile.mkdtemp(prefix='C',dir=out))
    # Only short local source names cross into the DOS process.
    src=ROOT/source;shutil.copyfile(src,directory/'INPUT.C')
    env={k:v for k,v in os.environ.items() if k.upper() in ('SYSTEMROOT','WINDIR','COMSPEC')}
    env.update(PATH=str((ROOT/config['bin']).resolve()),TMP=str(directory),TEMP=str(directory))
    if config.get('runner')=='win31-dosbox-x':
        # C7's DOSX32 requires a 32-bit DPMI host and its VPFD.386 driver.
        # Mount only construction/tool directories; no original assets.
        win=ROOT/'toolchain/win31';runner=ROOT/'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'
        shutil.copyfile(ROOT/'toolchain/CAPCL.COM',directory/'CAPCL.COM')
        (directory/'GO.BAT').write_text('@echo off\nset PATH=T:\\BIN;C:\\WINDOWS\nset TMP=W:\\\nset TEMP=W:\\\nW:\nCAPCL /c /FoOUT.OBJ '+' '.join(flags)+' INPUT.C > LOG.TXT\nif errorlevel 1 echo FAILED > FAILED.TXT\necho finished > DONE.TXT\nexit\n')
        conf='[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=32\nmachine=svga_s3\n[cpu]\ncore=normal\ncputype=486\ncycles=200000\n[autoexec]\n'
        conf+=f'mount c "{win}"\nmount t "{ROOT/config["bin"].rsplit("/",1)[0]}"\nmount w "{directory}"\nc:\nset PATH=C:\\WINDOWS;T:\\BIN\nC:\\WINDOWS\\WIN /3 W:\\GO.BAT\nexit\n'
        (directory/'RUN.CONF').write_text(conf)
        command=[str(runner),'-conf',str(directory/'RUN.CONF'),'-fastlaunch','-nogui','-nomenu','-noconsole']
        env.update(SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
        process=subprocess.Popen(command,cwd=directory,env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        try:
            deadline=time.monotonic()+30
            while time.monotonic()<deadline and process.poll() is None and not (directory/'DONE.TXT').exists():time.sleep(.1)
        finally:
            if process.poll() is None:process.kill()
            process.wait()
        done=(directory/'DONE.TXT').exists()
        log=(directory/'LOG.TXT').read_bytes() if (directory/'LOG.TXT').exists() else b'No compiler log'
        failed=(directory/'FAILED.TXT').exists() and (directory/'FAILED.TXT').stat().st_size>0
        r=subprocess.CompletedProcess(command,0 if done and not failed else 1,log,b'')
    else:
        command=[str(ROOT/lock['runner']),'-d',str(ROOT/config['bin']/'CL.EXE'),'/c','/FoOUT.OBJ']+flags+['INPUT.C']
        r=subprocess.run(command,cwd=directory,env=env,capture_output=True,timeout=30)
    (directory/'stdout.txt').write_bytes(r.stdout);(directory/'stderr.txt').write_bytes(r.stderr)
    obj=directory/'OUT.OBJ'
    receipt={'source':source,'source_identity':identity(src),'compiler':compiler,'flags':flags,
             'toolchain_lock_sha256':sha256((ROOT/'layout/toolchain.json').read_bytes()),
             'command':command,'exit_code':r.returncode,'stdout':r.stdout.decode('latin1'),'stderr':r.stderr.decode('latin1'),
             'object':obj.relative_to(ROOT).as_posix(),'fixture_dependencies':[]}
    receipt['unsupported_option']=any(x in (receipt['stdout']+receipt['stderr']).lower() for x in ('ignoring unknown flag','invalid for 16-bit target'))
    if r.returncode or not obj.is_file():
        write_json(directory/'receipt.json',receipt)
        raise FormatError('compiler failed: '+receipt['stdout']+receipt['stderr'])
    receipt['object_identity']=identity(obj);write_json(directory/'receipt.json',receipt)
    return obj,receipt

def validate_receipt(receipt):
    if identity(ROOT/receipt['source'])!=receipt['source_identity']:raise FormatError('stale source receipt')
    if identity(ROOT/receipt['object'])!=receipt['object_identity']:raise FormatError('stale object receipt')
    current=ROOT/'layout/toolchain.json'
    if sha256(current.read_bytes())!=receipt['toolchain_lock_sha256']:
        snapshot=ROOT/'layout/toolchain-locks'/(receipt['toolchain_lock_sha256']+'.json')
        if not snapshot.exists() or sha256(snapshot.read_bytes())!=receipt['toolchain_lock_sha256']:raise FormatError('stale toolchain receipt')
        current=snapshot
    verify_lock(read_json(current))
