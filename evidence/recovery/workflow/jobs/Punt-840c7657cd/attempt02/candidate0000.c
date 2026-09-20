/*
 * Punt is the historical formatted-failure reporter.  It stops the root
 * window's timer, formats the two far arguments into a 512-byte automatic
 * buffer with USER's WVSPrintf entry, presents that text in a modal error
 * box, and terminates through the module's exit routine.  The caption is a
 * private near data object in the original translation unit.
 */
extern int near rootWnd;
extern char near puntCaption[];
extern int far pascal KillTimer(int window, unsigned int timer);
extern int far pascal Wvsprintf(char far *buffer, char far *format,
                                char far *arguments);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);
extern void far exit(int status);

void Punt(char far *format, ...)
{
    char buffer[0x200];

    KillTimer(rootWnd, 0);
    Wvsprintf(buffer, format, (char far *)&format + 1);
    MessageBox(rootWnd, buffer, puntCaption, 0x10);
    exit(1);
}
