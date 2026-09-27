extern unsigned char far Dx8[];

void near AlarmHere(register int rowArg, int colArg, int level)
{
    int row;
    register int result;

    rowArg >>= 1;
    colArg >>= 1;
    row = rowArg;
    result = Dx8[0x52d2 + (row << 5) + colArg] + level;
    if (result > 0xc8)
        result = 0xc8;
    Dx8[0x52d2 + (row << 5) + colArg] = (unsigned char)result;
}
