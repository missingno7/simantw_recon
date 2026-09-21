/*
 * SetDefaultWindows: open the caste and mode tool windows and invalidate
 * their client areas (InvalidateRect is the USER ordinal-125 Pascal import;
 * the handles are the named near window-handle table entries win_hwnd[19]
 * and win_hwnd[18] at DGROUP 0xbccc/0xbcca), apply the current MapPlane
 * through SetMapPlane, then make sure the right view is open: with a
 * nonzero MapPlane the map window (0x100) is opened via YardToMap when
 * missing, otherwise the yard window (0x1900) via MapToYard.  Finally the
 * map title is refreshed and the edit window opened.  The same-segment
 * callees are far (LINK nop/push cs/call translation); win_IsWinOpen and
 * OpenEditWindow are far entries in other code groups.
 */
extern void far pascal InvalidateRect(int window, void far *rect,
                                      int erase);
extern int near win_hwnd[];
extern int near MapPlane;
extern void far OpenCasteWindow(void);
extern void far OpenModeWindow(void);
extern void far SetMapPlane(int plane);
extern int far win_IsWinOpen(int window);
extern void far YardToMap(void);
extern void far MapToYard(void);
extern void far SetMapTitle(void);
extern void far OpenEditWindow(void);

void far SetDefaultWindows(void)
{
    OpenCasteWindow();
    InvalidateRect(win_hwnd[19], 0, 0);
    OpenModeWindow();
    InvalidateRect(win_hwnd[18], 0, 0);
    SetMapPlane(MapPlane);
    if (MapPlane != 0) {
        if (!win_IsWinOpen(0x100))
            YardToMap();
    } else {
        if (!win_IsWinOpen(0x1900))
            MapToYard();
    }
    SetMapTitle();
    OpenEditWindow();
}
