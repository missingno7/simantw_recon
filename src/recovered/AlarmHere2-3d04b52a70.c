/* Preserve the existing alarm level while replacing a weaker cell. */
extern unsigned char far Dx8[];

void near AlarmHere2(register int x, int y, int level)
{
    x >>= 1;
    y >>= 1;
    if (Dx8[0x52d2 + (x << 5) + y] > level)
        return;
    Dx8[0x52d2 + (x << 5) + y] = (unsigned char)level;
}
