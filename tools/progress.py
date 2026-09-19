"""Publish recovery progress by revalidating the current built artifacts."""
from common import ROOT, read_json, write_json
from verify_recovery import main as verify

def main():
    verify()
    r=read_json(ROOT/'evidence/recovery/verified-objects.json')
    write_json(ROOT/'docs/progress.json', {k:v for k,v in r.items() if k not in ('game','runtime')})
    print('Published verified object recovery progress; standalone executable pending')

if __name__=='__main__':main()
