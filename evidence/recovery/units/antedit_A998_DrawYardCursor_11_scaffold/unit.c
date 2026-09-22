/* Candidate translation unit antedit_A998_DrawYardCursor_11_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawYardCursor, _EraseYardCursor, _UpdateYardMessage, _DrawYard, _UpdateYard, _DrawDog, _DrawSimBird, _DrawForSale, _DrawAnimYardMessage, _DrawRain, _TooFar
 * SCAFFOLDED: unclaimed members _win_DrawYardWindow, _DrawYardData, _DrawSimKid, _Draw_SimYard, _DrawSwarm are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct YardPoint {
    int x;
    int y;
};
extern struct YardPoint far CurYardPnt;
extern int near patchRgn2[];
extern void far InvertPatch(int x, int y);
extern int near win_hwnd[];
extern long far editMessage;
extern long far mapMessage;
extern long far mapMessageRemoveTime;
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern long far TickCount(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, long message);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far MSClipEnd(void);
extern void far Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void far DrawYardData(void);
extern int near YardMode;
static int near yardDrawFlag = 1;
extern int near DogX;
extern int near DogY;
extern int near DogFrame;
extern int near ForSaleState;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
static int near dogObject = -1;
static char near dogRunX[4] = { 3, 0, 1, 4 };
static char near dogRunY[4] = { 4, 3, 7, 2 };
static char near dogWalkX[12] = { 1, 0, 1, 2, 0, 1, 2, 2, 2, 1, 0, 1 };
static char near dogWalkY[12] = { 0, 1, 0, 1, 2, 1, 2, 0, 0, 1, 2, 1 };
extern int near BirdX;
extern int near BirdY;
extern int near BirdFrame;
static int near birdObject = -1;
static int near forSaleObject = -1;
extern int far SRand1(int range);
static int near rainObjects[14];

extern int far newMapForce;  /* scaffold reference for pool word C1A0 (segment 10, MAPSYM_SITE_NAME) */
extern int far mapBuf;  /* scaffold reference for pool word C1A2 (segment 10, MAPSYM_SITE_NAME) */
extern int far mapYsize;  /* scaffold reference for pool word C1A4 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapXsize;  /* scaffold reference for pool word C1A6 (segment 9, MAPSYM_SITE_NAME) */
extern int far ColonyUpdateFlag;  /* scaffold reference for pool word C1A8 (segment 8, MAPSYM_SITE_NAME) */
extern int far mapForce;  /* scaffold reference for pool word C1AA (segment 10, MAPSYM_SITE_NAME) */
extern int far BlkWarnHealth;  /* scaffold reference for pool word C1B2 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWarnHealth;  /* scaffold reference for pool word C1B4 (segment 9, MAPSYM_SITE_NAME) */
extern int far GamePaused;  /* scaffold reference for pool word C1B6 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C1B8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BoyMessOn;  /* scaffold reference for pool word C1BA (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word C1BC (segment 8, MAPSYM_SITE_NAME) */
extern int far BoyMsgOffset;  /* scaffold reference for pool word C1BE (segment 9, MAPSYM_SITE_NAME) */
extern int far BoyMsgs;  /* scaffold reference for pool word C1C0 (segment 9, MAPSYM_SITE_NAME) */
extern int far yardBalloonPtr;  /* scaffold reference for pool word C1C2 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapTileRect;  /* scaffold reference for pool word C1C4 (segment 9, MAPSYM_SITE_NAME) */
extern int far bHelp;  /* scaffold reference for pool word C1C6 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far MapMode;  /* scaffold reference for pool word C1C8 (segment 8, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word C1CA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1CC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SwarmCntB;  /* scaffold reference for pool word C1CE (segment 9, MAPSYM_SITE_NAME) */
extern int far Scycle;  /* scaffold reference for pool word C1D0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C1D2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SwarmCntR;  /* scaffold reference for pool word C1D4 (segment 9, MAPSYM_SITE_NAME) */
extern int far MiscStrs;  /* scaffold reference for pool word C1D6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C1D8 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_win_DrawYardWindow(void);
void far pool_stub_DrawYardData(void);
void far pool_stub_DrawSimKid(void);
void far pool_stub_Draw_SimYard(void);
void far pool_stub_DrawSwarm(void);
void far UpdateYardMessage(void);
void DrawYard(void);
void UpdateYard(void);
void far DrawDog(void);
void far DrawSimBird(void);
void DrawForSale(void);
void far DrawAnimYardMessage(void);
void far DrawRain(void);
int TooFar(int x, int y);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawYardWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawYardData)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimKid)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_Draw_SimYard)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSwarm)
#pragma alloc_text(RUN2_TEXT, UpdateYardMessage)
#pragma alloc_text(RUN3_TEXT, DrawYard, UpdateYard)
#pragma alloc_text(RUN4_TEXT, DrawDog, DrawSimBird)
#pragma alloc_text(RUN5_TEXT, DrawForSale)
#pragma alloc_text(RUN6_TEXT, DrawAnimYardMessage)
#pragma alloc_text(RUN7_TEXT, DrawRain)
#pragma alloc_text(RUN8_TEXT, TooFar)

void DrawYardCursor(void)
{
    if (!patchRgn2[9]) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 1;
    }
}

void EraseYardCursor(void)
{
    if (patchRgn2[9]) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 0;
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_DrawYardWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1A0 C1A2 C1A4 C1A6 C1A8 C1AA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_DrawYardWindow(void)
{
    volatile int t;

    t = newMapForce;
    t = mapBuf;
    t = mapYsize;
    t = mapXsize;
    t = ColonyUpdateFlag;
    t = mapForce;
}

void far UpdateYardMessage(void)
{
    if (win_IsWinOpen(0x1900) == 0)
        return;
    if (win_hwnd[35] == 0)
        return;
    if (win_IsWinOpen(0x1900) == 0)
        return;
    MSClipStart(win_hwnd[25]);
    if (TickCount() > mapMessageRemoveTime) {
        editMessage = 0L;
        mapMessage = 0L;
        win_FillObjRect(0x1916, ConvColor(12));
    } else if (mapMessage != 0L) {
        font_SetFont(2);
        win_PrintfAtObj(0x1916, mapMessage);
        font_SetFont(0);
    } else {
        win_FillObjRect(0x1916, ConvColor(12));
    }
    MSClipEnd();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawYardData.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B2 C1B4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawYardData(void)
{
    volatile int t;

    t = BlkWarnHealth;
    t = MeWarnHealth;
}

void DrawYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardDrawFlag = 0;
    UpdateWindow(win_hwnd[25]);
    yardDrawFlag = 1;
    DrawYardData();
}

void UpdateYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardDrawFlag = 0;
    UpdateWindow(win_hwnd[25]);
    yardDrawFlag = 1;
    DrawYardData();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSimKid.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B6 C1B8 C1BA C1BC C1BE C1C0 C1C2 C1C4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSimKid(void)
{
    volatile int t;

    t = GamePaused;
    t = match_position;
    t = BoyMessOn;
    t = Dx8;
    t = BoyMsgOffset;
    t = BoyMsgs;
    t = yardBalloonPtr;
    t = mapTileRect;
}

void far DrawDog(void)
{
    int right;
    int bottom;

    right = DogX;
    bottom = DogY;
    if (ForSaleState == 0) {
        if (DogFrame < 12) {
            right += dogWalkX[DogFrame];
            bottom += dogWalkY[DogFrame];
        } else {
            right += dogRunX[DogFrame - 12];
            bottom += dogRunY[DogFrame - 12];
        }
        if (dogObject != -1) {
            hanim_SetObjectPos(right, bottom, DogFrame + 0x2134,
                               yardAnimHandle, dogObject, -1);
        } else {
            dogObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                            DogFrame + 0x2134, -1);
        }
    }
}

void far DrawSimBird(void)
{
    int right;
    int bottom;

    right = BirdX - 0xa;
    bottom = BirdY - 3;
    if (BirdFrame != 0) {
        ++right;
        bottom += 2;
    }
    if (birdObject != -1) {
        hanim_SetObjectPos(right, bottom, BirdFrame + 0x4e2,
                           yardAnimHandle, birdObject, -1);
    } else {
        birdObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                         BirdFrame + 0x4e2, -1);
    }
}

void DrawForSale(void)
{
    if (forSaleObject != -1) {
        hanim_SetObjectPos(0xaa, 0xba, 0x4ec, yardAnimHandle,
                           forSaleObject, -1);
    } else {
        forSaleObject = hanim_AddAnimObject(yardAnimHandle, 0xaa, 0xba,
                                            0x4ec, -1);
    }
}

void far DrawAnimYardMessage(void)
{
    if (win_hwnd[35] == 0)
        return;
    if (win_IsWinOpen(0x1900) == 0)
        return;
    MSClipStart(win_hwnd[25]);
    if (TickCount() > mapMessageRemoveTime) {
        editMessage = 0L;
        mapMessage = 0L;
        win_FillObjRect(0x1916, ConvColor(12));
    } else if (mapMessage != 0L) {
        font_SetFont(2);
        win_PrintfAtObj(0x1916, mapMessage);
        font_SetFont(0);
    } else {
        win_FillObjRect(0x1916, ConvColor(12));
    }
    MSClipEnd();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _Draw_SimYard.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1C6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_Draw_SimYard(void)
{
    volatile int t;

    t = bHelp;
}

void far DrawRain(void)
{
    int right;
    int bottom;
    int i;
    int near *drop;

    i = 14;
    drop = rainObjects + 14;
    while (drop--, i--) {
        right = SRand1(400) + 50;
        bottom = SRand1(150);
        if (*drop != -1)
            hanim_SetObjectPos(right, bottom, 0x1b5d, yardAnimHandle,
                               *drop, 0x8000);
        else
            *drop = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                        0x1b5d, 1000);
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSwarm.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1C8 C1CA C1CC C1CE C1D0 C1D2 C1D4 C1D6 C1D8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSwarm(void)
{
    volatile int t;

    t = MapMode;
    t = match_length;
    t = pack_buf;
    t = SwarmCntB;
    t = Scycle;
    t = EditColumns;
    t = SwarmCntR;
    t = MiscStrs;
    t = LastQueenPlane;
}

int TooFar(int x, int y)
{
    if (x > 0x0f || x < -0x0f ||
        y > 0x0f || y < -0x0f)
        return 1;
    return 0;
}

