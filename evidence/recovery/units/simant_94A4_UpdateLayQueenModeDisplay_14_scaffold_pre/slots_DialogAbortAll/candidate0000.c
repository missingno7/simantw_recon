/* Snapshot the dialog count; fill the inclusive range with the empty sentinel. */
extern int near editMessage[];
static long near dialogTimes[8];
static int near dialogMessages[8];
void DialogAbortAll(void)
{
    int count;
    int i;
    count = editMessage[98];
    for (i = 0; i <= count; ++i)
        dialogMessages[i] = -1;
    editMessage[98] = -1;
}
