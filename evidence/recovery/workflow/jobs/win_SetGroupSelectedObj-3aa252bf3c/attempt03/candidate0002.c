/*
 * win_SetGroupSelectedObj: make exactly one object of a window group the
 * selected one.  The window is locked, its far bucket comes from
 * win_handles (object count at +0xc, far object pointer table at +0x2c),
 * and every object whose group byte (+0x20) equals the requested group is
 * selected through win_SetObjSelectedStateI(object, 1) when it is the
 * requested object and deselected through win_SetObjSelectedStateI(object, 0)
 * otherwise,
 * so the requested object becomes selected and its group mates are
 * deselected.  Object numbers are the window's high byte plus the index;
 * the loop keeps the object number and the index as induction values and
 * indexes the far table directly.  The window is unlocked afterwards.
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
extern void far win_SetObjSelectedStateI(int object, int selected);

void far win_SetGroupSelectedObj(int objectNumber, int group, int selectedObj)
{
    #define REG register
    REG int object;
    REG int i;
    struct WinBucket far *bucket;
    

    win_LockWin(objectNumber);
    object = objectNumber & 0xff00;
    i = 0;
    bucket = win_handles[objectNumber >> 8];
    for (; i < bucket->count; i++, object++) {
        if (bucket->objects[i]->group == (unsigned char)group) {
            if (selectedObj == object)
                win_SetObjSelectedStateI(object, 1);
            else
                win_SetObjSelectedStateI(object, 0);
        }
    }
    win_UnlockWin(objectNumber);
}
