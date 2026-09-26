/*
 * DialogWait asks whether the current queued dialog has waited long enough.
 * The current index is editMessage[98]; the queue supplies the wait value and
 * the parallel timestamp table supplies the far pointer examined by
 * WaitedEnough.  Both tables are near data in the original dialog module.
 */
extern int near editMessage[];
static unsigned long near dialogTimes[8];
static int near dialogMessages[8];

extern int far WaitedEnough(long far *stamp, int waitValue);

void DialogWait(void)
{
    WaitedEnough(&dialogTimes[editMessage[98]],
                 dialogMessages[editMessage[98]]);
}
