/* Derived mechanically from the mirrored colony function _PlaceEggB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToBList->AddAntToRList, DigTileB->DigTileR, LifeB->LifeR, ListIndexB->ListIndexR, PlaceEggB->PlaceEggR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: place one R-side egg below the 500-entry R-list bound and
 * inside rows 0..63 and columns 1..63.  DigTileB receives the coordinate
 * pair, AddAntToBList receives life, column, attribute 8, state 8's paired
 * direction 0 in the observed push order, and LifeB records the life byte
 * in the 64-byte row-strided grid.
 */
extern int far ListIndexR;
extern unsigned char near LifeR[];
extern void far DigTileR(int row, int column);
extern void far AddAntToRList(int life, int column, int attribute,
                              int state, int direction);

void far PlaceEggR(int row, int column, int life)
{
    int valid;

    if (ListIndexR >= 500)
        return;
    if (row < 0)
        goto invalid;
    if (row > 63)
        goto invalid;
    if (column < 1)
        goto invalid;
    if (column > 63)
        goto invalid;
    valid = 1;
    goto checked;
invalid:
    valid = 0;
checked:
    if (valid) {
        DigTileR(row, column);
        AddAntToRList(row, column, life, 8, 0);
        LifeR[(row << 6) + column] = (unsigned char)life;
    }
}

