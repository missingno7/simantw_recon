"""Emulated search: compile drafts with tools/c2_emu.py under the symbol's profile and score them
exactly like codegen_grinder (score_object + codegen_diff.diagnose). Diagnostic only; admission
still goes through tools/search.py / promote.py (DOSBox)."""
import sys, json, tempfile, os
from pathlib import Path
ROOT = Path('D:/Prog/simantw_wt_c2')
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'build/workers/f-study-bm'))
import c2_emu
import bm_sweep

_FLAGS = {}


def flags_for(symbol):
    if symbol not in _FLAGS:
        from promote import function_flags
        _FLAGS[symbol] = function_flags(symbol)[1]
    return _FLAGS[symbol]


def compile_obj(src_bytes, symbol, c2_hooks=None):
    r = c2_emu.compile_c(src_bytes, flags_for(symbol), c2_hooks=c2_hooks)
    return r


def score_bytes(obj, symbol):
    fd, p = tempfile.mkstemp(suffix='.OBJ', dir=str(ROOT / 'build/workers/f-alloc-emu'))
    os.close(fd)
    try:
        Path(p).write_bytes(obj)
        r = bm_sweep.score(Path(p), symbol)
    finally:
        os.unlink(p)
    return r


def evaluate(src_bytes, symbol):
    r = compile_obj(src_bytes, symbol)
    if not r.obj:
        return dict(result='COMPILE_FAILED', messages=r.messages[:400])
    s = score_bytes(r.obj, symbol)
    out = bm_sweep.summary(s)
    out['strict'] = s.get('result')
    return out


def full(src_bytes, symbol):
    r = compile_obj(src_bytes, symbol)
    return score_bytes(r.obj, symbol) if r.obj else None


if __name__ == '__main__':
    sym = sys.argv[1]
    for f in sys.argv[2:]:
        print(f, json.dumps(evaluate(Path(f).read_bytes(), sym)))
