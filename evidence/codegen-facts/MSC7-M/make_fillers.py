"""Build heap-history variants: unrelated filler functions compiled before (or after) a parked draft.

The fillers share no declarations with the draft, so any change in the draft's
own code can only come from C1/C2 state carried across functions (heap history,
symbol-table growth, pool reuse), not from source semantics.
"""
import json
from pathlib import Path

W = Path('D:/Prog/simantw_wt_c2/build/workers/f-study-bm')


def filler(k, big):
    if not big:
        return ('extern int far zzExt%d(int);\nint far zzFill%d(int a, int b)\n{\n  int i, s = 0;\n'
                '  for (i = 0; i < a; i++) s += zzExt%d(i + b);\n  return s;\n}\n' % (k, k, k))
    return ('extern int far zzExt%d(int, int);\nextern int zzTab%d[64];\n'
            'int far zzFill%d(int a, int b, int c)\n{\n  int i, j, s = 0, t = 1, u = 2, v = 3;\n'
            '  for (i = 0; i < a; i++) {\n    for (j = 0; j < b; j++) {\n'
            '      s += zzTab%d[(i * 8 + j) & 63] * t;\n      t = zzExt%d(s, u);\n      if (t > c) u += v; else v -= u;\n    }\n'
            '    zzTab%d[i & 63] = s + u + v;\n  }\n  return s + t + u + v;\n}\n' % (k, k, k, k, k, k))


def main():
    man = json.load(open(W / 'drafts/manifest.json'))
    (W / 'fill').mkdir(exist_ok=True)
    jobs = []
    variants = [('b', n, big) for n in (1, 2, 3, 5, 8, 13) for big in (False, True)] + [('a', 5, True)]
    for sym, v in man.items():
        for tag in ('frontier', 'best'):
            if tag not in v:
                continue
            draft = (W.parents[2] / v[tag]).read_text(encoding='latin1')
            for where, n, big in variants:
                fill = '\n'.join(filler(k, big) for k in range(n))
                text = (fill + '\n' + draft) if where == 'b' else (draft + '\n' + fill)
                name = '%s_%s_%s%d%s.c' % (sym.lstrip('_'), tag, where, n, 'B' if big else 's')
                (W / 'fill' / name).write_text(text, encoding='latin1')
                jobs.append(dict(symbol=sym, source='build/workers/f-study-bm/fill/' + name, extra=[],
                                 tag='%s:%s%d%s' % (tag, where, n, 'B' if big else 's')))
    json.dump(jobs, open(W / 'jobs_fill.json', 'w'))
    print(len(jobs))


if __name__ == '__main__':
    main()
