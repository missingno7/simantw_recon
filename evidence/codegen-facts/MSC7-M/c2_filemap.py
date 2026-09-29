"""Map C23216 code addresses to internal source files via ICE file-name string refs."""
import sys,pickle,collections,re,json
sys.path.insert(0,'build/workers/f-study-bm')
import c2dis as D
BS=chr(92)
im=D.img()
ins=pickle.load(open('build/workers/f-study-bm/c2ins.pkl','rb'))
cache={}
def s_at(va):
    if va in cache: return cache[va]
    try:
        o=im.va_to_file(va); r=im.data[o:o+60].split(b'\0')[0].decode('latin1')
    except Exception: r=None
    cache[va]=r; return r
hits=collections.defaultdict(list); callees=collections.Counter()
for k,i in enumerate(ins):
    m=re.search(r'0x4[78][0-9a-f]{4}\b',i[2])
    if i[1] in('push','mov') and m:
        s=s_at(int(m.group(),16))
        if s and s.endswith('.c') and (BS+'P2'+BS) in s:
            hits[s.split(BS)[-1]].append(i[0])
            c=next((x for x in ins[k+1:k+6] if x[1]=='call'),None)
            if c: callees[c[2]]+=1
print(callees.most_common(5))
rows=sorted((min(v),max(v),f,len(v)) for f,v in hits.items())
for a,b,f,n in rows: print(f'{f:24s} {n:4d} {hex(a)} {hex(b)}')
json.dump({f:sorted(hex(x) for x in v) for f,v in hits.items()},open('build/workers/f-study-bm/c2_source_file_sites.json','w'),indent=0)
