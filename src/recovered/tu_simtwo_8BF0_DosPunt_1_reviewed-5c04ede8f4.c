/* Reviewed wrapper unit source for simtwo:8BF0.
 * _DosPunt has an exact body candidate.  The POOLSTUB_TEXT stand-in retains
 * the wrapper object's shared strings and initialized flag; its code is not
 * compared or credited.  Static declarations follow observed DGROUP order.
 * The private two-byte "t" at B4B0 and odd char-array boundary at B4C9 are
 * retained from the target data bytes; no MAPSYM public names the prefix.
 */
extern int near errno;
extern char far * near sys_errlist[];
extern void far Punt(char far *message, ...);

static char near wrapperDataPrefix[] = "t";
struct WrapperStrings {
    char outOfHandles[16];
    char dbPathFormat[7];
    char createDataFileMessage[25];
};
static struct WrapperStrings near wrapperStrings = {
    "Out of handles.",
    "%s.dat",
    "Cannot create data file."
};
static int near openDBInitialized = 0;
static char near tooManyFiles[] = "Too many files open.  You need a statement 'FILES=12' in\nyour config.sys file.  Please refer to your dos manual\nfor more information.";
static char near dosErrorFormat[] = "%s\nDos error: %d: %s";

void DosPunt(int first, int second)
{
    if (errno == 0x18) {
        Punt(tooManyFiles);
    }
    Punt(dosErrorFormat, first, second, errno, sys_errlist[errno]);
}

void far openDBStandIn(void);
#pragma alloc_text(POOLSTUB_TEXT, openDBStandIn)

/* SCAFFOLD, not recovered source: keep OpenDB-owned private DGROUP data. */
void far openDBStandIn(void)
{
    char near * volatile literal;
    volatile int initialized;

    literal = wrapperDataPrefix;
    literal = wrapperStrings.outOfHandles;
    literal = wrapperStrings.dbPathFormat;
    literal = wrapperStrings.createDataFileMessage;
    initialized = openDBInitialized;
    literal = tooManyFiles;
    literal = dosErrorFormat;
}
