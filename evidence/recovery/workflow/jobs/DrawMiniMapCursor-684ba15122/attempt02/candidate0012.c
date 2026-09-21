/*
 * DrawMiniMapCursor: place and draw the mini-map cursor rectangle.  Its
 * top is the map point row scaled by miniYSize plus the mini-map top, the
 * bottom that plus the edit view height scaled the same way; the left is
 * the map point column scaled by miniXSize plus the miniJust offset and
 * the mini-map left, the right that plus the scaled edit width.  The
 * rectangle is drawn as an inverted outline inside the mini-map window
 * clip (win_hwnd[20]) and the cursor state is marked shown.
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

void far DrawMiniMapCursor(void)
{
    int size;
    int edge;

    ySize = miniYSize;
    top = MapPnt.y * ySize + miniMapRect.top;
    miniMapCursorRect.top = top;
    miniMapCursorRect.bottom = top + editHeight * ySize;
    xSize = miniXSize;
    left = MapPnt.x * xSize + miniJust + miniMapRect.left;
    miniMapCursorRect.left = left;
    miniMapCursorRect.right = left + editWidth * xSize;
    MSClipStart(win_hwnd[20]);
    GRectInvOutline(&miniMapCursorRect, 1);
    MSClipEnd();
    mmapCursorState = 1;
}
