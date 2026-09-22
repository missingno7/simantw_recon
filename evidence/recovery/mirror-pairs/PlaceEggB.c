/* Derived mechanically from the mirrored colony function _PlaceEggR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToRList->AddAntToBList, DigTileR->DigTileB, LifeR->LifeB, ListIndexR->ListIndexB, PlaceEggR->PlaceEggB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: place one R-side egg below the 500-entry R-list bound and
 * inside rows 0..63 and columns 1..63.  DigTileR receives the coordinate
 * pair, AddAntToRList receives life, column, attribute 8, state 8's paired
 * direction 0 in the observed push order, and LifeR records the life byte
 * in the 64-byte row-strided grid.
 */
extern int far ListIndexB;
extern unsigned char near LifeB[];
extern void far DigTileB(int row, int column);
extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);

void far PlaceEggB(int row, int column, int life)
{
    if (ListIndexB >= 500)
        return;
    if (row < 0 || row > 63 || column < 1 || column > 63)
        return;

    DigTileB(row, column);
    AddAntToBList(row, column, life, 8, 0);
    LifeB[(row << 6) + column] = (unsigned char)life;
}
