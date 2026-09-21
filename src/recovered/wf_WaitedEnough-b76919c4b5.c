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

    if (TickCount() < *timer)
        goto waited;
    if (*timer + delay <= TickCount())
        goto waited;
    result = 0;
    goto decided;
waited:
    result = 1;
decided:
    if (result) {
        *timer = TickCount();
    }
    return result;
}
