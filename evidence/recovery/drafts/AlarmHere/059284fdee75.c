extern unsigned char far Dx8[];

void near AlarmHere(int y, register int x, int level)
{
    int row;
    register int result;

    row = y >> 1;
    x >>= 1;
    result = Dx8[0x52d2 + (row << 5) + x] + level;
    if (result > 0xc8)
        result = 0xc8;
    Dx8[0x52d2 + (row << 5) + x] = (unsigned char)result;
}
