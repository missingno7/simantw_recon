/* Candidate translation unit antedit_E100_ToggleMiniMapCursor_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ToggleMiniMapCursor
 * SCAFFOLDED: unclaimed members _MapAreaEvent, _OpenMiniMapWin are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct MiniMapRect {
    int left;
    int top;
    int right;
    int bottom;
};
struct MapPoint {
    int x;
    int y;
};
extern int near win_hwnd[];
extern int near editWidth;
extern int near editHeight;
extern int near mmapCursorState;
extern struct MapPoint far MapPnt;
extern int far miniXSize;
extern int far miniYSize;
extern struct MiniMapRect far miniMapRect;
extern int far miniJust;
extern struct MiniMapRect far miniMapCursorRect;
extern void far MSClipStart(int window);
extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);
extern void far MSClipEnd(void);

extern int far match_position;  /* scaffold reference for pool word C21E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C220 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C222 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C226 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C228 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C22A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far GamePaused;  /* scaffold reference for pool word C22C (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_MapAreaEvent(void);
void far pool_stub_OpenMiniMapWin(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MapAreaEvent)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_OpenMiniMapWin)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _MapAreaEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C21E C220 C222 C224 C226 C228 C22A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_MapAreaEvent(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
    t = pack_buf;
    t = *(int far *)&MapPnt;
    t = Scycle;
    t = EditColumns;
    t = Dx8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _OpenMiniMapWin.
 * It only reproduces the object's selector-pool allocation order for the
 * words C22C C22E C230 C232 C234 C236; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_OpenMiniMapWin(void)
{
    volatile int t;

    t = GamePaused;
    t = (int)miniYSize;
    t = (int)miniXSize;
    t = *(int far *)&miniMapRect;
    t = *(int far *)&miniMapCursorRect;
    t = (int)miniJust;
}

void far ToggleMiniMapCursor(void)
{
    if (mmapCursorState != 0) {
        MSClipStart(win_hwnd[20]);
        GRectInvOutline(&miniMapCursorRect, 1);
        MSClipEnd();
        mmapCursorState = 0;
        return;
    }

    miniMapCursorRect.top = miniYSize * MapPnt.y + miniMapRect.top;
    miniMapCursorRect.bottom = miniMapCursorRect.top + miniYSize * editHeight;
    miniMapCursorRect.left = miniXSize * MapPnt.x + miniJust + miniMapRect.left;
    miniMapCursorRect.right = miniMapCursorRect.left + miniXSize * editWidth;
    MSClipStart(win_hwnd[20]);
    GRectInvOutline(&miniMapCursorRect, 1);
    MSClipEnd();
    mmapCursorState = 1;
}

