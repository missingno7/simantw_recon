/* Horizontal outlet with separate row fill and plug-stencil passes. */
extern unsigned char near MapA[];
extern unsigned char near PlugTemplate[];
extern void *memset(void *, int, unsigned);
extern void far TileFrame1(int top, int bottom, int left, int right);

void MakeOutletH(int row, int column)
{
    int rowOffset;
    int c;
    int outer;
    int inner;
    int width;
    int rowStart;

    rowStart = row;
    if (row + 12 < rowStart)
        goto frame;

    rowOffset = row << 6;
    c = column;
    width = c - column + 9;
    outer = row - rowStart + 13;
    while (outer != 0) {
        if (column + 8 >= column)
            memset(MapA + rowOffset + c, 0x63, width);
        rowOffset += 0x40;
        --outer;
    }

frame:
    TileFrame1(row, row + 12, column, column + 8);

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 130] =
                PlugTemplate[outer + inner * 4];
    }

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 450] =
                PlugTemplate[outer + inner * 4];
    }

    MapA[(row << 6) + column + 388] = 0x65;
}
