/* Candidate translation unit simone_3120_MakePlugV_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _MakePlugV, _MakePlugH
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern unsigned char near MapA[];

void MakePlugH(int row, int column);

#pragma alloc_text(RUN2_TEXT, MakePlugH)

static unsigned char near PlugTemplateV[] = {
    107, 108, 108, 108, 109, 113, 120, 100, 120, 114, 113, 121, 116, 121, 114, 110, 111, 111, 111, 112
};

extern void *memset(void *, int, unsigned);

extern void far TileFrame1(int top, int bottom, int left, int right);

volatile void MakeOutletV(int row, int column)
{
    int rowOffset;
    int c;
    int outer;
    int inner;
    struct OutletWidth { int width; volatile int savedRow; } widthState;
    int rowStart;

    rowStart = row;
    if (row + 8 < rowStart)
        goto frame;

    rowOffset = row << 6;
    c = column;
    widthState.width = c - column + 13;
    outer = row - rowStart + 9;
    widthState.savedRow = rowStart;
    do {
        if (column + 12 >= column)
            memset(MapA + rowOffset + c, 0x63, widthState.width);
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

static unsigned char near PlugTemplateH[] = {
    107, 108, 108, 109, 113, 118, 119, 114, 113, 100, 100, 114, 113, 118, 119, 114, 110, 111, 111, 112
};

void MakeOutletH(int row, int column)
{
    int rowOffset;
    int c;
    int outer;
    int inner;
    struct OutletWidth { int width; volatile int savedRow; } widthState;
    int rowStart;

    rowStart = row;
    if (row + 12 < rowStart)
        goto frame;

    rowOffset = row << 6;
    c = column;
    widthState.width = c - column + 9;
    outer = row - rowStart + 13;
    widthState.savedRow = rowStart;
    do {
        if (column + 8 >= column)
            memset(MapA + rowOffset + c, 0x63, widthState.width);
        rowOffset += 0x40;
    } while (--outer != 0);

frame:
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
