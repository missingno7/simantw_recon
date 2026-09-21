/*
 * Read one byte from the 128-by-64 map.  The caller supplies map coordinates;
 * the original routine clamps x to 0..127 and y to 0..63 before indexing the
 * private row-major map table.  The byte is returned as a zero-extended int.
 */
extern unsigned char near GrabMapTable[];

int GrabMap(int x, int y)
{
    if (x > 0x7f)
        x = 0;
    else if (x < 0)
        x = 0x7f;

    if (y > 0x3f)
        y = 0;
    else if (y < 0)
        y = 0x3f;

    return GrabMapTable[(x << 6) + y];
}
