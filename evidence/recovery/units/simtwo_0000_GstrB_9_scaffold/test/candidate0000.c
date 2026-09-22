/* Candidate translation unit simtwo_0000_GstrB_9_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GstrB, _SetModeProd, _StartAttack, _Recruit, _UnRecruit, _RecruitRed, _GetNewModeB, _GetNewModeR, _GetRandDir
 * SCAFFOLDED: unclaimed members _GetStrategy, _SetCasteProd, _GstrR, _GetNewMode, _GetForageDir, _GetNestDir are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near HealthB;
extern int near BpopT;
extern int near RpopT;
extern int far RedQueens;
extern int far TilesDugB;
#define QUEENS RedQueens
#define DUG TilesDugB
extern int far ModePopB[];
extern int far modeLevels[];
extern int far ModeTabB[];
extern int far ModeMe;
extern unsigned int far JustToBeMean;
extern unsigned int far * far AdviceStrs;
extern int far SRand1(unsigned int range);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far EditMessage(int first,int second,int width,int fourth,int fifth);
extern unsigned char far Dx8[];
#define AT(off) (Dx8[off])
#define AlistT(i) AT((i) + 0x2f62)
#define AlistM(i) AT((i) + 0x2b78)
#define AlistS(i) AT((i) + 0x334c)
#define BlistT(i) AT((i) + 0x3d18)
#define BlistM(i) AT((i) + 0x3b22)
#define BlistS(i) AT((i) + 0x3f0e)
extern int far ListIndexA;
extern int far ListIndexB;
#define RlistT(i) AT((i) + 0x46e6)
#define RlistM(i) AT((i) + 0x44f0)
extern int far ListIndexR;
static int __based(__segname("PACK")) RecruitPoolTotal;
extern int far SRand8(void);
extern int far ModeAuto;
extern int far StrategicModeB;
extern char far ModeTabWB[][8];
extern char far ModeTabSB[][8];
extern char far CasteModeTabB[];
extern int far StrategicModeR[];
extern char far TurnTab[][8];

extern int far ChaseSpid;  /* scaffold reference for pool word C4BE (segment 9, MAPSYM_SITE_NAME) */
extern int far FuzLocX;  /* scaffold reference for pool word C4C0 (segment 9, MAPSYM_SITE_NAME) */
extern int far FuzLocY;  /* scaffold reference for pool word C4C2 (segment 9, MAPSYM_SITE_NAME) */
extern int far CasteTabB;  /* scaffold reference for pool word C4C6 (segment 8, MAPSYM_SITE_NAME) */
extern int far MakeMe;  /* scaffold reference for pool word C4C8 (segment 8, MAPSYM_SITE_NAME) */
extern int far PherMapBT;  /* scaffold reference for pool word C4E4 (segment 8, MAPSYM_SITE_NAME) */
extern int far LastNewHoleR;  /* scaffold reference for pool word C4E8 (segment 8, MAPSYM_SITE_NAME) */
extern int far LastNewHoleB;  /* scaffold reference for pool word C4EA (segment 8, MAPSYM_SITE_NAME) */

void far pool_stub_GetStrategy(void);
void far pool_stub_SetCasteProd(void);
void far pool_stub_GstrR(void);
void far pool_stub_GetNewMode(void);
void far pool_stub_GetForageDir(void);
void far pool_stub_GetNestDir(void);
void far SetModeProd(void);
void StartAttack(void);
void far Recruit(int count);
void far UnRecruit(int all);
void far RecruitRed(int count);
int far GetNewModeB(int caste);
int far GetNewModeR(int mode);
int far GetRandDir(int x, int y, int dir);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetStrategy)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetCasteProd)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GstrR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetNewMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetForageDir)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetNestDir)
#pragma alloc_text(RUN2_TEXT, SetModeProd)
#pragma alloc_text(RUN3_TEXT, StartAttack)
#pragma alloc_text(RUN4_TEXT, Recruit, UnRecruit, RecruitRed)
#pragma alloc_text(RUN5_TEXT, GetNewModeB, GetNewModeR)
#pragma alloc_text(RUN6_TEXT, GetRandDir)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetStrategy.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4BE C4C0 C4C2 C4C4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetStrategy(void)
{
    volatile int t;

    t = ChaseSpid;
    t = FuzLocX;
    t = FuzLocY;
    t = StrategicModeR[0];
}

