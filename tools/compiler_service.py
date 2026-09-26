"""Durable filesystem service for validated, isolated persistent C7 workers."""
import argparse,json,os,shutil,subprocess,sys,time,uuid
from contextlib import contextmanager
from concurrent.futures import ThreadPoolExecutor
from common import ROOT,FormatError,identity,read_json,write_json,sha256
from compiler_worker import Win31Worker,validate_flags

BASE=ROOT/'build/compiler-service'
IMPLEMENTATION=['tools/compiler_service.py','tools/compiler_worker.py','tools/compiler_wait.asm','layout/toolchain.json']

def signature():return {p:identity(ROOT/p) for p in IMPLEMENTATION}
def atomic(path,value):
    path.parent.mkdir(parents=True,exist_ok=True);tmp=path.with_suffix('.tmp');tmp.write_text(json.dumps(value,indent=2)+'\n')
    deadline=time.monotonic()+2
    while True:
        try:tmp.replace(path);return
        except PermissionError:
            if time.monotonic()>=deadline:raise
            time.sleep(.005)
def state():
    try:return read_json(BASE/'status.json')
    except (FileNotFoundError,PermissionError,json.JSONDecodeError):return {}
def live(info):return info.get('status')=='RUNNING' and time.time()-info.get('heartbeat',0)<5

@contextmanager
def service_lock():
    BASE.mkdir(parents=True,exist_ok=True)
    with (BASE/'service.lock').open('a+b') as handle:
        handle.seek(0);handle.write(b'0');handle.flush();handle.seek(0)
        if os.name=='nt':
            import msvcrt
            try:msvcrt.locking(handle.fileno(),msvcrt.LK_NBLCK,1)
            except OSError as e:raise FormatError('compiler service already running') from e
        else:
            import fcntl
            fcntl.flock(handle.fileno(),fcntl.LOCK_EX|fcntl.LOCK_NB)
        try:yield
        finally:
            handle.seek(0)
            if os.name=='nt':msvcrt.locking(handle.fileno(),msvcrt.LK_UNLCK,1)
            else:fcntl.flock(handle.fileno(),fcntl.LOCK_UN)


def serve(workers=4,idle_seconds=120):
    if not 1<=workers<=4:raise FormatError('workers must be 1..4')
    with service_lock():
        from compiler import verify_lock
        verify_lock(read_json(ROOT/'layout/toolchain.json'))
        proof=read_json(ROOT/('evidence/experiments/runner/worker-%d.json'%(1 if workers==1 else 4)))
        if not proof['passed'] or any(identity(ROOT/p)!=h for p,h in proof['inputs'].items()):raise FormatError('worker implementation has not passed canonical oracle')
        for name in ['pending','running','completed','jobs']:(BASE/name).mkdir(exist_ok=True)
        # Under the service lock no host copy is live: remove orphans of crashed sessions.
        from compiler_worker import remove_tree
        for orphan in (ROOT/'build/compiler-workers').glob('W*_*') if (ROOT/'build/compiler-workers').exists() else []:
            try:remove_tree(orphan)
            except OSError:pass
        for p in (BASE/'running').glob('*.json'):
            atomic(BASE/'completed'/p.name,dict(error='Service interrupted this job; output is not accepted'))
            p.rename((BASE/'jobs'/p.stem/'interrupted.json'))
        stop=BASE/'STOP';stop.unlink(missing_ok=True)
        info=dict(status='RUNNING',pid=os.getpid(),workers=workers,implementation=signature(),instance=uuid.uuid4().hex)
        hosts=[Win31Worker(i) for i in range(workers)];busy={};last_active=time.monotonic();started=time.time();last_heartbeat=0
        try:
            with ThreadPoolExecutor(max_workers=workers) as pool:
                while True:
                    now=time.time()
                    if now-last_heartbeat>.25:
                        atomic(BASE/'status.json',dict(info,heartbeat=now,started=started,active_jobs=len(busy)));last_heartbeat=now
                    for future,(index,path,job) in list(busy.items()):
                        if not future.done():continue
                        try:
                            obj,receipt=future.result();receipt.update(source=job['source'],source_snapshot=job['snapshot'],request_id=job['id'],service_instance=info['instance'])
                            atomic(BASE/'completed'/path.name,dict(object=obj.relative_to(ROOT).as_posix() if obj else None,receipt=receipt))
                        except Exception as exc:atomic(BASE/'completed'/path.name,dict(error=str(exc)))
                        path.rename(BASE/'jobs'/job['id']/'request-completed.json');busy.pop(future);last_active=time.monotonic()
                    if stop.exists() and not busy:break
                    available=[i for i in range(workers) if i not in [row[0] for row in busy.values()]]
                    if not stop.exists():
                        for index,path in zip(available,sorted((BASE/'pending').glob('*.json'))):
                            job=read_json(path)
                            if job['implementation']!=info['implementation']:
                                atomic(BASE/'completed'/path.name,dict(error='Service code/tool identity changed'));path.rename(BASE/'jobs'/job['id']/'rejected.json');continue
                            if identity(ROOT/job['snapshot'])!=job['source_identity']:raise FormatError('changed queued source snapshot')
                            target=BASE/'running'/path.name;path.rename(target)
                            busy[pool.submit(hosts[index].compile,job['snapshot'],job['flags'])]=(index,target,job);last_active=time.monotonic()
                    if not busy and time.monotonic()-last_active>idle_seconds:break
                    time.sleep(.005)
        finally:
            for host in hosts:host.close()
            atomic(BASE/'status.json',dict(info,status='STOPPED',heartbeat=time.time()))


