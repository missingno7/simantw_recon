/* SmoothEdgesB: normalize a cell, then add direction flags for qualifying
 * neighboring terrain values. */
extern unsigned char near MapB[64][64];
extern int far SRand8(void);

void far SmoothEdgesB(int x, int y)
{
    register int xx = x;
    register int yy = y;
    int index;
    int value;
    int neighbor;
    int edges;

    if (xx < 0 || xx > 63 || yy > 63)
        return;

    if (yy == 0) {
        index = (xx << 6) + yy;
        if (MapB[0][index] < 0x30)
            return;
        MapB[0][index] = 0x18;
        return;
    }

    index = (xx << 6) + yy;
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

    edges = 0;
    if (yy >= 2) {
        neighbor = MapB[0][index - 1];
        if (neighbor < 0x20)
            neighbor = 0;
        else if (neighbor > 0x2f && neighbor < 0x4f)
            neighbor = 0;
        else
            neighbor = 1;
        if (neighbor != 0)
            edges |= 1;
    }
    if (xx <= 0x3e) {
        neighbor = MapB[0][index + 64];
        if (neighbor < 0x20)
            neighbor = 0;
        else if (neighbor > 0x2f && neighbor < 0x4f)
            neighbor = 0;
        else
            neighbor = 1;
        if (neighbor != 0)
            edges |= 2;
    }
    if (yy <= 0x3e) {
        neighbor = MapB[0][index + 1];
        if (neighbor < 0x20)
            neighbor = 0;
        else if (neighbor > 0x2f && neighbor < 0x4f)
            neighbor = 0;
        else
            neighbor = 1;
        if (neighbor != 0)
            edges |= 4;
    }
    if (xx >= 1) {
        neighbor = MapB[0][index - 64];
        if (neighbor < 0x20)
            neighbor = 0;
        else if (neighbor > 0x2f && neighbor < 0x4f)
            neighbor = 0;
        else
            neighbor = 1;
        if (neighbor != 0)
            edges |= 8;
    }

    if (edges != 0)
        MapB[0][index] = value + 0x1f + edges;
    else if (value == 0)
        MapB[0][index] = (unsigned char)SRand8();
    else
        MapB[0][index] = 0x4e;
}
