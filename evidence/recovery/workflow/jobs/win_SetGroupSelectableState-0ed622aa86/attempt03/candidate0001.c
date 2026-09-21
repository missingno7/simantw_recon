/*
 * win_SetGroupSelectableState: set the selectable flag (bit 1 of the
 * object flag word at +0x24, as in the verified GameObject declarations)
 * for every object in a window whose group byte (+0x20) equals the
 * requested group.  The window is the high byte of the packed object
 * number; its far bucket (win_handles, as in the admitted win_GetObjRect)
 * holds the object count at +0xc and the far object pointer table at
 * +0x2c.  The window is locked around the walk; the object table is
 * walked with DS switched to the bucket segment, and the flag bit is
 * rewritten as flags ^= ((flags ^ (state << 1)) & 2).  The masked window
 * number is assigned first to a variable that is later reused, which the
 * compiler evaluates but never stores.
 */
struct WinObject {
    unsigned char reserved[0x20];
    unsigned char group;
    unsigned char pad[3];
    unsigned int flags;
};

struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    struct WinObject far *objects[256];
};

extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

void far win_SetGroupSelectableState(int objectNumber, int group, int state)
{
    long handle;
    struct WinBucket far *bucket;
    struct WinObject far * far *entry;
    struct WinObject far *object;
    int n;

    win_LockWin(objectNumber);
    n = objectNumber & 0xff00;
    handle = (long)win_handles[objectNumber >> 8];
    bucket = (struct WinBucket far *)handle;
    if (bucket->count > 0) {
        entry = bucket->objects;
        n = bucket->count;
        do {
            object = *entry;
            if (object->group == (unsigned char)group)
                object->flags ^= (object->flags ^ (state << 1)) & 2;
            entry++;
        } while (--n);
    }
    win_UnlockWin(objectNumber);

}
