/*
 * ClearHistory: resets the history window's (simant:8A76) match state.
 * The public far array match_position[] (PACK) has one 64-word (0x40)
 * range zeroed first. Nine further 64-word arrays are the MAPSYM history series written by
 * HistUpdate: H_PDead/H_ADead/H_FoodA/H_RHeal/H_BHeal/H_RFood/H_BFood/
 * H_RPop/H_BPop at the exact PACK offsets seen in that member's packet.
 * Keep each far array separate so C7 emits the target's fresh selector
 * load for each series.
 * When newGame == 1 the running score/colony-start/kill counters are also
 * reset (OverallScore is a far long; BColoniesStarted/RColoniesStarted
 * are reseeded to 1, BColoniesKilled/RColoniesKilled to 0). The ant/egg
 * tally longs (confirmed far long via the admitted DoNestAntB/DoDrownB/
 * GetWinner/SimEggB/SimQueenB bodies) and the HistStart/HistCnt
 * circular-buffer indices are always reset last.
 */
extern int far match_position[];

extern int far H_PDead[];
extern int far H_ADead[];
extern int far H_FoodA[];
extern int far H_RHeal[];
extern int far H_BHeal[];
extern int far H_RFood[];
extern int far H_BFood[];
extern int far H_RPop[];
extern int far H_BPop[];

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
        H_PDead[i] = 0;
    for (i = 0; i < 64; i++)
        H_ADead[i] = 0;
    for (i = 0; i < 64; i++)
        H_FoodA[i] = 0;
    for (i = 0; i < 64; i++)
        H_RHeal[i] = 0;
    for (i = 0; i < 64; i++)
        H_BHeal[i] = 0;
    for (i = 0; i < 64; i++)
        H_RFood[i] = 0;
    for (i = 0; i < 64; i++)
        H_BFood[i] = 0;
    for (i = 0; i < 64; i++)
        H_RPop[i] = 0;
    for (i = 0; i < 64; i++)
        H_BPop[i] = 0;

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
