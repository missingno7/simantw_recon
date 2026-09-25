/*
 * CenterAnt: scroll the map view to the player's ant.  If the map window
 * (0x100) is open, the map cursor is erased inside a clip on the map
 * window handle (win_hwnd[1]).  The far PACK word LessonTemp is set to 1,
 * the map plane is switched to the ant's plane (near MePlane) when it
 * differs from MapPlane, and CenterEdit centres the edit view on the ant's
 * near location words MeLocX/MeLocY, refreshing with UpdateEdit when it
 * reports a change.  Finally, with the map window open, the map cursor is
 * redrawn inside the same clip.  SetMapPlane is a same-code-group far call
 * (LINK translation); the others are far entries in other code groups.
 */
extern int near win_hwnd[];
extern int far LessonTemp;
extern int near MapPlane;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);
extern void far SetMapPlane(int plane);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);

void far CenterAnt(void)
{
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        MSClipEnd();
    }
    LessonTemp = 1;
    if (MePlane != MapPlane)
        SetMapPlane(MePlane);
    if (CenterEdit(MeLocX, MeLocY))
        UpdateEdit();
    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }
}
