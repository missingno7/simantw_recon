"""Durable filesystem service for validated, isolated persistent C7 workers."""
import argparse,json,os,shutil,subprocess,sys,time,uuid
from contextlib import contextmanager
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from common import ROOT,FormatError,identity,read_json,write_json,sha256
from compiler_worker import Win31Worker,validate_flags

BASE=ROOT/'build/compiler-service'
IMPLEMENTATION=['tools/compiler_service.py','tools/compiler_worker.py','tools/compiler_wait.asm','layout/toolchain.json']
# A proof covers what produces the objects: the service, the host, the wait stub, the locked toolchain and the
# compiler oracle. Comparator/tooling modules are deliberately excluded, so an unrelated tool change cannot stop
# the shared service for the whole fleet.
PROOF_INPUTS=['tools/compiler_service.py','tools/compiler_worker.py','tools/compiler_wait.asm','layout/toolchain.json',
              'evidence/experiments/toolchain/msc700-baseline-Oelw.json']
SUPPORTED_WORKERS=(1,4,8,12,16)

def signature():return {p:identity(ROOT/p) for p in IMPLEMENTATION}
def current_proof_inputs():
    paths=list(PROOF_INPUTS);oracle_path=ROOT/'evidence/experiments/toolchain/msc700-baseline-Oelw.json'
    if not oracle_path.is_file():raise FormatError('canonical worker oracle is missing: evidence/experiments/toolchain/msc700-baseline-Oelw.json')
    oracle=read_json(oracle_path)
    virtual={}
    for row in oracle.get('results',[]):
        receipt=row.get('receipt',{})
        for key in ('source','object'):
            relative=receipt.get(key)
            if not relative:raise FormatError('canonical worker oracle has no '+key+' path')
            rel=Path(relative)
            if rel.is_absolute() or '..' in rel.parts:raise FormatError('canonical worker '+key+' path is not worktree-relative')
            path=(ROOT/rel).resolve()
            if not path.is_relative_to(ROOT.resolve()):raise FormatError('canonical worker '+key+' path leaves this worktree')
            if key=='source':
                if not path.is_file():raise FormatError('canonical worker source is missing: '+str(relative))
                actual=identity(path)
                if actual!=receipt.get('source_identity'):raise FormatError('canonical worker source identity disagrees with oracle: '+str(relative))
                paths.append(str(relative).replace('\\','/'))
            else:
                expected=receipt.get('object_identity')
                if (not isinstance(expected,dict) or not isinstance(expected.get('size'),int) or expected['size']<0 or
                    not isinstance(expected.get('sha256'),str) or len(expected['sha256'])!=64 or
                    any(char not in '0123456789abcdef' for char in expected['sha256'].lower())):
                    raise FormatError('canonical worker oracle has no valid object identity: '+str(relative))
                if path.is_file() and identity(path)!=expected:
                    raise FormatError('canonical worker OMF identity disagrees with oracle: '+str(relative))
                virtual['oracle-omf:'+str(relative).replace('\\','/')]=expected
    inputs={p:identity(ROOT/p) for p in dict.fromkeys(paths)}
    inputs.update(virtual)
    return inputs
def require_worker_proof(workers):
    if workers not in SUPPORTED_WORKERS:raise FormatError('workers must be one of '+', '.join(map(str,SUPPORTED_WORKERS)))
    path=ROOT/('evidence/experiments/runner/worker-%d.json'%workers)
    try:proof=read_json(path)
    except (FileNotFoundError,PermissionError,json.JSONDecodeError) as exc:raise FormatError('no valid canonical worker proof for %d workers'%workers) from exc
    if proof.get('workers')!=workers or not proof.get('passed'):raise FormatError('canonical worker proof does not pass for exactly %d workers'%workers)
    if proof.get('inputs')!=current_proof_inputs():raise FormatError('canonical worker proof inputs are stale for %d workers'%workers)
    return proof

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

