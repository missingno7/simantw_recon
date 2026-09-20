/*
 * Stamp the private 5-by-4 vertical plug template into the map.  The map
 * advances by one map row (0x40 bytes) for each outer iteration, while the
 * template is laid out in four columns with a five-byte stride.  The two
 * arrays are private DGROUP data in the historical module; these near
 * declarations state that binding without treating loader-chain words as
 * source constants.
 */
extern unsigned char near PlugTemplate[];
extern unsigned char near Map[];

void MakePlugV(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 4; ++inner)
            Map[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplate[0x2314 + outer + inner * 5];
    }
}
