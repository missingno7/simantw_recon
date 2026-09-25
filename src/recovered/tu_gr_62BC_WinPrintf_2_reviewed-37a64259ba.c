/* Both formatter bodies use the one DGROUP debugEnabled word at 08F2. */
extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far pascal OutputDebugString(char far *text);
extern int far pascal lstrlen(char far *text);

static int near debugEnabled = 0;
static char near winDebugCR[] = "\r";
static char near winDebugLF[] = "\r";
static char near debugCR[] = "\r";
static char near debugTrailingCR[] = "\r";
static char near debugFormat[] = "%s";

int far WinPrintf(char far *format, ...)
{
    char buffer[0x200];
    int length;

    if (debugEnabled != 0) {
        WVSPrintf(buffer, format, (char far *)(&format + 1));
        if (buffer[0] == '\n')
            OutputDebugString(winDebugCR);
        OutputDebugString(buffer);
        length = lstrlen(buffer);
        if (buffer[length - 1] == '\n')
            OutputDebugString(winDebugLF);
        return 1;
    }
    return 0;
}

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
            OutputDebugString(debugTrailingCR);
        return 1;
    }
    return 0;
}
