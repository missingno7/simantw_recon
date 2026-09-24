/* Candidate translation unit simone_5AD2_IsClear3x3_26_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _IsClear3x3, _AddAntToList, _IsThisEgg, _IsThisGrass, _IsThisFood, _IsItNFood, _GetLife, _GetMap, _SetMap, _SetQueenTail, _MoveMyLife, _DoMapUpdateDraw, _DoEditAndMapUpdateDraw, _TargetAnt, _EndTargetMode, _StartLifeTransfer, _EndLifeTransferMode, _ExchangeLives, _SetMyHealth, _PickupMyEgg, _DropMyObject, _PickupMyObject, _IsNotBarrier, _IsLessThanHole, _IsLiftable
 * SCAFFOLDED: unclaimed members _DoLifeExchange, _DropMyFood, _DropPebble, _PickupMyRock, _EatMyFood are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far IsClearTile(int plane, int x, int y);
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
extern char far Dy8[];
extern char far Dx8[];
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
#define TRUE 1
#define FALSE 0
extern void far DoEditUpdateDraw(void);
extern int far match_position[];
extern int far GamePaused;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);
#define CurGameTool ((int far *)((unsigned char far *)match_position + 0x7C22))  /* pool word C482: one object, MAPSYM _match_position+31778 */
extern int far LessonTemp;
extern int far DoLifeExchange(int a, int b, int c);
extern void far myBeginSound(int sound, int a, int b);
extern int far mySoundIsDone(void);
extern void far myDelay(unsigned long ticks);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern int far NeverHungry;
extern int far MeHealthCntDwn;
extern int far MeWarnHealth;
extern int far MeWantFood;
extern int near MeHealth;
extern int far MeEggCarried;
extern int far MeFoodInType;
extern int far FindEggAt(int far *index, int plane, int x, int y);
extern void far SetAntIndex(int plane, int index, int a, int b, int c, int d, int e);
extern int far DropMyEgg(int, int, int, int, int);
extern int far DropMyFood(int, int, int, int, int);
extern int far DropMyRock(int, int, int, int, int);
extern int far PickupMyRock(int plane, int x, int y);
extern int far PickupMyFood(int plane, int x, int y);
extern int far TERRAINset;

extern int far match_length;  /* scaffold reference for pool word C48A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C48E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C490 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C492 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C494 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C496 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C498 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C4A2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C4A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C4A6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TurnTab;  /* scaffold reference for pool word C4A8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word C4AA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C4AE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word C4B0 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoLifeExchange(void);
void far pool_stub_DropMyFood(void);
void far pool_stub_DropPebble(void);
void far pool_stub_PickupMyRock(void);
void far pool_stub_EatMyFood(void);
int far AddAntToList(int plane, int x, int y, int type, int a, int b);
int IsThisEgg(unsigned char value);
int IsThisGrass(int category, int tile);
int IsThisFood(int category, int tile);
int IsItNFood(int value);
int far GetLife(int plane, int x, int y);
int far GetMap(int plane, int x, int y);
void far SetMap(int plane, int x, int y, int value);
void SetQueenTail(int kind, int x, int y, int tableIndex, int tableType);
void far MoveMyLife(int plane, int x, int y, int type, int dir);
void DoMapUpdateDraw(void);
void DoEditAndMapUpdateDraw(void);
void TargetAnt(void);
void EndTargetMode(void);
void StartLifeTransfer(void);
void EndLifeTransferMode(void);
void far ExchangeLives(int a, int b, int c);
void far SetMyHealth(int health);
int far PickupMyEgg(int plane, int x, int y);
int far DropMyObject(int first, int second, int third, int fourth, int fifth);
int far PickupMyObject(int plane, int x, int y);
int IsNotBarrier(int x);
int IsLessThanHole(int x);
int far IsLiftable(int plane, int x, int y);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoLifeExchange)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DropMyFood)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DropPebble)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_PickupMyRock)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_EatMyFood)
#pragma alloc_text(RUN2_TEXT, AddAntToList)
#pragma alloc_text(RUN3_TEXT, IsThisEgg, IsThisGrass, IsThisFood)
#pragma alloc_text(RUN4_TEXT, IsItNFood)
#pragma alloc_text(RUN5_TEXT, GetLife, GetMap, SetMap)
#pragma alloc_text(RUN6_TEXT, SetQueenTail)
#pragma alloc_text(RUN7_TEXT, MoveMyLife, DoMapUpdateDraw, DoEditAndMapUpdateDraw, TargetAnt)
#pragma alloc_text(RUN7_TEXT, EndTargetMode, StartLifeTransfer, EndLifeTransferMode, ExchangeLives)
#pragma alloc_text(RUN8_TEXT, SetMyHealth)
#pragma alloc_text(RUN9_TEXT, PickupMyEgg)
#pragma alloc_text(RUN10_TEXT, DropMyObject, PickupMyObject)
#pragma alloc_text(RUN11_TEXT, IsNotBarrier)
#pragma alloc_text(RUN12_TEXT, IsLessThanHole)
#pragma alloc_text(RUN13_TEXT, IsLiftable)

#define Dy8 ((signed char far *)Dy8)  /* shape view of the unit declaration for this member only */
#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
int far IsClear3x3(int type, int y, int x)
{
    int index;

    if (IsClearTile(type, y, x) == 1) {
        for (index = 0; index < 8; ++index) {
            if (!IsClearTile(type, y + Dx8[index], x + Dy8[index]))
                return 0;
        }
        return 1;
    }
    return 0;
}
#undef Dy8
#undef Dx8

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

