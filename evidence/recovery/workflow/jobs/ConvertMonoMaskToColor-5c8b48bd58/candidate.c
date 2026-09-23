extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern void far WinPrintf(char far *format, ...);
extern void far invert(unsigned char far *buffer, unsigned int count);
extern void far * far memcpy(void far *dst, const void far *src, unsigned int n);
extern unsigned char near displayType;
struct MonoMask { unsigned int marker; unsigned char bitsPerPixel; unsigned char reserved[5]; int width; int height; unsigned char bits[1]; };
unsigned int far ConvertMonoMaskToColor(unsigned int sourceHandle)
{
    struct MonoMask far *source;
    struct MonoMask far *destination;
    unsigned int resultHandle;
    int width;
    int height;
    int rows;
    unsigned char far *sourceBits;
    unsigned char far *sourceRow;
    unsigned char far *destinationBits;
    source = (struct MonoMask far *)mem_Lock(sourceHandle);
    width = source->width;
    height = source->height;
    resultHandle = mem_Alloc((unsigned long)(unsigned int)(height * (width / 8) * 5 + 12), 1, "clrbln");
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
            sourceRow = sourceBits + width / 8;
            memcpy(destinationBits, sourceRow, width / 8);
            destinationBits += width / 8;
            if (displayType != 10)
                invert(sourceBits, width / 8);
            memcpy(destinationBits, sourceRow, width / 8);
            destinationBits += width / 8;
            memcpy(destinationBits, sourceRow, width / 8);
            destinationBits += width / 8;
            memcpy(destinationBits, sourceRow, width / 8);
            destinationBits += width / 8;
            memcpy(destinationBits, sourceRow, width / 8);
            destinationBits += width / 8;
            sourceBits += width / 8;
        } while (--rows);
    }
    mem_Unlock(sourceHandle);
    mem_Unlock(resultHandle);
    mem_Free(sourceHandle);
    return resultHandle;
}
