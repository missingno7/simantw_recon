/*
 * Hypothesis: place one R-side egg below the 500-entry R-list bound and
 * inside rows 0..63 and columns 1..63.  DigTileB receives the coordinate
 * pair, AddAntToBList receives life, column, attribute 8, state 8's paired
 * direction 0 in the observed push order, and LifeB records the life byte
 * in the 64-byte row-strided grid.
 */
extern int far ListIndexB;
extern unsigned char near LifeB[];
extern void far DigTileB(int row, int column);
extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);

void far PlaceEggB(int row, int column, int life)
{
    int valid;

    if (ListIndexB >= 500)
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
        DigTileB(row, column);
        AddAntToBList(row, column, life, 8, 0);
        LifeB[(row << 6) + column] = (unsigned char)life;
    }
}

