struct PicBlock {
    unsigned int unknown0;
    unsigned int size;
    unsigned char data[1];
};

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far WinPrintf(char far *format, ...);
extern void far UnpackInit(void far *src, unsigned size);
extern int far Unpack(void far *dest, unsigned int size);

void far GUnpackPic(void far *dest, unsigned int far *handleOut, unsigned int handle)
{
    struct PicBlock huge *block;
    void huge *buf;
    unsigned int savedWord;
    unsigned int result;

    block = (struct PicBlock huge *)mem_Lock(handle);
    buf = (void huge *)mem_Lock(*handleOut = mem_Alloc(block->size, 1, "dst"));
    UnpackInit((void far *)((unsigned long)block + 4), block->size);
    Unpack(dest, 12);
    savedWord = block->size;
    result = Unpack(buf, block->size - 16);
    WinPrintf("GUnpackPic(%u)(%u)\n", savedWord, result);
    mem_Unlock(handle);
    mem_Unlock(*handleOut);
}
