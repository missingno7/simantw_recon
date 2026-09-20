/*
 * Age the B-team scent table in Dx8.  Weak scent (below eight) expires;
 * stronger scent is reduced by half.  The table is walked in 0x20-byte
 * bands through the 0x800-byte colony area.
 */
extern unsigned char far Dx8[];

void near ColonySmellBT(void)
{
    int band;
    int cell;
    int smell;
    unsigned char near *p;

    for (band = 0; band < 0x800; band += 0x20) {
        for (cell = 0; cell < 0x20; ++cell) {
            p = (unsigned char near *)Dx8 + band + cell + 0x6ad2;
            smell = *p;
            if (smell < 8)
                *p = 0;
            else
                *p -= smell >> 1;
        }
    }
}
