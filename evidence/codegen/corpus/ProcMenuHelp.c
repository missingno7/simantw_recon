extern int near rootWnd;
extern void far pascal WinHelp(int window, int helpSegment,
                               int helpOffset, int command,
                               int dataHigh, int dataLow);

void ProcMenuHelp(int context)
{
    WinHelp(rootWnd, 0x4e41, 0x76ac, 1, 0, context);
}
