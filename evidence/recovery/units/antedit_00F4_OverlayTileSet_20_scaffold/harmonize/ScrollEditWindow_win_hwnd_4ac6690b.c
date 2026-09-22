/*
 * ScrollEditWindow: scroll the edit window so that map point (nx, ny)
 * replaces the current MapPnt.  The edit tile rectangle (far
 * editTileRect origin, editWidth by editHeight tiles of tileWidth by
 * tileHeight pixels) is scrolled by the tile difference, both as the
 * scroll and clip rectangle; the uncovered region is collected into a
 * temporary region, validated, the window updated, and the region then
 * invalidated for a later repaint before being deleted.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct MapPoint {
    int x;
    int y;
};

extern int near win_hwnd;
extern int near tileWidth;
extern int near tileHeight;
extern int near editWidth;
extern int near editHeight;
extern struct MapPoint far editTileRect;
extern struct MapPoint far MapPnt;

extern unsigned int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern void far pascal ScrollWindow(unsigned int window, int dx, int dy, struct Rect far *rect, struct Rect far *clip);
extern int far pascal GetUpdateRgn(unsigned int window, unsigned int region, int erase);
extern void far pascal ValidateRgn(unsigned int window, unsigned int region);
extern void far pascal UpdateWindow(unsigned int window);
extern void far pascal InvalidateRgn(unsigned int window, unsigned int region, int erase);
extern int far pascal DeleteObject(unsigned int object);

void far ScrollEditWindow(int nx, int ny)
{
    struct Rect rect;
    unsigned int region;

    region = CreateRectRgn(0, 0, 1, 1);
    rect.left = editTileRect.x;
    rect.top = editTileRect.y;
    rect.right = rect.left + tileWidth * editWidth;
    rect.bottom = rect.top + tileHeight * editHeight;
    ScrollWindow(win_hwnd[0], (nx - MapPnt.x) * tileWidth, (ny - MapPnt.y) * tileHeight, &rect, &rect);
    GetUpdateRgn(win_hwnd[0], region, 0);
    ValidateRgn(win_hwnd[0], region);
    UpdateWindow(win_hwnd[0]);
    InvalidateRgn(win_hwnd[0], region, 0);
    DeleteObject(region);
}
