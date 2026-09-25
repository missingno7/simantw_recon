/*
 * Hypothesis: this is the enabled diagnostic formatter paired with
 * DebugWinPrintf.  It formats the varargs into the 512-byte local buffer,
 * emits a private prefix/suffix around leading/trailing LF characters, and
 * otherwise emits the formatted text once.  The target's DS accesses at
 * 08f2/08f4/08f6 are kept as ordinary near globals; their exact private
 * contributions remain a separate binding obligation.
 */
extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far pascal OutputDebugString(char far *text);
extern int far pascal lstrlen(char far *text);

static int near debugEnabled = 0;
static char near debugCR[] = "\r";
static char near debugLF[] = "\r";

int far WinPrintf(char far *format, ...)
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
