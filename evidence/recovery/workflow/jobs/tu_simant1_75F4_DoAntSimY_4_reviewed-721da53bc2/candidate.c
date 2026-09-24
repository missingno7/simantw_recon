/* Candidate translation unit simant1_75F4_DoAntSimY_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoAntSimY, _EnterNest, _CheckMyBestDirs
 * SCAFFOLDED: unclaimed members _DoAntMoveY are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern int near MeHealth;
extern int near MeColor;
extern int far MeMode;
extern unsigned char far Cycle;
extern int far MeHealthCntDwn;
extern unsigned char far Dy8[];
extern unsigned char far Dx8[];
extern int far GetMap(int plane, int x, int y);
extern int far InNestBounds(int x, int y);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far SetMyHealth(int health);
extern int far SRand128(void);
extern void far PlaceEggB(int x, int y, int flag);
extern void far PlaceEggR(int x, int y, int flag);
extern void far DecEatB(void);
extern void far DecEatR(void);
extern void far YellowDeath(int code);
extern int far MeDropAlarm;
extern void far TryAntTheme(void);
extern void far SetAlarmDropState(int state, int quiet);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far DigMyTile(int plane, int x, int y);
extern int far GetMyBestDirs(int plane, int x, int y, int a, int b);

extern int far MeMoveMe;  /* scaffold reference for pool word C3AC (segment 9, MAPSYM_SITE_NAME) */
extern int far MeCmd;  /* scaffold reference for pool word C3AE (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargIndex;  /* scaffold reference for pool word C3B0 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLifePlane;  /* scaffold reference for pool word C3B2 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLife;  /* scaffold reference for pool word C3B4 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLifeX;  /* scaffold reference for pool word C3B6 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeGoalX;  /* scaffold reference for pool word C3B8 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeTargLifeY;  /* scaffold reference for pool word C3BA (segment 9, MAPSYM_SITE_NAME) */
extern int far MeGoalY;  /* scaffold reference for pool word C3BC (segment 9, MAPSYM_SITE_NAME) */
extern int far MeGoalPlane;  /* scaffold reference for pool word C3BE (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C3C0 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dy9;  /* scaffold reference for pool word C3C2 (segment 8, MAPSYM_SITE_NAME) */
extern int far MeLastX;  /* scaffold reference for pool word C3C6 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeLastY;  /* scaffold reference for pool word C3C8 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeSteps;  /* scaffold reference for pool word C3CC (segment 9, MAPSYM_SITE_NAME) */
extern int far MeNestStarted;  /* scaffold reference for pool word C3D0 (segment 8, MAPSYM_SITE_NAME) */
extern int far AlwaysHealthy;  /* scaffold reference for pool word C3D2 (segment 8, MAPSYM_SITE_NAME) */
extern int far OptionStates;  /* scaffold reference for pool word C3D4 (segment 8, MAPSYM_SITE_NAME) */
extern int far WindPromptStrs;  /* scaffold reference for pool word C3D6 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeStartedFight;  /* scaffold reference for pool word C3D8 (segment 9, MAPSYM_SITE_NAME) */
extern int far TERRAINset;  /* scaffold reference for pool word C3DA (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoAntMoveY(void);
void far EnterNest(void);
int far CheckMyBestDirs(int far *steps, int plane, int x, int y, int a, int b);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntMoveY)
#pragma alloc_text(RUN2_TEXT, EnterNest)
#pragma alloc_text(RUN3_TEXT, CheckMyBestDirs)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntMoveY.
 * It only reproduces the object's selector-pool allocation order for the
 * words C3AC C3AE C3B0 C3B2 C3B4 C3B6 C3B8 C3BA C3BC C3BE C3C0 C3C2 C3C4 C3C6 C3C8 C3CA C3CC C3CE C3D0 C3D2 C3D4 C3D6 C3D8 C3DA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntMoveY(void)
{
    volatile int t;

    t = MeMoveMe;
    t = MeCmd;
    t = MeTargIndex;
    t = MeTargLifePlane;
    t = MeTargLife;
    t = MeTargLifeX;
    t = MeGoalX;
    t = MeTargLifeY;
    t = MeGoalY;
    t = MeGoalPlane;
    t = Dx9;
    t = Dy9;
    t = Dy8[0];
    t = MeLastX;
    t = MeLastY;
    t = Dx8[0];
    t = MeSteps;
    t = (int)MeDropAlarm;
    t = MeNestStarted;
    t = AlwaysHealthy;
    t = OptionStates;
    t = WindPromptStrs;
    t = MeStartedFight;
    t = TERRAINset;
}

void far DoAntSimY(void)
{
    int newy, newx;
    int mapval;
    int bx;

    if (MeMode != 0)
        return;

    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);

    if (!(Cycle & 0x3f))
        SetMyHealth(MeHealth - 1);

    if (MePlane >= 2) {
        mapval = GetMap(MePlane, MeLocX, MeLocY);
        if (mapval >= 0x4e)
            SetMyHealth(MeHealth - 1);
    }

    if (MeType == 0x60 && MePlane > 1 && !(Cycle & 0xf)) {
        bx = MeDir ^ 4;
        newy = MeLocY + 2 * (signed char)Dy8[bx];
        newx = MeLocX + 2 * (signed char)Dx8[bx];
        if (InNestBounds(newx, newy)) {
            if (SRand128() <= MeHealth) {
                if (MeColor == 0) {
                    PlaceEggB(newx, newy, 1);
                    DecEatB();
                } else {
                    PlaceEggR(newx, newy, 1);
                    DecEatR();
                }
                SetMyHealth(MeHealth - 5);
            }
        }
    }

    if (MeHealth <= 0) {
        if (++MeHealthCntDwn >= 100) {
            if (MePlane >= 2 && mapval >= 0x4e)
                YellowDeath(7);
            else
                YellowDeath(8);
        }
    }
}

void far EnterNest(void)
{
    TryAntTheme();
    if (MeDropAlarm != 0)
        SetAlarmDropState(0, 1);
    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    MePlane = (MeLocX > 0x40) ? 3 : 2;
    MeLocX = MeLocY;
    MeLocY = (MeType == 0x60) ? 2 : 1;
    MeDir = 4;
    DigMyTile(MePlane, MeLocX, MeLocY);
    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
}

#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
#define Dy8 ((signed char far *)Dy8)  /* shape view of the unit declaration for this member only */
int far CheckMyBestDirs(int far *steps, int plane, int x, int y, int a, int b)
{
    int nx;
    int ny;
    int count;
    int dir;

    count = 0;
    dir = GetMyBestDirs(plane, x, y, a, b);
    if (dir >= 0) {
        nx = Dx8[dir] + x;
        ny = Dy8[dir] + y;
        while (dir >= 0 && count < 0x40) {
            dir = GetMyBestDirs(plane, nx, ny, a, b);
            if (dir >= 0) {
                nx += Dx8[dir];
                ny += Dy8[dir];
            }
            count++;
        }
    }
    *steps = count;
    if (dir >= 0)
        dir = -1;
    return dir;
}
#undef Dx8
#undef Dy8



