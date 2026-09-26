/* One translation unit shares debugEnabled and keeps the four formatter terminators and printf format referenced once. */
/* Candidate translation unit gr_62BC_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _WinPrintf, _DebugWinPrintf, _printf, _SetDebugFlag
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far pascal OutputDebugString(char far *text);
extern int far pascal lstrlen(char far *text);
extern int far WinPrintf(char far *format, ...);
extern int near paletteH[];




static int near debugEnabled = 0;
static char near winDebugCR[] = "\r";
static char near winDebugLF[] = "\r";
static char near debugCR[] = "\r";
static char near debugTrailingCR[] = "\r";
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

static char near debugFormat[] = "%s";
void printf(char far *format, ...)
{
    char buffer[0x200];

    WVSPrintf(buffer, format, (char far *)(&format + 1));
    WinPrintf(debugFormat, buffer);
}

void SetDebugFlag(void)
{
    paletteH[76] = 0;
}

