/*
 * win_DrawVBar: draw a vertical progress bar inside a window object.
 * The object's drawing colour is selected, its window locked and the
 * object's four-word rectangle copied out of the window bucket's far
 * rectangle table (DS switch around four MOVSW), grown by one on the
 * right and bottom while the ribbon bar is active, then unlocked. A
 * split point is computed from a 16.16 fixed-point fraction of the
 * rectangle height, measured from the bottom edge upward; the bottom
 * part from the split down to the bottom is filled in the foreground
 * colour, the remainder from the original top up to the split is
 * filled in the background colour.
 */
struct WinRect {
    int left;
    register int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};

extern struct WinBucket far * near win_handles[];
extern int near ribbonBarHeight;
extern int near _foreColor;
extern int near _backColor;

extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far GRectFill(void far *object, int color);

void far win_DrawVBar(int objectNumber, long fraction)
{
    struct WinRect rect;
    struct WinBucket far *bucket;
    register int top;

    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);

    top = rect.top;

    {
        int height;
        height = rect.bottom - top;
        rect.top = rect.bottom - (int)(((long)height * fraction) / 65536L);
    }

    if (rect.top < rect.bottom) {
        GRectFill(&rect, _foreColor);
    }
    if (rect.top > top) {
        rect.bottom = rect.top;
        rect.top = top;
        GRectFill(&rect, _backColor);
    }
}
