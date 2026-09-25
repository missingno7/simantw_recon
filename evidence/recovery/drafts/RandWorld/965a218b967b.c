/*
 * RandWorld(seed, blackSize, redSize, mapWidth, mapKind): generate a new
 * random game world.  Seed the PRNG, InitSpider, MakeMap(mapWidth,
 * mapKind); scale blackSize/redSize by 1.25.  Clear the 64x64 near
 * MapB/MapR to grass (0x2e), the far ExitMapB/ExitMapR to 0 and the near
 * LifeB/LifeR and both 64x64 halves of the 128x64 LifeA to 0.  Seed column
 * y = 0 of every row of MapB/MapR with an edge tile: with TERRAINset == 0 a
 * random SRand4()+0x1c tile, otherwise SRand1(2)+0x1c when mapKind > 3 or
 * the fixed 0x1e; ExitMapB/ExitMapR column 0 get 0xff.  Clear the six 64x32
 * pheromone maps (PherMapF/A/BN/BT/RN/RT).  Two vegetation passes over
 * LifeA budgeted by blackSize (rows 0..127 from SGRand) and redSize
 * (mirrored rows 0x7f-SGRand): each pick lands on an empty cell (MapA <
 * 0x50, LifeA == 0) and receives a SRand8()-based tile in one of four
 * bands chosen by an SRand16() roll against lim1 = SRand1(6)+7 and lim2 =
 * 15-SRand2() (black adds 0x10/0x30/0x20/0x40, red subtracts
 * 0x70/0x50/0x60/0x40); an occupied pick is retried while fewer than 50
 * collisions occurred.  Clear HoleMapR/HoleMapB, open the nest holes
 * (black unless a size-0 colony in game type 2, red when redSize >= 1),
 * reset the long tile totals and the mass/dug counters, set WaterTable to
 * 0x40, dig the initial nests (size << 4 when size > 1), rebuild list A
 * and clear lists B/R, reset the queen counts and last-egg positions.
 * When redSize > 0 the red queen is placed inline with the PlaceRedQueen
 * tunnel walk; when blackSize > 0 PlaceBlackQueen is called.  Then
 * InitYelloAnt, the food counters are cleared and the start food added
 * unless CurGameType == 3, both colonies get health 100, the long
 * EditMsgDelay and the lost/cycle counters are cleared,
 * ClearHistory/CountAnts/InvalEuMap run and the map view points are reset.
 *
 * Declarations (agentZ, og profile): ExitMapB/ExitMapR and the six PherMap
 * arrays share one SIMANT_DATA_GROUP selector in the original (one
 * immediate segment load hoisted into ES/DS for each clearing loop, one
 * pool word 0xc5b6 for both exit maps), so they are declared __based on
 * that named segment as IsMMWaveAvail's admitted word is; every other far
 * object owns its own pool word.  TileTotYR/XR/YB/XB and EditMsgDelay are
 * 32-bit (sub ax,ax after the selector load, high word stored first, as in
 * DoPreLoadInits).  The cell index of the vegetation passes is the CSE of
 * LifeA[count][x] with a frame home, not a named local; `roll` is declared
 * before lim1/lim2 so the second band test keeps the roll in AX
 * (cmp [lim2],ax).  The edge-row loop indexes column `y`, which the
 * optimizer propagates as 0 while keeping the live zero store (xor ax,ax
 * shared with the first loop's counter).  Queen-placement locals follow
 * the exact og PlaceRedQueen source.
 */
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
