/*
 * LionDialog: shows the antlion-trap warning dialog (window 0x1a00,
 * simant:6A38) with an animated bitmap, but only when SIMANT_DATA_GROUP
 * OptionStates[3] (offset 0x85f8) is set (a trap actually triggered); returns
 * immediately when it is zero. Opens the window, captures the mouse on
 * win_hwnd[26] (0xbcda), starts sound 0x26 and busy-waits for
 * mySoundIsDone() to go true before entering the animation loop
 * (MacTickCount-based 300ms overall / 30ms per-frame timers, exiting
 * early on any window event or the 300ms deadline). Each animation tick
 * clips to win_hwnd[26], draws the lion bitmap (mono path via
 * displayType==0xa, or a per-frame offset from LionTrapPnts[frame]
 * otherwise), plays a step sound (0x25) on odd frames, and advances the
 * 0..3 frame counter (wrapping to 2). On exit, flushes events, unlocks
 * and closes the window, restores or releases the prior mouse capture,
 * and refreshes all windows.
 */
extern int far OptionStates[];
extern int near win_hwnd[];
extern unsigned char near monoPat;
extern unsigned char near displayType;

struct WinRect { int left; int top; int right; int bottom; };
struct LionPnt { int y; int x; };

extern int far LionTrapPnts[];

extern void far win_LockWin(int window);
extern void far win_SetObjBitmap(int object, unsigned int bitmap);
extern void far win_Open(int window);
extern int far MySetCapture(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far mySoundIsDone(void);
extern unsigned long far MacTickCount(void);
extern void far win_FlushEvents(void);
extern int far win_Events(void);
extern int far win_IsWinOpen(int window);
extern int far pascal ISWINDOWVISIBLE(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far win_UnlockWin(int window);
extern void far MyReleaseCapture(void);
extern void far win_Close(int window);
extern void far UpdateAllWindows(void);

void far LionDialog(void)
{
    struct WinRect rect;
    int captured;
    int x0, y0;
    int frame;
    long t1, t2;

    if (OptionStates[3] == 0)
        return;

    win_LockWin(0x1a00);
    win_SetObjBitmap(0x1a01, 0x23f0);
    win_Open(0x1a00);
    captured = MySetCapture(win_hwnd[26]);
    win_GetObjRect(0x1a01, &rect);
    x0 = rect.top;
    y0 = rect.left;

    myBeginSound(0x26, 0, 0x7e);

    while (!mySoundIsDone())
        ;

    frame = 1;
    t1 = MacTickCount() + 0x12c;
    t2 = MacTickCount() + 0x1e;

    win_FlushEvents();
    monoPat &= 0x7f;
    if (!win_Events()) {
        for (;;) {
            if ((long)MacTickCount() >= (long)t1)
            break;
        if (!win_IsWinOpen(0x1a00))
            break;
        if ((long)MacTickCount() >= (long)t2) {
            t2 = MacTickCount() + 0x1e;

            MSClipStart(win_hwnd[26]);
            if (displayType == 0xa) {
                win_DrawBitMap(y0, x0, 0x23f0 + frame);
            } else {
                win_DrawBitMap(LionTrapPnts[frame * 2] + y0,
                                LionTrapPnts[frame * 2 + 1] + x0, 0x23f0 + frame);
            }
            MSClipEnd();

            if (frame & 1)
                myBeginSound(0x25, 0, 0x7e);

            frame++;
            if (frame > 3)
                frame = 2;
        }
            if (win_Events())
                break;
        }
    }

    win_FlushEvents();
    win_UnlockWin(0x1a00);

    if (captured != 0 && ISWINDOWVISIBLE(captured))
        MySetCapture(captured);
    else
        MyReleaseCapture();

    win_Close(0x1a00);
    UpdateAllWindows();
}
