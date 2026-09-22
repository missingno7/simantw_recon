/* Derived mechanically from the mirrored colony function _PlaceEggB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToBList->AddAntToRList, DigTileB->DigTileR, LifeB->LifeR, ListIndexB->ListIndexR, PlaceEggB->PlaceEggR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: place one B-side egg only while the B list has room and the
 * supplied row/column is inside the playable grid.  The calls use the same
 * argument order established by the verified B-list insertion routine:
 * DigTileB receives row, column, while AddAntToBList receives the life byte,
 * coordinate pair, state 8, and direction 0.  LifeB is the near DS grid;
 * match_position is the far DGROUP view of the selected B-list count.
 */
extern int far ListIndexR;
extern unsigned char near LifeR[];
extern void far DigTileR(int row, int column);
extern void far AddAntToRList(int life, int column, int attribute,
                              int state, int direction);

void far PlaceEggR(int row, int column, int life)
{
    int direction;

    if (ListIndexR >= 500)
        return;

    if (row < 0) {
        column = column;
        direction = 0;
    } else {
        if (row > 63 || column < 1 || column > 63)
            direction = 0;
        else
            direction = 1;
    }
    if (direction == 0)
        return;

    DigTileR(row, column);
    AddAntToRList(row, column, life, 8, 0);
    LifeR[(row << 6) + column] = (unsigned char)life;
}
