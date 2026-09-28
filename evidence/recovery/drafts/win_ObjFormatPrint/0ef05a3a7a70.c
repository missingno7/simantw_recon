struct RallocRecord {
    void far *data;
    unsigned int handle;
    long size;
    unsigned long tick;
    int tag;
};
/*
 * win_ObjFormatPrint: format and draw a window object's cached format
 * string, then draw it centred like win_CenterStrAtObj/win_PrintfAtObj.
 * The bucket/Punt bounds check follows the admitted win_ObjAddr shape;
 * bucket->objects[idx] is the object's FormatObject, whose flags bit 0
 * (+0x24) gates the format step.  vsprintf renders obj->fmt (+0x2e) with
 * the caller's varargs into a stack buffer -- called twice with identical
 * arguments, matching the observed duplicate call.  obj->buf (+0x2a) is a
 * Ralloc "handle" (a far pointer to the actual far text pointer, matching
 * the Ralloc/RallocRealloc "formatStr" growable-buffer family): if null,
 * Ralloc(1,len+8,"formatStr") creates it; otherwise the existing text's
 * strlen decides whether RallocRealloc(1,len+4,"formatStr") is needed;
 * either way the freshly rendered text is copied through the handle.
 * font_SetFont(obj->fontId) selects the object's font.  The object's
 * rectangle is then fetched exactly as win_CenterStrAtObj (DS switch
 * around four MOVSW, ribbon growth), and the handle's text is drawn
 * centred with SaveDC/IntersectClipRect/gr_CenterStrInRectClear/RestoreDC
 * before font_SetFont(0) resets the font and the window unlocks.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    unsigned char far *objects[256];
};

struct RectBucket {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};

struct FormatObject {
    unsigned char reserved[0x24];
    unsigned char flags;
    unsigned char pad1[0x28 - 0x25];
    signed char fontId;
    unsigned char pad2[0x2a - 0x29];
    struct RallocRecord far *buf;
    char fmt[1];
};

extern struct WinBucket far * near win_handles[];
extern int near ribbonBarHeight;
extern int near clipDC;

extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int);

extern void far Punt(char far *message, ...);
extern void far win_SetColorFromObjNum(int objectNumber);

extern void far font_SetFont(int fontId);
extern int far vsprintf(char far *buffer, char far *format, char far *args);

extern unsigned int strlen(const char far *text);

extern char far * far strcpy(char far *dst, char far *src);
extern struct RallocRecord far *far Ralloc(long size, int tag, char far *label);
extern struct RallocRecord far *far RallocRealloc(struct RallocRecord far *record,
                                            long size, int tag);

extern int far pascal SaveDC(int dc);
extern int far pascal IntersectClipRect(int dc, int left, int top, int right, int bottom);
extern int far pascal RestoreDC(int dc, int saved);
extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);

void far win_ObjFormatPrint(int objectNumber, ...)
{
    struct WinBucket far *bucket;
    struct FormatObject far *obj;
    struct RectBucket far *rbucket;
    struct WinRect rect;
    char buf[100];
    int id;
    int windowNumber;
    struct RallocRecord far *record;
    int len;
    void far *args;

    win_LockWin(objectNumber);
    id = objectNumber;
    bucket = win_handles[id >> 8];
    if (bucket->count <= (unsigned char)id)
        Punt("Attempt to get obj address outsize window");
    obj = (struct FormatObject far *)bucket->objects[(unsigned char)id];

    if (obj->flags & 1) {
        args = (void far *)(&objectNumber + 1);
        vsprintf(buf, obj->fmt, args);
        vsprintf(buf, obj->fmt, args);
        len = strlen(buf) + 1;
        record = obj->buf;
        if (record != 0) {
            if ((int)strlen((char far *)record->data) + 2 < len) {
                record = RallocRealloc(record, (long)(len + 4), 1);
                obj->buf = record;
            }
        } else {
            record = Ralloc((long)(len + 8), 1, "FormatStr");
            obj->buf = record;
        }
        strcpy((char far *)record->data, buf);
        font_SetFont(obj->fontId);

        windowNumber = objectNumber;
        win_SetColorFromObjNum(windowNumber);
        win_LockWin(windowNumber);
        rbucket = (struct RectBucket far *)win_handles[windowNumber >> 8];
        rect = *rbucket->rects[(unsigned char)windowNumber];
        if (ribbonBarHeight) {
            ++rect.right;
            ++rect.bottom;
        }
        win_UnlockWin(windowNumber);

        SaveDC(clipDC);
        IntersectClipRect(clipDC, rect.left, rect.top, rect.right, rect.bottom);
        gr_CenterStrInRectClear(&rect, buf);
        RestoreDC(clipDC, -1);
        font_SetFont(0);
    }

    win_UnlockWin(objectNumber);
}
