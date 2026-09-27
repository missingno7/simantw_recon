/* Candidate translation unit simtwo_5AB0_RandWorld_12: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _RandWorld, _RandYard, _GenerateTutorial, _DigOutBNest, _DigOutRNest, _InitYelloAnt, _PlaceBlackQueen, _MakeBlkQueen, _PlaceRedQueen, _MakeRedQueen, _fracSIN, _fracCOS */

extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapB[64][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapR[64][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapA[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapF[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBN[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBT[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRN[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRT[64][32];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern char far Dx8[];
extern char far Dy8[];
extern int far TERRAINset;
extern int far CurGameType;
extern long far TileTotYR;
extern long far TileTotXR;
extern long far TileTotYB;
extern long far TileTotXB;
extern int far TilesDugB;
extern int far TilesDugR;
extern int far TileMassYR;
extern int far TileMassXR;
extern int far TileMassYB;
extern int far TileMassXB;
extern int far WaterTable;
extern int far BlkQueens;
extern int far RedQueens;
extern int far LastBlackEgg[2];
extern int far LastRedEgg[2];
extern int near HealthB;
extern int near HealthR;
extern int far FoodB;
extern int far FoodR;
extern int far FoodA;
extern unsigned long far EditMsgDelay;
extern int far BlackLost;
extern int far RedLost;
extern int far Cycle;
extern int far EditRows;
extern int far EditColumns;
extern int far MapPnt[2];
extern int far AMapPnt[2];
extern int far BMapPnt[2];
extern int far RMapPnt[2];
extern void far SetSRandSeed(unsigned int seed, int flag);
extern void far InitSpider(void);
extern void far MakeMap(int width, int kind);
extern int far SRand1(int range);
extern int far SRand2(void);
extern int far SRand4(void);
extern int far SRand8(void);
extern int far SRand16(void);
extern int far SRand64(void);
extern int far SGRand(int range);
extern void far MakeNewHoleB(int x);
extern void far MakeNewHoleR(int x);
extern void far DigOutBNest(int count);
extern void far DigOutRNest(int count);
extern void far BuildAntListA(void);
extern void far ClearListB(void);
extern void far ClearListR(void);
extern void far DigTileR(int x, int y);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern void far PlaceBlackQueen(void);
extern void far InitYelloAnt(void);
extern void far AddFood(int a, int b);
extern void far ClearHistory(int a);
extern void far CountAnts(void);
extern void far InvalEuMap(int a, int b, int columns, int rows);
extern int far CurYardPnt[2];
extern int far YMapPnt[2];
extern int far CurGameTool;
extern unsigned long far LastThemeTime;
extern unsigned long far TimeTemp;
extern int far LastThemeSong;
extern int far HouseColonies;
extern int far JustToBeMean;
extern int far BlackWon;
extern int far IsGameOver;
extern int near ForSaleState;
extern int far AlwaysHealthy;
extern int far NeverHungry;
extern int far Invincible;
extern unsigned long far GameTime;
extern int near MapPlane;
extern int far MapMode;
extern int near YardMode;
extern int __based(__segname("SIMANT_DATA_GROUP")) YMapSeeds[16][12];
extern int far MeNestStarted;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern void far ClrArrays(void);
extern void far initControls(void);
extern void far InitSimYard(void);
extern int far RRand(int range);
extern void far RandWorld(int seed, int blackSize, int redSize, int mapWidth, int mapKind);
extern unsigned char far YMapPopB[12][16];
extern unsigned char far YMapPopR[12][16];
extern void far RandYard(void);
extern void far AddBlackAnts(int count);
extern void far AddRedAnts(int count);
extern void far FullCount(void);
extern void far SetMapPlane(int plane);
static char near tutorialX[30] = {
    0, 1, 2, 5, 7, 2, 2, 7, 8, 6, 3, 7, 7, 10, 11,
    6, 8, 10, 11, 9, 10, 11, 9, 10, 11, 9, 10, 10, 10, 11
};
static char near tutorialY[30] = {
    0, 0, 0, 0, 0, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5,
    6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 10, 11, 11
};
static char near tutorialBlack[30] = {
    2, 4, 6, 5, 7, 4, 2, 2, 3, 6, 1, 7, 4, 5, 3,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0
};
static char near tutorialRed[30] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 6, 3, 4, 6, 5, 6, 3, 0, 4, 3, 2, 5
};
extern void far DigTileB(int x, int y);
extern int far DigTileThemB(int x, int y);
extern int far DigTileThemR(int x, int y);
extern int near MeBase;
extern int near ELayerMode;
extern int near MeColor;
extern int near MeType;
extern int far MeEggCarried;
extern int far MeDropAlarm;
extern int far MeMode;
extern int far RebornX;
extern int far RebornY;
extern void far SetMyHealth(int health);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far ResetYellowVars(int plane, int x, int y);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern int far * far FracSineTab;

void far RandWorld(int seed, int blackSize, int redSize, int mapWidth, int mapKind)
{
    int count, y, roll, tries, lim1, lim2, x, wobble, n;

    SetSRandSeed(seed, 0);
    InitSpider();
    MakeMap(mapWidth, mapKind);

    blackSize += blackSize >> 2;
    redSize += redSize >> 2;

    y = 0;
    for (count = 0; count < 64; count++) {
        for (x = 0; x < 64; x++) {
            MapB[count][x] = 0x2e;
            MapR[count][x] = 0x2e;
            ExitMapB[count][x] = 0;
            ExitMapR[count][x] = 0;
            LifeB[count][x] = 0;
            LifeR[count][x] = 0;
            LifeA[count][x] = 0;
            LifeA[count + 64][x] = 0;
        }
    }

    for (count = 0; count < 64; count++) {
        if (TERRAINset == 0) {
            MapB[count][y] = SRand4() + 0x1c;
            MapR[count][y] = SRand4() + 0x1c;
        } else {
            if (mapKind > 3)
                MapB[count][y] = SRand1(2) + 0x1c;
            else
                MapB[count][y] = 0x1e;
            if (mapKind > 3)
                MapR[count][y] = SRand1(2) + 0x1c;
            else
                MapR[count][y] = 0x1e;
        }
        ExitMapB[count][y] = 0xff;
        ExitMapR[count][y] = 0xff;
    }

    for (count = 0; count < 64; count++) {
        for (x = 0; x < 32; x++) {
            PherMapF[count][x] = 0;
            PherMapA[count][x] = 0;
            PherMapBN[count][x] = 0;
            PherMapBT[count][x] = 0;
            PherMapRN[count][x] = 0;
            PherMapRT[count][x] = 0;
        }
    }

    tries = 0;
    lim1 = SRand1(6) + 7;
    lim2 = 15 - SRand2();
    n = blackSize;
    while (n > 0) {
        n--;
        count = SGRand(0x80);
        x = SRand64();
        if (MapA[count][x] < 0x50) {
            if (LifeA[count][x] != 0) {
                tries++;
                if (tries < 50)
                    n++;
            } else {
                roll = SRand16();
                if (roll < lim1)
                    LifeA[count][x] = SRand8() + 0x10;
                else if (roll < lim2)
                    LifeA[count][x] = SRand8() + 0x30;
                else if (SRand2())
                    LifeA[count][x] = SRand8() + 0x20;
                else
                    LifeA[count][x] = SRand8() + 0x40;
            }
        }
    }

    tries = 0;
    lim1 = SRand1(6) + 7;
    lim2 = 15 - SRand2();
    n = redSize;
    while (n > 0) {
        n--;
        count = 0x7f - SGRand(0x80);
        x = SRand64();
        if (MapA[count][x] < 0x50) {
            if (LifeA[count][x] != 0) {
                tries++;
                if (tries < 50)
                    n++;
            } else {
                roll = SRand16();
                if (roll < lim1)
                    LifeA[count][x] = SRand8() - 0x70;
                else if (roll < lim2)
                    LifeA[count][x] = SRand8() - 0x50;
                else if (SRand2())
                    LifeA[count][x] = SRand8() - 0x60;
                else
                    LifeA[count][x] = SRand8() - 0x40;
            }
        }
    }

    for (x = 0; x < 64; x++)
        HoleMapR[x] = 0;
    for (x = 0; x < 64; x++)
        HoleMapB[x] = 0;

    if (CurGameType != 2 || blackSize >= 1)
        MakeNewHoleB(0x20);
    if (redSize >= 1)
        MakeNewHoleR(0x20);

    TileTotYR = 0;
    TileTotXR = 0;
    TileTotYB = 0;
    TileTotXB = 0;
    TilesDugB = 0;
    TilesDugR = 0;
    TileMassYR = 0;
    TileMassXR = 0;
    TileMassYB = 0;
    TileMassXB = 0;
    WaterTable = 0x40;

    if (blackSize > 1)
        DigOutBNest(blackSize << 4);
    if (redSize > 1)
        DigOutRNest(redSize << 4);

    BuildAntListA();
    ClearListB();
    ClearListR();

    BlkQueens = 0;
    RedQueens = 0;
    LastBlackEgg[0] = -1;
    LastBlackEgg[1] = -1;
    LastRedEgg[0] = -1;
    LastRedEgg[1] = -1;

    if (redSize > 0) {
        x = 0x20;
        y = 1;
        count = SRand4() + 7;
        if (count > y) {
            do {
                DigTileR(x, y);
                wobble = SRand1(3) - 1;
                if (wobble + x >= 8 && wobble + x <= 0x38)
                    x += wobble;
                y++;
            } while (y < count);
        }

        count = 2;
        do {
            DigTileR(x, y);
            x++;
            y++;
            count--;
        } while (count != 0);

        DigTileR(x, y);
        LastRedEgg[0] = x;
        LastRedEgg[1] = y;

        x += 2;
        DigTileR(x, y);
        DigTileR(x + Dx8[6], y + Dy8[6]);
        DigTileR(x + 2 * Dx8[6], y + 2 * Dy8[6]);
        AddAntToRList(x, y, 0xe2, 9, 0);
        AddAntToRList(x + Dx8[6], y + Dy8[6], 0xea, 9, 0);
        RedQueens++;
    }

    if (blackSize > 0)
        PlaceBlackQueen();
    InitYelloAnt();

    FoodB = 0;
    FoodR = 0;
    FoodA = 0;
    if (CurGameType != 3)
        AddFood(-1, 0);

    HealthB = 100;
    HealthR = 100;

    EditMsgDelay = 0;
    BlackLost = 0;
    RedLost = 0;
    Cycle = 0;

    ClearHistory(0);
    CountAnts();
    InvalEuMap(0, 0, EditColumns, EditRows);

    MapPnt[0] = 0x40;
    AMapPnt[0] = 0x40;
    MapPnt[1] = 0x20;
    AMapPnt[1] = 0x20;
    BMapPnt[0] = 0x20;
    RMapPnt[0] = 0x20;
    BMapPnt[1] = 1;
    RMapPnt[1] = 1;
}

void far RandYard(void)
{
    int __based(__segname("SIMANT_DATA_GROUP")) *seed;

    ClrArrays();
    ClearHistory(1);
    initControls();

    *CurYardPnt = 11;
    *YMapPnt = 11;
    *(CurYardPnt + 1) = 8;
    *(YMapPnt + 1) = 8;

    InitSimYard();

    CurGameTool = -1;
    LastThemeTime = 0;
    TimeTemp = 0;
    LastThemeSong = 0;
    HouseColonies = 0;
    JustToBeMean = 0;
    BlackWon = 0;
    IsGameOver = 0;
    ForSaleState = 0;
    AlwaysHealthy = 0;
    NeverHungry = 0;
    Invincible = 0;
    GameTime = 0L;

    if (CurGameType <= 1)
        MapPlane = 2;
    else
        MapPlane = 1;
    MapMode = MapPlane;
    YardMode = 0;

    for (seed = &YMapSeeds[0][0]; seed < &YMapSeeds[16][0]; seed++)
        *seed = (RRand(0x7fff) - 0xc000) & 0x7fff;

    if (CurGameType == 2)
        RandWorld(YMapSeeds[*(CurYardPnt + 1)][*CurYardPnt], MeNestStarted = 0, 1, *YMapPnt, *(YMapPnt + 1));
    else
        RandWorld(YMapSeeds[*(CurYardPnt + 1)][*CurYardPnt], MeNestStarted = 1, 1, *YMapPnt, *(YMapPnt + 1));

    if (MePlane <= 1) {
        AMapPnt[0] = MeLocX;
        AMapPnt[1] = MeLocY;
    } else if (MePlane == 2) {
        BMapPnt[0] = MeLocX;
        BMapPnt[1] = MeLocY;
    } else {
        RMapPnt[0] = MeLocX;
        RMapPnt[1] = MeLocY;
    }
}

void far GenerateTutorial(void)
{
    int i;

    CurGameType = 1;
    RandYard();
    AddBlackAnts(32);
    AddRedAnts(32);
    FullCount();
    CurGameType = 2;
    SetMapPlane(MePlane);
    for (i = 0; i < 30; i++) {
        YMapPopB[tutorialX[i]][tutorialY[i]] = tutorialBlack[i] << 5;
        YMapPopR[tutorialX[i]][tutorialY[i]] = tutorialRed[i] << 5;
    }
}

void far DigOutBNest(int count)
{
    int dir, y, x, newX, newY;

    dir = 4;
    y = 1;
    x = 0x20;
    DigTileB(x, y);
    if (count == 0)
        return;
    for (;;) {
        dir = (SRand1(5) + dir - 3) & 7;
        newX = x + Dx8[dir];
        newY = y + Dy8[dir];
        if (newX < 1) {
            newX = 1;
            dir = 2;
        } else if (newX > 0x3e) {
            newX = 0x3e;
            dir = 6;
        }
        if (newY < 2) {
            newY = 1;
            dir = 4;
        } else if (newY > 0x3e) {
            newY = 0x3e;
            dir = 0;
        }
        if (DigTileThemB(newX, newY) == 1) {
            x = newX;
            y = newY;
            if (y == 1 && HoleMapB[x] == 0)
                MakeNewHoleB(newX);
        }
        if (--count == 0)
            break;
    }
}

void far DigOutRNest(int count)
{
    int dir, y, x, newX, newY;

    dir = 4;
    y = 1;
    x = 0x20;
    DigTileR(x, y);
    if (count == 0)
        return;
    for (;;) {
        dir = (SRand1(5) + dir - 3) & 7;
        newX = x + Dx8[dir];
        newY = y + Dy8[dir];
        if (newX < 1) {
            newX = 1;
            dir = 2;
        } else if (newX > 0x3e) {
            newX = 0x3e;
            dir = 6;
        }
        if (newY < 2) {
            newY = 1;
            dir = 4;
        } else if (newY > 0x3e) {
            newY = 0x3e;
            dir = 0;
        }
        if (DigTileThemR(newX, newY) == 1) {
            x = newX;
            y = newY;
            if (y == 1 && HoleMapR[x] == 0)
                MakeNewHoleR(newX);
        }
        if (--count == 0)
            break;
    }
}

void far InitYelloAnt(void)
{
    MeBase = 0;
    MeEggCarried = 0xfd;
    if (MeDropAlarm != 0) {
        MeDropAlarm = 0;
        ELayerMode = -1;
    }
    SetMyHealth(100);

    if (CurGameType != 3) {
        MeColor = 0;
        MeMode = 0;
        if (CurGameType != 2 || MeNestStarted != 0) {
            SetMyLife(2, RebornX, RebornY, 0x10, 2, 0xff);
        } else {
            int x, y;

            x = 0x40;
            y = 0x20;
            {
                int col, count, tries;

                for (tries = 0; tries < 100; tries++) {
                    count = SRand16() - SRand16() + 0x20;
                    col = SRand8() - SRand8() + 0x20;
                    if (MapA[count][col] < 0x10) {
                        x = count;
                        y = col;
                        break;
                    }
                }
            }
            SetMyLife(1, x, y, 0x40, 2, 0xff);
        }
        goto done;
    }
    MePlane = 1;
    MeColor = 0;
    MeMode = 2;
    MeLocX = 0x40;
    MeLocY = 0x20;
    MeType = 0x10;

done:
    ResetYellowVars(MePlane, MeLocX, MeLocY);
}

void far PlaceBlackQueen(void)
{
    int count, x, y, wobble;

    wobble = 0;
    x = 0x20;
    y = 1;
    count = SRand4() + 7;
    if (count > y) {
        do {
            DigTileB(x, y);
            if (SRand2() == 0)
                wobble = SRand1(3) - 1;
            if (wobble + x >= 8 && wobble + x <= 0x38)
                x += wobble;
            y++;
        } while (y < count);
    }

    count = 2;
    do {
        DigTileB(x, y);
        x++;
        y++;
        count--;
    } while (count != 0);

    DigTileB(x, y);
    LastBlackEgg[0] = x;
    LastBlackEgg[1] = y;
    RebornX = x;
    RebornY = y;

    x += 2;
    DigTileB(x, y);
    DigTileB(x + Dx8[6], y + Dy8[6]);
    DigTileB(x + 2 * Dx8[6], y + 2 * Dy8[6]);
    AddAntToBList(x, y, 0x62, 9, 0);
    AddAntToBList(x + Dx8[6], y + Dy8[6], 0x6a, 9, 0);
    BlkQueens++;
}

void far MakeBlkQueen(int x, int y, int dir)
{
    int d;

    d = dir ^ 4;
    DigTileB(x, y);
    DigTileB(x + Dx8[d], y + Dy8[d]);
    DigTileB(x + 2 * Dx8[d], y + 2 * Dy8[d]);
    AddAntToBList(x, y, dir + 0x60, 9, 0);
    AddAntToBList(x + Dx8[d], y + Dy8[d], dir + 0x68, 9, 0);
    BlkQueens++;
}

void far PlaceRedQueen(void)
{
    int count, x, y, wobble;

    x = 0x20;
    y = 1;
    count = SRand4() + 7;
    if (count > y) {
        do {
            DigTileR(x, y);
            wobble = SRand1(3) - 1;
            if (wobble + x >= 8 && wobble + x <= 0x38)
                x += wobble;
            y++;
        } while (y < count);
    }

    count = 2;
    do {
        DigTileR(x, y);
        x++;
        y++;
        count--;
    } while (count != 0);

    DigTileR(x, y);
    LastRedEgg[0] = x;
    LastRedEgg[1] = y;

    x += 2;
    DigTileR(x, y);
    DigTileR(x + Dx8[6], y + Dy8[6]);
    DigTileR(x + 2 * Dx8[6], y + 2 * Dy8[6]);
    AddAntToRList(x, y, 0xe2, 9, 0);
    AddAntToRList(x + Dx8[6], y + Dy8[6], 0xea, 9, 0);
    RedQueens++;
}

void far MakeRedQueen(int x, int y, int dir)
{
    int d;

    d = dir ^ 4;
    DigTileR(x, y);
    DigTileR(x + Dx8[d], y + Dy8[d]);
    DigTileR(x + 2 * Dx8[d], y + 2 * Dy8[d]);
    AddAntToRList(x, y, dir + 0xE0, 9, 0);
    AddAntToRList(x + Dx8[d], y + Dy8[d], dir + 0xE8, 9, 0);
    RedQueens++;
}

int fracSIN(int angle)
{
    int index;
    int value;

    index = angle & 0x7f;
    if (index > 0x3f)
        index = 0x80 - index;

    if (index == 0x40)
        value = 0x7fff;
    else {
        index &= 0x3f;
        value = FracSineTab[index];
    }
    if ((angle & 0xff) > 0x7f)
        value = -value;

done:
    return value;
}

int fracCOS(int angle)
{
    int index;
    int value;

    index = angle - 0xc0;
    index &= 0x7f;
    if (index > 0x3f)
        index = 0x80 - index;

    if (index == 0x40)
        value = 0x7fff;
    else {
        index &= 0x3f;
        value = FracSineTab[index];
    }
    if (((angle + 0x40) & 0xff) > 0x7f)
        value = -value;

    return value;
}

