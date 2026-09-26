/* Run the spider animation dialog, then display its selected picture text. */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near win_hwnd[];
extern unsigned char far AnTab[];
extern unsigned char near monoPat;
extern void far win_LockWin(int objectNumber);
extern void far win_SetObjBitmap(int objectNumber, unsigned int bitmap);
extern void far win_Open(int objectNumber);
extern void far win_Close(int objectNumber);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far win_GetObjRect(int objectNumber, struct WinRect far *rect);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern long near MacTickCount(void);
extern void near DialogWaitInit(int waitValue);
extern int near DialogAbortOrCont(void);
extern int far win_Events(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void near DialogDone(void);
extern int far SRand1(int range);
extern void near StopSimulation(void);
extern char far * far * far LoadStringAnt(int object);
extern void far PictureDialog(char far * far *strings, int count, int picture, int force);
extern void far free(void far *block);
extern void far db_PurgeObject(int object, int kind);
extern void near RestartSimulation(void);
extern void far win_FlushEvents(void);
extern void far win_UnlockWin(int objectNumber);
extern int far pascal IsWindowVisible(unsigned int window);
extern void far UpdateAllWindows(void);

void far SpiderDialog(void)
{
    struct WinRect rect;
    long deadline;
    int capturedWindow;
    int frame;
    int bitmap;
    int stringObject;
    int stringCount;
    char far * far *strings;

    win_LockWin(0x1a00);
    win_SetObjBitmap(0x1a01, 0x2ee0);
    win_Open(0x1a00);
    capturedWindow = MySetCapture(win_hwnd[42]);
    win_GetObjRect(0x1a01, &rect);
    myBeginSound(0x2d, frame = 0, 0x7e);

    MacTickCount();
    deadline = MacTickCount() + 8L;
    DialogWaitInit(8);

    bitmap = AnTab[frame] + 0x2ee1;
    rect.left += 0x2e;
    rect.top += 0x4d;
    monoPat &= 0x7f;

    for (;;) {
        if (DialogAbortOrCont())
            break;
        if (win_Events())
            break;

        if (MacTickCount() < deadline)
            continue;

        deadline = MacTickCount() + 8L;
        ++frame;
        if (frame <= 3) {
            bitmap = AnTab[frame] + 0x2ee1;
        } else {
            frame = 0;
            myBeginSound(0x2d, frame, 0x7e);
            bitmap = AnTab[frame] + 0x2ee1;
        }

        MSClipStart(win_hwnd[42]);
        win_DrawBitMap(rect.left, rect.top, bitmap);
        MSClipEnd();
        if (DialogAbortOrCont())
            break;
    }

    DialogDone();
    stringObject = 0x2740 - (SRand1(2) == 0);
    if (bitmap != 0) {
        MSClipStart(win_hwnd[42]);
        win_DrawBitMap(rect.left, rect.top, bitmap);
        MSClipEnd();
    }

    StopSimulation();
    strings = LoadStringAnt(stringObject);
    stringCount = 0;
    if (strings != 0) {
        while (strings[stringCount] != 0)
            ++stringCount;
    }
    PictureDialog(strings, stringCount, 0, 1);
    if (strings != 0) {
        free(strings);
        db_PurgeObject(stringObject, 4);
    }

    RestartSimulation();
    win_FlushEvents();
    win_UnlockWin(0x1a00);
    if (capturedWindow != 0 && IsWindowVisible(capturedWindow))
        MySetCapture(capturedWindow);
    else
        MyReleaseCapture();
    win_Close(0x1a00);
    UpdateAllWindows();
}
