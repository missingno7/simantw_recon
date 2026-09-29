"""Capture CL's MSC_CMD_FLAGS for passes 1-3 under every catalogued profile (DOSBox, arg-dump wrappers)."""
import sys, shutil, subprocess, json, re
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT)); sys.path.insert(0, str(ROOT / 'tools'))
from tools import c2_debug as CD
W = ROOT / 'build/workers/f-alloc-emu/capflags'
CD.WIN = ROOT / 'build/workers/f-study-bm/win31'
base = (ROOT / 'build/workers/f-study-c2/capargs.asm').read_text(encoding='ascii')
begin = base.index('    ; This Win3.1 runner')
data = "finish:\n    mov ax, 4c00h\n    int 21h\nfilename db 'W:\\CAPARGS.TXT',0\n"
data += "tail_label db 'T:'\nenv_label db 13,10,'E:'\nenvbuf times 32768 db 0\nbuffer times 4096 db 0\n"
asm = base[:begin].replace('jc .exit', 'jc finish') + '    jmp finish\n' + data
prof = json.load(open(ROOT / 'layout/compiler-profiles.json'))
out = {}
for name, p in prof['profiles'].items():
    for stage in (1, 2, 3):
        case = W / ('%s_%d' % (name, stage))
        if case.exists():
            shutil.rmtree(case)
        case.mkdir(parents=True)
        (case / 'CAP.ASM').write_text(asm, encoding='ascii')
        subprocess.run(['nasm', '-f', 'bin', str(case / 'CAP.ASM'), '-o', str(case / 'CAPTURE.COM')], check=True)
        shutil.copyfile(ROOT / 'toolchain/CAPCL.COM', case / 'CAPCL.COM')
        (case / 'INPUT.C').write_text('int f(int a){return a+1;}\n')
        flags = prof['common_flags'] + p['flags'] + ['/NTSEG_X']
        lines = ['@echo off', 'set PATH=T:\\BIN;C:\\WINDOWS', 'set TMP=W:\\', 'set TEMP=W:\\', 'W:',
                 'CAPCL /c /FoOUT.OBJ ' + ' '.join(flags) + ' /B%dW:\\CAPTURE.COM INPUT.C > CL.LOG' % stage,
                 'echo finished > DONE.TXT', 'exit']
        (case / 'GO.BAT').write_text('\n'.join(lines) + '\n', encoding='ascii')
        CD.write_runner(case)
        r = CD.run_dos(case)
        raw = (case / 'CAPARGS.TXT').read_bytes() if (case / 'CAPARGS.TXT').exists() else b''
        m = re.search(rb'MSC_CMD_FLAGS=([^\x00]*)', raw)
        out['%s/%d' % (name, stage)] = m.group(1).decode('latin1') if m else None
        print(name, stage, r, out['%s/%d' % (name, stage)])
json.dump(out, open(W / 'flags.json', 'w'), indent=1)
