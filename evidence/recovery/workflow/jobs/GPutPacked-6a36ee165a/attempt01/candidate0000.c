/*
 * Semantic hypothesis: unpack a packed image header and payload, expand the
 * image into an internal bitmap when its type requires it, then draw the
 * image in eight scanline bands plus a final partial band.  The source record
 * begins with a byte count followed by the packed stream.
 */
struct PackedHeader {
    int type;
    unsigned char flags;
    unsigned char mode;
    unsigned char reserved0[4];
    int width;
    int height;
    int extra;
};

extern void far UnpackInit(unsigned int bytes, void far *source);
extern int far Unpack(unsigned int bytes, void far *destination);
extern int far GImgSize(int left, int top, int right, int bottom);
extern int far GPicSize(int left, int top, int right, int bottom);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern unsigned int far mem_malloc(char far *name, unsigned int bytes);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far GPutPicS(int x, int y, int width, int height,
                         void far *bits, int stride, int transparent);

void far GPutPacked(int x, int y, unsigned char far *packed)
{
    struct PackedHeader header;
    unsigned int handle;
    unsigned int scratchHandle;
    unsigned char far *scratch;
    unsigned char far *bitmap;
    int height;
    int remainder;
    int stride;
    int row;
    int transparent;
    int width;

    UnpackInit(*(unsigned int far *)(packed + 2), packed + 4);
    Unpack(12, &header);
    width = header.width;
    remainder = header.height & 7;
    height = header.height & 0xfff8;
    row = 0;
    if (header.flags & 0x80) {
        stride = ((((header.flags & 0x7f) * width) + 31) & 0xffe0) >> 3;
    } else if ((header.flags & 0x7f) == 4 ||
               (header.flags & 0x7f) == 8) {
        stride = GPicSize(0, 0, width - 1, 0) - 4;
    } else {
        stride = GImgSize(0, 0, width - 1, 0) - 4;
    }

    if (header.type == 3) {
        handle = mem_Alloc((unsigned long)(GImgSize(0, x,
                                  width + x + 15 & 0xfff8, 0) - 4) * 8 + 4,
                           1, "PutPackedBuf");
        scratchHandle = mem_malloc("GPutPacked",
                                   (unsigned int)(header.extra * 8 + 4));
        bitmap = (unsigned char far *)mem_Lock(handle);
        scratch = (unsigned char far *)mem_Lock(scratchHandle);
        *(int far *)bitmap = width;
        *((int far *)bitmap + 1) = 8;
        *(int far *)scratch = width;
        *((int far *)scratch + 1) = 8;
    } else {
        stride = height;
        handle = mem_Alloc((unsigned long)stride * 8 + 4,
                           1, "utPackedBuf");
        bitmap = (unsigned char far *)mem_Lock(handle);
        scratch = bitmap;
    }

    if (header.height != 0) {
        bitmap = (unsigned char far *)mem_Lock(handle);
        if (Unpack(height * 8, bitmap + 4)) {
            if (header.type == 0) {
                transparent = (header.flags & 0x80) != 0;
                if (transparent) {
                    for (row = 0; row < height; row += 8) {
                        GPutPicS(x, y, FP_OFF(bitmap + 4), FP_SEG(bitmap + 4),
                                 width, 8, transparent);
                        if (!(header.flags & 0x80)) y += 8;
                    }
                    packed = packed;
                }
            }
        }
    }

    mem_Unlock(handle);
    mem_Free(handle);
}
