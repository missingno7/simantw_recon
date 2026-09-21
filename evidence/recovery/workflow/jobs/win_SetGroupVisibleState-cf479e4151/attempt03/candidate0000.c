/*
 * win_SetGroupVisibleState: show or hide every object of a window whose
 * group byte (+0x20) equals the requested group.  The window is the high
 * byte of the packed object number; its far bucket (win_handles, as in the
 * admitted win_GetObjRect) holds the object count at +0xc and the far
 * object pointer table at +0x2c.  The window is locked around the walk; a
 * running object number (a local copy of the argument, kept in SI) and an
 * index (DI) advance together with the far table pointer, and each
 * matching object is changed through win_SetObjVisibleState.  The
 * objects are indexed as bucket->objects[i]; the loop optimizer turns that
 * into a far pointer temp in the frame ([bp-4]) advanced by four, while
 * the index lives in DI and the running number in SI.  The index is
 * zeroed before the bucket lookup.
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
    int number;
    int i;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    number = objectNumber;
    i = 0;
    bucket = win_handles[objectNumber >> 8];
    while (i < bucket->count) {
        if (bucket->objects[i]->group == (unsigned char)group)
            win_SetObjVisibleState(number, visible);
        number++;
        i++;
    }
    win_UnlockWin(objectNumber);
}

