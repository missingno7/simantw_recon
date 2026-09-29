import json,glob,collections,sys,re
prefix=sys.argv[1] if len(sys.argv)>1 else 'tmp'
files=sorted(glob.glob(f'{prefix}_L*.json'))
tab=collections.OrderedDict(); ex=[]
for f in files:
    L=int(re.search(r'_L(\d+)',f).group(1))
    for r in json.load(open(f)):
        k=(r['symbol'],r['tag'])
        s=r.get('summary') or {}
        tab.setdefault(k,{})[L]=((r.get('code_sha256') or 'FAIL')[:6], s.get('opcodes'))
        if r.get('exact'): ex.append((k,L))
Ls=sorted({L for v in tab.values() for L in v})
print('L:',Ls)
for k,v in tab.items():
    hs=[v.get(L,('-',None))[0] for L in Ls]
    ids={}; seq=''.join(ids.setdefault(h,chr(65+len(ids))) for h in hs)
    best=max(((v[L][1] or '0/0'),L) for L in v if v[L][1] and v[L][1]!='None/None') if any(v[L][1] and v[L][1]!='None/None' for L in v) else None
    opsets={h:v[L][1] for L in v for h in [v[L][0]]}
    print(f'{k[0]:18s}{k[1]:9s} {seq}  ', {ids[h]:opsets[h] for h in ids})
print('EXACT:',ex)
