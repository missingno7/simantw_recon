/* Candidate translation unit simant_9D04_SetMapPlane_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _SetMapPlane
 * SCAFFOLDED: unclaimed members _AddSomeAnts, _KillSomeAnts, _SubtractFood, _SetEditMode, _SetMapModeAnt, _SetYardMode, _SetMapPlaneLocation, _GotoMapPoint are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct MapPoint { int x, y; };
extern int near volatile MapPlane;
extern int near OldMapPlane;
extern int far EditRows;
extern int far EditColumns;
extern int far hScrollMax;
extern int far CurEditMode;
extern int far MapPlane2EditTab[];
extern struct MapPoint far YMapPnt;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;
extern void far InvalEuMap(int a, int b, int columns, int rows);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern int far win_IsWinOpen(int window);
extern void far DrawMap(void);
extern void far SetMapModeAnt(int mode);

extern int far ListIndexA;  /* scaffold reference for pool word C0DA (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word C0DC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C0DE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word C0E0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C0E4 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far bHelp;  /* scaffold reference for pool word C0E6 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C0E8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C0EA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C0F2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C0F6 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_AddSomeAnts(void);
void far pool_stub_KillSomeAnts(void);
void far pool_stub_SubtractFood(void);
void far pool_stub_SetEditMode(void);
void far pool_stub_SetMapModeAnt(void);
void far pool_stub_SetYardMode(void);
void far pool_stub_SetMapPlaneLocation(void);
void far pool_stub_GotoMapPoint(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_AddSomeAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_KillSomeAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SubtractFood)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetEditMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapModeAnt)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetYardMode)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapPlaneLocation)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_GotoMapPoint)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _AddSomeAnts.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0DA C0DC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_AddSomeAnts(void)
{
    volatile int t;

    t = ListIndexA;
    t = Dx8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _KillSomeAnts.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0DE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_KillSomeAnts(void)
{
    volatile int t;

    t = Dy8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SubtractFood.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SubtractFood(void)
{
    volatile int t;

    t = match_position;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetEditMode.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetEditMode(void)
{
    volatile int t;

    t = (int)CurEditMode;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMapModeAnt.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMapModeAnt(void)
{
    volatile int t;

    t = Dx9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetYardMode.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0E6 C0E8 C0EA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetYardMode(void)
{
    volatile int t;

    t = bHelp;
    t = match_length;
    t = pack_buf;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMapPlaneLocation.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0EC C0EE C0F0 C0F2 C0F4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMapPlaneLocation(void)
{
    volatile int t;

    t = (int)EditRows;
    t = (int)EditColumns;
    t = (int)hScrollMax;
    t = Scycle;
    t = *(int far *)&YMapPnt;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _GotoMapPoint.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0F6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_GotoMapPoint(void)
{
    volatile int t;

    t = MiscStrs;
}

void far SetMapPlane(int plane)
{
    struct MapPoint pnt;

    if (plane != 0)
        InvalEuMap(0, 0, EditColumns, EditRows);
    else
        OldMapPlane = MapPlane;

    MapPlane = plane;
    hScrollMax = (plane == 1 ? 0x80 : 0x40) - EditColumns;
    CurEditMode = MapPlane2EditTab[MapPlane];

    switch (MapPlane) {
    case 0:
        pnt = YMapPnt;
        break;
    case 1:
        pnt = AMapPnt;
        break;
    case 2:
        pnt = BMapPnt;
        break;
    case 3:
        pnt = RMapPnt;
        break;
    }

    SetMapPlaneLocation(plane, pnt.x, pnt.y);
    if (MapPlane != 0) {
        if (CenterEdit(pnt.x, pnt.y))
            UpdateEdit();
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    SetMapModeAnt(MapPlane);
    UpdateEdit();
}

