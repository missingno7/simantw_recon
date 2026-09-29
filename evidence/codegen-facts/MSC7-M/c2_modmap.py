"""Assign C23216 functions to internal source modules (worker-local, heuristic).

Initialized data of each MSC7 C2 module sits after its '@(#)module.c:ver' SCCS
string, in link order. A function is attributed to the module owning most of the
initialized-data addresses it references. Output: c2_function_modules.json.
"""
import sys, pickle, re, json, bisect, collections
sys.path.insert(0, 'build/workers/f-study-bm')
ins = pickle.load(open('build/workers/f-study-bm/c2ins.pkl', 'rb'))
sccs = json.load(open('build/workers/f-study-bm/c2_sccs_modules.json'))
starts = [int(r[1], 16) for r in sccs]; names = [r[2] for r in sccs]
END = 0x483000
def module_of(va):
    if not (starts[0] <= va < END): return None
    return names[bisect.bisect_right(starts, va) - 1]
targets = sorted({int(i[2], 16) for i in ins if i[1] == 'call' and re.fullmatch(r'0x[0-9a-f]+', i[2])})
addrs = [i[0] for i in ins]
funcs = {}
for n, t in enumerate(targets):
    a = bisect.bisect_left(addrs, t)
    stop = targets[n + 1] if n + 1 < len(targets) else 1 << 40
    votes = collections.Counter()
    k = a
    while k < len(ins) and ins[k][0] < stop:
        for m in re.finditer(r'0x4[78][0-9a-f]{4}\b', ins[k][2]):
            mod = module_of(int(m.group(), 16))
            if mod: votes[mod] += 1
        k += 1
    funcs[hex(t)] = dict(size=(min(stop, ins[k - 1][0]) - t), module=votes.most_common(1)[0][0] if votes else None,
                         votes=dict(votes.most_common(3)))
json.dump(funcs, open('build/workers/f-study-bm/c2_function_modules.json', 'w'), indent=0)
by = collections.defaultdict(list)
for f, v in funcs.items():
    if v['module']: by[v['module']].append(int(f, 16))
for mod in names:
    v = by.get(mod)
    if v: print(f'{mod:14s} {len(v):4d} funcs  {hex(min(v))}-{hex(max(v))}  median {hex(sorted(v)[len(v)//2])}')
print('unattributed', sum(1 for v in funcs.values() if not v['module']), 'of', len(funcs))
