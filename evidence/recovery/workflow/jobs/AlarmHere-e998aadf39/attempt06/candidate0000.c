/*
 * Add an alarm level to the half-resolution Dx8 grid.  The first coordinate
 * selects a 32-byte row and the second selects a column; the accumulated
 * level saturates at 0xc8 before the cell is written back.
 */
extern unsigned char far Dx8[];

void near AlarmHere(int y, register int x, int level)
{
    int row;
    int total;
    int result;

    row = y >> 1;
    total = Dx8[0x52d2 + (row << 5) + (x >> 1)] + level;
    if (total > 0xc8)
        result = 0xc8;
    else
        result = total;
    Dx8[0x52d2 + (row << 5) + (x >> 1)] = (unsigned char)result;
}
