/* Candidate translation unit simant_8A76_ProcHistoryEvent_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ProcHistoryEvent, _ClearHistory
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

struct HistEvent { char reserved[12]; unsigned int message; };
struct HistLocals { volatile int v2; volatile int v1; int message; };
extern int near win_hwnd[];
extern int far editBufInvalidFlag[];
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far DoWinHelp(int mode);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern int far StillDown(void);
extern void far drawHistGraph(int value, int flag, int index);
extern void far ToggleHistButton(int message);
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


void far ClearHistory(int newGame);

#pragma alloc_text(RUN2_TEXT, ClearHistory)

void far ProcHistoryEvent(struct HistEvent far *event)
{
    struct HistLocals local; unsigned int p; int i;
    local.message=event->message;
    switch(local.message) {
    case 0x150d: DoWinHelp(0x150f); return;
    case 0x150e:
        clip_SetWin(0x1500); MSClipStart(win_hwnd[21]);
        win_FillObjRect(0x150e,ConvColor(0));
        for(i=0,p=0x2f;p<0x33;p++,i++) {
            if((local.v1=editBufInvalidFlag[p])!=(int)0x8000) drawHistGraph(editBufInvalidFlag[p],1,i);
        }
        while(StillDown()) ;
        win_FillObjRect(0x150e,ConvColor(0));
        for(i=0,p=0x2f;p<0x33;p++,i++) {
            if((local.v2=editBufInvalidFlag[p])!=(int)0x8000) drawHistGraph(editBufInvalidFlag[p],0,i);
        }
        clip_Off(); MSClipEnd(); return;
    default:
        if(event->message<0x1503) return;
        if(event->message>0x150c) return;
        ToggleHistButton(local.message);
    }
}

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

