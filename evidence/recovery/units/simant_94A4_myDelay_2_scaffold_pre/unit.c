/* Candidate translation unit simant_94A4_myDelay_2_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _myDelay
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far win_Events(void);
extern int far pascal GetAsyncKeyState(unsigned int key);
static int near delayLevel = -1;
static long near delayStamps[8];
static unsigned int near delayWaits[8];




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

