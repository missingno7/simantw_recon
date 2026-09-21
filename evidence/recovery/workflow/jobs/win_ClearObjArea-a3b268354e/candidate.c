/*
 * win_ClearObjArea: fill a window object's rectangle with its colour.  The
 * packed object number selects the far bucket (high byte) and the far
 * rectangle pointer (low byte) exactly as in the admitted win_GetObjRect;
 * the four words are copied into a local rectangle with the DS switch
 * around MOVSW, and the active ribbon bar adds one to right and bottom.
 * After unlocking, win_SetColorFromObjNum selects the object's colour and
 * win_RectFill paints the local rectangle passed as a far pointer.  All
 * four callees are same-code-group far functions (LINK translation).
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
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_RectFill(struct WinRect far *rect);

void far win_ClearObjArea(int objectNumber)
{
    struct WinRect rect;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);
    win_SetColorFromObjNum(objectNumber);
    win_RectFill(&rect);
}
