/*
 * DialogAbortAll clears every queued dialog message through the current
 * message index, inclusive, using -1 as the empty marker.  The count lives
 * in editMessage[98], while the queued words are a separate near array; a
 * signed negative count skips the fill, after which the count is reset.
 */
extern int near editMessage[];
extern int near dialogMessages[];

void DialogAbortAll(void)
{
    int i;

    if (editMessage[98] >= 0) {
        for (i = 0; i <= editMessage[98]; ++i)
            dialogMessages[i] = -1;
    }
    editMessage[98] = -1;
}
