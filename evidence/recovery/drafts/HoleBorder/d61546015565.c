/* HoleBorder visits each of the eight neighboring offsets. Out-of-range neighbors and map cells at or above 0x50 are skipped; eligible cells receive the corresponding HoleValues entry. Signed direction bytes provide negative edge offsets. */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near MapA[];
extern unsigned char near HoleValues[];

void far HoleBorder(int x, int y)
{
    register int row;
    register int i;
    register int column;
    register int offset;

    for (i = 0; i < 8; ++i) {
        row = Dy8[i] + y;
        column = Dx8[i] + x;
        if (column < 0 || column > 0x7f || row < 0 || row > 0x3f)
            continue;
        offset = (column << 6) + row;
        if (MapA[offset] >= 0x50)
            continue;
        MapA[offset] = HoleValues[i];
    }
}
