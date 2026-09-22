/* Candidate translation unit simant_9D04_GotoSpider_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GotoSpider
 * SCAFFOLDED: unclaimed members _AddSomeAnts, _KillSomeAnts, _SubtractFood, _SetEditMode, _SetMapModeAnt, _SetYardMode, _SetMapPlaneLocation, _GotoMapPoint, _SetMapPlane, _CenterAnt, _GotoMyAnt are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near win_hwnd[];
extern int near MapPlane;
extern int near SpidX;
extern int near SpidY;
extern int far SpidOn;
extern int far UDMapFlip;
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern void far DrawMap(void);
extern void far DrawMapCursor(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

extern int far ListIndexA;  /* scaffold reference for pool word C0DA (segment 9, MAPSYM_SITE_NAME) */
extern int far CommandKey;  /* scaffold reference for pool word C0DC (segment 8, MAPSYM_SITE_NAME) */
extern int far AlistX;  /* scaffold reference for pool word C0DE (segment 8, MAPSYM_SITE_NAME) */
extern int far FoodA;  /* scaffold reference for pool word C0E0 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurEditMode;  /* scaffold reference for pool word C0E2 (segment 9, MAPSYM_SITE_NAME) */
extern int far MapMode;  /* scaffold reference for pool word C0E4 (segment 8, MAPSYM_SITE_NAME) */
extern int far mapBuf;  /* scaffold reference for pool word C0E6 (segment 10, MAPSYM_SITE_NAME) */
extern int far mapXsize;  /* scaffold reference for pool word C0E8 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapYsize;  /* scaffold reference for pool word C0EA (segment 9, MAPSYM_SITE_NAME) */
extern int far EditRows;  /* scaffold reference for pool word C0EC (segment 9, MAPSYM_SITE_NAME) */
extern int far EditColumns;  /* scaffold reference for pool word C0EE (segment 9, MAPSYM_SITE_NAME) */
extern int far hScrollMax;  /* scaffold reference for pool word C0F0 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurYardPnt;  /* scaffold reference for pool word C0F2 (segment 9, MAPSYM_SITE_NAME) */
extern int far YMapPnt;  /* scaffold reference for pool word C0F4 (segment 9, MAPSYM_SITE_NAME) */
extern int far MapPlane2EditTab;  /* scaffold reference for pool word C0F8 (segment 8, MAPSYM_SITE_NAME) */
extern int far AMapPnt;  /* scaffold reference for pool word C0FA (segment 9, MAPSYM_SITE_NAME) */
extern int far BMapPnt;  /* scaffold reference for pool word C0FC (segment 9, MAPSYM_SITE_NAME) */
extern int far RMapPnt;  /* scaffold reference for pool word C0FE (segment 9, MAPSYM_SITE_NAME) */
extern int far LessonTemp;  /* scaffold reference for pool word C100 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word C102 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_AddSomeAnts(void);
void far pool_stub_KillSomeAnts(void);
void far pool_stub_SubtractFood(void);
void far pool_stub_SetEditMode(void);
void far pool_stub_SetMapModeAnt(void);
void far pool_stub_SetYardMode(void);
void far pool_stub_SetMapPlaneLocation(void);
void far pool_stub_GotoMapPoint(void);
void far pool_stub_SetMapPlane(void);
void far pool_stub_CenterAnt(void);
void far pool_stub_GotoMyAnt(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_AddSomeAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_KillSomeAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SubtractFood)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetEditMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapModeAnt)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetYardMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapPlaneLocation)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GotoMapPoint)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapPlane)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_CenterAnt)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GotoMyAnt)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _AddSomeAnts.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0DA C0DC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_AddSomeAnts(void)
{
    volatile int t;

    t = ListIndexA;
    t = CommandKey;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _KillSomeAnts.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0DE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_KillSomeAnts(void)
{
    volatile int t;

    t = AlistX;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SubtractFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SubtractFood(void)
{
    volatile int t;

    t = FoodA;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetEditMode.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetEditMode(void)
{
    volatile int t;

    t = CurEditMode;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMapModeAnt.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMapModeAnt(void)
{
    volatile int t;

    t = MapMode;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetYardMode.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E6 C0E8 C0EA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetYardMode(void)
{
    volatile int t;

    t = mapBuf;
    t = mapXsize;
    t = mapYsize;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMapPlaneLocation.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0EC C0EE C0F0 C0F2 C0F4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMapPlaneLocation(void)
{
    volatile int t;

    t = EditRows;
    t = EditColumns;
    t = hScrollMax;
    t = CurYardPnt;
    t = YMapPnt;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GotoMapPoint.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0F6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GotoMapPoint(void)
{
    volatile int t;

    t = (int)UDMapFlip;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMapPlane.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0F8 C0FA C0FC C0FE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMapPlane(void)
{
    volatile int t;

    t = MapPlane2EditTab;
    t = AMapPnt;
    t = BMapPnt;
    t = RMapPnt;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _CenterAnt.
 * It only reproduces the object's selector-pool allocation order for the
 * words C100; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_CenterAnt(void)
{
    volatile int t;

    t = LessonTemp;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GotoMyAnt.
 * It only reproduces the object's selector-pool allocation order for the
 * words C102; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GotoMyAnt(void)
{
    volatile int t;

    t = CurGameType;
}

void far GotoSpider(void)
{
    int ex, ey;

    if (!SpidOn) {
        myBeginSound(1, 0, 0x7e);
        return;
    }

    ex = SpidX >> 4;
    ey = SpidY >> 4;

    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    if (MapPlane == 1) {
        if (CenterEdit(ex, ey))
            UpdateEdit();
        UDMapFlip = 0;
    } else {
        SetMapPlaneLocation(1, ex, ey);
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
}