int far GstrB(void)
{
#define HEALTH HealthB
    if (HEALTH < 10) {
        if ((BpopT >> 1) > RpopT && RpopT > 0 && QUEENS > 0)
            return 0;
    }
    if (HEALTH < 30)
        return 5;
    if (HEALTH < 50)
        return 4;
    if (DUG < BpopT)
        return 3;
    if (DUG < BpopT * 2)
        return 2;
    if (BpopT > 100 && RpopT > 0 && QUEENS > 0 && BpopT / 3 > RpopT)
        return 0;
    return 1;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetCasteProd.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4C6 C4C8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetCasteProd(void)
{
    volatile int t;

    t = CasteTabB;
    t = MakeMe;
}

void far SetModeProd(void)
{
    int scaled[6];
    int diff[6];
    int total;
    int i;
    int best;
    int max;
    int near *q;

    total = 0;
    for (i = 0; i < 3; i++)
        total += ModePopB[i];
    for (i = 0; i < 3; i++)
        scaled[i] = (unsigned)modeLevels[i] * (long)total / 65535UL;
    for (i = 0; i < 3; i++)
        diff[i] = scaled[i] - ModePopB[i];
    i = 0;
    max = 0;
    best = 0;
    for (i = 0; i < 3; i++) {
        if (diff[i] > max) {
            max = diff[i];
            best = i;
        }
    }
    ModeMe = ModeTabB[best];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GstrR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4CE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GstrR(void)
{
    volatile int t;

    t = (int)AdviceStrs;
}

void StartAttack(void) {
    JustToBeMean = SRand1(100) + 30;
    myBeginSong(0x2b0a,0x3f);
    EditMessage(AdviceStrs[10],AdviceStrs[11],0x78,0,0);
}

void far Recruit(int count)
{
    int i;
    int n;
    int type;
    int caste;

    n = count;
    i = ListIndexA;
    while (i > 0) {
        if (n <= 0)
            break;
        i--;
        type = AlistT(i);
        if (type != 0 && !(type & 0x80)) {
            caste = (type & 0x78) >> 3;
            if (caste == 2 || caste == 6) {
                if (AlistM(i) != 6) {
                    AlistM(i) = 6;
                    AlistS(i) = 0;
                    n--;
                }
            }
        }
    }
    i = ListIndexB;
    while (i > 0) {
        if (n <= 0)
            break;
        i--;
        type = BlistT(i);
        if (type != 0 && !(type & 0x80)) {
            caste = (type & 0x78) >> 3;
            if (caste == 2 || caste == 6) {
                if (BlistM(i) != 6) {
                    BlistM(i) = 6;
                    BlistS(i) = 0;
                    n--;
                }
            }
        }
    }
}

void far UnRecruit(int all)
{
    int n;
    int i;
    int type;

    n = RecruitPoolTotal;
    if (all == 0)
        n = n / 2;
    else
        n = n + 100;

    i = ListIndexA;
    if (i > 0) {
        while (n > 0) {
            i--;
            type = AlistT(i);
            if (type != 0 && !(type & 0x80)) {
                if (AlistM(i) == 6) {
                    AlistM(i) = 0;
                    n--;
                }
            }
            if (i <= 0)
                break;
        }
    }

    i = ListIndexB;
    if (i > 0) {
        while (n > 0) {
            i--;
            type = BlistT(i);
            if (type != 0 && !(type & 0x80)) {
                if (BlistM(i) == 6) {
                    BlistM(i) = 0;
                    n--;
                }
            }
            if (i <= 0)
                break;
        }
    }

    i = ListIndexR;
    if (i > 0) {
        while (n > 0) {
            i--;
            type = RlistT(i);
            if (type != 0 && !(type & 0x80)) {
                if (RlistM(i) == 6) {
                    RlistM(i) = 7;
                    n--;
                }
            }
            if (i <= 0)
                break;
        }
    }
}

void far RecruitRed(int count)
{
    int cur;
    int need;
    int i;
    int type;
    int mode;

    need = count;
    i = ListIndexA;
    while (i > 0 && need > 0) {
        i--;
        type = Dx8[i + 0x2f62];
        if (type != 0 && type > 0x7f) {
            cur = Dx8[i + 0x2b78];
            mode = (type & 0x78) >> 3;
            if (mode == 2 || mode == 6) {
                if (cur != 0x13 && cur != 6) {
                    Dx8[i + 0x2b78] = 6;
                    Dx8[i + 0x334c] = 0;
                    need--;
                }
            }
        }
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetNewMode.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4DA C4DC C4DE C4E0 C4E2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetNewMode(void)
{
    volatile int t;

    t = ModeTabWB[0][0];
    t = ModeTabSB[0][0];
    t = CasteModeTabB[0];
    t = (int)ModeAuto;
    t = (int)StrategicModeB;
}

int far GetNewModeB(int caste)
{
    if (ModeAuto == 1) {
        if (caste == 2)
            return ModeTabWB[StrategicModeB][SRand8()];
        if (caste == 6)
            return ModeTabSB[StrategicModeB][SRand8()];
    } else if (caste == 2 || caste == 6) {
        return ModeMe;
    }
    return CasteModeTabB[caste];
}

#define ModeTabWB ((signed char far *)ModeTabWB)  /* shape view of the unit declaration for this member only */
#define ModeTabSB ((signed char far *)ModeTabSB)  /* shape view of the unit declaration for this member only */
int far GetNewModeR(int mode)
{
    if (mode == 2) {
        return ModeTabWB[(StrategicModeR[0] << 3) + SRand8()];
    }
    if (mode == 6) {
        return ModeTabSB[(StrategicModeR[0] << 3) + SRand8()];
    }
    return CasteModeTabB[mode];
}
#undef ModeTabWB
#undef ModeTabSB

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetForageDir.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4E4 C4E6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetForageDir(void)
{
    volatile int t;

    t = PherMapBT;
    t = TurnTab[0][0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetNestDir.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4E8 C4EA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetNestDir(void)
{
    volatile int t;

    t = LastNewHoleR;
    t = LastNewHoleB;
}

int far GetRandDir(int x, int y, int dir)
{
    int r;

    if (x == 0) {
        if (y == 0)
            r = SRand1(3) + 3;
        else if (y == 63)
            r = SRand1(3) + 1;
        else
            r = SRand1(5) + 1;
    } else if (y == 0) {
        if (x == 127)
            r = SRand1(3) + 5;
        else
            r = SRand1(5) + 3;
    } else if (x == 127) {
        if (y == 63)
            r = SRand1(3) + 7;
        else
            r = SRand1(5) + 5;
    } else if (y == 63)
        r = SRand1(5) + 7;
    else
        r = 0;
    if (r != 0)
        return (unsigned char)r - 1 & 7;
    return TurnTab[dir][SRand8()];
}

