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
#define ATP(off) (&Dx8 + (off))

int far FindLifeAt(int far *outIndex, volatile int list, int x, int y)
{
    int index = -1;
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

    life = -1;
    if (list <= 1)
        valid = x >= 0 && x <= 127 && y >= 0 && y <= 63;
    else
        valid = x >= 0 && x <= 63 && y >= 0 && y <= 63;

    if (valid) {
        switch (list) {
        case 0:
        case 1: life = LifeA[x][y]; break;
        case 2: life = LifeB[x][y]; break;
        case 3: life = LifeR[x][y]; break;
        default: life = -1; break;
        }
    }

    if (life == 0 || life == 0xff || life == 0xfe) {
        fallback = 1;
        index = FindLifeIndex(list, x, y, 1, 0x7f, 0x7f);
    } else {
        fallback = 0;
        if (list <= 1) {
            count = ListIndexA;
            lifeArray = ATP(0x23a4);
            columnArray = ATP(0x278e);
            attributeArray = ATP(0x2f62);
        } else if (list == 2) {
            count = ListIndexB;
            lifeArray = ATP(0x3736);
            columnArray = ATP(0x392c);
            attributeArray = ATP(0x3d18);
        } else {
            count = ListIndexR;
            lifeArray = ATP(0x4104);
            columnArray = ATP(0x42fa);
            attributeArray = ATP(0x46e6);
        }

        index = count - 1;
        while (index >= 0) {
            if (lifeArray[index] == x && columnArray[index] == y &&
                attributeArray[index] == life)
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
    return life;
}
