/*
 * GotoMyAnt: scroll the map/edit view onto the player's ant.  LessonTemp
 * is set to 1 unconditionally.  In the "watch" game type (CurGameType ==
 * 3, where there is no player ant) just play the "can't" sound
 * (myBeginSound(1, 0, 0x7e)) and return.  Otherwise take a snapshot of
 * the ant's plane and near location (MePlane/MeLocX/MeLocY), erase the
 * map cursor inside the map window clip (win_hwnd[1]) if the map window
 * (0x100) is open, then either recentre the edit view (CenterEdit,
 * refreshing with UpdateEdit when it reports a change, and clearing
 * UDMapFlip) when already on the ant's plane, or switch to that plane
 * and location (SetMapPlaneLocation) and redraw the map if its window is
 * open.  Finally redraw the map cursor inside the clip if the map window
 * is open.  Mirrors the admitted CenterAnt/GotoMapPoint siblings in this
 * same SIMANT_MODULE object.
 */
extern int near win_hwnd[];
extern int near MapPlane;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int far LessonTemp;
extern int far CurGameType;
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

void far GotoMyAnt(void)
{
    int ex, ey, plane;

    LessonTemp = 1;
    if (CurGameType == 3) {
        myBeginSound(1, 0, 0x7e);
        return;
    }

    plane = MePlane;
    ex = MeLocX;
    ey = MeLocY;

    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    if (MapPlane == plane && plane > 0) {
        if (CenterEdit(ex, ey))
            UpdateEdit();
        UDMapFlip = 0;
    } else {
        SetMapPlaneLocation(plane, ex, ey);
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
}
