/* Initial nest setup, followed by a readable prey interaction pass. */
extern int __based(__segname("SIMANT_DATA_GROUP")) LionIndex;
extern int __based(__segname("PACK")) InitialLions;
extern unsigned char __based(__segname("PACK")) LionListX[10];
extern unsigned char __based(__segname("PACK")) LionListY[10];
extern unsigned char __based(__segname("PACK")) LionListM[10];
extern unsigned char __based(__segname("PACK")) LionListS[10];
extern unsigned char __based(__segname("PACK")) LionListT[10];
extern char far Dx8[];
extern char far Dy8[];

extern int far SRand1(int range);
extern int far SRand8(void);
extern int far IsClear3x3(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);
extern int far GetMap(int plane, int x, int y);
extern int far IsThisPebble(int x, int y);
extern int far IsThisFood(int x, int y);
extern int far IsYellowAnt(int x, int y);
extern void far SetMap(int plane, int x, int y, int value);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far YellowDeath(int x, int y);

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};

void far DoAntLions(void)
{
    int tries;
    int x;
    int y;
    int i;
    int lx;
    int ly;
    int mapTile;

    if (LionIndex == 0) {
        if (InitialLions <= 0)
            return;
        if (SRand1(0x400) != 0)
            return;

        tries = 0;
        for (;;) {
            x = SRand1(0x40) + SRand1(0x41);
            y = SRand1(0x20) + SRand1(0x21);
            if (IsClear3x3(1, x, y) == 1)
                break;
            if (IsClearTile(1, x, y) == 1 && tries >= 100)
                break;
            tries++;
            if (tries >= 200)
                return;
        }

        SetMap(1, x, y, 0x38);
        for (i = 0; i < 8; i++) {
            ly = y + Dy8[i];
            lx = x + Dx8[i];
            if (IsClearTile(1, lx, ly) == 1)
                SetMap(1, lx, ly, lionRing[i] + 0x30);
        }
        LionListX[LionIndex] = x;
        LionListY[LionIndex] = y;
        LionListM[LionIndex] = 0;
        LionListS[LionIndex] = 0;
        LionListT[LionIndex] = 0;
        if (LionIndex < 9)
            LionIndex++;
        return;
    }

    for (i = 0; i < LionIndex; i++) {
        x = LionListX[i];
        y = LionListY[i];
        mapTile = GetMap(1, x, y);
        if (IsThisPebble(x, y) || IsThisFood(x, y))
            continue;
        if (IsYellowAnt(x, y)) {
            MoveMyLife(1, x, y, 0, SRand8());
            YellowDeath(x, y);
        }
    }
}
