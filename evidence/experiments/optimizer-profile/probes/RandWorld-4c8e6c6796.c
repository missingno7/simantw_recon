/*
 * RandWorld: generate a new game world.  Parameters (in declaration
 * order, matching push order into SetSRandSeed/MakeMap): seed, blackSize
 * (scaled by *1.25 and later used both as the initial DigOutBNest tunnel
 * length << 4 and as the terrain-seeding budget for the black pass),
 * redSize (same role, mirrored for red), mapWidth, mapKind (both passed
 * straight through to MakeMap and gate the initial terrain-clearing
 * pass's border seeding).
 *
 * Steps: seed the PRNG and call InitSpider/MakeMap; scale blackSize and
 * redSize by *1.25; clear the 64x64 MapB/MapR to grass (0x2e), the far
 * ExitMapB/ExitMapR to 0, and the near LifeB/LifeR/LifeA (and an unnamed
 * near companion array immediately after LifeA) to 0; seed a border row
 * with rock/edge tiles (TERRAINset-gated); run two near-identical
 * "vegetation" seeding passes over LifeA -- one budgeted by blackSize,
 * one by redSize -- that pick a random empty (LifeA==0, MapA<0x50) cell
 * and give it a SRand8()-based tile value in a range chosen by two
 * SRand16()/SRand2() thresholds (black adds 0x10/0x20/0x30/0x40, red
 * subtracts the same steps); clear the HoleMapR/HoleMapB tables; clear
 * the accumulated tile-total/mass/dug counters and the water table; dig
 * the initial black/red nest tunnels (DigOutBNest/DigOutRNest) when
 * their size exceeds 1; rebuild the A ant list and clear the B/R lists;
 * reset the queen counters and last-egg positions; when redSize > 0,
 * place the initial red queen using the same random-walk-then-chamber
 * logic as PlaceRedQueen (inlined here rather than called); when
 * blackSize > 0, call PlaceBlackQueen and InitYelloAnt, reset the food
 * counters and add the initial food pile unless CurGameType==3, seed
 * both colonies' health to 100; clear the edit/lost/cycle counters, run
 * ClearHistory/CountAnts/InvalEuMap, and set the map/colony view points.
 */
extern unsigned char near MapA[];
extern unsigned char near MapB[];
extern unsigned char near MapR[];
extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far ExitMapB[];
extern unsigned char far ExitMapR[];
extern unsigned char far HoleMapB[64];
extern unsigned char far HoleMapR[64];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned int far TERRAINset;
extern int far CurGameType;
extern int far TileTotYR[2];
extern int far TileTotXR[2];
extern int far TileTotYB[2];
extern int far TileTotXB[2];
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
extern int far EditMsgDelay[2];
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
extern int far SRand4(void);
extern int far SRand2(void);
extern int far SRand1(int range);
extern int far SGRand(int range);
extern int far SRand64(void);
extern int far SRand16(void);
extern int far SRand8(void);
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

