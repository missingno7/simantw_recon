/* Candidate translation unit simant1_0000_DoSmells_17_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoSmells, _ClrModePop, _TallyModePop, _FeedAnts, _SimEggA, _LostHeadA, _DoRepoLoit, _DoRepoFly, _DoDefendNest, _DoReturnFoodAnt, _GoInNest, _StartFightA, _GetWinner, _DoFightA, _RandTurn, _IsItHole, _IsItFood
 * SCAFFOLDED: unclaimed members _DoAntSim, _DoAntSimA, _DoRandAntA are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far Cycle;
extern void far CompactListA(void);
extern void far CompactListB(void);
extern void far CompactListR(void);
extern void far FullCount(void);
extern void far HistUpdate(void);
extern void near FillHolesBN(void);
extern void near FillHolesRN(void);
extern void near ColonySmellBN(void);
extern void near ColonySmellRN(void);
extern void near ColonySmellBT(void);
extern void near ColonySmellRT(void);
extern void near SmoothAlarm(void);
extern unsigned int far TemRModePop[];
extern unsigned int far TemBModePop[];
extern unsigned int far FlyAwayB;
extern unsigned int far FlyAwayR;
extern int far match_position[];
extern int far ModePopB[];
extern int far ModePopR[];
extern void far MakeRedInitiator(void);
extern int near HealthB;
extern int near HealthR;
extern int far AlwaysHealthy;
extern int far CurGameType;
extern int far NextFeed;
extern int far FoodA;
extern void far AddFood(int amount, int kind);
extern int far SRand1(int limit);
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern signed char far Dy8[];
extern int far FindInAList(int x, int y);
extern int far SRand2(void);
extern void near DoRandAntAA(int index);
extern void near DoToNestAnt(int index);
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern int far Tindex;
extern unsigned char near LifeA[128][64];
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int far SRand32(void);
extern int far SRand16(void);
extern void far InvalQueenStorageDisp(void);
extern unsigned char far Dx8[];
#define ANT(off) AlistT[(off) - 0x2f62]
#define DIR(off) ((&Dx8)[off])
extern char far TurnTab[8][8];
extern int far Barrier;
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];
extern int far IsValidA(int x, int y);
extern int far GetNestDir(int x, int y, int dir, int attribute);
extern int far SRand8(void);
extern void near GoInNest(int x, int y, int index);
extern void near JamScentRT(int x, int y, int scent);
extern void far JamScentBT(int x, int y, int scent);
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);
extern void far DigTileB(int x, int y);
extern void far DigTileR(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);
#define AT(off) ((&Dx8)[off])
extern int far Invincible;
extern long far RAntsKilled;
extern int far BlackLost;
extern long far BAntsKilled;
extern int far RedLost;
extern int far RRand(int range);
extern int far OptionStates[];
extern int far GetNewMode(int caste, int type);
extern void far DeadAntHere(int x, int y, int colour);
extern void far FightBalloons(int x, int y, int plane);

extern int far match_length;  /* scaffold reference for pool word C308 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C30A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexA;  /* scaffold reference for pool word C314 (segment 9, MAPSYM_SITE_NAME) */
extern int __based(__segname("SIMANT_DATA_GROUP")) pool_segment_ref_SIMANT_DATA_GROUP;  /* scaffold reference for pool word C318 (based segment) */
extern int far pack_buf;  /* scaffold reference for pool word C31A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C324 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C326 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C330 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoAntSim(void);
void far pool_stub_DoAntSimA(void);
void far pool_stub_DoRandAntA(void);
void near SimEggA(int index);
int near LostHeadA(int x, int y, int life);
void near DoRepoLoit(int index);
void near DoRepoFly(int ant);
void near DoDefendNest(long ant);
void near DoReturnFoodAnt(int index);
void near GoInNest(int colour, int life, int index);
void near StartFightA(int ant, int x, int y, int nx, int ny);
int near GetWinner(int a, int b);
void near DoFightA(int index);
int near RandTurn(int d);
int far IsItHole(int x, int y);
int IsItFood(int tile);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSim)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimA)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoRandAntA)
#pragma alloc_text(RUN2_TEXT, SimEggA)
#pragma alloc_text(RUN3_TEXT, LostHeadA)
#pragma alloc_text(RUN4_TEXT, DoRepoLoit)
#pragma alloc_text(RUN5_TEXT, DoRepoFly, DoDefendNest)
#pragma alloc_text(RUN6_TEXT, DoReturnFoodAnt)
#pragma alloc_text(RUN7_TEXT, GoInNest, StartFightA, GetWinner, DoFightA)
#pragma alloc_text(RUN8_TEXT, RandTurn)
#pragma alloc_text(RUN9_TEXT, IsItHole, IsItFood)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSim.
 * It only reproduces the object's selector-pool allocation order for the
 * words C2FE C300 C302 C304 C306 C308 C30A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSim(void)
{
    volatile int t;

    t = (int)NextFeed;
    t = TemRModePop[0];
    t = TemBModePop[0];
    t = ModePopB[0];
    t = ModePopR[0];
    t = match_length;
    t = Dx9;
}

void near DoSmells(void)
{
    switch ((Cycle & 0x60) >> 5) {
    case 0:
        CompactListA();
        FullCount();
        HistUpdate();
        SmoothAlarm();
        break;
    case 1:
        CompactListB();
        FillHolesBN();
        ColonySmellBN();
        ColonySmellBT();
        break;
    case 2:
        FullCount();
        HistUpdate();
        SmoothAlarm();
        break;
    case 3:
        CompactListR();
        FillHolesRN();
        ColonySmellRN();
        ColonySmellRT();
        break;
    }
}

void near ClrModePop(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        TemRModePop[i] = 0;

    for (i = 0; i < 20; ++i)
        TemBModePop[i] = 0;

    if (FlyAwayB != 0)
        --FlyAwayB;

    if (FlyAwayR != 0)
        --FlyAwayR;
}

#define TemBModePop ((int far *)TemBModePop)  /* shape view of the unit declaration for this member only */
#define TemRModePop ((int far *)TemRModePop)  /* shape view of the unit declaration for this member only */
void near TallyModePop(void)
{
    ModePopB[0] = TemBModePop[2] + TemBModePop[3];
    ModePopB[1] = TemBModePop[4] + TemBModePop[5];
    ModePopB[2] = TemBModePop[1];
    ModePopB[3] = TemBModePop[7];
    ModePopB[4] = TemBModePop[12];
    ModePopB[5] = TemBModePop[6];

    ModePopR[0] = TemRModePop[2] + TemRModePop[3];
    ModePopR[1] = TemRModePop[4] + TemRModePop[5];
    ModePopR[2] = TemRModePop[1];
    ModePopR[3] = TemRModePop[7];
    ModePopR[4] = TemRModePop[12];
    ModePopR[5] = TemRModePop[6];

    if (TemRModePop[19] < 1)
        MakeRedInitiator();
}
#undef TemBModePop
#undef TemRModePop

