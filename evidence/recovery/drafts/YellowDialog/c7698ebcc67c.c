/* Draw the selected yellow dialog prompt and handle its modal button action. */
struct WinRect { int left; int top; int right; int bottom; };
struct YellowPromptTable { unsigned char pad[0x5c]; char far *prompts[8]; };
struct Point { int x; int y; };
extern int __based(__segname("SIMANT_DATA_GROUP")) OptionStates[];
extern int near win_hwnd[];
extern unsigned char near displayType;
extern char near monoPat;
extern char far * far * far WindPromptStrs;
extern struct Point far YellowEatPnt;
extern void far win_LockWin(int window);
extern void far win_UnlockWin(int window);
extern void far win_SetObjBitmap(int object, int bitmap);
extern void far win_Open(int window);
extern void far win_Close(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern void far myDelay(unsigned long ticks);
extern int far win_Events(void);
extern void far DialogWaitInit(int mode);
extern int far DialogAbortOrCont(int capture);
extern void far DialogDone(void);
extern void far win_FlushEvents(void);
extern int far pascal IsWindowVisible(unsigned int window);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far UpdateAllWindows(void);

void far YellowDialog(int bitmap, int promptIndex)
{
    struct WinRect rect;
    int captured;
    volatile int left;
    register int top;

    if (OptionStates[3] == 0)
        goto cleanup;
    win_LockWin(0x1a00);
    win_SetObjBitmap(0x1a01, bitmap);
    win_Open(0x1a00);
    captured = MySetCapture(win_hwnd[2]);
    win_GetObjRect(0x1a01, &rect);
    left = rect.left;
    top = rect.top;

    switch (bitmap) {
    case 0x238d:
        MSClipStart(win_hwnd[2]);
        font_SetFont(4);
        win_PrintfAtObj(0x1a02, WindPromptStrs[0x17 + promptIndex]);
        font_SetFont(0);
        MSClipEnd();
        /* fall through */
    case 0x238c:
        if (displayType & 1) {
            MSClipStart(win_hwnd[2]);
            font_SetFont(4);
            win_PrintfAtObj(0x1a02, WindPromptStrs[0x17 + promptIndex]);
            font_SetFont(0);
            MSClipEnd();
        }
        myDelay(0x12c);
        if (!win_Events()) {
            DialogWaitInit(3);
            while (!DialogAbortOrCont(captured)) {
                if (!win_Events()) continue;
                DialogDone();
                win_FlushEvents();
                win_UnlockWin(0x1a00);
                if (captured && IsWindowVisible(captured)) MySetCapture(captured);
                else MyReleaseCapture();
                break;
            }
        }
        break;
    case 0x2396:
        myBeginSound(0x7e, 0, 0x2a);
        monoPat &= 0x7f;
        win_DrawBitMap(left + YellowEatPnt.x, top + YellowEatPnt.y, 0x2397);
        win_UnlockWin(0x1a00);
        myBeginSound(0x7e, 0, 0x2d);
        break;
    default:
        myDelay(0x12c);
        win_Events();
        break;
    }
cleanup:
    MyReleaseCapture();
    win_Close(0x1a00);
    UpdateAllWindows();
}




