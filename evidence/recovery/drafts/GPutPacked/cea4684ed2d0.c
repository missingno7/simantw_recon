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

extern void far UnpackInit(void far *source, unsigned int bytes);
extern int far Unpack(void far *destination, unsigned int bytes);
extern int far GImgSize(int left, int top, int right, int bottom);
extern int far GPicSize(int left, int top, int right, int bottom);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern unsigned int far mem_malloc(char far *name, unsigned int bytes);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far GPutPicS(int first, int second, int third, int fourth,
                         int fifth, int sixth, int seventh);

#define FP_OFF(fp) ((unsigned)(unsigned long)(fp))
#define FP_SEG(fp) ((unsigned)((unsigned long)(fp) >> 16))

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
    int rowCount;

    UnpackInit(packed + 4, *(unsigned int far *)(packed + 2));
    Unpack(&header, 12);
    remainder = header.height & 7;
    header.height &= 0xfff8;
    height = header.height;
    rowCount = height;
    row = 0;
    if (header.flags & 0x80) {
        stride = ((((header.flags & 0x7f) * header.width) + 31) & 0xffe0) >> 3;
    } else if ((header.flags & 0x7f) == 4 ||
               (header.flags & 0x7f) == 8) {
        stride = GPicSize(0, 0, header.width - 1, 0) - 4;
    } else {
        stride = GImgSize(0, 0, header.width - 1, 0) - 4;
    }

    if (header.type == 3) {
        handle = mem_Alloc((unsigned long)(GImgSize(x, 0,
                                  header.width + x + 15 & 0xfff8, 1) - 4) * 8 + 4,
                           1, "PutPackedBuf");
        scratchHandle = mem_malloc("GPutPacked",
                                   (unsigned int)(header.extra * 8 + 4));
        bitmap = (unsigned char far *)mem_Lock(handle);
        scratch = (unsigned char far *)mem_Lock(scratchHandle);
        *(int far *)bitmap = header.width;
        *((int far *)bitmap + 1) = 8;
        *(int far *)scratch = header.width;
        *((int far *)scratch + 1) = 8;
    } else {
        handle = mem_Alloc((unsigned long)stride * 8 + 4,
                           1, "utPackedBuf");
        bitmap = (unsigned char far *)mem_Lock(handle);
        scratch = bitmap;
    }

    if (header.height != 0) {
        bitmap = (unsigned char far *)mem_Lock(handle);
        if (Unpack(bitmap + 4, stride * 8)) {
            if (header.type == 0) {
                transparent = (header.flags & 0x80) != 0;
                if (transparent) {
                    for (row = 0; row < rowCount; row += 8) {
                        GPutPicS(x, y, FP_OFF(bitmap + 4), FP_SEG(bitmap + 4),
                                 header.width, 8, transparent);
                        if (!(header.flags & 0x80)) y += 8;
                    }
                    packed = packed;
                }
            }
        }
    }

    if (remainder != 0) {
        if (Unpack(bitmap + 4, remainder * stride)) {
            if (header.type == 0) {
                GPutPicS(x, y + height, FP_OFF(bitmap + 4), FP_SEG(bitmap + 4),
                         header.width, remainder, (header.flags & 0x80) != 0);
            }
        }
    }

    mem_Unlock(handle);
    mem_Free(handle);
}
