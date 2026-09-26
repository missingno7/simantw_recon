/* Candidate translation unit simtwo_8BF0_DosPunt_1_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DosPunt
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

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

