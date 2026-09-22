/*
 * ResetEditScrollRange: keep the edit window's scrollbars in sync with
 * the map.  Nothing happens unless win_hwnd[0] (the edit window) exists.
 * When MapMode, editHeight or editWidth differ from the values cached at
 * the previous call (three private words, initialised to -1 at DGROUP
 * 0x14f8/0x14fa/0x14fc: ff ff ff ff ff ff), both scrollbar ranges are
 * recomputed with SetScrollRange: vertical 0..(0x40-editHeight),
 * horizontal 0..(0x40-editWidth) in map modes 2 and 3, else 0..(0x80-editWidth),
 * and the cache is refreshed.  Either way each bar's thumb is synced to
 * MapPnt.x / MapPnt.y when GetScrollPos reports it drifted.
 *
 * Unit profile /Og: the far address of MapMode is computed once, homed
 * on the frame (ENTER 4,0) and reloaded via LES after the first
 * SetScrollRange call; the source uses the plain far global.  The two
 * horizontal SetScrollRange calls share a cross-jumped tail (sub ax,editWidth/push/call).
 */
struct MapPoint {
    int x;
    int y;
};

extern int near win_hwnd;
extern int near editHeight;
extern int near editWidth;
extern int far MapMode;
extern struct MapPoint far MapPnt;

static int near lastMode = -1;
static int near lastEditHeight = -1;
static int near lastEditWidth = -1;

extern void far pascal SetScrollRange(int hwnd, int bar, int minPos, int maxPos, int redraw);
extern int far pascal SetScrollPos(int hwnd, int bar, int pos, int redraw);
extern int far pascal GetScrollPos(int hwnd, int bar);

void far ResetEditScrollRange(void)
{
    if (win_hwnd[0] == 0)
        return;

    if (MapMode != lastMode || lastEditHeight != editHeight || lastEditWidth != editWidth) {
        SetScrollRange(win_hwnd[0], 1, 0, 0x40 - editHeight, 1);
        if (MapMode != 2 && MapMode != 3)
            SetScrollRange(win_hwnd[0], 0, 0, 0x80 - editWidth, 1);
        else
            SetScrollRange(win_hwnd[0], 0, 0, 0x40 - editWidth, 1);
        lastMode = MapMode;
        lastEditHeight = editHeight;
        lastEditWidth = editWidth;
    }

    if (GetScrollPos(win_hwnd[0], 0) != MapPnt.x)
        SetScrollPos(win_hwnd[0], 0, MapPnt.x, 1);
    if (GetScrollPos(win_hwnd[0], 1) != MapPnt.y)
        SetScrollPos(win_hwnd[0], 1, MapPnt.y, 1);
}
