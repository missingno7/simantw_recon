/*
 * ClearHistory: resets the history window's (simant:8A76) match state.
 * The public far array match_position[] (PACK) has one 64-word (0x40)
 * range zeroed first. Nine more 64-word ranges follow in PACK but (unlike
 * match_position) each needs its OWN fresh selector load with a plain,
 * fixup-free offset immediate -- the __based(__segname("PACK")) private
 * static shape used by the admitted IsMMWaveAvail/IsMMMidiAvail/
 * RecruitPoolTotal statics, one static per range (module-private rolling
 * per-stat history sample buffers; unclaimed/no public MAPSYM name).
 * When newGame == 1 the running score/colony-start/kill counters are also
 * reset (OverallScore is a far long; BColoniesStarted/RColoniesStarted
 * are reseeded to 1, BColoniesKilled/RColoniesKilled to 0). The ant/egg
 * tally longs (confirmed far long via the admitted DoNestAntB/DoDrownB/
 * GetWinner/SimEggB/SimQueenB bodies) and the HistStart/HistCnt
 * circular-buffer indices are always reset last.
 */
extern int far match_position[];

static int far histBuf1[64];
static int far histBuf2[64];
static int far histBuf3[64];
static int far histBuf4[64];
static int far histBuf5[64];
static int far histBuf6[64];
static int far histBuf7[64];
static int far histBuf8[64];
static int far histBuf9[64];

extern long far OverallScore;
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int far BColoniesKilled;
extern int far RColoniesKilled;

extern int far HistStart;
extern int far HistCnt;
extern long far BAntsEaten;
extern long far BAntsExpired;
extern long far BAntsKilled;
extern long far RAntsEaten;
extern long far RAntsExpired;
extern long far RAntsKilled;
extern long far TotalEggsLaidB;
extern long far TotalEggsDiedB;

void far ClearHistory(int newGame)
{
    int i;

    for (i = 0; i < 0x40; i++)
        match_position[0x4ef5 + i] = 0;
    for (i = 0; i < 64; i++)
        histBuf1[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf2[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf3[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf4[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf5[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf6[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf7[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf8[i] = 0;
    for (i = 0; i < 64; i++)
        histBuf9[i] = 0;

    if (newGame == 1) {
        OverallScore = 0L;
        BColoniesStarted = 1;
        RColoniesStarted = 1;
        BColoniesKilled = 0;
        RColoniesKilled = 0;
    }

    HistStart = 0x3f;
    HistCnt = 0;
    BAntsEaten = 0L;
    BAntsExpired = 0L;
    BAntsKilled = 0L;
    RAntsEaten = 0L;
    RAntsExpired = 0L;
    RAntsKilled = 0L;
    TotalEggsLaidB = 0L;
    TotalEggsDiedB = 0L;
}
