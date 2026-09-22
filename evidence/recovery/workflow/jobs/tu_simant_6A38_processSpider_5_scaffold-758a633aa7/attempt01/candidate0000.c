/* Candidate translation unit simant_6A38_processSpider_5_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _processSpider, _ResetYellowVars, _DoTroph, _SetAlarmDropState, _YellowHelp
 * SCAFFOLDED: unclaimed members _processEdit, _DoLaserFire, _YellowBirth, _YellowDeath, _SpecialXfer, _LionDialog, _YellowDialog are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far CurGameTool;
extern int far Starg;
extern int far StargLife;
extern int far SMode;
extern int far SuserX;
extern int far SuserY;
extern int far MeCmd;
extern int far MeSMode;
extern unsigned char near LifeA[128][64];
extern int far FindAntIndex(int list, int life, int column, int attribute);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far EndTargetMode(void);
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int far MeGoalPlane;
extern int far MeLastX;
extern int far MeLastY;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeMoveMe;
extern int far MePrevDis;
extern int far MeDis;
extern int far MeSteps;
extern int far MeCrazyCnt;
extern char far Dx8[];
extern char far Dy8[];
extern int near MeType;
extern int far GetDir(int a, int b, int c, int d);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far DoEditUpdateDraw(void);
extern void far EatMyFood(int amount);
extern int near ELayerMode;
extern int far MeMode;
extern int far MeDropAlarm;
extern int far EditRows;
extern int far EditColumns;
extern void far win_SetObjSelectedState(int object, int selected);
extern void far InvalEuMap(int left, int top, int right, int bottom);
extern int near rootWnd;
extern char far helpFile[];
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);

extern int far editTileRect;  /* scaffold reference for pool word BF06 (segment 9, MAPSYM_SITE_NAME) */
extern int far MapPnt;  /* scaffold reference for pool word BF08 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word BF0A (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargIndex;  /* scaffold reference for pool word BF0E (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLife;  /* scaffold reference for pool word BF12 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLifePlane;  /* scaffold reference for pool word BF14 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLifeX;  /* scaffold reference for pool word BF16 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLifeY;  /* scaffold reference for pool word BF18 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapXsize;  /* scaffold reference for pool word BF24 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapTileRect;  /* scaffold reference for pool word BF26 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapYsize;  /* scaffold reference for pool word BF28 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word BF42 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far MeNestStarted;  /* scaffold reference for pool word BF44 (segment 8, MAPSYM_SITE_NAME) */
extern int far UnCarryCaste;  /* scaffold reference for pool word BF46 (segment 8, MAPSYM_SITE_NAME) */
extern int far MeStartedFight;  /* scaffold reference for pool word BF48 (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsEaten;  /* scaffold reference for pool word BF4A (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsKilled;  /* scaffold reference for pool word BF4C (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsExpired;  /* scaffold reference for pool word BF4E (segment 9, MAPSYM_SITE_NAME) */
extern int far ListIndexB;  /* scaffold reference for pool word BF56 (segment 9, MAPSYM_SITE_NAME) */
extern int far IsGameOver;  /* scaffold reference for pool word BF58 (segment 9, MAPSYM_SITE_NAME) */
extern int far BlackWon;  /* scaffold reference for pool word BF5A (segment 9, MAPSYM_SITE_NAME) */
extern int far RebornY;  /* scaffold reference for pool word BF5C (segment 9, MAPSYM_SITE_NAME) */
extern int far RebornX;  /* scaffold reference for pool word BF5E (segment 9, MAPSYM_SITE_NAME) */
extern int far CurYardPnt;  /* scaffold reference for pool word BF60 (segment 9, MAPSYM_SITE_NAME) */
extern int far YMapPopB;  /* scaffold reference for pool word BF62 (segment 8, MAPSYM_SITE_NAME) */
extern int far ColonyUpdateFlag;  /* scaffold reference for pool word BF64 (segment 8, MAPSYM_SITE_NAME) */
extern int far WindPromptStrs;  /* scaffold reference for pool word BF66 (segment 9, MAPSYM_SITE_NAME) */
extern int far patchRgn;  /* scaffold reference for pool word BF68 (segment 10, MAPSYM_SITE_NAME) */
extern int far YMapPnt;  /* scaffold reference for pool word BF6A (segment 9, MAPSYM_SITE_NAME) */
extern int far LionTrapPnts;  /* scaffold reference for pool word BF6C (segment 8, MAPSYM_SITE_NAME) */
extern int far YellowEatPnt;  /* scaffold reference for pool word BF6E (segment 8, MAPSYM_SITE_NAME) */

