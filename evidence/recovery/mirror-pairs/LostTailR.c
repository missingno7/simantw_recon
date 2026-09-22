/* Derived mechanically from the mirrored colony function _LostTailB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped FindInBList->FindInRList, LifeB->LifeR, LostTailB->LostTailR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: for a B-list life at (x,y), derive its eight-way direction
 * index from the low byte of life, offset the coordinate by Dy8/Dx8, and
 * test the LifeB cell against life+8.  A matching cell is repeatedly
 * searched in the B list until FindInBList returns a negative result; this
 * drains duplicate list entries before reporting success.
 */
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near LifeR[];
extern int far FindInRList(int life, int column, int row);

int far LostTailR(int x, int y, int life)
{
    int index;
    int column;
    int row;
    int found;

    index = life ^ 0xfc;
    index &= 7;
    column = Dy8[index + 8] + y;
    life += 8;
    row = Dx8[index] + x;
    if (LifeR[(row << 6) + column] != life)
        return 0;
    do {
        found = FindInRList(row, column, life);
    } while (found >= 0);
    return 1;
}
