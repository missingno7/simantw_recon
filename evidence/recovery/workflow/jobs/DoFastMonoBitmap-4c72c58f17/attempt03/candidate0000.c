struct MonoInfo {
    unsigned long size;
    long width;
    long height;
    unsigned int planes;
    unsigned int bitCount;
    unsigned long compression;
    unsigned long imageSize;
    long xPixelsPerMeter;
    long yPixelsPerMeter;
    unsigned long colorsUsed;
    unsigned long colorsImportant;
    unsigned char palette[8];
};

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern int near clipDC;
extern int far pascal SetBkMode(int dc, int mode);
extern int far pascal SetDIBitsToDevice(int dc, int xDest, int yDest,
                                        unsigned int width, unsigned int height,
                                        int xSource, int ySource,
                                        unsigned int firstScan,
                                        unsigned int scanCount,
                                        void far *bits, void far *info,
                                        unsigned int colorUse);

void far DoFastMonoBitmap(int xDest, int yDest, int height,
                          int width, unsigned int bitsOffset,
                          unsigned int bitsSegment)
{
    unsigned int handle;
    struct MonoInfo far *info;

    if ((bitsOffset | bitsSegment) == 0)
        return;
    handle = mem_Alloc(0x30L, 0, "bm");
    if (handle == 0)
        return;
    info = (struct MonoInfo far *)mem_Lock(handle);
    SetBkMode(clipDC, 1);
    info->size = 0x28L;
    info->width = (long)width;
    info->height = (long)height;
    info->planes = 1;
    info->bitCount = 1;
    info->compression = 0L;
    info->imageSize = ((((long)width + 31L) / 32L) * 4L) * (long)height;
    info->xPixelsPerMeter = 0L;
    info->yPixelsPerMeter = 0L;
    info->colorsUsed = 0L;
    info->colorsImportant = 0L;
    info->palette[0] = 0;
    info->palette[1] = 0;
    info->palette[2] = 0;
    info->palette[3] = 0;
    info->palette[4] = 0xff;
    info->palette[5] = 0xff;
    info->palette[6] = 0xff;
    info->palette[7] = 0;
    SetDIBitsToDevice(clipDC, xDest, yDest, height, width,
                      0, 0, 0, width,
                      (void far *)(((unsigned long)bitsSegment << 16) | bitsOffset),
                      info, 0);
    mem_Unlock(handle);
    mem_Free(handle);
}



