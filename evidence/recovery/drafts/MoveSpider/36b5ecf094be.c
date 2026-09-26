/*
 * MoveSpider advances the spider animation clock, reacts to the current
 * ant-finding mode, and moves the spider by one eight-way grid step.  It
 * also handles emergence, nearby-ant pressure, and the death transition.
 */
extern int far Scycle, SCycle2, SMode, MeSMode;
extern int far DeathCnt[];
extern int far SpidOn, SpidRevenge, RevSpider, CurGameType;
extern int far Starg, StargLife, SuserX, SuserY;
extern int far MeMode, MeStartedFight;
extern int near SpidX, SpidY, SpidDir;
extern int near MeLocX, MeLocY, MeType, MeDir, MePlane;
extern int far MeGoalX, MeGoalY;
extern unsigned char far AlistT[];
extern unsigned char near LifeA[];
extern signed char far Dx8[], Dy8[];
extern int far SFoundAnt(void);
extern int far SpiderScan(void);
extern long far GetDis(int x1, int y1, int x2, int y2);
extern int far GetBestDir(int x1, int y1, int x2, int y2, int mode);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far SRand1(int range);
extern int far SRand2(void);
extern int far SRand4(void);
extern long far SRand256(void);
extern void far GotoMyAnt(void);
extern void far DropFoodA(int x, int y);
extern void far YellowDeath(int reason);
extern void far PictStrnDialog(int picture, int object, int force);
extern void far myBeginSound(unsigned int effect, unsigned int mode,
                             unsigned int repeats);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern int far IsValidA(int x, int y);

void far MoveSpider(void)
{
    int x;
    int y;
    int target;
    int direction;
    int distance;
    int nearby;
    int tx;
    int ty;
    int row;
    int column;
    int cellX;
    int cellY;
    int random;

    SCycle2 = (SCycle2 + 1) & 0x3ff;
    x = SpidX >> 4;
    y = SpidY >> 4;

    if (MeMode != 1)
        return;
    if (SMode == 2 || SMode == 3)
        return;

    if (MeSMode == 7) {
        target = SFoundAnt();
        Starg = target;
        if (target == -2) {
            StargLife = -1;
        } else {
            SMode = 2;
            StargLife = target >= 0 ? AlistT[target] : -1;
        }
        return;
    }

    if (MeSMode == 8) {
        SpiderScan();
        distance = (int)GetDis(SuserX, SuserY, MeLocX, MeLocY);
        if (distance < 1) {
            Scycle = 2;
            return;
        }
        direction = GetBestDir(SuserX, SuserY, MeLocX, MeLocY, 1);
        if (direction == -1)
            return;
        if (direction == -2)
            direction = GetDir(SuserX, SuserY, MeLocX, MeLocY);
        if (direction >= 0 && direction < 8) {
            SpidDir = direction;
            SpidX += Dx8[direction] * 16;
            SpidY += Dy8[direction] * 16;
        }
    }

    if (!SpidOn && CurGameType == 0 && SRand1(300) == 0) {
        SpidX = SRand1(0x400) + 0x200;
        SpidY = 0x200;
        SpidOn = 1;
        SMode = 1;
        RevSpider = 0;
        direction = SRand1(2) ? 4 : 0;
        if (direction == 0) {
            SpidY = 1;
            SpidDir = 4;
        } else {
            SpidY = 0x3ff;
            SpidDir = 0;
        }
        return;
    }

    if ((SCycle2 & 3) != 0 || SMode >= 5)
        return;

    nearby = 0;
    for (row = -1; row <= 1; ++row) {
        for (column = -1; column <= 1; ++column) {
            cellX = x + column;
            cellY = y + row;
            if (IsValidA(cellX, cellY) &&
                LifeA[cellY * 128 + cellX] != 0)
                ++nearby;
        }
    }

    if (nearby > 8) {
        SMode = 5;
        DeathCnt[0] = 500;
        Scycle = 0;
        PictStrnDialog(0x273e, 0, 0);
        if (SpidRevenge == 0) {
            YellowDeath(3);
            return;
        }
    }

    if (SMode < 5) {
        if (SMode >= 3)
            ++SpidRevenge;
        if (SpidRevenge > 3)
            SpidRevenge = 0;
        if (MeSMode == 8)
            direction = SpiderScan();
        else
            direction = GetDir(SpidX, SpidY, MeLocX, MeLocY);
        if (direction < 0 || direction > 7)
            direction = SRand1(8);
        if (SRand1(30) == 0)
            direction = (direction + SRand1(8)) & 7;
        SpidDir = direction;
        tx = x + Dx8[direction];
        ty = y + Dy8[direction];
        if (IsValidA(tx, ty)) {
            SpidX += Dx8[direction] * 16;
            SpidY += Dy8[direction] * 16;
        }
        if (SRand2())
            DropFoodA(x, y);
        if (SpidRevenge && tx == (MeLocX >> 4) && ty == (MeLocY >> 4)) {
            myBeginSound(0x7e, 0, 1);
            MoveMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
            YellowDeath(3);
        }
    }
}
