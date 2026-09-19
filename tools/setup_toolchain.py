"""Install an already acquired toolchain tree, enforcing the checked-in lock."""
import argparse
import shutil
from pathlib import Path
from common import ROOT, identity, read_json, FormatError
from compiler import verify_lock

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--from',dest='source',type=Path);args=ap.parse_args()
    lock=read_json(ROOT/'layout/toolchain.json')
    if args.source:
        pairs=[]
        for relative,expected in lock['files'].items():
            source=args.source/Path(relative).relative_to('toolchain');dest=ROOT/relative
            if not source.is_file() or identity(source)!=expected:raise FormatError(f'wrong or missing tool input: {source}')
            pairs.append((source,dest))
        for source,dest in pairs:
            dest.parent.mkdir(parents=True,exist_ok=True)
            if source.resolve()!=dest.resolve():shutil.copyfile(source,dest)
    verify_lock(lock);print(f"Verified {len(lock['files'])} locked local toolchain inputs")

if __name__=='__main__':main()
