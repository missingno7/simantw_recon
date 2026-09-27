struct BitmapHeader {
    unsigned int kind;
    unsigned char flags;
    unsigned char reserved[5];
    int width;
    int height;
};
struct BitmapResource {
    unsigned int kind;
    unsigned char flags;
    unsigned char reserved[5];
    int width;
    int height;
    unsigned char bits[1];
};

extern unsigned char near displayType;
extern unsigned int far db_LoadObject(int objectNumber, int kind, int lock);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far mem_Free(unsigned int handle);
extern void far UnpackInit(void far *input, unsigned int bytes);
extern int far Unpack(void far *output, unsigned int bytes);
extern void far WinPrintf(char far *format, ...);

extern void far ConvertBitmap2(int x, int y, void far *bits, int width,
    int height, int headerHeight, int headerWidth, int sourceX, int sourceY);
extern void far CopyBitmap2(int x, int y, void far *bits, int width,
    int height, int headerHeight, int headerWidth, int sourceX, int sourceY);
extern void far CopyMonoBitmap(int x, int y, void far *bits, int width,
    int height, int headerHeight, int headerWidth, int sourceX, int sourceY);
extern void far ConvertMaskBitmap2(int x, int y, void far *bits, int width,
    int height, int headerHeight, int headerWidth, int sourceX, int sourceY);
extern void far CopyMaskBitmap2(int x, int y, void far *bits, int width,
    int height, int headerHeight, int headerWidth, int sourceX, int sourceY);
extern void far CopyMonoMaskBitmap(int x, int y, void far *bits, int width,
    int height, int headerHeight, int headerWidth, int sourceX, int sourceY);

void far DrawBitMapToBuffer(int x, int y, int sourceX, int sourceY,
    int width, int height, int objectNumber,
    int far *heightOut, int far *widthOut)
{
    unsigned int sourceHandle;
    unsigned int unpackHandle;
    unsigned int packedBytes;
    int unpackedBytes;
    int sourceRow;
    struct BitmapResource far *resource;
    struct BitmapHeader header;
    void far *unpackedBits;
    void far *bitmapBits;

    sourceHandle = db_LoadObject(objectNumber, 2, 1);
    resource = (struct BitmapResource far *)mem_Lock(sourceHandle);

    if (resource->kind == 0xffffU) {
        resource = (struct BitmapResource far *)mem_Lock(sourceHandle);
        packedBytes = resource->height;
        unpackHandle = mem_Alloc((unsigned long)packedBytes, 1, "dst");
        unpackedBits = mem_Lock(unpackHandle);
        UnpackInit((void far *)resource->bits, packedBytes);
        Unpack((void far *)&header, 12);
        unpackedBytes = Unpack(unpackedBits, packedBytes - 0x10);
        WinPrintf("GUnpackPic(%u)(%u)\n", packedBytes, unpackedBytes);
        mem_Unlock(sourceHandle);
        mem_Unlock(unpackHandle);
        unpackedBits = mem_Lock(unpackHandle);

        if (header.kind == 0) {
            if (displayType & 1) {
                CopyMonoBitmap(x, y, unpackedBits, width, height,
                    header.height, header.width, sourceX,
                    width - header.height - sourceY);
            } else if (header.flags & 0x80) {
                CopyBitmap2(x, y, unpackedBits, width, height,
                    header.height, header.width, sourceX,
                    width - header.height - sourceY);
            } else {
                ConvertBitmap2(x, y, unpackedBits, width, height,
                    header.height, header.width, sourceX,
                    width - header.height - sourceY);
            }
        } else if (header.kind == 3) {
            if (displayType & 1) {
                CopyMonoMaskBitmap(x, y, unpackedBits, width, height,
                    header.height, header.width, sourceX,
                    width - header.height - sourceY);
            } else if (header.flags & 0x80) {
                CopyMaskBitmap2(x, y, unpackedBits, width, height,
                    header.height, header.width, sourceX,
                    width - header.height - sourceY);
            } else {
                ConvertMaskBitmap2(x, y, unpackedBits, width, height,
                    header.height, header.width, sourceX,
                    width - header.height - sourceY);
            }
        }

        mem_Unlock(unpackHandle);
        mem_Free(unpackHandle);
        *widthOut = header.width;
        *heightOut = header.height;
        mem_Unlock(sourceHandle);
        db_ReleaseHandle(sourceHandle);
        return;
    }

    bitmapBits = (void far *)resource->bits;
    if (resource->kind == 0) {
        if (displayType & 1) {
            CopyMonoBitmap(x, y, bitmapBits, width, height,
                resource->height, resource->width, sourceX,
                width - resource->height - sourceY);
        } else if (resource->flags & 0x80) {
            CopyBitmap2(x, y, bitmapBits, width, height,
                resource->height, resource->width, sourceX,
                width - resource->height - sourceY);
        } else {
            ConvertBitmap2(x, y, bitmapBits, width, height,
                resource->height, resource->width, sourceX,
                width - resource->height - sourceY);
        }
    } else if (resource->kind == 3) {
        if (displayType & 1) {
            CopyMonoMaskBitmap(x, y, bitmapBits, width, height,
                resource->height, resource->width, sourceX,
                width - resource->height - sourceY);
        } else if (resource->flags & 0x80) {
            CopyMaskBitmap2(x, y, bitmapBits, width, height,
                resource->height, resource->width, sourceX,
                width - resource->height - sourceY);
        } else {
            ConvertMaskBitmap2(x, y, bitmapBits, width, height,
                resource->height, resource->width, sourceX,
                width - resource->height - sourceY);
        }
    }

    *widthOut = resource->width;
    *heightOut = resource->height;
    mem_Unlock(sourceHandle);
    db_ReleaseHandle(sourceHandle);
}
