extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near MapA[];
extern unsigned char near HoleValues[];

void far HoleBorder(int x, int y)
{
    register int i;
    int column;
    int row;

    for (i = 0; i < 8; ++i) {
        row = Dy8[i] + y;
        column = Dx8[i] + x;
        if (column < 0 || column > 0x7f || row < 0 || row > 0x3f)
            return;
        if (MapA[(column << 6) + row] >= 0x50)
            return;
        MapA[(column << 6) + row] = HoleValues[i];
    }
}
