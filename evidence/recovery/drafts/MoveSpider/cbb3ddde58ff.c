/*
 * MoveSpider advances the spider animation clock, reacts to the current
 * ant-finding mode, and moves the spider by one eight-way grid step.  It
 * also handles emergence, nearby-ant pressure, and the death transition.
 */
extern int far Scycle, Scycle2, SMode, MeSMode;
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
extern signed char far SpX[], SpY[];
extern unsigned char far TurnTab[];
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
    register int x;
    register int y;
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
    int far *meMode;
    int far *spiderMode;
    int far *userX;
    int far *userY;
    int far *spiderOn;
    int far *revenge;

    Scycle2 = (Scycle2 + 1) & 0x3ff;
    x = SpidX >> 4;
    y = SpidY >> 4;

    meMode = &MeMode;
    if (*meMode == 1) {
        spiderMode = &SMode;
        if (*spiderMode == 2 || *spiderMode == 3)
            return;

        if (MeSMode == 7) {
            target = SFoundAnt();
                        Starg = target;
            if (target == -2) {
                                StargLife = -1;
            } else {
                *spiderMode = 2;
                                StargLife = target >= 0 ? AlistT[target] : -1;
            }
            return;
        }

        if (MeSMode == 8) {
            SpiderScan();
            userX = &SuserX;
            userY = &SuserY;
            distance = (int)GetDis(*userX, *userY, MeLocX, MeLocY);
            if (distance < 1) {
                Scycle = 2;
                return;
            }
            direction = GetBestDir(*userX, *userY, MeLocX, MeLocY, 1);
            if (direction == -1)
                return;
            if (direction == -2)
                direction = GetDir(*userX, *userY, MeLocX, MeLocY);
            if (direction >= 0 && direction < 8) {
                direction = TurnTab[SpidDir * 8 + direction];
                SpidDir = direction;
                SpidX += Dx8[direction] * 16;
                SpidY += Dy8[direction] * 16;
            }
        }
    } else {
        spiderOn = &SpidOn;
        spiderMode = &SMode;
        if (*spiderOn)
            goto normal_move;
        if (CurGameType == 0 && SRand1(300) == 0) {
            SpidX = SRand1(0x400) + 0x200;
            SpidY = 0x200;
            *spiderOn = 1;
            *spiderMode = 1;
            RevSpider = 0;
            direction = SRand1(2) ? 4 : 0;
            if (direction == 0) {
                SpidY = 1;
                SpidDir = 4;
            } else {
                SpidY = 0x3ff;
                SpidDir = 0;
            }
        }
        return;
    }

normal_move:
    spiderMode = &SMode;
    spiderOn = &SpidOn;
    if ((Scycle2 & 3) != 0 || *spiderMode >= 5)
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
        *spiderMode = 5;
        DeathCnt[0] = 500;
        Scycle = 0;
        if (*meMode == 1)
            PictStrnDialog(0x273e, 0, 0);
    }

    if (*spiderMode >= 3 && *spiderMode < 5) {
        revenge = &SpidRevenge;
        ++*revenge;
        if (*revenge >= 5)
            *revenge = 0;
    }
    if (*spiderMode >= 5)
        MeSMode = 8;
    else
        MeSMode = 7;

    switch (*spiderMode) {
    case 0:
        Scycle = 2;
        if (SRand1(150) == 0) {
            *spiderMode = 1;
            target = SFoundAnt();
                        Starg = target;
            if (target != -2)
                return;
        }
        if (SRand1(30) == 0) {
            random = SRand1(8);
            SpidDir = TurnTab[SpidDir * 8 + random];
        }
        if (MeSMode == 8)
            SpiderScan();
        break;

    case 1:
        direction = SpidDir & 7;
        if (RevSpider) {
            SpidX -= SpX[direction];
            SpidY -= SpY[direction];
            --Scycle;
        } else {
            SpidX += SpX[direction];
            SpidY += SpY[direction];
            ++Scycle;
        }
        break;

    case 2:
                        target = Starg;
        if (target >= 0 &&
            ((AlistT[target] ^ StargLife) & 0xf0) != 0) {
            *spiderMode = 0;
            Starg = -2;
        } else if (target >= 0) {
            direction = GetDir(SpidX, SpidY, MeLocX, MeLocY);
            if (direction >= 0 && direction < 8)
                SpidDir = direction;
        }
        break;

    case 3:
        SpidX = (SpidX & 0xfff0) + 8;
        SpidY = (SpidY & 0xfff0) + 8;
        if (*meMode == 1) {
            MeLocX = SpidX >> 4;
            MeLocY = SpidY >> 4;
            if (MeSMode == 6) {
                MeSMode = 0;
                GotoMyAnt();
            }
        }
        break;

    case 4:
        random = SRand1(8);
        SpidDir = TurnTab[SpidDir * 8 + random];
        direction = SpidDir;
        if (RevSpider) {
            SpidX -= SpX[direction] * 5;
            SpidY -= SpY[direction] * 5;
            Scycle -= 2;
        } else {
            SpidX += SpX[direction] * 5;
            SpidY += SpY[direction] * 5;
            Scycle = (Scycle + 2) & 0x3ff;
        }
        if (SRand1(50) == 0)
            SpiderScan();
        break;

    case 5:
        --DeathCnt[0];
        if (DeathCnt[0] == 0) {
            *spiderOn = 0;
            *spiderMode = 0;
            DropFoodA(x, y);
            DropFoodA(x, y);
            return;
        }
        if (SRand1(1000) >= DeathCnt[0])
            return;
        if (DeathCnt[0] > 0x190)
            *spiderMode = SRand1(3) + 1;
        else
            Scycle = SRand1(2) + 2;
        break;

    default:
        break;
    }
}
