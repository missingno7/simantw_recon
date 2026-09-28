struct EditEvent {
    char reserved[8];
    int value;
    char reserved2[2];
    int message;
};
struct HistEvent { char reserved[12]; unsigned int message; };
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
extern int near mapUserButton[8];
extern int near yardUserButton[8];
extern unsigned long __based(__segname("SIMANT_DATA_GROUP")) userButtonHelpId[16];
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

void far DoEvent(struct DoEventRecord event)
{
    unsigned int helpContext;

    if (bHelp) {
        bHelp = 0;
        helpContext = (unsigned int)event.message.bytes.high << 8;
        if (helpContext == 0) {
            WinHelp(rootWnd, helpFile, 1, 4UL);
            return;
        }
        if (helpContext == 0x0100 || helpContext == 0x1900) {
            WinHelp(rootWnd, helpFile, 1, 0x0102UL);
            return;
        }
        if (helpContext == 0x0500 || helpContext == 0x1200 || helpContext == 0x1300) {
            WinHelp(rootWnd, helpFile, 1, (unsigned long)helpContext);
            return;
        }
        if (helpContext == 0x1500 || helpContext == 0x2200 || helpContext == 0x2300) {
            if (helpContext == 0x1500) {
                if (event.message.word >= 0x1503 && event.message.word <= 0x150d)
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)event.message.word);
                else if (event.message.word == 0x150e || event.message.word == 0x150f)
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)(event.message.word - 3));
                else
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)helpContext);
                return;
            }
            if (helpContext == 0x2200) {
                if (event.message.word >= 0x2202 && event.message.word <= 0x2209)
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)event.message.word);
                else if (event.message.word >= 0x220b && event.message.word <= 0x220d)
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)event.message.word);
                else if (event.message.word == 0x220e || event.message.word == 0x220f)
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)(event.message.word - 3));
                else if (event.message.word >= 0x2210 && event.message.word <= 0x2217)
                    WinHelp(rootWnd, helpFile, 1, userButtonHelpId[mapUserButton[event.message.word - 0x2210]]);
                else if (event.message.word >= 0x2218 && event.message.word <= 0x221e)
                    WinHelp(rootWnd, helpFile, 1, 0xfd48UL);
                else
                    WinHelp(rootWnd, helpFile, 1, (unsigned long)helpContext);
                return;
            }
            if (event.message.word == 0x2308)
                WinHelp(rootWnd, helpFile, 1, (unsigned long)event.message.word);
            else if (event.message.word >= 0x230b && event.message.word <= 0x2312)
                WinHelp(rootWnd, helpFile, 1, userButtonHelpId[yardUserButton[event.message.word - 0x230b]]);
            else if (event.message.word >= 0x2313 && event.message.word <= 0x2319)
                WinHelp(rootWnd, helpFile, 1, 0xfd48UL);
            else
                WinHelp(rootWnd, helpFile, 1, (unsigned long)helpContext);
            return;
        }
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