/* DIAGNOSTIC ONLY: unclaimed selector stand-ins after the exact prior unit.
 * Their references use representative publics verified in MAPSYM segment 8.
 * These helper bodies are POOLSTUB_TEXT only and are never claimed as source. */
extern int far TurnTab;       /* representative MAPSYM public, segment 8 */
extern int far relSearchDirs; /* representative MAPSYM public, segment 8 */
extern int far absSearchDirs; /* representative MAPSYM public, segment 8 */
extern int far IsCarryCaste;  /* representative MAPSYM public, segment 8 */
extern int far UnCarryCaste;  /* representative MAPSYM public, segment 8 */
extern int far YMapPopB;      /* representative MAPSYM public, segment 8 */
extern int far YMapPopR;      /* representative MAPSYM public, segment 8 */
extern int far MeCrazyCnt;    /* exact target selector owner evidenced at C3F6 */
void far pool_stub_ExitNest(void);
void far pool_stub_ZeroGap(void);
void far pool_stub_GetMyDis(void);
void far pool_stub_GetMyNextRandDirs(void);
void far GetMyInitialRandDir(int unused1, int unused2, int unused3,
                            int unused4, int count, int a, int b,
                            int c, int d);
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ExitNest)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ZeroGap)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetMyDis)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetMyNextRandDirs)
#pragma alloc_text(RUN4_TEXT, GetMyInitialRandDir)

/* SCAFFOLD ONLY: stand-in for three unclaimed segment-8 selectors at C3E2-E6. */
void far pool_stub_ExitNest(void)
{
    volatile int t;
    t = TurnTab;
    t = relSearchDirs;
    t = absSearchDirs;
}

/* SCAFFOLD ONLY: measured three-scalar, six-byte unrelocated CONST gap C3E8-ED.
 * This filler has no asserted historical owner and is not a recovered object. */
static const __segment near scaffoldZero0 = 0;
static const __segment near scaffoldZero1 = 0;
static const __segment near scaffoldZero2 = 0;
void far pool_stub_ZeroGap(void)
{
    volatile int t;
    t = scaffoldZero0;
    t = scaffoldZero1;
    t = scaffoldZero2;
}

/* SCAFFOLD ONLY: stand-in for four unclaimed segment-8 selectors at C3EE-F4. */
void far pool_stub_GetMyDis(void)
{
    volatile int t;
    t = IsCarryCaste;
    t = UnCarryCaste;
    t = YMapPopB;
    t = YMapPopR;
}

/* SCAFFOLD ONLY: stand-in for the unclaimed segment-9 selector at C3F6. */
void far pool_stub_GetMyNextRandDirs(void)
{
    volatile int t;
    t = MeCrazyCnt;
}

/*
 * Hypothesis: the final five inputs describe the initial position/direction
 * request.  GetDir supplies MeCrazyDir-1, the three persistent direction
 * outputs are initialized, and GetMyRandDirs receives the five inputs plus
 * the observed output references.  The explicit near casts model the
 * target's one-word offsets for match_position and MeCrazyRot; MeCrazyDir
 * remains a far pointer because the target pushes its selector.
 */
extern int far GetDir(int a, int b, int c, int d);
extern void far GetMyRandDirs(int far *rotation,
                               int near *direction,
                               int selector,
                               int a, int b, int c, int d, int e);
extern int far match_position[];
extern int far MeCrazyDir;
extern int far MeCrazyCnt;
extern int far MeCrazyRot;

void far GetMyInitialRandDir(int unused1, int unused2, int unused3,
                             int unused4, int count, int a, int b,
                             int c, int d)
{
    int near *positions;

    MeCrazyDir = GetDir(a, b, c, d) - 1;
    MeCrazyCnt = 0x10;
    MeCrazyRot = 0;
    positions = (int near *)match_position;
    GetMyRandDirs(&MeCrazyRot, (int near *)&MeCrazyDir, __segname("PACK"),
                  count, a, b, c, d);
}
