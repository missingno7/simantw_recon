/*
 * Age the red-team scent table in Dx8.  A live scent below eight expires
 * completely; stronger scent loses half its strength on each pass.  The
 * table is visited as 0x20-byte bands across the 0x800-byte colony area.
 */
extern unsigned char far Dx8[];

void near ColonySmellRT(void)
{
    int band;
    int cell;
    int smell;

    for (band = 0; band < 0x800; band += 0x20) {
        for (cell = 0; cell < 0x20; ++cell) {
            smell = Dx8[cell + band + 0x7ad2];
            if (smell <= 0)
                continue;
            if (smell < 8)
                Dx8[cell + band + 0x7ad2] = 0;
            else
                Dx8[cell + band + 0x7ad2] -= smell >> 1;
        }
    }
}
