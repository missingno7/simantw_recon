/* Candidate translation unit simant1_5344_DoAntSimR_16_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoAntSimR, _RaidInR, _StayInR, _RaidOutR, _DoRestR, _DoRandR, _CheckNestFightR, _SimEggR, _QueenMoveR, _MakeNewTailR, _LostHeadR, _LostTailR, _TryEatFoodR, _EatFoodR, _DecEatR, _GetOutR
 * SCAFFOLDED: unclaimed members _DoNestAntR, _DoNestFightR, _SimQueenR are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
extern int far ListIndexR;
extern int far Tindex;
extern void far DoNestAntR(int life, int column, int attribute);
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far FoodR;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far GetEnterDirR(int x, int y, int dir);
extern int far TryMoveDirR(int x, int y, int dir);
extern int far GetExitDirR(int x, int y, int limit);
extern int near MeColor;
extern int far OptionStates[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far GetNewMode(int caste, int type);
extern void far RestBalloons(int x, int y, int plane);
extern int far SRand32(void);
extern int far GetNewModeR(int mode);
extern int far Cycle;
extern int far StrategicModeR;
extern char far CasteTabC[];
extern void far EggBalloons(int x, int y, int plane);
extern int far TileMassXR;
extern int far TileMassYR;
extern char far Dy8[];
extern char far Dx8[];
extern int far GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern void far AddAntToRList(int,int,int,int,int);
extern int far EatCountR;
extern int near CastePopR[];
extern int near RpopT;
extern int near HealthR;
extern unsigned char far HoleMapR[];
extern unsigned char far ExitMapR[];
extern void far MakeNewHoleR(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemR(int x, int count);

extern int far match_position;  /* scaffold reference for pool word C388 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C38A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C38E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C390 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C392 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C3A0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C3A2 (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoNestAntR(void);
void far pool_stub_DoNestFightR(void);
void far pool_stub_SimQueenR(void);
void far RaidInR(int x, int y, int dirHint);
void far StayInR(int x, int y, int dirHint);
void far RaidOutR(int x, int y);
void far DoRestR(int x, int y, int attacker);
void far DoRandR(int x, int y, int attr, int modeArg);
int far CheckNestFightR(int x, int y, int attacker);
void far SimEggR(int x, int y);
int far QueenMoveR(int x, int y, int dirHint);
void far MakeNewTailR(int index);
int far LostHeadR(int x, int y, int attr);
int far LostTailR(int x, int y, int attr);
void far TryEatFoodR(int y, int x);
void far EatFoodR(int x, int y);
void DecEatR(void);
int far GetOutR(int x);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestFightR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimQueenR)
#pragma alloc_text(RUN2_TEXT, RaidInR, StayInR, RaidOutR, DoRestR)
#pragma alloc_text(RUN3_TEXT, DoRandR)
#pragma alloc_text(RUN4_TEXT, CheckNestFightR)
#pragma alloc_text(RUN5_TEXT, SimEggR)
#pragma alloc_text(RUN6_TEXT, QueenMoveR, MakeNewTailR)
#pragma alloc_text(RUN7_TEXT, LostHeadR, LostTailR)
#pragma alloc_text(RUN8_TEXT, TryEatFoodR, EatFoodR)
#pragma alloc_text(RUN9_TEXT, DecEatR)
#pragma alloc_text(RUN10_TEXT, GetOutR)

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

    t = *(int far *)&RlistX;
    t = match_position;
    t = match_length;
    t = OptionStates[0];
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestFightR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C396 C398; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestFightR(void)
{
    volatile int t;

    t = Dy8[0];
    t = Dx8[0];
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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimQueenR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C3A0 C3A2 C3A4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimQueenR(void)
{
    volatile int t;

    t = MiscStrs;
    t = Dx9;
    t = (int)EatCountR;
}

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
                newRow = y + Dy8[opp];
                LifeR[newCol * 64 + newRow] = 0;

                index = FindInRList(newCol, newRow, (dirHint & 7) + 0xe8);
                if (index >= 0 && Dx8[index + 0x46e6] != 0) {
                    Dx8[index + 0x4104] = (char)x;
                    Dx8[index + 0x42fa] = (char)y;
                    Dx8[index + 0x46e6] = (char)(dir - 0x18);
                    LifeR[x * 64 + y] = (unsigned char)(dir - 0x18);
                }
        return 1;
    }
    return 0;
}

#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
#define Dy8 ((signed char far *)Dy8)  /* shape view of the unit declaration for this member only */
void far MakeNewTailR(int index){
    unsigned char type;
    int direction;
    int life;
    int column;

    type = RlistX.t[index];
    direction = type & 7;
    direction ^= 4;
    life = RlistX.x[index] + (signed char)Dx8[direction];
    column = RlistX.y[index] + (signed char)Dy8[direction];
    AddAntToRList(life, column, type + 8, 9, 0);
}
#undef Dx8
#undef Dy8

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
    cell = ((unsigned char near *)LifeR)[(newX << 6) + newY];
    if (cell == headMarker)
        return 0;
    if (FindInRList(newX, newY, headMarker) >= 0)
        return 0;
    return 1;
}

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
    cell = ((unsigned char near *)LifeR)[(newX << 6) + newY];
    if (cell == tailMarker)
        return 0;
    if (FindInRList(newX, newY, tailMarker) >= 0)
        return 0;
    return 1;
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

