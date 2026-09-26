/*
 * DoLoadInitializations clears the A/B/R life planes, restores occupied
 * cells from their MAPSYM list records, then initializes the active player
 * and editor view after loading a world.
 */
extern int far TERRAINset;
extern int far CurGndTileID;
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char far AlistX[];
extern unsigned char far AlistY[];
extern unsigned char far AlistT[];
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];
extern unsigned char far BlistT[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];
extern unsigned char far RlistT[];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern int near MeMode;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern int near MapPlane;
struct MapPoint { int x; int y; };
extern struct MapPoint far YMapPnt;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;
extern void far OverlayTileSet(int type, int id);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far FullCount(void);
extern void far SetDefaultWindows(void);
extern int far CenterEdit(int x, int y);
extern void far UpdateLayQueenModeDisplay(void);
extern void far SetDefaultWindPrompt(int mode);

void far DoLoadInitializations(void)
{
    int row;
    int column;
    int index;
    int x;
    int y;

    if (TERRAINset == 1)
        CurGndTileID = 0x3e9;
    else
        CurGndTileID = 0x3e8;
    OverlayTileSet(0, CurGndTileID);

    for (row = 0; row < 128; ++row) {
        for (column = 0; column < 64; ++column)
            LifeA[row][column] = 0;
    }
    for (row = 0; row < 64; ++row) {
        for (column = 0; column < 64; ++column)
            LifeB[row][column] = 0;
    }
    for (row = 0; row < 64; ++row) {
        for (column = 0; column < 64; ++column)
            LifeR[row][column] = 0;
    }

    index = ListIndexA;
    while (index >= 0) {
        x = AlistX[index];
        y = AlistY[index];
        LifeA[x][y] = AlistT[index];
        --index;
    }
    index = ListIndexB;
    while (index >= 0) {
        x = BlistX[index];
        y = BlistY[index];
        LifeB[x][y] = BlistT[index];
        --index;
    }
    index = ListIndexR;
    while (index >= 0) {
        x = RlistX[index];
        y = RlistY[index];
        LifeR[x][y] = RlistT[index];
        --index;
    }

    if (MeMode == 0)
        SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
    FullCount();

    x = MeLocX;
    y = MeLocY;
    switch (MePlane) {
    case 0:
        YMapPnt.x = x;
        YMapPnt.y = y;
        break;
    case 1:
        AMapPnt.x = x;
        AMapPnt.y = y;
        break;
    case 2:
        BMapPnt.x = x;
        BMapPnt.y = y;
        break;
    default:
        RMapPnt.x = x;
        RMapPnt.y = y;
        break;
    }

    SetDefaultWindows();
    if (MapPlane == MePlane) {
        CenterEdit(MeLocX, MeLocY);
        UpdateLayQueenModeDisplay();
        SetDefaultWindPrompt(1);
    }
}
