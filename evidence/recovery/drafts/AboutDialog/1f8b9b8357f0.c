struct StrPos {
    int x;
    int y;
};
struct WinRect { int left; int top; int right; int bottom; };
/*
 * Pause the simulation, open and capture the about window, then pace the
 * resource string table through its clipped text object.  Each timed step
 * scrolls the already painted lines by one pixel and redraws the three text
 * bands that overlap the window rectangle.  Input and the clear-wait timer
 * share the same short event path, and the exit path releases every resource.
 */
struct AboutRect { int left, top, right, bottom; };
struct AboutTextPos { int x, y; };
extern int far GamePaused;
extern int far activeAppFlag;
extern int near win_hwnd[];
extern int near clipDC;
extern int near _backColor;
extern struct StrPos far lastStrPos;

extern char far * far * far LoadStringAnt(int object);
extern void far SetPause(int pause);
extern void far win_Open(int object);
extern int far MySetCapture(int window);
extern void far DialogClearWaitInit(void);
extern void far DialogClearWait(void);
extern void far DialogDone(void);
extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *timer, int delay);

extern int far DialogAbortOrCont(void);
extern int far win_Events(void);
extern void far win_FlushEvents(void);
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void win_DrawObjectNum(int objectNumber);

extern void far clip_ToRect(struct WinRect far *rect);
extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal SelectClipRgn(int dc, int region);
extern int far pascal DeleteObject(int object);
extern void far win_SetColorFromObjNum(int object);
extern void far font_SetFont(int font);
extern int far font_FontHeight(void);
extern void far gr_JustifyStrInRect(struct WinRect far *rect, char far *string, int justify);

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
    volatile long eventCount;
    struct AboutRect rect;
    struct AboutRect lineRect;
    int count;
    int page;
    int row;
    int pixels;
    int rowHeight;
    int region;
    int oldPause;
    int event;
    int y;
    int start;
    int end;
    int width;
    int delay;

    eventCount = 0;
    oldPause = GamePaused;
    SetPause(1);
    win_Open(0x1f00);
    MySetCapture(win_hwnd[31]);
    strings = LoadStringAnt(0x6a4);
    count = 0;
    while (strings[count] != 0)
        ++count;

    DialogClearWaitInit();
    stamp = TickCount();
    DialogClearWait();
    for (;;) {
        if (WaitedEnough(&stamp, 90))
            break;
        if (!DialogAbortOrCont()) {
            event = win_Events();
            if (!event)
                continue;
        }
        if (eventCount > 1)
            goto about_done;
        win_FlushEvents();
        break;
    }
    ++eventCount;
    win_GetObjRect(0x1f02, &rect);
    MSClipStart(win_hwnd[31]);
    win_DrawObjectNum(0x1f01);
    clip_ToRect(&rect);
    region = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
    SelectClipRgn(clipDC, region);
    DeleteObject(region);
    win_SetColorFromObjNum(0x1f02);

    if (count > 0 && !activeAppFlag) {
        page = 0;
        pixels = 0;
        rowHeight = 0;
        y = rect.top;
        while (page < count && !activeAppFlag) {
            while (pixels == 0 || pixels < rowHeight) {
                DialogClearWaitInit();
                stamp = TickCount();
                DialogClearWait();
                delay = (page == 0 && pixels == 1) ? 54 : 1;
                for (;;) {
                    if (WaitedEnough(&stamp, delay))
                        break;
                    if (!DialogAbortOrCont()) {
                        event = win_Events();
                        if (!event)
                            continue;
                    }
                    if (eventCount > 3)
                        goto about_done;
                    win_FlushEvents();
                    break;
                }
                ++eventCount;
                font_SetFont(4);
                rowHeight = font_FontHeight();
                win_GetObjRect(0x1f02, &rect);
                MSClipStart(win_hwnd[31]);
                win_DrawObjectNum(0x1f02);
                region = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
                SelectClipRgn(clipDC, region);
                DeleteObject(region);
                win_SetColorFromObjNum(0x1f02);
                y = rect.top - pixels;
                start = page;

                if (pixels != 0) {
                    GBoxMove(rect.left, rect.top, rect.right, rect.bottom,
                             rect.left, rect.top + 1);
                    y += rect.bottom - rect.top;
                    start += (rect.bottom - rect.top + rowHeight - 1) / rowHeight;
                    row = start;
                    if (row < count && y < rect.bottom && strings[row] != 0 && strings[row][0] != 0) {
                        lineRect.left = rect.left;
                        lineRect.top = y;
                        lineRect.right = rect.right;
                        lineRect.bottom = y + rowHeight;
                        gr_JustifyStrInRect(&lineRect, strings[row], 3);
                        GBoxFill(lastStrPos.x, y, rect.right, y + rowHeight, _backColor);
                    } else {
                        GBoxFill(rect.left, y, rect.right, y + rowHeight, _backColor);
                    }
                    end = page - 1;
                    y = rect.top - pixels - rowHeight;
                    if (end >= 0 && y >= rect.top && strings[end] != 0 && strings[end][0] != 0) {
                        lineRect.left = rect.left;
                        lineRect.top = y;
                        lineRect.right = rect.right;
                        lineRect.bottom = y + rowHeight;
                        gr_JustifyStrInRect(&lineRect, strings[end], 3);
                        GBoxFill(lastStrPos.x, y, rect.right, y + rowHeight, _backColor);
                    }
                } else {
                    row = start;
                    y = rect.top - pixels;
                    while (row < count && y <= rect.bottom) {
                        if (strings[row] == 0 || strings[row][0] == 0)
                            break;
                        lineRect.left = rect.left;
                        lineRect.top = y;
                        lineRect.right = rect.right;
                        lineRect.bottom = y + rowHeight;
                        gr_JustifyStrInRect(&lineRect, strings[row], 3);
                        GBoxFill(lastStrPos.x, y, rect.right, y + rowHeight, _backColor);
                        y += rowHeight;
                        ++row;
                    }
                }
                MSClipEnd();
                ++pixels;
            }
            pixels = 0;
            ++page;
            font_SetFont(0);
        }
    }

about_done:
    clip_Off();
    MSClipStart(win_hwnd[31]);
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



