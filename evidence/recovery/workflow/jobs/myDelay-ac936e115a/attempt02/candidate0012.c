/*
 * myDelay: wait about `ticks` timer ticks while keeping the message loop
 * alive.  The start stamp is TickCount() and the wait value is ticks / 3
 * (unsigned division).  Each pass returns as soon as WaitedEnough reports
 * the wait elapsed (verified far prototype) or win_Events reports a user
 * action; otherwise a nested per-level stamp/wait pair is checked.  The
 * three private objects are unnamed DGROUP data: the nesting level word at
 * 0x150a (fixture bytes ff ff, initialised -1), a BSS array of eight long
 * stamps at 0xcad4 and a BSS array of eight wait words at 0xcaf4 (bounded
 * by the following allocations at 0xcaf4 and 0xcb04).  When the level's
 * pair has elapsed the loop ends; otherwise it ends when the space bar
 * (GetAsyncKeyState, USER ordinal 249, VK_SPACE 0x20) is currently down.
 */
extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far win_Events(void);
extern int far pascal GetAsyncKeyState(unsigned int key);

static int near delayLevel = -1;
static unsigned int near delayWaits[8];
static long near delayStamps[8];

void far myDelay(unsigned int ticks)
{
    unsigned int wait;
    long stamp;
    int done;

    stamp = TickCount();
    wait = ticks / 3;
    do {
        if (WaitedEnough(&stamp, wait))
            return;
        if (win_Events())
            return;
        if (WaitedEnough(&delayStamps[delayLevel], delayWaits[delayLevel]))
            done = 1;
        else
            done = GetAsyncKeyState(0x20) & 0x8000;
    } while (!done);
}
