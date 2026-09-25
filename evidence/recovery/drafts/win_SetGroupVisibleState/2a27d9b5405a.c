/*
 * win_SetGroupVisibleState: show or hide every object of a window whose
 * group byte (+0x20) equals the requested group.  The window is the high
 * byte of the packed object number; its far bucket (win_handles, as in the
 * admitted win_GetObjRect) holds the object count at +0xc and the far
 * object pointer table at +0x2c.  The window is locked around the walk;
 * for each object index the matching object is changed through
 * win_SetObjVisibleState(objectNumber + index, visible), which the
 * compiler strength-reduces into an incrementing copy of the object
 * number in SI.  The index starts at zero before the bucket lookup.
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
extern void far win_SetObjVisibleState(int object, int visible);

void far win_SetGroupVisibleState(int objectNumber, int group, int visible)
{
    struct WinBucket far *bucket;
    struct WinObject far * far *entry;
    int i;

    win_LockWin(objectNumber);
    i = 0;
    bucket = win_handles[objectNumber >> 8];
    if (bucket->count > 0) {
        entry = bucket->objects;
        do {
            if ((*entry)->group == (unsigned char)group)
                win_SetObjVisibleState(objectNumber + i, visible);
            entry++;
            i++;
        } while (i < bucket->count);
    }
    win_UnlockWin(objectNumber);
}
