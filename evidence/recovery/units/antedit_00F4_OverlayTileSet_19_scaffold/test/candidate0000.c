/* Candidate translation unit antedit_00F4_OverlayTileSet_19_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _OverlayTileSet, _OpenEditWindow, _MakeEditOpen, _ForceUpdateEdit, _DoEditUpdateDraw, _UpdateEditWindow, _DrawEdit, _InvalidUpdateEdit, _ed_MoveTo, _BalloonIsVisible, _EggBalloons, _FightBalloons, _QueenBalloons, _RestBalloons, _EditMsgBalloon, _PreDrawBalloons, _ResetEditScrollRange
 * SCAFFOLDED: unclaimed members _LoadTiles, _ProcEditEvent, _win_EditChanged, _ScrollEditWindow, _DrawEditGraphs, _SetEditWinTitle, _PreDrawSpider, _DrawSpider, _DrawPalps, _DrawLegs, _DrawCurBalloons, _DoEditScroll are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

static int __based(__segname("SIMANT_DATA_GROUP")) terrainSetState;
extern int far TERRAINset;
extern unsigned int far terrainTiles;
extern int far Barrier;
extern void far mem_Free(unsigned int handle);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_UnhookObject(int object, int kind);
extern void far win_Open(int flags);
extern int far win_IsWinOpen(int window);
extern void far UpdateEdit(void);
extern int near scrollBarFlag;
extern int near editForce;
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);
extern int far editBufInvalidFlag[];
extern int near edata[];
struct BalloonPoint {
    int x;
    int y;
};
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
struct MapPoint {
    int x;
    int y;
};
extern int far EggBalloonCnt;
extern struct MapPoint far MapPnt;
extern struct MapPoint far CurEggPnt;
extern int far CurEggPlane;
extern struct MapPoint far LastEggPnt;
extern int far LastEggPlane;
extern int far FightBalloonCnt;
extern struct MapPoint far CurFightPnt;
extern int far CurFightPlane;
extern struct MapPoint far LastFightPnt;
extern int far LastFightPlane;
extern int far QueenBalloonCnt;
extern struct MapPoint far CurQueenPnt;
extern int far CurQueenPlane;
extern struct MapPoint far LastQueenPnt;
extern int far LastQueenPlane;
extern int far RestBalloonCnt;
extern struct MapPoint far CurRestPnt;
extern int far CurRestPlane;
extern struct MapPoint far LastRestPnt;
extern int far LastRestPlane;
extern void far DrawCurBalloons(void);
extern int near win_hwnd[];
extern int far MapMode;
extern void far pascal SetScrollRange(int hwnd, int bar, int minPos, int maxPos, int redraw);
extern int far pascal SetScrollPos(int hwnd, int bar, int pos, int redraw);
extern int far pascal GetScrollPos(int hwnd, int bar);

extern int far match_position;  /* scaffold reference for pool word BF86 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word BF88 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far tileDsp;  /* scaffold reference for pool word BF8C (segment 9, MAPSYM_SITE_NAME) */
extern int far GamePaused;  /* scaffold reference for pool word BF8E (segment 9, MAPSYM_SITE_NAME) */
extern int far editTileRect;  /* scaffold reference for pool word BF90 (segment 9, MAPSYM_SITE_NAME) */
extern int far spiderTileLeft;  /* scaffold reference for pool word BF94 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word BF96 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dy8;  /* scaffold reference for pool word BF98 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far MeWarnHealth;  /* scaffold reference for pool word BF9A (segment 9, MAPSYM_SITE_NAME) */
extern int far BlkWarnHealth;  /* scaffold reference for pool word BF9C (segment 9, MAPSYM_SITE_NAME) */
extern int far MiscStrs;  /* scaffold reference for pool word BF9E (segment 9, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word BFA0 (segment 9, MAPSYM_SITE_NAME) */
extern int far ScenarioNameStrs;  /* scaffold reference for pool word BFA2 (segment 9, MAPSYM_SITE_NAME) */
extern int far pack_buf;  /* scaffold reference for pool word BFA4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far spiderTileTop;  /* scaffold reference for pool word BFA6 (segment 9, MAPSYM_SITE_NAME) */
extern int far SpidOn;  /* scaffold reference for pool word BFA8 (segment 9, MAPSYM_SITE_NAME) */
extern int far spiderBuf;  /* scaffold reference for pool word BFAA (segment 9, MAPSYM_SITE_NAME) */
extern int far SMode;  /* scaffold reference for pool word BFAC (segment 9, MAPSYM_SITE_NAME) */
extern int far Scycle;  /* scaffold reference for pool word BFAE (segment 9, MAPSYM_SITE_NAME) */
extern int far DBodX;  /* scaffold reference for pool word BFB0 (segment 8, MAPSYM_SITE_NAME) */
extern int far DBodY;  /* scaffold reference for pool word BFB2 (segment 8, MAPSYM_SITE_NAME) */
extern int far BodX;  /* scaffold reference for pool word BFB4 (segment 8, MAPSYM_SITE_NAME) */
extern int far BodY;  /* scaffold reference for pool word BFB6 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word BFB8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SpidBalloonTicks;  /* scaffold reference for pool word BFBA (segment 8, MAPSYM_SITE_NAME) */
extern int far WantSpiderBalloon;  /* scaffold reference for pool word BFBC (segment 9, MAPSYM_SITE_NAME) */
extern int far SpidMsgOffset;  /* scaffold reference for pool word BFBE (segment 8, MAPSYM_SITE_NAME) */
extern int far LastSMode;  /* scaffold reference for pool word BFC0 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dy9;  /* scaffold reference for pool word BFC2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SpiderMsgs;  /* scaffold reference for pool word BFC4 (segment 9, MAPSYM_SITE_NAME) */
extern int far TurnTab;  /* scaffold reference for pool word BFC6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far CurBalloonCnt;  /* scaffold reference for pool word BFC8 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurBalloonPnts;  /* scaffold reference for pool word BFCA (segment 9, MAPSYM_SITE_NAME) */
extern int far CurBalloonPlane;  /* scaffold reference for pool word BFCC (segment 9, MAPSYM_SITE_NAME) */
extern int far CurBalloonFlags;  /* scaffold reference for pool word BFCE (segment 9, MAPSYM_SITE_NAME) */
extern int far CurBalloonMsgs;  /* scaffold reference for pool word BFD0 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeSMode;  /* scaffold reference for pool word BFD2 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeMode;  /* scaffold reference for pool word BFD4 (segment 9, MAPSYM_SITE_NAME) */
extern int far PyT;  /* scaffold reference for pool word BFD6 (segment 8, MAPSYM_SITE_NAME) */
extern int far PxT;  /* scaffold reference for pool word BFD8 (segment 8, MAPSYM_SITE_NAME) */
extern int far PyT2;  /* scaffold reference for pool word BFDA (segment 8, MAPSYM_SITE_NAME) */
extern int far PxT2;  /* scaffold reference for pool word BFDC (segment 8, MAPSYM_SITE_NAME) */
extern int far PyD;  /* scaffold reference for pool word BFDE (segment 8, MAPSYM_SITE_NAME) */
extern int far PxD;  /* scaffold reference for pool word BFE0 (segment 8, MAPSYM_SITE_NAME) */
extern int far PyD2;  /* scaffold reference for pool word BFE2 (segment 8, MAPSYM_SITE_NAME) */
extern int far PxD2;  /* scaffold reference for pool word BFE4 (segment 8, MAPSYM_SITE_NAME) */
extern int far Lx;  /* scaffold reference for pool word BFE6 (segment 8, MAPSYM_SITE_NAME) */
extern int far Ly;  /* scaffold reference for pool word BFE8 (segment 8, MAPSYM_SITE_NAME) */
extern int far L1yA;  /* scaffold reference for pool word BFEA (segment 8, MAPSYM_SITE_NAME) */
extern int far L1xA;  /* scaffold reference for pool word BFEC (segment 8, MAPSYM_SITE_NAME) */
extern int far L1yB;  /* scaffold reference for pool word BFEE (segment 8, MAPSYM_SITE_NAME) */
extern int far L1xB;  /* scaffold reference for pool word BFF0 (segment 8, MAPSYM_SITE_NAME) */
extern int far L2yA;  /* scaffold reference for pool word BFF2 (segment 8, MAPSYM_SITE_NAME) */
extern int far L2xA;  /* scaffold reference for pool word BFF4 (segment 8, MAPSYM_SITE_NAME) */
extern int far L2yB;  /* scaffold reference for pool word BFF6 (segment 8, MAPSYM_SITE_NAME) */
extern int far L2xB;  /* scaffold reference for pool word BFF8 (segment 8, MAPSYM_SITE_NAME) */
extern int far L3yA;  /* scaffold reference for pool word BFFA (segment 8, MAPSYM_SITE_NAME) */
extern int far L3xA;  /* scaffold reference for pool word BFFC (segment 8, MAPSYM_SITE_NAME) */
extern int far L3yB;  /* scaffold reference for pool word BFFE (segment 8, MAPSYM_SITE_NAME) */
extern int far L3xB;  /* scaffold reference for pool word C000 (segment 8, MAPSYM_SITE_NAME) */
extern int far L4yA;  /* scaffold reference for pool word C002 (segment 8, MAPSYM_SITE_NAME) */
extern int far L4xA;  /* scaffold reference for pool word C004 (segment 8, MAPSYM_SITE_NAME) */
extern int far L4yB;  /* scaffold reference for pool word C006 (segment 8, MAPSYM_SITE_NAME) */
extern int far L4xB;  /* scaffold reference for pool word C008 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx;  /* scaffold reference for pool word C00A (segment 8, MAPSYM_SITE_NAME) */
extern int far Dy;  /* scaffold reference for pool word C00C (segment 8, MAPSYM_SITE_NAME) */
extern int far D1yA;  /* scaffold reference for pool word C00E (segment 8, MAPSYM_SITE_NAME) */
extern int far D1xA;  /* scaffold reference for pool word C010 (segment 8, MAPSYM_SITE_NAME) */
extern int far D1yB;  /* scaffold reference for pool word C012 (segment 8, MAPSYM_SITE_NAME) */
extern int far D1xB;  /* scaffold reference for pool word C014 (segment 8, MAPSYM_SITE_NAME) */
extern int far D2yA;  /* scaffold reference for pool word C016 (segment 8, MAPSYM_SITE_NAME) */
extern int far D2xA;  /* scaffold reference for pool word C018 (segment 8, MAPSYM_SITE_NAME) */
extern int far D2yB;  /* scaffold reference for pool word C01A (segment 8, MAPSYM_SITE_NAME) */
extern int far D2xB;  /* scaffold reference for pool word C01C (segment 8, MAPSYM_SITE_NAME) */
extern int far D3yA;  /* scaffold reference for pool word C01E (segment 8, MAPSYM_SITE_NAME) */
extern int far D3xA;  /* scaffold reference for pool word C020 (segment 8, MAPSYM_SITE_NAME) */
extern int far D3yB;  /* scaffold reference for pool word C022 (segment 8, MAPSYM_SITE_NAME) */
extern int far D3xB;  /* scaffold reference for pool word C024 (segment 8, MAPSYM_SITE_NAME) */
extern int far D4yA;  /* scaffold reference for pool word C026 (segment 8, MAPSYM_SITE_NAME) */
extern int far D4xA;  /* scaffold reference for pool word C028 (segment 8, MAPSYM_SITE_NAME) */
extern int far D4yB;  /* scaffold reference for pool word C02A (segment 8, MAPSYM_SITE_NAME) */
extern int far D4xB;  /* scaffold reference for pool word C02C (segment 8, MAPSYM_SITE_NAME) */
extern int far EditColumns;  /* scaffold reference for pool word C02E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C030 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C032 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word C034 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C036 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RFightBalloonTicks;  /* scaffold reference for pool word C038 (segment 9, MAPSYM_SITE_NAME) */
extern int far BFightBalloonTicks;  /* scaffold reference for pool word C03A (segment 9, MAPSYM_SITE_NAME) */
extern int far WantBFightBalloon;  /* scaffold reference for pool word C03C (segment 9, MAPSYM_SITE_NAME) */
extern int far BFightBalloonIndex;  /* scaffold reference for pool word C03E (segment 9, MAPSYM_SITE_NAME) */
extern int far BFightMsgs;  /* scaffold reference for pool word C040 (segment 9, MAPSYM_SITE_NAME) */
extern int far WantRFightBalloon;  /* scaffold reference for pool word C042 (segment 9, MAPSYM_SITE_NAME) */
extern int far RFightBalloonIndex;  /* scaffold reference for pool word C044 (segment 9, MAPSYM_SITE_NAME) */
extern int far RFightMsgs;  /* scaffold reference for pool word C046 (segment 9, MAPSYM_SITE_NAME) */
extern int far CatCycle;  /* scaffold reference for pool word C048 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word C04A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word C04C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDir;  /* scaffold reference for pool word C04E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WantRestBalloon;  /* scaffold reference for pool word C050 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EggBalloonTicks;  /* scaffold reference for pool word C052 (segment 9, MAPSYM_SITE_NAME) */
extern int far WantEggBalloon;  /* scaffold reference for pool word C054 (segment 9, MAPSYM_SITE_NAME) */
extern int far EggBalloonIndex;  /* scaffold reference for pool word C056 (segment 9, MAPSYM_SITE_NAME) */
extern int far EggMsgs;  /* scaffold reference for pool word C058 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastColonyPopB;  /* scaffold reference for pool word C05A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SpidRevenge;  /* scaffold reference for pool word C05C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TilesDugB;  /* scaffold reference for pool word C05E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far lastMapMapBuf;  /* scaffold reference for pool word C060 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexR;  /* scaffold reference for pool word C062 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far QueenBalloonTicks;  /* scaffold reference for pool word C064 (segment 9, MAPSYM_SITE_NAME) */
extern int far WantQueenBalloon;  /* scaffold reference for pool word C066 (segment 9, MAPSYM_SITE_NAME) */
extern int far QueenBalloonIndex;  /* scaffold reference for pool word C068 (segment 9, MAPSYM_SITE_NAME) */
extern int far QueenMsgs;  /* scaffold reference for pool word C06A (segment 9, MAPSYM_SITE_NAME) */
extern int far hHelpCursor;  /* scaffold reference for pool word C06C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triBoundRun;  /* scaffold reference for pool word C06E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far spiderRect;  /* scaffold reference for pool word C070 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far FoodR;  /* scaffold reference for pool word C072 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far DeathCnt;  /* scaffold reference for pool word C074 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RestBalloonTicks;  /* scaffold reference for pool word C076 (segment 9, MAPSYM_SITE_NAME) */
extern int far custIdNumStrHandle;  /* scaffold reference for pool word C078 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RestBalloonIndex;  /* scaffold reference for pool word C07A (segment 9, MAPSYM_SITE_NAME) */
extern int far RestMsgs;  /* scaffold reference for pool word C07C (segment 9, MAPSYM_SITE_NAME) */
extern int far TutLesson;  /* scaffold reference for pool word C07E (segment 8, MAPSYM_SITE_NAME) */
extern int far LessonTemp;  /* scaffold reference for pool word C080 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_LoadTiles(void);
void far pool_stub_ProcEditEvent(void);
void far pool_stub_win_EditChanged(void);
void far pool_stub_ScrollEditWindow(void);
void far pool_stub_DrawEditGraphs(void);
void far pool_stub_SetEditWinTitle(void);
void far pool_stub_PreDrawSpider(void);
void far pool_stub_DrawSpider(void);
void far pool_stub_DrawPalps(void);
void far pool_stub_DrawLegs(void);
void far pool_stub_DrawCurBalloons(void);
void far pool_stub_DoEditScroll(void);
void OpenEditWindow(void);
void MakeEditOpen(void);
void ForceUpdateEdit(void);
void DoEditUpdateDraw(void);
void UpdateEditWindow(void);
void DrawEdit(void);
void InvalidUpdateEdit(void);
void ed_MoveTo(int x, int y);
int BalloonIsVisible(int plane, int x, int y);
void far EggBalloons(int x, int y, int plane);
void far FightBalloons(int x, int y, int plane);
void far QueenBalloons(int x, int y, int plane);
void far RestBalloons(int x, int y, int plane);
void far EditMsgBalloon(int x, int y, int plane, int style, char far *msg);
void PreDrawBalloons(void);
void far ResetEditScrollRange(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_LoadTiles)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcEditEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_EditChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ScrollEditWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawEditGraphs)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetEditWinTitle)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_PreDrawSpider)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSpider)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawPalps)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawLegs)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawCurBalloons)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoEditScroll)
#pragma alloc_text(RUN2_TEXT, OpenEditWindow, MakeEditOpen, ForceUpdateEdit, DoEditUpdateDraw)
#pragma alloc_text(RUN3_TEXT, UpdateEditWindow)
#pragma alloc_text(RUN4_TEXT, DrawEdit)
#pragma alloc_text(RUN5_TEXT, InvalidUpdateEdit)
#pragma alloc_text(RUN6_TEXT, ed_MoveTo)
#pragma alloc_text(RUN7_TEXT, BalloonIsVisible, EggBalloons, FightBalloons, QueenBalloons)
#pragma alloc_text(RUN7_TEXT, RestBalloons)
#pragma alloc_text(RUN8_TEXT, EditMsgBalloon, PreDrawBalloons)
#pragma alloc_text(RUN9_TEXT, ResetEditScrollRange)

void far OverlayTileSet(int type, int id)
{
    if (type != 0)
        return;

    if (id == 0x3e9) {
        if (terrainSetState != 1) {
            terrainSetState = 1;
            TERRAINset = 1;
            if (terrainTiles != 0)
                mem_Free(terrainTiles);
            terrainTiles = db_LoadObject(9, 9, 1);
            db_UnhookObject(9, 9);
        }
        Barrier = 0x90;
    } else if (id == 0x3e8) {
        if (terrainSetState != 0) {
            terrainSetState = 0;
            TERRAINset = 0;
            if (terrainTiles != 0)
                mem_Free(terrainTiles);
            terrainTiles = db_LoadObject(10, 9, 1);
            db_UnhookObject(10, 9);
        }
        Barrier = 0x50;
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _LoadTiles.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF86 BF88 BF8A BF8C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_LoadTiles(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
    t = editBufInvalidFlag[0];
    t = tileDsp;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcEditEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF8E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcEditEvent(void)
{
    volatile int t;

    t = GamePaused;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_EditChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF90; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_EditChanged(void)
{
    volatile int t;

    t = editTileRect;
}

void OpenEditWindow(void)
{
    win_Open(0);
}

void MakeEditOpen(void)
{
    if (!win_IsWinOpen(0)) win_Open(0);
}

void ForceUpdateEdit(void)
{
    UpdateEdit();
}

void DoEditUpdateDraw(void)
{
    UpdateEdit();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ScrollEditWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF92 BF94; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ScrollEditWindow(void)
{
    volatile int t;

    t = *(int far *)&MapPnt;
    t = spiderTileLeft;
}

void UpdateEditWindow(void)
{
    UpdateEdit();
}

void DrawEdit(void) {}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawEditGraphs.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF96 BF98 BF9A BF9C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawEditGraphs(void)
{
    volatile int t;

    t = Dx8;
    t = Dy8;
    t = MeWarnHealth;
    t = BlkWarnHealth;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetEditWinTitle.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF9E BFA0 BFA2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetEditWinTitle(void)
{
    volatile int t;

    t = MiscStrs;
    t = CurGameType;
    t = ScenarioNameStrs;
}

#define editBufInvalidFlag ((editBufInvalidFlag)[0])  /* shape view of the unit declaration for this member only */
#define win_hwnd ((win_hwnd)[0])  /* shape view of the unit declaration for this member only */
void InvalidUpdateEdit(void)
{
    if (editBufInvalidFlag && !scrollBarFlag) {
        editForce = 1;
        InvalidateRect(win_hwnd, (void far *)0, 0);
    }
}
#undef editBufInvalidFlag
#undef win_hwnd

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _PreDrawSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFA4 BFA6 BFA8 BFAA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_PreDrawSpider(void)
{
    volatile int t;

    t = pack_buf;
    t = spiderTileTop;
    t = SpidOn;
    t = spiderBuf;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFAC BFAE BFB0 BFB2 BFB4 BFB6 BFB8 BFBA BFBC BFBE BFC0 BFC2 BFC4 BFC6 BFC8 BFCA BFCC BFCE BFD0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSpider(void)
{
    volatile int t;

    t = SMode;
    t = Scycle;
    t = DBodX;
    t = DBodY;
    t = BodX;
    t = BodY;
    t = Dx9;
    t = SpidBalloonTicks;
    t = WantSpiderBalloon;
    t = SpidMsgOffset;
    t = LastSMode;
    t = Dy9;
    t = SpiderMsgs;
    t = TurnTab;
    t = CurBalloonCnt;
    t = CurBalloonPnts;
    t = CurBalloonPlane;
    t = CurBalloonFlags;
    t = CurBalloonMsgs;
}

void ed_MoveTo(int x, int y)
{
    editBufInvalidFlag[-3] = x;
    edata[57] = y;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawPalps.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFD2 BFD4 BFD6 BFD8 BFDA BFDC BFDE BFE0 BFE2 BFE4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawPalps(void)
{
    volatile int t;

    t = MeSMode;
    t = MeMode;
    t = PyT;
    t = PxT;
    t = PyT2;
    t = PxT2;
    t = PyD;
    t = PxD;
    t = PyD2;
    t = PxD2;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawLegs.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFE6 BFE8 BFEA BFEC BFEE BFF0 BFF2 BFF4 BFF6 BFF8 BFFA BFFC BFFE C000 C002 C004 C006 C008 C00A C00C C00E C010 C012 C014 C016 C018 C01A C01C C01E C020 C022 C024 C026 C028 C02A C02C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawLegs(void)
{
    volatile int t;

    t = Lx;
    t = Ly;
    t = L1yA;
    t = L1xA;
    t = L1yB;
    t = L1xB;
    t = L2yA;
    t = L2xA;
    t = L2yB;
    t = L2xB;
    t = L3yA;
    t = L3xA;
    t = L3yB;
    t = L3xB;
    t = L4yA;
    t = L4xA;
    t = L4yB;
    t = L4xB;
    t = Dx;
    t = Dy;
    t = D1yA;
    t = D1xA;
    t = D1yB;
    t = D1xB;
    t = D2yA;
    t = D2xA;
    t = D2yB;
    t = D2xB;
    t = D3yA;
    t = D3xA;
    t = D3yB;
    t = D3xB;
    t = D4yA;
    t = D4xA;
    t = D4yB;
    t = D4xB;
}

#define MapPnt (*(struct BalloonPoint far *)&MapPnt)  /* shape view of the unit declaration for this member only */
int BalloonIsVisible(int plane, int x, int y)
{
    if (plane != MapPlane)
        return 0;
    if (x < MapPnt.x || x >= MapPnt.x + editWidth)
        return 0;
    if (y - 3 < MapPnt.y || y >= MapPnt.y + editHeight)
        return 0;
    return 1;
}
#undef MapPnt

void far EggBalloons(int x, int y, int plane)
{
    int visible;

    if (EggBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurEggPnt.x == x && CurEggPnt.y == y && CurEggPlane == plane) {
        EggBalloonCnt++;
        return;
    }
    LastEggPnt.x = x;
    LastEggPnt.y = y;
    LastEggPlane = plane;
}

void far FightBalloons(int x, int y, int plane)
{
    int visible;

    if (FightBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurFightPnt.x == x && CurFightPnt.y == y && CurFightPlane == plane) {
        FightBalloonCnt++;
        return;
    }
    LastFightPnt.x = x;
    LastFightPnt.y = y;
    LastFightPlane = plane;
}

void far QueenBalloons(int x, int y, int plane)
{
    int visible;

    if (QueenBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurQueenPnt.x == x && CurQueenPnt.y == y && CurQueenPlane == plane) {
        QueenBalloonCnt++;
        return;
    }
    LastQueenPnt.x = x;
    LastQueenPnt.y = y;
    LastQueenPlane = plane;
}

void far RestBalloons(int x, int y, int plane)
{
    int visible;

    if (RestBalloonCnt != 0)
        return;
    visible = MapPlane == plane && MapPnt.x <= x && x < MapPnt.x + editWidth && MapPnt.y <= y - 3 && y < MapPnt.y + editHeight;
    if (!visible)
        return;
    if (CurRestPnt.x == x && CurRestPnt.y == y && CurRestPlane == plane) {
        RestBalloonCnt++;
        return;
    }
    LastRestPnt.x = x;
    LastRestPnt.y = y;
    LastRestPlane = plane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawCurBalloons.
 * It only reproduces the object's selector-pool allocation order for the
 * words C02E C030 C032 C034 C036 C038 C03A C03C C03E C040 C042 C044 C046 C048 C04A C04C C04E C050 C052 C054 C056 C058 C05A C05C C05E C060 C062 C064 C066 C068 C06A C06C C06E C070 C072 C074 C076 C078 C07A C07C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawCurBalloons(void)
{
    volatile int t;

    t = EditColumns;
    t = EditDragPnt;
    t = modeButtonState;
    t = StoreArray;
    t = mapCursorRect;
    t = RFightBalloonTicks;
    t = BFightBalloonTicks;
    t = WantBFightBalloon;
    t = BFightBalloonIndex;
    t = BFightMsgs;
    t = WantRFightBalloon;
    t = RFightBalloonIndex;
    t = RFightMsgs;
    t = CatCycle;
    t = custNameStrHandle;
    t = ncbHead;
    t = CatDir;
    t = WantRestBalloon;
    t = EggBalloonTicks;
    t = WantEggBalloon;
    t = EggBalloonIndex;
    t = EggMsgs;
    t = LastColonyPopB;
    t = SpidRevenge;
    t = TilesDugB;
    t = lastMapMapBuf;
    t = ListIndexR;
    t = QueenBalloonTicks;
    t = WantQueenBalloon;
    t = QueenBalloonIndex;
    t = QueenMsgs;
    t = hHelpCursor;
    t = triBoundRun;
    t = spiderRect;
    t = FoodR;
    t = DeathCnt;
    t = RestBalloonTicks;
    t = custIdNumStrHandle;
    t = RestBalloonIndex;
    t = RestMsgs;
}

#define MapPnt (*(struct BalloonPoint far *)&MapPnt)  /* shape view of the unit declaration for this member only */
void far EditMsgBalloon(int x, int y, int plane, int style, char far *msg)
{
    char line1[256];
    char line2[256];
    int tileX;
    int tileY;
    int visible;

    tileX = (x >> 4) + MapPnt.x;
    tileY = (y >> 4) + MapPnt.y;
    visible = (plane == MapPlane &&
               tileX >= MapPnt.x && tileX < MapPnt.x + editWidth &&
               tileY - 3 >= MapPnt.y && tileY < MapPnt.y + editHeight);
    if (visible && msg != 0) {
        line2[0] = 0;
        line1[0] = 0;
    }
}
#undef MapPnt

void PreDrawBalloons(void)
{
    DrawCurBalloons();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoEditScroll.
 * It only reproduces the object's selector-pool allocation order for the
 * words C07E C080; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoEditScroll(void)
{
    volatile int t;

    t = TutLesson;
    t = LessonTemp;
}

static int near lastMode = -1;
static int near lastEditHeight = -1;
static int near lastEditWidth = -1;
void far ResetEditScrollRange(void)
{
    if (win_hwnd[0] == 0)
        return;

    if (MapMode != lastMode || lastEditHeight != editHeight || lastEditWidth != editWidth) {
        SetScrollRange(win_hwnd[0], 1, 0, 0x40 - editHeight, 1);
        if (MapMode != 2 && MapMode != 3)
            SetScrollRange(win_hwnd[0], 0, 0, 0x80 - editWidth, 1);
        else
            SetScrollRange(win_hwnd[0], 0, 0, 0x40 - editWidth, 1);
        lastMode = MapMode;
        lastEditHeight = editHeight;
        lastEditWidth = editWidth;
    }

    if (GetScrollPos(win_hwnd[0], 0) != MapPnt.x)
        SetScrollPos(win_hwnd[0], 0, MapPnt.x, 1);
    if (GetScrollPos(win_hwnd[0], 1) != MapPnt.y)
        SetScrollPos(win_hwnd[0], 1, MapPnt.y, 1);
}

