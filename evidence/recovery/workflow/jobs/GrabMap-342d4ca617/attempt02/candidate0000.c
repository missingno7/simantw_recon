/*
 * Read one byte from the 128-by-64 map.  The caller supplies map coordinates;
 * the original routine clamps x to 0..127 and y to 0..63 before indexing the
 * private row-major map table.  The byte is returned as a zero-extended int.
 */
extern unsigned char near GrabMapTable[];

int GrabMap(int x, int y)
{
    int row;
    int column;

    row = x;
    column = y;
    if (row > 0x7f)
        row = 0;
    else if (row < 0)
        row = 0x7f;

    if (column > 0x3f)
        column = 0;
    else if (column < 0)
        column = 0x3f;

    return GrabMapTable[(row << 6) + column];
}
