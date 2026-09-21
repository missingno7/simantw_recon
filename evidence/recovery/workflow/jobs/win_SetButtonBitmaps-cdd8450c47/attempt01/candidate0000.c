struct WinButtonObject {
    unsigned char reserved[0x21];
    unsigned char objectType;
    unsigned char gap[6];
    unsigned int bitmapUp;
    unsigned int bitmapDown;
};

extern void far win_LockWin(int objectNumber);
extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far Punt(char far *message, ...);

void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                              unsigned int bitmapDown)
{
    struct WinButtonObject far *button;

    win_LockWin(objectNumber);
    button = win_ObjAddr(objectNumber);
    if (button->objectType != 13)
        Punt("win_SetButtonBitmaps: object is not a button");
    button->bitmapUp = bitmapUp;
    button->bitmapDown = bitmapDown;
    win_UnlockWin(objectNumber);
}
