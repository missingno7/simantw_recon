/*
 * Hypothesis: drain the dialog input state before starting a new wait entry.
 * The initializer shares the verified eight-entry queue tables and overflow
 * message path with DialogClearWaitInit, but records the caller's wait value
 * scaled by the observed 0x12 factor.
 */
extern int near editMessage[];
static unsigned long near dialogTimes[8];
static int near dialogMessages[8];

extern int near rootWnd;
extern int far StillDown(void);
extern void far win_FlushEvents(void);
extern unsigned long far TickCount(void);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);

static char near dialogError[] = "SimAnt Internal Error";
static char near dialogOverflow[] = "DialogWaitInit - Overflow";

void far DialogWaitInit(int waitValue)
{
    if (StillDown()) {
        do {
            win_FlushEvents();
        } while (StillDown());
    }
    win_FlushEvents();

    ++editMessage[98];
    if (editMessage[98] >= 8) {
        editMessage[98] = 0;
        MessageBox(rootWnd, dialogOverflow, dialogError, 0x1010);
    }
    dialogTimes[editMessage[98]] = TickCount();
    dialogMessages[editMessage[98]] = waitValue * 0x12;
}
