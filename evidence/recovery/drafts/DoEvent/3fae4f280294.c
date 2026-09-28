struct EditEvent {
    char reserved[8];
    int value;
    char reserved2[2];
    int message;
};
struct HistEvent { char reserved[12]; unsigned int message; };
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
extern void far ProcMapEvent(struct EditEvent far *event);

extern void far ProcInfoEvent(struct DoEventRecord far *event);
extern void far ProcModeEvent(struct DoEventRecord far *event);
extern void far ProcCasteEvent(struct DoEventRecord far *event);
extern void far ProcYardEvent(struct DoEventRecord far *event);
extern void far ProcHistoryEvent(struct HistEvent far *event);

extern void far ProcMapRibbonEvent(struct EditEvent far *event);

extern void far ProcYardRibbonEvent(struct DoEventRecord far *event);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern void far DoKeyDown(struct DoEventRecord far *event);
extern void far DoMouse(struct DoEventRecord far *event);

/* Hypothesis: help routing switches on the message high byte and forwards selected messages through WinHelp. */
extern int near mapUserButton[8];
extern int near yardUserButton[8];
extern unsigned long __based(__segname("SIMANT_DATA_GROUP")) userButtonHelpId[16];
void far DoEvent(struct DoEventRecord event)
{
    unsigned int helpContext;

    if (bHelp) {
        bHelp = 0;
        helpContext = (unsigned int)event.message.bytes.high << 8;
        switch (helpContext) {
        case 0x0000:
            helpContext = 4;
            break;
        case 0x0100:
        case 0x1900:
            helpContext = 0x0102;
            break;
        case 0x0500:
        case 0x1200:
        case 0x1300:
            break;
        case 0x1500:
        case 0x2200:
        case 0x2300:
            switch (event.message.word) {
            case 0x1503: case 0x1504: case 0x1505: case 0x1506:
            case 0x1507: case 0x1508: case 0x1509: case 0x150a:
            case 0x150b: case 0x150c: case 0x150d:
            case 0x2202: case 0x2203: case 0x2204: case 0x2205:
            case 0x2206: case 0x2207: case 0x2208: case 0x2209:
            case 0x220b: case 0x220c: case 0x220d:
            case 0x2308:
                helpContext = event.message.word;
                break;
            case 0x150e: case 0x150f:
            case 0x220e: case 0x220f:
                helpContext = event.message.word - 3;
                break;
            case 0x2210: case 0x2211: case 0x2212: case 0x2213:
            case 0x2214: case 0x2215: case 0x2216: case 0x2217:
                helpContext = (unsigned int)userButtonHelpId[mapUserButton[event.message.word - 0x2210]];
                break;
            case 0x2218: case 0x2219: case 0x221a: case 0x221b:
            case 0x221c: case 0x221d: case 0x221e:
            case 0x2313: case 0x2314: case 0x2315: case 0x2316:
            case 0x2317: case 0x2318: case 0x2319:
                helpContext = 0xfd48;
                break;
            case 0x230b: case 0x230c: case 0x230d: case 0x230e:
            case 0x230f: case 0x2310: case 0x2311: case 0x2312:
                helpContext = (unsigned int)userButtonHelpId[yardUserButton[event.message.word - 0x230b]];
                break;
            default:
                break;
            }
            break;
        default:
            return;
        }
        WinHelp(rootWnd, helpFile, 1, (unsigned long)helpContext);
        return;
    }

    switch ((unsigned int)event.message.bytes.high << 8) {
    case 0x0000: ProcEditEvent((struct DoEventRecord far *)&event); break;
    case 0x0100: ProcMapEvent((struct EditEvent far *)&event); break;
    case 0x0500: ProcInfoEvent((struct DoEventRecord far *)&event); break;
    case 0x1200: ProcModeEvent((struct DoEventRecord far *)&event); break;
    case 0x1300: ProcCasteEvent((struct DoEventRecord far *)&event); break;
    case 0x1500: ProcHistoryEvent((struct HistEvent far *)&event); break;
    case 0x1900: ProcYardEvent((struct DoEventRecord far *)&event); break;
    case 0x2200: ProcMapRibbonEvent((struct EditEvent far *)&event); break;
    case 0x2300: ProcYardRibbonEvent((struct DoEventRecord far *)&event); break;
    }
}
