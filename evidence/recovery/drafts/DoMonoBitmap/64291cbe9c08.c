/*
 * DoMonoBitmap builds a one-bit DIB and draws it.  The call site in the
 * recovered GPutImg pushes x, y, width, height, one far image pointer, and a
 * final integer mode, then cleans fourteen argument bytes.  The body allocates
 * a 32-bit-row-aligned pixel buffer and a 0x30-byte DIB record, optionally
 * copies source rows, sets the two palette entries from display colors or the
 * monochrome pattern, and calls SetDIBitsToDevice.
 */
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

extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern int near clipDC;
extern int near __backColor;
extern unsigned int near __foreColor;
extern unsigned char near displayType;
extern unsigned char near monoPat;
extern unsigned char far rgb[];
extern int far pascal SetBkMode(int dc, int mode);
extern int far pascal SetDIBitsToDevice(
    int dc, int xDest, int yDest, unsigned int width, unsigned int height,
    int xSource, int ySource, unsigned int firstScan, unsigned int scanCount,
    void far *bits, void far *info, unsigned int colorUse);

void far DoMonoBitmap(int xDest, int yDest, int width, int height,
                      void far *source, int mode)
{
    unsigned int bitsHandle;
    unsigned int infoHandle;
    unsigned char far *bits;
    struct MonoInfo far *info;
    unsigned long rowBytes;
    unsigned long imageBytes;
    int sourceRowBytes;
    int row;
    int column;
    unsigned long copyBytes;

    rowBytes = (((long)width + 31L) / 32L) * 4L;
    imageBytes = rowBytes * (long)height + 0x20L;
    bitsHandle = mem_Alloc(imageBytes, 0, "bm");
    infoHandle = mem_Alloc(0x30L, 0, "bm");

    if (source == 0 || bitsHandle == 0 || infoHandle == 0) {
        if (infoHandle != 0)
            mem_Free(infoHandle);
        if (bitsHandle != 0)
            mem_Free(bitsHandle);
        return;
    }

    bits = (unsigned char far *)mem_Lock(bitsHandle);
    info = (struct MonoInfo far *)mem_Lock(infoHandle);
    SetBkMode(clipDC, 1);

    sourceRowBytes = (width + 7) >> 3;
    if (mode != 0) {
        unsigned char far *src;
        unsigned char far *dst;

        src = (unsigned char far *)source;
        dst = bits;
        for (row = 0; row < height; ++row) {
            for (column = 0; column < sourceRowBytes; ++column)
                dst[column] = src[column];
            src += sourceRowBytes;
            dst += (unsigned int)rowBytes;
        }
    } else {
        unsigned char far *src;
        unsigned char far *dst;

        /* The mode-zero target path copies the full padded allocation span. */
        src = (unsigned char far *)source;
        dst = bits;
        copyBytes = imageBytes;
        if (copyBytes != 0L) while (copyBytes != 0L) {
            *dst++ = *src++;
            --copyBytes;
        }
    }

    info->size = 0x28L;
    info->width = (long)width;
    info->height = (long)height;
    info->planes = 1;
    info->bitCount = 1;
    info->compression = 0L;
    info->imageSize = rowBytes * (long)height;
    info->xPixelsPerMeter = 0L;
    info->yPixelsPerMeter = 0L;
    info->colorsUsed = 0L;
    info->colorsImportant = 0L;

    if (displayType & 1) {
        int color;

        color = __backColor & 0x0f;
        info->palette[0] = rgb[(color << 2) + 2];
        info->palette[1] = rgb[(color << 2) + 1];
        info->palette[2] = rgb[color << 2];
        info->palette[3] = 0;
        color = __foreColor & 0x0f;
        info->palette[4] = rgb[(color << 2) + 2];
        info->palette[5] = rgb[(color << 2) + 1];
        info->palette[6] = rgb[color << 2];
        info->palette[7] = 0;
    } else if (monoPat & 0x80) {
        info->palette[0] = 0xff;
        info->palette[1] = 0xff;
        info->palette[2] = 0xff;
        info->palette[3] = 0;
        info->palette[4] = 0;
        info->palette[5] = 0;
        info->palette[6] = 0;
        info->palette[7] = 0;
    } else {
        info->palette[0] = 0;
        info->palette[1] = 0;
        info->palette[2] = 0;
        info->palette[3] = 0;
        info->palette[4] = 0xff;
        info->palette[5] = 0xff;
        info->palette[6] = 0xff;
        info->palette[7] = 0;
    }

    SetDIBitsToDevice(clipDC, xDest, yDest, width, height, 0, 0, 0, height,
                      bits, info, 0);
    mem_Unlock(infoHandle);
    mem_Free(infoHandle);
    mem_Unlock(bitsHandle);
    mem_Free(bitsHandle);
}

/* Round 1, variant 3: controlled source-shape hypothesis. */
