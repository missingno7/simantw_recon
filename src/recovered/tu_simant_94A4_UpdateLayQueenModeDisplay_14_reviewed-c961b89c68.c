/* Reviewed extension simant:94A4 with UpdateLayQueenModeDisplay and MapToYard: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_MapChanged, _SetMapTitle, _ClearMapScentButtons, _myDelay, _DialogClearWait, _DialogClearWaitInit, _DialogWait, _DialogWaitInit, _DialogAbort, _DialogAbortOrCont, _DialogDone, _DialogAbortAll
 * Exact additions: UpdateLayQueenModeDisplay and MapToYard. Queen-mode arrays are shared once in address order. */

struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
extern int far win_IsWinOpen(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern struct WinRect far mapTileRect;
extern int far mapForce;
extern int far MapMode;
extern int near YardMode;
extern char far * far * far MwinTitle;
extern void far win_SetObjFormatStr(int object, char far *text);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_DrawTitle(int object);
extern void far win_MakeGroupUnselected(int window, int group);
extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far win_Events(void);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern int near editMessage[];
#define dialogTimes delayStamps
#define dialogMessages delayWaits
#define dialogError dialogStrings
#define dialogOverflow (dialogStrings + 22)
#define dialogWaitError (dialogStrings + 53)
#define dialogWaitOverflow (dialogStrings + 75)
extern int near rootWnd;
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);
extern int far StillDown(void);
extern void far win_FlushEvents(void);

