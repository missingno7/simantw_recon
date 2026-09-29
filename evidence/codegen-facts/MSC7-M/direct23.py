"""Direct C2 -> C3 replay of one captured C1 IL set with a chosen -il directory.

Question: is the TMP-path sensitivity in C2/C3 (given byte-identical C1 IL)?
The IL files (IL_*.BAK from c1cap.py) are copied to W:\\<dir>\\185436xx and
C23216 then C33216 run with -il "W:\\<dir>\\185436".
"""
import hashlib, json, shutil, sys
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT)); sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(ROOT / 'build/workers/f-study-c2c'))
import memory_study as MS
MS.WIN = ROOT / 'build/workers/f-study-bm/win31'
B = chr(92)
W = ROOT / 'build/workers/f-study-bm/direct23'


def run(capdir, label, sub, nt, c2flags_extra=''):
    capdir = Path(capdir)
    case = W / label
    if case.exists():
        shutil.rmtree(case)
    case.mkdir(parents=True)
    d = case if sub == '.' else case / sub
    d.mkdir(parents=True, exist_ok=True)
    for s in ('EX', 'GL', 'IN', 'ST', 'SY'):
        shutil.copyfile(capdir / ('IL_%s.BAK' % s), d / ('185436' + s))
    shutil.copyfile(ROOT / 'toolchain/msc700/BIN/C23.ERR', case / 'C23.ERR')
    il = 'W:' + B + ('' if sub == '.' else sub.replace('/', B) + B) + '185436'
    c2 = ('-ef "W:%sC23.ERR" -il "%s" -A lfd -Bm 2048 -Oc -Oe -Og -Ol -On -Ot -Ow -G2 -NT "%s" -W 1 %s'
          % (B, il, nt, c2flags_extra)).strip()
    c3 = ('-T 0 -ef "W:%sC23.ERR" -il "%s" -lib "OLDNAMES.LIB" -A lfd -Ot -NM "input" -NT "%s" -W 1 -dos -FPi '
          '-c "W:%sOUT.OBJ" -CC 2LO -v "7.00"' % (B, il, nt, B))
    lines = ['@echo off', 'set PATH=T:' + B + 'BIN;C:' + B + 'WINDOWS', 'set NO87=', 'W:',
             'set MSC_CMD_FLAGS=' + c2, 'T:' + B + 'BIN' + B + 'C23216.EXE > C2.LOG',
             'if errorlevel 1 echo C2FAIL > C2.RC',
             'set MSC_CMD_FLAGS=' + c3, 'T:' + B + 'BIN' + B + 'C33216.EXE  > C3.LOG',
             'if errorlevel 1 echo C3FAIL > C3.RC',
             'echo finished > DONE.TXT', 'exit']
    (case / 'GO.BAT').write_text('\n'.join(lines) + '\n', encoding='ascii')
    MS.runner_environment(case, 128)
    res = MS.run_dos(case, 128)
    out = {}
    for p in sorted(d.iterdir()):
        if p.name.startswith('185436') and p.name[-2:] in ('GS', 'LS', 'PR'):
            out[p.name[-2:]] = hashlib.sha256(p.read_bytes()).hexdigest()[:12] + ':%d' % p.stat().st_size
    obj = case / 'OUT.OBJ'
    if obj.exists():
        sys.path.insert(0, str(ROOT / 'build/workers/f-study-bm'))
        import bm_sweep
        out['OBJ_code'] = bm_sweep.code_hash(obj)[:12]
    out['logs'] = {n: (case / n).read_text(errors='replace') for n in ('C2.LOG', 'C3.LOG', 'C2.RC', 'C3.RC') if (case / n).exists()}
    print(label, res, json.dumps(out))
    return out


if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
