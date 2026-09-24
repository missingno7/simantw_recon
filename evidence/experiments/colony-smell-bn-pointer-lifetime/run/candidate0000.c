/*
 * ColonySmellBN ages the 0x20-byte scent bands in the Dx8 segment.  Each
 * nonzero byte is reduced by one; the outer walk covers the 0x800-byte
 * colony area in 0x20-byte bands.  This helper is near, as shown by RET.
 */
extern unsigned char far PherMapBN[];

void near ColonySmellBN(void)
{
    int band;
    int cell;
    unsigned char far *p;

    for (band = 0; band < 0x800; band += 0x20) {
        for (cell = 0; cell < 0x20; ++cell) {
            p = &PherMapBN[band + cell];
            if (*p != 0)
                --*p;
        }
    }
}
