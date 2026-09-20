/*
 * Food tiles in the 0x18..0x27 band are always accepted.  The separate
 * 0x48..0x4b band is accepted only when the current Dx8 state byte is clear.
 */
extern unsigned char far Dx8[];

int IsItFood(int tile)
{
    if (Dx8[0x9b6e] == 0) {
        if (tile >= 0x48 && tile <= 0x4b)
            return 1;
    }
    if (tile < 0x18 || tile > 0x27)
        return 0;
    return 1;
}
