/*
 * HistUpdate: append values from the exact MAPSYM counters and PACK
 * history arrays observed by the target at index HistStart, then advance
 * HistStart modulo 0x40 and clamp HistCnt. The target's indexed stores
 * resolve directly to H_BPop, H_RPop, H_BFood, H_RFood, H_BHeal,
 * H_RHeal, H_FoodA, H_ADead, H_PDead, and H_FDead. If the history window
 * (0x1500) is open,
 * it redraws the current colony-population graph (same Dx8[0x8e54..
 * 0x8e5c) 4-colony loop, flag 0, as ProcHistoryEvent's case 0x150e second
 * half) inside a clip guard.
 */
extern int near BpopT;
extern int near RpopT;
extern int near HealthB;
extern int near HealthR;

extern int far H_BPop[];
extern int far H_RPop[];
extern int far H_BFood[];
extern int far H_RFood[];
extern int far H_BHeal[];
extern int far H_RHeal[];
extern int far H_FoodA[];
extern int far H_ADead[];
extern int far H_PDead[];
extern int far H_FDead[];

extern int far FoodB;
extern int far FoodR;
extern int far FoodA;
extern long far BAntsEaten;
extern long far BAntsExpired;
extern long far BAntsKilled;

extern int far HistStart;
extern int far HistCnt;

extern int far editBufInvalidFlag[];
extern int near win_hwnd[];

extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far MSClipStart(int window);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far drawHistGraph(int value, int flag, int index);
extern void far MSClipEnd(void);
extern void far clip_Off(void);

/* 12: loop_index_expr */
void far HistUpdate(void)
{
    int hs;
    unsigned int p;
    int i;
    int v;

    hs = HistStart;

    H_BPop[hs] = BpopT;
    H_RPop[hs] = RpopT;
    H_BFood[hs] = FoodB;
    H_RFood[hs] = FoodR;
    H_BHeal[hs] = HealthB;
    H_RHeal[hs] = HealthR;
    H_FoodA[hs] = FoodA;
    H_ADead[hs] = (int)BAntsExpired;
    H_PDead[hs] = (int)BAntsEaten;
    H_FDead[hs] = (int)BAntsKilled;

    if (HistCnt < 0x3f)
        HistCnt++;
    HistStart = (HistStart + 1) & 0x3f;

    if (win_IsWinOpen(0x1500)) {
        clip_SetWin(0x1500);
        MSClipStart(win_hwnd[21]);
        win_FillObjRect(0x150e, ConvColor(0));
        for (i = 0, p = 0x2f; i < 4; ++i, p = 0x2f + (i << 1) ) {
            v = editBufInvalidFlag[p];
            if (v != (int)0x8000)
                drawHistGraph(v, 0, i);
        }
        MSClipEnd();
        clip_Off();
    }
}
