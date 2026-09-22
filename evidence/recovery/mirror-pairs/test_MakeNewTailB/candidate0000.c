/* Derived mechanically from the mirrored colony function _MakeNewTailR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToRList->AddAntToBList, MakeNewTailR->MakeNewTailB, RlistT->BlistT, RlistY->BlistY; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: the R-tail record at index supplies its type, column and life.
 * Select the direction ((type & 7) ^ 4), add Dy8[direction+8] to the
 * R-list column and Dx8[direction] to the R-list life, raise type by 8, and
 * insert the new record with state 9 and direction 0.  This is the exact
 * R-side mirror of the preserved B-side reconstruction.
 */
extern unsigned char far BlistT[];
extern unsigned char far BlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);

void far MakeNewTailB(int index)
{
    AddAntToBList(
        BlistT[index + 0x4104] +
            Dx8[((BlistT[index + 0x46e6] & 7) ^ 4)],
        BlistY[index + 0x42fa] +
            Dy8[((BlistT[index + 0x46e6] & 7) ^ 4) + 8],
        BlistT[index + 0x46e6] + 8,
        9,
        0);
}
