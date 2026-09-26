/*
 * win_PrintfAtObj: format a message and draw it centred in a window
 * object.  The variable arguments (the address just past the format
 * pointer) are formatted with the C runtime vsprintf into a 100-byte
 * stack buffer; then, as in win_CenterStrAtObj, the object's drawing
 * attributes are selected, its window locked, its four-word rectangle
 * copied out of the window bucket's far rectangle table (DS switch
 * around four MOVSW), grown by one on the right and bottom while the
 * ribbon bar is active, the window unlocked, the clip DC saved and
 * clipped to the rectangle, the text drawn centred with clearing, and
 * the DC restored.
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

extern int far vsprintf(char far *buffer, char far *format, char far *args);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern int far pascal SaveDC(int dc);
extern int far pascal IntersectClipRect(int dc, int left, int top, int right, int bottom);
extern int far pascal RestoreDC(int dc, int saved);
extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);

void far win_PrintfAtObj(int objectNumber, char far *format, ...)
{
    struct WinRect rect;
    char buffer[100];
    struct WinBucket far *bucket;

    vsprintf(buffer, format, (char far *)(&format + 1));
    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);
    SaveDC(clipDC);
    IntersectClipRect(clipDC, rect.left, rect.top, rect.right, rect.bottom);
    gr_CenterStrInRectClear(&rect, buffer);
    RestoreDC(clipDC, -1);
}
