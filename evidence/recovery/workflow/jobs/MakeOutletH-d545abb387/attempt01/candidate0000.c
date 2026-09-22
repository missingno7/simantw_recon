/*
 * MakeOutletH(row, column): stamps a horizontal wall outlet fixture. Fills
 * the 13-row by 9-column rectangle anchored at (row, column) with the
 * background tile 0x63, frames it with TileFrame1(row, row+12, column,
 * column+8), then stamps the shared 4-by-5 PlugTemplate stencil (same
 * private array as the admitted MakePlugH, confirmed by the identical
 * DGROUP:2328 reference in layout/private-data-topology.json) twice: once
 * anchored at (row+2, column+2) and again at (row+7, column+2), and
 * finally writes a single screw/knob dot 0x65 at (row+6, column+4).
 * MapA and PlugTemplate are reused verbatim from the admitted MakePlugH
 * (src/recovered/wf_MakePlugH-4c8422f5bd.c), which is a sibling public in
 * the same unit (simone:3120) and is the private array's real owner (this
 * function only reads it, hence the extern declaration here rather than a
 * second static definition). TileFrame1's 4-argument (top, bottom, left,
 * right) signature is inferred from the exact push order at the call site
 * (push column+8, column, row+12, row) and is itself target
 * _TileFrame1 in this same task list.
 */
extern unsigned char near MapA[];
extern unsigned char near PlugTemplate[];

extern void far TileFrame1(int top, int bottom, int left, int right);

void MakeOutletH(int row, int column)
{
    int r;
    int c;
    int outer;
    int inner;

    for (r = row; r < row + 13; r++) {
        for (c = column; c < column + 9; c++)
            MapA[(r << 6) + c] = 0x63;
    }

    TileFrame1(row, row + 0xc, column, column + 8);

    for (outer = 0; outer < 4; outer++) {
        for (inner = 0; inner < 5; inner++)
            MapA[(row << 6) + column + (outer << 6) + inner + 130] =
                PlugTemplate[outer + inner * 4];
    }

    for (outer = 0; outer < 4; outer++) {
        for (inner = 0; inner < 5; inner++)
            MapA[(row << 6) + column + (outer << 6) + inner + 450] =
                PlugTemplate[outer + inner * 4];
    }

    MapA[(row << 6) + column + 388] = 0x65;
}
