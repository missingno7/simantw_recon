/* Derived mechanically from the mirrored colony function _LostHeadB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped FindInBList->FindInRList, LifeB->LifeR, LostHeadB->LostHeadR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: the life value selects one of eight signed Dx8/Dy8 offsets.
 * The adjusted row and column address LifeB; a matching life-8 marker or an
 * existing B-list entry means the head was not lost, otherwise return one.
 */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near LifeR[];
extern int far FindInRList(int firstKey, int secondKey, int thirdKey);

int far LostHeadR(int x, int y, int life)
{
    int index;
    int row;
    int column;

    index = life & 7;
    column = y + Dy8[index + 8];
    life -= 8;
    row = x + Dx8[index];
    if (LifeR[(row << 6) + column] == life)
        return 0;
    if (FindInRList(row, column, life) >= 0)
        return 0;
    return 1;
}
