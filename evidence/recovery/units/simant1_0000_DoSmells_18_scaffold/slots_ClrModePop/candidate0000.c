/*
 * ClrModePop resets the two fixed-size mode-pop work areas in the shared
 * far-state segment.  Each area is twenty words and is cleared before the
 * associated mode counters are conditionally decremented.  The counters and
 * arrays are the public PACK objects TemRModePop / TemBModePop (twenty words
 * each) and the FlyAwayB / FlyAwayR counters; the original routine loads
 * their segment immediately (no selector pool) while operating on them.
 * Unit review (simant1:0000): the earlier spelling reached these objects
 * through invented names and displacements.
 */
extern unsigned int far TemRModePop[];
extern unsigned int far TemBModePop[];
extern unsigned int far FlyAwayB;
extern unsigned int far FlyAwayR;

void near ClrModePop(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        TemRModePop[i] = 0;

    for (i = 0; i < 20; ++i)
        TemBModePop[i] = 0;

    if (FlyAwayB != 0)
        --FlyAwayB;

    if (FlyAwayR != 0)
        --FlyAwayR;
}
