/* Candidate translation unit simant1_0000_ClrModePop_7_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ClrModePop, _TallyModePop, _DoDefendNest, _GoInNest, _StartFightA, _RandTurn, _IsItFood
 * SCAFFOLDED: unclaimed members _DoAntSim, _DoSmells, _FeedAnts, _DoAntSimA, _DoRandAntA are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern unsigned int far first_area[];
extern unsigned int far second_area[];
extern unsigned int far first_count;
extern unsigned int far second_count;
extern int far match_position[];
extern int far ModePopB[];
extern int far ModePopR[];
extern void far MakeRedInitiator(void);
extern unsigned char far Dx8[];
extern void near DoToNestAnt(int ant);
extern void near DoRandAntAA(int ant);
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern unsigned char near LifeA[];
extern void far CompactListB(void);
extern void far CompactListR(void);
extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);
extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);
extern void far DigTileB(int x, int y);
extern void far DigTileR(int x, int y);
extern int far FindInAList(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);
#define AT(off) ((&Dx8)[off])
extern int far SRand8(void);
extern char far TurnTab[8][8];
extern unsigned int far TERRAINset;

extern int far NextFeed;  /* scaffold reference for pool word C2FE (segment 8, MAPSYM_SITE_NAME) */
extern int far IsGameOver;  /* scaffold reference for pool word C308 (segment 9, MAPSYM_SITE_NAME) */
extern int far gGameNeedsSaving;  /* scaffold reference for pool word C30A (segment 8, MAPSYM_SITE_NAME) */
extern int far Cycle;  /* scaffold reference for pool word C30C (segment 9, MAPSYM_SITE_NAME) */
extern int far AlwaysHealthy;  /* scaffold reference for pool word C30E (segment 8, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word C310 (segment 9, MAPSYM_SITE_NAME) */
extern int far FoodA;  /* scaffold reference for pool word C312 (segment 9, MAPSYM_SITE_NAME) */
extern int far ListIndexA;  /* scaffold reference for pool word C314 (segment 9, MAPSYM_SITE_NAME) */
extern int far Tindex;  /* scaffold reference for pool word C316 (segment 9, MAPSYM_SITE_NAME) */
extern int far BAntsExpired;  /* scaffold reference for pool word C31A (segment 9, MAPSYM_SITE_NAME) */
extern int far Dy8;  /* scaffold reference for pool word C31C (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C31E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C322 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far FlyAwayR;  /* scaffold reference for pool word C324 (segment 9, MAPSYM_SITE_NAME) */
extern int far FlyAwayB;  /* scaffold reference for pool word C326 (segment 9, MAPSYM_SITE_NAME) */
extern int far SwarmCntB;  /* scaffold reference for pool word C328 (segment 9, MAPSYM_SITE_NAME) */
extern int far SwarmCntR;  /* scaffold reference for pool word C32A (segment 9, MAPSYM_SITE_NAME) */
extern int far Barrier;  /* scaffold reference for pool word C32C (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWantFood;  /* scaffold reference for pool word C330 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoAntSim(void);
void far pool_stub_DoSmells(void);
void far pool_stub_FeedAnts(void);
void far pool_stub_DoAntSimA(void);
void far pool_stub_DoRandAntA(void);
void near DoDefendNest(long ant);
void near GoInNest(int colour, int life, int index);
void near StartFightA(int ant, int x, int y, int nx, int ny);
int near RandTurn(int d);
int IsItFood(int tile);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSim)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoSmells)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_FeedAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimA)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoRandAntA)
#pragma alloc_text(RUN2_TEXT, DoDefendNest)
#pragma alloc_text(RUN3_TEXT, GoInNest, StartFightA)
#pragma alloc_text(RUN4_TEXT, RandTurn)
#pragma alloc_text(RUN5_TEXT, IsItFood)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSim.
 * It only reproduces the object's selector-pool allocation order for the
 * words C2FE C300 C302 C304 C306 C308 C30A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSim(void)
{
    volatile int t;

    t = NextFeed;
    t = match_position[0];
    t = match_position[0];
    t = ModePopB[0];
    t = ModePopR[0];
    t = IsGameOver;
    t = gGameNeedsSaving;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoSmells.
 * It only reproduces the object's selector-pool allocation order for the
 * words C30C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoSmells(void)
{
    volatile int t;

    t = Cycle;
}

void near ClrModePop(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        first_area[0x3df2 + i] = 0;

    for (i = 0; i < 20; ++i)
        second_area[0x3c35 + i] = 0;

    if (first_count != 0)
        --first_count;

    if (second_count != 0)
        --second_count;
}

void near TallyModePop(void)
{
    ModePopB[0] = match_position[0x3c37] + match_position[0x3c38];
    ModePopB[1] = match_position[0x3c39] + match_position[0x3c3a];
    ModePopB[2] = match_position[0x3c36];
    ModePopB[3] = match_position[0x3c3c];
    ModePopB[4] = match_position[0x3c41];
    ModePopB[5] = match_position[0x3c3b];

    ModePopR[0] = match_position[0x3df4] + match_position[0x3df5];
    ModePopR[1] = match_position[0x3df6] + match_position[0x3df7];
    ModePopR[2] = match_position[0x3df3];
    ModePopR[3] = match_position[0x3df9];
    ModePopR[4] = match_position[0x3dfe];
    ModePopR[5] = match_position[0x3df8];

    if (match_position[0x3e05] < 1)
        MakeRedInitiator();
}

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
    t = Dx8[0];
    t = BAntsExpired;
    t = Dy8;
    t = Dx9;
    t = (int)TERRAINset;
    t = Dy9;
    t = FlyAwayR;
    t = FlyAwayB;
    t = SwarmCntB;
    t = SwarmCntR;
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
        AddAntToBList(life, 1, (Dx8[index + 0x2f62] & 0xf8) + 4, Dx8[index + 0x2b78], Dx8[index + 0x334c]);
        if (HoleMapB[life] != 0)
            DigTileB(life, 1);
    } else {
        if (ListIndexR >= 500)
            CompactListR();
        if (ListIndexR >= 500)
            return;
        AddAntToRList(life, 1, (Dx8[index + 0x2f62] & 0xf8) + 4, Dx8[index + 0x2b78], Dx8[index + 0x334c]);
        if (HoleMapR[life] != 0)
            DigTileR(life, 1);
    }
    Dx8[index + 0x2f62] = 0;
    LifeA[(colour << 6) + life] = 0;
}

#define Dx8 ((Dx8)[0])  /* shape view of the unit declaration for this member only */
void near StartFightA(int ant, int x, int y, int nx, int ny)
{
    int loser;
    int type;
    int winner;

    type = AT(ant + 0x2f62);
    AT(ant + 0x2f62) = 0;
    LifeA[x * 64 + y] = 0;
    loser = FindInAList(nx, ny);
    if (loser >= 0) {
        winner = GetWinner(AT(loser + 0x2f62), type);
        AT(loser + 0x2f62) = (winner & 0x80) + 0x70;
        LifeA[nx * 64 + ny] = (winner & 0x80) + 0x70;
        AT(loser + 0x2b78) = 0xa;
        AT(loser + 0x334c) = winner;
        AlarmHere2(nx, ny, 0x28);
    }
}
#undef Dx8

int near RandTurn(int d) { return TurnTab[d][SRand8()]; }

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

