/*
 * GotoSpider: scroll the map/edit view onto the spider.  If the spider is
 * not currently active (SpidOn == 0), just play the "can't" sound
 * (myBeginSound(1, 0, 0x7e)) and return without touching the view.
 * Otherwise compute the spider's tile coordinates (SpidX/SpidY are pixel
 * coordinates; >>4 converts to tile units), erase the map cursor inside
 * the map window clip (win_hwnd[1]) if the map window (0x100) is open,
 * then either recenter the edit view (CenterEdit, refreshing with
 * UpdateEdit when it reports a change, and clearing UDMapFlip) when
 * already on plane 1, or switch to plane 1 at that location
 * (SetMapPlaneLocation) and redraw the map if its window is open.
 * Finally redraw the map cursor inside the clip if the map window is
 * open.  Mirrors the admitted CenterAnt/GotoMapPoint siblings in this
 * same SIMANT_MODULE object.
 */
extern int near win_hwnd[];
extern int near volatile MapPlane;
extern int near SpidX;
extern int near SpidY;
extern int far SpidOn;
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
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

void far GotoSpider(void)
{
    int ex, ey;

    if (!SpidOn) {
        myBeginSound(1, 0, 0x7e);
        return;
    }

    ex = SpidX >> 4;
    ey = SpidY >> 4;

    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    if (MapPlane == 1) {
        if (CenterEdit(ex, ey))
            UpdateEdit();
        UDMapFlip = 0;
    } else {
        SetMapPlaneLocation(1, ex, ey);
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
}
