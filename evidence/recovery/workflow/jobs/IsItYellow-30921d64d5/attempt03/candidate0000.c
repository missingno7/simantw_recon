extern int near MePlane;
extern int near SpidX;
extern int near SpidY;
extern int far MeMode;
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern long far Dist(int x1, int y1, int x2, int y2);

int far IsItYellow(int level, int x, int y)
{
    int tile;

    if (MePlane != (level ? level : 1))
        return 0;
    if (MeMode == 1) {
        if (level > 1)
            return 0;
        if (Dist(x * 16 + 8, y * 16 + 8, SpidX, SpidY) < 0x200)
            return 1;
        return 0;
    }
    switch (level) {
    case 0:
    case 1:
        tile = LifeA[x][y];
        break;
    case 2:
        tile = LifeB[x][y];
        break;
    case 3:
        tile = LifeR[x][y];
        break;
    }
    if (tile == 0xff || tile == 0xfe)
        return 1;
    return 0;
}
