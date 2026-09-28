/* Hypothesis: the stack-passed event record stores its dispatch word at byte 12;
   bHelp selects WinHelp routing, otherwise the word selects a Proc* handler. */
struct DoEventRecord {
    unsigned int reserved0;
    unsigned int reserved2;
    unsigned int reserved4;
    unsigned int reserved6;
    unsigned int reserved8;
    unsigned int reserved10;
    unsigned int state;
    unsigned int reserved14;
};
extern int near bHelp;
extern int near rootWnd;
extern int far match_position[];
extern void far ProcEditEvent(struct DoEventRecord far *event);
extern void far ProcMapEvent(struct DoEventRecord far *event);
extern void far ProcInfoEvent(struct DoEventRecord far *event);
extern void far ProcYardEvent(struct DoEventRecord far *event);
extern void far ProcHistoryEvent(struct DoEventRecord far *event);
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
    case 0x1300: ProcEditEvent((struct DoEventRecord far *)&event); break;
    case 0x1500: ProcMapEvent((struct DoEventRecord far *)&event); break;
    case 0x1900: ProcInfoEvent((struct DoEventRecord far *)&event); break;
    case 0x2200: ProcYardEvent((struct DoEventRecord far *)&event); break;
    case 0x2300: ProcMapRibbonEvent((struct DoEventRecord far *)&event); break;
    case 0x2400: ProcYardRibbonEvent((struct DoEventRecord far *)&event); break;
    case 0x2500: ProcHistoryEvent((struct DoEventRecord far *)&event); break;
    }
}
