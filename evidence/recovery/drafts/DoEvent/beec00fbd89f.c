/* Hypothesis: DoEvent routes a stack-passed event record by its byte-12 message;
   bHelp selects WinHelp routing, otherwise that word selects a Proc* handler. */
struct DoEventBytes { unsigned char low; unsigned char high; };
union DoEventWord { unsigned int word; struct DoEventBytes bytes; };
struct DoEventRecord {
    unsigned int reserved0;
    unsigned int keyState;
    unsigned int reserved4;
    unsigned int reserved6;
    unsigned int x;
    unsigned int y;
    union DoEventWord message;
    unsigned int reserved14;
};
extern int near bHelp;
extern int near rootWnd;
extern char far helpFile[];
extern void far ProcEditEvent(struct DoEventRecord far *event);
extern void far ProcMapEvent(struct DoEventRecord far *event);
extern void far ProcInfoEvent(struct DoEventRecord far *event);
extern void far ProcModeEvent(struct DoEventRecord far *event);
extern void far ProcCasteEvent(struct DoEventRecord far *event);
extern void far ProcYardEvent(struct DoEventRecord far *event);
extern void far ProcHistoryEvent(struct DoEventRecord far *event);
extern void far ProcMapRibbonEvent(struct DoEventRecord far *event);
extern void far ProcYardRibbonEvent(struct DoEventRecord far *event);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern void far DoKeyDown(struct DoEventRecord far *event);
extern void far DoMouse(struct DoEventRecord far *event);

/* Hypothesis: help routing switches on the message high byte and forwards selected messages through WinHelp. */
void far DoEvent(struct DoEventRecord event)
{
    unsigned int helpContext;
    if (bHelp) goto help_mode;
    goto normal_event;
help_mode:
    bHelp = 0;
    helpContext = ((unsigned int)event.message.bytes.high) << 8;
    switch (helpContext) {
    case 0x0000: helpContext = 4; break;
    case 0x0100: case 0x1900: helpContext = 0x0102; break;
    case 0x0500: case 0x1200: case 0x1300: break;
    case 0x1500: case 0x2200: case 0x2300: helpContext = event.message.word; break;
    default: return;
    }
    WinHelp(rootWnd, helpFile, 1, (unsigned long)helpContext);
    return;

normal_event:
    switch (event.message.word) {
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
