/* Candidate translation unit antedit_C19C_ToggleMapCursor_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ToggleMapCursor
 * SCAFFOLDED: unclaimed members _InitMapFunctions, _ProcMapEvent, _ProcMapRibbonEvent, _DrawMapCursor are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct Point {
    int x;
    int y;
};
extern int near mapCursorState;
extern struct Rect far mapCursorRect;
extern struct Point far MapPnt;
extern int far mapYsize;
extern int far mapXsize;
extern int far just;
extern struct Rect far mapTileRect;
extern int near editHeight;
extern int near editWidth;
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int color);

extern unsigned int far lastMapMapBuf;  /* selector C1E0 from the admitted C19C pool ledger */
extern int far match_length;  /* scaffold reference for pool word C1E6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1E8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C1EA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C1EC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MapMode;  /* selector C1EE from C854 binding */

void far pool_stub_KeepMiniMapRefreshLow(void);
void far pool_stub_InitMapFunctions(void);
void far pool_stub_ProcMapEvent(void);
void far pool_stub_ProcMapRibbonEvent(void);
void far pool_stub_DrawMapCursor(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_KeepMiniMapRefreshLow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitMapFunctions)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcMapEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcMapRibbonEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawMapCursor)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitMapFunctions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1E0 C1E2 C1E4 C1E6 C1E8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitMapFunctions(void)
{
    volatile int t;

    t = (int)lastMapMapBuf;
    t = (int)mapYsize;
    t = (int)mapXsize;
    t = match_length;
    t = pack_buf;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcMapEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1EA C1EC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcMapEvent(void)
{
    volatile int t;

    t = Scycle;
    t = EditColumns;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcMapRibbonEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1EE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcMapRibbonEvent(void)
{
    volatile int t;

    t = MapMode;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawMapCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1F0 C1F2 C1F4 C1F6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawMapCursor(void)
{
    volatile int t;

    t = *(int far *)&MapPnt;
    t = *(int far *)&mapTileRect;
    t = *(int far *)&mapCursorRect;
    t = (int)just;
}

void far ToggleMapCursor(void)
{
    if (mapCursorState != 0) {
        if (win_IsWinOpen(0x100) && mapCursorState == 1) {
            clip_Push();
            clip_SetWin(0x100);
            GRectInvOutline(&mapCursorRect, 2);
            mapCursorState = 0;
            clip_Pop();
        }
        return;
    }

    if (win_IsWinOpen(0x100) && mapCursorState == 0) {
        clip_Push();
        clip_SetWin(0x100);

        mapCursorRect.top = mapYsize * MapPnt.y + mapTileRect.top;
        mapCursorRect.bottom = mapCursorRect.top + mapYsize * editHeight;
        mapCursorRect.left = mapXsize * MapPnt.x + just + mapTileRect.left;
        mapCursorRect.right = mapCursorRect.left + mapXsize * editWidth;

        GRectInvOutline(&mapCursorRect, 2);
        mapCursorState = 1;
        clip_Pop();
    }
}



extern int far MapMode;
extern int far TERRAINset;
extern unsigned int far mapMapBuf;
extern unsigned int far lastMapMapBuf;
extern int near showTrails;
extern unsigned char near displayType;
extern int near mapMem;
extern int near lastMapGenMode;
extern void far win_MapChanged(void);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far GenOverMap(void far *destination, int baseX, int baseY,
                           int pattern, int terrainPattern, int trails);
struct MapCopy { unsigned int word[4096]; };
struct MapAFrame { int pad[2]; int trails; };

static void near MiniMapHelperA(void)
{
    struct MapAFrame frame;
    struct MapCopy far *destination;

    frame.trails = showTrails;
    if (MapMode != lastMapGenMode) {
        win_MapChanged();
        lastMapGenMode = MapMode;
        frame.trails = 0;
    }
    destination = (struct MapCopy far *)mem_Lock(mapMapBuf);
    if (frame.trails != 0) {
        *(struct MapCopy far *)destination =
            *(struct MapCopy far *)mem_Lock(lastMapMapBuf);
        mem_Unlock(lastMapMapBuf);
    }
    if (!(displayType & 1)) {
        if (TERRAINset == 1)
            GenOverMap(destination, 0x68e8, 0x28e8, 0xaa48, 0xa978, frame.trails);
        else
            GenOverMap(destination, 0x68e8, 0x28e8, 0xaa48, 0xa8e8, frame.trails);
    } else {
        if (TERRAINset == 1)
            GenOverMap(destination, 0x68e8, 0x28e8, 0xabf8, 0xab28, frame.trails);
        else
            GenOverMap(destination, 0x68e8, 0x28e8, 0xabf8, 0xaaa8, frame.trails);
    }
    mem_Unlock(mapMapBuf);
}

void far pool_stub_KeepMiniMapRefreshLow(void)
{
    MiniMapHelperA();
}
