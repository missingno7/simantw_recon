/* Candidate translation unit gr_6322_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DebugWinPrintf
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern int far pascal WVSPrintf(char far *buffer, char far *format,
                                char far *arguments);
extern void far pascal OutputDebugString(char far *text);
extern int far pascal lstrlen(char far *text);
static int near debugEnabled = 0;
static char near debugCR[] = "\r";
static char near debugLF[] = "\n";
static char near debugFormat[] = "%s";


void far pool_literal_fill_08F4(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_literal_fill_08F4)

/* SCAFFOLD, not recovered source: body literals between _DebugWinPrintf and _DebugWinPrintf (DGROUP 08F4-08F8), unclaimed members' body literals. */
void far pool_literal_fill_08F4(void)
{
    volatile char far *p;

    p = "\015\000\015";
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
            OutputDebugString(debugLF);
        return 1;
    }
    return 0;
}

