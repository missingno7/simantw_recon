/*
 * Add an alarm level to the half-resolution Dx8 grid.  The first coordinate
 * selects a 32-byte row and the second selects a column; the accumulated
 * level saturates at 0xc8 before the cell is written back.
 */
extern unsigned char far Dx8[];

void near AlarmHere(int y, int x, int level)
{
    int total;
    int result;
    int row;
    int index;

    row = y >> 1;
    index = row << 5;
    index += x >> 1;
    total = Dx8[0x52d2 + index] + level;
    if (total > 0xc8)
        result = 0xc8;
    else
        result = total;
    Dx8[0x52d2 + index] = (unsigned char)result;
}
