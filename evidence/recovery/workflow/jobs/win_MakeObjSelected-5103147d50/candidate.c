/*
 * win_MakeObjSelected: select the given object; if its exclusive-select
 * flag (+0x24 bit 0x20) is set, first deselect every other object in the
 * same window bucket that shares its group byte (+0x20), walking the
 * bucket's far object-pointer table with a pointer (not an index), as in
 * the admitted win_MakeGroupSelected / win_ObjInv style bucket walks.
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

void far win_MakeObjSelected(int objectNumber)
{
    struct WinObject far *object;
    int group;
    struct WinBucket far *bucket;
    struct WinObject far * far *p;
    int window;
    int i;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (object->flags & 0x20) {
        group = object->group;
        win_LockWin(objectNumber);
        window = objectNumber & 0xff00;
        i = 0;
        bucket = win_handles[objectNumber >> 8];
        if (bucket->count > 0) {
            p = bucket->objects;
            do {
                if ((*p)->group == (unsigned char)group)
                    win_SetObjSelectedStateI(window, 0);
                p++;
                window++;
                i++;
            } while (i < bucket->count);
        }
        win_UnlockWin(objectNumber);
    }
    win_SetObjSelectedStateI(objectNumber, 1);
    win_UnlockWin(objectNumber);
}
