/*
 * HelpKeyDown: handle the help keys for a window.  F1 with Shift toggles
 * the help-pointer mode (bHelp), switching between the far hHelpCursor
 * and the window class cursor; F1 alone opens the help file's index
 * (WinHelp command 3); both report 1.  Escape leaves help mode (class
 * cursor restored) and reports 1.  Delete toggles help mode with the
 * matching cursor but reports 0, as does any other key.
 */
extern int near bHelp;
extern int near rootWnd;
extern int far hHelpCursor;
extern char far helpFile[];

extern int far pascal GetKeyState(int key);
extern unsigned int far pascal SetCursor(unsigned int cursor);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern unsigned int far pascal GetClassWord(unsigned int window, int index);

int far HelpKeyDown(unsigned int window, int key)
{
    if (key == 0x70) {
        if (GetKeyState(0x10) & 0x8000) {
            bHelp = !bHelp;
            if (bHelp)
                SetCursor(hHelpCursor);
            else
                SetCursor(GetClassWord(window, -12));
        } else
            WinHelp(rootWnd, helpFile, 3, 0L);
        return 1;
    }
    if (key == 0x1b) {
        if (bHelp) {
            bHelp = 0;
            SetCursor(GetClassWord(window, -12));
            return 1;
        }
    }
    if (key == 0x2e) {
        bHelp = bHelp ? 0 : 1;
        if (bHelp)
            SetCursor(hHelpCursor);
        else
            SetCursor(GetClassWord(window, -12));
    }
    return 0;
}
