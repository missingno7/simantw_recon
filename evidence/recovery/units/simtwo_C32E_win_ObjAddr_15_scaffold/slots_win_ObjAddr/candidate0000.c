/*
 * Hypothesis: a packed object number selects a signed high-byte window bucket
 * and an unsigned low-byte entry.  Each far bucket stores its active-entry
 * limit at offset 0x0c and a table of four-byte far object addresses at 0x2c.
 * Invalid low-byte indices are reported through Punt; valid entries return the
 * stored far address.
 */
struct WinObjectBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    void far *objects[256];
};

extern struct WinObjectBucket far * near win_handles[];
extern void far Punt(char far *message, ...);

void far *win_ObjAddr(int objectNumber)
{
    struct WinObjectBucket far *bucket;

    bucket = win_handles[objectNumber >> 8];
    if (bucket->objectCount <= (unsigned char)objectNumber)
        Punt("Attempt to get obj address outsize window");
    return bucket->objects[(unsigned char)objectNumber];
}
