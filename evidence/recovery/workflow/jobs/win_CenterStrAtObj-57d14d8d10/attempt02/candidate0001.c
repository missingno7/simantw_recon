/*
 * win_CenterStrAtObj: draw a string centred in a window object.  The
 * object's drawing attributes are selected, its window is locked and the
 * object's four-word rectangle is copied out of the window bucket's far
 * rectangle table (the DS switch around four MOVSW), grown by one on the
 * right and bottom while the ribbon bar is active, and the window is
 * unlocked.  The clip DC is saved, clipped to that rectangle, the string
 * is drawn centred (clearing the rectangle first) and the DC restored.
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
extern int near clipDC;

extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern int far pascal SaveDC(int dc);
extern int far pascal IntersectClipRect(int dc, int left, int top, int right, int bottom);
extern int far pascal RestoreDC(int dc, int saved);
extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);

void far win_CenterStrAtObj(int objectNumber, char far *text)
{
    struct WinRect rect;
    struct WinBucket far *bucket;

    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[objectNumber & 0xff];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);
    SaveDC(clipDC);
    IntersectClipRect(clipDC, rect.left, rect.top, rect.right, rect.bottom);
    gr_CenterStrInRectClear(&rect, text);
    RestoreDC(clipDC, -1);
}
