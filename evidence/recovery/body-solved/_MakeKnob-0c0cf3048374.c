/*
 * Stamp the private 5-by-5 knob template into the map.  The destination is
 * anchored at the requested 64-byte map row and column; each outer row adds
 * 0x40 bytes, while template bytes are read in five-byte row steps.
 */
extern unsigned char near KnobTemplate[];
extern unsigned char near Map[];

void MakeKnob(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            Map[(row << 6) + column + (outer << 6) + inner] =
                KnobTemplate[0x233c + outer + inner * 5];
    }
}
