/*
 * DosPunt is the database layer's errno reporter.  DOS error 0x18 is
 * handled separately because the CRT's indexed text is not useful for the
 * "too many open files" failure; all other errors pass the caller's two
 * words, errno, and the indexed far error text to Punt.
 */
extern int near errno;
extern char far * near sys_errlist[];
extern void far Punt(char far *message, ...);

void DosPunt(int first, int second)
{
    if (errno == 0x18) {
        Punt("Too many open files");
    }
    Punt("DOS error %d: %s (%d, %d)", first, second, errno,
         sys_errlist[errno]);
}
