/* Candidate translation unit simtwo_0000_GetStrategy_15_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetStrategy, _GstrB, _SetCasteProd, _SetModeProd, _StartAttack, _Recruit, _UnRecruit, _RecruitRed, _UnRecruitRed, _GetNewModeB, _GetNewModeR, _GetForageDir, _GetRandDir, _GetDefendDir, _GetRedDefendDir
 * SCAFFOLDED: unclaimed members _GstrR, _GetNewMode, _GetNestDir are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near HealthB;
extern int near BpopT;
extern int near RpopT;
extern int far ChaseSpid;
extern int far FuzLocX;
extern int far FuzLocY;
extern int far SpidOn;
extern int far RedQueens;
extern int far TilesDugB;
extern int far StrategicModeB;
extern int far SRand1(unsigned int range);
extern int near SpidX;
extern int near SpidY;
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GstrR(void);
extern void far SetCasteProd(void);
extern void far SetModeProd(void);
#define QUEENS RedQueens
#define DUG TilesDugB
extern int near CastePopB[];
extern int far IdealCaste[];
extern int far CasteTabB[];
extern int far MakeMe;
extern int far ModePopB[];
extern int far modeLevels[];
extern int far ModeTabB[];
extern int far ModeMe;
extern unsigned int far JustToBeMean;
extern unsigned int far * far AdviceStrs;
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
extern char far ModeTabWB[][8];
extern char far ModeTabSB[][8];
extern char far CasteModeTabB[];
extern int far StrategicModeR[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBT[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRT[64][32];
extern char far Dy8[];
extern char far TurnTab[][8];
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far GetNestDir(int x, int y, int dir, int flag);
extern int far RedPlane;
extern int far RedLocX;
extern int far RedLocY;
extern int far ModePopR[];

extern int far Dx9;  /* scaffold reference for pool word C4E8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C4EA (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_GstrR(void);
void far pool_stub_GetNewMode(void);
void far pool_stub_GetNestDir(void);
void StartAttack(void);
void far Recruit(int count);
void far UnRecruit(int all);
void far RecruitRed(int count);
void far UnRecruitRed(void);
int far GetNewModeB(int caste);
int far GetNewModeR(int mode);
int far GetForageDir(int x, int y, int dir, int attribute);
int far GetAlarmDir(int x, int y, int dir);
int far GetRandDir(int x, int y, int dir);
int far GetDefendDir(int x, int y, int dir);
int far GetRedDefendDir(int x, int y, int dir);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GstrR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetNewMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GetNestDir)
#pragma alloc_text(RUN2_TEXT, StartAttack)
#pragma alloc_text(RUN3_TEXT, Recruit, UnRecruit, RecruitRed, UnRecruitRed)
#pragma alloc_text(RUN4_TEXT, GetNewModeB, GetNewModeR, GetForageDir)
#pragma alloc_text(RUN5_TEXT, GetAlarmDir)
#pragma alloc_text(RUN6_TEXT, GetRandDir, GetDefendDir, GetRedDefendDir)

#define StrategicModeR ((StrategicModeR)[0])  /* shape view of the unit declaration for this member only */
void far GetStrategy(void)
{
    int distance;

    ChaseSpid = 0;
    if (MePlane == 1) {
        FuzLocX = SRand1(5) + MeLocX - 2;
        FuzLocY = SRand1(5) + MeLocY - 2;
        if (FuzLocX < 0)
            FuzLocX = 0;
        if (FuzLocX > 127)
            FuzLocX = 127;
        if (FuzLocY < 0)
            FuzLocY = 0;
        if (FuzLocY > 63)
            FuzLocY = 63;
        if (SpidOn) {
            distance = (int)GetDis(SpidX >> 4, SpidY >> 4, MeLocX, MeLocY);
            if (distance < 100)
                ChaseSpid = 1;
        }
    }

    FuzLocX = MeLocX;
    if (HealthB < 10) {
        if ((BpopT >> 1) <= RpopT)
            goto chooseMode;
        if (RpopT <= 0)
            goto chooseMode;
        if (RedQueens <= 0)
            goto chooseMode;
        StrategicModeB = 0;
        goto strategyReady;
    }
    goto chooseMode;

chooseMode:
    if (HealthB < 30) {
        StrategicModeB = 5;
    } else if (HealthB < 50) {
        StrategicModeB = 4;
    } else {
        if (TilesDugB < BpopT) {
            StrategicModeB = 3;
        } else if (TilesDugB < BpopT * 2) {
            StrategicModeB = 2;
        } else if (BpopT > 100) {
                if (RpopT <= 0 || RedQueens <= 0 || BpopT / 3 <= RpopT)
                StrategicModeB = 1;
            else
                StrategicModeB = 0;
        } else {
            StrategicModeB = 1;
        }
    }
strategyReady:
    StrategicModeR = GstrR();
    SetCasteProd();
    SetModeProd();
}
#undef StrategicModeR

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

