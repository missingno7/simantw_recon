/* Toggle the mini-map cursor: erase its current inverted outline when it is
 * shown, or recompute the map rectangle and draw it when hidden. */
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
