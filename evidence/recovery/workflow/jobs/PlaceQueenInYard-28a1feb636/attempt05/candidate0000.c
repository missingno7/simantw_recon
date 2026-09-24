/*
 * Evidence hypothesis: the target pauses the yard simulation while the user
 * chooses a blue queen placement. It tracks the pointer over a clamped 7x7
 * area around CurYardPnt, then updates the blue yard counts on a valid click.
 * The event layout and screen-to-yard transform follow admitted event and
 * yard cursor sources; StopSimulation/RestartSimulation are MAPSYM-resolved.
 */
struct YardPoint { int x, y; };
struct YardRect { int left, top, right, bottom; };
struct YardEvent {
    unsigned char unused[8];
    int x;
    int y;
    int object;
    int extra;
};

extern int near QueenStorageB;
extern int near win_hwnd[];
extern int far CurGameType;
extern int far LayDownQueenMode;
extern struct YardPoint far CurYardPnt;
extern struct YardPoint far YMapPnt;
extern struct YardRect far mapTileRect;
extern struct YardPoint near patchRgn;
extern char far * far * far WindPromptStrs;
extern unsigned char far YMapPopB[12][16];
extern int far BColoniesStarted;
extern int far ColonyUpdateFlag;

extern void near StopSimulation(void);
extern void near RestartSimulation(void);
extern void far myBeginSound(unsigned int sound, unsigned int channel,
                             unsigned int priority);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far win_FlushEvents(void);
extern int far win_GetEvent(struct YardEvent far *event);
extern int far GetMousePos(struct YardPoint far *point);
extern int far pascal ScreenToClient(int window, struct YardPoint far *point);
extern int far win_IsWinInFront(int window);
extern void far MSClipStart(int window);
extern void far InvertPatch(int x, int y);
extern void far MSClipEnd(void);
extern void near EditMessage(long message, int x, int y, int mode);
extern void near MakeDMap(int mode);
extern void far DrawMap(void);
extern void far UpdateYard(void);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern void near myDelay(int ticks);

void far PlaceQueenInYard(void)
{
    struct YardEvent event;
    struct YardPoint point;
    int left;
    int right;
    int top;
    int bottom;
    int col;
    int row;
    int cursorCol;
    int cursorRow;
    int prevCol;
    int prevRow;
    int clicked;

    cursorCol = -1;
    if (QueenStorageB < 1) {
        myBeginSound(1, 0, 0x7e);
        EditMessage((long)WindPromptStrs[0x10], 0xb4, 0, 1);
        return;
    }
    if (CurGameType == 2) {
        EditMessage((long)WindPromptStrs[0x07], 0xb4, 0, 1);
        return;
    }
    if (LayDownQueenMode == 1)
        LayDownQueenMode = 0;

    left = CurYardPnt.x - 3;
    right = CurYardPnt.x + 3;
    top = CurYardPnt.y - 3;
    bottom = CurYardPnt.y + 3;
    if (left < 0)
        left = 0;
    if (left > 11)
        left = 11;
    if (right < 0)
        right = 0;
    if (right > 11)
        right = 11;
    if (top < 0)
        top = 0;
    if (top > 15)
        top = 15;
    if (bottom < 0)
        bottom = 0;
    if (bottom > 15)
        bottom = 15;

    StopSimulation();
    win_FlushEvents();
    EditMessage((long)WindPromptStrs[0x08], -2, -1, 1);
    prevCol = -1;
    prevRow = -1;
    clicked = 0;

    for (;;) {
        clicked = 0;
        if (win_GetEvent(&event) && event.object == 0x1902) {
            point.x = event.x;
            point.y = event.y;
            clicked = 1;
        } else {
            GetMousePos(&point);
            ScreenToClient(win_hwnd[25], &point);
            if (!win_IsWinInFront(0x1900))
                continue;
        }

        row = (point.y - mapTileRect.top - patchRgn.y) / 10;
        col = (row * 10 + point.x - mapTileRect.left - patchRgn.x) / 28;

        if (col < left || col > right || row < top || row > bottom) {
            if (cursorCol != -1) {
                MSClipStart(win_hwnd[25]);
                InvertPatch(cursorCol, cursorRow);
                MSClipEnd();
                cursorCol = -1;
            }
            prevCol = col;
            prevRow = row;
            continue;
        }

        if (col != prevCol || row != prevRow) {
            if (cursorCol != -1) {
                MSClipStart(win_hwnd[25]);
                InvertPatch(cursorCol, cursorRow);
                MSClipEnd();
            }
            prevCol = col;
            prevRow = row;
            cursorCol = col;
            cursorRow = row;
            YMapPnt.x = col;
            YMapPnt.y = row;
            MSClipStart(win_hwnd[25]);
            InvertPatch(col, row);
            MSClipEnd();
        }

        if (clicked) {
            myBeginSong(0x2afb, 0x7e);
            --QueenStorageB;
            ++YMapPopB[col][row];
            ++BColoniesStarted;
            ColonyUpdateFlag = 1;
            MakeDMap(1);
            DrawMap();
            EditMessage((long)WindPromptStrs[0x09], 0x78, 0, 1);

            if (QueenStorageB > 0)
                UpdateYard();
            EditMessage((long)WindPromptStrs[0x0a], 0x78, 0, 1);
            myBeginSound(1, 0, 0x7e);
            if (GetAsyncKeyState(0x10) & 0x8000) {
                myDelay(0x1e);
                if (GetAsyncKeyState(0x10) & 0x8000)
                    continue;
            } else if (GetAsyncKeyState(0x10) & 0x8000)
                continue;
            break;
        }
    }

    EditMessage(0L, -2, -1, 1);
    RestartSimulation();
}
