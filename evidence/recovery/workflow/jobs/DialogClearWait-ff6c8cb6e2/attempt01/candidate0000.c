/*
 * DialogClearWait marks the current dialog entry as waiting.  An empty entry
 * (the -1 sentinel) is left untouched; otherwise the current tick is stored
 * in the parallel timestamp table and the entry receives the 0x1518 wait
 * marker.  editMessage[98] is the active queue index.
 */
extern int near editMessage[];
extern int near dialogMessages[];
extern unsigned long near dialogTimes[];
extern unsigned long far TickCount(void);

void DialogClearWait(void)
{
    unsigned long now;
    int index;

    index = editMessage[98];
    if (dialogMessages[index] != -1) {
        now = TickCount();
        dialogTimes[index] = now;
        dialogMessages[index] = 0x1518;
    }
}
