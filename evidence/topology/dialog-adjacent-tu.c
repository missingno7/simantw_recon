/* Adjacent dialog operations share parallel eight-entry private tables. */
extern int near editMessage[];
extern int near rootWnd;
static unsigned long near dialogTimes[8];
static int near dialogMessages[8];
static char near dialogError[] = "SimAnt Internal Error";
static char near dialogOverflow[] = "DialogClearWaitInit - Overflow";
extern unsigned long far TickCount(void);
extern int far WaitedEnough(long far *stamp, int waitValue);
extern int far pascal MessageBox(int window, char far *text, char far *caption, unsigned style);
void DialogClearWait(void)
{
    unsigned long now;

    if (dialogMessages[editMessage[98]] != -1) {
        now = TickCount();
        dialogTimes[editMessage[98]] = now;
        dialogMessages[editMessage[98]] = 0x1518;
    }
}

void DialogClearWaitInit(void)
{
    ++editMessage[98];
    if (editMessage[98] >= 8) {
        editMessage[98] = 0;
        MessageBox(rootWnd, dialogOverflow, dialogError, 0x1010);
    }
    dialogTimes[editMessage[98]] = TickCount();
    dialogMessages[editMessage[98]] = 0x1518;
}

void DialogWait(void)
{
    WaitedEnough(&dialogTimes[editMessage[98]],
                 dialogMessages[editMessage[98]]);
}