def prune_transient(now=None,max_age_seconds=86400):
    """Prune terminal transport records after a day; compile objects/cache stay untouched."""
    now=time.time() if now is None else now;cutoff=now-max_age_seconds;removed=dict(completed=0,jobs=0)
    completed=BASE/'completed'
    if completed.exists():
        for path in completed.glob('*.json'):
            try:
                if path.stat().st_mtime<cutoff:path.unlink();removed['completed']+=1
            except (FileNotFoundError,PermissionError,OSError):pass
    jobs=BASE/'jobs'
    if jobs.exists():
        for folder in jobs.iterdir():
            if not folder.is_dir() or not any((folder/name).exists() for name in ('request-completed.json','rejected.json','interrupted.json')):continue
            try:
                if folder.stat().st_mtime<cutoff:shutil.rmtree(folder);removed['jobs']+=1
            except (FileNotFoundError,PermissionError,OSError):pass
    return removed

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
    if workers not in SUPPORTED_WORKERS:raise FormatError('workers must be one of '+', '.join(map(str,SUPPORTED_WORKERS)))
    with service_lock():
        from compiler import verify_lock
        verify_lock(read_json(ROOT/'layout/toolchain.json'))
        proof=require_worker_proof(workers)
        for name in ['pending','running','completed','jobs']:(BASE/name).mkdir(exist_ok=True)
        prune_transient()
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
                        completed_at=time.time()
                        try:
                            obj,receipt=future.result();receipt.update(source=job['source'],source_snapshot=job['snapshot'],request_id=job['id'],service_instance=info['instance'])
                            receipt['service_timing']=dict(queue_seconds=max(0,job['dispatched_at']-job['submitted_at']),end_to_end_seconds=max(0,completed_at-job['submitted_at']))
                            atomic(BASE/'completed'/path.name,dict(object=obj.relative_to(ROOT).as_posix() if obj else None,receipt=receipt))
                        except Exception as exc:atomic(BASE/'completed'/path.name,dict(error=str(exc),request_id=job['id'],service_instance=info['instance'],submitted_at=job['submitted_at'],completed_at=completed_at))
                        path.rename(BASE/'jobs'/job['id']/'request-completed.json');busy.pop(future);last_active=time.monotonic()
                    if stop.exists() and not busy:break
                    available=[i for i in range(workers) if i not in [row[0] for row in busy.values()]]
                    if not stop.exists():
                        for index,path in zip(available,sorted((BASE/'pending').glob('*.json'))):
                            job=read_json(path)
                            if job['implementation']!=info['implementation']:
                                atomic(BASE/'completed'/path.name,dict(error='Service code/tool identity changed',request_id=job['id']));path.rename(BASE/'jobs'/job['id']/'rejected.json');continue
                            if identity(ROOT/job['snapshot'])!=job['source_identity']:raise FormatError('changed queued source snapshot')
                            target=BASE/'running'/path.name;path.rename(target)
                            job['dispatched_at']=time.time()
                            busy[pool.submit(hosts[index].compile,job['snapshot'],job['flags'])]=(index,target,job);last_active=time.monotonic()
                    if not busy and time.monotonic()-last_active>idle_seconds:break
                    time.sleep(.005)
        finally:
            for host in hosts:host.close()
            atomic(BASE/'status.json',dict(info,status='STOPPED',heartbeat=time.time()))


def configured_workers():
    """Host count for auto-started services: layout/compiler-service.json 'workers' (proof-gated in serve)."""
    try:return int(read_json(ROOT/'layout/compiler-service.json').get('workers',4))
    except (FileNotFoundError,ValueError,TypeError,json.JSONDecodeError):return 4


def start(workers=None):
    workers=configured_workers() if workers is None else workers
    require_worker_proof(workers)
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


def compile_jobs(jobs,workers=None):
    if not jobs:return []
    info=start(workers);requests=[];batch=uuid.uuid4().hex
    for row in jobs:
        validate_flags(row['flags']);source=(ROOT/row['source']).resolve()
        if not source.is_relative_to(ROOT):raise FormatError('worker source must be inside repository')
        key=uuid.uuid4().hex;folder=BASE/'jobs'/key;folder.mkdir();snapshot=folder/'INPUT.C';shutil.copyfile(source,snapshot)
        job=dict(id=key,source=source.relative_to(ROOT).as_posix(),snapshot=snapshot.relative_to(ROOT).as_posix(),source_identity=identity(snapshot),flags=row['flags'],implementation=info['implementation'],submitted_at=time.time())
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
