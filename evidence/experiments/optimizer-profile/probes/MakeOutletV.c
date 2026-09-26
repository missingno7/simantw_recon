extern void *memset(void *, int, unsigned);
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
    int r;
    int c;
    int outer;
    int inner;

    for (r = row; r <= row + 8; r++) {
        memset(MapA + (r << 6) + column, 0x63, 13);
    }

    TileFrame1(row, row + 8, column, column + 0xc);

    for (outer = 0; outer < 5; outer++) {
        for (inner = 0; inner < 4; inner++)
            MapA[(row << 6) + column + (outer << 6) + inner + 130] =
                PlugTemplateV[outer + inner * 5];
    }

    for (outer = 0; outer < 5; outer++) {
        for (inner = 0; inner < 4; inner++)
            MapA[(row << 6) + column + (outer << 6) + inner + 135] =
                PlugTemplateV[outer + inner * 5];
    }

    MapA[(row << 6) + column + 262] = 0x65;
}
