"""Sweep the TMP directory path length for all parked drafts (one DOSBox session per path)."""
import json, os, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
ROOT = 'D:/Prog/simantw_wt_c2'
def path_for(n):
    """A relative DOS path of exactly n characters (components of <=8 letters), '' for n==0."""
    if n == 0: return '.'
    comps = []; left = n; k = 0
    while left > 0:
        take = min(8, left) if left != 9 else 7  # avoid a trailing 0-length component
        comps.append(''.join(chr(65 + (k + j) % 26) for j in range(take))); k += 1
        left -= take
        if left > 0: left -= 1  # separator
    return '/'.join(comps)
def run(n, jobs_file, label_prefix, extra_env=None):
    p = path_for(n)
    env = dict(os.environ, BM_LAYOUT='custom:%s:%s' % (p, p))
    if extra_env: env.update(extra_env)
    label = '%s_L%02d' % (label_prefix, 3 + (0 if p == '.' else len(p)))
    r = subprocess.run([sys.executable, 'build/workers/f-study-bm/bm_sweep.py', '--jobs', jobs_file, '--label', label,
                        '--toolchain', 'toolchain/msc700', '--memsize', '128'], cwd=ROOT, env=env, capture_output=True, text=True)
    return label, r.returncode
if __name__ == '__main__':
    jobs_file, prefix, lo, hi, par = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5])
    with ThreadPoolExecutor(par) as ex:
        for label, rc in ex.map(lambda n: run(n, jobs_file, prefix), range(lo, hi + 1)):
            print(label, rc, flush=True)
