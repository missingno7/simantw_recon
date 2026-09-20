"""Fresh isolated compile. Construction never opens assets/ or evidence/."""
import os
import shutil
import subprocess
import tempfile
import time
from contextlib import contextmanager
from pathlib import Path
from common import ROOT, FormatError, identity, read_json, write_json, sha256

def verify_lock(lock):
    for path,expected in lock['files'].items():
        p=ROOT/path
        if not p.is_file() or identity(p)!=expected:raise FormatError(f'tool hash mismatch: {path}')

def _compile_source(source,flags,compiler='msc600a'):
    total_started=time.perf_counter();launch_wall=None
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
        (directory/'GO.BAT').write_text('@echo off\nset PATH=T:\\BIN;C:\\WINDOWS\nset TMP=W:\\\nset TEMP=W:\\\nW:\necho ready > HOST.RDY\necho start > CL.BEG\nCAPCL /c /FoOUT.OBJ '+' '.join(flags)+' INPUT.C > LOG.TXT\nif errorlevel 1 echo FAILED > FAILED.TXT\necho finished > DONE.TXT\nexit\n')
        conf='[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=32\nmachine=svga_s3\n[cpu]\ncore=normal\ncputype=486\ncycles=200000\n[autoexec]\n'
        conf+=f'mount c "{win}"\nmount t "{ROOT/config["bin"].rsplit("/",1)[0]}"\nmount w "{directory}"\nc:\nset PATH=C:\\WINDOWS;T:\\BIN\nC:\\WINDOWS\\WIN /3 W:\\GO.BAT\nexit\n'
        (directory/'RUN.CONF').write_text(conf)
        command=[str(runner),'-conf',str(directory/'RUN.CONF'),'-fastlaunch','-nogui','-nomenu','-noconsole']
        env.update(SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
        launch_wall=time.time_ns()
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
    receipt['timing']=dict(total_compile_request_seconds=time.perf_counter()-total_started,runner_startup_seconds=((directory/'HOST.RDY').stat().st_ctime_ns-launch_wall)/1e9 if launch_wall and (directory/'HOST.RDY').exists() else None,compiler_execution_seconds=((directory/'DONE.TXT').stat().st_ctime_ns-(directory/'CL.BEG').stat().st_ctime_ns)/1e9 if (directory/'CL.BEG').exists() and (directory/'DONE.TXT').exists() else None,measurement='Host file-creation timestamps around DOS runner-ready and CL execution markers; CL includes its internal pass startup')
    receipt['unsupported_option']=any(x in (receipt['stdout']+receipt['stderr']).lower() for x in ('ignoring unknown flag','ignoring unknown option','invalid for 16-bit target'))
    if r.returncode or not obj.is_file():
        write_json(directory/'receipt.json',receipt)
        raise FormatError('compiler failed: '+receipt['stdout']+receipt['stderr'])
    receipt['object_identity']=identity(obj);write_json(directory/'receipt.json',receipt)
    return obj,receipt

def validate_receipt(receipt, validated_locks=None):
    if receipt.get('exit_code')!=0 or receipt.get('unsupported_option'):raise FormatError('unsuccessful or unsupported compiler receipt')
    if identity(ROOT/receipt['source'])!=receipt['source_identity']:raise FormatError('stale source receipt')
    if identity(ROOT/receipt['object'])!=receipt['object_identity']:raise FormatError('stale object receipt')
    current=ROOT/'layout/toolchain.json'
    if sha256(current.read_bytes())!=receipt['toolchain_lock_sha256']:
        snapshot=ROOT/'layout/toolchain-locks'/(receipt['toolchain_lock_sha256']+'.json')
        if not snapshot.exists() or sha256(snapshot.read_bytes())!=receipt['toolchain_lock_sha256']:raise FormatError('stale toolchain receipt')
        current=snapshot
    digest=receipt['toolchain_lock_sha256']
    if validated_locks is None or digest not in validated_locks:
        verify_lock(read_json(current))
        if validated_locks is not None:validated_locks.add(digest)

def _compile_session(jobs, compiler='msc700', timeout=None):
    """Compile an ordered queue in ONE Win3.x session, with isolated per-job outputs.

    Jobs contain source and flags. Failures are returned (never silently skipped).
    The worker sees only tool directories and a fresh construction directory.
    No original fixtures or evidence are mounted. DOS filenames are always 8.3.
    """
    jobs=list(jobs)
    if not jobs:return []
    if len(jobs)>9999:raise FormatError('batch exceeds DOS job-name capacity')
    lock=read_json(ROOT/'layout/toolchain.json');verify_lock(lock)
    config=lock['compilers'][compiler]
    if config.get('runner')!='win31-dosbox-x':raise FormatError('batch runner requires Win3.x compiler')
    directory=Path(tempfile.mkdtemp(prefix='Q',dir=ROOT/'build'))
    shutil.copyfile(ROOT/'toolchain/CAPCL.COM',directory/'CAPCL.COM')
    lines=['@echo off','set PATH=T:\\BIN;C:\\WINDOWS','set TMP=W:\\','set TEMP=W:\\','W:','echo ready > W:\\HOST.RDY']
    for i,job in enumerate(jobs):
        stem='J%04d'%i
        flags=job['flags']
        if any(any(c in f for c in '\r\n><&|') for f in flags):raise FormatError('unsafe compiler flag')
        jobdir=directory/('B%04d'%(i//64));jobdir.mkdir(exist_ok=True)
        if i%64==0:lines += ['cd W:\\'+jobdir.name, 'set TMP=W:\\'+jobdir.name, 'set TEMP=W:\\'+jobdir.name]
        shutil.copyfile(ROOT/job['source'],jobdir/(stem+'.C'))
        compile_command='W:\\CAPCL /c /Fo'+stem+'.OBJ '+' '.join(flags)+' '+stem+'.C > '+stem+'.LOG'
        worker=['echo start > '+stem+'.BEG',compile_command,'if errorlevel 1 goto failed','echo finished > '+stem+'.END','goto end',':failed','echo FAILED > '+stem+'.ERR',':end']
        (jobdir/(stem+'.BAT')).write_text('\n'.join(worker)+'\n')
        lines.append('call W:\\'+jobdir.name+'\\'+stem+'.BAT')
    lines += ['echo finished > W:\\DONE.TXT','exit']
    (directory/'GO.BAT').write_text('\n'.join(lines)+'\n')
    conf='[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=128\nmachine=svga_s3\n[cpu]\ncore=normal\ncputype=486\ncycles=200000\n[autoexec]\n'
    conf+=f'mount c "{ROOT/"toolchain/win31"}"\nmount t "{ROOT/config["bin"].rsplit("/",1)[0]}"\nmount w "{directory}"\nc:\nset PATH=C:\\WINDOWS;T:\\BIN\nC:\\WINDOWS\\WIN /3 W:\\GO.BAT\nexit\n'
    (directory/'RUN.CONF').write_text(conf)
    runner=ROOT/'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'
    command=[str(runner),'-conf',str(directory/'RUN.CONF'),'-fastlaunch','-nogui','-nomenu','-noconsole']
    env={k:v for k,v in os.environ.items() if k.upper() in ('SYSTEMROOT','WINDIR','COMSPEC')}
    env.update(SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
    started=time.monotonic();launch_wall=time.time_ns()
    process=subprocess.Popen(command,cwd=directory,env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    try:
        deadline=started+(timeout if timeout is not None else 30+len(jobs)*3)
        while time.monotonic()<deadline and process.poll() is None and not (directory/'DONE.TXT').exists():time.sleep(.1)
    finally:
        if process.poll() is None:process.kill()
        process.wait()
    results=[]
    for i,job in enumerate(jobs):
        stem='J%04d'%i;jobdir=directory/('B%04d'%(i//64));obj=jobdir/(stem+'.OBJ');log=jobdir/(stem+'.LOG')
        done=(jobdir/(stem+'.END')).exists()
        error=jobdir/(stem+'.ERR')
        failed=error.exists() and error.stat().st_size>0
        receipt=dict(source=job['source'],source_identity=identity(jobdir/(stem+'.C')),compiler=compiler,
                     flags=job['flags'],toolchain_lock_sha256=sha256((ROOT/'layout/toolchain.json').read_bytes()),
                     command=command,compile_command=(jobdir/(stem+'.BAT')).read_text().splitlines()[1],batch_index=i,
                     batch_directory=directory.relative_to(ROOT).as_posix(),configuration_identity=identity(directory/'RUN.CONF'),queue_identity=identity(directory/'GO.BAT'),exit_code=0 if done and not failed and obj.exists() else 1,
                     stdout=log.read_text(encoding='latin1') if log.exists() else 'No compiler log',stderr='',
                     object=obj.relative_to(ROOT).as_posix(),fixture_dependencies=[])
        receipt['timing']=dict(runner_startup_seconds=((directory/'HOST.RDY').stat().st_ctime_ns-launch_wall)/1e9 if (directory/'HOST.RDY').exists() else None,compiler_execution_seconds=((jobdir/(stem+'.END')).stat().st_ctime_ns-(jobdir/(stem+'.BEG')).stat().st_ctime_ns)/1e9 if done and (jobdir/(stem+'.BEG')).exists() else None,measurement='Shared startup plus per-job host file-creation timestamps; internal pass startup included')
        receipt['unsupported_option']=any(x in receipt['stdout'].lower() for x in ('ignoring unknown flag','ignoring unknown option','invalid for 16-bit target'))
        if obj.exists():receipt['object_identity']=identity(obj)
        write_json(jobdir/(stem+'.json'),receipt)
        results.append((obj if receipt['exit_code']==0 else None,receipt))
    write_json(directory/'batch.json',dict(jobs=len(jobs),environment_launches=1,completed=sum(r['exit_code']==0 for _,r in results),
               queue_identity=identity(directory/'GO.BAT'),configuration_identity=identity(directory/'RUN.CONF'),elapsed_seconds=time.monotonic()-started,receipts=[r for _,r in results]))
    return results


def _compile_batch(jobs, compiler='msc700', timeout=None, session_limit=96):
    """Bounded queue: amortize boot cost while avoiding long-lived C7/Win3 failures.

    Exploratory 384-job sessions ceased progressing after about 160 compiles.
    The reproducible default is 96 jobs per boot. Every job retains its receipt;
    a failed job is never counted or automatically accepted because OBJ exists.
    """
    jobs=list(jobs)
    if not 1<=session_limit<=128:raise FormatError('session_limit must be 1..128')
    results=[]
    for start in range(0,len(jobs),session_limit):
        results.extend(_compile_session(jobs[start:start+session_limit],compiler,timeout))
    return results


@contextmanager
def compiler_lock():
    """One historical worker at a time; OS releases the lock after host crashes."""
    (ROOT/'build').mkdir(exist_ok=True)
    with (ROOT/'build/compiler-worker.lock').open('a+b') as handle:
        handle.seek(0);handle.write(b'0');handle.flush();handle.seek(0)
        try:
            if os.name=='nt':
                import msvcrt
                msvcrt.locking(handle.fileno(),msvcrt.LK_NBLCK,1)
            else:
                import fcntl
                fcntl.flock(handle.fileno(),fcntl.LOCK_EX|fcntl.LOCK_NB)
        except OSError as exc:raise FormatError('Historical compiler worker is already active') from exc
        try:yield
        finally:
            handle.seek(0)
            if os.name=='nt':msvcrt.locking(handle.fileno(),msvcrt.LK_UNLCK,1)
            else:fcntl.flock(handle.fileno(),fcntl.LOCK_UN)


def persistent_enabled(compiler):
    profile=ROOT/'layout/compiler-service.json'
    return compiler=='msc700' and os.environ.get('SIMANT_COMPILER_REFERENCE')!='1' and profile.exists() and read_json(profile).get('enabled',False)


def compile_source(source,flags,compiler='msc600a'):
    if persistent_enabled(compiler):
        from compiler_service import compile_jobs
        obj,receipt=compile_jobs([dict(source=source,flags=flags)])[0]
        if obj is None or receipt['exit_code']:raise FormatError('compiler failed: '+receipt['stdout'])
        return obj,receipt
    with compiler_lock():return _compile_source(source,flags,compiler)


def compile_batch(jobs,compiler='msc700',timeout=None,session_limit=96):
    if persistent_enabled(compiler):
        from compiler_service import compile_jobs
        return compile_jobs(list(jobs))
    with compiler_lock():return _compile_batch(jobs,compiler,timeout,session_limit)
