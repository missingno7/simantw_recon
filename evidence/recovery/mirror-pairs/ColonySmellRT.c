/* Derived mechanically from the mirrored colony function _ColonySmellBT (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped ColonySmellBT->ColonySmellRT, ColonySmellRT->ColonySmellBT; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Age the B-team scent table in Dx8.  Weak scent (below eight) expires;
 * stronger scent is reduced by half.  The table is walked in 0x20-byte
 * bands through the 0x800-byte colony area.
 */
extern unsigned char far Dx8[];

void near ColonySmellRT(void)
{
    register int cell;
    register int index;
    int band;
    int smell;

    for (band = 0; band < 0x800; band += 0x20) {
        for (cell = 0; cell < 0x20; ++cell) {
            index = band;
            index += cell;
            smell = Dx8[index + 0x6ad2];
            if (smell < 8)
                Dx8[band + cell + 0x6ad2] = 0;
            else
                Dx8[band + cell + 0x6ad2] = smell - (smell >> 1);
        }
    }
}
