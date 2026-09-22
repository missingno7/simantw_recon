/* Candidate translation unit gr_6322: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DebugWinPrintf */

extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far pascal OutputDebugString(char far *text);
extern int far pascal lstrlen(char far *text);
static int near debugEnabled = 0;
static char near debugCR[] = "\r";
static char near debugLF[] = "\n";
static char near debugFormat[] = "%s";

int far DebugWinPrintf(char far *format, ...)
{
    char buffer[0x200];
    int length;

    if (debugEnabled != 0) {
        WVSPrintf(buffer, format, (char far *)(&format + 1));
        if (buffer[0] == '\n')
            OutputDebugString(debugCR);
        OutputDebugString(buffer);
        length = lstrlen(buffer);
        if (buffer[length - 1] == '\n')
            OutputDebugString(debugLF);
        return 1;
    }
    return 0;
}