void far SetCasteProd(void)
{
    int i;
    int diff;
    int pct[5];
    int want[5];

    {
        int total;
        int ideal;
        total = 0;
        ideal = 0;
        for (i = 0; i < 4; i++) {
            total += CastePopB[i + 1];
            ideal += IdealCaste[i];
        }
        for (i = 0; i < 4; i++) {
            if (total <= 0)
                pct[i] = 0;
            else
                pct[i] = 100L * CastePopB[i + 1] / total;
            if (ideal <= 0)
                want[i] = 0;
            else
                want[i] = 100L * IdealCaste[i] / ideal;
        }
    }
    {
        int best;
        int chosen;
        best = 0;
        chosen = best;
        for (i = 0; i < 4; i++) {
            diff = pct[i] - want[i];
            if (diff < best) {
                best = diff;
                chosen = i;
            }
        }
        MakeMe = CasteTabB[chosen];
    }
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

void far UnRecruitRed(void)
{
    int index;

    index = ListIndexA;
    if (index <= 0)
        return;

    do {
        int type;

        index--;
        type = Dx8[index + 0x2f62];
        if (type != 0 && type > 0x7f) {
            if (Dx8[index + 0x2b78] == 6)
                Dx8[index + 0x2b78] = 0;
        }
    } while (index > 0);
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
#define CasteModeTabB ((signed char far *)CasteModeTabB)  /* shape view of the unit declaration for this member only */
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
#undef CasteModeTabB

#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
int far GetForageDir(int x, int y, int dir, int attribute)
{
    int xCell;
    int yCell;
    int plane;
    int best;
    int bestDir;
    int i;
    int nx;
    int ny;
    int current;
    int value;

    if (x == 0) {
        if (y == 0)
            return 3;
        if (y == 63)
            return 1;
        return SRand1(3) + 1;
    }
    if (y == 0) {
        if (x == 127)
            return 5;
        return SRand1(3) + 3;
    }
    if (x == 127) {
        if (y == 63)
            return 7;
        return SRand1(3) + 5;
    }
    if (y == 63)
        return (SRand1(3) - 1) & 7;

    xCell = x >> 1;
    yCell = y >> 1;
    plane = attribute & 0x80;
    if (plane)
        current = PherMapRT[xCell][yCell];
    else
        current = PherMapBT[xCell][yCell];

    best = 0;
    bestDir = SRand8();
    for (i = 0; i < 8; ++i) {
        nx = xCell + Dx8[i];
        nx &= 0x3f;
        ny = yCell + Dy8[i];
        ny &= 0x1f;
        if (plane)
            value = PherMapRT[nx][ny];
        else
            value = PherMapBT[nx][ny];
        if (value > best) {
            best = value;
            bestDir = i;
        }
    }
    if (best > 0) {
        if (current > best)
            return -1;
        return TurnTab[dir][bestDir];
    }
    return TurnTab[dir][SRand8()];
}
#undef Dx8

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GetNestDir.
 * It only reproduces the object's selector-pool allocation order for the
 * words C4E8 C4EA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GetNestDir(void)
{
    volatile int t;

    t = Dx9;
    t = Dy9;
}

int far GetAlarmDir(int x, int y, int dir)
{
    int r;
    register int i;
    int best;
    register int bestValue;
    int row;
    int col;
    unsigned char value;
    int yh;
    int xh;

    xh = x >> 1;
    yh = y >> 1;

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

    i = 0;
    bestValue = i;
    best = bestValue;
    for (; i < 8; i++) {
        col = (Dy8[i] + yh) & 0x1f;
        row = (Dx8[i] + xh) & 0x3f;
        value = (unsigned char)Dx8[0x52d2 + (row << 5) + col];
        if (value > bestValue) {
            bestValue = value;
            best = i;
        }
    }
    if (bestValue != 0)
        return TurnTab[dir][best];
    return TurnTab[dir][SRand8()];
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

int far GetDefendDir(int x, int y, int dir)
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

    switch (MePlane) {
    case 1:
        goto chase;
    case 2:
        return GetNestDir(x, y, dir, 0);
    case 3:
        return GetNestDir(x, y, dir, 0x80);
    }
check:
    if (r != 0)
        return ((char far *)TurnTab - 1)[dir * 8 + r];
    return dir;

chase:
    if (ChaseSpid == 1) {
        r = GetDir(x, y, SpidX >> 4, SpidY >> 4);
    } else {
        r = GetDis(x, y, FuzLocX, FuzLocY);
        if (ModePopB[5] >> 1 < r)
            r = GetDir(x, y, FuzLocX, FuzLocY);
        else
            r = SRand1(8) + 1;
    }
    goto check;
}

int far GetRedDefendDir(int x, int y, int dir)
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

    switch (RedPlane) {
    case 1:
        goto chase;
    case 2:
        return GetNestDir(x, y, dir, 0);
    case 3:
        return GetNestDir(x, y, dir, 0x80);
    }
check:
    if (r != 0)
        return ((char far *)TurnTab - 1)[dir * 8 + r];
    return dir;

chase:
    r = GetDis(x, y, RedLocX, RedLocY);
    if (ModePopR[5] >> 1 < r)
        r = GetDir(x, y, RedLocX, RedLocY);
    else
        r = SRand1(8) + 1;
    goto check;
}

