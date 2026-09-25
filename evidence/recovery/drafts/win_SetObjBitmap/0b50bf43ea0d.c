/*
 * win_SetObjBitmap: assign a bitmap number to a bitmap-type window object.
 * The packed object number selects the far bucket (high byte, win_handles
 * as in the admitted win_GetObjRect) and the object index (low byte).  An
 * index at or beyond the bucket's object count (+0xc) aborts through Punt
 * with the private literal "Attempt to get obj address outsize window";
 * the far object pointer comes from the table at +0x2c, and an object
 * whose type byte (+0x21) is not 6 aborts with "Attempt to set bitmap on
 * non-bitmap object".  Otherwise the bitmap word at +0x28 is stored.  The
 * window is locked around the update.
 */
struct WinObject {
    unsigned char reserved[0x21];
    unsigned char type;
    unsigned char pad[6];
    int bitmap;
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
extern void far Punt(char far *message, ...);

void far win_SetObjBitmap(int objectNumber, int bitmap)
{
    struct WinObject far *object;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if ((unsigned char)objectNumber >= bucket->count)
        Punt("Attempt to get obj address outsize window");
    object = bucket->objects[(unsigned char)objectNumber];
    if (object->type != 6)
        Punt("Attempt to set bitmap on non-bitmap object");
    object->bitmap = bitmap;
    win_UnlockWin(objectNumber);
}
