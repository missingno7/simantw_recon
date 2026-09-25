/*
 * win_ClearObjToEOL: clear a window object's row from the last printed
 * string position to the end of the object's rectangle.  The window is
 * locked (twice, as in the original), the object's four-word rectangle is
 * fetched from the bucket's far rects[] table exactly as in the admitted
 * win_GetObjRect/win_ClearObjArea/win_CenterStrAtObj (DS switch around
 * four MOVSW), grown by one on right/bottom while the ribbon bar is
 * active, and the window is unlocked.  The bucket is then reloaded and
 * reinterpreted as the win_ObjAddr bucket shape: if the packed object's
 * low byte is out of the bucket's objectCount, Punt reports the same
 * "Attempt to get obj address outsize window" message used by win_ObjAddr
 * (same DGROUP string literal); otherwise the object pointer is taken from
 * bucket->objects[] and reinterpreted as the win_SetColorFromObj colour
 * object to read its colour index byte at +0x26.  The colour table entry
 * (PACK win_colors[][6], byte 2 for mono display, byte 3 for colour
 * display, replicated into a word by *0x101 exactly as in
 * win_SetColorFromObj) becomes the fill colour.  lastStrPos (the far PACK
 * StrPos used by font_PrintStr) supplies the fill origin: y is clamped up
 * to rect.top, and when rect.bottom is still below the clamped y and x
 * lies within [rect.left, rect.right) the box from (x, y) to
 * (rect.right, rect.bottom) is filled with GBoxFill before the final
 * unlock.
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

struct WinObjectBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    void far *objects[256];
};

struct WinColorObject {
    unsigned char reserved[0x24];
    unsigned int flags;
    char color;
    char altColor;
};

struct StrPos {
    int x;
    int y;
};

extern struct WinBucket far * near win_handles[];
extern int near ribbonBarHeight;
extern unsigned char near displayType;
extern char far win_colors[][6];
extern struct StrPos far lastStrPos;

extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far Punt(char far *message, ...);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);

void far win_ClearObjToEOL(int objectNumber)
{
    struct WinBucket far *bucket;
    struct WinObjectBucket far *objBucket;
    struct WinColorObject far *object;
    struct WinRect rect;
    int index;
    int color;
    int x, y;

    win_LockWin(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);

    objBucket = (struct WinObjectBucket far *)win_handles[objectNumber >> 8];
    if (objBucket->objectCount <= (unsigned char)objectNumber)
        Punt("Attempt to get obj address outsize window");
    object = (struct WinColorObject far *)objBucket->objects[(unsigned char)objectNumber];

    index = object->color;
    if ((displayType & 1) == 0)
        color = win_colors[index][2] * 0x101;
    else
        color = win_colors[index][3] * 0x101;

    y = lastStrPos.y;
    if (y < rect.top)
        y = rect.top;
    if (rect.bottom > y) {
        x = lastStrPos.x;
        if (x >= rect.left && x < rect.right)
            GBoxFill(x, y, rect.right, rect.bottom, color);
    }

    win_UnlockWin(objectNumber);
}
