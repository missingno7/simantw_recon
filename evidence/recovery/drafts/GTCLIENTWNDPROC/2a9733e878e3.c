/* Handle the client's DDE acknowledge and data messages. */
extern unsigned short near commandStr[];
extern unsigned short __based(__segname("PACK")) theDDEDataH;
extern long far pascal DefWindowProc(unsigned int hwnd, unsigned int message,
                                     unsigned int wParam, long lParam);
extern int far cdecl wsprintf(char far *buffer, char far *format, ...);
extern void far DebugWinPrintf(char far *format, ...);

long far pascal GTCLIENTWNDPROC(unsigned int hwnd, unsigned int message,
                                unsigned int wParam, long lParam)
{
    char buffer[256];

    if (message == 0x3e4) {
        DebugWinPrintf((char far *)commandStr + 0x14e);
        if (commandStr[0x26] != 0) {
            commandStr[0x27] = wParam;
            wsprintf((char far *)buffer, (char far *)commandStr + 0x163,
                     wParam);
            DebugWinPrintf((char far *)buffer);
        }
    } else if (message == 0x3e5) {
        DebugWinPrintf((char far *)commandStr + 0x139);
        theDDEDataH = (unsigned int)lParam;
    } else {
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}
