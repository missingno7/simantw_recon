/* Vertical outlet using the horizontal twin's per-row fill lifetime. */
extern unsigned char near MapA[];
extern unsigned char near PlugTemplateV[];
extern void *memset(void *, int, unsigned);
extern void far TileFrame1(int top, int bottom, int left, int right);

void MakeOutletV(int row, int column)
{
    int rowOffset;
    int c;
    int outer;
    int inner;
    int width;
    int rowStart;

    rowStart = row;
    if (row + 8 < rowStart)
        goto frame;

    rowOffset = row << 6;
    c = column;
    width = c - column + 13;
    outer = row - rowStart + 9;
    while (outer != 0) {
        if (column + 12 >= column)
            memset(MapA + rowOffset + c, 0x63, width);
        rowOffset += 0x40;
        --outer;
    }

frame:
    TileFrame1(row, row + 8, column, column + 12);

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 130] =
                PlugTemplateV[outer + inner * 5];
    }

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 135] =
                PlugTemplateV[outer + inner * 5];
    }
    MapA[(row << 6) + column + 262] = 0x65;
}
