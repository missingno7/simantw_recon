struct GameObject {
    unsigned int left;
    unsigned int top;
    unsigned char reserved0[0x1d];
    unsigned char type;
    unsigned char reserved1[2];
    unsigned int flags;
    unsigned int bitmap[2];
    unsigned int bitmapValue;
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
extern int far win_DrawBitMap(int bitmapOffset, int bitmapArgument, int value);
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
    unsigned char type;
    int bitmapNumber;

    object = win_ObjAddr(objectNumber);
    if ((object->flags & 1) == state)
        return;
    object->flags ^= ((object->flags & 1) ^ state) & 1;

    if (!win_IsWinOpen(objectNumber))
        return;

    if ((object->flags & 1) && (object->flags & 4)) {
        clipStarted = 0;
        if (clipDC == 0) {
            MSClipStart(win_hwnd[objectNumber >> 8]);
            clipStarted = 1;
        }

        type = object->type;
        /* The target's subtract/decrement chain dispatches these four types. */
        if (type == 0x11) {
            GRectInv(object);
        } else if (type <= 0x11) {
            if (type == 1)
                win_DrawObject(object);
            else {
                type -= 1;
                if (type == 4)
                    GRectInv(object);
                else {
                    type -= 4;
                    if (type == 8) {
                        GSetAttrib(__foreColor, __backColor, monoPat & 0x7f);
                        bitmapNumber = object->bitmap[(object->flags & 4) == 0];
                        win_DrawBitMapAtObj((struct BitmapObject far *)object,
                                            bitmapNumber);
                    }
                }
            }
        }

        if (clipStarted)
            MSClipEnd();
    } else {
        clipStarted = 0;
        if (clipDC == 0) {
            MSClipStart(win_hwnd[objectNumber >> 8]);
            clipStarted = 1;
        }

        if (object->type == 13) {
            GSetAttrib(__foreColor, __backColor, monoPat & 0x7f);
            win_DrawBitMap(object->left, object->top,
                           object->bitmapValue);
        }

        if (clipStarted)
            MSClipEnd();
    }
}