def start(workers=4):
    info=state()
    if live(info):
        if info['implementation']!=signature():raise FormatError('compiler service implementation changed; stop it before restarting')
        return info
    BASE.mkdir(parents=True,exist_ok=True)
    with (BASE/'service.log').open('ab') as log:
        subprocess.Popen([sys.executable,str(ROOT/'tools/compiler_service.py'),'serve','--workers',str(workers)],cwd=ROOT,stdout=log,stderr=log,creationflags=subprocess.CREATE_NO_WINDOW if os.name=='nt' else 0)
    deadline=time.monotonic()+15
    while time.monotonic()<deadline:
        info=state()
        if live(info):return info
        time.sleep(.05)
    raise FormatError('compiler service startup failed; inspect build/compiler-service/service.log')


def compile_jobs(jobs,workers=4):
    if not jobs:return []
    info=start(workers);requests=[];batch=uuid.uuid4().hex
    for row in jobs:
        validate_flags(row['flags']);source=(ROOT/row['source']).resolve()
        if not source.is_relative_to(ROOT):raise FormatError('worker source must be inside repository')
        key=uuid.uuid4().hex;folder=BASE/'jobs'/key;folder.mkdir();snapshot=folder/'INPUT.C';shutil.copyfile(source,snapshot)
        job=dict(id=key,source=source.relative_to(ROOT).as_posix(),snapshot=snapshot.relative_to(ROOT).as_posix(),source_identity=identity(snapshot),flags=row['flags'],implementation=info['implementation'])
        atomic(BASE/'pending'/(key+'.json'),job);requests.append(key)
    atomic(BASE/'requests'/(batch+'.json'),dict(id=batch,requests=requests,implementation=info['implementation'],created=time.time()))
    deadline=time.monotonic()+45+len(jobs)*3;results={};last_live=time.monotonic()
    while len(results)<len(requests) and time.monotonic()<deadline:
        for key in requests:
            if key in results:continue
            path=BASE/'completed'/(key+'.json')
            if path.exists():
                try:results[key]=read_json(path)
                except (PermissionError,FileNotFoundError):pass
        if len(results)==len(requests):break
        current=state()
        if live(current):last_live=time.monotonic()
        elif current.get('status')=='STOPPED' or time.monotonic()-last_live>5:raise FormatError('compiler service stopped; queued evidence retained in request batch '+batch)
        time.sleep(.005)
    if len(results)!=len(requests):raise FormatError('compiler service request timeout; inspect pending/running/completed')
    output=[]
    for key in requests:
        result=results[key]
        if 'error' in result:raise FormatError(result['error'])
        output.append((ROOT/result['object'] if result['object'] else None,result['receipt']))
    return output


def main():
    ap=argparse.ArgumentParser();ap.add_argument('action',choices=['start','serve','status','stop']);ap.add_argument('--workers',type=int,default=4)
    ap.add_argument('--idle-seconds',type=int,default=120,help='serve: stop after this long without work (a supervisor-owned service may use a long value)');args=ap.parse_args()
    if args.action=='serve':serve(args.workers,args.idle_seconds)
    elif args.action=='start':print(json.dumps(start(args.workers),indent=2))
    elif args.action=='stop':
        BASE.mkdir(parents=True,exist_ok=True);(BASE/'STOP').write_text('stop');print('Stop requested; active jobs finish before shutdown.')
    else:print(json.dumps(state(),indent=2))

if __name__=='__main__':main()
