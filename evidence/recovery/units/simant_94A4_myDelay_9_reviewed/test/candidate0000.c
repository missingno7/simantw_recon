/* Candidate translation unit simant_94A4_myDelay_9_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _myDelay, _DialogClearWait, _DialogClearWaitInit, _DialogWait, _DialogWaitInit, _DialogAbort, _DialogAbortOrCont, _DialogDone, _DialogAbortAll
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far win_Events(void);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern int near editMessage[];
#define dialogTimes delayStamps
#define dialogMessages delayWaits
extern int near rootWnd;
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);
extern int far StillDown(void);
extern void far win_FlushEvents(void);


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

static int near delayLevel = -1;
static long near delayStamps[8];
static unsigned int near delayWaits[8];
static char near dialogStrings[] = "SimAnt Internal Error\0DialogClearWaitInit - Overflow\0SimAnt Internal Error\0DialogWaitInit - Overflow";
#define dialogError dialogStrings
#define dialogOverflow (dialogStrings + 22)
#define dialogWaitError (dialogStrings + 53)
#define dialogWaitOverflow (dialogStrings + 75)
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

