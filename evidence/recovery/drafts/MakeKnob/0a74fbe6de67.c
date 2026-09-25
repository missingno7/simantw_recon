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
