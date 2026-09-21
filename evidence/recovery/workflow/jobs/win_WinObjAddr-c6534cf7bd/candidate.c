struct WinObjectBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    void far *objects[256];
};

extern struct WinObjectBucket far * near win_handles[];
extern void far Punt(char far *message, ...);

void far *win_WinObjAddr(int windowPart, int objectPart)
{
    int objectNumber;
    unsigned int objectIndex;
    struct WinObjectBucket far *bucket;

    objectNumber = (windowPart & 0xff00) + objectPart;
    objectIndex = (unsigned char)objectNumber;
    bucket = win_handles[objectNumber >> 8];
    if (bucket->objectCount <= objectIndex)
        Punt("Attempt to get obj address outsize window");
    return bucket->objects[(unsigned char)objectNumber];
}
