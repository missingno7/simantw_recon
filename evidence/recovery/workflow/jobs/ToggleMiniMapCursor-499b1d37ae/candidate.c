/*
 * ToggleMiniMapCursor: flip the mini-map cursor rectangle between shown
 * and hidden.  When it is already shown (mmapCursorState != 0), erase it
 * with the same MSClipStart/GRectInvOutline/MSClipEnd sequence as
 * EraseMiniMapCursor and clear the flag.  When it is hidden, recompute
 * the cursor rectangle from the current map point the same way
 * DrawMiniMapCursor does (top/bottom scaled by miniYSize against
 * miniMapRect and editHeight, left/right scaled by miniXSize against
 * miniJust, miniMapRect and editWidth), draw it inverted inside the
 * mini-map window clip (win_hwnd[20]) and set the flag.
 */
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
extern int far miniXSize;
extern int far miniYSize;
extern int far miniJust;
extern struct MapPoint far MapPnt;
extern struct MiniMapRect far miniMapRect;
extern struct MiniMapRect far miniMapCursorRect;

extern void far MSClipStart(int window);
extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);
extern void far MSClipEnd(void);

void far ToggleMiniMapCursor(void)
{
    int ySize, xSize, top, left;

    if (mmapCursorState) {
        MSClipStart(win_hwnd[20]);
        GRectInvOutline(&miniMapCursorRect, 1);
        MSClipEnd();
        mmapCursorState = 0;
        return;
    }

    ySize = miniYSize;
    top = ySize * MapPnt.y + miniMapRect.top;
    miniMapCursorRect.top = top;
    miniMapCursorRect.bottom = top + ySize * editHeight;

    xSize = miniXSize;
    left = xSize * MapPnt.x + miniJust + miniMapRect.left;
    miniMapCursorRect.left = left;
    miniMapCursorRect.right = left + xSize * editWidth;

    MSClipStart(win_hwnd[20]);
    GRectInvOutline(&miniMapCursorRect, 1);
    MSClipEnd();
    mmapCursorState = 1;
}
