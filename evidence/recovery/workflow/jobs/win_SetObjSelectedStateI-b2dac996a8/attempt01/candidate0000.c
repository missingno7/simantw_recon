/*
 * Set or clear an object's selected state. The state byte's bit 2 stores
 * selection, bit 0 marks a visible object, and the type at +0x21 selects
 * the redraw path. The window handle and drawing globals are MAPSYM-backed.
 */
struct WinObject {
    unsigned char reserved0[0x21];
    unsigned char type;
    unsigned char reserved1[2];
    unsigned char state;
    unsigned char reserved2[1];
    unsigned int bitmap[2];
};

extern int near clipDC;
extern int near win_hwnd[];
extern unsigned char near monoPat;
extern int near _backColor;
extern int near _foreColor;
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern struct WinObject far * far win_ObjAddr(int objectNumber);
extern int far win_IsWinOpen(int objectNumber);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far GRectInv(struct WinObject far *object);
extern void far win_DrawObject(struct WinObject far *object);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far win_DrawBitMapAtObj(struct WinObject far *object, int bitmap);

void far win_SetObjSelectedStateI(int objectNumber, int selected)
{
    struct WinObject far *object;
    int clipping;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (win_IsWinOpen(objectNumber)) {
        if (((object->state & 4) >> 2) != selected) {
            object->state ^= (object->state ^ (selected << 2)) & 4;
            if (object->state & 1) {
                clipping = 0;
                if (clipDC == 0) {
                    MSClipStart(win_hwnd[objectNumber >> 8]);
                    clipping = 1;
                }
                if (object->type == 0x11 || object->type == 5) {
                    GRectInv(object);
                } else if (object->type == 0x0d) {
                    /* bitmap path below */
                } else {
                    win_DrawObject(object);
                }
                if (clipping)
                    MSClipEnd();
            } else if (object->type == 0x0d) {
                clipping = 0;
                if (clipDC == 0) {
                    MSClipStart(win_hwnd[objectNumber >> 8]);
                    clipping = 1;
                }
                if (object->type == 0x0d) {
                    GSetAttrib(_foreColor, _backColor, monoPat & 0x7f);
                    win_DrawBitMapAtObj(object, object->bitmap[(object->state & 4) ? 1 : 0]);
                }
                if (clipping)
                    MSClipEnd();
            }
        }
    }
    win_UnlockWin(objectNumber);
}
