/* Candidate translation unit antedit_7022_DoTool_15_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoTool, _ReDrawMapEdit, _ClearLifeB, _ClearLifeR, _ExpAddAnt, _ExpAddFood, _ConnectWall, _WallNeighbors, _IsItWall, _FillDirtB, _FillDirtR, _SmoothMany, _IsValidSLoc, _GetSM, _SetSM
 * SCAFFOLDED: unclaimed members _processExp, _DropWall, _ExpDig, _IncFoodHere are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far CurExpTool;
extern int near MapPlane;
extern int far ExpLastPnt[2];
extern signed char far ExpSubStates[];
extern int far GetLife(int plane, int x, int y);
extern void far MagnifyMenu(int x, int y, int plane);
extern void far DropWall(int lastX, int lastY, int x, int y);
extern void far ExpDig(int lastX, int lastY, int x, int y);
extern void far ExpAddAnt(int x, int y);
extern int far IncFoodHere(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far SRand1(int range);
extern int far IsValidLocation(int plane, int x, int y);
extern void far ExpIncSmell(int x, int y);
extern void far ExpKillAnts(int x, int y);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinOpen(int window);
extern void far UpdateEdit(void);
extern void far DrawEdit(void);
extern void far MakeDMap(int mode);
extern void far DrawMap(void);
extern int far ListIndexB;
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];
extern int far ListIndexR;
extern unsigned char near LifeR[];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far IsClearTile(int plane, int x, int y);
extern void far AddAntToAList(int x, int y, int type, int a, int b);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern void far DigTileB(int x, int y);
extern void far DigTileR(int x, int y);
#define SUBSTATE(i) ExpSubStates[i]
extern unsigned char near MapA[][64];
extern int far GetMap(int plane, int x, int y);
static unsigned char near wallShape[16] = {
    0x60, 0x64, 0x65, 0x66, 0x62, 0x61, 0x62, 0x61,
    0x63, 0x63, 0x60, 0x60, 0x67, 0x67, 0x67, 0x67
};
#define ExitMapB ((unsigned char (far *)[64])((unsigned char far *)&Dx8 + 0x3A4))  /* pool word C27A: one object, MAPSYM _Dx8+932 */
extern int far TilesDugB;
extern long far TileTotXB;
extern long far TileTotYB;
extern void far SmoothEdgesB(int x, int y);
#define ExitMapR ((unsigned char (far *)[64])((unsigned char far *)&Dx8 + 0x13A4))  /* pool word C27A: one object, MAPSYM _Dx8+5028 */
extern int far TilesDugR;
extern long far TileTotXR;
extern long far TileTotYR;
extern void far SmoothEdgesR(int x, int y);
extern void far SmoothACell(int x, int y);

