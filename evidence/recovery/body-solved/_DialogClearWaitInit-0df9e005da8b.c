/*
 * Advance the dialog-overflow counter.  Once eight pending entries have
 * accumulated, reset the counter and report the overflow through the USER
 * message box.  The current counter then records a TickCount timestamp in
 * the parallel long table and marks the corresponding message slot with the
 * historical 0x1518 wait value.
 */
extern int near editMessage[];
extern int near dialogMessages[];
extern unsigned long near dialogTimes[];
extern int near rootWnd;
extern unsigned long far TickCount(void);
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);

void DialogClearWaitInit(void)
{
    ++editMessage[98];
    if (editMessage[98] >= 8) {
        editMessage[98] = 0;
        MessageBox(rootWnd, "SimAnt Internal Error",
                   "DialogClearWaitInit - Overflow", 0x1010);
    }
    dialogTimes[editMessage[98]] = TickCount();
    dialogMessages[editMessage[98]] = 0x1518;
}
