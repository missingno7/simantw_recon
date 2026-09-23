extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern void far WinPrintf(char far *format, ...);
extern void far invert(unsigned int base, unsigned int segment, unsigned int row);
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
    unsigned int row;
    unsigned int i;
    unsigned char far *sourceBits;
    unsigned char far *destinationBits;

    source = (struct MonoMask far *)mem_Lock(sourceHandle);
    width = source->width;
    height = source->height;
    rowBytes = (width + 7) / 8;
    resultHandle = mem_Alloc((unsigned long)rowBytes * height * 5L + 12L,
                             1, "clrbln");
    destination = (struct MonoMask far *)mem_Lock(resultHandle);
    destination->width = width;
    destination->height = height;
    destination->prefix[0] = 3;
    destination->prefix[2] = 4;
    sourceBits = (unsigned char far *)source + 12 + rowBytes;
    destinationBits = (unsigned char far *)destination + 12;
    WinPrintf("\nBalloon Size=%d, %d", width, height);

    if (height > 0) {
        row = height;
        do {
            for (i = 0; i < rowBytes; ++i)
                destinationBits[i] = sourceBits[i];
            if (displayType != 10)
                invert((unsigned int)((unsigned char far *)source + 12),
                       source->prefix[0], (unsigned int)sourceBits);
            for (i = 1; i < 5; ++i) {
                for (width = 0; width < rowBytes; ++width)
                    destinationBits[width] = sourceBits[width];
                destinationBits += rowBytes;
            }
            sourceBits += rowBytes;
            destinationBits += rowBytes;
        } while (--row != 0);
    }
    mem_Unlock(sourceHandle);
    mem_Unlock(resultHandle);
    mem_Free(sourceHandle);
    return resultHandle;
}
