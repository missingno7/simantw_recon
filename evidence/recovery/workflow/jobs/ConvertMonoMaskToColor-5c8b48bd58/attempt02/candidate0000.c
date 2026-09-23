extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern void far WinPrintf(char far *format, ...);
extern void far invert(unsigned char far *buffer, unsigned int count);
extern void far * far _fmemcpy(void far *dst, const void far *src, unsigned int n);
extern unsigned char near displayType;

struct MonoMask {
    unsigned char prefix[8];
    unsigned int width;
    unsigned int height;
    unsigned char bits[1];
};

unsigned int far ConvertMonoMaskToColor(unsigned int sourceHandle)
{
    struct MonoMask far *source;
    struct MonoMask far *destination;
    unsigned int resultHandle;
    unsigned int width;
    unsigned int height;
    unsigned int rowBytes;
    unsigned int bytes;
    unsigned int rows;
    unsigned char far *sourceBits;
    unsigned char far *sourceRow;
    unsigned char far *destinationBits;

    source = (struct MonoMask far *)mem_Lock(sourceHandle);
    width = source->width;
    height = source->height;
    rowBytes = (width + 7) / 8;
    bytes = rowBytes * height;
    bytes = bytes * 5 + 12;
    resultHandle = mem_Alloc((unsigned long)bytes, 1, "clrbln");
    destination = (struct MonoMask far *)mem_Lock(resultHandle);
    destination->width = width;
    destination->height = height;
    destination->prefix[2] = 4;
    destination->prefix[0] = 3;
    sourceBits = (unsigned char far *)source + 12;
    destinationBits = (unsigned char far *)destination + 12;
    WinPrintf("\nBalloon Size=%d, %d", width, height);

    if (height > 0) {
        rows = height;
        do {
            sourceRow = sourceBits + rowBytes;
            _fmemcpy(destinationBits, sourceRow, rowBytes);
            destinationBits += rowBytes;
            if (displayType != 10)
                invert(sourceBits, rowBytes);
            _fmemcpy(destinationBits, sourceRow, rowBytes);
            destinationBits += rowBytes;
            _fmemcpy(destinationBits, sourceRow, rowBytes);
            destinationBits += rowBytes;
            _fmemcpy(destinationBits, sourceRow, rowBytes);
            destinationBits += rowBytes;
            _fmemcpy(destinationBits, sourceRow, rowBytes);
            destinationBits += rowBytes;
            sourceBits += rowBytes;
        } while (--rows);
    }
    mem_Unlock(sourceHandle);
    mem_Unlock(resultHandle);
    mem_Free(sourceHandle);
    return resultHandle;
}
