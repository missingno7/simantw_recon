/* Find an ant at a board coordinate using the life grid and compact list. */
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char far Dx8;
extern int far FindLifeIndex(int list, int matchLife, int matchColumn, int low, int high, int mask);
extern int far GetAntIndex(int list, int index, int far *life, int far *column,
                           int far *attribute, int far *state, int far *direction);

int far FindLifeAt(int far *outIndex, volatile int list, int x, int y)
{
    int index = -1;
    volatile int tile;
    int life;
    int column;
    int attribute;
    int state;
    int direction;
    unsigned char far *lifeArray;
    unsigned char far *columnArray;
    unsigned char far *attributeArray;
    int count;
    int fallback;
    int valid;

    tile = -1;
    if (list <= 1)
        valid = x >= 0 && x <= 127 && y >= 0 && y <= 63;
    else
        valid = x >= 0 && x <= 63 && y >= 0 && y <= 63;

    if (--valid != 0) {
        tile = index;
    } else {
        switch (list) {
        case 0:
        case 1: tile = LifeA[x][y]; break;
        case 2: tile = LifeB[x][y]; break;
        case 3: tile = LifeR[x][y]; break;
        default: tile = index; break;
        }
    }

    if (tile == 0 || tile == 0xff || tile == 0xfe) {
        fallback = 1;
        index = FindLifeIndex(list, x, y, 1, 0x7f, 0x7f);
    } else {
        fallback = 0;
        if (list <= 1) {
            count = ListIndexA;
            lifeArray = (&Dx8 + (0x23a4));
            columnArray = (&Dx8 + (0x278e));
            attributeArray = (&Dx8 + (0x2f62));
        } else if (list == 2) {
            count = ListIndexB;
            lifeArray = (&Dx8 + (0x3736));
            columnArray = (&Dx8 + (0x392c));
            attributeArray = (&Dx8 + (0x3d18));
        } else {
            count = ListIndexR;
            lifeArray = (&Dx8 + (0x4104));
            columnArray = (&Dx8 + (0x42fa));
            attributeArray = (&Dx8 + (0x46e6));
        }

        index = count - 1;
        while (index >= 0) {
            if (lifeArray[index] == x && columnArray[index] == y &&
                attributeArray[index] == tile)
                break;
            --index;
        }
    }

    if (index >= 0) {
        GetAntIndex(list, index, &life, &column, &attribute, &state, &direction);
        *outIndex = index;
        return life;
    }

    *outIndex = -1;
    if (fallback)
        return -1;
    return tile;
}
