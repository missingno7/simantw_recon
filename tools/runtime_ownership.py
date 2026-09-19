"""Publish exclusion ranges from complete SDK member matches only."""
from common import ROOT, read_json, write_json

def main():
    source='evidence/experiments/toolchain/library-members.json'
    evidence=read_json(ROOT/source);members=[];covered=set()
    for lib in evidence['results']:
        if lib['library'] not in ('toolchain/sdk300/CLIB/LLIBCW.LIB','toolchain/sdk300/CLIB/LLIBFPW.LIB'):continue
        for m in lib['members']:
            if m['result'] not in ('CONFIRMED_MEMBER','STRONGLY_SUPPORTED_MEMBER'):continue
            ranges=[]
            for c in m['contributions']:
                if c['segment']!='_TEXT':continue
                for a,b in c['initialized_ranges']:
                    ranges.append(dict(segment=c['original_segment'],offset=c['original_offset']+a,size=b-a))
                    covered.update((c['original_segment'],c['original_offset']+i) for i in range(a,b))
            members.append(dict(library=lib['library'],library_identity=lib['identity'],member=m['module'],
                member_sha256=m['module_sha256'],status='CONFIRMED' if m['result']=='CONFIRMED_MEMBER' else 'STRONGLY SUPPORTED',
                publics=m['publics'],code_ranges=ranges,evidence=source,
                scope='REUSE_HISTORICAL_OBJECT; excluded from C reconstruction; library packaging identity not uniquely implied by shared members'))
    write_json(ROOT/'layout/runtime-ownership.json',dict(fixture_sha256=evidence['exe_sha256'],members=members,unique_code_bytes=len(covered)))
    print(len(members),'complete members;',len(covered),'unique code bytes')

if __name__=='__main__':main()
