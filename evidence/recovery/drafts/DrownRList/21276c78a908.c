/*
 * Hypothesis: walk the R list backwards and mark every matching live entry
 * as drowned.  The byte at +42fa is the requested list kind; the status
 * byte at +46e6 must be nonzero and its packed bits must represent a kind
 * from 1 through 11.  The write at +44f0 is the observed drown marker.
 */
extern int far ListIndexR;
extern unsigned char far Dx8[];

void DrownRList(int listKind)
{
    int index;
    int state;

    index = ListIndexR;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x42fa] != listKind)
            continue;
        state = Dx8[index + 0x46e6];
        if (state == 0)
            continue;
        state = (state & 0x78) >> 3;
        if (state <= 0 || state >= 0x0c)
            continue;
        Dx8[index + 0x44f0] = 0x11;
    }
}
