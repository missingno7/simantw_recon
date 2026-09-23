/*
 * Build a bottom-up 4bpp DIB for an already-packed bitmap, or ask
 * ConvertBitmap to pack the four source planes when conversion is enabled.
 * Rows are DWORD-padded, and the two color-table layouts are read from Dx8.
 * The target's palette-choice word at SS:BA2E has no exact MAPSYM name, so
 * this draft records the color-table choice as an explicit mode hypothesis.
 */
struct BitmapInfo {
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
    unsigned char palette[64];
};

extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern int near clipDC;
extern unsigned char far Dx8[];
extern void far ConvertBitmap(void far *destination, void far *source,
                              int height, int width);
extern int far pascal SetBkMode(int dc, int mode);
extern int far pascal SetDIBitsToDevice(int dc, int xDest, int yDest,
                                        unsigned int width,
                                        unsigned int height,
                                        int xSource, int ySource,
                                        unsigned int firstScan,
                                        unsigned int scanCount,
                                        void far *bits, void far *info,
                                        unsigned int colorUse);

void far DoBitmap(int xDest, int yDest, int width, int height,
                  void far *bits, int convert)
{
    unsigned int pixelsHandle;
    unsigned int infoHandle;
    unsigned char far *pixels;
    struct BitmapInfo far *info;
    unsigned long imageSize;
    unsigned long rowWords;
    unsigned long copyCount;
    unsigned long i;
    unsigned char far *source;
    unsigned char far *destination;
    unsigned char far *colorSource;
    unsigned char far *colorDestination;

    imageSize = ((((long)width * 4L) + 31L) / 32L) *
                (long)height * 4L;
    pixelsHandle = mem_Alloc(imageSize + 0x20L, 0, "bm");
    infoHandle = mem_Alloc(0x68L, 0, "bi");

    if (bits == 0 || pixelsHandle == 0 || infoHandle == 0)
        goto cleanup;

    pixels = (unsigned char far *)mem_Lock(pixelsHandle);
    info = (struct BitmapInfo far *)mem_Lock(infoHandle);
    SetBkMode(clipDC, 1);

    if (convert) {
        ConvertBitmap(pixels, bits, height, width);
    } else {
        copyCount = imageSize;
        source = (unsigned char far *)bits;
        destination = pixels;
        for (i = 0; i < copyCount; ++i)
            *destination++ = *source++;
    }

    info->size = 0x28L;
    info->width = (long)width;
    info->height = (long)height;
    info->planes = 1;
    info->bitCount = 4;
    info->compression = 0L;
    info->imageSize = imageSize;
    info->xPixelsPerMeter = 0L;
    info->yPixelsPerMeter = 0L;
    info->colorsUsed = 0L;
    info->colorsImportant = 0L;

    colorDestination = info->palette;
    if (convert)
        colorSource = Dx8 + 0x8c02;
    else
        colorSource = Dx8 + 0x8c42;
    for (i = 0; i < 16L; ++i) {
        colorDestination[0] = colorSource[0];
        colorDestination[1] = colorSource[1];
        colorDestination[2] = colorSource[2];
        colorDestination[3] = 0;
        colorDestination += 4;
        colorSource += 4;
    }

    rowWords = imageSize;
    SetDIBitsToDevice(clipDC, xDest, yDest, width, height,
                      0, 0, 0, height,
                      pixels, info, 0);
    mem_Unlock(pixelsHandle);
    mem_Free(pixelsHandle);
    mem_Unlock(infoHandle);
    mem_Free(infoHandle);
    return;

cleanup:
    if (infoHandle != 0)
        mem_Free(infoHandle);
    if (pixelsHandle != 0)
        mem_Free(pixelsHandle);
}
