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

    total = Dx8[0x52d2 + ((y >> 1) << 5) + (x >> 1)] + level;
    if (total > 0xc8)
        result = 0xc8;
    else
        result = total;
    Dx8[0x52d2 + ((y >> 1) << 5) + (x >> 1)] = (unsigned char)result;
}
