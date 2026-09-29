"""Worker-local end-to-end CL sweep of MSC 7.00 memory settings (f-study-bm).

Compiles (source, symbol) pairs through the authentic CL -> C1 -> C2 -> C3
route with the symbol's catalogued profile plus one extra memory setting
(/Bm<N>, which CL forwards to C23216 as `-Bm N`: a KB cap on C2's pool heap)
and scores every object exactly as tools/codegen_grinder.run does
(score_object + codegen_diff.diagnose).

Uses the reference DOSBox-X batch runner (not the persistent service) so the
DOSBox memsize can also be varied. Everything lives under this worker dir.
"""
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
WORK = ROOT / 'build/workers/f-study-bm'

import compiler  # noqa: E402
from common import fixture, identity, FormatError  # noqa: E402
from codegen_grinder import score_object, GOOD  # noqa: E402
from library_match import import_symbols  # noqa: E402
import ne, mapsym, omf  # noqa: E402

_CTX = {}


def ctx():
    if not _CTX:
        raw = fixture('SIMANTW.EXE')
        _CTX.update(raw=raw, n=ne.parse(raw), s=mapsym.parse(fixture('SIMANTW.SYM')),
                    imports=import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB'))
    return _CTX


def score(obj: Path, symbol: str) -> dict:
    c = ctx()
    module = omf.parse(obj.read_bytes())
    try:
        r = score_object(module, c['raw'], c['n'], c['s'], c['imports'], symbol)
    except FormatError as e:
        r = dict(result='UNSUPPORTED_COMPARISON', issues=[str(e)])
    from codegen_diff import diagnose
    try:
        r['diagnostic'] = diagnose(module, c['raw'], c['n'], c['s'], symbol, r)
    except Exception as e:  # diagnostic only
        r['diagnostic'] = {'error': str(e)}
    return r


def code_hash(obj: Path) -> str:
    """Identity of generated code/data/fixups, ignoring THEADR/source-name records."""
    import hashlib
    m = omf.parse(obj.read_bytes())
    key = json.dumps(dict(segments=[(s['name'], s['length'], s['data_hex']) for s in m['segments']],
                          fixups=m['fixups'], externals=m['externals'], publics=m['publics']), sort_keys=True)
    return hashlib.sha256(key.encode()).hexdigest()


def func_hash(obj: Path, symbol: str) -> str:
    """Hash of one public's code extent (bytes up to the next public) plus its fixups."""
    import hashlib
    m = omf.parse(obj.read_bytes())
    pub = next(p for p in m['publics'] if p['name'] == symbol)
    seg = m['segments'][pub['segment'] - 1]
    code = bytes.fromhex(seg['data_hex'])
    stop = min([p['offset'] for p in m['publics'] if p['segment'] == pub['segment'] and p['offset'] > pub['offset']] + [len(code)])
    body = bytearray(code[pub['offset']:stop]); fx = []
    for f in m['fixups']:
        if f['segment'] == pub['segment'] and pub['offset'] <= f['offset'] < stop:
            o = f['offset'] - pub['offset']
            for q in range(o, min(o + (f.get('width') or 2), len(body))):
                body[q] = 0  # mask relocated bytes; identity kept via normalized fixup below
            t = f.get('target') or {}
            fx.append((o, f.get('location_type'), f.get('self_relative'), t.get('kind'), t.get('name'), f.get('displacement')))
    key = bytes(body).hex() + json.dumps(fx)
    return hashlib.sha256(key.encode()).hexdigest()


def summary(r: dict) -> dict:
    d = r.get('diagnostic') or {}
    from tu_assembly import body_exact
    try:
        be = body_exact(r) if d and 'error' not in d else False
    except Exception:
        be = None
    return dict(result=r.get('result'), exact_body=be,
                opcodes=f"{d.get('opcode_matches')}/{d.get('opcode_total')}",
                bytes=f"{d.get('candidate_bytes')}/{d.get('target_bytes')}",
                literal=f"{r.get('literal_equal')}/{r.get('literal_compared')}",
                fixups=f"{r.get('fixups_equal')}/{r.get('fixups_total')}",
                reg=d.get('register_only_differences'), stack=d.get('stack_local_differences'),
                mem=d.get('memory_operand_differences'),
                first=d.get('first_structural_difference'),
                frame=(r.get('features') or {}).get('frame'))


def session(jobs, toolchain, memsize, timeout=None, pre=(), layout=None):
    """One Win3.1/DOSBox-X session like compiler._compile_session, but with a
    selectable toolchain root (mounted read-only as T:, BIN under it) and memsize.
    Scratch only: no toolchain lock (the patched C7PATB copy is not locked)."""
    import os, shutil, subprocess, tempfile, time
    (WORK / 'sessions').mkdir(exist_ok=True)
    directory = Path(tempfile.mkdtemp(prefix='Q', dir=WORK / 'sessions'))
    shutil.copyfile(ROOT / 'toolchain/CAPCL.COM', directory / 'CAPCL.COM')
    B = chr(92)
    import os as _os0
    if not pre and _os0.environ.get('BM_PRE'):
        pre = _os0.environ['BM_PRE'].split('|')
    lines = ['@echo off', 'set PATH=T:' + B + 'BIN;C:' + B + 'WINDOWS', 'W:', 'set TMP=W:' + B, 'set TEMP=W:' + B] + list(pre)
    import os as _os
    layout = layout or _os.environ.get('BM_LAYOUT', 'flat')
    jdirs = []
    for i, job in enumerate(jobs):
        stem = job.get('stem') or 'J%04d' % i
        sub = ''
        if layout == 'batchdir':  # mimic compiler._compile_session: W:\B0000\J0000.C, TMP there
            sub = 'B%04d' % (i // 64)
            (directory / sub).mkdir(exist_ok=True)
            if i % 64 == 0:
                lines += ['cd W:' + B + sub, 'set TMP=W:' + B + sub, 'set TEMP=W:' + B + sub]
        elif layout.startswith('custom:'):  # custom:CWD:TMP  (relative dirs under W:, '.' = root)
            _c, cwd, tmp = layout.split(':')
            sub = '' if cwd == '.' else cwd
            if sub:
                (directory / sub).mkdir(parents=True, exist_ok=True)
            if tmp != '.':
                (directory / tmp).mkdir(parents=True, exist_ok=True)
            if i == 0:
                lines += ['cd W:' + B + (sub.replace('/', B) if sub else ''),
                          'set TMP=W:' + B + ('' if tmp == '.' else tmp.replace('/', B)),
                          'set TEMP=W:' + B + ('' if tmp == '.' else tmp.replace('/', B))]
        jd = directory / sub if sub else directory
        jdirs.append(jd)
        shutil.copyfile(ROOT / job['source'], jd / (stem + '.C'))
        lines += ['W:' + B + 'CAPCL /c /Fo' + stem + '.OBJ ' + ' '.join(job['flags']) + ' ' + stem + '.C > ' + stem + '.LOG',
                  'if errorlevel 1 echo FAILED > ' + stem + '.ERR', 'echo done > ' + stem + '.END']
    lines += ['echo finished > W:' + B + 'DONE.TXT', 'exit']
    (directory / 'GO.BAT').write_text('\n'.join(lines) + '\n')
    if not (WORK / 'win31').exists():
        shutil.copytree(ROOT / 'toolchain/win31', WORK / 'win31')
    conf = ('[sdl]\noutput=surface\nshowmenu=false\n[mixer]\nnosound=true\n[dosbox]\nmemsize=%d\nmachine=svga_s3\n'
            '[cpu]\ncore=normal\ncputype=486\ncycles=200000\n[autoexec]\n' % memsize)
    conf += ('mount c "%s"\nmount t "%s" -ro\nmount w "%s"\nc:\nset PATH=C:%sWINDOWS;T:%sBIN\nC:%sWINDOWS%sWIN /3 W:%sGO.BAT\nexit\n'
             % (WORK / 'win31', (ROOT / toolchain).resolve(), directory, B, B, B, B, B))
    (directory / 'RUN.CONF').write_text(conf)
    runner = ROOT / 'toolchain/dosbox-x/bin/x64/Release/dosbox-x.exe'
    env = {k: v for k, v in os.environ.items() if k.upper() in ('SYSTEMROOT', 'WINDIR', 'COMSPEC')}
    env.update(SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy')
    proc = subprocess.Popen([str(runner), '-conf', str(directory / 'RUN.CONF'), '-fastlaunch', '-nogui', '-nomenu', '-noconsole'],
                            cwd=directory, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    try:
        deadline = time.monotonic() + (timeout or 60 + len(jobs) * 6)
        while time.monotonic() < deadline and proc.poll() is None and not (directory / 'DONE.TXT').exists():
            time.sleep(.1)
    finally:
        if proc.poll() is None:
            proc.kill()
        proc.wait()
    out = []
    for i, job in enumerate(jobs):
        stem = job.get('stem') or 'J%04d' % i
        jd = jdirs[i]
        obj = jd / (stem + '.OBJ'); log = jd / (stem + '.LOG')
        err = jd / (stem + '.ERR')
        ok = (jd / (stem + '.END')).exists() and not (err.exists() and err.stat().st_size > 0) and obj.exists()
        receipt = dict(source=job['source'], flags=job['flags'], exit_code=0 if ok else 1,
                       stdout=log.read_text(encoding='latin1') if log.exists() else 'No compiler log',
                       batch_directory=str(directory.relative_to(ROOT)), toolchain=toolchain, memsize=memsize)
        out.append((obj if ok else None, receipt))
    return out


def run(jobs: list[dict], label: str, memsize: int | None = None, session_limit: int = 96,
        toolchain: str | None = None) -> list[dict]:
    """jobs: dicts with symbol, source (ROOT-relative), extra (list of flags), tag."""
    from promote import function_flags
    cjobs = []
    for j in jobs:
        if j.get('flags'):
            flags = j['flags']
        else:
            _p, flags = function_flags(j['symbol'])
        cjobs.append(dict(source=j['source'], flags=list(flags) + list(j.get('extra', []))))
    if memsize is None and toolchain is None:
        with compiler.compiler_lock():
            results = compiler._compile_batch(cjobs, 'msc700', None, session_limit)
    else:
        results = []
        for k in range(0, len(cjobs), session_limit):
            results.extend(session(cjobs[k:k + session_limit], toolchain or 'toolchain/msc700', memsize or 128))
    rows = []
    for j, (obj, receipt) in zip(jobs, results):
        row = dict(j, flags=receipt['flags'], exit_code=receipt['exit_code'],
                   log=receipt['stdout'][-600:], batch=receipt['batch_directory'])
        if obj is not None:
            row['object_sha256'] = identity(obj)['sha256']
            row['code_sha256'] = code_hash(obj)
            try:
                row['func_sha256'] = func_hash(obj, j['symbol'])
            except Exception as e:
                row['func_sha256'] = 'ERR:' + str(e)
            row['object'] = str(obj.relative_to(ROOT))
            r = score(obj, j['symbol'])
            row['exact'] = r.get('result') in GOOD
            row['summary'] = summary(r)
            if j.get('members'):
                me = {}
                for mem in j['members']:
                    if mem == j['symbol']:
                        continue
                    try:
                        rm = score(obj, mem)
                        me[mem] = (rm.get('result'), (rm.get('diagnostic') or {}).get('opcode_matches'))
                    except Exception as e:
                        me[mem] = ('ERR', str(e)[:80])
                row['members'] = me
                row['members_all_good'] = all(v[0] in GOOD for v in me.values())
        rows.append(row)
    out = WORK / 'results' / f'{label}.json'
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(rows, indent=1), encoding='utf-8')
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--jobs', required=True, help='JSON list of jobs')
    ap.add_argument('--label', required=True)
    ap.add_argument('--memsize', type=int)
    ap.add_argument('--toolchain', help='ROOT-relative toolchain root containing BIN (scratch session runner)')
    ap.add_argument('--session-limit', type=int, default=96)
    a = ap.parse_args()
    rows = run(json.loads(Path(a.jobs).read_text()), a.label, a.memsize, a.session_limit, a.toolchain)
    for r in rows:
        s = r.get('summary') or {}
        print(r['symbol'], r.get('tag'), ' '.join(r.get('extra', [])), r['exit_code'],
              (r.get('func_sha256') or '')[:10], s.get('result'), s.get('opcodes'), s.get('bytes'),
              s.get('fixups'), s.get('frame'), 'C47' if 'C47' in r['log'] else '')


if __name__ == '__main__':
    main()
