extern int near rootWnd;
extern char far helpFile[];
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);

void DoWinHelp(unsigned int context)
{
    WinHelp(rootWnd, helpFile, 1, (unsigned long)(context & 0xff00));
}
