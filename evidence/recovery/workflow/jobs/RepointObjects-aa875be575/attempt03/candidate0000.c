/*
 * Hypothesis: a window bucket stores its object-count word at +0x0c and a
 * far-pointer table at +0x2c.  The packed object data begins immediately
 * after that table, so the routine seeds a cursor at table+count*4 and
 * repoints each table entry to the next packed object.  Each object's word
 * at +0x22 is its byte stride.
 */
struct WinObject {
    unsigned char header[0x22];
    unsigned int stride;
};

struct WinObjectBucket {
    unsigned char header[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    struct WinObject far *objects[256];
};

extern struct WinObjectBucket far * near win_handles[];

void far RepointObjects(int objectNumber)
{
    struct WinObjectBucket far *bucket;
    struct WinObject far *cursor;
    struct WinObject far * far *slot;
    int count;
    int index;

    bucket = win_handles[objectNumber >> 8];
    count = bucket->objectCount;
    cursor = (struct WinObject far *)((unsigned char far *)bucket
                                      + 0x2c + count * 4);
    if (count <= 0)
        return;
    slot = (struct WinObject far * far *)((unsigned char far *)bucket + 0x2c);
    index = count;
    do {
        *slot = cursor;
        cursor = (struct WinObject far *)((unsigned char far *)cursor
                                          + cursor->stride);
        ++slot;
    } while (--index);
}
