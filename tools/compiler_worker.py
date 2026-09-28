"""One persistent Win3.1 C7 host. Construction mounts never include assets."""
import os,re,shutil,subprocess,tempfile,time
from pathlib import Path
from common import ROOT,FormatError,identity,read_json,write_json,sha256


def process_metrics(pid):
    """Read cumulative CPU, working set and process I/O counters on Windows."""
    if os.name!='nt':return None
    import ctypes
    from ctypes import wintypes
    class FILETIME(ctypes.Structure):_fields_=[('low',wintypes.DWORD),('high',wintypes.DWORD)]
    class IO_COUNTERS(ctypes.Structure):_fields_=[('read_operations',ctypes.c_ulonglong),('write_operations',ctypes.c_ulonglong),('other_operations',ctypes.c_ulonglong),('read_bytes',ctypes.c_ulonglong),('write_bytes',ctypes.c_ulonglong),('other_bytes',ctypes.c_ulonglong)]
    class PROCESS_MEMORY_COUNTERS(ctypes.Structure):_fields_=[('cb',wintypes.DWORD),('PageFaultCount',wintypes.DWORD),('PeakWorkingSetSize',ctypes.c_size_t),('WorkingSetSize',ctypes.c_size_t),('QuotaPeakPagedPoolUsage',ctypes.c_size_t),('QuotaPagedPoolUsage',ctypes.c_size_t),('QuotaPeakNonPagedPoolUsage',ctypes.c_size_t),('QuotaNonPagedPoolUsage',ctypes.c_size_t),('PagefileUsage',ctypes.c_size_t),('PeakPagefileUsage',ctypes.c_size_t)]
    kernel=ctypes.WinDLL('kernel32',use_last_error=True);psapi=ctypes.WinDLL('psapi',use_last_error=True)
    kernel.OpenProcess.argtypes=[wintypes.DWORD,wintypes.BOOL,wintypes.DWORD];kernel.OpenProcess.restype=wintypes.HANDLE
    kernel.GetProcessTimes.argtypes=[wintypes.HANDLE,ctypes.POINTER(FILETIME),ctypes.POINTER(FILETIME),ctypes.POINTER(FILETIME),ctypes.POINTER(FILETIME)];kernel.GetProcessTimes.restype=wintypes.BOOL
    kernel.GetProcessIoCounters.argtypes=[wintypes.HANDLE,ctypes.POINTER(IO_COUNTERS)];kernel.GetProcessIoCounters.restype=wintypes.BOOL
    kernel.CloseHandle.argtypes=[wintypes.HANDLE];kernel.CloseHandle.restype=wintypes.BOOL
    psapi.GetProcessMemoryInfo.argtypes=[wintypes.HANDLE,ctypes.POINTER(PROCESS_MEMORY_COUNTERS),wintypes.DWORD];psapi.GetProcessMemoryInfo.restype=wintypes.BOOL
    handle=kernel.OpenProcess(0x0400|0x0010,False,pid)
    if not handle:return None
    try:
        created=FILETIME();exited=FILETIME();kernel_time=FILETIME();user_time=FILETIME();io=IO_COUNTERS();memory=PROCESS_MEMORY_COUNTERS();memory.cb=ctypes.sizeof(memory)
        if not kernel.GetProcessTimes(handle,ctypes.byref(created),ctypes.byref(exited),ctypes.byref(kernel_time),ctypes.byref(user_time)):return None
        if not kernel.GetProcessIoCounters(handle,ctypes.byref(io)):return None
        if not psapi.GetProcessMemoryInfo(handle,ctypes.byref(memory),memory.cb):return None
        ticks=lambda value:(value.high<<32)|value.low
        return dict(cpu_seconds=(ticks(kernel_time)+ticks(user_time))/10_000_000,
                    working_set_bytes=memory.WorkingSetSize,peak_working_set_bytes=memory.PeakWorkingSetSize,
                    read_transfer_bytes=io.read_bytes,write_transfer_bytes=io.write_bytes,
                    read_operations=io.read_operations,write_operations=io.write_operations)
    finally:kernel.CloseHandle(handle)


def validate_flags(flags):
    if not flags or any(not isinstance(f,str) or not re.fullmatch(r'/[A-Za-z][A-Za-z0-9_:+-]*',f) for f in flags):raise FormatError('unsafe worker compiler flags')


def remove_tree(path):
    """Delete a host copy; its toolchain files keep their read-only attribute."""
    import stat
    def writable(function,target,_):
        os.chmod(target,stat.S_IWRITE);function(target)
    shutil.rmtree(path,onerror=writable) if Path(path).exists() else None


