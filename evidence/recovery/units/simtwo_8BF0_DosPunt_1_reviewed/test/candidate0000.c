/* Reviewed wrapper unit source for simtwo:8BF0.
 * _DosPunt has an exact body candidate.  The POOLSTUB_TEXT stand-in retains
 * the wrapper object's shared strings and initialized flag; its code is not
 * compared or credited.  Static declarations follow observed DGROUP order.
 */
extern int near errno;
extern char far * near sys_errlist[];
extern void far Punt(char far *message, ...);

static char near outOfHandles[] = "Out of handles.";
static char near dbPathFormat[] = "%s.dat";
static char near createDataFileMessage[] = "Cannot create data file.";
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

    literal = outOfHandles;
    literal = dbPathFormat;
    literal = createDataFileMessage;
    initialized = openDBInitialized;
    literal = tooManyFiles;
    literal = dosErrorFormat;
}
