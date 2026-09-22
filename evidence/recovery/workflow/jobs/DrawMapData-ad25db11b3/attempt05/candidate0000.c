/*
 * DrawMapData: map-window twin of the admitted (escalated) DrawYardData,
 * for window 0x2200 (clipped through win_hwnd[34]).  popMax is
 * max(1, BpopT, RpopT); redHealth is HealthR when RpopT is alive, else 0.
 * Population counts print with font 3 at objects 0x2220/0x2221, then five
 * 16.16-fraction bars (fraction = value<<16 / scale) show MeHealth/100
 * (0x2222), HealthB/100 (0x2223), BpopT/popMax (0x2225), redHealth/100
 * (0x2224) and RpopT/popMax (0x2226).  A vertical GInvBox marker is drawn
 * at the warning-threshold position (left + width*warn/100) on the
 * HealthB bar (object 0x2223, threshold BlkWarnHealth) and the MeHealth
 * bar (object 0x2222, threshold MeWarnHealth).
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
extern int far BlkWarnHealth;
extern int far MeWarnHealth;

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GInvBox(int x1, int y1, int x2, int y2);
extern void far win_DrawHBar(int objectNumber, long fraction);

void far DrawMapData(void)
{
    int popMax;
    int redHealth;
    int splitX;
    long maxPop;
    struct WinRect rect;

    popMax = 1;
    if (BpopT > popMax)
        popMax = BpopT;
    if (RpopT > popMax)
        popMax = RpopT;

    redHealth = RpopT == 0 ? 0 : HealthR;

    if (!win_IsWinOpen(0x2200))
        return;
    MSClipStart(win_hwnd[34]);

    font_SetFont(3);
    win_PrintfAtObj(0x2220, "%1d", BpopT);
    win_PrintfAtObj(0x2221, "%1d", RpopT);
    font_SetFont(0);

    win_DrawHBar(0x2222, ((long)MeHealth << 16) / 100);
    win_DrawHBar(0x2223, ((long)HealthB << 16) / 100);

    maxPop = popMax;
    win_DrawHBar(0x2225, ((long)BpopT << 16) / maxPop);
    win_DrawHBar(0x2224, ((long)redHealth << 16) / 100);
    win_DrawHBar(0x2226, ((long)RpopT << 16) / maxPop);

    win_GetObjRect(0x2223, &rect);
    splitX = rect.left + (rect.right - rect.left) * BlkWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    win_GetObjRect(0x2222, &rect);
    splitX = rect.left + (rect.right - rect.left) * MeWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    MSClipEnd();
}
