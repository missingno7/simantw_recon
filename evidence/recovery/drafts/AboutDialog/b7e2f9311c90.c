/*
 * AboutDialog saves the pause state, opens and captures the about window,
 * waits for input while flushing queued events, scrolls the loaded string
 * table through the text box, then releases the dialog resources.
 */
struct AboutRect { int left, top, right, bottom; };
extern int far GamePaused;
extern int near win_hwnd[];
extern int near clipDC;
extern int near _backColor;
extern char far * far * far LoadStringAnt(int object);
extern void far SetPause(int pause);
extern void far win_Open(int object);
extern int far MySetCapture(int window);
extern void far DialogClearWaitInit(void);
extern void far DialogClearWait(void);
extern void far DialogDone(void);
extern unsigned long far TickCount(void);
extern int far WaitedEnough(unsigned long far *stamp, int ticks);
extern int far DialogAbortOrCont(void);
extern int far win_Events(void);
extern void far win_FlushEvents(void);
extern void far win_GetObjRect(int object, struct AboutRect far *rect);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_DrawObjectNum(int object);
extern void far clip_ToRect(struct AboutRect far *rect);
extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal SelectClipRgn(int dc, int region);
extern int far pascal DeleteObject(int object);
extern void far win_SetColorFromObjNum(int object);
extern void far font_SetFont(int font);
extern int far font_FontHeight(void);
extern void far gr_JustifyStrInRect(struct AboutRect far *rect, char far *text, int align);
extern void far GBoxMove(int left, int top, int right, int bottom, int newLeft, int newTop);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);
extern void far clip_Off(void);
extern void far free(void far *block);
extern void far db_PurgeObject(int object, int kind);
extern void far MyReleaseCapture(void);
extern void far win_Close(int object);

void far AboutDialog(void)
{
    char far * far * far strings;
    unsigned long stamp;
    unsigned long eventCount;
    struct AboutRect rect;
    struct AboutRect lineRect;
    char far *current;
    int count;
    int page;
    int row;
    int rowHeight;
    int region;
    int oldPause;
    int event;
    int y;
    int width;

    eventCount = 0;
    oldPause = GamePaused;
    SetPause(1);
    win_Open(0x1f00);
    MySetCapture(win_hwnd[79]);
    strings = LoadStringAnt(0x6a4);
    count = 0;
    while (strings[count] != 0)
        ++count;

    DialogClearWaitInit();
    stamp = TickCount();
    DialogClearWait();
    while (!WaitedEnough(&stamp, 90)) {
        if (DialogAbortOrCont())
            break;
        event = win_Events();
        if (event)
            break;
        win_FlushEvents();
        ++eventCount;
        if (eventCount > 3)
            break;
    }

    if (count != 0) {
        font_SetFont(4);
        rowHeight = font_FontHeight();
        MSClipStart(win_hwnd[79]);
        win_GetObjRect(0x1f02, &rect);
        region = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
        SelectClipRgn(clipDC, region);
        DeleteObject(region);
        win_SetColorFromObjNum(0x1f02);
        width = rect.right - rect.left;
        y = rect.top;
        for (page = 0; page < count; ++page) {
            for (row = page; row < count; ++row) {
                current = strings[row];
                if (current == 0 || current[0] == 0)
                    break;
                lineRect = rect;
                lineRect.top = y;
                lineRect.bottom = y + rowHeight;
                gr_JustifyStrInRect(&lineRect, current, 3);
                GBoxFill(lineRect.left, lineRect.top, lineRect.right, lineRect.bottom, _backColor);
                y += rowHeight;
                if (y >= lineRect.bottom)
                    break;
            }
            if (page + 1 < count) {
                GBoxMove(lineRect.left, lineRect.top, lineRect.right, lineRect.bottom,
                         lineRect.left, lineRect.top + rowHeight);
                DialogClearWaitInit();
                stamp = TickCount();
                DialogClearWait();
                while (!WaitedEnough(&stamp, 1)) {
                    if (DialogAbortOrCont() || win_Events())
                        break;
                    win_FlushEvents();
                }
            }
            y = lineRect.top;
        }
        MSClipEnd();
    }

    clip_Off();
    MSClipStart(win_hwnd[79]);
    win_DrawObjectNum(0x1f02);
    MSClipEnd();
    DialogDone();
    free(strings);
    db_PurgeObject(0x6a4, 4);
    win_FlushEvents();
    MyReleaseCapture();
    win_Close(0x1f00);
    SetPause(oldPause);
}
