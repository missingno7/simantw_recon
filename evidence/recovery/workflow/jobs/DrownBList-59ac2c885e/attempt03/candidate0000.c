/*
 * Hypothesis: walk the B list backwards and mark every matching live entry
 * as drowned.  The byte at +392c is the caller's requested list kind; the
 * status byte at +3d18 must be nonzero and its packed bits must represent a
 * kind from 1 through 11.  The write at +3b22 is the observed drown marker.
 */
extern int far ListIndexB;
extern unsigned char far Dx8[];

void DrownBList(int listKind)
{
    int index;
    register unsigned char state;

    index = ListIndexB;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x392c] != listKind)
            continue;
        state = Dx8[index + 0x3d18];
        if (state == 0)
            continue;
        state = (state & 0x78) >> 3;
        if (state <= 0 || state >= 0x0c)
            continue;
        Dx8[index + 0x3b22] = 0x11;
    }
}
