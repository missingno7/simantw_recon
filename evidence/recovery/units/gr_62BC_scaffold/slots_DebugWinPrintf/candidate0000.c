/*
 * Hypothesis: this is the debug-gated companion to printf.  It formats the
 * far varargs into a 512-byte stack buffer. If the text starts with LF, it
 * emits the carriage-return string at DGROUP 08F8 first. It emits the text,
 * then emits the carriage-return string at 08FA if the text ends with LF.
 * Both target strings contain CR; the prior LF declaration was disproved by
 * the target's private DATA bytes. The flag is at 08F2.
 */
extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far pascal OutputDebugString(char far *text);
extern int far pascal lstrlen(char far *text);

static int near debugEnabled = 0;
static char near debugCR[] = "\r";
static char near debugTrailingCR[] = "\r";
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
            OutputDebugString(debugTrailingCR);
        return 1;
    }
    return 0;
}
