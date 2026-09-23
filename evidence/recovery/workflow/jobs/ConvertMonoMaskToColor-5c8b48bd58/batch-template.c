extern unsigned int @ALLOC_QUAL@ mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *@LOCK_QUAL@ mem_Lock(unsigned int handle);
extern int @UNLOCK_QUAL@ mem_Unlock(unsigned int handle);
extern void @FREE_QUAL@ mem_Free(int handle);
extern void @PRINTF_QUAL@ WinPrintf(char far *format, ...);
extern void far invert(unsigned char far *buffer, unsigned int count);
extern unsigned char near displayType;

struct MonoMask {
    unsigned int marker;
    unsigned char bitsPerPixel;
    unsigned char reserved[5];
    int width;
    int height;
    unsigned char bits[1];
};

unsigned int far ConvertMonoMaskToColor(unsigned int sourceHandle)
{
    struct MonoMask far *source;
    struct MonoMask far *destination;
    unsigned int resultHandle;
    int width;
    int height;
    int rows;
    int count;
    unsigned char far *sourceBits;
    unsigned char far *sourceRow;
    unsigned char far *destinationBits;
    unsigned char far *to;
    unsigned char far *from;

    source = (struct MonoMask far *)mem_Lock(sourceHandle);
    width = source->width;
    height = source->height;
    resultHandle = mem_Alloc((unsigned long)(height * (width / 8) * 5 + 12),
                             1, "clrbln");
    destination = (struct MonoMask far *)mem_Lock(resultHandle);
    destination->width = width;
    destination->height = height;
    destination->bitsPerPixel = 4;
    destination->marker = 3;
    sourceBits = (unsigned char far *)source + 12;
    destinationBits = (unsigned char far *)destination + 12;
    WinPrintf("\nBalloon Size=%d, %d", width, height);

    if (height > 0) {
        rows = height;
        do {
            sourceRow = sourceBits + (width / 8);
            from = sourceRow;
            to = destinationBits;
            count = width / 8;
            while (count--) *to++ = *from++;
            destinationBits = to;
            if (displayType != 10)
                invert(sourceBits, width / 8);
            from = sourceRow;
            to = destinationBits;
            count = width / 8;
            while (count--) *to++ = *from++;
            destinationBits = to;
            from = sourceRow;
            to = destinationBits;
            count = width / 8;
            while (count--) *to++ = *from++;
            destinationBits = to;
            from = sourceRow;
            to = destinationBits;
            count = width / 8;
            while (count--) *to++ = *from++;
            destinationBits = to;
            from = sourceRow;
            to = destinationBits;
            count = width / 8;
            while (count--) *to++ = *from++;
            destinationBits = to;
            sourceBits += width / 8;
        } while (--rows);
    }
    mem_Unlock(sourceHandle);
    mem_Unlock(resultHandle);
    mem_Free(sourceHandle);
    return resultHandle;
}
