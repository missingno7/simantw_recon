/* SmoothEdgesB: the center value is normalized and a direction mask is
 * accumulated for qualifying adjacent MapB cells. */
extern unsigned char near MapB[64][64];
extern int far SRand8(void);

void far SmoothEdgesB(int x, int y)
{
    int index;
    int value;
    int neighbor;
    int edges;

    if (x < 0 || x > 63 || y > 63)
        return;

    index = (x << 6) + y;
    if (y == 0) {
        if (MapB[x][y] >= 0x30)
            MapB[x][y] = 0x18;
        return;
    }

    value = MapB[x][y];
    if (value < 0x20)
        return;
    if (value > 0x2f) {
        if (value < 0x4f)
            return;
        if (value == 0x4f)
            return;
    }
    if (value > 0x2f) {
        if (value <= 0x4d)
            value = 0;
        else
            value = 0x2f;
    }

    edges = 0;
    if (y >= 2) {
        neighbor = MapB[x][y - 1];
        if (neighbor >= 0x20) {
            if (neighbor > 0x2f && neighbor < 0x4f)
                neighbor = 0;
            else
                neighbor = 1;
        }
        if (neighbor != 0)
            edges |= 1;
    }
    if (x <= 0x3e) {
        neighbor = MapB[x + 1][y];
        if (neighbor >= 0x20) {
            if (neighbor > 0x2f && neighbor < 0x4f)
                neighbor = 0;
            else
                neighbor = 1;
        } else
            neighbor = 0;
        if (neighbor != 0)
            edges |= 2;
    }
    if (y <= 0x3e) {
        neighbor = MapB[x][y + 1];
        if (neighbor >= 0x20) {
            if (neighbor > 0x2f && neighbor < 0x4f)
                neighbor = 0;
            else
                neighbor = 1;
        } else
            neighbor = 0;
        if (neighbor != 0)
            edges |= 4;
    }
    if (x >= 1) {
        neighbor = MapB[x - 1][y];
        if (neighbor >= 0x20) {
            if (neighbor > 0x2f && neighbor < 0x4f)
                neighbor = 0;
            else
                neighbor = 1;
        } else
            neighbor = 0;
        if (neighbor != 0)
            edges |= 8;
    }

    if (edges != 0)
        MapB[x][y] = value + 0x1f + edges;
    else if (value == 0)
        MapB[x][y] = (unsigned char)SRand8();
    else
        MapB[x][y] = 0x4e;
}
