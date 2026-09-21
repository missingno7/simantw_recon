/*
 * Hypothesis: timer points to a far 32-bit deadline.  A future deadline is
 * accepted immediately; otherwise the stored deadline plus signed delay is
 * compared with a fresh TickCount.  Success refreshes the deadline and
 * returns one, while failure leaves it unchanged and returns zero.
 */
extern long far TickCount(void);

int far WaitedEnough(long far *timer, int delay)
{
    int result;

    if (*timer > TickCount()) {
        result = 1;
    } else {
        if (TickCount() >= *timer + delay)
            result = 1;
        else
            result = 0;
    }
    if (result) {
        *timer = TickCount();
        return 1;
    }
    return 0;
}
