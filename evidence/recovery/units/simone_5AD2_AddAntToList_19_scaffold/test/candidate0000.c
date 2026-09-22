/* Candidate translation unit simone_5AD2_AddAntToList_19_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddAntToList, _IsThisEgg, _IsThisGrass, _IsThisFood, _IsItNFood, _GetLife, _GetMap, _SetMap, _MoveMyLife, _DoMapUpdateDraw, _DoEditAndMapUpdateDraw, _EndTargetMode, _EndLifeTransferMode, _ExchangeLives, _PickupMyEgg, _PickupMyObject, _IsNotBarrier, _IsLessThanHole, _IsLiftable
 * SCAFFOLDED: unclaimed members _IsClear3x3, _TargetAnt, _DoLifeExchange, _DropMyFood, _DropPebble, _PickupMyRock, _SetMyHealth, _EatMyFood, _PickupMyFood are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern void far AddAntToAList(int x, int y, int type, int a, int b);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern void far SetLife(int plane, int x, int y, int type);
extern int far IsItFood(int tile);
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
#define CASEBODY(v) result = v; break;
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern void far ZapEuMapAt(int plane, int x, int y);
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern char far Dy8[];
extern char far Dx8[];
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
#define TRUE 1
#define FALSE 0
extern void far DoEditUpdateDraw(void);
extern int far CurGameTool;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);
extern int far LessonTemp;
extern int far DoLifeExchange(int a, int b, int c);
extern void far myBeginSound(int sound, int a, int b);
extern int far mySoundIsDone(void);
extern void far myDelay(unsigned long ticks);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern int near MeHealth;
extern int far MeEggCarried;
extern int far MeFoodInType;
extern int far FindEggAt(int far *index, int plane, int x, int y);
extern void far SetAntIndex(int plane, int index, int a, int b, int c, int d, int e);
extern int far PickupMyRock(int plane, int x, int y);
extern int far PickupMyFood(int plane, int x, int y);
extern int far TERRAINset;

extern int far GamePaused;  /* scaffold reference for pool word C486 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeMode;  /* scaffold reference for pool word C48A (segment 9, MAPSYM_SITE_NAME) */
extern int far UnCarryCaste;  /* scaffold reference for pool word C48E (segment 8, MAPSYM_SITE_NAME) */
extern int far Starg;  /* scaffold reference for pool word C490 (segment 9, MAPSYM_SITE_NAME) */
extern int far SuserX;  /* scaffold reference for pool word C492 (segment 9, MAPSYM_SITE_NAME) */
extern int far SuserY;  /* scaffold reference for pool word C494 (segment 9, MAPSYM_SITE_NAME) */
extern int far SMode;  /* scaffold reference for pool word C496 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeSMode;  /* scaffold reference for pool word C498 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeHealthCntDwn;  /* scaffold reference for pool word C49C (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWarnHealth;  /* scaffold reference for pool word C49E (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWantFood;  /* scaffold reference for pool word C4A0 (segment 9, MAPSYM_SITE_NAME) */
extern int far absSearchDirs;  /* scaffold reference for pool word C4A2 (segment 8, MAPSYM_SITE_NAME) */
extern int far FoodB;  /* scaffold reference for pool word C4A4 (segment 9, MAPSYM_SITE_NAME) */
extern int far FoodR;  /* scaffold reference for pool word C4A6 (segment 9, MAPSYM_SITE_NAME) */
extern int far HoleMapB;  /* scaffold reference for pool word C4A8 (segment 8, MAPSYM_SITE_NAME) */
extern int far HoleMapR;  /* scaffold reference for pool word C4AA (segment 8, MAPSYM_SITE_NAME) */
extern int far NeverHungry;  /* scaffold reference for pool word C49A (segment 8, MAPSYM_SITE_NAME) */
extern int far EditMsgDelay;  /* scaffold reference for pool word C4AE (segment 9, MAPSYM_SITE_NAME) */
extern int far WindPromptStrs;  /* scaffold reference for pool word C4B0 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastNewHoleB;  /* scaffold reference for pool word C4B4 (segment 8, MAPSYM_SITE_NAME) */
extern int far MeDis;  /* scaffold reference for pool word C4B6 (segment 9, MAPSYM_SITE_NAME) */
extern int far MePrevDis;  /* scaffold reference for pool word C4B8 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_IsClear3x3(void);
void far pool_stub_TargetAnt(void);
void far pool_stub_DoLifeExchange(void);
void far pool_stub_DropMyFood(void);
void far pool_stub_DropPebble(void);
void far pool_stub_PickupMyRock(void);
void far pool_stub_SetMyHealth(void);
void far pool_stub_EatMyFood(void);
void far pool_stub_PickupMyFood(void);
int IsThisEgg(unsigned char value);
int IsThisGrass(int category, int tile);
int IsThisFood(int category, int tile);
int IsItNFood(int value);
int far GetLife(int plane, int x, int y);
int far GetMap(int plane, int x, int y);
void far SetMap(int plane, int x, int y, int value);
void far MoveMyLife(int plane, int x, int y, int type, int dir);
void DoMapUpdateDraw(void);
void DoEditAndMapUpdateDraw(void);
void EndTargetMode(void);
void EndLifeTransferMode(void);
void far ExchangeLives(int a, int b, int c);
int far PickupMyEgg(int plane, int x, int y);
int far PickupMyObject(int plane, int x, int y);
int IsNotBarrier(int x);
int IsLessThanHole(int x);
int far IsLiftable(int plane, int x, int y);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_IsClear3x3)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_TargetAnt)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoLifeExchange)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DropMyFood)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DropPebble)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_PickupMyRock)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMyHealth)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_EatMyFood)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_PickupMyFood)
#pragma alloc_text(RUN2_TEXT, IsThisEgg, IsThisGrass, IsThisFood)
#pragma alloc_text(RUN3_TEXT, IsItNFood)
#pragma alloc_text(RUN4_TEXT, GetLife, GetMap, SetMap)
#pragma alloc_text(RUN5_TEXT, MoveMyLife, DoMapUpdateDraw, DoEditAndMapUpdateDraw)
#pragma alloc_text(RUN6_TEXT, EndTargetMode)
#pragma alloc_text(RUN7_TEXT, EndLifeTransferMode, ExchangeLives)
#pragma alloc_text(RUN8_TEXT, PickupMyEgg)
#pragma alloc_text(RUN9_TEXT, PickupMyObject)
#pragma alloc_text(RUN10_TEXT, IsNotBarrier)
#pragma alloc_text(RUN11_TEXT, IsLessThanHole)
#pragma alloc_text(RUN12_TEXT, IsLiftable)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _IsClear3x3.
 * It only reproduces the object's selector-pool allocation order for the
 * words C478 C47A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_IsClear3x3(void)
{
    volatile int t;

    t = Dy8[0];
    t = Dx8[0];
}

int far AddAntToList(int plane, int x, int y, int type, int a, int b)
{
    int added;

    added = 0;
    if (plane <= 1) {
        if (ListIndexA < 1000) {
            AddAntToAList(x, y, type, a, b);
            added = 1;
        }
    } else if (plane == 2) {
        if (ListIndexB < 500) {
            AddAntToBList(x, y, type, a, b);
            added = 1;
        }
    } else if (ListIndexR < 500) {
        AddAntToRList(x, y, type, a, b);
        added = 1;
    }
    if (added == 1)
        SetLife(plane, x, y, type);
    return added;
}

int IsThisEgg(unsigned char value)
{
    int normalized;
    normalized = value;
    normalized &= 0x7f;
    if (normalized >= 1 && normalized <= 7) return 1;
    return 0;
}

int IsThisGrass(int category, int tile)
{
    if (category < 2)
        return 0;
    if (tile < 0x1c || tile > 0x1f)
        return 0;
    return 1;
}

int IsThisFood(int category, int tile)
{
    int result;

    if (category <= 1)
        return IsItFood(tile);
    if (tile < 0x10 || tile > 0x13)
        result = 0;
    else
        result = 1;
    return result;
}

int IsItNFood(int value)
{
    if (value < 0x10 || value > 0x13) return 0;
    return 1;
}

int far GetLife(int plane, int x, int y)
{
    int result;
    int ok;

    result = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 127 && y >= 0 && y <= 63);
    else
        ok = (x >= 0 && x <= 63 && y >= 0 && y <= 63);
    if (ok == 1) {
        switch (plane) {
        case 0:
        case 1:
            CASEBODY(LifeA[x][y])
        case 2:
            CASEBODY(LifeB[x][y])
        case 3:
            CASEBODY(LifeR[x][y])
        
        }
        if (result == 0)
            result = -1;
    }
    return result;
}

int far GetMap(int plane, int x, int y)
{
    int result;
    int ok;

    result = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 127 && y >= 0 && y <= 63);
    else
        ok = (x >= 0 && x <= 63 && y >= 0 && y <= 63);
    if (ok == 1) {
        switch (plane) {
        case 0:
        case 1:
            CASEBODY(MapA[x][y])
        case 2:
            CASEBODY(MapB[x][y])
        case 3:
            CASEBODY(MapR[x][y])
        }
    }
    return result;
}

void far SetMap(int plane, int x, int y, int value)
{
    int ok;

    if (plane <= 1)
        ok = (x >= 0 && x <= 127 && y >= 0 && y <= 63);
    else
        ok = (x >= 0 && x <= 63 && y >= 0 && y <= 63);
    if (ok == 1) {
        switch (plane) {
        case 0:
        case 1:
            MapA[x][y] = value;
            break;
        case 2:
            MapB[x][y] = value;
            break;
        case 3:
            MapR[x][y] = value;
            break;
        }
        ZapEuMapAt(plane, x, y);
    }
}

void far MoveMyLife(int plane, int x, int y, int type, int dir)
{
    int p;
    int ok;

    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    if (plane == 0)
        p = 1;
    else
        p = plane;
    if (p <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        SetLife(p, x, y, 0xff);
        if (type == 0x60)
            SetLife(p, x + Dx8[dir ^ 4], y + Dy8[dir ^ 4], 0xfe);
        MeLocX = x;
        MeLocY = y;
        MeDir = dir;
        MeType = type;
        MePlane = p;
    }
}

void DoMapUpdateDraw(void) {}

void DoEditAndMapUpdateDraw(void)
{
    DoEditUpdateDraw();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _TargetAnt.
 * It only reproduces the object's selector-pool allocation order for the
 * words C482 C484 C486; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_TargetAnt(void)
{
    volatile int t;

    t = (int)CurGameTool;
    t = (int)SaveGamePaused;
    t = GamePaused;
}

void EndTargetMode(void)
{
    CurGameTool = -1;
    PauseGame(SaveGamePaused);
}

void EndLifeTransferMode(void)
{
    CurGameTool = -1;
    PauseGame(SaveGamePaused);
}

void far ExchangeLives(int a, int b, int c)
{
    LessonTemp = 1;
    if (DoLifeExchange(a, b, c) == 1) {
        CurGameTool = -1;
        PauseGame(SaveGamePaused);
        if (MeType == 0x60) {
            myBeginSound(0xf, 0, 0x7e);
            DoEditUpdateDraw();
            while (!mySoundIsDone())
                myDelay(5L);
            myBeginSong(0x2afe, 0x7e);
        } else
            myBeginSound(0xf, 0, 0x7e);
    } else
        myBeginSound(1, 0, 0x7e);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoLifeExchange.
 * It only reproduces the object's selector-pool allocation order for the
 * words C48A C48C C48E C490 C492 C494 C496 C498 C49C C49E C4A0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoLifeExchange(void)
{
    volatile int t;

    t = MeMode;
    t = (int)MeEggCarried;
    t = UnCarryCaste;
    t = Starg;
    t = SuserX;
    t = SuserY;
    t = SMode;
    t = MeSMode;
    t = MeHealthCntDwn;
    t = MeWarnHealth;
    t = MeWantFood;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DropMyFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4A2 C4A4 C4A6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DropMyFood(void)
{
    volatile int t;

    t = absSearchDirs;
    t = FoodB;
    t = FoodR;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DropPebble.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4A8 C4AA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DropPebble(void)
{
    volatile int t;

    t = HoleMapB;
    t = HoleMapR;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _PickupMyRock.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4AC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_PickupMyRock(void)
{
    volatile int t;

    t = (int)TERRAINset;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMyHealth.
 * It only reproduces the object's selector-pool allocation order for the
 * words C49A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMyHealth(void)
{
    volatile int t;

    t = NeverHungry;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _EatMyFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4AE C4B0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_EatMyFood(void)
{
    volatile int t;

    t = EditMsgDelay;
    t = WindPromptStrs;
}

int far PickupMyEgg(int plane, int x, int y)
{
    int index;
    int egg;

    if (MeType == 0x10 || MeHealth < 10) {
        MeEggCarried = 0xfd;
        egg = FindEggAt(&index, plane, x, y);
        if (egg >= 0) {
            SetAntIndex(plane, index, 0, 0, 0, 0, 0);
            if (x != MeLocX || y != MeLocY)
                SetLife(plane, x, y, 0);
            if (MeHealth >= 10) {
                myBeginSound(0x1c, 0, 0x7e);
                MeEggCarried = egg;
                MeType = 8;
            } else
                MeFoodInType = 3;
            return 1;
        }
    }
    return 0;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _PickupMyFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4B4 C4B6 C4B8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_PickupMyFood(void)
{
    volatile int t;

    t = LastNewHoleB;
    t = MeDis;
    t = MePrevDis;
}

int far PickupMyObject(int plane, int x, int y)
{
    int eggIndex;
    int result;

    if (MeType & 8)
        return FALSE;
    if (MeType == 0x10 || MeHealth < 10) {
        MeEggCarried = 0xfd;
        result = FindEggAt(&eggIndex, plane, x, y);
        if (result >= 0) {
            SetAntIndex(plane, eggIndex, 0, 0, 0, 0, 0);
            if (x != MeLocX || y != MeLocY)
                SetLife(plane, x, y, 0);
            if (MeHealth >= 10) {
                myBeginSound(0x1c, 0, 0x7e);
                MeEggCarried = result;
                MeType = 8;
            } else {
                MeFoodInType = 3;
            }
            result = TRUE;
        } else {
            result = FALSE;
        }
    } else {
        result = FALSE;
    }
    if (result == FALSE) {
        result = PickupMyRock(plane, x, y);
        if (result == FALSE)
            result = PickupMyFood(plane, x, y);
    }
    return result;
}

int IsNotBarrier(int x)
{
    if (!TERRAINset)
        return x <= 0x50;
    return x <= 0x5f;
}

int IsLessThanHole(int x)
{
    if (!TERRAINset)
        return x < 0x50;
    return x < 0x59;
}

int far IsLiftable(int plane, int x, int y)
{
    int eggIndex;
    int eggResult;
    int map;
    int ok;
    int tile;

    eggResult = FindEggAt(&eggIndex, plane, x, y);
    map = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        switch (plane) {
        case 0:
        case 1:
            map = MapA[x][y];
            break;
        case 2:
            map = MapB[x][y];
            break;
        case 3:
            map = MapR[x][y];
            break;
        }
    }
    tile = map;

    if (plane <= 1)
        ok = IsItFood(tile);
    else
        ok = (tile >= 0x10 && tile <= 0x13);
    if (ok == FALSE) {
        if (plane <= 1)
            ok = (plane == 1 && tile >= 0x51 && tile <= 0x53);
        else
            ok = (tile >= 0x30 && tile <= 0x31);
        if (ok == FALSE) {
            ok = eggResult & 0x7f;
            ok = (ok >= 1 && ok <= 7);
            if (ok == FALSE)
                return FALSE;
        }
    }
    return TRUE;
}

