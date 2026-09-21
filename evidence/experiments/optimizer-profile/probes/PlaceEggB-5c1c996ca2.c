/*
 * Hypothesis: place one B-side egg only while the B list has room and the
 * supplied row/column is inside the playable grid.  The calls use the same
 * argument order established by the verified B-list insertion routine:
 * DigTileB receives row, column, while AddAntToBList receives the life byte,
 * coordinate pair, state 8, and direction 0.  LifeB is the near DS grid;
 * match_position is the far DGROUP view of the selected B-list count.
 */
extern int far ListIndexB;
extern unsigned char near LifeB[];
extern void far DigTileB(int row, int column);
extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);

void far PlaceEggB(int row, int column, int life)
{
    int direction;

    if (ListIndexB >= 500)
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

    DigTileB(row, column);
    AddAntToBList(row, column, life, 8, 0);
    LifeB[(row << 6) + column] = (unsigned char)life;
}
