/*
 * A dialog abort is complete once its current queue entry has waited long
 * enough.  Otherwise Escape is the abort signal; the high bit of the Windows
 * key-state result is returned as the predicate.
 */
extern int near editMessage[];
static unsigned long near dialogTimes[8];
static int near dialogMessages[8];

extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far pascal GetAsyncKeyState(unsigned int key);

int DialogAbort(void)
{
    if (WaitedEnough(&dialogTimes[editMessage[98]],
                     dialogMessages[editMessage[98]]))
        return 1;
    return GetAsyncKeyState(0x1b) & 0x8000;
}
