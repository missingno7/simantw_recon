/*
 * win_InvalidateObject: invalidate a window object's rectangle.  The packed
 * object number selects the far bucket (high byte) and the far rectangle
 * pointer (low byte) exactly as in the admitted win_GetObjRect and
 * win_ClearObjArea; the four words are copied into a local rectangle with
 * the DS switch around MOVSW, and the active ribbon bar adds one to right
 * and bottom.  After unlocking, InvalidateRect (USER ordinal 125, Pascal)
 * is called with the window handle from the named near win_hwnd table
 * indexed by the high byte, the local rectangle as a far pointer, and no
 * background erase.
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
extern int near win_hwnd[];
extern int near ribbonBarHeight;
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect,
                                      int erase);

void far win_InvalidateObject(int objectNumber)
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
    InvalidateRect(win_hwnd[objectNumber >> 8], &rect, 0);
}
