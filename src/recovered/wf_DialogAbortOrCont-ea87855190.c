/*
 * Continue a dialog when its current wait has elapsed; otherwise the space
 * key requests continuation.  The result is kept in one register across
 * both paths, matching the historical common return epilogue.
 */
extern int near editMessage[];
static long near dialogTimes[8];
static int near dialogMessages[8];

extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far pascal GetAsyncKeyState(unsigned int key);

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
