/* Candidate translation unit simant1_0000_DoSmells_10_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoSmells, _ClrModePop, _TallyModePop, _LostHeadA, _DoDefendNest, _GoInNest, _StartFightA, _RandTurn, _IsItHole, _IsItFood
 * SCAFFOLDED: unclaimed members _DoAntSim, _FeedAnts, _DoAntSimA, _DoRandAntA are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
extern signed char far Dy8[];
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);
extern unsigned char far Dx8[];
extern void near DoToNestAnt(int ant);
extern void near DoRandAntAA(int ant);
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);
extern void far DigTileB(int x, int y);
extern void far DigTileR(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);
#define AT(off) ((&Dx8)[off])
extern int far SRand8(void);
extern char far TurnTab[8][8];
extern int far IsValidA(int x, int y);
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];

extern int far NextFeed;  /* scaffold reference for pool word C2FE (segment 8, MAPSYM_SITE_NAME) */
extern int far IsGameOver;  /* scaffold reference for pool word C308 (segment 9, MAPSYM_SITE_NAME) */
extern int far gGameNeedsSaving;  /* scaffold reference for pool word C30A (segment 8, MAPSYM_SITE_NAME) */
extern int far AlwaysHealthy;  /* scaffold reference for pool word C30E (segment 8, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word C310 (segment 9, MAPSYM_SITE_NAME) */
extern int far FoodA;  /* scaffold reference for pool word C312 (segment 9, MAPSYM_SITE_NAME) */
extern int far ListIndexA;  /* scaffold reference for pool word C314 (segment 9, MAPSYM_SITE_NAME) */
extern int far Tindex;  /* scaffold reference for pool word C316 (segment 9, MAPSYM_SITE_NAME) */
extern int __based(__segname("SIMANT_DATA_GROUP")) pool_segment_ref_SIMANT_DATA_GROUP;  /* scaffold reference for pool word C318 (based segment) */
extern int far BAntsExpired;  /* scaffold reference for pool word C31A (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C322 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C324 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C326 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SwarmCntB;  /* scaffold reference for pool word C328 (segment 9, MAPSYM_SITE_NAME) */
extern int far SwarmCntR;  /* scaffold reference for pool word C32A (segment 9, MAPSYM_SITE_NAME) */
extern int far Barrier;  /* scaffold reference for pool word C32C (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWantFood;  /* scaffold reference for pool word C330 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoAntSim(void);
void far pool_stub_FeedAnts(void);
void far pool_stub_DoAntSimA(void);
void far pool_stub_DoRandAntA(void);
int near LostHeadA(int x, int y, int life);
void near DoDefendNest(long ant);
void near GoInNest(int colour, int life, int index);
void near StartFightA(int ant, int x, int y, int nx, int ny);
int near RandTurn(int d);
int far IsItHole(int x, int y);
int IsItFood(int tile);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSim)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_FeedAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimA)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoRandAntA)
#pragma alloc_text(RUN2_TEXT, LostHeadA)
#pragma alloc_text(RUN3_TEXT, DoDefendNest)
#pragma alloc_text(RUN4_TEXT, GoInNest, StartFightA)
#pragma alloc_text(RUN5_TEXT, RandTurn)
#pragma alloc_text(RUN6_TEXT, IsItHole, IsItFood)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSim.
 * It only reproduces the object's selector-pool allocation order for the
 * words C2FE C300 C302 C304 C306 C308 C30A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSim(void)
{
    volatile int t;

    t = NextFeed;
    t = TemRModePop[0];
    t = TemBModePop[0];
    t = ModePopB[0];
    t = ModePopR[0];
    t = IsGameOver;
    t = gGameNeedsSaving;
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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _FeedAnts.
 * It only reproduces the object's selector-pool allocation order for the
 * words C30E C310 C312; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_FeedAnts(void)
{
    volatile int t;

    t = AlwaysHealthy;
    t = CurGameType;
    t = FoodA;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSimA.
 * It only reproduces the object's selector-pool allocation order for the
 * words C314 C316 C318 C31A C31C C31E C320 C322 C324 C326 C328 C32A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimA(void)
{
    volatile int t;

    t = ListIndexA;
    t = Tindex;
    t = pool_segment_ref_SIMANT_DATA_GROUP;
    t = BAntsExpired;
    t = Dy8[0];
    t = Dx8[0];
    t = (int)TERRAINset;
    t = Dx9;
    t = match_length;
    t = pack_buf;
    t = SwarmCntB;
    t = SwarmCntR;
}

#define Dx8 ((signed char far *)Dx8)  /* shape view of the unit declaration for this member only */
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

    t = Barrier;
    t = TurnTab[0][0];
    t = MeWantFood;
}

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
#undef Dx8

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

