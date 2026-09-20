/*
 * Add an alarm level to the half-resolution Dx8 grid.  The first coordinate
 * selects a 32-byte row and the second selects a column; the accumulated
 * level saturates at 0xc8 before the cell is written back.
 */
extern unsigned char far Dx8[];

void near AlarmHere(int y, register int x, int level)
{
    int result;
    int total;
    int row;

    row = y >> 1;
    total = Dx8[0x52d2 + (row << 5) + (x >> 1)] + level;
    if (total <= 0xc8)
        result = total;
    else
        result = 0xc8;
    Dx8[0x52d2 + (row << 5) + (x >> 1)] = (unsigned char)result;
}
