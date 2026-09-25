/* Candidate translation unit antedit_C19C_DrawMapCursor_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawMapCursor
 * SCAFFOLDED: unclaimed members _InitMapFunctions, _ProcMapEvent, _ProcMapRibbonEvent are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct MapPoint {
    int x;
    int y;
};
extern int near mapCursorState;
extern int near editHeight;
extern int near editWidth;
extern struct MapPoint far MapPnt;
extern int far mapYsize;
extern int far mapXsize;
extern int far just;
extern struct Rect far mapTileRect;
extern struct Rect far mapCursorRect;
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int width);

extern int far match_position;  /* scaffold reference for pool word C1E0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1E6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1E8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C1EA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C1EC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C1EE (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_InitMapFunctions(void);
void far pool_stub_ProcMapEvent(void);
void far pool_stub_ProcMapRibbonEvent(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitMapFunctions)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcMapEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcMapRibbonEvent)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitMapFunctions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1E0 C1E2 C1E4 C1E6 C1E8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitMapFunctions(void)
{
    volatile int t;

    t = match_position;
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

    t = Dx8;
}

void far DrawMapCursor(void)
{
    if (!win_IsWinOpen(0x100))
        return;
    if (mapCursorState != 0)
        return;
    clip_Push();
    clip_SetWin(0x100);
    mapCursorRect.top = mapYsize * MapPnt.y + mapTileRect.top;
    mapCursorRect.bottom = mapCursorRect.top + mapYsize * editHeight;
    mapCursorRect.left = mapXsize * MapPnt.x + mapTileRect.left + just;
    mapCursorRect.right = mapCursorRect.left + mapXsize * editWidth;
    GRectInvOutline(&mapCursorRect, 2);
    mapCursorState = 1;
    clip_Pop();
}

