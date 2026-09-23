/*
 * Age the B-team scent table in Dx8.  Weak scent (below eight) expires;
 * stronger scent is reduced by half.  The table is walked in 0x20-byte
 * bands through the 0x800-byte colony area.
 */
extern unsigned char far PherMapBT[64][32];

void near ColonySmellBT(void)
{
    int band;
    int cell;
    int smell;

    for (band = 0; band < 0x800; band += 0x20) {
        for (cell = 0; cell < 0x20; ++cell) {
            smell = PherMapBT[band >> 5][cell];
            if (smell < 8)
                PherMapBT[band >> 5][cell] = 0;
            else
                PherMapBT[band >> 5][cell] = smell - (smell >> 1);
        }
    }
}
