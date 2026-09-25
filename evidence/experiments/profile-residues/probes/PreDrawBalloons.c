/* Candidate translation unit antedit_00F4_OverlayTileSet_19_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _OverlayTileSet, _ProcEditEvent, _OpenEditWindow, _MakeEditOpen, _ForceUpdateEdit, _DoEditUpdateDraw, _UpdateEditWindow, _DrawEdit, _InvalidUpdateEdit, _PreDrawSpider, _ed_MoveTo, _BalloonIsVisible, _EggBalloons, _FightBalloons, _QueenBalloons, _RestBalloons, _EditMsgBalloon, _PreDrawBalloons, _ResetEditScrollRange
 * SCAFFOLDED: unclaimed members _LoadTiles, _win_EditChanged, _ScrollEditWindow, _DrawEditGraphs, _SetEditWinTitle, _DrawSpider, _DrawPalps, _DrawLegs, _DrawCurBalloons, _DoEditScroll are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

static int __based(__segname("SIMANT_DATA_GROUP")) terrainSetState;
extern int far TERRAINset;
extern unsigned int far terrainTiles;
extern int far Barrier;
extern void far mem_Free(unsigned int handle);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_UnhookObject(int object, int kind);
struct EditEvent {
    char reserved[12];
    int message;
};
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far processEdit(struct EditEvent far *event);
extern void far DoWinHelp(int mode);
extern void far EditToolsMenu(void);
extern void far SetMapPlane(int plane);
extern void far GotoMyAnt(void);
extern void far GotoSpider(void);
extern void far GotoBQueen(void);
extern void far GotoRQueen(void);
extern int far GamePaused;
extern void far SetPause(int pause);
extern void far EditScentMenu(void);
extern void far DoHealthSetY(struct EditEvent far *event, int mode);
extern void far DoWarnSetB(struct EditEvent far *event, int mode);
extern void far win_Open(int flags);
extern int far win_IsWinOpen(int window);
extern void far UpdateEdit(void);
extern int near scrollBarFlag;
extern int near editForce;
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);
struct Rect { int left, top, right, bottom; };
extern struct Rect far spiderRect;
extern int far spiderTileLeft;
extern int far spiderTileTop;
extern int far SpidOn;
struct MapPoint { int x, y; };
extern struct MapPoint far spiderBuf;
extern int near editWidth;
extern int near editHeight;
extern struct MapPoint far MapPnt;
extern int near tileWidth;
extern int near tileHeight;
extern int near SpidX;
extern int near SpidY;
extern unsigned char near displayType;
extern int near MapPlane;
extern int far editBufInvalidFlag[];
extern int near win_hwnd[];
extern int near edata[];
struct BalloonPoint {
    int x;
    int y;
};
extern int far EggBalloonCnt;
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
extern int far MapMode;
extern void far pascal SetScrollRange(int hwnd, int bar, int minPos, int maxPos, int redraw);
extern int far pascal SetScrollPos(int hwnd, int bar, int pos, int redraw);
extern int far pascal GetScrollPos(int hwnd, int bar);

extern int far match_position;  /* scaffold reference for pool word BF86 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word BF88 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word BF8C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word BF90 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word BF96 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word BF98 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word BF9A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word BF9C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word BF9E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word BFA0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word BFA2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word BFAC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word BFAE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word BFB0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word BFB2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TurnTab;  /* scaffold reference for pool word BFB4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word BFB6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far absSearchDirs;  /* scaffold reference for pool word BFB8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far IsCarryCaste;  /* scaffold reference for pool word BFBA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word BFBC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far UnCarryCaste;  /* scaffold reference for pool word BFBE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word BFC0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YMapPopB;  /* scaffold reference for pool word BFC2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word BFC4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YMapPopR;  /* scaffold reference for pool word BFC6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far CatDir;  /* scaffold reference for pool word BFC8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WantRestBalloon;  /* scaffold reference for pool word BFCA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastColonyPopB;  /* scaffold reference for pool word BFCC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SpidRevenge;  /* scaffold reference for pool word BFCE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TilesDugB;  /* scaffold reference for pool word BFD0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far lastMapMapBuf;  /* scaffold reference for pool word BFD2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexR;  /* scaffold reference for pool word BFD4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YMapSeeds;  /* scaffold reference for pool word BFD6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ExitMapB;  /* scaffold reference for pool word BFD8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ExitMapR;  /* scaffold reference for pool word BFDA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistX;  /* scaffold reference for pool word BFDC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistY;  /* scaffold reference for pool word BFDE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistM;  /* scaffold reference for pool word BFE0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistT;  /* scaffold reference for pool word BFE2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistS;  /* scaffold reference for pool word BFE4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistX;  /* scaffold reference for pool word BFE6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistY;  /* scaffold reference for pool word BFE8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistM;  /* scaffold reference for pool word BFEA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistT;  /* scaffold reference for pool word BFEC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistS;  /* scaffold reference for pool word BFEE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistX;  /* scaffold reference for pool word BFF0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistY;  /* scaffold reference for pool word BFF2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistM;  /* scaffold reference for pool word BFF4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistT;  /* scaffold reference for pool word BFF6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistS;  /* scaffold reference for pool word BFF8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TemDensity;  /* scaffold reference for pool word BFFA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapA;  /* scaffold reference for pool word BFFC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapF;  /* scaffold reference for pool word BFFE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapBN;  /* scaffold reference for pool word C000 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapBT;  /* scaffold reference for pool word C002 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapRN;  /* scaffold reference for pool word C004 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapRT;  /* scaffold reference for pool word C006 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far HoleMapB;  /* scaffold reference for pool word C008 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far HoleMapR;  /* scaffold reference for pool word C00A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewExitB;  /* scaffold reference for pool word C00C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewExitR;  /* scaffold reference for pool word C00E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewHoleB;  /* scaffold reference for pool word C010 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewHoleR;  /* scaffold reference for pool word C012 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastBlackEgg;  /* scaffold reference for pool word C014 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastRedEgg;  /* scaffold reference for pool word C016 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastFoodDrop;  /* scaffold reference for pool word C018 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LayDownQueenMode;  /* scaffold reference for pool word C01A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far gGameNeedsSaving;  /* scaffold reference for pool word C01C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far theSndIDs;  /* scaffold reference for pool word C01E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Cheats;  /* scaffold reference for pool word C020 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far CheatIndex;  /* scaffold reference for pool word C022 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far GAME_FILE;  /* scaffold reference for pool word C024 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far nilPStr;  /* scaffold reference for pool word C026 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ErrStr;  /* scaffold reference for pool word C028 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlertSimAntFastPStr;  /* scaffold reference for pool word C02A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far in16colorPStr;  /* scaffold reference for pool word C02C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far hHelpCursor;  /* scaffold reference for pool word C02E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triBoundRun;  /* scaffold reference for pool word C030 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far FoodR;  /* scaffold reference for pool word C032 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far DeathCnt;  /* scaffold reference for pool word C034 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custIdNumStrHandle;  /* scaffold reference for pool word C036 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeCrazyCnt;  /* scaffold reference for pool word C038 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far gInBackground;  /* scaffold reference for pool word C03A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far HistGraphStrs;  /* scaffold reference for pool word C03C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ChaseSpid;  /* scaffold reference for pool word C03E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeTargLife;  /* scaffold reference for pool word C040 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far UDMapFlip;  /* scaffold reference for pool word C042 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BoyMsgOffset;  /* scaffold reference for pool word C044 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastSMode;  /* scaffold reference for pool word C046 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RMapPnt;  /* scaffold reference for pool word C048 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far H_BPop;  /* scaffold reference for pool word C04A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WindPromptStrs;  /* scaffold reference for pool word C04C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDelay;  /* scaffold reference for pool word C04E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far H_FoodA;  /* scaffold reference for pool word C050 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EatCountB;  /* scaffold reference for pool word C052 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far openDBData;  /* scaffold reference for pool word C054 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WantSpiderBalloon;  /* scaffold reference for pool word C056 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeDropAlarm;  /* scaffold reference for pool word C058 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Cycle;  /* scaffold reference for pool word C05A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YDMapFlip;  /* scaffold reference for pool word C05C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far oldMusicOn;  /* scaffold reference for pool word C05E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ShowPercentMode;  /* scaffold reference for pool word C060 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RedPlane;  /* scaffold reference for pool word C062 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far H_RPop;  /* scaffold reference for pool word C064 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far FontNameStrs;  /* scaffold reference for pool word C066 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far shiftMaskPutRtn;  /* scaffold reference for pool word C068 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StrategicModeR;  /* scaffold reference for pool word C06A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far lastStrPos;  /* scaffold reference for pool word C06C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triBoundMaxD;  /* scaffold reference for pool word C06E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far hScrollMax;  /* scaffold reference for pool word C070 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BlkWarnHealth;  /* scaffold reference for pool word C072 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far win_numOfGroups;  /* scaffold reference for pool word C074 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BAntsEaten;  /* scaffold reference for pool word C076 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SpiderMsgs;  /* scaffold reference for pool word C078 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far GameTime;  /* scaffold reference for pool word C07A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far helpFile;  /* scaffold reference for pool word C07C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far PleaseRefToPStr;  /* scaffold reference for pool word C07E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Scycle2;  /* scaffold reference for pool word C080 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_LoadTiles(void);
void far pool_stub_win_EditChanged(void);
void far pool_stub_ScrollEditWindow(void);
void far pool_stub_DrawEditGraphs(void);
void far pool_stub_SetEditWinTitle(void);
void far pool_stub_DrawSpider(void);
void far pool_stub_DrawPalps(void);
void far pool_stub_DrawLegs(void);
void far pool_stub_DrawCurBalloons(void);
void far pool_stub_DoEditScroll(void);
void far ProcEditEvent(struct EditEvent far *event);
void OpenEditWindow(void);
void MakeEditOpen(void);
void ForceUpdateEdit(void);
void DoEditUpdateDraw(void);
void UpdateEditWindow(void);
void DrawEdit(void);
void InvalidUpdateEdit(void);
void far PreDrawSpider(void);
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
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_EditChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ScrollEditWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawEditGraphs)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetEditWinTitle)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSpider)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawPalps)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawLegs)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawCurBalloons)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoEditScroll)
#pragma alloc_text(RUN2_TEXT, ProcEditEvent)
#pragma alloc_text(RUN3_TEXT, OpenEditWindow, MakeEditOpen, ForceUpdateEdit, DoEditUpdateDraw)
#pragma alloc_text(RUN4_TEXT, UpdateEditWindow)
#pragma alloc_text(RUN5_TEXT, DrawEdit)
#pragma alloc_text(RUN6_TEXT, InvalidUpdateEdit, PreDrawSpider)
#pragma alloc_text(RUN7_TEXT, ed_MoveTo)
#pragma alloc_text(RUN8_TEXT, BalloonIsVisible, EggBalloons, FightBalloons, QueenBalloons)
#pragma alloc_text(RUN8_TEXT, RestBalloons)
#pragma alloc_text(RUN9_TEXT, EditMsgBalloon, PreDrawBalloons)
#pragma alloc_text(RUN10_TEXT, ResetEditScrollRange)

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
    t = pack_buf;
}

void far ProcEditEvent(struct EditEvent far *event)
{
    clip_SetWin(0);

    switch (event->message) {
    case 4:
    case 21:
        processEdit(event);
        break;
    case 6:
        DoWinHelp(2);
        break;
    case 7:
        EditToolsMenu();
        break;
    case 8:
        SetMapPlane(1);
        break;
    case 9:
        SetMapPlane(2);
        break;
    case 10:
        SetMapPlane(3);
        break;
    case 11:
        GotoMyAnt();
        break;
    case 12:
        GotoSpider();
        break;
    case 13:
        GotoBQueen();
        break;
    case 14:
        GotoRQueen();
        break;
    case 15:
        SetPause(GamePaused == 0);
        break;
    case 16:
        EditScentMenu();
        break;
    case 17:
        DoHealthSetY(event, 17);
        break;
    case 18:
        DoWarnSetB(event, 18);
        break;
    }

    clip_Off();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_EditChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF90; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_EditChanged(void)
{
    volatile int t;

    t = Scycle;
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
    t = (int)spiderTileLeft;
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
    t = EditColumns;
    t = MiscStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetEditWinTitle.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF9E BFA0 BFA2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetEditWinTitle(void)
{
    volatile int t;

    t = EditDragPnt;
    t = SMode;
    t = modeButtonState;
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

void far PreDrawSpider(void)
{
    int x, y, px, py;
    int sx, sy;

    spiderRect.top = 0x8000;
    spiderTileLeft = 500;
    spiderTileTop = 500;

    if (!SpidOn)
        return;

    y = MapPnt.y;
    x = MapPnt.x;
    px = x * tileWidth;
    py = y * tileHeight;

    sx = SpidX;
    sy = SpidY;

    if (displayType == 2) {
        sx = sx * 3 / 4;
        sy = sy * 3 / 4;
    }

    if (MapPlane != 1 && MapPlane != 0)
        return;
    if (px > sx)
        return;
    if (tileWidth * editWidth + px < sx)
        return;
    if (py > sy)
        return;
    if (tileHeight * editHeight + py < sy)
        return;

    spiderBuf.x = tileWidth * 7;
    spiderBuf.y = tileHeight * 7;

    spiderTileLeft = SpidX / 16 - x - 3;
    spiderTileTop = SpidY / 16 - y - 3;

    if (editBufInvalidFlag[0] && !scrollBarFlag) {
        editForce = 1;
        InvalidateRect(win_hwnd[0], (void far *)0, 0);
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFAC BFAE BFB0 BFB2 BFB4 BFB6 BFB8 BFBA BFBC BFBE BFC0 BFC2 BFC4 BFC6 BFC8 BFCA BFCC BFCE BFD0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSpider(void)
{
    volatile int t;

    t = StoreArray;
    t = mapCursorRect;
    t = Dx9;
    t = Dy9;
    t = TurnTab;
    t = relSearchDirs;
    t = absSearchDirs;
    t = IsCarryCaste;
    t = CatCycle;
    t = UnCarryCaste;
    t = custNameStrHandle;
    t = YMapPopB;
    t = ncbHead;
    t = YMapPopR;
    t = CatDir;
    t = WantRestBalloon;
    t = LastColonyPopB;
    t = SpidRevenge;
    t = TilesDugB;
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

    t = lastMapMapBuf;
    t = ListIndexR;
    t = YMapSeeds;
    t = ExitMapB;
    t = ExitMapR;
    t = AlistX;
    t = AlistY;
    t = AlistM;
    t = AlistT;
    t = AlistS;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawLegs.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFE6 BFE8 BFEA BFEC BFEE BFF0 BFF2 BFF4 BFF6 BFF8 BFFA BFFC BFFE C000 C002 C004 C006 C008 C00A C00C C00E C010 C012 C014 C016 C018 C01A C01C C01E C020 C022 C024 C026 C028 C02A C02C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawLegs(void)
{
    volatile int t;

    t = BlistX;
    t = BlistY;
    t = BlistM;
    t = BlistT;
    t = BlistS;
    t = RlistX;
    t = RlistY;
    t = RlistM;
    t = RlistT;
    t = RlistS;
    t = TemDensity;
    t = PherMapA;
    t = PherMapF;
    t = PherMapBN;
    t = PherMapBT;
    t = PherMapRN;
    t = PherMapRT;
    t = HoleMapB;
    t = HoleMapR;
    t = LastNewExitB;
    t = LastNewExitR;
    t = LastNewHoleB;
    t = LastNewHoleR;
    t = LastBlackEgg;
    t = LastRedEgg;
    t = LastFoodDrop;
    t = LayDownQueenMode;
    t = gGameNeedsSaving;
    t = theSndIDs;
    t = Cheats;
    t = CheatIndex;
    t = GAME_FILE;
    t = nilPStr;
    t = ErrStr;
    t = AlertSimAntFastPStr;
    t = in16colorPStr;
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

    t = hHelpCursor;
    t = triBoundRun;
    t = FoodR;
    t = DeathCnt;
    t = custIdNumStrHandle;
    t = MeCrazyCnt;
    t = gInBackground;
    t = HistGraphStrs;
    t = ChaseSpid;
    t = MeTargLife;
    t = UDMapFlip;
    t = BoyMsgOffset;
    t = LastSMode;
    t = RMapPnt;
    t = H_BPop;
    t = WindPromptStrs;
    t = CatDelay;
    t = H_FoodA;
    t = EatCountB;
    t = openDBData;
    t = WantSpiderBalloon;
    t = MeDropAlarm;
    t = Cycle;
    t = YDMapFlip;
    t = oldMusicOn;
    t = ShowPercentMode;
    t = RedPlane;
    t = H_RPop;
    t = FontNameStrs;
    t = shiftMaskPutRtn;
    t = StrategicModeR;
    t = lastStrPos;
    t = triBoundMaxD;
    t = hScrollMax;
    t = BlkWarnHealth;
    t = win_numOfGroups;
    t = BAntsEaten;
    t = SpiderMsgs;
    t = GameTime;
    t = helpFile;
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

    t = PleaseRefToPStr;
    t = Scycle2;
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

