/*
 * Selection state is bit 2 of the byte at object +0x24. Closed windows
 * still receive the state update; open windows redraw only visible objects.
 * Bitmap type 13 chooses the state-specific descriptor at +0x26/+0x28.
 */
struct WinObject {
    unsigned char reserved0[0x21];
    unsigned char type;
    unsigned char reserved1[2];
    unsigned char state;
    unsigned char pad;
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
    int open;
    int clipping;
    int state;
    int type;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    open = win_IsWinOpen(objectNumber);
    state = object->state;
    if (open) {
        if (((state & 4) >> 2) != selected) {
            object->state ^= (state ^ (selected << 2)) & 4;
            state = object->state;
        }
        if (state & 1) {
            clipping = 0;
            if (clipDC == 0) {
                MSClipStart(win_hwnd[objectNumber >> 8]);
                clipping = 1;
            }
            type = object->type;
            if (type == 0x11) {
                win_DrawObject(object);
            } else if (type > 0x11) {
                GRectInv(object);
            } else if (type == 5) {
                win_DrawObject(object);
            } else if (type == 0x0d) {
                GSetAttrib(_foreColor, _backColor, monoPat & 0x7f);
                win_DrawBitMapAtObj(object, object->bitmap[(state & 4) ? 1 : 0]);
            } else {
                GRectInv(object);
            }
            if (clipping)
                MSClipEnd();
        }
    } else {
        object->state ^= (state ^ (selected << 2)) & 4;
    }
    win_UnlockWin(objectNumber);
}
