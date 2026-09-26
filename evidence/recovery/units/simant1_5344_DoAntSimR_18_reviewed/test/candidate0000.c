/* Candidate translation unit simant1_5344_DoAntSimR_11_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoAntSimR, _RaidInR, _StayInR, _RaidOutR, _DoRestR, _DoRandR, _DoNestFightR, _CheckNestFightR, _SimEggR, _QueenMoveR, _KillTailR, _LostHeadR, _LostTailR, _TryMoveDirR, _TryEatFoodR, _EatFoodR, _StealFoodR, _DecEatR
 * SCAFFOLDED: unclaimed members _DoNestAntR and _SimQueenR are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far ListIndexR;
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far TileMassYR;
extern int far TileMassXR;
extern int near GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern void far DoNestAntR(int life, int column, int attribute);
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far FoodR;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far SRand16(void);
extern int far GetEnterDirR(int x, int y, int dir);
extern int far TryMoveDirR(int x, int y, int dir);
extern int near GetOutR(int x);
extern int far GetExitDirR(int x, int y, int limit);
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
#define RlistY RlistX.y
#define RlistM RlistX.m
#define RlistS RlistX.s
#define RlistT RlistX.t
extern int near MeColor;
extern int far OptionStates[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far GetNewMode(int caste, int type);
extern void far RestBalloons(int x, int y, int plane);
extern int far SRand32(void);
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);
extern void far FightBalloons(int x, int y, int kind);
extern unsigned char near CasteModeTab[];
extern int far GetNewModeR(int mode);
extern int far Cycle;
extern int far StrategicModeR;
extern char far CasteTabC[];
extern void far EggBalloons(int x, int y, int plane);
extern int far EatCountR;
extern int near CastePopR[];
extern int near RpopT;
extern int near HealthR;

extern int far TemRModePop;  /* scaffold reference for pool word C388 (segment 9, MAPSYM_SITE_NAME) */
extern int far RAntsExpired;  /* scaffold reference for pool word C38A (segment 9, MAPSYM_SITE_NAME) */
extern int far FlyAwayR;  /* scaffold reference for pool word C38E (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsExpired;  /* scaffold reference for pool word C390 (segment 9, MAPSYM_SITE_NAME) */
extern int far TemBModePop;  /* scaffold reference for pool word C392 (segment 9, MAPSYM_SITE_NAME) */
extern int far RedQueens;  /* scaffold reference for pool word C3A0 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastRedEgg;  /* scaffold reference for pool word C3A2 (segment 8, MAPSYM_SITE_NAME) */

void far pool_stub_DoNestAntR(void);
void far pool_stub_SimQueenR(void);
void far RaidInR(int x, int y, int dirHint);
void far StayInR(int x, int y, int dirHint);
void far RaidOutR(int x, int y);
void far DoRestR(int x, int y, int attacker);
void far DoRandR(int x, int y, int attr, int modeArg);
void far DoNestFightR(int x, int y);
int far CheckNestFightR(int x, int y, int attacker);
void far SimEggR(int x, int y);
int far QueenMoveR(int x, int y, int dirHint);
void KillTailR(int tail);
int far LostHeadR(int x, int y, int attr);
int far LostTailR(int x, int y, int attr);
void far TryEatFoodR(int y, int x);
void far EatFoodR(int x, int y);
void far StealFoodR(int x, int y);
void DecEatR(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimQueenR)
#pragma alloc_text(RUN2_TEXT, RaidInR, StayInR, RaidOutR, DoRestR)
#pragma alloc_text(RUN3_TEXT, DoRandR)
#pragma alloc_text(RUN4_TEXT, DoNestFightR)
#pragma alloc_text(RUN5_TEXT, CheckNestFightR)
#pragma alloc_text(RUN6_TEXT, SimEggR)
#pragma alloc_text(RUN7_TEXT, QueenMoveR)
#pragma alloc_text(RUN8_TEXT, KillTailR)
#pragma alloc_text(RUN9_TEXT, LostHeadR)
#pragma alloc_text(RUN10_TEXT, LostTailR)
#pragma alloc_text(RUN11_TEXT, TryMoveDirR)
#pragma alloc_text(RUN12_TEXT, TryEatFoodR, EatFoodR, StealFoodR, DecEatR)

