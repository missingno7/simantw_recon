extern int near rootWnd;
extern void far pascal WinHelp(int window, unsigned int helpSegment,
                               unsigned int helpOffset, unsigned int command,
                               unsigned int dataHigh, unsigned int dataLow);

void ProcMenuHelp(unsigned int context)
{
    WinHelp(rootWnd, 0x4e41, 0x76ac, 1, 0, context);
}
