/* Candidate translation unit simant1_2D4E_DoAntSimB_15_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoAntSimB, _RaidInB, _RaidOutB, _DoRestB, _DoRandB, _DoRecruitN, _CheckNestFightB, _SimEggB, _QueenMoveB, _MakeNewTailB, _TryEatFoodB, _EatFoodB, _DecEatB, _LeaveNestB, _GetOutB
 * SCAFFOLDED: unclaimed members _DoNestAntB, _DoNestFightB, _SimQueenB, _TryMoveDirB are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct BListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct BListPlanes far BlistX;
extern int far ListIndexB;
extern int far Tindex;
extern void far DoNestAntB(int life, int column, int attribute);
extern unsigned char near MapB[];
extern int far FoodB;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far GetEnterDirB(int x, int y, int dir);
extern int far TryMoveDirB(int x, int y, int dir);
extern int far GetExitDirB(int x, int y, int limit);
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
extern int far Cycle;
extern int far ModeAuto;
extern int far modeLevels[];
extern long far TotalEggsDiedB;
extern int far MakeMe;
extern int far SGRand(int range);
extern void far EggBalloons(int x, int y, int plane);
extern int far TileMassXB;
extern int far TileMassYB;
extern char far Dy8[];
extern char far Dx8[];
extern int far GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern void far AddAntToBList(int, int, int, int, int);
extern int far EatCountB;
extern int near CastePopB[];
extern int near BpopT;
extern int near HealthB;
extern int far AlwaysHealthy;
extern unsigned char near LifeB[128][64];
extern unsigned char far HoleMapB[];
extern void far MakeNewHoleB(int x);
extern int far ExitHole(int hole, int x, int dir, int mode, int state);
extern unsigned char far ExitMapB[];
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemB(int x, int count);

extern int far match_position;  /* scaffold reference for pool word C354 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C356 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C35A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C35C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C35E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C370 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C372 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C376 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C378 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C37E (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoNestAntB(void);
void far pool_stub_DoNestFightB(void);
void far pool_stub_SimQueenB(void);
void far pool_stub_TryMoveDirB(void);
void far RaidInB(int x, int y, int dirHint);
void far RaidOutB(int x, int y);
void far DoRestB(int x, int y, int attacker);
void far DoRandB(int x, int y, int attr, int modeArg);
void far DoRecruitN(int x, int y, int attacker);
int far CheckNestFightB(int x, int y, long attacker);
void far SimEggB(int x, int y);
int far QueenMoveB(int x, int y, int dirHint);
void far MakeNewTailB(int index);
void far TryEatFoodB(int y, int x);
void far EatFoodB(int x, int y);
void DecEatB(void);
int far LeaveNestB(int x, int y);
int far GetOutB(int x);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestFightB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimQueenB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_TryMoveDirB)
#pragma alloc_text(RUN2_TEXT, RaidInB, RaidOutB, DoRestB)
#pragma alloc_text(RUN3_TEXT, DoRandB, DoRecruitN)
#pragma alloc_text(RUN4_TEXT, CheckNestFightB)
#pragma alloc_text(RUN5_TEXT, SimEggB)
#pragma alloc_text(RUN6_TEXT, QueenMoveB, MakeNewTailB)
#pragma alloc_text(RUN7_TEXT, TryEatFoodB, EatFoodB)
#pragma alloc_text(RUN8_TEXT, DecEatB)
#pragma alloc_text(RUN9_TEXT, LeaveNestB, GetOutB)

void far DoAntSimB(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexB;
    while (Tindex > 0) {
        --Tindex;
        life = BlistX.x[Tindex];
        column = BlistX.y[Tindex] & 0xff;
        attribute = BlistX.t[Tindex];
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

    t = *(int far *)&BlistX;
    t = match_position;
    t = match_length;
    t = OptionStates[0];
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
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
        BlistX.m[Tindex] = 3;
        BlistX.t[Tindex] |= 8;
        LifeB[(x << 6) + y] = BlistX.t[Tindex];
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

    BlistX.m[Tindex] = 1;
    LifeB[(x << 6) + y] = BlistX.t[Tindex];
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
            LifeB[x * 64 + y] = BlistX.t[Tindex];
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
        BlistX.s[index] = winner;
        BlistX.t[index] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        BlistX.m[index] = 0xa;
        handled = 1;
    } else {
        handled = 0;
    }
    if (handled == 1)
        return;

    LifeB[(x << 6) + y] = BlistX.t[Tindex];
    if (SRand1(20) == 0) {
        type = BlistX.t[Tindex];
        caste = (type & 0x78) >> 3;
        BlistX.m[Tindex] = (unsigned char)GetNewMode(caste, type);
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
        BlistX.m[Tindex] = (unsigned char)GetNewModeB(modeArg);

    ant = LifeB[(x << 6) + y];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8 && (index = FindInBList(x, y, ant)) >= 0) {
        winner = GetWinner(ant, attr);
        BlistX.s[index] = winner;
        BlistX.t[index] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        BlistX.m[index] = 0xa;
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
        BlistX.s[index] = winner;
        BlistX.t[index] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        BlistX.m[index] = 0xa;
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

    t = Dy8[0];
    t = Dx8[0];
}

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
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
            BlistX.s[index] = winner;
            BlistX.t[index] = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            BlistX.m[index] = 0xa;
            return 1;
        }
    }
    return 0;
}
#undef LifeB

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void far SimEggB(int x, int y)
{
    int attr;
    int mode;
    int mask;

    attr = BlistX.t[Tindex];
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
                    BlistX.m[Tindex] = 1;
                else
                    BlistX.m[Tindex] = (unsigned char)GetNewModeB(mode);
            } else {
                attr = 0;
                TotalEggsDiedB++;
            }
        }
    }

    if (OptionStates[5] != 0 && mode < 0)
        EggBalloons(x, y, 2);

    LifeB[(x << 6) + y] = (unsigned char)attr;
    BlistX.t[Tindex] = (unsigned char)attr;
    BlistX.s[Tindex] = 0;
}
#undef LifeB

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimQueenB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C370 C372 C374 C376 C378; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimQueenB(void)
{
    volatile int t;

    t = MiscStrs;
    t = Dx9;
    t = (int)EatCountB;
    t = Dy9;
    t = LastQueenPlane;
}

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
int far QueenMoveB(int x, int y, int dirHint)
{
    int dir;
    int newRow;
    int newCol;
    int opp;
    int index;

    dir = GetBestDir(2, x, y, TileMassXB, TileMassYB);
    if (dir < 0) {
        dir++;
        if (dir == 0)
            return 0;
        dir = SRand8();
    }
    if (y < 3) {
        if (dir > 5)
            return 0;
        if (dir < 3)
            return 0;
    }
    if (TryMoveDirB(x, y, dir) != 0) {
                opp = (dirHint ^ 0xfc) & 7;
                newCol = x + Dx8[opp];
                newRow = y + Dy8[opp];
                LifeB[newCol * 64 + newRow] = 0;

                index = FindInBList(newCol, newRow, (dirHint & 7) + 0x68);
                if (index >= 0 && BlistX.t[index] != 0) {
                    BlistX.x[index] = (char)x;
                    BlistX.y[index] = (char)y;
                    BlistX.t[index] = (char)(dir + 0x68);
                    LifeB[x * 64 + y] = (unsigned char)(dir + 0x68);
                }
        return 1;
    }
    return 0;
}
#undef LifeB

#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
#define Dy8 ((signed char far *)Dy8)  /* shape view of the unit declaration for this member only */
void far MakeNewTailB(int index)
{
    unsigned char type;
    int direction;
    int life;
    int column;

    type = BlistX.t[index];
    direction = type & 7;
    direction ^= 4;
    life = BlistX.x[index] + (signed char)Dx8[direction];
    column = BlistX.y[index] + (signed char)Dy8[direction];
    AddAntToBList(life, column, type + 8, 9, 0);
}
#undef Dx8
#undef Dy8

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _TryMoveDirB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C37E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_TryMoveDirB(void)
{
    volatile int t;

    t = EditDragPnt;
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

int far LeaveNestB(int x, int y)
{
    int dir;

    dir = BlistX.t[Tindex];
    BlistX.t[Tindex] = 0;
    if (HoleMapB[x] == 0)
        MakeNewHoleB(x);
    if (ExitHole(HoleMapB[x], x, SRand8() + (dir & 0xf8), BlistX.m[Tindex], BlistX.s[Tindex])) {
        LifeB[x][y] = 0;
        return 1;
    }
    BlistX.t[Tindex] = dir;
    BlistX.m[Tindex] = 0;
    return 0;
}

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
int far GetOutB(int x)
{
    
    int raw;

    if (MapB[x << 6] == 0x18) {
        raw = BlistX.t[Tindex];
        BlistX.t[Tindex] = 0;
        if (HoleMapB[x] == 0)
            MakeNewHoleB(x);
        if (ExitHole(HoleMapB[x], x, SRand8() + (raw & 0xf8),
                      BlistX.m[Tindex], BlistX.s[Tindex]) != 0) {
            LifeB[(x << 6) + 1] = 0;
            return 1;
        }
        BlistX.t[Tindex] = raw;
        BlistX.m[Tindex] = 0;
        return 0;
    }

    if (ExitMapB[x << 6] != 0)
        ExitMapB[x << 6]--;

    if (SRand2() != 0) {
        if (x > 0 && IsItDirt(MapB[(x << 6) - 0x3f]) != 0)
            DigTileThemB(x - 1, 1);
    } else {
        if (x < 0x3f && IsItDirt(MapB[(x << 6) + 0x41]) != 0)
            DigTileThemB(x + 1, 1);
    }

    TryMoveDirB(x, 1, SRand8());
    return 0;
}
#undef LifeB

