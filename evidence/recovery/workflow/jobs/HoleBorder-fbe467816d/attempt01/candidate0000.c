extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char near MapA[];
extern unsigned char near HoleValues[];

void far HoleBorder(int x, int y)
{
    int i;
    int column;
    int row;
    int offset;

    for (i = 0; i < 8; ++i) {
        row = (int)Dy8[i] + y;
        column = (int)Dx8[i] + x;
        if (column < 0 || column > 0x7f || row < 0 || row > 0x3f)
            return;
        offset = (column << 6) + row;
        if (MapA[offset] >= 0x50)
            return;
        MapA[offset] = HoleValues[i];
    }
}
