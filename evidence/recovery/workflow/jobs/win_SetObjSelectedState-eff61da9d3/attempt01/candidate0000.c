/*
 * win_SetObjSelectedState: set the selection state of an object; if its
 * exclusive-select flag (+0x24 bit 0x20) is set, first deselect every
 * other object in the same window bucket that shares its group byte
 * (+0x20), as in the admitted win_MakeGroupSelected / win_MakeObjSelected
 * family.
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
extern struct WinObject far * far win_ObjAddr(int objectNumber);
extern void far win_SetObjSelectedStateI(int object, int selected);

void far win_SetObjSelectedState(int objectNumber, int selected)
{
    struct WinObject far *object;
    struct WinBucket far *bucket;
    int window;
    int i;
    int group;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (object->flags & 0x20) {
        group = object->group;
        win_LockWin(objectNumber);
        window = objectNumber & 0xff00;
        i = 0;
        bucket = win_handles[objectNumber >> 8];
        for (; i < bucket->count; i++) {
            if (bucket->objects[i]->group == (unsigned char)group)
                win_SetObjSelectedStateI(window + i, 0);
        }
        win_UnlockWin(objectNumber);
    }
    win_SetObjSelectedStateI(objectNumber, selected);
    win_UnlockWin(objectNumber);
}