void far DoAntSimR(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexR;
    while (Tindex > 0) {
        --Tindex;
        life = RlistX.x[Tindex];
        column = RlistX.y[Tindex] & 0xff;
        attribute = RlistX.t[Tindex];
        if (attribute != 0)
            DoNestAntR(life, column, attribute);
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestAntR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C386 C388 C38A C38C C38E C390 C392; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestAntR(void)
{
    volatile int t;

    t = RlistX.m[0];
    t = TemRModePop;
    t = RAntsExpired;
    t = OptionStates[0];
    t = FlyAwayR;
    t = BAntsExpired;
    t = TemBModePop;
}

void far RaidInR(int x, int y, int dirHint)
{
    int dir;

    if (MapR[(x << 6) + y] >= 0x10 && MapR[(x << 6) + y] <= 0x13) {
        if (MapR[(x << 6) + y] == 0x10)
            MapR[(x << 6) + y] = (unsigned char)SRand8();
        else
            MapR[(x << 6) + y]--;
        if (FoodR > 0)
            FoodR--;
        RlistX.m[Tindex] = 3;
        RlistX.t[Tindex] |= 8;
        LifeR[(x << 6) + y] = RlistX.t[Tindex];
        return;
    }

    dir = (SRand1(3) + dirHint - 2) & 7;
    if (TryMoveDirR(x, y, dir) != 0)
        return;

    dir = GetEnterDirR(x, y, dirHint & 7);
    if (dir < 0)
        dir = SRand1(8);
    if (TryMoveDirR(x, y, dir) != 0)
        return;

    RlistX.m[Tindex] = 1;
    LifeR[(x << 6) + y] = RlistX.t[Tindex];
}

void far StayInR(int x, int y, int dirHint)
{
    int dir;

    if (MapR[(x << 6) + y] >= 0x10 && MapR[(x << 6) + y] <= 0x13) {
        if (MapR[(x << 6) + y] == 0x10)
            MapR[(x << 6) + y] = (unsigned char)SRand8();
        else
            MapR[(x << 6) + y]--;
        if (FoodR > 0)
            FoodR--;
        RlistX.m[Tindex] = 3;
        RlistX.t[Tindex] |= 8;
        LifeR[(x << 6) + y] = RlistX.t[Tindex];
        return;
    }

    dir = (SRand1(3) + dirHint - 2) & 7;
    RlistX.t[Tindex] = (RlistX.t[Tindex] & 0xf8) | dir;
    if (TryMoveDirR(x, y, dir) != 0)
        return;

    dir = GetEnterDirR(x, y, dirHint & 7);
    if (dir < 0)
        dir = SRand1(8);
    if (TryMoveDirR(x, y, dir) != 0)
        return;

    LifeR[(x << 6) + y] = RlistX.t[Tindex];
}

void far RaidOutR(int x, int y)
{
    int dir;

    dir = GetExitDirR(x, y, 8);
    if (dir == 0)
        dir = SRand8();
    else
        dir--;
    if (TryMoveDirR(x, y, dir) == 0) {
        if (TryMoveDirR(x, y, SRand8()) == 0)
            LifeR[x * 64 + y] = RlistT[Tindex];
    }
}

void far DoRestR(int x, int y, int attacker)
{
    int ant;
    int handled;
    int index;
    int winner;
    int type;
    int caste;

    ant = LifeR[(x << 6) + y];
    do {
        if (ant > 7 && ant < 0x68) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attacker);
                RlistX.s[index] = winner;
                RlistX.t[index] = (winner & 0x80) + 0x70;
                LifeR[(x << 6) + y] = (winner & 0x80) + 0x70;
                RlistX.m[index] = 0xa;
                handled = 1;
                break;
            }
        } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
            YellowFight(3, Tindex);
            handled = 1;
            break;
        }
        handled = 0;
    } while (0);
    if (handled)
        return;

    LifeR[(x << 6) + y] = RlistX.t[Tindex];
    if (SRand1(20) == 0) {
        type = RlistX.t[Tindex];
        caste = (type & 0x78) >> 3;
        RlistX.m[Tindex] = (unsigned char)GetNewMode(caste, type);
        return;
    }
    if (OptionStates[5] != 0)
        RestBalloons(x, y, 3);
}

