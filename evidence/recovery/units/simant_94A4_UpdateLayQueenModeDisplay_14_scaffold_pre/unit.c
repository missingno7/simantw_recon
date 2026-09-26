/* Candidate translation unit simant_94A4_UpdateLayQueenModeDisplay_14_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _UpdateLayQueenModeDisplay, _win_MapChanged, _SetMapTitle, _ClearMapScentButtons, _myDelay, _DialogClearWait, _DialogClearWaitInit, _DialogWait, _DialogWaitInit, _DialogAbort, _DialogAbortOrCont, _DialogDone, _DialogAbortAll
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern void far clip_Push(void);
extern void far clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far win_SetGroupSelectedObj(int object, int state, int group);
extern void far win_MakeObjSelected(int object);
extern int near layQueenModeDisplayFlag;
extern int far LayDownQueenMode;
extern int near layQueenGroupObjects[2];
extern int near layQueenObjects[2];
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern struct WinRect far mapTileRect;
extern int far mapForce;
extern int far MapMode;
extern int near YardMode;
extern char far * far * far MwinTitle;
extern void far win_SetObjFormatStr(int object, char far *text);
extern void far win_DrawTitle(int object);
extern void far win_MakeGroupUnselected(int window, int group);
extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far win_Events(void);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern int near editMessage[];
static unsigned long near dialogTimes[8];
extern int near rootWnd;
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);
static char near dialogOverflow[] = "DialogClearWaitInit - Overflow";
extern int far StillDown(void);
extern void far win_FlushEvents(void);
static int near delayLevel = -1;
static long near delayStamps[8];
static unsigned int near delayWaits[8];
static char near dialogError[] = "SimAnt Internal Error";
static int near dialogMessages[8];


void DialogClearWait(void);
void DialogClearWaitInit(void);
void DialogWait(void);
void far DialogWaitInit(int waitValue);
int DialogAbort(void);
int DialogAbortOrCont(void);
void DialogDone(void);
void DialogAbortAll(void);

#pragma alloc_text(RUN2_TEXT, DialogClearWait, DialogClearWaitInit, DialogWait, DialogWaitInit)
#pragma alloc_text(RUN2_TEXT, DialogAbort, DialogAbortOrCont, DialogDone, DialogAbortAll)

void far UpdateLayQueenModeDisplay(void)
{
    int index;

    clip_Push();
    if (layQueenModeDisplayFlag) {
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
        MessageBox(rootWnd, dialogOverflow, dialogError, 0x1010);
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