void SetQueenTail(int kind, int x, int y, int tableIndex, int tableType)
{
    int lifeType;

    if (tableType == 0xff)
        lifeType = 0xfe;
    else
        lifeType = tableType;

    SetLife(kind, x + Dx8[tableIndex ^ 4], y + Dy8[tableIndex ^ 4], lifeType);
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

void TargetAnt(void)
{
    if (match_position[0x3e11] == 11) {
        match_position[0x3e11] = -1;
        PauseGame(SaveGamePaused);
    } else {
        SaveGamePaused = GamePaused;
        match_position[0x3e11] = 11;
        PauseGame(1);
    }
}

void EndTargetMode(void)
{
    CurGameTool = -1;
    PauseGame(SaveGamePaused);
}

void StartLifeTransfer(void)
{
    if (match_position[0x3e11] == 10) {
        match_position[0x3e11] = -1;
        PauseGame(SaveGamePaused);
    } else {
        SaveGamePaused = GamePaused;
        match_position[0x3e11] = 10;
        PauseGame(1);
    }
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
 * words C48A C48C C48E C490 C492 C494 C496 C498 C49A C49C C49E C4A0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoLifeExchange(void)
{
    volatile int t;

    t = match_length;
    t = (int)MeEggCarried;
    t = Dx9;
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
    t = MiscStrs;
    t = LastQueenPlane;
    t = (int)NeverHungry;
    t = (int)MeHealthCntDwn;
    t = (int)MeWarnHealth;
    t = (int)MeWantFood;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DropMyFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4A2 C4A4 C4A6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DropMyFood(void)
{
    volatile int t;

    t = Dy9;
    t = EditDragPnt;
    t = SMode;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DropPebble.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4A8 C4AA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DropPebble(void)
{
    volatile int t;

    t = TurnTab;
    t = relSearchDirs;
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

void far SetMyHealth(int health)
{
    int value;

    if (!NeverHungry)
        value = health;
    else
        value = 100;

    if (value > 0)
        MeHealthCntDwn = 0;

    if (value > 100)
        value = 100;
    else if (value < 0)
        value = 0;

    if (MeWarnHealth < value && value >= 10) {
        MeHealth = value;
        MeWantFood = 0;
    } else {
        MeHealth = value;
        MeWantFood = 1;
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _EatMyFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4AE C4B0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_EatMyFood(void)
{
    volatile int t;

    t = modeButtonState;
    t = CurRestPlane;
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

int far DropMyObject(int first, int second, int third, int fourth, int fifth)
{
    switch (MeType) {
    case 8:
        return DropMyEgg(first, second, third, fourth, fifth);
    case 0x18:
    case 0x38:
        return DropMyFood(first, second, third, fourth, fifth);
    case 0x28:
    case 0x48:
        return DropMyRock(first, second, third, fourth, fifth);
    }
    return 0;
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