void far DoRandR(int x, int y, int attr, int modeArg)
{
    int ant;
    int handled;
    int index;
    int winner;

    if (SRand32() == 0)
        RlistX.m[Tindex] = (unsigned char)GetNewModeR(modeArg);

    ant = LifeR[(x << 6) + y];
    do {
        if (ant > 7 && ant < 0x68) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attr);
                RlistX.s[index] = winner;
                RlistX.t[index] = (winner & 0x80) + 0x70;
                LifeR[(x << 6) + y] = (winner & 0x80) + 0x70;
                RlistX.m[index] = 0xa;
                handled = 1;
                break;
            }
        } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
            YellowFight(3, Tindex);
            handled = 1;
            break;
        }
        handled = 0;
    } while (0);
    if (handled)
        return;
    if (TryMoveDirR(x, y, attr & 7) != 0)
        return;
    TryMoveDirR(x, y, SRand8());
}

void far DoNestFightR(int x, int y) {
    unsigned char raw;
    int cellIndex;
    cellIndex = (x << 6) + y;
    raw = (RlistX.t[Tindex] & 0xf8) + SRand1(7);
    RlistX.t[Tindex] = raw;
    LifeR[cellIndex] = raw;
    if (SRand16() == 0) {
        LifeR[(x << 6) + y] = RlistX.s[Tindex]; RlistX.t[Tindex] = RlistX.s[Tindex];
        if (((RlistX.t[Tindex] & 0x78) == 0x60)) AddAntToRList((signed char)Dx8[(4 ^ (RlistX.t[Tindex] & 7))] + RlistX.x[Tindex], Dy8[(4 ^ (RlistX.t[Tindex] & 7))] + RlistX.y[Tindex], RlistX.t[Tindex] + 8, 9, 0);
        if (RlistX.t[Tindex] & 0x80) RlistX.m[Tindex] = 7;
        else RlistX.m[Tindex] = CasteModeTab[(RlistX.t[Tindex] & 0x78) >> 3];
        return;
    }
    if (OptionStates[5] != 0) FightBalloons(x, y, 3);
}

#define Dx8 ((Dx8)[0])  /* shape view of the unit declaration for this member only */
int far CheckNestFightR(int x, int y, int attacker)
{
    int ant;
    int index;
    int winner;

    ant = LifeR[(x << 6) + y];
    if (ant > 7 && ant < 0x68) {
        index = FindInRList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, (int)attacker);
            RlistX.s[index] = winner;
            RlistX.t[index] = (winner & 0x80) + 0x70;
            LifeR[(x << 6) + y] = (winner & 0x80) + 0x70;
            RlistX.m[index] = 0xa;
            return 1;
        }
    } else if (IsYellowAnt(ant) && MeColor == 0) {
        YellowFight(3, Tindex);
        return 1;
    }
    return 0;
}
#undef Dx8

