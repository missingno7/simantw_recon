/* Candidate translation unit antedit_00F4_ResetEditScrollRange_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ResetEditScrollRange
 * SCAFFOLDED: unclaimed members _OverlayTileSet, _LoadTiles, _ProcEditEvent, _win_EditChanged, _ScrollEditWindow, _DrawEditGraphs, _SetEditWinTitle, _PreDrawSpider, _DrawSpider, _DrawPalps, _DrawLegs, _DrawCurBalloons, _DoEditScroll are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct MapPoint {
    int x;
    int y;
};
extern int near win_hwnd[];
extern int near editHeight;
extern int near editWidth;
extern int far MapMode;
extern struct MapPoint far MapPnt;
extern void far pascal SetScrollRange(int hwnd, int bar, int minPos, int maxPos, int redraw);
extern int far pascal SetScrollPos(int hwnd, int bar, int pos, int redraw);
extern int far pascal GetScrollPos(int hwnd, int bar);

extern int far Dx8;  /* scaffold reference for pool word BF7E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word BF80 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word BF82 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word BF84 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word BF86 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word BF88 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far editBufInvalidFlag;  /* scaffold reference for pool word BF8A (segment 8, MAPSYM_SITE_NAME) */
extern int far MiscStrs;  /* scaffold reference for pool word BF8C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word BF8E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word BF90 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far spiderTileLeft;  /* scaffold reference for pool word BF94 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dy8;  /* scaffold reference for pool word BF96 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word BF98 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word BF9A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word BF9C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word BF9E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word BFA0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word BFA2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word BFA4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far spiderTileTop;  /* scaffold reference for pool word BFA6 (segment 9, MAPSYM_SITE_NAME) */
extern int far SpidOn;  /* scaffold reference for pool word BFA8 (segment 9, MAPSYM_SITE_NAME) */
extern int far custNameStrHandle;  /* scaffold reference for pool word BFAA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word BFAC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDir;  /* scaffold reference for pool word BFAE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word BFB0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TurnTab;  /* scaffold reference for pool word BFB2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word BFB4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far absSearchDirs;  /* scaffold reference for pool word BFB6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far IsCarryCaste;  /* scaffold reference for pool word BFB8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far UnCarryCaste;  /* scaffold reference for pool word BFBA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far WantRestBalloon;  /* scaffold reference for pool word BFBC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YMapPopB;  /* scaffold reference for pool word BFBE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastColonyPopB;  /* scaffold reference for pool word BFC0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YMapPopR;  /* scaffold reference for pool word BFC2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SpidRevenge;  /* scaffold reference for pool word BFC4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YMapSeeds;  /* scaffold reference for pool word BFC6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastRestPnt;  /* scaffold reference for pool word BFC8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TilesDugB;  /* scaffold reference for pool word BFCA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far lastMapMapBuf;  /* scaffold reference for pool word BFCC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexR;  /* scaffold reference for pool word BFCE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far hHelpCursor;  /* scaffold reference for pool word BFD0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triBoundRun;  /* scaffold reference for pool word BFD2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far spiderRect;  /* scaffold reference for pool word BFD4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ExitMapB;  /* scaffold reference for pool word BFD6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ExitMapR;  /* scaffold reference for pool word BFD8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistX;  /* scaffold reference for pool word BFDA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistY;  /* scaffold reference for pool word BFDC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistM;  /* scaffold reference for pool word BFDE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistT;  /* scaffold reference for pool word BFE0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlistS;  /* scaffold reference for pool word BFE2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistX;  /* scaffold reference for pool word BFE4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistY;  /* scaffold reference for pool word BFE6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistM;  /* scaffold reference for pool word BFE8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistT;  /* scaffold reference for pool word BFEA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BlistS;  /* scaffold reference for pool word BFEC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistX;  /* scaffold reference for pool word BFEE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistY;  /* scaffold reference for pool word BFF0 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistM;  /* scaffold reference for pool word BFF2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistT;  /* scaffold reference for pool word BFF4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far RlistS;  /* scaffold reference for pool word BFF6 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far TemDensity;  /* scaffold reference for pool word BFF8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapA;  /* scaffold reference for pool word BFFA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapF;  /* scaffold reference for pool word BFFC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapBN;  /* scaffold reference for pool word BFFE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapBT;  /* scaffold reference for pool word C000 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapRN;  /* scaffold reference for pool word C002 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PherMapRT;  /* scaffold reference for pool word C004 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far HoleMapB;  /* scaffold reference for pool word C006 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far HoleMapR;  /* scaffold reference for pool word C008 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewExitB;  /* scaffold reference for pool word C00A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewExitR;  /* scaffold reference for pool word C00C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewHoleB;  /* scaffold reference for pool word C00E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastNewHoleR;  /* scaffold reference for pool word C010 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastBlackEgg;  /* scaffold reference for pool word C012 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastRedEgg;  /* scaffold reference for pool word C014 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastFoodDrop;  /* scaffold reference for pool word C016 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LayDownQueenMode;  /* scaffold reference for pool word C018 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far gGameNeedsSaving;  /* scaffold reference for pool word C01A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far theSndIDs;  /* scaffold reference for pool word C01C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Cheats;  /* scaffold reference for pool word C01E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far CheatIndex;  /* scaffold reference for pool word C020 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far GAME_FILE;  /* scaffold reference for pool word C022 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far nilPStr;  /* scaffold reference for pool word C024 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far ErrStr;  /* scaffold reference for pool word C026 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AlertSimAntFastPStr;  /* scaffold reference for pool word C028 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far in16colorPStr;  /* scaffold reference for pool word C02A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far PleaseRefToPStr;  /* scaffold reference for pool word C02C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far FoodR;  /* scaffold reference for pool word C02E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far DeathCnt;  /* scaffold reference for pool word C030 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custIdNumStrHandle;  /* scaffold reference for pool word C032 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeCrazyCnt;  /* scaffold reference for pool word C034 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far gInBackground;  /* scaffold reference for pool word C036 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far HistGraphStrs;  /* scaffold reference for pool word C038 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ChaseSpid;  /* scaffold reference for pool word C03A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeTargLife;  /* scaffold reference for pool word C03C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far UDMapFlip;  /* scaffold reference for pool word C03E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BoyMsgOffset;  /* scaffold reference for pool word C040 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastSMode;  /* scaffold reference for pool word C042 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RMapPnt;  /* scaffold reference for pool word C044 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far H_BPop;  /* scaffold reference for pool word C046 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WindPromptStrs;  /* scaffold reference for pool word C048 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDelay;  /* scaffold reference for pool word C04A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far H_FoodA;  /* scaffold reference for pool word C04C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EatCountB;  /* scaffold reference for pool word C04E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far FightBalloonCnt;  /* scaffold reference for pool word C050 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastEggPlane;  /* scaffold reference for pool word C052 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far openDBData;  /* scaffold reference for pool word C054 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WantSpiderBalloon;  /* scaffold reference for pool word C056 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MeDropAlarm;  /* scaffold reference for pool word C058 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Cycle;  /* scaffold reference for pool word C05A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far YDMapFlip;  /* scaffold reference for pool word C05C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far oldMusicOn;  /* scaffold reference for pool word C05E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ShowPercentMode;  /* scaffold reference for pool word C060 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Barrier;  /* scaffold reference for pool word C062 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far RedPlane;  /* scaffold reference for pool word C064 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far H_RPop;  /* scaffold reference for pool word C066 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far FontNameStrs;  /* scaffold reference for pool word C068 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far shiftMaskPutRtn;  /* scaffold reference for pool word C06A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StrategicModeR;  /* scaffold reference for pool word C06C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far lastStrPos;  /* scaffold reference for pool word C06E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far triBoundMaxD;  /* scaffold reference for pool word C070 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far hScrollMax;  /* scaffold reference for pool word C072 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BlkWarnHealth;  /* scaffold reference for pool word C074 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far win_numOfGroups;  /* scaffold reference for pool word C076 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BAntsEaten;  /* scaffold reference for pool word C078 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SpiderMsgs;  /* scaffold reference for pool word C07A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far GameTime;  /* scaffold reference for pool word C07C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far theSimAntManPStr;  /* scaffold reference for pool word C07E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far helpFile;  /* scaffold reference for pool word C080 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_OverlayTileSet(void);
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

extern int near MapPlane;
int far CenterEdit(int x, int y);
void far ResetEditScrollRange(void);
static int near ScrollEditBy(int dx, int dy);
#pragma alloc_text(RUN1_TEXT, CenterEdit)
#pragma alloc_text(RUN2_TEXT, ResetEditScrollRange, ScrollEditBy)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_OverlayTileSet)
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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _OverlayTileSet.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF7E BF80 BF82 BF84; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_OverlayTileSet(void)
{
    volatile int t;

    t = Dx8;
    t = match_position;
    t = match_length;
    t = pack_buf;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _LoadTiles.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF86 BF88 BF8A BF8C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_LoadTiles(void)
{
    volatile int t;

    t = Scycle;
    t = EditColumns;
    t = editBufInvalidFlag;
    t = MiscStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcEditEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF8E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcEditEvent(void)
{
    volatile int t;

    t = LastQueenPlane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_EditChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF90; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_EditChanged(void)
{
    volatile int t;

    t = EditDragPnt;
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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawEditGraphs.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF96 BF98 BF9A BF9C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawEditGraphs(void)
{
    volatile int t;

    t = Dy8;
    t = Dx9;
    t = SMode;
    t = modeButtonState;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetEditWinTitle.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF9E BFA0 BFA2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetEditWinTitle(void)
{
    volatile int t;

    t = CurRestPlane;
    t = StoreArray;
    t = mapCursorRect;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _PreDrawSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFA4 BFA6 BFA8 BFAA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_PreDrawSpider(void)
{
    volatile int t;

    t = CatCycle;
    t = spiderTileTop;
    t = SpidOn;
    t = custNameStrHandle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSpider.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFAC BFAE BFB0 BFB2 BFB4 BFB6 BFB8 BFBA BFBC BFBE BFC0 BFC2 BFC4 BFC6 BFC8 BFCA BFCC BFCE BFD0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSpider(void)
{
    volatile int t;

    t = ncbHead;
    t = CatDir;
    t = Dy9;
    t = TurnTab;
    t = relSearchDirs;
    t = absSearchDirs;
    t = IsCarryCaste;
    t = UnCarryCaste;
    t = WantRestBalloon;
    t = YMapPopB;
    t = LastColonyPopB;
    t = YMapPopR;
    t = SpidRevenge;
    t = YMapSeeds;
    t = LastRestPnt;
    t = TilesDugB;
    t = lastMapMapBuf;
    t = ListIndexR;
    t = hHelpCursor;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawPalps.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFD2 BFD4 BFD6 BFD8 BFDA BFDC BFDE BFE0 BFE2 BFE4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawPalps(void)
{
    volatile int t;

    t = triBoundRun;
    t = spiderRect;
    t = ExitMapB;
    t = ExitMapR;
    t = AlistX;
    t = AlistY;
    t = AlistM;
    t = AlistT;
    t = AlistS;
    t = BlistX;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawLegs.
 * It only reproduces the object's selector-pool allocation order for the
 * words BFE6 BFE8 BFEA BFEC BFEE BFF0 BFF2 BFF4 BFF6 BFF8 BFFA BFFC BFFE C000 C002 C004 C006 C008 C00A C00C C00E C010 C012 C014 C016 C018 C01A C01C C01E C020 C022 C024 C026 C028 C02A C02C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawLegs(void)
{
    volatile int t;

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
    t = PleaseRefToPStr;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawCurBalloons.
 * It only reproduces the object's selector-pool allocation order for the
 * words C02E C030 C032 C034 C036 C038 C03A C03C C03E C040 C042 C044 C046 C048 C04A C04C C04E C050 C052 C054 C056 C058 C05A C05C C05E C060 C062 C064 C066 C068 C06A C06C C06E C070 C072 C074 C076 C078 C07A C07C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawCurBalloons(void)
{
    volatile int t;

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
    t = FightBalloonCnt;
    t = LastEggPlane;
    t = openDBData;
    t = WantSpiderBalloon;
    t = MeDropAlarm;
    t = Cycle;
    t = YDMapFlip;
    t = oldMusicOn;
    t = ShowPercentMode;
    t = Barrier;
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
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoEditScroll.
 * It only reproduces the object's selector-pool allocation order for the
 * words C07E C080; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoEditScroll(void)
{
    volatile int t;

    t = theSimAntManPStr;
    t = helpFile;
}

static int near lastMode = -1;
static int near lastEditHeight = -1;
static int near lastEditWidth = -1;
int far CenterEdit(int x, int y)
{
    int width;
    int height;
    int result;

    if (ScrollEditBy(x - MapPnt.x - editWidth / 2,
                     y - MapPnt.y - editHeight / 2)) {
        height = 64;
        switch (MapPlane) {
        case 0:
        case 1:
            width = 128;
            break;
        }
        if (MapPnt.x < 0)
            MapPnt.x = 0;
        else if (MapPnt.x + editWidth > width)
            MapPnt.x = width - editWidth;
        if (MapPnt.y < 0)
            MapPnt.y = 0;
        else if (MapPnt.y + editHeight > height)
            MapPnt.y = height - editHeight;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

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

static int near ScrollEditBy(int dx, int dy)
{
    extern struct MapPoint __based(__segname("SIMANT_DATA_GROUP")) MapPnt;
    int yStep;
    int xStep;
    register int i;
    unsigned long fraction;
    unsigned long error;

    if (dx == 0 && dy == 0) return 0;

    yStep = 1;
    xStep = 1;
    if (dx < 0) {
        yStep = -1;
        dx = -dx;
    }
    if (dy < 0) {
        xStep = -1;
        dy = -dy;
    }

    error = 0UL;
    if (dy >= dx) {
        fraction = ((unsigned long)dx << 16) / (unsigned long)dy;
        if (dy > 0) {
            i = dy;
            do {
                MapPnt.y += xStep;
                error += fraction;
                if ((error >> 16) & 1UL) {
                    MapPnt.x += yStep;
                    error ^= 0x10000UL;
                }
            } while (--i);
        }
    } else {
        fraction = ((unsigned long)dy << 16) / (unsigned long)dx;
        if (dx > 0) {
            i = dx;
            do {
                MapPnt.x += yStep;
                error += fraction;
                if ((error >> 16) & 1UL) {
                    MapPnt.y += xStep;
                    error ^= 0x10000UL;
                }
            } while (--i);
        }
    }
    return 1;
}
