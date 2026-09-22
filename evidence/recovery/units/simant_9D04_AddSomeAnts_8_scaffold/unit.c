/* Candidate translation unit simant_9D04_AddSomeAnts_8_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddSomeAnts, _SetEditMode, _SetMapModeAnt, _GotoMapPoint, _CenterAnt, _GotoSpider, _GotoRQueen
 * SCAFFOLDED: unclaimed members _KillSomeAnts, _SubtractFood, _SetYardMode, _SetMapPlaneLocation, _SetMapPlane, _GotoMyAnt are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far ListIndexA;
extern int far CommandKey;
extern void far AddBlackAnts(int count);
extern void far AddRedAnts(int count);
extern void far FullCount(void);
extern int far CurEditMode;
extern int near MapPlane;
extern int near YardMode;
extern int near win_hwnd[];
extern int far MapMode;
extern void far SetMapPlane(int plane);
extern void far SetMapTitle(void);
extern void far SetYardMode(int mode);
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_SetGroupSelectedObj(int group, int selected, int object);
extern void far win_MakeObjSelected(int object);
extern void far win_MakeGroupUnselected(int id1, int id2);
extern int far UDMapFlip;
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern void far DrawMap(void);
extern void far DrawMapCursor(void);
extern int far LessonTemp;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near SpidX;
extern int near SpidY;
extern int far SpidOn;
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far GotoQueen(int value);

extern int far AlistX;  /* scaffold reference for pool word C0DE (segment 8, MAPSYM_SITE_NAME) */
extern int far FoodA;  /* scaffold reference for pool word C0E0 (segment 9, MAPSYM_SITE_NAME) */
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
extern int far CurGameType;  /* scaffold reference for pool word C102 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_KillSomeAnts(void);
void far pool_stub_SubtractFood(void);
void far pool_stub_SetYardMode(void);
void far pool_stub_SetMapPlaneLocation(void);
void far pool_stub_SetMapPlane(void);
void far pool_stub_GotoMyAnt(void);
void SetEditMode(int value);
void far SetMapModeAnt(int mode);
void far GotoMapPoint(int plane, int x, int y);
void far CenterAnt(void);
void far GotoSpider(void);
void GotoRQueen(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_KillSomeAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SubtractFood)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetYardMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapPlaneLocation)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapPlane)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GotoMyAnt)
#pragma alloc_text(RUN2_TEXT, SetEditMode, SetMapModeAnt)
#pragma alloc_text(RUN3_TEXT, GotoMapPoint)
#pragma alloc_text(RUN4_TEXT, CenterAnt)
#pragma alloc_text(RUN5_TEXT, GotoSpider)
#pragma alloc_text(RUN6_TEXT, GotoRQueen)

void far AddSomeAnts(int kind)
{
    int count;

    count = ListIndexA;
    if (count < 1000) {
        if (CommandKey == 1) {
            if (kind == 1)
                AddBlackAnts(1000 - count);
            else
                AddRedAnts(1000 - count);
        } else if (kind == 1) {
            AddBlackAnts(0x20);
        } else {
            AddRedAnts(0x20);
        }
    }
    FullCount();
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

void SetEditMode(int value)
{
    CurEditMode = value;
}

static int antModeObjIds[14] = {
    0x7265, 0x6c66, 0x776f, 0x0000,
    0x220b, 0x220c, 0x220e, 0x220f, 0x220d,
    0x0109, 0x010a, 0x010c, 0x010d, 0x010b
};
void far SetMapModeAnt(int mode)
{
    if (MapMode == mode && mode >= 4 && mode <= 8)
        mode = 1;

    switch (mode) {
    case 0:
        if (MapMode != 0) {
            MapMode = mode;
            SetYardMode(YardMode);
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (MapPlane != 1)
            SetMapPlane(1);
    case 1:
    case 2:
    case 3:
        MapMode = mode;
        SetMapTitle();
        if (win_IsWinOpen(0x100)) {
            clip_Push();
            clip_SetWin(0x100);
        }
        if (win_hwnd[34] != 0) {
            if (mode >= 4 && mode <= 8)
                win_SetGroupSelectedObj(0x2200, 1, antModeObjIds[mode]);
            else
                win_MakeGroupUnselected(0x2200, 1);
        } else {
            if (mode >= 4 && mode <= 8)
                win_MakeObjSelected(antModeObjIds[mode + 5]);
            else
                win_MakeGroupUnselected(0x100, 2);
        }
        if (win_IsWinOpen(0x100))
            clip_Pop();
        break;
    }
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

void far GotoMapPoint(int plane, int x, int y)
{
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    if (plane == MapPlane && plane > 0) {
        if (CenterEdit(x, y))
            UpdateEdit();
        UDMapFlip = 0;
    } else {
        SetMapPlaneLocation(plane, x, y);
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
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

void far CenterAnt(void)
{
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    LessonTemp = 1;
    if (MePlane != MapPlane)
        SetMapPlane(MePlane);
    if (CenterEdit(MeLocX, MeLocY))
        UpdateEdit();
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
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

void GotoRQueen(void)
{
    GotoQueen(0x00e0);
}

