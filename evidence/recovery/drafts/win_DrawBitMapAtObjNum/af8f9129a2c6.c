/*
 * Hypothesis: lock the requested window, resolve its far object record, and
 * draw the object's bitmap only when the state byte at offset 0x24 has bit 1
 * set.  The first two words of this object are the bitmap handles passed to
 * win_DrawBitMap.  If that draw reports failure, the object rectangle is
 * filled with monoPat OR __foreColor, then the window is unlocked.
 */
struct WinBitmapObject {
    unsigned int bitmap;
    unsigned int bitmapMask;
    unsigned char reserved[0x20];
    unsigned char state;
};

extern void far win_LockWin(int objectNumber);
extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);
extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask,
                              int bitmapNumber);
extern void far GRectFill(void far *object, int color);
extern void far win_UnlockWin(int objectNumber);
extern char near monoPat;
extern int near _foreColor;

void far win_DrawBitMapAtObjNum(int objectNumber, int bitmapNumber)
{
    struct WinBitmapObject far *object;
    int color;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (object->state & 1) {
        if (!win_DrawBitMap(object->bitmap, object->bitmapMask,
                            bitmapNumber)) {
            color = monoPat | _foreColor;
            GRectFill(object, color);
        }
    }
    win_UnlockWin(objectNumber);
}
