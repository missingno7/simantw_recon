/*
 * DrawMapCursor: draw the inverted outline of the edit-window cursor on
 * the map window (0x100) when that window is open and the cursor is not
 * already shown.  Inside a pushed clip set to the map window the cursor
 * rectangle is computed from the map tile origin: top = mapYsize *
 * MapPnt.y + mapTileRect.top, bottom = top + mapYsize * editHeight,
 * left = mapXsize * MapPnt.x + mapTileRect.left + just, right = left +
 * mapXsize * editWidth, each pair computed in one expression with the
 * embedded assignment; the outline is drawn two pixels wide, the
 * cursor state set to shown and the clip popped.
 */
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
extern int far mapYsize;
extern int far mapXsize;
extern struct MapPoint far MapPnt;
extern struct Rect far mapTileRect;
extern struct Rect far mapCursorRect;
extern int far just;

extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int width);

void far DrawMapCursor(void)
{
    if (!win_IsWinOpen(0x100))
        return;
    if (mapCursorState != 0)
        return;
    clip_Push();
    clip_SetWin(0x100);
    mapCursorRect.bottom = (mapCursorRect.top = mapYsize * MapPnt.y + mapTileRect.top) + mapYsize * editHeight;
    mapCursorRect.right = (mapCursorRect.left = mapXsize * MapPnt.x + mapTileRect.left + just) + mapXsize * editWidth;
    GRectInvOutline(&mapCursorRect, 2);
    mapCursorState = 1;
    clip_Pop();
}
