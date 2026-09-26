/*
 * Load a bitmap resource, unpack its compressed payload when the first header
 * word is the compressed sentinel, then choose conversion/copy helpers from
 * displayType and the high mask bit.  The resource header's compressed-size
 * field is at +2 and its stream begins at +4; the two private format strings
 * were read from the matching DGROUP operands in the original image.
 */
struct BitmapResource {
    unsigned int compressed;
    unsigned int packedBytes;
    unsigned char payload[1];
};

struct BitmapInfo {
    unsigned char header[0x10];
    unsigned int width;
    unsigned int height;
    unsigned char flags;
};

extern unsigned char near displayType;
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far mem_Free(unsigned int handle);
extern void far UnpackInit(void far *src, unsigned int size);
extern int far Unpack(void far *output, unsigned int bytes);
extern void far WinPrintf(char far *format, ...);

extern void far ConvertBitmap2(int x, int y, void far *bits, int width,
    int height, int a, int b, int sourceX, int sourceY);
extern void far CopyBitmap2(int x, int y, void far *bits, int width,
    int height, int a, int b, int sourceX, int sourceY);
extern void far CopyMonoBitmap(int x, int y, void far *bits, int width,
    int height, int a, int b, int sourceX, int sourceY);
extern void far ConvertMaskBitmap2(int x, int y, void far *bits, int width,
    int height, int a, int b, int sourceX, int sourceY);
extern void far CopyMaskBitmap2(int x, int y, void far *bits, int width,
    int height, int a, int b, int sourceX, int sourceY);
extern void far CopyMonoMaskBitmap(int x, int y, void far *bits, int width,
    int height, int a, int b, int sourceX, int sourceY);

void far DrawBitMapToBuffer(int x, int y, int sourceX, int sourceY,
    int width, int height, int objectNumber,
    struct BitmapInfo far *info, void far *buffer)
{
    unsigned int sourceHandle;
    unsigned int unpackHandle;
    struct BitmapResource far *resource;
    void far *unpacked;
    unsigned int outputType;
    unsigned int packedBytes;
    int rowWidth;
    int firstRow;
    int lastRow;

    sourceHandle = db_LoadObject(objectNumber, 2, 1);
    resource = (struct BitmapResource far *)mem_Lock(sourceHandle);
    if (resource->compressed == 0xffffU) {
        resource = (struct BitmapResource far *)mem_Lock(sourceHandle);
        packedBytes = resource->packedBytes;
        unpackHandle = mem_Alloc((unsigned long)packedBytes, 1, "dst");
        unpacked = mem_Lock(unpackHandle);
        UnpackInit(packedBytes, resource->payload);
        outputType = (unsigned int)Unpack(&outputType, 12);
        rowWidth = Unpack((void far *)((char far *)resource - 0x10),
                          packedBytes);
        WinPrintf("GUnpackPic(%u)(%u)\n", outputType, rowWidth);
        mem_Unlock(sourceHandle);
        mem_Unlock(unpackHandle);
        unpacked = mem_Lock(unpackHandle);
    }

    if (outputType == 3) {
        if (!(displayType & 1)) {
            if (info->flags & 0x80)
                ConvertMaskBitmap2(x, y, unpacked, width, height,
                    firstRow, lastRow, sourceX, sourceY);
            else
                ConvertBitmap2(x, y, unpacked, width, height,
                    firstRow, lastRow, sourceX, sourceY);
        } else if (info->flags & 0x80) {
            CopyMaskBitmap2(x, y, unpacked, width, height,
                firstRow, lastRow, sourceX, sourceY);
        } else {
            CopyBitmap2(x, y, unpacked, width, height,
                firstRow, lastRow, sourceX, sourceY);
        }
    } else if (info->flags & 0x80) {
        CopyMonoMaskBitmap(x, y, unpacked, width, height,
            firstRow, lastRow, sourceX, sourceY);
    } else {
        CopyMonoBitmap(x, y, unpacked, width, height,
            firstRow, lastRow, sourceX, sourceY);
    }

    mem_Unlock(unpackHandle);
    mem_Free(unpackHandle);
    db_ReleaseHandle(sourceHandle);
}
