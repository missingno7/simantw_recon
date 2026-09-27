/* Candidate translation unit antedit_C19C_InitMapFunctions_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitMapFunctions, _ToggleMapCursor
 * SCAFFOLDED: unclaimed members _ProcMapEvent, _ProcMapRibbonEvent, _DrawMapCursor are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

typedef void (far *MakeTableProc)();
extern unsigned char near displayType;
extern unsigned int far lastMapMapBuf;
extern int far mapXsize;
extern int far mapYsize;
extern MakeTableProc far makea;
extern MakeTableProc far makeb;
extern void far RallocMemorySoft(void);
extern void far RallocMemoryFree(void);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far Windows_MakeTable4x4();
extern void far WindowsMono_MakeTable4x4a();
extern void far WindowsMono_MakeTable4x4b();
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
extern int far just;
extern struct Rect far mapTileRect;
extern int near editHeight;
extern int near editWidth;
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int color);

extern int far match_position;  /* scaffold reference for pool word C1EA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1EC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C1EE (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_ProcMapEvent(void);
void far pool_stub_ProcMapRibbonEvent(void);
void far pool_stub_DrawMapCursor(void);
void far ToggleMapCursor(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcMapEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcMapRibbonEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawMapCursor)
#pragma alloc_text(RUN2_TEXT, ToggleMapCursor)

void far InitMapFunctions(void)
{
    RallocMemorySoft();
    RallocMemoryFree();
    lastMapMapBuf = mem_Alloc(0x2000L, 1, "Generated buffer window");
    mapYsize = 4;
    mapXsize = 4;
    if (!(displayType & 1)) {
        makea = Windows_MakeTable4x4;
        makeb = Windows_MakeTable4x4;
    } else {
        makea = WindowsMono_MakeTable4x4a;
        makeb = WindowsMono_MakeTable4x4b;
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcMapEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1EA C1EC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcMapEvent(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcMapRibbonEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1EE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcMapRibbonEvent(void)
{
    volatile int t;

    t = Dx8;
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

