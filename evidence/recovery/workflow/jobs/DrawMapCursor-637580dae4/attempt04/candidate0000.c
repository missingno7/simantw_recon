/*
 * DrawMapCursor: draw the inverted outline of the edit-window cursor on
 * the map window (0x100) when that window is open and the cursor is not
 * already shown.  Inside a pushed clip set to the map window the cursor
 * rectangle is computed from the map tile origin: top = mapYsize *
 * MapPnt.y + mapTileRect.top, bottom = top + mapYsize * editHeight,
 * left = mapXsize * MapPnt.x + mapTileRect.left + just, right = left +
 * mapXsize * editWidth (the tile size and the computed edge are held in
 * locals); the outline is drawn two pixels wide, the
 * cursor state set to shown and the clip popped.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
#define R(field) r->field
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
    int size;
    int pos;
    struct Rect far *r;

    r = &mapCursorRect;
    if (!win_IsWinOpen(0x100))
        return;
    if (mapCursorState != 0)
        return;
    clip_Push();
    clip_SetWin(0x100);
    size = mapYsize;
    pos = size * MapPnt.y + mapTileRect.top;
    R(top) = pos;
    R(bottom) = pos + size * editHeight;
    size = mapXsize;
    pos = size * MapPnt.x + mapTileRect.left + just;
    R(left) = pos;
    R(right) = pos + size * editWidth;
    GRectInvOutline(r, 2);
    mapCursorState = 1;
    clip_Pop();
}
