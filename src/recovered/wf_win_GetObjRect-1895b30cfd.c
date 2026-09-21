/*
 * Hypothesis: the packed object number selects a far rectangle pointer from
 * the window bucket table.  Copying the four-word rectangle preserves the
 * target's DS switch around four MOVSW instructions; the active ribbon adds
 * one to the right and bottom output coordinates before unlocking.
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
extern int near ribbonBarHeight;
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

void far win_GetObjRect(int objectNumber, struct WinRect far *rect)
{
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    *rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect->right;
        ++rect->bottom;
    }
    win_UnlockWin(objectNumber);
}
