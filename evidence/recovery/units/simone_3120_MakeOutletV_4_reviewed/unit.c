/* Shared private stencils established by admitted MakePlugV/H data contributions. */
static unsigned char near PlugTemplateV[20] = {107,108,108,108,109,113,120,100,120,114,113,121,116,121,114,110,111,111,111,112};
static unsigned char near PlugTemplateH[20] = {107,108,108,109,113,118,119,114,113,100,100,114,113,118,119,114,110,111,111,112};

/*
 * MakeOutletV(row, column): vertical twin of MakeOutletH. Fills the 9-row
 * by 13-column rectangle anchored at (row, column) with the background
 * tile 0x63, frames it with TileFrame1(row, row+8, column, column+12),
 * then stamps the shared 5-by-4 vertical plug stencil (same private array
 * as the admitted MakePlugV, confirmed by the identical DGROUP:2314
 * reference in layout/private-data-topology.json; this function only
 * reads it, hence extern rather than a second static definition) twice:
 * once anchored at (row+2, column+2) and again at (row+2, column+7), and
 * finally writes a single screw/knob dot 0x65 at (row+4, column+6).
 * MapA and the plug stencil are reused verbatim from the admitted
 * MakePlugV (src/recovered/wf_MakePlugV-9d1d0472d2.c), a sibling public in
 * the same unit (simone:3120). TileFrame1's 4-argument (top, bottom, left,
 * right) signature matches the accepted-shape MakeOutletH draft's
 * hypothesis (build/grind/agentW/MakeOutletH.c, MATCH_BLOCKED) and is
 * itself target _TileFrame1 in this same task list.
 */
extern unsigned char near MapA[];
extern unsigned char near PlugTemplateV[];

extern void far TileFrame1(int top, int bottom, int left, int right);

void MakeOutletV(int row, int column)
{
    /* Variant 01: plain-int-inclusive. */
int r, c, outer, inner;

    for (r = row; r <= row + 8; ++r)
        for (c = column; c <= column + 12; ++c)
            MapA[(r << 6) + c] = 0x63;

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

/*
 * Stamp the private 5-by-4 vertical plug template into the map.  The map
 * advances by one map row (0x40 bytes) for each outer iteration, while the
 * template is laid out in four columns with a five-byte stride.  The two
 * arrays are private DGROUP data in the historical module; these near
 * declarations state that binding without treating loader-chain words as
 * source constants.
 */
/* Tile IDs in column-major stencil order; bounds are the loop dimensions. */
extern unsigned char near MapA[];

void MakePlugV(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplateV[outer + inner * 5];
    }
}

/*
 * MakeOutletH(row, column): stamps a horizontal wall outlet fixture. Fills
 * the 13-row by 9-column rectangle anchored at (row, column) with the
 * background tile 0x63, frames it with TileFrame1(row, row+12, column,
 * column+8), then stamps the shared 4-by-5 PlugTemplateH stencil (same
 * private array as the admitted MakePlugH, confirmed by the identical
 * DGROUP:2328 reference in layout/private-data-topology.json) twice: once
 * anchored at (row+2, column+2) and again at (row+7, column+2), and
 * finally writes a single screw/knob dot 0x65 at (row+6, column+4).
 * MapA and PlugTemplateH are reused verbatim from the admitted MakePlugH
 * (src/recovered/wf_MakePlugH-4c8422f5bd.c), which is a sibling public in
 * the same unit (simone:3120) and is the private array's real owner (this
 * function only reads it, hence the extern declaration here rather than a
 * second static definition). TileFrame1's 4-argument (top, bottom, left,
 * right) signature is inferred from the exact push order at the call site
 * (push column+8, column, row+12, row) and is itself target
 * _TileFrame1 in this same task list.
 */
extern unsigned char near MapA[];
extern unsigned char near PlugTemplateH[];

extern void far TileFrame1(int top, int bottom, int left, int right);

void MakeOutletH(int row, int column)
{
    /* Variant 01: plain-int-inclusive. */
int r, c, outer, inner;

    for (r = row; r <= row + 12; ++r)
        for (c = column; c <= column + 8; ++c)
            MapA[(r << 6) + c] = 0x63;

    TileFrame1(row, row + 12, column, column + 8);
    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 130] =
                PlugTemplateH[outer + inner * 4];
    }

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner + 450] =
                PlugTemplateH[outer + inner * 4];
    }
    MapA[(row << 6) + column + 388] = 0x65;
}

/*
 * Stamp the private 4-by-5 horizontal plug template into the map.  The map
 * advances by 0x40 bytes per outer row and the template by four bytes per
 * inner column.
 */
/* Tile IDs in column-major stencil order; bounds are the loop dimensions. */
extern unsigned char near MapA[];

void MakePlugH(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplateH[outer + inner * 4];
    }
}
