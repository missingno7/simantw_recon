/*
 * MakeSink(void): stamps a fixed kitchen-sink fixture at a hardcoded
 * position in MapA (no parameters; every destination address in the
 * target is a literal DGROUP offset, decoded here as row/column pairs via
 * (addr - 10472) / 64 and % 64 against MapA's own base). Two counter
 * basins (rows 41-68 and 73-88, columns 33-53 filled 0xc2, columns 35-53
 * re-filled 0xc1 on top) are each framed with TileFrame2, a backsplash
 * band (rows 37-91, columns 26-56) is filled 0x01, and the whole fixture
 * is framed once more with TileFrame1(0x25,0x5b,0x1a,0x38). Four 5x5 knob
 * stamps reuse the admitted MakeKnob's private KnobTemplate (same address
 * DGROUP:233C, confirmed by layout/private-data-topology.json) at
 * (44,27), (60,27), (52,27) and (52,36); a lone 0x4d dot sits at (62,29).
 * A small trim block at rows 52-58 layers 0x4e then 0x43 (overwriting row
 * 52) across columns 29-38, 0x44 across row 56, single dots 0x45/0x48 at
 * column 40 of rows 52/56, and two small 0xc2 patches at rows 54-56
 * (columns 41-42) and rows 57-58 (columns 35-42). MapA and KnobTemplate
 * are reused verbatim from the admitted MakeKnob
 * (src/recovered/wf_MakeKnob-7ddc938695.c), a sibling public in this same
 * unit (simone:3120); TileFrame1/TileFrame2 are the accepted-shape drafts
 * elsewhere in this task list (build/grind/agentW/TileFrame1.c,
 * TileFrame2.c, both MATCH_BLOCKED).
 */
extern unsigned char near MapA[128][64];
extern unsigned char near KnobTemplate[];

extern void far TileFrame1(int top, int bottom, int left, int right);
extern void far TileFrame2(int top, int bottom, int left, int right);

void far MakeSink(void)
{
    int row;
    int col;
    int outer;
    int inner;
    int rowOffset;

    for (row = 37; row <= 91; row++)
        for (col = 26; col <= 56; col++)
            MapA[row][col] = 0x01;

    for (row = 41; row <= 68; row++)
        for (col = 33; col <= 53; col++)
            MapA[row][col] = 0xc2;

    for (row = 42; row <= 68; row++)
        for (col = 35; col <= 53; col++)
            MapA[row][col] = 0xc1;

    TileFrame2(0x28, 0x44, 0x20, 0x35);

    for (row = 73; row <= 88; row++)
        for (col = 33; col <= 53; col++)
            MapA[row][col] = 0xc2;

    for (row = 74; row <= 88; row++)
        for (col = 35; col <= 53; col++)
            MapA[row][col] = 0xc1;

    TileFrame2(0x48, 0x58, 0x20, 0x35);

    TileFrame1(0x25, 0x5b, 0x1a, 0x38);

    for (outer = 0, rowOffset = 0; outer < 5; ++outer, rowOffset += 0x40)
        for (inner = 0; inner < 5; ++inner)
            MapA[(((44 + outer) << 6) + 27 + rowOffset + inner) / 64][(((44 + outer) << 6) + 27 + rowOffset + inner) % 64] = KnobTemplate[outer + inner * 5];

    for (outer = 0, rowOffset = 0; outer < 5; ++outer, rowOffset += 0x40)
        for (inner = 0; inner < 5; ++inner)
            MapA[(((60 + outer) << 6) + 27 + rowOffset + inner) / 64][(((60 + outer) << 6) + 27 + rowOffset + inner) % 64] = KnobTemplate[outer + inner * 5];

    MapA[62][29] = 0x4d;

    for (outer = 0, rowOffset = 0; outer < 5; ++outer, rowOffset += 0x40)
        for (inner = 0; inner < 5; ++inner)
            MapA[(((52 + outer) << 6) + 27 + rowOffset + inner) / 64][(((52 + outer) << 6) + 27 + rowOffset + inner) % 64] = KnobTemplate[outer + inner * 5];

    for (outer = 0, rowOffset = 0; outer < 5; ++outer, rowOffset += 0x40)
        for (inner = 0; inner < 5; ++inner)
            MapA[(((52 + outer) << 6) + 36 + rowOffset + inner) / 64][(((52 + outer) << 6) + 36 + rowOffset + inner) % 64] = KnobTemplate[outer + inner * 5];

    for (row = 52; row <= 56; row++)
        for (col = 29; col <= 38; col++)
            MapA[row][col] = 0x4e;

    for (col = 29; col <= 38; col++)
        MapA[52][col] = 0x43;

    for (col = 29; col <= 38; col++)
        MapA[56][col] = 0x44;

    MapA[52][40] = 0x45;
    MapA[56][40] = 0x48;

    for (row = 54; row <= 56; row++)
        for (col = 41; col <= 42; col++)
            MapA[row][col] = 0xc2;

    for (row = 57; row <= 58; row++)
        for (col = 35; col <= 42; col++)
            MapA[row][col] = 0xc2;
}
