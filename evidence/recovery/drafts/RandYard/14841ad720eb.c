/*
 * RandYard: build a fresh random yard and its first world.  Clears the
 * ant arrays (ClrArrays), the history (ClearHistory(1)) and the controls
 * (initControls); the current yard position CurYardPnt and the yard map
 * position YMapPnt are set to (11, 8); InitSimYard; the current tool is
 * cleared to -1, the long LastThemeTime/TimeTemp/GameTime and the
 * LastThemeSong, HouseColonies, JustToBeMean, BlackWon, IsGameOver,
 * ForSaleState, AlwaysHealthy, NeverHungry and Invincible flags are
 * zeroed; MapPlane (and MapMode) is 2 for game types up to 1 and 1
 * otherwise; YardMode is 0.  Every one of the 16x12 yard seeds
 * (YMapSeeds, SIMANT_DATA_GROUP based, walked with a based pointer)
 * becomes (RRand(0x7fff) - 0xc000) & 0x7fff.  RandWorld then generates
 * the world at the current yard's seed with red size 1 and the black
 * nest already started (black size 1, MeNestStarted = 1) except in game
 * type 2 where the player starts the nest (black size 0, MeNestStarted =
 * 0); finally the player's map view point (A, B or R map by MePlane) is
 * set to MeLocX/MeLocY.
 *
 * Declarations (agentZ, og profile): YMapSeeds shares the SIMANT_DATA_GROUP
 * pool word 0xc5b6 with RandWorld's exit maps, so it is __based on that
 * segment; the other far objects own their pool words.  LastThemeTime,
 * TimeTemp and GameTime are 32-bit (sub reg,reg then high word first).
 * CurYardPnt/YMapPnt are read and written through the decayed array
 * pointers (*CurYardPnt, *(CurYardPnt + 1)); under og the compiler keeps
 * each far address as a CSE temporary with a frame home (enter 0x10, les
 * bx,[bp-n] reloads after the calls), which plain array subscripts do not
 * produce.  MapPlane is an if/else, not a conditional expression: og
 * hoists a conditional expression above the preceding zero stores.
 * MeNestStarted is assigned inside RandWorld's black-size argument, which
 * places its store between the argument pushes; GameTime = 0L directly
 * precedes the if/else so its zero survives in CX for YardMode.
 */
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
extern int far CurGameType;
extern int near MapPlane;
extern int far MapMode;
extern int near YardMode;
extern int __based(__segname("SIMANT_DATA_GROUP")) YMapSeeds[16][12];
extern int far MeNestStarted;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int far AMapPnt[2];
extern int far BMapPnt[2];
extern int far RMapPnt[2];

extern void far ClrArrays(void);
extern void far ClearHistory(int a);
extern void far initControls(void);
extern void far InitSimYard(void);
extern int far RRand(int range);
extern void far RandWorld(int seed, int blackSize, int redSize, int mapWidth, int mapKind);

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
