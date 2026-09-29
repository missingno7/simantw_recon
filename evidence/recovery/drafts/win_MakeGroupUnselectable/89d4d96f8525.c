struct WinObject {
    unsigned char reserved[0x20];
    unsigned char group;
    unsigned char pad[3];
    unsigned char state;
};
struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    struct WinObject far *objects[256];
};
struct WinHandleWords { unsigned int offset; unsigned int selector; };
extern struct WinHandleWords near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
void far win_MakeGroupUnselectable(int objectNumber, int group)
{
    __segment bucketSegment;
    unsigned int bucketOffset;
    struct WinBucket __based(bucketSegment) *bucket;
    struct WinObject far * far *entry;
    int count;
    int i;
    volatile int window;

    win_LockWin(objectNumber);
    window = objectNumber & 0xff00;
    i = objectNumber >> 8;
    bucketOffset = win_handles[i].offset;
    bucketSegment = win_handles[i].selector;
    bucket = (struct WinBucket __based(bucketSegment) *)bucketOffset;
    i = 0;
    if (bucket->count > 0) {
        entry = bucket->objects;
        count = bucket->count;
        for (i = 0; i < count; i++) {
            if ((*entry)->group == (unsigned char)group)
                (*entry)->state &= ~2;
            entry++;
        }
    }
    win_UnlockWin(objectNumber);
}
