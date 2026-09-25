/* Hypothesis: DoEvent routes a stack-passed event record by its byte-12 message;
   bHelp selects WinHelp routing, otherwise that word selects a Proc* handler. */
struct DoEventRecord {
    unsigned int reserved0;
    unsigned int keyState;
    unsigned int reserved4;
    unsigned int reserved6;
    unsigned int x;
    unsigned int y;
    unsigned int state;
    unsigned int reserved14;
};
extern int near bHelp;
extern int near rootWnd;
extern int far match_position[];
extern void far ProcEditEvent(struct DoEventRecord far *event);
extern void far ProcMapEvent(struct DoEventRecord far *event);
extern void far ProcInfoEvent(struct DoEventRecord far *event);
extern void near ProcModeEvent(struct DoEventRecord far *event);
extern void near ProcCasteEvent(struct DoEventRecord far *event);
extern void far ProcYardEvent(struct DoEventRecord far *event);
extern void near ProcHistoryEvent(struct DoEventRecord far *event);
extern void far ProcMapRibbonEvent(struct DoEventRecord far *event);
extern void far ProcYardRibbonEvent(struct DoEventRecord far *event);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern void far DoKeyDown(struct DoEventRecord far *event);
extern void far DoMouse(struct DoEventRecord far *event);

void far DoEvent(struct DoEventRecord event)
{
    if (bHelp) {
        bHelp = 0;
        switch (event.state) {
        case 0x1300:
            WinHelp(rootWnd, (char far *)match_position, 1, 4L);
            return;
        case 0x0100:
            DoKeyDown((struct DoEventRecord far *)&event);
            return;
        case 0x0200:
        case 0x0400:
        case 0x2000:
            DoMouse((struct DoEventRecord far *)&event);
            return;
        default:
            return;
        }
    }
    switch (event.state) {
    case 0x0000: ProcEditEvent((struct DoEventRecord far *)&event); break;
    case 0x0100: ProcMapEvent((struct DoEventRecord far *)&event); break;
    case 0x0500: ProcInfoEvent((struct DoEventRecord far *)&event); break;
    case 0x1200: ProcModeEvent((struct DoEventRecord far *)&event); break;
    case 0x1300: ProcCasteEvent((struct DoEventRecord far *)&event); break;
    case 0x1500: ProcHistoryEvent((struct DoEventRecord far *)&event); break;
    case 0x1900: ProcYardEvent((struct DoEventRecord far *)&event); break;
    case 0x2200: ProcMapRibbonEvent((struct DoEventRecord far *)&event); break;
    case 0x2300: ProcYardRibbonEvent((struct DoEventRecord far *)&event); break;
    }
}
