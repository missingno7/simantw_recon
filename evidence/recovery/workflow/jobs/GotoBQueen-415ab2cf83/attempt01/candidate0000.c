/*
 * GotoBQueen: if the local player is currently a black queen (MeType ==
 * 0x60), jump the map view to the player's own location (MePlane,
 * MeLocX, MeLocY), following the same show-map-point logic as
 * GotoMapPoint (erase/redraw the map cursor inside the map window's
 * clip, either recenter the edit view when already on the current map
 * plane or switch plane/location and redraw the map).  Otherwise defer
 * to GotoQueen(0x60) (red queen path).
 */
extern int near win_hwnd[];
extern int near MapPlane;
extern int far UDMapFlip;

extern int near MeType;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern void far DrawMap(void);
extern void far DrawMapCursor(void);
extern void far GotoQueen(int value);

void far GotoBQueen(void)
{
    int plane, x, y;

    if (MeType == 0x60) {
        plane = MePlane;
        x = MeLocX;
        y = MeLocY;

        if (win_IsWinOpen(0x100)) {
            MSClipStart(win_hwnd[1]);
            EraseMapCursor();
            MSClipEnd();
        }
        if (plane == MapPlane && plane > 0) {
            if (CenterEdit(x, y))
                UpdateEdit();
            UDMapFlip = 0;
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
    } else {
        GotoQueen(0x60);
    }
}
