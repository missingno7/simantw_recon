/* Derived mechanically from the mirrored colony function _MakeNewTailB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToBList->AddAntToRList, BlistT->RlistT, BlistY->RlistY, MakeNewTailB->MakeNewTailR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: the B-tail record at index supplies its type, column and life.
 * The low three type bits select one of eight directions, with the B-side
 * table's fourth bit toggled before indexing Dx8/Dy8.  The new tail is eight
 * type units above the old type, its column is shifted by Dy8[index+8], its
 * life by Dx8[index], and the verified B-list insertion receives state 9 and
 * direction 0.
 */
extern unsigned char far RlistT[];
extern unsigned char far RlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToRList(int life, int column, int attribute,
                              int state, int direction);

void far MakeNewTailR(int index)
{
    int type;
    int direction;
    int life;
    int column;

    type = RlistT[index + 0x3d18];
    direction = (type & 7) ^ 4;
    life = RlistT[index + 0x3736] + Dx8[direction];
    column = RlistY[index + 0x392c] + Dy8[direction + 8];
    AddAntToRList(life, column, type + 8, 9, 0);
}
