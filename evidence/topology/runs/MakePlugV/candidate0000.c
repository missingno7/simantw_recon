/*
 * Stamp the private 5-by-4 vertical plug template into the map.  The map
 * advances by one map row (0x40 bytes) for each outer iteration, while the
 * template is laid out in four columns with a five-byte stride.  The two
 * arrays are private DGROUP data in the historical module; these near
 * declarations state that binding without treating loader-chain words as
 * source constants.
 */
/* Tile IDs in column-major stencil order; bounds are the loop dimensions. */
static unsigned char near PlugTemplate[] = {
    107, 108, 108, 108, 109, 113, 120, 100, 120, 114, 113, 121, 116, 121, 114, 110, 111, 111, 111, 112
};
extern unsigned char near MapA[];

void MakePlugV(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 5; ++outer) {
        for (inner = 0; inner < 4; ++inner)
            MapA[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplate[outer + inner * 5];
    }
}
