/* Candidate translation unit simant1_2D4E_DoAntSimB_12_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoAntSimB, _RaidInB, _RaidOutB, _DoRestB, _DoRandB, _DoRecruitN, _CheckNestFightB, _SimEggB, _TryEatFoodB, _EatFoodB, _DecEatB, _LeaveNestB
 * SCAFFOLDED: unclaimed members _DoNestAntB, _DoNestFightB, _SimQueenB, _QueenMoveB, _TryMoveDirB are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far ListIndexB;
extern int far Tindex;
extern unsigned char far Dx8[];
extern void far DoNestAntB(int life, int column, int attribute);
extern unsigned char near MapB[];
extern int far FoodB;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far GetEnterDirB(int x, int y, int dir);
extern int far TryMoveDirB(int x, int y, int dir);
extern int far GetExitDirB(int x, int y, int limit);
#define BlistT ((unsigned char far *)((unsigned char far *)Dx8 + 0x3D18))  /* pool word C352: one object, MAPSYM _Dx8+15640 */
extern int near MeColor;
extern int far OptionStates[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far GetNewMode(int caste, int type);
extern void far RestBalloons(int x, int y, int plane);
extern int far SRand32(void);
extern int far GetNewModeB(int mode);
extern int near MePlane;
extern void far DoDigOutB(int x, int y, int attacker);
#define AT(off) ((&Dx8)[off])
extern int far Cycle;
extern int far ModeAuto;
extern int far modeLevels[];
extern long far TotalEggsDiedB;
extern int far MakeMe;
extern int far SGRand(int range);
extern void far EggBalloons(int x, int y, int plane);
extern int far EatCountB;
extern int near CastePopB[];
extern int near BpopT;
extern int near HealthB;
extern int far AlwaysHealthy;
extern unsigned char near LifeB[128][64];
#define BlistS(i) AT((i) + 0x3f0e)
#define BlistM(i) AT((i) + 0x3b22)
extern unsigned char far HoleMapB[];
extern void far MakeNewHoleB(int x);
extern int far ExitHole(int hole, int x, int dir, int mode, int state);

extern int far TemBModePop;  /* scaffold reference for pool word C354 (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsExpired;  /* scaffold reference for pool word C356 (segment 9, MAPSYM_SITE_NAME) */
extern int far FlyAwayB;  /* scaffold reference for pool word C35A (segment 9, MAPSYM_SITE_NAME) */
extern int far RAntsExpired;  /* scaffold reference for pool word C35C (segment 9, MAPSYM_SITE_NAME) */
extern int far TemRModePop;  /* scaffold reference for pool word C35E (segment 9, MAPSYM_SITE_NAME) */
extern int far Dy8;  /* scaffold reference for pool word C364 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C366 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlkQueens;  /* scaffold reference for pool word C370 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastBlackEgg;  /* scaffold reference for pool word C372 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dy9;  /* scaffold reference for pool word C376 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TotalEggsLaidB;  /* scaffold reference for pool word C378 (segment 9, MAPSYM_SITE_NAME) */
extern int far TileMassYB;  /* scaffold reference for pool word C37A (segment 9, MAPSYM_SITE_NAME) */
extern int far TileMassXB;  /* scaffold reference for pool word C37C (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWantFood;  /* scaffold reference for pool word C37E (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoNestAntB(void);
void far pool_stub_DoNestFightB(void);
void far pool_stub_SimQueenB(void);
void far pool_stub_QueenMoveB(void);
void far pool_stub_TryMoveDirB(void);
void far RaidInB(int x, int y, int dirHint);
void far RaidOutB(int x, int y);
void far DoRestB(int x, int y, int attacker);
void far DoRandB(int x, int y, int attr, int modeArg);
void far DoRecruitN(int x, int y, int attacker);
int far CheckNestFightB(int x, int y, long attacker);
void far SimEggB(int x, int y);
void far TryEatFoodB(int y, int x);
void far EatFoodB(int x, int y);
void DecEatB(void);
int far LeaveNestB(int x, int y);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestFightB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimQueenB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_QueenMoveB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_TryMoveDirB)
#pragma alloc_text(RUN2_TEXT, RaidInB, RaidOutB, DoRestB)
#pragma alloc_text(RUN3_TEXT, DoRandB, DoRecruitN)
#pragma alloc_text(RUN4_TEXT, CheckNestFightB)
#pragma alloc_text(RUN5_TEXT, SimEggB)
#pragma alloc_text(RUN6_TEXT, TryEatFoodB, EatFoodB)
#pragma alloc_text(RUN7_TEXT, DecEatB)
#pragma alloc_text(RUN8_TEXT, LeaveNestB)

void far DoAntSimB(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexB;
    while (Tindex > 0) {
        --Tindex;
        life = Dx8[Tindex + 0x3736];
        column = Dx8[Tindex + 0x392c] & 0xff;
        attribute = Dx8[Tindex + 0x3d18];
        if (attribute != 0)
            DoNestAntB(life, column, attribute);
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestAntB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C352 C354 C356 C358 C35A C35C C35E C360; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestAntB(void)
{
    volatile int t;

    t = Dx8[0];
    t = TemBModePop;
    t = BAntsExpired;
    t = OptionStates[0];
    t = FlyAwayB;
    t = RAntsExpired;
    t = TemRModePop;
    t = (int)TotalEggsDiedB;
}

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far RaidInB(int x, int y, int dirHint)
{
    int dir;

    if (MapB[(x << 6) + y] >= 0x10 && MapB[(x << 6) + y] <= 0x13) {
        if (MapB[(x << 6) + y] == 0x10)
            MapB[(x << 6) + y] = (unsigned char)SRand8();
        else
            MapB[(x << 6) + y]--;
        if (FoodB > 0)
            FoodB--;
        Dx8[Tindex + 0x3b22] = 3;
        Dx8[Tindex + 0x3d18] |= 8;
        LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];
        return;
    }

    dir = (SRand1(3) + dirHint - 2) & 7;
    if (TryMoveDirB(x, y, dir) != 0)
        return;

    dir = GetEnterDirB(x, y, dirHint & 7);
    if (dir < 0)
        dir = SRand1(8);
    if (TryMoveDirB(x, y, dir) != 0)
        return;

    Dx8[Tindex + 0x3b22] = 1;
    LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];
}
#undef LifeB

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far RaidOutB(int x, int y)
{
    int dir;

    dir = GetExitDirB(x, y, 8);
    if (dir == 0)
        dir = SRand8();
    else
        dir--;
    if (TryMoveDirB(x, y, dir) == 0) {
        if (TryMoveDirB(x, y, SRand8()) == 0)
            LifeB[x * 64 + y] = BlistT[Tindex];
    }
}
#undef LifeB

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far DoRestB(int x, int y, int attacker)
{
    int index;
    int handled;
    int ant;
    int winner;
    int type;
    int caste;

    ant = LifeB[(x << 6) + y];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8 && (index = FindInBList(x, y, ant)) >= 0) {
        winner = GetWinner(ant, attacker);
        Dx8[index + 0x3f0e] = winner;
        Dx8[index + 0x3d18] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        Dx8[index + 0x3b22] = 0xa;
        handled = 1;
    } else {
        handled = 0;
    }
    if (handled == 1)
        return;

    LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];
    if (SRand1(20) == 0) {
        type = Dx8[Tindex + 0x3d18];
        caste = (type & 0x78) >> 3;
        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewMode(caste, type);
        return;
    }
    if (OptionStates[5] == 1)
        RestBalloons(x, y, 2);
}
#undef LifeB

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far DoRandB(int x, int y, int attr, int modeArg)
{
    int index;
    int handled;
    int ant;
    int winner;

    if (SRand32() == 0)
        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(modeArg);

    ant = LifeB[(x << 6) + y];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8 && (index = FindInBList(x, y, ant)) >= 0) {
        winner = GetWinner(ant, attr);
        Dx8[index + 0x3f0e] = winner;
        Dx8[index + 0x3d18] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        Dx8[index + 0x3b22] = 0xa;
        handled = 1;
    } else {
        handled = 0;
    }
    if (handled == 1)
        return;

    if (TryMoveDirB(x, y, attr & 7) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
#undef LifeB

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far DoRecruitN(int x, int y, int attacker)
{
    int index;
    int handled;
    int ant;
    int winner;

    if (MePlane != 2) {
        DoDigOutB(x, y, attacker);
        return;
    }

    ant = LifeB[(x << 6) + y];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8 && (index = FindInBList(x, y, ant)) >= 0) {
        winner = GetWinner(ant, attacker);
        Dx8[index + 0x3f0e] = winner;
        Dx8[index + 0x3d18] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        Dx8[index + 0x3b22] = 0xa;
        handled = 1;
    } else {
        handled = 0;
    }
    if (handled == 1)
        return;

    if (TryMoveDirB(x, y, attacker & 7) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
#undef LifeB

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestFightB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C364 C366; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestFightB(void)
{
    volatile int t;

    t = Dy8;
    t = Dx9;
}

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
#define Dx8 ((Dx8)[0])  /* shape view of the unit declaration for this member only */
int far CheckNestFightB(int x, int y, long attacker)
{
    unsigned char near *cell;
    int ant;
    int index;
    int winner;

    cell = &LifeB[(x << 6) + y];
    ant = *cell & 0xff;
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        return 1;
    }
    if (ant > 0x87 && ant < 0xe8) {
        index = FindInBList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, (int)attacker);
            AT(index + 0x3f0e) = winner;
            AT(index + 0x3d18) = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            AT(index + 0x3b22) = 0xa;
            return 1;
        }
    }
    return 0;
}
#undef LifeB
#undef Dx8

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far SimEggB(int x, int y)
{
    int attr;
    int mode;
    int mask;

    attr = Dx8[Tindex + 0x3d18];
    mode = -1;

    if (BpopT <= 2)
        mask = 0x1f;
    else
        mask = 0x7f;
    if (!(Cycle & mask)) {
        attr++;
        if ((attr & 0xf) == 8) {
            if (ModeAuto != 0 || (int)((unsigned int)modeLevels[2] >> 7) >= SGRand(255)) {
                mode = MakeMe;
                attr = (mode << 3) + 2;
                if (mode == 2)
                    Dx8[Tindex + 0x3b22] = 1;
                else
                    Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(mode);
            } else {
                attr = 0;
                TotalEggsDiedB++;
            }
        }
    }

    if (OptionStates[5] != 0 && mode < 0)
        EggBalloons(x, y, 2);

    LifeB[(x << 6) + y] = (unsigned char)attr;
    Dx8[Tindex + 0x3d18] = (unsigned char)attr;
    Dx8[Tindex + 0x3f0e] = 0;
}
#undef LifeB

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimQueenB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C370 C372 C374 C376 C378; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimQueenB(void)
{
    volatile int t;

    t = BlkQueens;
    t = LastBlackEgg;
    t = (int)EatCountB;
    t = Dy9;
    t = TotalEggsLaidB;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _QueenMoveB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C37A C37C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_QueenMoveB(void)
{
    volatile int t;

    t = TileMassYB;
    t = TileMassXB;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _TryMoveDirB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C37E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_TryMoveDirB(void)
{
    volatile int t;

    t = MeWantFood;
}

void far TryEatFoodB(int y, int x)
{
    int threshold;
    int level;

    level = MapB[x + y * 64];
    if (level < 0x10 || level > 0x13)
        return;
    if (level == 0x10)
        MapB[x + y * 64] = SRand8();
    else
        MapB[x + y * 64]--;

    if (FoodB > 0)
        FoodB--;
    threshold = (BpopT + CastePopB[2]) >> 4;
    EatCountB += 5;
    if (threshold < EatCountB) {
        EatCountB = 0;
        if (HealthB < 100)
            HealthB++;
    }
}

void far EatFoodB(int x, int y)
{
    if (MapB[x * 64 + y] == 0x10)
        MapB[x * 64 + y] = SRand8();
    else
        MapB[x * 64 + y]--;

    if (FoodB > 0)
        FoodB--;
    EatCountB += 5;
    if ((BpopT + CastePopB[2]) >> 4 < EatCountB) {
        EatCountB = 0;
        if (HealthB < 100)
            HealthB++;
    }
}

void DecEatB(void)
{
    --EatCountB;
    if (EatCountB < 0) {
        EatCountB = BpopT >> 5;
        if (HealthB > 0 && !AlwaysHealthy)
            --HealthB;
    }
}

#undef BlistT
#define BlistT(i) AT((i) + 0x3d18)
#define Dx8 ((Dx8)[0])  /* shape view of the unit declaration for this member only */
int far LeaveNestB(int x, int y)
{
    int dir;

    dir = BlistT(Tindex);
    BlistT(Tindex) = 0;
    if (HoleMapB[x] == 0)
        MakeNewHoleB(x);
    if (ExitHole(HoleMapB[x], x, SRand8() + (dir & 0xf8), BlistM(Tindex), BlistS(Tindex))) {
        LifeB[x][y] = 0;
        return 1;
    }
    BlistT(Tindex) = dir;
    BlistM(Tindex) = 0;
    return 0;
}
#undef Dx8
#undef BlistT
#define BlistT ((unsigned char far *)((unsigned char far *)Dx8 + 0x3D18))  /* pool word C352: one object, MAPSYM _Dx8+15640 */

