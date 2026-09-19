"""Construct recovered objects from sources/libraries, never original fixtures."""
import argparse
import shutil
from common import ROOT, read_json, write_json, identity, sha256, FormatError
from compiler import compile_source
import omf

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('action',nargs='?',choices=['objects'],default='objects')
    ap.add_argument('--only',help='Comma-separated symbols to rebuild; retain other previously built objects for verification')
    args=ap.parse_args()
    out=ROOT/'build/recovered';out.mkdir(parents=True,exist_ok=True)
    objects=[]
    previous={r['symbol']:r for r in read_json(out/'manifest.json')['game_objects']} if args.only and (out/'manifest.json').exists() else {}
    selected=set(args.only.split(',')) if args.only else None
    recipes=read_json(ROOT/'src/recovery.json')['targets']
    if selected and selected-set(recipes):raise FormatError('unknown requested recovery symbol')
    for name,target in recipes.items():
        if selected is not None and name not in selected:
            if name not in previous:raise FormatError('missing prior object; run full build')
            objects.append(previous[name]);continue
        obj,receipt=compile_source(target['source'],target['flags'],target.get('compiler','msc600a'))
        dest=out/(name+'.obj');shutil.copyfile(obj,dest)
        objects.append(dict(symbol=name,object=dest.relative_to(ROOT).as_posix(),identity=identity(dest),receipt=receipt))
        print('Recovered C:',name,flush=True)
    runtime=[];cache={}
    for index,member in enumerate(read_json(ROOT/'layout/runtime-ownership.json')['members']):
        lib=member['library']
        if lib not in cache:
            if identity(ROOT/lib)!=member['library_identity']:raise FormatError('changed library '+lib)
            cache[lib]={sha256(b):b for b in omf.library_modules((ROOT/lib).read_bytes())}
        b=cache[lib].get(member['member_sha256'])
        if b is None:raise FormatError('missing matched historical member')
        dest=out/('crt%03d.obj'%index);dest.write_bytes(b)
        runtime.append(dict(library=lib,member=member['member'],member_sha256=member['member_sha256'],object=dest.relative_to(ROOT).as_posix(),identity=identity(dest)))
    write_json(out/'manifest.json',dict(game_objects=objects,runtime_objects=runtime,fixture_construction_inputs=[],whole_executable=False))
    print('Constructed',len(objects),'game objects and',len(runtime),'historical runtime objects. Full link pending.')

if __name__=='__main__':main()
