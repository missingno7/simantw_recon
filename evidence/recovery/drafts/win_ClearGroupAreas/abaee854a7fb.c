/*
 * win_ClearGroupAreas: clear the area of every object of a window whose group byte
 * (+0x20) equals the requested group.  The window number is masked to its
 * high byte into a local, the far bucket comes from win_handles (as in the
 * admitted win_GetObjRect; object count at +0xc, far object pointer table
 * at +0x2c), and each matching object area is cleared through
 * win_ClearObjArea(window + index); the loop optimizer keeps
 * window + index as an induction value in SI (its home is the window
 * local's slot) and the index in DI, with the table walked through a far
 * pointer temp advanced by four.  The window is locked around the update.
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
extern void far win_ClearObjArea(int objectNumber);

void far win_ClearGroupAreas(int objectNumber, int group)
{
    struct WinObject far * far * volatile entry;
    register int window;
    register int i;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    window = objectNumber & 0xff00;
    i = 0;
    bucket = win_handles[objectNumber >> 8];
    if (bucket->count > 0) {
        entry=bucket->objects;while(i<bucket->count){if((*entry)->group==(unsigned char)group)win_ClearObjArea(window);window++;entry++;i++;}
    }
    win_UnlockWin(objectNumber);
}


/* continuation round 04 loop forms variant 1 */
