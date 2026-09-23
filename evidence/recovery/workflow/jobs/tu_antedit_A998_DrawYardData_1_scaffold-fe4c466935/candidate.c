/* Candidate translation unit antedit_A998_DrawYardData_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawYardData
 * SCAFFOLDED: unclaimed members _DrawYardCursor, _win_DrawYardWindow, _UpdateYardMessage are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GInvBox(int x1, int y1, int x2, int y2);
extern void far win_DrawHBar(int objectNumber, long fraction);

extern int far match_position;  /* scaffold reference for pool word C19E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far bHelp;  /* scaffold reference for pool word C1A0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far mapUserButton;  /* scaffold reference for pool word C1A2 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1A6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C1A8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far yardUserButton;  /* scaffold reference for pool word C1AA (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far paletteFlag;  /* scaffold reference for pool word C1AC (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far activeAppFlag;  /* scaffold reference for pool word C1AE (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far captureWnd;  /* scaffold reference for pool word C1B0 (segment 10, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DrawYardCursor(void);
void far pool_stub_win_DrawYardWindow(void);
void far pool_stub_UpdateYardMessage(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawYardCursor)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawYardWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateYardMessage)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawYardCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C19E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawYardCursor(void)
{
    volatile int t;

    t = match_position;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_DrawYardWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1A0 C1A2 C1A4 C1A6 C1A8 C1AA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_DrawYardWindow(void)
{
    volatile int t;

    t = bHelp;
    t = mapUserButton;
    t = match_length;
    t = pack_buf;
    t = Dx8;
    t = yardUserButton;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateYardMessage.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1AC C1AE C1B0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateYardMessage(void)
{
    volatile int t;

    t = paletteFlag;
    t = activeAppFlag;
    t = captureWnd;
}

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
    win_PrintfAtObj(0x231b, "%-d", BpopT);
    win_PrintfAtObj(0x231c, "%-d", RpopT);
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

    win_PrintfAtObj(0x231a, "%d", QueenStorageB < 0 ? 0 : QueenStorageB);
    win_PrintfAtObj(0x231d, "%d", ColonyTotalBlack);
    win_PrintfAtObj(0x231e, "%d", ColonyTotalRed);

    MSClipEnd();
}

