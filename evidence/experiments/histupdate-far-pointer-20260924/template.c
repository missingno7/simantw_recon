/*
 * HistUpdate: appends one sample to each of the history window's
 * (simant:8A76) 10 rolling per-stat circular buffers at index HistStart
 * (PACK, 0x9e6e, 0..0x3f), then advances HistStart (wrapped mod 0x40) and
 * HistCnt (clamped at 0x3f). The 10 buffers are the same PACK ranges
 * ClearHistory zeroes (word bases 0x4ef5 match_position/0x4f56/0x4e79/
 * 0x39c1/0x4ff8/0x4f98/0x3ebb/0x3e4c/0x3b04/0x397d); here each is
 * evidenced by name: BAntsKilled, BAntsEaten, BAntsExpired, an unnamed
 * scalar (u1), HealthR, HealthB, an unnamed scalar (u2), an unnamed
 * scalar (u3), RpopT, BpopT (near DGROUP ints per admitted BpopT/RpopT/
 * HealthB/HealthR declarations). If the history window (0x1500) is open,
 * it redraws the current colony-population graph (same Dx8[0x8e54..
 * 0x8e5c) 4-colony loop, flag 0, as ProcHistoryEvent's case 0x150e second
 * half) inside a clip guard.
 */
extern int near BpopT;
extern int near RpopT;
extern int near HealthB;
extern int near HealthR;

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

extern long far BAntsEaten;
extern long far BAntsExpired;
extern long far BAntsKilled;
extern int far u1;
extern int far u2;
extern int far u3;

extern int far HistStart;
extern int far HistCnt;

extern unsigned char far Dx8[];
extern int near win_hwnd[];

extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far MSClipStart(int window);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far drawHistGraph(int value, int flag, int index);
extern void far MSClipEnd(void);
extern void far clip_Off(void);

void far HistUpdate(void)
{
    int hs;
@PTR_DECL@
    int i;
    int v;

    hs = HistStart;

    H_BPop[hs] = BpopT;
    H_RPop[hs] = RpopT;
    H_BFood[hs] = u3;
    H_RFood[hs] = u2;
    H_BHeal[hs] = HealthB;
    H_RHeal[hs] = HealthR;
    H_FoodA[hs] = u1;
    H_ADead[hs] = (int)BAntsExpired;
    H_PDead[hs] = (int)BAntsEaten;
    match_position[hs] = (int)BAntsKilled;

    if (HistCnt < 0x3f)
        HistCnt++;
    HistStart = (HistStart + 1) & 0x3f;

    if (win_IsWinOpen(0x1500)) {
        clip_SetWin(0x1500);
        MSClipStart(win_hwnd[21]);
        win_FillObjRect(0x150e, ConvColor(0));
        for (i = 0, p = (int far *)(Dx8 + 0x8e54);
             p < (int far *)(Dx8 + 0x8e5c); p++, i++) {
            v = *p;
            if (v != (int)0x8000)
                drawHistGraph(v, 0, i);
        }
        MSClipEnd();
        clip_Off();
    }
}
