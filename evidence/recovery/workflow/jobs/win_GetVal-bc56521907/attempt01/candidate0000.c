/*
 * win_GetVal: read word `index` of a window object's data.  The window
 * is the high byte of the packed object number; a window at or beyond
 * the far PACK count win_numOfWindows is only accepted when the masked
 * window number is a special window (0x2800 or above), otherwise 0x8000
 * is returned.  The window is locked, its far bucket found through
 * win_handles (as in the admitted win_GetObjRect; object count at +0xc,
 * far object pointer table at +0x2c) and an object index at or beyond the
 * count returns 0x8000 after unlocking.  Otherwise the far object pointer
 * is fetched, the window unlocked, and the object's word at the given
 * index returned.
 */
struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    int far *objects[256];
};

extern struct WinBucket far * near win_handles[];
extern int far win_numOfWindows;
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

int far win_GetVal(int objectNumber, int index)
{
    int window;
    int object;
    struct WinBucket far *bucket;
    int far *values;

    window = objectNumber & 0xff00;
    if ((char)(objectNumber >> 8) >= win_numOfWindows && window < 0x2800)
        return 0x8000;
    win_LockWin(window);
    object = objectNumber & 0xff;
    bucket = win_handles[window >> 8];
    if (bucket->count <= object) {
        win_UnlockWin(window);
        return 0x8000;
    }
    values = bucket->objects[object];
    win_UnlockWin(window);
    return values[index];
}