void far RandWorld(int seed, int blackSize, int redSize, int mapWidth, int mapKind)
{
    int row, col, tries, lim1, lim2, roll, cellRow, tile, budget;
    int dir, i, j, x, y, newX, newY, cand, count;

    SetSRandSeed(seed, 0);
    InitSpider();
    MakeMap(mapWidth, mapKind);

    blackSize += blackSize >> 2;
    redSize += redSize >> 2;

    for (row = 0; row < 0x1000; row += 0x40) {
        for (col = 0; col < 0x40; col++) {
            MapB[row + col] = 0x2e;
            MapR[row + col] = 0x2e;
            ExitMapB[row + col] = 0;
            ExitMapR[row + col] = 0;
            LifeB[row + col] = 0;
            LifeR[row + col] = 0;
            LifeA[row + col] = 0;
            LifeA[0x1000 + row + col] = 0;
        }
    }

    for (row = 0; row < 0x1000; row += 0x40) {
        if (TERRAINset == 0) {
            tile = SRand4() + 0x1c;
            LifeA[row] = tile;
            tile = SRand4() + 0x1c;
        } else if (mapWidth > 3) {
            tile = SRand1(2) + 0x1c;
            LifeA[row] = tile;
        } else {
            LifeA[row] = 0x1e;
            tile = 0x1e;
        }
        if (mapWidth > 3)
            SRand1(2);
        LifeA[row + 0x40] = 0x1e;
        ExitMapB[row] = 0xff;
        ExitMapR[row] = 0xff;
    }

    tries = 0;
    lim1 = SRand1(6) + 7;
    lim2 = -(SRand2() - 0xf);
    budget = blackSize;
    if (budget > 0) {
        do {
            budget--;
            row = SGRand(0x80);
            col = SRand64();
            cellRow = (row << 6) + col;
            if (MapA[cellRow] < 0x50) {
                if (LifeA[cellRow] != 0) {
                    if (++tries < 0x32)
                        budget++;
                } else {
                    roll = SRand16();
                    if (roll < lim1)
                        tile = SRand8() + 0x10;
                    else if (lim2 <= roll)
                        tile = SRand8() + 0x30;
                    else if (SRand2() == 0)
                        tile = SRand8() + 0x40;
                    else
                        tile = SRand8() + 0x20;
                    LifeA[cellRow] = tile;
                }
            }
        } while (budget > 0);
    }

    tries = 0;
    lim1 = SRand1(6) + 7;
    lim2 = -(SRand2() - 0xf);
    budget = redSize;
    if (budget > 0) {
        do {
            budget--;
            row = SGRand(0x80);
            col = SRand64();
            cellRow = (row << 6) + col;
            if (MapA[cellRow] < 0x50) {
                if (LifeA[cellRow] != 0) {
                    if (++tries < 0x32)
                        budget++;
                } else {
                    roll = SRand16();
                    if (roll < lim1)
                        tile = SRand8() - 0x70;
                    else if (lim2 <= roll)
                        tile = SRand8() - 0x50;
                    else if (SRand2() == 0)
                        tile = SRand8() - 0x60;
                    else
                        tile = SRand8() - 0x40;
                    LifeA[cellRow] = tile;
                }
            }
        } while (budget > 0);
    }

    for (i = 0; i < 64; i++)
        HoleMapR[i] = 0;
    for (i = 0; i < 64; i++)
        HoleMapB[i] = 0;

    if (CurGameType != 2 || blackSize >= 1)
        MakeNewHoleB(0x20);
    if (redSize >= 1)
        MakeNewHoleR(0x20);

    TileTotYR[1] = 0;
    TileTotYR[0] = 0;
    TileTotXR[1] = 0;
    TileTotXR[0] = 0;
    TileTotYB[1] = 0;
    TileTotYB[0] = 0;
    TileTotXB[1] = 0;
    TileTotXB[0] = 0;
    TilesDugB = 0;
    TilesDugR = 0;
    TileMassYR = 0;
    TileMassXR = 0;
    TileMassYB = 0;
    TileMassXB = 0;
    WaterTable = 0x40;

    if (mapWidth > 1)
        DigOutBNest(mapWidth << 4);
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
        i = 1;
        count = SRand4() + 7;
        if (count > i) {
            do {
                DigTileR(x, i);
                dir = SRand1(3);
                dir--;
                cand = dir + x;
                if (cand >= 8 && cand <= 0x38)
                    x = cand;
                i++;
            } while (i < count);
        }
        y = i;

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

    if (blackSize > 0) {
        PlaceBlackQueen();
        InitYelloAnt();

        FoodB = 0;
        FoodR = 0;
        FoodA = 0;
        if (CurGameType != 3)
            AddFood(-1, 0);

        HealthB = 0x64;
        HealthR = 0x64;

        EditMsgDelay[1] = 0;
        EditMsgDelay[0] = 0;
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
}
