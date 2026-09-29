"""Capture C1 IL (and C2/C3 inputs) for one source under a chosen TMP dir (worker-local)."""
import sys, shutil, hashlib, json
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT)); sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(ROOT / 'build/workers/f-study-c2c'))
import memory_study as MS
W = ROOT / 'build/workers/f-study-bm/c1cap'
MS.WIN = ROOT / 'build/workers/f-study-bm/win31'
def cap(source, symbol, label, tmp, stage=2):
    from tools.c2_debug import wrapper_asm
    import subprocess
    case = W / label; 
    if case.exists(): shutil.rmtree(case)
    case.mkdir(parents=True)
    shutil.copyfile(ROOT / 'toolchain/CAPCL.COM', case / 'CAPCL.COM')
    if stage == 2:
        shutil.copyfile(ROOT / 'build/workers/f-study-c2b/c2-debug/CAPTURE.COM', case / 'CAPTURE.COM')
    else:
        (case / 'CAP3.ASM').write_text(wrapper_asm(3), encoding='ascii')
        subprocess.run(['nasm', '-f', 'bin', str(case / 'CAP3.ASM'), '-o', str(case / 'CAPTURE.COM')], check=True)
    shutil.copyfile(ROOT / source, case / 'INPUT.C')
    if tmp != '.': (case / tmp).mkdir(parents=True, exist_ok=True)
    B = chr(92); t = 'W:' + B + ('' if tmp == '.' else tmp.replace('/', B))
    flags = MS.assigned_flags(symbol)
    lines = ['@echo off', 'set PATH=T:' + B + 'BIN;C:' + B + 'WINDOWS', 'set TMP=' + t, 'set TEMP=' + t, 'W:',
             'CAPCL /c /FoOUT.OBJ ' + ' '.join(flags) + ' /B%dW:' % stage + B + 'CAPTURE.COM INPUT.C > CL.LOG',
             'echo finished > DONE.TXT', 'exit']
    (case / 'GO.BAT').write_text('\n'.join(lines) + '\n', encoding='ascii')
    MS.runner_environment(case, 128)
    print(MS.run_dos(case, 128))
    out = {p.name: hashlib.sha256(p.read_bytes()).hexdigest()[:12] + ':%d' % p.stat().st_size for p in sorted(case.rglob('*')) if p.is_file()}
    print(json.dumps(out, indent=0))
if __name__ == '__main__':
    cap(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], int(sys.argv[5]) if len(sys.argv) > 5 else 2)
