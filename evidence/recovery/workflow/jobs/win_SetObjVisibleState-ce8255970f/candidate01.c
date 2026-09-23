struct GameObject {
    unsigned char reserved0[0x21];
    unsigned char type;
    unsigned char reserved1[2];
    unsigned int flags;
    unsigned int bitmap[2];
    unsigned char reserved2[0x20];
};

struct BitmapObject {
    unsigned int bitmapOffset;
    unsigned int bitmapArgument;
    unsigned char reserved[0x20];
    unsigned char flags;
};

extern struct GameObject far * far win_ObjAddr(int objectNumber);
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far GRectInv(struct GameObject far *object);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far win_DrawBitMapAtObj(struct BitmapObject far *object, int value);
extern void win_DrawObject(struct GameObject far *object);
extern int near clipDC;
extern int near win_hwnd[];
extern int near __backColor;
extern int near __foreColor;
extern unsigned char near monoPat;

void far win_SetObjVisibleState(int objectNumber, int state)
{
    struct GameObject far *object;
    int clipStarted;
    int type;
    int bitmapNumber;

    object = win_ObjAddr(objectNumber);
    if ((object->flags & 1) == state)
        return;
    object->flags ^= ((object->flags & 1) ^ state) & 1;

    if (!win_IsWinOpen(objectNumber))
        return;
    if ((object->flags & 1) == 0)
        return;
    if ((object->flags & 4) == 0)
        return;

    clipStarted = 0;
    if (clipDC == 0) {
        MSClipStart(win_hwnd[objectNumber >> 8]);
        clipStarted = 1;
    }

    type = object->type;
    if (type == 0x11) {
        GRectInv(object);
    } else if (type == 1) {
        win_DrawObject(object);
    } else if (type == 5) {
        GRectInv(object);
    } else if (type == 13) {
        GSetAttrib(__foreColor, __backColor, monoPat & 0x7f);
        bitmapNumber = object->bitmap[(object->flags & 4) ? 1 : 0];
        win_DrawBitMapAtObj((struct BitmapObject far *)object, bitmapNumber);
    }

    if (clipStarted)
        MSClipEnd();
}
