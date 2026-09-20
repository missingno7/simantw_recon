/*
 * This historical printf wrapper formats the caller's far format string and
 * varargs into a 512-byte stack buffer with USER's WVSPrintf, then forwards
 * the completed text to WinPrintf through the module's debug format string.
 */
extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far WinPrintf(char far *format, ...);
extern char near debugFormat[];

void printf(char far *format, ...)
{
    char buffer[0x200];

    WVSPrintf(buffer, format, (char far *)(&format + 1));
    WinPrintf(debugFormat, buffer);
}
