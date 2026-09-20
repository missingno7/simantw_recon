/*
 * Stamp the private 4-by-5 horizontal plug template into the map.  The map
 * advances by 0x40 bytes per outer row and the template by four bytes per
 * inner column.
 */
extern unsigned char near PlugTemplate[];
extern unsigned char near Map[];

void MakePlugH(int row, int column)
{
    int outer;
    int inner;

    for (outer = 0; outer < 4; ++outer) {
        for (inner = 0; inner < 5; ++inner)
            Map[(row << 6) + column + (outer << 6) + inner] =
                PlugTemplate[0x2328 + outer + inner * 4];
    }
}
