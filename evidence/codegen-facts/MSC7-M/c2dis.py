"""Tiny disassembly helper for C23216/CL images (worker-local)."""
import sys,struct
sys.path.insert(0,'tools')
from c2_image import C2Image
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
IM={}
def img(name='C23216.EXE'):
    if name not in IM: IM[name]=C2Image.read('toolchain/msc700/BIN/'+name)
    return IM[name]
md=Cs(CS_ARCH_X86,CS_MODE_32)
def dis(va,n=0x80,name='C23216.EXE'):
    im=img(name);o=im.va_to_file(va)
    for i in md.disasm(im.data[o:o+n],va): print(hex(i.address),i.mnemonic,i.op_str)
def dword(va,name='C23216.EXE'):
    im=img(name);return struct.unpack_from('<I',im.data,im.va_to_file(va))[0]
def sweep(name='C23216.EXE'):
    """Linear sweep that resynchronises after undecodable bytes."""
    im=img(name);code=im.objects[0];base=im.image_base+code.rva
    data=im.data[code.seek_offset:code.file_end];pos=0;out=[]
    while pos<len(data):
        got=False
        for i in md.disasm(data[pos:],base+pos):
            out.append((i.address,i.mnemonic,i.op_str,i.size));pos=i.address-base+i.size;got=True
        if pos<len(data) and (not got or True):
            pos+=1
    return out
def refs(needle,ins):
    return [k for k,i in enumerate(ins) if needle in i[2]]
if __name__=='__main__':
    va=int(sys.argv[1],16);n=int(sys.argv[2],16) if len(sys.argv)>2 else 0x80
    dis(va,n,sys.argv[3] if len(sys.argv)>3 else 'C23216.EXE')
