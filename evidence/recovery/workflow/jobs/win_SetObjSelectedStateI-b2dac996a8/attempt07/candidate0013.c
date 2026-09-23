struct WinObject {
    unsigned char beforeType[0x21];
    unsigned char type;
    unsigned char reserved[2];
    unsigned char state;
    unsigned char pad;
    unsigned int bitmap[3];
};
extern int near clipDC;
extern int near win_hwnd[];
extern unsigned char near monoPat;
extern int near _backColor;
extern int near _foreColor;
extern void far win_LockWin(int);
extern void far win_UnlockWin(int);
extern struct WinObject far * far win_ObjAddr(int);
extern int far win_IsWinOpen(int);
extern void far MSClipStart(int);
extern void far MSClipEnd(void);
extern void far GRectInv(struct WinObject far *);
extern void far win_DrawObject(struct WinObject far *);
extern void far GSetAttrib(int, int, int);
extern void far win_DrawBitMapAtObj(struct WinObject far *, int);

void far win_SetObjSelectedStateI(int objectNumber, int selected)
{
    register struct WinObject far *object;
    int clipping;
    char type;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (win_IsWinOpen(objectNumber)) {
        if (((object->state & 4) >> 2) != selected) {
            object->state = (object->state & 0xfb) | ((selected & 1) << 2);
            if (object->state & 1) {
                clipping = 0;
                if (clipDC == 0) {
                    MSClipStart(win_hwnd[objectNumber >> 8]);
                    clipping = 1;
                }
                type = object->type;
                if (type == 0x11) { win_DrawObject(object); } else if (type > 0x11) { GRectInv(object); } else if (type == 5) { win_DrawObject(object); } else if (type == 0x0d) { GSetAttrib(_foreColor, _backColor, monoPat & 0x7f); win_DrawBitMapAtObj(object, object->bitmap[1 + ((object->state & 4) == 0)]); } else { GRectInv(object); }
                if (clipping)
                    MSClipEnd();
            }
        } else if (object->state & 1) {
            clipping = 0;
            if (clipDC == 0) {
                MSClipStart(win_hwnd[objectNumber >> 8]);
                clipping = 1;
            }
            if (object->type == 0x0d) {
                GSetAttrib(_foreColor, _backColor, monoPat & 0x7f);
                win_DrawBitMapAtObj(object, 1 + ((object->state & 4) == 0));
            }
            if (clipping)
                MSClipEnd();
        }
    } else {
        object->state = (object->state & 0xfb) | ((selected & 1) << 2);
    }
    win_UnlockWin(objectNumber);
}
