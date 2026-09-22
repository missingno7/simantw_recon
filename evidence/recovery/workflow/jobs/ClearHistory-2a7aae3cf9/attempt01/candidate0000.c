/*
 * ClearHistory: resets the history window's (simant:8A76) match state.
 * Ten 64-word (0x40) ranges of the shared far scratch array match_position
 * are zeroed first (rolling per-stat history sample buffers; each range
 * reloads its own selector even though every range lives in the same
 * segment as match_position, matching this unit's per-statement far
 * access style). When newGame == 1 the running score/colony-start/kill
 * counters are also reset (OverallScore is a far long; BColoniesStarted/
 * RColoniesStarted are reseeded to 1, BColoniesKilled/RColoniesKilled to
 * 0). The ant/egg tally longs (confirmed far long via the admitted
 * DoNestAntB/DoDrownB/GetWinner/SimEggB/SimQueenB bodies) and the
 * HistStart/HistCnt circular-buffer indices are always reset last.
 */
extern int far match_position[];

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
    for (i = 0; i < 0x40; i++)
        match_position[0x4f56 + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x4e79 + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x39c1 + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x4ff8 + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x4f98 + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x3ebb + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x3e4c + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x3b04 + i] = 0;
    for (i = 0; i < 0x40; i++)
        match_position[0x397d + i] = 0;

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
