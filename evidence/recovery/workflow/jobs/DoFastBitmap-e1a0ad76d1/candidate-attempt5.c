struct FastInfo {
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
    unsigned char pixels[64];
};

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern int near clipDC;
extern volatile unsigned char far Dx8[];
extern int far pascal SetBkMode(int dc, int mode);
extern int far pascal SetDIBitsToDevice(int dc, int xDest, int yDest,
                                        unsigned int width, unsigned int height,
                                        int xSource, int ySource,
                                        unsigned int firstScan,
                                        unsigned int scanCount,
                                        void far *bits, void far *info,
                                        unsigned int colorUse);

void far DoFastBitmap(int xDest, int yDest, int width, int height,
                      void far *bits, int fourByteMode)
{
    unsigned int handle;
    struct FastInfo far *info;
    int i;
    unsigned char near *pixels;

    handle = mem_Alloc(0x68L, 0, "bm");
    if (bits != 0 && handle != 0) {
        info = (struct FastInfo far *)mem_Lock(handle);
        SetBkMode(clipDC, 1);
        info->size = 0x28L;
        info->width = (long)width;
        info->height = (long)height;
        info->planes = 1;
        info->bitCount = 4;
        info->compression = 0L;
        info->imageSize = ((((long)width * 4L) + 31L) / 32L) * (long)height * 4L;
        info->xPixelsPerMeter = 0L;
        info->yPixelsPerMeter = 0L;
        info->colorsUsed = 0L;
        info->colorsImportant = 0L;
        pixels = info->pixels;
        for (i = 0; i < 64; i += 4) {
            if (fourByteMode == 0) {
                pixels[i] = Dx8[i - 0x7400 + 0x40];
                pixels[i + 1] = Dx8[i - 0x7400 + 0x41];
                pixels[i + 2] = Dx8[i - 0x7400 + 0x42];
                pixels[i + 3] = 0;
            } else {
                pixels[i] = Dx8[i - 0x7400 + 2];
                pixels[i + 1] = Dx8[i - 0x7400 + 1];
                pixels[i + 2] = Dx8[i - 0x7400];
            }
        }
        SetDIBitsToDevice(clipDC, xDest, yDest, width, height,
                          0, 0, 0, height, bits, info, 0);
        mem_Unlock(handle);
        goto free_handle;
    }
    if (handle == 0) return;
free_handle:
    mem_Free(handle);
}