extern int far Dx8;  /* scaffold reference for pool word C0D2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int near win_hwnd[];
extern void far win_Swap(int first, int second);
extern void far win_Open(int flags);
extern void far SetMapPlane(int plane);
extern void far DrawYard(void);
extern void far pascal UpdateWindow(int window);
extern int far LayDownQueenMode;
extern void far win_SetGroupSelectedObj(int group, int selected, int object);
extern void far win_MakeObjSelected(int object);
extern int far LayDownQueenMode;
static int near layQueenGroupObjects[2] = {0x2309, 0x230a};
static int near layQueenObjects[2] = {0x190d, 0x190e};

void far MapToYard(void);
void far pool_stub_MacTickCount(void);
void DialogClearWait(void);
void DialogClearWaitInit(void);
void DialogWait(void);
void far DialogWaitInit(int waitValue);
int DialogAbort(void);
int DialogAbortOrCont(void);
void DialogDone(void);
void DialogAbortAll(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MacTickCount)
#pragma alloc_text(RUN2_TEXT, MapToYard)
#pragma alloc_text(RUN3_TEXT, DialogClearWait, DialogClearWaitInit, DialogWait, DialogWaitInit)
#pragma alloc_text(RUN3_TEXT, DialogAbort, DialogAbortOrCont, DialogDone, DialogAbortAll)



void far pool_stub_MacTickCount(void)
{
}

void far UpdateLayQueenModeDisplay(void)
{
    int index;

    clip_Push();
    if (win_hwnd[35]) {
        index = LayDownQueenMode == 0;
        win_SetGroupSelectedObj(0x2300, 3, layQueenGroupObjects[index]);
    } else {
        if (win_IsWinOpen(0x1900))
            clip_SetWin(0x1900);
        index = LayDownQueenMode == 0;
        win_MakeObjSelected(layQueenObjects[index]);
    }
    clip_Pop();
}

void win_MapChanged(void)
{
    if (!win_IsWinOpen(0x100))
        return;
    win_GetObjRect(0x102, &mapTileRect);
    mapForce = 1;
}

void far SetMapTitle(void)
{
    win_SetObjFormatStr(0x101, MwinTitle[MapMode]);
    win_SetObjFormatStr(0x1901, MwinTitle[YardMode + 9]);
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        win_DrawTitle(0x101);
        clip_Pop();
    } else if (win_IsWinOpen(0x1900)) {
        clip_Push();
        clip_SetWin(0x1900);
        win_DrawTitle(0x1901);
        clip_Pop();
    }
}

void ClearMapScentButtons(void)
{
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
    }
    win_MakeGroupUnselected(0x100, 2);
    if (win_IsWinOpen(0x100))
        clip_Pop();
}

static int near delayLevel = -1;
static long near delayStamps[8];
static unsigned int near delayWaits[8];
static char near dialogStrings[] = "SimAnt Internal Error\0DialogClearWaitInit - Overflow\0SimAnt Internal Error\0DialogWaitInit - Overflow";
void far myDelay(unsigned long ticks)
{
    long stamp;
    int done;

    stamp = TickCount();
    do {
        if (WaitedEnough(&stamp, (unsigned)ticks / 3))
            return;
        if (win_Events())
            return;
        if (WaitedEnough(&delayStamps[delayLevel], delayWaits[delayLevel]))
            done = 1;
        else
            done = GetAsyncKeyState(0x20) & 0x8000;
    } while (!done);
}

void far MapToYard(void)
{
    if (win_hwnd[25] != 0)
        goto open_yard;
    if (win_hwnd[1] == 0)
        goto open_yard;

    SetMapPlane(0);
    win_Swap(0x100, 0x1900);
    win_SetObjFormatStr(0x101, MwinTitle[MapMode]);
    win_SetObjFormatStr(0x1901, MwinTitle[YardMode + 9]);

    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        win_DrawTitle(0x101);
        clip_Pop();
    } else if (win_IsWinOpen(0x1900)) {
        clip_Push();
        clip_SetWin(0x1900);
        win_DrawTitle(0x1901);
        clip_Pop();
    }

    if (win_IsWinOpen(0x2200)) {
        win_Swap(0x2200, 0x2300);
        clip_Push();
        if (win_hwnd[35] != 0) {
            win_SetGroupSelectedObj(0x2300, 3,
                layQueenGroupObjects[!LayDownQueenMode]);
        } else {
            if (win_IsWinOpen(0x1900))
                clip_SetWin(0x1900);
            win_MakeObjSelected(layQueenObjects[!LayDownQueenMode]);
        }
        clip_Pop();
        UpdateWindow(win_hwnd[35]);
    }
    DrawYard();
    return;

open_yard:
    win_Open(0x1900);
    win_SetObjFormatStr(0x101, MwinTitle[MapMode]);
    win_SetObjFormatStr(0x1901, MwinTitle[YardMode + 9]);
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        win_DrawTitle(0x101);
        clip_Pop();
    } else if (win_IsWinOpen(0x1900)) {
        clip_Push();
        clip_SetWin(0x1900);
        win_DrawTitle(0x1901);
        clip_Pop();
    }
}

void DialogClearWait(void)
{
    unsigned long now;

    if (dialogMessages[editMessage[98]] != -1) {
        now = TickCount();
        dialogTimes[editMessage[98]] = now;
        dialogMessages[editMessage[98]] = 0x1518;
    }
}

void DialogClearWaitInit(void)
{
    ++editMessage[98];
    if (editMessage[98] >= 8) {
        editMessage[98] = 0;
        MessageBox(rootWnd, dialogOverflow, dialogError, 0x1010);
    }
    dialogTimes[editMessage[98]] = TickCount();
    dialogMessages[editMessage[98]] = 0x1518;
}

void DialogWait(void)
{
    WaitedEnough(&dialogTimes[editMessage[98]],
                 dialogMessages[editMessage[98]]);
}

void far DialogWaitInit(int waitValue)
{
    if (StillDown()) {
        do {
            win_FlushEvents();
        } while (StillDown());
    }
    win_FlushEvents();

    ++editMessage[98];
    if (editMessage[98] >= 8) {
        editMessage[98] = 0;
        MessageBox(rootWnd, dialogWaitOverflow, dialogWaitError, 0x1010);
    }
    dialogTimes[editMessage[98]] = TickCount();
    dialogMessages[editMessage[98]] = waitValue * 0x12;
}

int DialogAbort(void)
{
    if (WaitedEnough(&dialogTimes[editMessage[98]],
                     dialogMessages[editMessage[98]]))
        return 1;
    return GetAsyncKeyState(0x1b) & 0x8000;
}

int DialogAbortOrCont(void)
{
    int result;

    if (WaitedEnough(&dialogTimes[editMessage[98]],
                     dialogMessages[editMessage[98]]))
        result = 1;
    else
        result = GetAsyncKeyState(0x20) & 0x8000;
    return result;
}

void DialogDone(void)
{
    if (--editMessage[98] < -1)
        editMessage[98] = -1;
}

void DialogAbortAll(void)
{
    int count;
    int i;
    count = editMessage[98];
    for (i = 0; i <= count; ++i)
        dialogMessages[i] = -1;
    editMessage[98] = -1;
}

