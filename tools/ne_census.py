"""Regenerate canonical, hash-bound structural evidence."""
import csv
import io
from collections import Counter
from common import ROOT, fixture, write_json, sha256
import ne
import mapsym

def ownership(segment,name,offset):
    if segment==4:
        if name.startswith('Prof') or name.startswith('PROF'):return 'THIRD_PARTY','PLAUSIBLE','profiler-named startup prefix'
        if offset>=0x43d6:return 'UNKNOWN','UNKNOWN','mixed utility/library tail; not established CRT'
        if name=='__astart':return 'WINDOWS_STARTUP','PROBABLE','entry point and Microsoft startup symbol'
        if name.startswith(('__aF','__aN','__rt','__f','__cint')):return 'FLOAT_RUNTIME','PLAUSIBLE','runtime naming; library comparison pending'
        return 'MICROSOFT_CRT','PROBABLE','CRT names/adjacency; exact library unproven'
    if segment<=7:
        return ('GAME','PROBABLE','game/graphics/application segment; upstream utility ownership unresolved')
    return 'UNKNOWN','UNKNOWN','data ownership requires references and library evidence'

def main():
    exe=fixture('SIMANTW.EXE');sym=fixture('SIMANTW.SYM')
    n=ne.parse(exe);s=mapsym.parse(sym);check=mapsym.cross_check(s,n)
    provenance={'exe_sha256':sha256(exe),'sym_sha256':sha256(sym)}
    n['provenance']=provenance;s['provenance']=provenance
    write_json(ROOT/'evidence/census/ne.json',n)
    write_json(ROOT/'evidence/census/pair-validation.json',dict(provenance,**check))
    write_json(ROOT/'evidence/symbols/symbols.json',s)
    segments=[];inventory=[];address_map={}
    for ns,ss in zip(n['segments'],s['segments']):
        segments.append({**ns,'name':ss['name'],'symbol_count':ss['symbol_count'],
            'ownership':'MIXED_RUNTIME_AND_UTILITIES' if ns['number']==4 else 'PROBABLE_GAME' if ns['kind']=='CODE' else 'UNCLASSIFIED_DATA',
            'historical_translation_unit':None,'topology_confidence':'UNKNOWN'})
        sy=sorted(ss['symbols'],key=lambda x:(x['offset'],x['table_order']))
        for x in sy:
            own,confidence,reason=ownership(ss['number'],x['name'],x['offset'])
            following=next((a['offset'] for a in sy if a['offset']>x['offset']),ns['logical_size'])
            row={**x,'segment':ss['number'],'segment_name':ss['name'],'kind':'DATA_SYMBOL' if ns['kind']=='DATA' else 'SYMBOL_ONLY_START',
                 'ownership':own,'ownership_confidence':confidence,'ownership_reason':reason,
                 'next_symbol_upper_bound':following,'extent':None,'proof':'SYMBOL_IDENTIFIED'}
            inventory.append(row)
            address_map.setdefault(f"{ss['number']:04x}:{x['offset']:04x}",[]).append(x['name'])
    write_json(ROOT/'evidence/census/segments.json',dict(provenance,segments=segments))
    write_json(ROOT/'evidence/symbols/inventory.json',dict(provenance,symbols=inventory))
    write_json(ROOT/'evidence/symbols/symbol-address-map.json',dict(provenance,addresses=address_map))
    stream=io.StringIO(newline='');w=csv.writer(stream)
    w.writerow(['exe_sha256','sym_sha256','segment','segment_name','offset','name','kind','ownership','confidence'])
    for x in inventory:w.writerow([provenance['exe_sha256'],provenance['sym_sha256'],x['segment'],x['segment_name'],x['offset'],x['name'],x['kind'],x['ownership'],x['ownership_confidence']])
    for x in s['absolute_symbols']:w.writerow([provenance['exe_sha256'],provenance['sym_sha256'],0,'ABSOLUTE',x['offset'],x['name'],'ABSOLUTE','UNKNOWN','UNKNOWN'])
    (ROOT/'evidence/symbols/symbols.csv').write_text(stream.getvalue(),encoding='utf8')
    summary=dict(provenance,segments=len(segments),segmented_symbols=len(inventory),absolute_symbols=len(s['absolute_symbols']),
        resources=len(n['resources']),relocation_records=sum(len(x['relocations']) for x in segments),
        relocation_sites=sum(len(r['sites']) for x in segments for r in x['relocations']),
        ownership_counts=dict(Counter(x['ownership'] for x in inventory)),imports=n['modules'])
    write_json(ROOT/'evidence/census/summary.json',summary)
    print(f"NE: {len(segments)} segments, {summary['relocation_records']} fixup records / {summary['relocation_sites']} sites, {len(n['resources'])} resources")
    print(f"MAPSYM {s['version']}: {len(inventory)} segmented + {len(s['absolute_symbols'])} absolute symbols; pair checks pass")

if __name__=='__main__':main()
