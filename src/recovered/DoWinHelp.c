extern int near rootWnd;
extern void far pascal WinHelp(int window, int helpSegment,
                               int helpOffset, int command,
                               int dataHigh, int dataLow);

void DoWinHelp(unsigned int context)
{
    context &= 0xff00;
    WinHelp(rootWnd, 0x58a1, 0x76ac, 1, 0, context);
}
