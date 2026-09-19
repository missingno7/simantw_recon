"""Expand locally supplied PCjs disk JSON and Microsoft SZDD distribution files.

Research/bootstrap only. Never consumes game fixtures. Format references in docs/sources.md.
"""
import argparse
import json
import struct
import subprocess
import hashlib
from pathlib import Path
from common import ROOT, Reader, FormatError, identity, write_json

def szdd(data):
    r=Reader(data);magic=r.take(8)
    if magic==bytes.fromhex('535a2088f02733d1'):pos=4096-18;size=r.u32()
    elif magic==bytes.fromhex('535a444488f02733'):
        if r.u8()!=65:raise FormatError('unsupported SZDD mode')
        r.u8();size=r.u32();pos=4096-16
    else:raise FormatError('not SZDD')
    window=bytearray(b' '*4096);out=bytearray()
    while len(out)<size:
        control=r.u8()
        for bit in range(8):
            if len(out)==size:break
            if control&(1<<bit):values=[r.u8()]
            else:
                lo,hi=r.unpack('BB');offset=lo|((hi&240)<<4);count=(hi&15)+3
                values=None
            if values is not None:
                window[pos]=values[0];out.append(values[0]);pos=(pos+1)&4095
            else:
                for i in range(count):
                    v=window[(offset+i)&4095];window[pos]=v;out.append(v);pos=(pos+1)&4095
    if len(out)!=size:raise FormatError('SZDD output length mismatch')
    return bytes(out)

def expand_disk(path):
    j=json.loads(path.read_text());out=bytearray()
    for cyl in j['diskData']:
        for track in cyl:
            for s in sorted(track,key=lambda x:x['s']):
                d=s.get('d',[0]);d=d+[d[-1]]*(s['l']//4-len(d))
                out.extend(struct.pack('<'+'I'*len(d),*(x&0xffffffff for x in d)))
    img=path.with_suffix('.img');img.write_bytes(out)
    # FAT12 extraction also handles old SDK boot sectors rejected by 7-Zip.
    v=j['volTable'][0]
    if v['idFAT']!=12:raise FormatError('expected FAT12 distribution image')
    fat=out[v['vbaFAT']*512:v['vbaRoot']*512]
    def chain(cluster):
        chunks=[];seen=set()
        while 2<=cluster<0xff8:
            if cluster in seen or cluster>=v['clusTotal']+2:raise FormatError('invalid FAT12 chain')
            seen.add(cluster);start=(v['vbaData']+(cluster-2)*v['clusSecs'])*512
            chunks.append(out[start:start+v['clusSecs']*512]);k=cluster*3//2
            word=int.from_bytes(fat[k:k+2],'little');cluster=(word>>4) if cluster&1 else word&4095
        return b''.join(chunks)
    expected={x['path'].lstrip('/'):x for x in j['fileTable'] if 'hash' in x}
    def directory(data,prefix=''):
        for pos in range(0,len(data),32):
            entry=data[pos:pos+32]
            if not entry or entry[0]==0:break
            if entry[0] in (0xe5,46) or entry[11]&8:continue
            stem=entry[:8].decode('ascii').rstrip();ext=entry[8:11].decode('ascii').rstrip()
            name=prefix+stem+('.'+ext if ext else '')
            payload=chain(int.from_bytes(entry[26:28],'little'))
            if entry[11]&16:directory(payload,name+'/');continue
            size=int.from_bytes(entry[28:32],'little');payload=payload[:size]
            if name not in expected or hashlib.md5(payload).hexdigest()!=expected[name]['hash']:raise FormatError('archive file hash mismatch: '+name)
            dest=path.with_suffix('')/name;dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(payload)
    start=v['vbaRoot']*512;directory(out[start:start+v['rootTotal']*32])

def main():
    receipts=[]
    for disk in sorted((ROOT/'toolchain').glob('MSC*.json')):
        expand_disk(disk)
        version='msc600a' if disk.name.startswith('MSC600') else 'msc700'
        for p in sorted(disk.with_suffix('').rglob('*')):
            if not p.is_file() or not p.name.endswith('$'):continue
            if version=='msc600a' and p.suffix=='.EX$':
                # PACKING.LST places DOS compiler passes across disks 1, 5, 7.
                selected={'C1':1,'C1L':1,'C2':1,'C3':7,'CL':5}
                if p.stem in selected and f'DISK{selected[p.stem]}-' not in disk.name:continue
            rel=p.relative_to(disk.with_suffix(''))
            ext={'EX$':'EXE','ER$':'ERR','MS$':'MSG','DE$':'DEF','LI$':'LIB','OB$':'OBJ','H$':'H','IN$':'INC','DL$':'DLL','38$':'386'}.get(p.suffix[1:])
            if ext is None:continue
            if version=='msc600a' and len(rel.parts)==1:rel=Path('BIN')/rel
            dest=ROOT/'toolchain'/version/rel.with_suffix('.'+ext)
            dest.parent.mkdir(parents=True,exist_ok=True)
            if p.read_bytes().startswith(b'KWAJ'):
                subprocess.run([str(ROOT/'toolchain/unpack_kwaj.exe'),str(p),str(dest)],check=True,capture_output=True)
                if dest.read_bytes().startswith(b'KWAJ'):raise FormatError('expand did not decode KWAJ')
            else:dest.write_bytes(szdd(p.read_bytes()))
            receipts.append({'disk':disk.name,'disk_identity':identity(disk),'compressed_path':p.relative_to(ROOT).as_posix(),
                             'output':dest.relative_to(ROOT).as_posix(),'identity':identity(dest)})
    write_json(ROOT/'layout/tool-extraction.json',receipts)
    print(f'Expanded {len(receipts)} compiler, library and header files')

if __name__=='__main__':main()
