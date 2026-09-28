/* Derived mechanically from the mirrored colony function _MakeOutletV (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped MakeOutletV->MakeOutletH; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* Post-test the row count, as the target does at the fill loop tail. */
extern unsigned char near MapA[];
extern unsigned char near PlugTemplateV[];
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
    if (row + 8 < rowStart)
        goto frame;

    rowOffset = row << 6;
    c = column;
    width = c - column + 13;
    outer = row - rowStart + 9;
    do {
        if (column + 12 >= column)
            memset(MapA + rowOffset + c, 0x63, width);
        rowOffset += 0x40;
    } while (--outer != 0);

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
