/* SmoothEdgesB: normalize a cell, then add direction flags for qualifying
 * neighboring terrain values. */
extern unsigned char near MapB[64][64];
extern int far SRand8(void);

void far SmoothEdgesB(int x, int y)
{
    int neighbor;
    int edges;
    int index;
    int value;

    if (x < 0 || x > 63 || y > 63)
        return;

    if (y == 0) {
        index = (x << 6) + y;
        if (MapB[0][index] < 0x30)
            return;
        MapB[0][index] = 0x18;
        return;
    }

    index = (x << 6) + y;
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
    if (y >= 2) {
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
    if (x <= 0x3e) {
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
    if (y <= 0x3e) {
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
    if (x >= 1) {
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
