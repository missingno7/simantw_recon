/*
 * ToggleMapCursor: erase or draw the inverted map-cursor rectangle
 * (mapCursorRect, a far PACK Rect at segment 9) depending on
 * mapCursorState.  State 1 means "shown": while the map window (0x100)
 * is open, erase it (GRectInvOutline color 2) inside a push/pop clip and
 * set state 0.  State 0 means "hidden": while the window is open,
 * recompute the rectangle from mapYsize/mapXsize scaled by MapPnt and
 * offset by mapTileRect (plus the far word "just" on the X axis), draw it
 * and set state 1.  Any other state (or a closed window) does nothing.
 * No locals: everything lives in registers, matching the missing
 * ENTER/LEAVE frame.
 */
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
extern struct Rect far mapTileRect;
extern int far mapYsize;
extern int far mapXsize;
extern int far just;
extern int near editHeight;
extern int near editWidth;

extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int color);

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
        mapCursorRect.left = mapXsize * MapPnt.x + mapTileRect.left + just;
        mapCursorRect.right = mapCursorRect.left + mapXsize * editWidth;

        GRectInvOutline(&mapCursorRect, 2);
        mapCursorState = 1;
        clip_Pop();
    }
}
