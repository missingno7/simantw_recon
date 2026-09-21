/*
 * GUnpackPic: locate a packed picture resource, allocate a fresh block
 * for its unpacked form and unpack it into the caller's buffer.  The
 * source handle's block starts with an unknown word then a size word
 * at +2 and packed data at +4.  A new handle sized to that word (named
 * "dst" for mem_Alloc's debug tag) is returned through handleOut and
 * locked; UnpackInit is primed from the packed data pointer and its
 * size, Unpack copies a 12-byte header into dest, then Unpack expands
 * the remaining (size-16) bytes into the new block, and the count is
 * reported with WinPrintf before both handles are unlocked.
 */
struct PicBlock {
    unsigned int unknown0;
    unsigned int size;
    unsigned char data[1];
};

static char near allocName[] = "dst";
static char near fmt[] = "GUnpackPic(%u)(%u)\n";

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far WinPrintf(char far *format, ...);
extern void far UnpackInit(void far *src, unsigned int size);
extern unsigned int far Unpack(void far *dest, unsigned int size);

void far GUnpackPic(void far *dest, unsigned int far *handleOut, unsigned int handle)
{
    struct PicBlock far *block;
    void far *buf;
    unsigned int far *hp;
    unsigned int savedWord;
    unsigned int newHandle;
    unsigned int result;

    hp = handleOut;
    block = (struct PicBlock far *)mem_Lock(handle);
    newHandle = mem_Alloc(block->size, 1, allocName);
    *hp = newHandle;
    buf = mem_Lock(newHandle);
    UnpackInit((char far *)block + 4, block->size);
    Unpack(dest, 12);
    savedWord = block->size;
    result = Unpack(buf, savedWord - 16);
    WinPrintf(fmt, savedWord, result);
    mem_Unlock(handle);
    mem_Unlock(*hp);
}
