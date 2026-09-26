/*
 * DrawMap: while the map window (0x100) is open, clip to it, recompute
 * mapCursorRect (an unresolved near-call target in this code group -- no
 * MAPSYM name is available; it is inferred purely from the values read
 * immediately after: the same far Rect at segment 9 that ToggleMapCursor
 * also derives from mapYsize/mapXsize/MapPnt/mapTileRect), then
 * invalidate its four 2px border strips (top, bottom, left, right) on
 * win_hwnd[1] via InvalidateRect (USER ordinal 125), UpdateWindow
 * (USER ordinal 124) it, redraw the population/health readouts
 * (DrawMapData) and release the clip.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near win_hwnd[];
extern struct Rect far mapCursorRect;

extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far CalcMapCursorRect(void);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect, int erase);
extern void far pascal UpdateWindow(int window);
extern void far DrawMapData(void);

void far DrawMap(void)
{
    struct WinRect rect;

    if (!win_IsWinOpen(0x100))
        return;
    clip_SetWin(0x100);
    CalcMapCursorRect();

    rect.left = mapCursorRect.left + 2;
    rect.top = mapCursorRect.top;
    rect.right = mapCursorRect.right - 2;
    rect.bottom = mapCursorRect.top + 2;
    InvalidateRect(win_hwnd[1], &rect, 0);

    rect.left = mapCursorRect.left + 2;
    rect.top = mapCursorRect.bottom - 2;
    rect.right = mapCursorRect.right - 2;
    rect.bottom = mapCursorRect.bottom;
    InvalidateRect(win_hwnd[1], &rect, 0);

    rect.top = mapCursorRect.top;
    rect.left = mapCursorRect.left;
    rect.right = mapCursorRect.left + 2;
    rect.bottom = mapCursorRect.bottom;
    InvalidateRect(win_hwnd[1], &rect, 0);

    rect.left = mapCursorRect.right - 2;
    rect.top = mapCursorRect.top;
    rect.right = mapCursorRect.right;
    rect.bottom = mapCursorRect.bottom;
    InvalidateRect(win_hwnd[1], &rect, 0);

    UpdateWindow(win_hwnd[1]);
    DrawMapData();
    clip_Off();
}
