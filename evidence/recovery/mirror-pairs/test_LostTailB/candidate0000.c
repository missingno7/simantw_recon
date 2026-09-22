/* Derived mechanically from the mirrored colony function _LostTailR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped FindInRList->FindInBList, LifeR->LifeB, LostTailR->LostTailB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: derive the R-tail direction from the low byte of life,
 * offset the coordinate by the shared Dy8/Dx8 direction tables, and test
 * the LifeR cell against life+8.  A matching cell is retained only after
 * the repeated FindInRList(row,column,life) search has exhausted duplicates.
 */
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near LifeB[];
extern int far FindInBList(int row, int column, int life);

int far LostTailB(int x, int y, int life)
{
    int index;
    int column;
    int row;

    index = life ^ 0xfc;
    index &= 7;
    column = Dy8[index + 8] + y;
    life += 8;
    row = Dx8[index] + x;
    if (LifeB[(row << 6) + column] != life)
        return 0;
    while (FindInBList(row, column, life) >= 0) {
    }
    return 1;
}
