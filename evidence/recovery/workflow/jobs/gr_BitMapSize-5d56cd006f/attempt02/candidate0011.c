/*
 * gr_BitMapSize: report the pixel size of a bitmap database object.  The
 * object (kind 2, locked) is loaded; if it cannot be, the size is set to
 * 1x1 and 0 returned.  The locked block starts with a word that is -1
 * for a packed bitmap: then the packed stream after the 4-byte header
 * (its length in the second word) is opened with UnpackInit, the first
 * twelve bytes are unpacked into a stack header and its point at offset
 * 8 is copied to the caller as a whole.  An unpacked block gives its
 * width and height words at offsets 8 and 10.  The block is unlocked,
 * the object released and 1 returned.
 */
struct Point {
    int x;
    int y;
};

struct BitmapHeader {
    unsigned char raw[8];
    struct Point size;
};

struct BitmapBlock {
    int packed;
    int length;
    unsigned char data[4];
    int width;
    int height;
};

extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_ReleaseObject(int object, int kind);
extern void far *far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far UnpackInit(unsigned char far *packed, int length);
extern void far Unpack(void far *dest, int count);

int far gr_BitMapSize(struct Point far *size, int object)
{
    unsigned int handle;
    struct BitmapBlock far *block;
    struct BitmapHeader header;
    struct Point far *p;

    handle = db_LoadObject(object, 2, 1);
    if (handle == 0) {
        size->y = 1;
        size->x = 1;
        return 0;
    }
    block = (struct BitmapBlock far *)mem_Lock(handle);
    if (block->packed == -1) {
        UnpackInit(block->data, block->length);
        Unpack((void far *)&header, 12);
        size->x = header.size.x;
        size->y = header.size.y;
    } else {
        size->x = block->width;
        size->y = block->height;
    }
    mem_Unlock(handle);
    db_ReleaseObject(object, 2);
    return 1;
}
