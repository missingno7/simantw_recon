"""Library code-generation screening, deliberately weaker than FUNCTION_MATCH.

Objects with unsupported records are retained as errors, never silently matched.
Nearest publics bound the search; CFG-derived extents avoid counting padding.
Only OMF-declared fields are omitted from literal-byte screening. No compiler
identity is declared from these scores, especially when near-call relaxation or
Windows prologue transformations may be involved.
"""
from collections import Counter
from common import ROOT, fixture, write_json, identity, FormatError, sha256
from analysis import extent
from omf import parse,library_modules
import ne,mapsym

def main():
    raw=fixture('SIMANTW.EXE');n=ne.parse(raw);s=mapsym.parse(fixture('SIMANTW.SYM'))
    wanted={'__astart','__cinit','_malloc','_free','_realloc','_calloc','_rand','_srand','_fopen','_fread','_fwrite','_sprintf','_sqrt'}
    originals={}
    for seg in s['segments']:
        for symbol in seg['symbols']:
            if symbol['name'] not in wanted:continue
            ns=n['segments'][seg['number']-1];code=raw[ns['file_offset']:ns['file_offset']+ns['logical_size']]
            following=min([x['offset'] for x in seg['symbols'] if x['offset']>symbol['offset']]+[len(code)])
            e=extent(code,symbol['offset'],following)
            originals[symbol['name']]={'segment':seg['number'],'offset':symbol['offset'],'extent':e,'bytes':code[symbol['offset']:e['end'] or following]}
    results=[]
    for lib in ['toolchain/msc6ax/LIB/MLIBCE.LIB','toolchain/msc6ax/LIB/LLIBCE.LIB','toolchain/msc700/LIB/MLIBCW.LIB','toolchain/msc700/LIB/LLIBCW.LIB']:
        errors=Counter();rows=[];count=0
        for raw_obj in library_modules((ROOT/lib).read_bytes()):
            count+=1
            try:m=parse(raw_obj)
            except FormatError as e:errors[str(e)]+=1;continue
            for p in m['publics']:
                if p['name'] not in originals or not p['segment']:continue
                ss=m['segments'][p['segment']-1];code=bytes.fromhex(ss['data_hex'])
                following=min([x['offset'] for x in m['publics'] if x['segment']==p['segment'] and x['offset']>p['offset']]+[len(code)])
                e=extent(code,p['offset'],following);candidate=code[p['offset']:e['end'] or following];old=originals[p['name']]
                mask={i-p['offset'] for f in m['fixups'] if f['segment']==p['segment'] for i in range(f['offset'],f['offset']+f['width']) if p['offset']<=i<(e['end'] or following)}
                indices=[i for i in range(min(len(candidate),len(old['bytes']))) if i not in mask]
                rows.append({'symbol':p['name'],'module':m['name'],'module_sha256':m['sha256'],'candidate_size':len(candidate),'original_size':len(old['bytes']),
                    'same_length':len(candidate)==len(old['bytes']),'literal_bytes_equal':sum(candidate[i]==old['bytes'][i] for i in indices),'literal_bytes_compared':len(indices),
                    'candidate_extent':e,'original_extent':old['extent'],'candidate_hex':candidate.hex(),'original_hex':old['bytes'].hex(),
                    'fixups':[f for f in m['fixups'] if f['segment']==p['segment'] and p['offset']<=f['offset']<(e['end'] or following)],
                    'proof':'SCREENING_ONLY','semantic_fixups_proven':False})
        results.append({'library':lib,'identity':identity(ROOT/lib),'modules':count,'parse_errors':dict(errors),'functions':rows})
    write_json(ROOT/'evidence/experiments/toolchain/runtime-screen.json',{'exe_sha256':n['sha256'],'sym_sha256':s['sha256'],'results':results,
        'conclusion':'Exact original runtime NOT identified. DOS C6 libraries and C7 Windows libraries differ; test Windows SDK 3.0/3.1 C6-era runtime and linker prologue/call transformations.'})
    print('Screened',sum(len(x['functions']) for x in results),'runtime function/library pairs; no original compiler lock claimed')

if __name__=='__main__':main()
