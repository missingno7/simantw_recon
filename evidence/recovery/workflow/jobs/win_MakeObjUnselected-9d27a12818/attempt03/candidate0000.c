/*
 * win_MakeObjUnselected: deselect a window object, and if its exclusive-
 * select ("radio group") flag is set (+0x24 bit 0x20), first deselect every
 * other object in the same window bucket that shares its group byte (+0x20),
 * as in the admitted win_SetObjSelectedState/win_MakeGroupUnselected family
 * (win_handles bucket: object count at +0xc, far object-pointer table at
 * +0x2c).  The object is locked once for the flag/group read and, when the
 * group flag is set, locked again around the sibling scan before the common
 * unselect call and final unlock.
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

void far win_MakeObjUnselected(int objectNumber)
{
    register struct WinObject far *object;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (object->flags & 0x20) {
        struct WinObject far * far *p;
        int group;
        int window;
        int i;

        group = object->group;
        win_LockWin(objectNumber);
        window = objectNumber & 0xff00;
        i = 0;
        if (win_handles[objectNumber >> 8]->count > 0) {
            p = win_handles[objectNumber >> 8]->objects;
            do {
                if ((*p)->group == (unsigned char)group)
                    win_SetObjSelectedStateI(window, 0);
                p++;
                window++;
                i++;
            } while (i < win_handles[objectNumber >> 8]->count);
        }
        win_UnlockWin(objectNumber);
    }
    win_SetObjSelectedStateI(objectNumber, 0);
    win_UnlockWin(objectNumber);
}
