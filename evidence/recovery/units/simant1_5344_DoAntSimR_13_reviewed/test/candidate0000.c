/* Reviewed control union: admitted simant1_5344_DoAntSimR_11 plus admitted KillTailR/GetOutR. */
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
extern int far GetExitDirR(int x, int y, int limit);
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
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



extern unsigned char far HoleMapR[];
extern int far ExitMapR[];
extern void far MakeNewHoleR(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemR(int x, int count);
extern int far GetOutR(int x);
void far pool_stub_DoNestFightR(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntR, pool_stub_DoNestFightR, pool_stub_SimQueenR)
#pragma alloc_text(RUN2_TEXT, RaidInR, StayInR, RaidOutR, DoRestR)
#pragma alloc_text(RUN3_TEXT, DoRandR)
#pragma alloc_text(RUN4_TEXT, CheckNestFightR)
#pragma alloc_text(RUN5_TEXT, SimEggR)
#pragma alloc_text(RUN8_TEXT, KillTailR)
#pragma alloc_text(RUN6_TEXT, TryEatFoodR, EatFoodR)
#pragma alloc_text(RUN7_TEXT, DecEatR)
#pragma alloc_text(RUN13_TEXT, GetOutR)
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
            LifeR[x * 64 + y] = RlistX.t[Tindex];
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

void far pool_stub_SimQueenR(void)
{
    volatile int t;

    t = RedQueens;
    t = LastRedEgg;
    t = (int)EatCountR;
}

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

void DecEatR(void)
{
    --EatCountR;
    if (EatCountR < 0) {
        EatCountR = RpopT >> 5;
        if (HealthR > 0)
            --HealthR;
    }
}

void far pool_stub_DoNestFightR(void)
{
    volatile int t;

    t = Dy8;
    t = Dx8[0];
}

int far GetOutR(int x)
{
    
    int raw;

    if (MapR[x << 6] == 0x18) {
        raw = RlistX.t[Tindex];
        RlistX.t[Tindex] = 0;
        if (HoleMapR[x] == 0)
            MakeNewHoleR(x);
        if (ExitHole(HoleMapR[x], x, SRand8() + (raw & 0xf8),
                      RlistX.m[Tindex], RlistX.s[Tindex]) != 0) {
            LifeR[(x << 6) + 1] = 0;
            return 1;
        }
        RlistX.t[Tindex] = raw;
        RlistX.m[Tindex] = 0;
        return 0;
    }

    if (ExitMapR[x << 6] != 0)
        ExitMapR[x << 6]--;

    if (SRand2() != 0) {
        if (x > 0 && IsItDirt(MapR[(x << 6) - 0x3f]) != 0)
            DigTileThemR(x - 1, 1);
    } else {
        if (x < 0x3f && IsItDirt(MapR[(x << 6) + 0x41]) != 0)
            DigTileThemR(x + 1, 1);
    }

    TryMoveDirR(x, 1, SRand8());
    return 0;
}
