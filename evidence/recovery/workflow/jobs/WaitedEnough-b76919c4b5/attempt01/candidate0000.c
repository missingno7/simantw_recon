/*
 * Hypothesis: timer points to a far 32-bit deadline.  A future deadline is
 * accepted immediately; otherwise the stored deadline plus signed delay is
 * compared with a fresh TickCount.  Success refreshes the deadline and
 * returns one, while failure leaves it unchanged and returns zero.
 */
extern unsigned long far TickCount(void);

int far WaitedEnough(unsigned long far *timer, int delay)
{
    unsigned long now;
    int result;

    now = TickCount();
    if (*timer > now) {
        result = 1;
    } else {
        now = TickCount();
        if (now >= *timer + delay)
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
