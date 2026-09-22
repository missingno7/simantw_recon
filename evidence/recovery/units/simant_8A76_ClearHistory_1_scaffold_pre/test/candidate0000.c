/* Candidate translation unit simant_8A76_ClearHistory_1_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ClearHistory
 * SCAFFOLDED: unclaimed members _ProcHistoryEvent are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far match_position[];
extern int far histBuf1[];
extern int far histBuf2[];
extern int far histBuf3[];
extern int far histBuf4[];
extern int far histBuf5[];
extern int far histBuf6[];
extern int far histBuf7[];
extern int far histBuf8[];
extern int far histBuf9[];
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

extern int far Dx8;  /* scaffold reference for pool word C084 (segment 8, MAPSYM_SITE_NAME) */

void far pool_stub_ProcHistoryEvent(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcHistoryEvent)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcHistoryEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C084; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcHistoryEvent(void)
{
    volatile int t;

    t = Dx8;
}

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

