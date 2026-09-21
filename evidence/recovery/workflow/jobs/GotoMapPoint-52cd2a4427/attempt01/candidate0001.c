/*
 * GotoMapPoint: show map point (x, y) on the given plane.  While the map
 * window (0x100) is open its cursor is erased inside the window clip
 * (win_hwnd[1]).  On the current plane (a positive MapPlane) the edit
 * view is centred on the point and, when that moved it, the edit view is
 * updated and the far UDMapFlip flag cleared; otherwise the map plane and
 * location are set and an open map window is redrawn.  Finally the map
 * cursor is drawn again inside the clip when the window is open.
 */
extern int near win_hwnd[];
extern int near MapPlane;
extern int far UDMapFlip;

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern void far DrawMap(void);
extern void far DrawMapCursor(void);

void far GotoMapPoint(int plane, int x, int y)
{
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    if (MapPlane == plane && plane > 0) {
        if (CenterEdit(x, y)) {
            UpdateEdit();
            UDMapFlip = 0;
        }
    } else {
        SetMapPlaneLocation(plane, x, y);
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
}
