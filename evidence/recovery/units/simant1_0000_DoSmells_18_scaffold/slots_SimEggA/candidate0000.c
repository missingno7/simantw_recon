/*
 * SimEggA: per-tick step of a generic A-list egg record (index).  The egg's
 * type byte (AlistT) is redrawn into its LifeA cell at (AlistX, AlistY);
 * with probability 1/200 (SRand1(200) == 0) the egg dies: its type and the
 * LifeA cell are cleared.  The A-list fields are the public based arrays of
 * SIMANT_DATA_GROUP (one segment word).  Assignment order x, y, type: the
 * first-assigned local (x) wins the free register (DI) and its load is
 * emitted at first use; y keeps a frame home, the type is a byte in CL.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char near LifeA[];
extern int far SRand1(int range);

void near SimEggA(int index)
{
    int x;
    int y;
    unsigned char type;

    x = AlistX[index];
    y = AlistY[index];
    type = AlistT[index];
    LifeA[(x << 6) + y] = type;
    if (SRand1(200) == 0) {
        AlistT[index] = 0;
        LifeA[(x << 6) + y] = 0;
    }
}
