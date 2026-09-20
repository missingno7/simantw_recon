/*
 * Stamp the private 4-by-5 horizontal plug template into the map.  The map
 * advances by 0x40 bytes per outer row and the template by four bytes per
 * inner column.
 */
/* Tile IDs in column-major stencil order; bounds are the loop dimensions. */
static unsigned char near PlugTemplate[] = {
    107, 108, 108, 109, 113, 118, 119, 114, 113, 100, 100, 114, 113, 118, 119, 114, 110, 111, 111, 112
};
extern unsigned char near MapA[];

void MakePlugH(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplate[outer + inner * 4];
    }
}

/*
 * Stamp the private 5-by-5 knob template into the map.  The destination is
 * anchored at the requested 64-byte map row and column; each outer row adds
 * 0x40 bytes, while template bytes are read in five-byte row steps.
 */
/* Tile IDs in column-major stencil order; bounds are the loop dimensions. */
static unsigned char near KnobTemplate[] = {
    64, 65, 65, 65, 66, 67, 78, 78, 78, 68, 67, 78, 76, 78, 68, 67, 78, 78, 78, 68, 70, 71, 71, 71, 73
};
extern unsigned char near MapA[];

void MakeKnob(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                KnobTemplate[outer + inner * 5];
    }
}

/*
 * Stamp the private 3-by-3 penny template into the map.  Map rows advance by
 * 0x40 bytes; template bytes advance by three bytes for each inner column.
 */
/* Tile IDs in column-major stencil order; bounds are the loop dimensions. */
static unsigned char near PennyTemplate[] = {
    40, 41, 42, 43, 44, 45, 46, 47, 48
};
extern unsigned char near MapA[];

void MakePenny(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 3; ++outer) {
        for (inner = 0; inner < 3; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PennyTemplate[outer + inner * 3];
    }
}
