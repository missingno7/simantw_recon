/*
 * ResetEditScrollRange: keep the edit window's scrollbars in sync with
 * the map.  If win_hwnd[0] isn't open, do nothing.  When MapMode,
 * editHeight or editWidth have changed since the last call (each
 * cached, initially -1), recompute both scrollbar ranges: vertical
 * 0..(0x40-editHeight), horizontal 0..0x80 normally or 0..(0x40-editWidth)
 * when MapMode is 2 or 3, then remember the new MapMode/editHeight/
 * editWidth.  Either way, sync each scrollbar's thumb position to
 * MapPnt.x / MapPnt.y if it has drifted.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near win_hwnd[];
extern int near editHeight;
extern int near editWidth;
extern int near MapMode;
extern struct MapPoint far MapPnt;

static int near lastMode = -1;
static int near lastEditHeight = -1;
static int near lastEditWidth = -1;

extern void far pascal SetScrollRange(int hwnd, int bar, int minPos, int maxPos, int redraw);
extern int far pascal SetScrollPos(int hwnd, int bar, int pos, int redraw);
extern int far pascal GetScrollPos(int hwnd, int bar);

void far ResetEditScrollRange(void)
{
    int hMax;

    if (win_hwnd[0] == 0)
        return;

    if (MapMode != lastMode || lastEditHeight != editHeight || lastEditWidth != editWidth) {
        SetScrollRange(win_hwnd[0], 1, 0, 0x40 - editHeight, 1);
        if (MapMode == 2 || MapMode == 3)
            hMax = 0x40 - editWidth;
        else
            hMax = 0x80;
        SetScrollRange(win_hwnd[0], 0, 0, hMax, 1);
        lastMode = MapMode;
        lastEditHeight = editHeight;
        lastEditWidth = editWidth;
    }

    if (GetScrollPos(win_hwnd[0], 0) != MapPnt.x)
        SetScrollPos(win_hwnd[0], 0, MapPnt.x, 1);
    if (GetScrollPos(win_hwnd[0], 1) != MapPnt.y)
        SetScrollPos(win_hwnd[0], 1, MapPnt.y, 1);
}
