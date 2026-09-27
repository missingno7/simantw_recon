/*
 * DrawYardData: refresh the numeric readouts and health/population bars in
 * the yard status window (window 0x2300), clipped through win_hwnd[35].
 * popMax is max(1, BpopT, RpopT); redHealth is HealthR when RpopT is alive,
 * else 0.  Population counts print with font 3, then five 16.16-fraction
 * bars (fraction = value<<16 / scale) show MeHealth/100, HealthB/100,
 * BpopT/popMax, redHealth/100 and RpopT/popMax.  A vertical GInvBox marker
 * is drawn at the warning-threshold position (left + width*warn/100) on
 * the HealthB bar (object 0x2320, threshold BlkWarnHealth) and the
 * MeHealth bar (object 0x231f, threshold MeWarnHealth); both thresholds
 * are far words in the PACK data segment (same segment as mapTileRect).
 * QueenStorageB prints floored at 0; colony totals print plain.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near win_hwnd[];
extern int near BpopT;
extern int near RpopT;
extern int near HealthB;
extern int near HealthR;
extern int near MeHealth;
extern int near QueenStorageB;
extern int near ColonyTotalBlack;
extern int near ColonyTotalRed;
extern int far BlkWarnHealth;
extern int far MeWarnHealth;

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, long message);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GInvBox(int x1, int y1, int x2, int y2);
extern void far win_DrawHBar(int objectNumber, long fraction);

void far DrawYardData(void)
{
    int popMax;
    int redHealth;
    int splitX;
    long maxPop;
    struct WinRect rect;

    if (!win_IsWinOpen(0x2300))
        return;
    MSClipStart(win_hwnd[35]);

    popMax = 1;
    if (BpopT > popMax)
        popMax = BpopT;
    if (RpopT > popMax)
        popMax = RpopT;

    redHealth = RpopT == 0 ? 0 : HealthR;

    font_SetFont(3);
    win_PrintfAtObj(0x231b, "%3d", BpopT);
    win_PrintfAtObj(0x231c, "%3d", RpopT);
    font_SetFont(0);

    win_DrawHBar(0x231f, ((long)MeHealth << 16) / 100);
    win_DrawHBar(0x2320, ((long)HealthB << 16) / 100);

    maxPop = popMax;
    win_DrawHBar(0x2322, ((long)BpopT << 16) / maxPop);
    win_DrawHBar(0x2321, ((long)redHealth << 16) / 100);
    win_DrawHBar(0x2323, ((long)RpopT << 16) / maxPop);

    win_GetObjRect(0x2320, &rect);
    splitX = rect.left + (rect.right - rect.left) * BlkWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    win_GetObjRect(0x231f, &rect);
    splitX = rect.left + (rect.right - rect.left) * MeWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    win_PrintfAtObj(0x231a, "%3d", QueenStorageB < 0 ? 0 : QueenStorageB);
    win_PrintfAtObj(0x231d, "%d", ColonyTotalBlack);
    win_PrintfAtObj(0x231e, "%d", ColonyTotalRed);

    MSClipEnd();
}