void near FeedAnts(void)
{
    if (AlwaysHealthy == 0) {
        if (--HealthB < 0)
            HealthB = 0;
    }
    if (--HealthR < 0)
        HealthR = 0;
    if (CurGameType == 3)
        return;
    if (FoodA >= NextFeed)
        return;
    AddFood(0x96, 1);
    NextFeed = SRand1(0x32) + 1;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSimA.
 * It only reproduces the object's selector-pool allocation order for the
 * words C314 C316 C318 C31A C31C C31E C320 C322 C324 C326 C328 C32A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimA(void)
{
    volatile int t;

    t = ListIndexA;
    t = (int)Tindex;
    t = pool_segment_ref_SIMANT_DATA_GROUP;
    t = pack_buf;
    t = Dy8[0];
    t = Dx8[0];
    t = (int)TERRAINset;
    t = OptionStates[0];
    t = Scycle;
    t = EditColumns;
    t = (int)SwarmCntB;
    t = (int)SwarmCntR;
}

#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
void near SimEggA(int index)
{
    int x;
    int y;
    unsigned char type;

    x = AlistX[index];
    y = AlistY[index];
    type = AlistT[index];
    LifeA[(x << 6) + y] = type;
    if (SRand1(200) == 0) {
        AlistT[index] = 0;
        LifeA[(x << 6) + y] = 0;
    }
}
#undef LifeA

#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
int near LostHeadA(int x, int y, int life)
{
    int index;
    int column;
    int row;

    index = life & 7;
    row = x + Dx8[index];
    column = y + Dy8[index];
    if (LifeA[(row << 6) + column] - life == -8)
        return 0;
    if (FindInAList(row, column) >= 0)
        return 0;
    return 1;
}
#undef Dx8
#undef LifeA

#define FlyAwayR (*(int far *)&FlyAwayR)  /* shape view of the unit declaration for this member only */
#define FlyAwayB (*(int far *)&FlyAwayB)  /* shape view of the unit declaration for this member only */
void near DoRepoLoit(int index)
{
    if (SRand2())
        DoRandAntAA(index);
    else
        DoToNestAnt(index);

    if (AlistT[index] & 0x80) {
        if (FlyAwayR > 100)
            AlistM[Tindex] = 0xf;
    } else {
        if (FlyAwayB > 100)
            AlistM[Tindex] = 0xf;
    }
}
#undef FlyAwayR
#undef FlyAwayB

void near DoRepoFly(int ant)
{
    int red;

    red = AlistT[ant] & 0x80;
    if (SRand32() == 0) {
        if ((red == 0 && SwarmCntB < 50) || (red != 0 && SwarmCntR < 50)) {
            AlistT[ant] = 0;
            LifeA[AlistX[ant] & 0xff][AlistY[ant]] = 0;
            if (CurGameType == 2) {
                if (red == 0)
                    SwarmCntB++;
                else
                    SwarmCntR++;
                if (SRand16() == 0) {
                    if (red == 0) {
                        QueenStorageB++;
                        InvalQueenStorageDisp();
                    } else
                        QueenStorageR++;
                }
            }
        }
    }
}

void near DoDefendNest(long ant)
{
    int scent;

    if (Dx8[(int)ant + 0x2f62] & 0x80)
        scent = Dx8[((Dx8[(int)ant + 0x23a4] & 0xfe) << 4) +
                    (Dx8[(int)ant + 0x278e] >> 1) + 0x72d2];
    else
        scent = Dx8[((Dx8[(int)ant + 0x23a4] & 0xfe) << 4) +
                    (Dx8[(int)ant + 0x278e] >> 1) + 0x62d2];
    if (scent < 0x6e)
        DoToNestAnt((int)ant);
    else
        DoRandAntAA((int)ant);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoRandAntA.
 * It only reproduces the object's selector-pool allocation order for the
 * words C32C C32E C330; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoRandAntA(void)
{
    volatile int t;

    t = (int)Barrier;
    t = TurnTab[0][0];
    t = MiscStrs;
}

#define Dx8 ((Dx8)[0])  /* shape view of the unit declaration for this member only */
#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
void near DoReturnFoodAnt(int index)
{
    int x, y;
    int hole;
    int flags;
    int tile;
    int attribute;
    int ndir;
    int nx, ny;

    x = ANT(index + 0x23a4) & 0xff;
    y = ANT(index + 0x278e);
    attribute = ANT(index + 0x2f62);

    if (!IsValidA(x, y)) {
        hole = 0;
    } else if (TERRAINset == 0) {
        if (MapA[x * 64 + y] == 0x50)
            hole = 1;
        else
            hole = 0;
    } else {
        tile = MapA[x * 64 + y];
        if (tile < 0x80)
            hole = 0;
        else if (tile > 0x8f)
            hole = 0;
        else
            hole = 1;
    }

    if (hole) {
        GoInNest(x, y, index);
        return;
    }

    flags = attribute & 0xf8;
    ndir = GetNestDir(x, y, attribute & 7, attribute);
    nx = x + (signed char)DIR(ndir);
    ny = y + Dy8[ndir];

    if (MapA[(nx << 6) + ny] > Barrier) {
        ANT(index + 0x2f62) = TurnTab[attribute & 7][SRand8()] | flags;
        LifeA[(x << 6) + y] = ANT(index + 0x2f62);
        return;
    }

    LifeA[(nx << 6) + ny] = ndir | flags;
    ANT(index + 0x2f62) = ndir | flags;
    LifeA[(x << 6) + y] = 0;
    ANT(index + 0x23a4) = nx;
    ANT(index + 0x278e) = ny;

    if (ANT(index + 0x334c) != 0) {
        ANT(index + 0x334c)--;
        if (attribute & 0x80)
            JamScentRT(nx, ny, ANT(index + 0x334c));
        else
            JamScentBT(nx, ny, ANT(index + 0x334c));
    }
}
#undef Dx8
#undef LifeA

#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
void near GoInNest(int colour, int life, int index)
{
    if (colour < 0x40) {
        if (ListIndexB >= 500)
            CompactListB();
        if (ListIndexB >= 500)
            return;
        AddAntToBList(life, 1, (AlistT[index] & 0xf8) + 4, AlistM[index], AlistS[index]);
        if (HoleMapB[life] != 0)
            DigTileB(life, 1);
    } else {
        if (ListIndexR >= 500)
            CompactListR();
        if (ListIndexR >= 500)
            return;
        AddAntToRList(life, 1, (AlistT[index] & 0xf8) + 4, AlistM[index], AlistS[index]);
        if (HoleMapR[life] != 0)
            DigTileR(life, 1);
    }
    AlistT[index] = 0;
    LifeA[(colour << 6) + life] = 0;
}
#undef LifeA

#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
#define Dx8 ((Dx8)[0])  /* shape view of the unit declaration for this member only */
void near StartFightA(int ant, int x, int y, int nx, int ny)
{
    int loser;
    int type;
    int winner;

    type = AlistT[ant];
    AlistT[ant] = 0;
    LifeA[x * 64 + y] = 0;
    loser = FindInAList(nx, ny);
    if (loser >= 0) {
        winner = GetWinner(AlistT[loser], type);
        AlistT[loser] = (winner & 0x80) + 0x70;
        LifeA[nx * 64 + ny] = (winner & 0x80) + 0x70;
        AlistM[loser] = 0xa;
        AlistS[loser] = winner;
        AlarmHere2(nx, ny, 0x28);
    }
}
#undef LifeA
#undef Dx8

static unsigned char near combatLevel[16] = {
    0, 0, 0, 0, 2, 0, 1, 1, 2, 1, 0, 0, 3, 3, 0, 0
};
static unsigned char near combatOdds[16] = {
    5, 2, 7, 3, 8, 5, 9, 4, 3, 1, 5, 2, 7, 6, 8, 5
};
int near GetWinner(int a, int b)
{
    int levelA;
    int levelB;
    int threshold;

    if (Invincible == 1) {
        RAntsKilled++;
        if (a & 0x80)
            return b;
        return a;
    }

    levelA = combatLevel[(a & 0x78) >> 3];
    levelB = combatLevel[(b & 0x78) >> 3];
    threshold = combatOdds[(levelA << 2) + levelB];

    if (RRand(10) < threshold) {
        if (a & 0x80) {
            BlackLost++;
            BAntsKilled++;
        } else {
            RedLost++;
            RAntsKilled++;
        }
        return a;
    }

    if (b & 0x80) {
        BlackLost++;
        BAntsKilled++;
    } else {
        RedLost++;
        RAntsKilled++;
    }
    return b;
}

#define LifeA ((unsigned char near *)LifeA)  /* shape view of the unit declaration for this member only */
void near DoFightA(int index)
{
    int x;
    int y;

    x = AlistX[index];
    y = AlistY[index];
    AlistT[index] = (AlistT[index] & 0xf8) + SRand1(7);
    LifeA[(x << 6) + y] = AlistT[index];
    if (SRand16() == 0) {
        LifeA[(x << 6) + y] = AlistS[index];
        AlistT[index] = LifeA[(x << 6) + y];
        AlistM[Tindex] = GetNewMode((AlistT[index] & 0x78) >> 3, AlistT[index]);
        AlistS[index] = 0;
        DeadAntHere(x, y, AlistT[index] & 0x80);
    } else if (OptionStates[5] == 1)
        FightBalloons(x, y, 1);
}
#undef LifeA

int near RandTurn(int d) { return TurnTab[d][SRand8()]; }

int far IsItHole(int x, int y)
{
    int tile;

    if (IsValidA(x, y) == 0)
        return 0;
    if (TERRAINset == 0) {
        if (MapA[(x << 6) + y] == 0x50)
            return 1;
        return 0;
    }
    tile = MapA[(x << 6) + y];
    if (tile < 0x80)
        return 0;
    if (tile > 0x8f)
        return 0;
    return 1;
}

int IsItFood(int tile)
{
    if (TERRAINset == 0) {
        if (tile < 0x48 || tile > 0x4b)
            return 0;
        return 1;
    }
    if (tile < 0x18 || tile > 0x27)
        return 0;
    return 1;
}

