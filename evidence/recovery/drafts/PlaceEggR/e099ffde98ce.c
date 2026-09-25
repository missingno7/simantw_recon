/*
 * Hypothesis: place one R-side egg below the 500-entry R-list bound and
 * inside rows 0..63 and columns 1..63.  DigTileR receives the coordinate
 * pair, AddAntToRList receives life, column, attribute 8, state 8's paired
 * direction 0 in the observed push order, and LifeR records the life byte
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
    valid = 0;
    if (row >= 0 && row <= 63 && column >= 1 && column <= 63)
        valid = 1;
    if (valid) {
        DigTileR(row, column);
        AddAntToRList(row, column, life, 8, 0);
        LifeR[(row << 6) + column] = (unsigned char)life;
    }
}
