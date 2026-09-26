struct WinRect { int left; int top; int right; int bottom; };
extern unsigned int near casteBitmap[];
extern int near YardMode;
extern int near MapPlane;
extern int near win_hwnd[];
extern void far MapToYard(void);
extern void far SetYardMode(int mode);
extern void far SetMapPlane(int plane);
extern void far DrawYard(void);
extern void far myDelay(unsigned long ticks);
extern void far win_LockWin(int objectNumber);
extern void far win_SetObjBitmap(int objectNumber, unsigned int bitmap);
extern void far win_Open(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_UnlockWin(int window);
extern long far MacTickCount(void);
extern void far DialogWaitInit(int waitValue);
extern int far DialogAbortOrCont(void);
extern int far mySongIsDone(void);
extern void far myBeginSong(int song, int priority);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far DialogDone(void);
extern void far win_Close(int window);

void far DrawSimPayoff(void)
{
    struct WinRect rect;
    long nextFrame, deadline;
    int song, row, index;

    MapToYard();
    if (YardMode != 0)
        SetYardMode(0);
    if (MapPlane != 0)
        SetMapPlane(0);
    DrawYard();
    myDelay(0x96);

    win_LockWin(0x1a00);
    win_SetObjBitmap(0x1a01, 0x3f48);
    win_Open(0x1a00);
    win_GetObjRect(0x1a01, &rect);
    win_UnlockWin(0x1a00);

    song = 0x4e23;
    row = 1;
    nextFrame = MacTickCount() + 0x1eL;
    deadline = MacTickCount() + 0x258L;
    DialogWaitInit(10);

    for (;;) {
        if (DialogAbortOrCont())
            break;
        if (MacTickCount() >= deadline)
            break;
        if (mySongIsDone() && song < 0x4e25) {
            myBeginSong(song, 0x7e);
            ++song;
        }
        if (MacTickCount() >= nextFrame) {
            nextFrame = MacTickCount() + 8L;
            for (index = 17; index < 29; index += 2) {
                MSClipStart(win_hwnd[26]);
                win_DrawBitMap(rect.left + casteBitmap[index],
                               rect.top + casteBitmap[index - 1],
                               0x3f52 + row);
                MSClipEnd();
            }
            ++row;
            if (row >= 3)
                row = 0;
        }
    }

    DialogDone();
    myDelay(0x12c);
    win_Close(0x1a00);
}