extern int far UDcntr;  /* scaffold reference for pool word C260 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapTileRect;  /* scaffold reference for pool word C262 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapXsize;  /* scaffold reference for pool word C264 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapYsize;  /* scaffold reference for pool word C266 (segment 9, MAPSYM_SITE_NAME) */
extern int far editTileRect;  /* scaffold reference for pool word C268 (segment 9, MAPSYM_SITE_NAME) */
extern int far MapPnt;  /* scaffold reference for pool word C26A (segment 9, MAPSYM_SITE_NAME) */
extern int far ExpCursAnimCycle;  /* scaffold reference for pool word C26E (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C272 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dy9;  /* scaffold reference for pool word C274 (segment 8, MAPSYM_SITE_NAME) */
extern int far WindPromptStrs;  /* scaffold reference for pool word C276 (segment 9, MAPSYM_SITE_NAME) */
extern int far FoodB;  /* scaffold reference for pool word C27E (segment 9, MAPSYM_SITE_NAME) */
extern int far FoodR;  /* scaffold reference for pool word C280 (segment 9, MAPSYM_SITE_NAME) */
extern int far FoodA;  /* scaffold reference for pool word C282 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_processExp(void);
void far pool_stub_DropWall(void);
void far pool_stub_ExpDig(void);
void far pool_stub_IncFoodHere(void);
void far ReDrawMapEdit(unsigned char flags);
void far ClearLifeB(int life, int column);
void far ClearLifeR(int life, int column);
void far ExpAddAnt(int x, int y);
void far ExpAddFood(int x, int y);
void far ConnectWall(int x, int y);
int far WallNeighbors(int x, int y, int plane);
int IsItWall(int value);
void far FillDirtB(int x, int y);
void far FillDirtR(int x, int y);
void far SmoothMany(int x, int y);
int IsValidSLoc(int x,int y);
int far GetSM(int x, int y);
void far SetSM(int x, int y, int val);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_processExp)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DropWall)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ExpDig)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_IncFoodHere)
#pragma alloc_text(RUN2_TEXT, ReDrawMapEdit)
#pragma alloc_text(RUN3_TEXT, ClearLifeB, ClearLifeR, ExpAddAnt, ExpAddFood)
#pragma alloc_text(RUN4_TEXT, ConnectWall, WallNeighbors, IsItWall, FillDirtB)
#pragma alloc_text(RUN4_TEXT, FillDirtR, SmoothMany)
#pragma alloc_text(RUN5_TEXT, IsValidSLoc, GetSM, SetSM)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _processExp.
 * It only reproduces the object's selector-pool allocation order for the
 * words C25E C260 C262 C264 C266 C268 C26A C26C C26E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_processExp(void)
{
    volatile int t;

    t = ExpLastPnt[0];
    t = UDcntr;
    t = mapTileRect;
    t = mapXsize;
    t = mapYsize;
    t = editTileRect;
    t = MapPnt;
    t = (int)CurExpTool;
    t = ExpCursAnimCycle;
}

void far DoTool(int x, int y)
{
    int i;
    int fx;
    int fy;

    switch (CurExpTool) {
    case 0:
        if (GetLife(MapPlane, x, y))
            MagnifyMenu(x, y, MapPlane);
        break;
    case 1:
        if (MapPlane == 1 || MapPlane == 0)
            DropWall(ExpLastPnt[0], ExpLastPnt[1], x, y);
        break;
    case 2:
        ExpDig(ExpLastPnt[0], ExpLastPnt[1], x, y);
        break;
    case 3:
        ExpAddAnt(x, y);
        break;
    case 4:
        if (ExpSubStates[4] == 0) {
            if (IncFoodHere(x, y))
                myBeginSound(0x1d, 0, 0x7e);
        } else {
            myBeginSound(0x20, 0, 0x7e);
            for (i = 20; i != 0; i--) {
                fx = SRand1(9) + x - 4;
                fy = SRand1(9) + y - 4;
                if (IsValidLocation(MapPlane, fx, fy))
                    IncFoodHere(fx, fy);
            }
        }
        break;
    case 5:
        ExpIncSmell(x, y);
        break;
    case 6:
        ExpKillAnts(x, y);
        break;
    }
}

void far ReDrawMapEdit(unsigned char flags)
{
    if (win_IsWinInFront(0)) {
        UpdateEdit();
        DrawEdit();
        if (!win_IsWinOpen(0x100))
            return;
        if (flags & 3)
            return;
        MakeDMap(1);
        DrawMap();
        return;
    }

    MakeDMap(1);
    DrawMap();
    if (!win_IsWinOpen(0))
        return;
    if (flags & 3)
        return;
    UpdateEdit();
    DrawEdit();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DropWall.
 * It only reproduces the object's selector-pool allocation order for the
 * words C272 C274; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DropWall(void)
{
    volatile int t;

    t = Dx9;
    t = Dy9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ExpDig.
 * It only reproduces the object's selector-pool allocation order for the
 * words C276 C278 C27A C27C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ExpDig(void)
{
    volatile int t;

    t = WindPromptStrs;
    t = (int)ListIndexB;
    t = Dx8[0];
    t = (int)ListIndexR;
}

void far ClearLifeB(int life, int column)
{
    int index;

    index = ListIndexB;
    while (index) {
        --index;
        if (Dx8[index + 0x3d18] != 0 &&
            Dx8[index + 0x3736] == life &&
            Dx8[index + 0x392c] == column)
            Dx8[index + 0x3d18] = 0;
    }

    LifeB[((unsigned int)life << 6) + column] = 0;
}

void far ClearLifeR(int life, int column)
{
    int index;

    index = ListIndexR;
    while (index) {
        --index;
        if (Dx8[index + 0x46e6] != 0 &&
            Dx8[index + 0x4104] == life &&
            Dx8[index + 0x42fa] == column)
            Dx8[index + 0x46e6] = 0;
    }

    LifeR[((unsigned int)life << 6) + column] = 0;
}

void far ExpAddAnt(int x, int y)
{
    int amt;

    amt = SRand1(8) + 16;
    if (ExpSubStates[3] == 1)
        amt += 0x80;

    switch (MapPlane) {
    case 0:
    case 1:
        if (IsClearTile(1, x, y))
            AddAntToAList(x, y, amt, 2, 0);
        else
            return;
        break;
    case 2:
        if (y == 0)
            return;
        if (MapB[x][y] >= 0x1c)
            DigTileB(x, y);
        if (amt > 0x80)
            AddAntToBList(x, y, amt, 7, 0);
        else
            AddAntToBList(x, y, amt, 2, 0);
        break;
    case 3:
        if (y == 0)
            return;
        if (MapR[x][y] >= 0x1c)
            DigTileR(x, y);
        if (amt > 0x80)
            AddAntToRList(x, y, amt, 2, 0);
        else
            AddAntToRList(x, y, amt, 7, 0);
        break;
    }

    myBeginSound(0x1c, 0, 0x7e);
}

void far ExpAddFood(int x, int y)
{
    int i;
    int fx;
    int fy;

    if (SUBSTATE(4) == 0) {
        if (IncFoodHere(x, y))
            myBeginSound(0x1d, 0, 0x7e);
    } else {
        myBeginSound(0x20, 0, 0x7e);
        for (i = 20; i != 0; i--) {
            fx = SRand1(9) + x - 4;
            fy = SRand1(9) + y - 4;
            if (IsValidLocation(MapPlane, fx, fy))
                IncFoodHere(fx, fy);
        }
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _IncFoodHere.
 * It only reproduces the object's selector-pool allocation order for the
 * words C27E C280 C282; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_IncFoodHere(void)
{
    volatile int t;

    t = FoodB;
    t = FoodR;
    t = FoodA;
}

void far ConnectWall(int x, int y)
{
    int w;
    int ww;
    int si;
    int cell;
    int isWall;
    unsigned char near *cellPtr;

    cellPtr = &MapA[x][y];
    cell = *cellPtr;
    isWall = (cell >= 0x60 && cell <= 0x67);
    if (isWall) {
        si = 0;

        w = GetMap(1, x - 1, y);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;
        si <<= 1;

        w = GetMap(1, x, y + 1);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;
        si <<= 1;

        w = GetMap(1, x + 1, y);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;
        si <<= 1;

        w = GetMap(1, x, y - 1);
        ww = (w >= 0x60 && w <= 0x67);
        if (ww == 1)
            si++;

        *cellPtr = wallShape[si];
    }
}

int far WallNeighbors(int x, int y, int plane)
{
    int m;
    int w;
    int result;

    result = 0;

    m = GetMap(plane, x - 1, y);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;
    result *= 2;

    m = GetMap(plane, x, y + 1);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;
    result *= 2;

    m = GetMap(plane, x + 1, y);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;
    result *= 2;

    m = GetMap(plane, x, y - 1);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;

    return result;
}

int IsItWall(int value)
{
    return value >= 96 && value <= 103;
}

#undef CNT
#define CNT TilesDugB
void far FillDirtB(int x, int y)
{
    MapB[x][y] = '.';
    LifeB[(x << 6) + y] = 0;

    if (CNT > 1) {
        TileTotXB -= x;
        if (TileTotXB < 0)
            TileTotXB = 0;
        TileTotYB -= y;
        if (TileTotYB < 0)
            TileTotYB = 0;
        --CNT;
    }

    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x, y + 1);
    SmoothEdgesB(x - 1, y);

    ExitMapB[x][y] = 0;
}

#undef CNT
#define CNT TilesDugR
void far FillDirtR(int x, int y)
{
    MapR[x][y] = '.';
    LifeR[(x << 6) + y] = 0;

    if (CNT > 1) {
        TileTotXR -= x;
        if (TileTotXR < 0)
            TileTotXR = 0;
        TileTotYR -= y;
        if (TileTotYR < 0)
            TileTotYR = 0;
        --CNT;
    }

    SmoothEdgesR(x, y - 1);
    SmoothEdgesR(x + 1, y);
    SmoothEdgesR(x, y + 1);
    SmoothEdgesR(x - 1, y);

    ExitMapR[x][y] = 0;
}

void far SmoothMany(int x, int y)
{
    SmoothACell(x, y);
    SmoothACell(x, y - 1);
    SmoothACell(x + 1, y);
    SmoothACell(x, y + 1);
    SmoothACell(x - 1, y);
    SmoothACell(x, y);
}

int IsValidSLoc(int x,int y) { if(x>=0 && x<=63 && y>=0 && y<=31) return 1; return 0; }

int far GetSM(int x, int y)
{
    int ok;
    int v;

    if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x1f)
        ok = 1;
    else
        ok = 0;
    if (!ok)
        return -1;
    switch (SUBSTATE(5)) {
    case 0:
        v = Dx8[(x << 5) + y + 0x62d2];
        break;
    case 1:
        v = Dx8[(x << 5) + y + 0x6ad2];
        break;
    case 2:
        v = Dx8[(x << 5) + y + 0x72d2];
        break;
    case 3:
        v = Dx8[(x << 5) + y + 0x7ad2];
        break;
    case 4:
        v = Dx8[(x << 5) + y + 0x52d2];
        break;
    }
    return v;
}

void far SetSM(int x, int y, int val)
{
    int ok;

    if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x1f)
        ok = 1;
    else
        ok = 0;
    if (ok) {
        if (val > 0xff)
            val = 0xff;
        switch (SUBSTATE(5)) {
        case 0:
            Dx8[(x << 5) + y + 0x62d2] = val;
            break;
        case 1:
            Dx8[(x << 5) + y + 0x6ad2] = val;
            break;
        case 2:
            Dx8[(x << 5) + y + 0x72d2] = val;
            break;
        case 3:
            Dx8[(x << 5) + y + 0x7ad2] = val;
            break;
        case 4:
            Dx8[(x << 5) + y + 0x52d2] = val;
            break;
        }
    }
}

