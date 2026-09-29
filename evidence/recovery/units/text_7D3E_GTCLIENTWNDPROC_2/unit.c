/* Candidate translation unit text_7D3E_GTCLIENTWNDPROC_2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: GTCLIENTWNDPROC, _GtRegisterClass */

extern unsigned short near commandStr[];
extern unsigned short __based(__segname("PACK")) theDDEDataH;
extern long far pascal DefWindowProc(unsigned int hwnd, unsigned int message,
                                     unsigned int wParam, long lParam);
extern int far cdecl wsprintf(char far *buffer, char far *format, ...);
extern void far DebugWinPrintf(char far *format, ...);
typedef long (far pascal *WNDPROC)(int, unsigned int, int, long);
struct WndClass {
    unsigned style;
    WNDPROC windowProc;
    int classExtra;
    int windowExtra;
    unsigned instance;
    unsigned icon;
    unsigned cursor;
    unsigned background;
    char far *menuName;
    char far *className;
};
extern long far pascal GTCLIENTWNDPROC(unsigned int, unsigned int, unsigned int, long);
extern unsigned int far pascal LoadIcon(unsigned int instance, char far *name);
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);
extern unsigned int far pascal RegisterClass(struct WndClass far *wndClass);

long far pascal GTCLIENTWNDPROC(unsigned int hwnd, unsigned int message,
                                unsigned int wParam, long lParam)
{
    char buffer[256];

    switch (message) {
    case 0x3e4:
        DebugWinPrintf((char far *)commandStr + 0x14e);
        if (commandStr[0x26] != 0) {
            commandStr[0x27] = wParam;
            wsprintf((char far *)buffer, (char far *)commandStr + 0x163,
                     wParam);
            DebugWinPrintf((char far *)buffer);
        }
        break;
    case 0x3e5:
        DebugWinPrintf((char far *)commandStr + 0x139);
        theDDEDataH = (unsigned int)lParam;
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

int GtRegisterClass(unsigned instance)
{
    struct WndClass wc;
    wc.style = 0;
    wc.windowProc = GTCLIENTWNDPROC;
    wc.classExtra = 0;
    wc.windowExtra = 0;
    wc.instance = instance;
    wc.icon = LoadIcon(0, 0x7f00L);
    wc.cursor = LoadCursor(0, 0x7f00L);
    wc.background = 0x000d;
    wc.menuName = 0L;
    wc.className = "ClientDDEClass";
    return RegisterClass(&wc);
}

