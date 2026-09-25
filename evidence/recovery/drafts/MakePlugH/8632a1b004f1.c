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
