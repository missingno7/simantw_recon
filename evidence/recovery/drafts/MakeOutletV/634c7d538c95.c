extern unsigned char near MapA[];
extern unsigned char near PlugTemplate[];
extern void far TileFrame1(int top, int bottom, int left, int right);
void far MakeOutletV(int row, int column)
{
    int r, c, outer, inner;
    if (row > 0x7ff7 || column > 0x7ff3) return;
    for (r = row; r <= row + 8; ++r)
        for (c = column; c < column + 13; ++c)
            MapA[(r << 6) + c] = 0x63;
    TileFrame1(row, row + 8, column, column + 12);
    for (outer = 0; outer < 5; ++outer)
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 130] = PlugTemplate[outer + inner * 5];
    for (outer = 0; outer < 5; ++outer)
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 135] = PlugTemplate[outer + inner * 5];
    MapA[(row << 6) + column + 262] = 0x65;
}
