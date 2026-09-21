/*
 * win_MakeGroupSelectable: set the selectable bit (bit 1 of the state byte
 * at +0x24, as in the verified win_SetObjSelectableState declaration) for
 * every object of a window whose group byte (+0x20) equals the requested
 * group.  The window number is masked to its high byte into a local that
 * indexes win_handles (the optimizer folds the masked shift), the far
 * bucket comes from win_handles (as in the admitted win_GetObjRect;
 * object count at +0xc, far object pointer table at +0x2c), and the
 * count and index are locals: the loop optimizer turns the indexed walk
 * into a CX countdown over a DS:SI table pointer while ES addresses each
 * object.  Locals are declared entry, count, index, bucket, window to
 * give the observed frame layout ([bp-4], [bp-6], [bp-8], [bp-0xc],
 * [bp-0xe]).  The window is locked around the update.
 */
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

extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

void far win_MakeGroupSelectable(int objectNumber, int group)
{
    struct WinObject far * far *entry;
    int count;
    int i;
    struct WinBucket far *bucket;
    int window;

    win_LockWin(objectNumber);
    window = objectNumber & 0xff00;
    bucket = win_handles[window >> 8];
    i = 0;
    if (bucket->count > 0) {
        entry = bucket->objects;
        count = bucket->count;
        do {
            if ((*entry)->group == (unsigned char)group)
                (*entry)->state |= 2;
            entry++;
            i++;
        } while (i < count);
    }
    win_UnlockWin(objectNumber);
}

