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
