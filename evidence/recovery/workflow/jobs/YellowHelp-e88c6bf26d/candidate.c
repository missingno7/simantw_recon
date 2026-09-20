/*
 * Open the yellow help topic for the current simulation state.  The private
 * help-state flag takes precedence; otherwise MeType 0x40 selects the
 * special topic, with the ordinary topic as the fallback.
 */
extern int near rootWnd;
extern int near MeType;
extern int far yellowHelpState;
extern char far helpFile[];
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);

void YellowHelp(void)
{
    unsigned long data;

    if (yellowHelpState == 0) {
        if (MeType == 0x40)
            data = 0x00030100L;
        else
            data = 0x00010100L;
    } else {
        data = 0x00020100L;
    }
    WinHelp(rootWnd, helpFile, 1, data);
}
