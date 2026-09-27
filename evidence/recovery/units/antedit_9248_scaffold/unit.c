/* Candidate translation unit antedit_9248_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _SpecialTutorialInit, _DoPreLoadInits, _DoLoadInitializations, _ClearLastFileName
 * SCAFFOLDED: unclaimed members OPENDLG are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern char far * far * far MiscStrs;
extern char far * far strrchr(const char far *text, int character);
extern int far stricmp(const char far *a, const char far *b);
extern void far GenerateTutorial(void);
extern void far SetEditWinTitle(char far *title);
extern void far InitSimVars(void);
extern void far SeedSRand(void);
extern void far EditMessage(long position, int a, int b, int mode);
extern int far JustXfered;
extern unsigned long far LastThemeTime;
extern unsigned long far TimeTemp;
extern unsigned long far EditMsgDelay;
extern void far RandYard(void);
extern int far TERRAINset;
extern int far CurGndTileID;
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern int far MeMode;
extern int near MapPlane;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
struct MapPoint { int x; int y; };
extern struct MapPoint far YMapPnt;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;
extern void far OverlayTileSet(int type, int id);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far FullCount(void);
extern void far SetDefaultWindows(void);
extern void far CenterEdit(int x, int y);
extern void far UpdateLayQueenModeDisplay(void);
extern void far SetDefaultWindPrompt(int mode);
extern unsigned char far editBufInvalidFlag[];


void far pool_stub_OPENDLG(void);
void ClearLastFileName(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_OPENDLG)
#pragma alloc_text(RUN2_TEXT, ClearLastFileName)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member OPENDLG.
 * It only reproduces the object's selector-pool allocation order for the
 * words C170; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_OPENDLG(void)
{
    volatile int t;

    t = editBufInvalidFlag[0];
}

int far SpecialTutorialInit(char far *name)
{
    char far *base;
    int tutorial;

    base = strrchr(name, 0x5c);
    if (base)
        base++;
    else
        base = name;
    tutorial = stricmp(base, MiscStrs[0]) == 0;
    if (tutorial) {
        GenerateTutorial();
        SetEditWinTitle("Tutorial Game");
        InitSimVars();
        SeedSRand();
        EditMessage(0L, -2, -1, 1);
    } else
        SetEditWinTitle(base);
    return tutorial;
}

void DoPreLoadInits(void)
{
    JustXfered = 1;
    LastThemeTime = 0;
    TimeTemp = 300;
    EditMsgDelay = 0;
    RandYard();
}

int far DoLoadInitializations(void)
{
    int row;
    int column;
    int index;
    int x;
    int y;
    struct MapPoint pnt;

    if (TERRAINset != 1)
        CurGndTileID = 0x3e8;
    else
        CurGndTileID = 0x3e9;
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

    pnt.x = MeLocX;
    pnt.y = MeLocY;
    switch (MePlane) {
    case 0:
        YMapPnt = pnt;
        break;
    case 1:
        AMapPnt = pnt;
        break;
    case 2:
        BMapPnt = pnt;
        break;
    case 3:
        RMapPnt = pnt;
        break;
    }

    SetDefaultWindows();
    if (MapPlane == MePlane)
        CenterEdit(MeLocX, MeLocY);
    UpdateLayQueenModeDisplay();
    SetDefaultWindPrompt(1);
    return 1;
}

void ClearLastFileName(void)
{
    editBufInvalidFlag[1834] = 0;
}

