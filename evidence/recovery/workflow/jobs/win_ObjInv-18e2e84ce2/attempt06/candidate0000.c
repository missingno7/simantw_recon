/*
 * Hypothesis: window objects are bucketed by the signed high byte of the
 * packed object number.  Each bucket is a far table with a 0x2c-byte header
 * followed by 256 far rectangle pointers indexed by the low byte.  Invert
 * the selected rectangle while its window bucket is locked.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};

extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far GRectInv(struct WinRect far *rect);
extern void far win_UnlockWin(int objectNumber);

void win_ObjInv(int objectNumber)
{
    win_LockWin(objectNumber);
    GRectInv(win_handles[objectNumber >> 8]->rects[
        objectNumber & 0xff]);
    win_UnlockWin(objectNumber);
}
