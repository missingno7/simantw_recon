/*
 * win_MakeGroupVisible: show every object of a window whose
 * group byte (+0x20) equals the requested group.  The window is the high
 * byte of the packed object number; its far bucket (win_handles, as in the
 * admitted win_GetObjRect) holds the object count at +0xc and the far
 * object pointer table at +0x2c.  The window is locked around the walk; a
 * running object number (a local copy of the argument, kept in SI) and an
 * index (DI) advance together with the far table pointer, and each
 * matching object is changed through win_SetObjVisibleState.  Locals are
 * declared in the order entry, object number, index, bucket to give the
 * observed frame layout (entry at [bp-4], number at [bp-6], index at
 * [bp-8], bucket at [bp-0xc]).
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

void far win_MakeGroupVisible(int objectNumber, int group)
{
    struct WinObject far * far *entry;
    int number;
    int i;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    number = objectNumber;
    i = 0;
    bucket = win_handles[objectNumber >> 8];
    if (bucket->count > 0) {
        entry = bucket->objects;
        do {
            if ((*entry)->group == (unsigned char)group)
                win_SetObjVisibleState(number, 1);
            entry++;
            number++;
            i++;
        } while (i < bucket->count);
    }
    win_UnlockWin(objectNumber);
}