class Win31Worker:
    def __init__(self,worker_id=0,session_limit=96):
        self.worker_id=worker_id;self.session_limit=session_limit;self.count=0;self.process=None;self.boots=0;self.paused=False
    def pause(self):
        if self.process is None or self.paused:return
        if os.name=='nt':
            import ctypes
            fn=ctypes.WinDLL('ntdll').NtSuspendProcess;fn.argtypes=[ctypes.c_void_p];fn.restype=ctypes.c_long
            if fn(int(self.process._handle))!=0:raise FormatError('cannot suspend idle compiler process')
        else:
            import signal
            os.kill(self.process.pid,signal.SIGSTOP)
        self.paused=True
    def resume(self):
        if self.process is None or not self.paused:return
        if os.name=='nt':
            import ctypes
            fn=ctypes.WinDLL('ntdll').NtResumeProcess;fn.argtypes=[ctypes.c_void_p];fn.restype=ctypes.c_long
            if fn(int(self.process._handle))!=0:raise FormatError('cannot resume compiler process')
        else:
            import signal
            os.kill(self.process.pid,signal.SIGCONT)
        self.paused=False
    def start(self):
        self.close();start=time.perf_counter();base=ROOT/'build/compiler-workers';base.mkdir(parents=True,exist_ok=True)
        self.directory=Path(tempfile.mkdtemp(prefix='W%d_'%self.worker_id,dir=base));self.work=self.directory/'work';self.work.mkdir()
        shutil.copytree(ROOT/'toolchain/win31',self.directory/'host')
        subprocess.run(['nasm','-f','bin',str(ROOT/'tools/compiler_wait.asm'),'-o',str(self.work/'WAIT.COM')],check=True,capture_output=True)
        shutil.copyfile(ROOT/'toolchain/CAPCL.COM',self.work/'CAPCL.COM')
        for name in ['CONTROL.BIN','HOST.RDY','JOB.DON','JOB.BEG','JOB.RC','INPUT.C','OUTPUT.OBJ','OUTPUT.LOG','JOB.BAT']:(self.work/name).write_bytes(b'0' if name=='CONTROL.BIN' else b'')
        (self.work/'GO.BAT').write_text('@echo off\nset PATH=T:\\BIN;C:\\WINDOWS\nset TMP=W:\\\nset TEMP=W:\\\nW:\necho ready > HOST.RDY\n:again\nWAIT\nif errorlevel 2 goto end\ncall JOB.BAT\necho finished > JOB.DON\ngoto again\n:end\nexit\n')
        conf='[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=128\nmachine=svga_s3\n[cpu]\ncore=normal\ncputype=486\ncycles=200000\n[autoexec]\n'
        conf+=f'mount c "{self.directory/"host"}"\nmount t "{ROOT/"toolchain/msc700"}"\nmount w "{self.work}" -nocachedir\nc:\nset PATH=C:\\WINDOWS;T:\\BIN\nC:\\WINDOWS\\WIN /3 W:\\GO.BAT\nexit\n'
        (self.work/'RUN.CONF').write_text(conf)
        self.command=[str(ROOT/'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'),'-conf',str(self.work/'RUN.CONF'),'-fastlaunch','-nogui','-nomenu','-noconsole']
        env={k:v for k,v in os.environ.items() if k.upper() in ('SYSTEMROOT','WINDIR','COMSPEC')};env.update(SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
        self.process=subprocess.Popen(self.command,cwd=self.work,env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
        deadline=time.monotonic()+30
        while time.monotonic()<deadline:
            if (self.work/'HOST.RDY').read_bytes().strip()==b'ready':break
            if self.process.poll() is not None:raise FormatError('persistent historical host exited before readiness')
            time.sleep(.005)
        else:self.close();raise FormatError('historical host startup timeout')
        self.startup_seconds=time.perf_counter()-start;self.boots+=1;self.count=0;self.pause()
    def compile(self,source,flags,timeout=30):
        validate_flags(flags);start=time.perf_counter();boot=False
        if self.process is None or self.process.poll() is not None or self.count>=self.session_limit:self.start();boot=True
        snapshot=(ROOT/source).read_bytes();(self.work/'INPUT.C').write_bytes(snapshot)
        for name in ['OUTPUT.OBJ','OUTPUT.LOG','JOB.DON','JOB.BEG','JOB.RC']:(self.work/name).write_bytes(b'')
        line='CAPCL /c /FoOUTPUT.OBJ '+' '.join(flags)+' INPUT.C > OUTPUT.LOG'
        (self.work/'JOB.BAT').write_text('@echo off\necho started > JOB.BEG\n'+line+'\nif errorlevel 1 goto failed\necho 0 > JOB.RC\ngoto end\n:failed\necho 1 > JOB.RC\n:end\n')
        resource_before=process_metrics(self.process.pid)
        sent=time.perf_counter();(self.work/'CONTROL.BIN').write_bytes(b'1');self.resume();began=None;deadline=time.monotonic()+timeout
        while time.monotonic()<deadline:
            now=time.perf_counter()
            if began is None and (self.work/'JOB.BEG').read_bytes().strip()==b'started':began=now
            if (self.work/'JOB.DON').read_bytes().strip()==b'finished':break
            if self.process.poll() is not None:raise FormatError('persistent host exited during compilation')
            time.sleep(.002)
        else:self.close();raise FormatError('persistent compiler job timeout')
        ended=time.perf_counter();self.pause();resource_after=process_metrics(self.process.pid);self.count+=1
        # Job outputs outlive the session: receipts name these files, while the
        # Windows host copy in self.directory is removed when the session closes.
        archive=ROOT/'build/compiler-jobs'/self.directory.name/('job%04d'%self.count);archive.mkdir(parents=True)
        for name in ['INPUT.C','OUTPUT.OBJ','OUTPUT.LOG','JOB.BAT','JOB.RC']:shutil.copyfile(self.work/name,archive/name)
        obj=archive/'OUTPUT.OBJ';log=(archive/'OUTPUT.LOG').read_text(encoding='latin1')
        success=(archive/'JOB.RC').read_text().strip()=='0' and obj.stat().st_size>0
        resource_delta=None
        if resource_before and resource_after:
            resource_delta=dict(process_id=self.process.pid,cpu_seconds=max(0,resource_after['cpu_seconds']-resource_before['cpu_seconds']),
                                working_set_bytes=resource_after['working_set_bytes'],peak_working_set_bytes=max(resource_before['peak_working_set_bytes'],resource_after['peak_working_set_bytes']),
                                read_transfer_bytes=max(0,resource_after['read_transfer_bytes']-resource_before['read_transfer_bytes']),
                                write_transfer_bytes=max(0,resource_after['write_transfer_bytes']-resource_before['write_transfer_bytes']),
                                read_operations=max(0,resource_after['read_operations']-resource_before['read_operations']),
                                write_operations=max(0,resource_after['write_operations']-resource_before['write_operations']),
                                io_measurement='Windows process I/O transfer counters; logical bytes, not physical-device bytes')
        receipt=dict(source=source,source_identity=dict(size=len(snapshot),sha256=sha256(snapshot)),compiler='msc700',flags=flags,toolchain_lock_sha256=sha256((ROOT/'layout/toolchain.json').read_bytes()),command=self.command,compile_command=line,exit_code=0 if success else 1,stdout=log,stderr='',object=obj.relative_to(ROOT).as_posix(),object_identity=identity(obj),fixture_dependencies=[],unsupported_option=any(x in log.lower() for x in ['ignoring unknown flag','ignoring unknown option','invalid for 16-bit target']),worker_id=self.worker_id,worker_session=self.directory.relative_to(ROOT).as_posix(),batch_directory=self.directory.relative_to(ROOT).as_posix(),batch_index=self.count-1,worker_implementation={p:identity(ROOT/p) for p in ['tools/compiler_worker.py','tools/compiler_wait.asm']},configuration_identity=identity(self.work/'RUN.CONF'),wait_helper_identity=identity(self.work/'WAIT.COM'),resource_delta=resource_delta,timing=dict(runner_startup_seconds=self.startup_seconds if boot else 0,environment_launches=int(boot),queue_dispatch_seconds=(began or ended)-sent,compiler_execution_seconds=ended-began if began else None,total_compile_request_seconds=time.perf_counter()-start,measurement='Host monotonic observation of precreated DOS protocol files; 2ms sampling; CL time includes internal pass initialization'))
        write_json(archive/'receipt.json',receipt)
        return (obj if success else None),receipt
    def close(self):
        if self.process is not None:
            if self.process.poll() is None:self.process.kill()
            self.process.wait();self.process=None;self.paused=False
        # Each session copies the Windows host; never leave the copy behind
        # (hundreds of thousands of stale files slowed every workspace scan).
        if getattr(self,'directory',None) is not None:
            remove_tree(self.directory);self.directory=None
    def __enter__(self):return self
    def __exit__(self,*args):self.close()