void far SimEggR(int x, int y)
{
    int attr;
    int mode;
    int mask;

    attr = RlistX.t[Tindex];
    mode = -1;

    if (RpopT == 1)
        mask = 0x1f;
    else
        mask = 0x7f;
    if (!(Cycle & mask)) {
        attr++;
        if ((attr & 0xf) == 8) {
            mode = CasteTabC[((StrategicModeR % 7) << 3) + SRand8()];
            attr = (mode << 3) + 0x82;
            RlistX.m[Tindex] = (unsigned char)GetNewModeR(mode);
        }
    }

    if (OptionStates[5] != 0 && mode < 0)
        EggBalloons(x, y, 3);

    LifeR[(x << 6) + y] = (unsigned char)attr;
    RlistX.t[Tindex] = (unsigned char)attr;
    RlistX.s[Tindex] = 0;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimQueenR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C3A0 C3A2 C3A4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimQueenR(void)
{
    volatile int t;

    t = RedQueens;
    t = LastRedEgg;
    t = (int)EatCountR;
}

/* Exact-body draft: move the R queen and repair the vacated tail cell. */
#define Dx8 ((signed char far *)Dx8)
#define Dy8 ((signed char far *)Dy8)
int far QueenMoveR(int x, int y, int dirHint)
{
    int dir;
    int newRow;
    int newCol;
    int opp;
    int index;

    dir = GetBestDir(3, x, y, TileMassXR, TileMassYR);
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
    if (TryMoveDirR(x, y, dir) != 0) {
                opp = (dirHint ^ 0xfc) & 7;
                newCol = x + Dx8[opp];
                newRow = y + Dy8[opp + 8];
                LifeR[newCol * 64 + newRow] = 0;

                index = FindInRList(newCol, newRow, (dirHint & 7) + 0xe8);
                if (index >= 0 && RlistX.t[index] != 0) {
                    RlistX.x[index] = (char)x;
                    RlistX.y[index] = (char)y;
                    RlistX.t[index] = (char)(dir - 0x18);
                    LifeR[x * 64 + y] = (unsigned char)(dir - 0x18);
                }
        return 1;
    }
    return 0;
}
#undef Dx8
#undef Dy8

/* Reuse admitted KillTailR body with its original based DGROUP arrays. */
void KillTailR(int tail)
{
    unsigned char direction;
    unsigned int row;

    RlistX.t[tail] = 0;
    direction = RlistX.y[tail];
    row = *(unsigned int far *)(RlistX.x + tail);
    row &= 0xff;
    row <<= 6;
    LifeR[row + direction] = 0;
}

/* Admitted LostHeadR body; use its byte-array view for this member. */
#define LifeR ((unsigned char near *)LifeR)
int far LostHeadR(int x, int y, int attr)
{
    int dir;
    int newY;
    int headMarker;
    int newX;
    unsigned char cell;
    dir = attr & 7;
    newY = (signed char)Dy8[dir];
    newX = x + (signed char)Dx8[dir];
    newY += y;
    headMarker = attr - 8;
    cell = LifeR[(newX << 6) + newY];
    if (cell == headMarker)
        return 0;
    if (FindInRList(newX, newY, headMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeR

/* Admitted LostTailR body; use its byte-array view for this member. */
#define LifeR ((unsigned char near *)LifeR)
int far LostTailR(int x, int y, int attr)
{
    int dir;
    int newY;
    int tailMarker;
    int newX;
    unsigned char cell;

    dir = (attr ^ 0xfc) & 7;
    newY = (signed char)Dy8[dir];
    newX = x + (signed char)Dx8[dir];
    newY += y;
    tailMarker = attr + 8;
    cell = LifeR[(newX << 6) + newY];
    if (cell == tailMarker)
        return 0;
    if (FindInRList(newX, newY, tailMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeR
#define Dx8 ((signed char far *)Dx8)
#define Dy8 ((signed char far *)Dy8)
int far TryMoveDirR(int x, int y, int dir)
{
    int dy, dx, cell;

    if (dir < 0)
        return 0;

    dy = Dy8[dir] + y;
    dx = Dx8[dir] + x;
    if (dx > 0x3f)
        return 0;
    if (dx < 0)
        return 0;
    if (dy > 0x3f)
        return 0;
    if (dy < 1)
        return GetOutR(x);

    cell = dx * 64 + dy;
    if (MapR[cell] >= 0x1c)
        return 0;

    LifeR[cell] = (RlistX.t[Tindex] & 0xf8) | dir;
    LifeR[x * 64 + y] = 0;
    RlistX.x[Tindex] = LifeR[cell];
    RlistX.y[Tindex] = (unsigned char)dy;
    RlistX.t[Tindex] = LifeR[cell];
    return 1;
}
#undef Dy8
#undef Dx8


void far TryEatFoodR(int y, int x)
{
    int threshold;
    int level;

    level = MapR[x + y * 64];
    if (level < 0x10 || level > 0x13)
        return;
    if (level == 0x10)
        MapR[x + y * 64] = SRand8();
    else
        MapR[x + y * 64]--;

    if (FoodR > 0)
        FoodR--;
    threshold = (RpopT + CastePopR[2]) >> 4;
    EatCountR += 5;
    if (threshold < EatCountR) {
        EatCountR = 0;
        if (HealthR < 100)
            HealthR++;
    }
}

void far EatFoodR(int x, int y)
{
    if (MapR[x * 64 + y] == 0x10)
        MapR[x * 64 + y] = SRand8();
    else
        MapR[x * 64 + y]--;

    if (FoodR > 0)
        FoodR--;
    EatCountR += 5;
    if ((RpopT + CastePopR[2]) >> 4 < EatCountR) {
        EatCountR = 0;
        if (HealthR < 100)
            HealthR++;
    }
}

/* Admitted StealFoodR body. */
void far StealFoodR(int x, int y)
{
    if (MapR[(x << 6) + y] == 0x10)
        MapR[(x << 6) + y] = (unsigned char)SRand8();
    else
        MapR[(x << 6) + y]--;

    if (FoodR > 0)
        FoodR--;
}
void DecEatR(void)
{
    --EatCountR;
    if (EatCountR < 0) {
        EatCountR = RpopT >> 5;
        if (HealthR > 0)
            --HealthR;
    }
}

