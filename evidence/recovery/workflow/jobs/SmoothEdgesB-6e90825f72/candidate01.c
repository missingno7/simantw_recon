/* SmoothEdgesB: validate a cell and mark its exposed cardinal edges from
 * neighbouring colony map values.  The B and R map planes are mirror twins. */
extern unsigned char near MapB[64][64];
extern int far SRand8(void);

void far SmoothEdgesB(int x, int y)
{
    unsigned char value;
    unsigned char edges;

    if (x < 0 || x > 63 || y > 63)
        return;

    value = MapB[x][y];
    if (y == 0) {
        if (value >= 0x30)
            MapB[x][y] = 0x18;
        return;
    }

    if (value < 0x20 || (value > 0x2f && value < 0x4f))
        return;
    if (value <= 0x4e)
        value = 0x2f;

    edges = 0;
    if (y >= 2) {
        unsigned char n = MapB[x][y - 1];
        if ((n >= 0x20 && n <= 0x2f) || n >= 0x4f)
            edges |= 1;
    }
    if (x <= 62) {
        unsigned char n = MapB[x + 1][y];
        if ((n >= 0x20 && n <= 0x2f) || n >= 0x4f)
            edges |= 2;
    }
    if (y <= 62) {
        unsigned char n = MapB[x][y + 1];
        if ((n >= 0x20 && n <= 0x2f) || n >= 0x4f)
            edges |= 4;
    }
    if (x >= 2) {
        unsigned char n = MapB[x - 1][y];
        if ((n >= 0x20 && n <= 0x2f) || n >= 0x4f)
            edges |= 8;
    }

    if (edges != 0)
        MapB[x][y] = value + 0x1f + edges;
    else if (value == 0)
        MapB[x][y] = (unsigned char)SRand8();
    else
        MapB[x][y] = 0x4e;
}