void far pool_stub_processEdit(void);
void far pool_stub_DoLaserFire(void);
void far pool_stub_YellowBirth(void);
void far pool_stub_YellowDeath(void);
void far pool_stub_SpecialXfer(void);
void far pool_stub_LionDialog(void);
void far pool_stub_YellowDialog(void);
void far DoTroph(int x, int y, int index);
void far SetAlarmDropState(int state, int quiet);
void YellowHelp(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_processEdit)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoLaserFire)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YellowBirth)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YellowDeath)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SpecialXfer)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_LionDialog)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YellowDialog)
#pragma alloc_text(RUN2_TEXT, DoTroph, SetAlarmDropState)
#pragma alloc_text(RUN3_TEXT, YellowHelp)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _processEdit.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF06 BF08 BF0A BF0C BF0E BF10 BF12 BF14 BF16 BF18 BF1A BF1C BF1E BF20 BF22; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_processEdit(void)
{
    volatile int t;

    t = editTileRect;
    t = MapPnt;
    t = CurGameType;
    t = (int)MeMode;
    t = MeTargIndex;
    t = (int)MeCmd;
    t = MeTargLife;
    t = MeTargLifePlane;
    t = MeTargLifeX;
    t = MeTargLifeY;
    t = (int)MeGoalPlane;
    t = (int)MeGoalX;
    t = (int)MeGoalY;
    t = (int)MeCrazyCnt;
    t = (int)MeMoveMe;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoLaserFire.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF24 BF26 BF28; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoLaserFire(void)
{
    volatile int t;

    t = mapXsize;
    t = mapTileRect;
    t = mapYsize;
}

void far processSpider(int row, int col, int mode)
{
    int life;
    int idx;

    if (mode < 1 && CurGameTool != 0xb) {
        Starg = -2;
        StargLife = -1;
        SMode = 0;
        SuserX = row;
        SuserY = col;
        MeCmd = mode;
        return;
    }

    life = LifeA[row][col];
    if (life != 0) {
        idx = FindAntIndex(1, row, col, life);
        if (idx >= 0) {
            StargLife = life;
            Starg = idx;
            SMode = 2;
            if (CurGameTool == 0xb) {
                myBeginSound(0xf, 0, 0x7e);
                MeSMode = 6;
                EndTargetMode();
            }
            return;
        }
    }

    if (CurGameTool == 0xb) {
        myBeginSound(1, 0, 0x7e);
        return;
    }

    Starg = -2;
    StargLife = -1;
    SMode = 0;
    SuserX = row;
    SuserY = col;
    MeCmd = mode;
}

void ResetYellowVars(int plane, int x, int y)
{
    MePlane = plane;
    MeGoalPlane = plane;
    MeLocX = x;
    MeLastX = x;
    MeGoalX = x;
    MeLocY = y;
    MeLastY = y;
    MeGoalY = y;
    MeCmd = 0;
    MeMoveMe = 0;
    MeDis = 0;
    MePrevDis = 0;
    MeSteps = 0;
    MeCrazyCnt = -2;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YellowBirth.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF42 BF44; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YellowBirth(void)
{
    volatile int t;

    t = Dx9;
    t = MeNestStarted;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YellowDeath.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF46 BF48 BF4A BF4C BF4E BF50 BF52 BF54 BF56 BF58 BF5A BF5C BF5E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YellowDeath(void)
{
    volatile int t;

    t = UnCarryCaste;
    t = MeStartedFight;
    t = BAntsEaten;
    t = BAntsKilled;
    t = BAntsExpired;
    t = (int)MeDropAlarm;
    t = (int)EditRows;
    t = (int)EditColumns;
    t = ListIndexB;
    t = IsGameOver;
    t = BlackWon;
    t = RebornY;
    t = RebornX;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SpecialXfer.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF60 BF62 BF64 BF66 BF68 BF6A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SpecialXfer(void)
{
    volatile int t;

    t = CurYardPnt;
    t = YMapPopB;
    t = ColonyUpdateFlag;
    t = WindPromptStrs;
    t = patchRgn;
    t = YMapPnt;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _LionDialog.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF6C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_LionDialog(void)
{
    volatile int t;

    t = LionTrapPnts;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YellowDialog.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF6E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YellowDialog(void)
{
    volatile int t;

    t = YellowEatPnt;
}

void far DoTroph(int x, int y, int index)
{
    int newX;
    int newY;

    newX = Dx8[index] + x;
    newY = Dy8[index] + y;
    MoveMyLife(MePlane, newX, newY, MeType,
               GetDir(newX, newY, x, y) - 1);
    DoEditUpdateDraw();
    EatMyFood(1);
}

void far SetAlarmDropState(int state, int quiet)
{
    if (state != 0) {
        if (MePlane == 1 && MeMode == 0) {
            ELayerMode = 0;
            win_SetObjSelectedState(0x10, state);
            MeDropAlarm = 1;
            if (quiet == 0)
                myBeginSound(0xf, 0, 0x7e);
        } else if (quiet == 0)
            myBeginSound(1, 0, 0x7e);
    } else {
        MeDropAlarm = 0;
        win_SetObjSelectedState(0x10, state);
        ELayerMode = -1;
        if (quiet == 0)
            myBeginSound(0xf, 0, 0x7e);
    }
    InvalEuMap(0, 0, EditColumns, EditRows);
}

void YellowHelp(void)
{
    unsigned long data;

    if (MeMode == 0) {
        if (MeType == 0x40)
            data = 0x00030100L;
        else
            data = 0x00010100L;
    } else {
        data = 0x00020100L;
    }
    WinHelp(rootWnd, helpFile, 1, data);
}

