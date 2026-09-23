/* SmoothEdgesB: keep x/y live for the four bounds checks, cache the linear
 * cell index, and normalize map categories before marking adjacent edges. */
extern unsigned char near MapB[64][64];
extern int far SRand8(void);

void far SmoothEdgesB(int x, int y)
{
    int value;
    int scratch;
    int index;
    register int ix;
    register int iy;
    int neighbor;

    ix = x;
    iy = y;
    if (ix < 0 || ix > 63 || iy > 63)
        return;

    if (iy == 0) {
        index = (ix << 6) + iy;
        if (MapB[0][index] < 0x30)
            return;
        MapB[0][index] = 0x18;
        return;
    }

    index = (ix << 6) + iy;
    value = MapB[0][index];
    if (value < 0x20)
        return;
    if (value > 0x2f && value < 0x4f)
        return;
    if (value <= 0x2f || value >= 0x4f) {
        if (value <= 0x4d)
            value = 0;
        else
            value = 0x2f;
    }

    scratch = 0;
    if (iy >= 2) {
        neighbor = MapB[0][index - 1];
        if (neighbor >= 0x20 &&
            (neighbor <= 0x2f || neighbor >= 0x4f))
            scratch = 1;
    }
    if (ix <= 0x3e) {
        neighbor = MapB[0][index + 64];
        if (neighbor >= 0x20 &&
            (neighbor <= 0x2f || neighbor >= 0x4f))
            scratch |= 2;
    }
    if (iy <= 0x3e) {
        neighbor = MapB[0][index + 1];
        if (neighbor >= 0x20 &&
            (neighbor <= 0x2f || neighbor >= 0x4f))
            scratch |= 4;
    }
    if (ix >= 1) {
        neighbor = MapB[0][index - 64];
        if (neighbor >= 0x20 &&
            (neighbor <= 0x2f || neighbor >= 0x4f))
            scratch |= 8;
    }

    if (scratch != 0)
        MapB[0][index] = value + 0x1f + scratch;
    else if (value == 0)
        MapB[0][index] = (unsigned char)SRand8();
    else
        MapB[0][index] = 0x4e;
}
