"""Sweep an unrelated environment variable's length (PAD=xxx) at fixed TMP."""
import os, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
ROOT = 'D:/Prog/simantw_wt_c2'
def run(n, jobs_file, prefix, layout):
    env = dict(os.environ, BM_LAYOUT=layout, BM_PRE=('set PAD=' + 'x' * n) if n else 'rem nopad')
    label = '%s_P%02d' % (prefix, n)
    r = subprocess.run([sys.executable, 'build/workers/f-study-bm/bm_sweep.py', '--jobs', jobs_file, '--label', label,
                        '--toolchain', 'toolchain/msc700', '--memsize', '128'], cwd=ROOT, env=env, capture_output=True, text=True)
    return label, r.returncode
if __name__ == '__main__':
    jobs_file, prefix, lo, hi, par, layout = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5]), sys.argv[6]
    with ThreadPoolExecutor(par) as ex:
        for label, rc in ex.map(lambda n: run(n, jobs_file, prefix, layout), range(lo, hi + 1)):
            print(label, rc, flush=True)
