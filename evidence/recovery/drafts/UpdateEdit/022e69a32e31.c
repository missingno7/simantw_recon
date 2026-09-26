/*
 * Keep the edit viewport's cached map position current.  When the cached and
 * live views overlap on the same map and terrain, scroll the existing pixels
 * and edit arrays; otherwise let the normal invalidation path redraw them.
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

extern int near win_hwnd[];
extern int near scrollBarFlag;
extern int near editForce;
extern int near editWidth;
extern int near editHeight;
extern int near tileWidth;
extern int near tileHeight;
extern int near MapPlane;
extern int far TERRAINset;
extern struct MapPoint far editTileRect;
extern struct MapPoint far MapPnt;

extern int far win_IsWinOpen(int window);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinExposed(int window);
extern void far ScrollEditArrays(int dx, int dy);
extern void near UpdateEditIfBufInvalid(void);
extern void far ResetEditScrollRange(int window);
extern void far DrawEditGraphs(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);

extern unsigned int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern void far pascal ScrollWindow(unsigned int window, int dx, int dy, struct Rect far *rect, struct Rect far *clip);
extern int far pascal GetUpdateRgn(unsigned int window, unsigned int region, int erase);
extern void far pascal ValidateRgn(unsigned int window, unsigned int region);
extern void far pascal UpdateWindow(unsigned int window);
extern void far pascal InvalidateRgn(unsigned int window, unsigned int region, int erase);
extern int far pascal DeleteObject(unsigned int object);

static int lastMapX = -1;
static int lastMapY = -1;
static int lastMapPlane = -1;
static int lastTerrain = -1;

void far UpdateEdit(void)
{
    struct Rect rect;
    unsigned int region;
    int dx;
    int dy;
    int currentTerrain;

    if (!win_IsWinOpen(0))
        return;

    if (scrollBarFlag) {
        region = CreateRectRgn(0, 0, 1, 1);
        rect.left = editTileRect.x;
        rect.top = editTileRect.y;
        rect.right = rect.left + tileWidth * editWidth;
        rect.bottom = rect.top + tileHeight * editHeight;
        dx = tileWidth * (lastMapX - MapPnt.x);
        dy = tileHeight * (lastMapY - MapPnt.y);
        ScrollWindow(win_hwnd[0], dx, dy, &rect, &rect);
        GetUpdateRgn(win_hwnd[0], region, 0);
        ValidateRgn(win_hwnd[0], region);
        UpdateWindow(win_hwnd[0]);
        InvalidateRgn(win_hwnd[0], region, 0);
        DeleteObject(region);
    } else if (lastMapX != -1 && lastMapY != -1 &&
               (lastMapX != MapPnt.x || lastMapY != MapPnt.y)) {
        int overlapsX;
        int overlapsY;

        overlapsX = lastMapX > MapPnt.x - editWidth &&
                    lastMapX < MapPnt.x + editWidth;
        overlapsY = lastMapY > MapPnt.y - editHeight &&
                    lastMapY < MapPnt.y + editHeight;
        if (overlapsX && overlapsY && MapPlane == lastMapPlane &&
            TERRAINset == lastTerrain && win_IsWinInFront(0) && win_IsWinExposed(0)) {
            region = CreateRectRgn(0, 0, 1, 1);
            rect.left = editTileRect.x;
            rect.top = editTileRect.y;
            rect.right = rect.left + tileWidth * editWidth;
            rect.bottom = rect.top + tileHeight * editHeight;
            dx = tileWidth * (lastMapX - MapPnt.x);
            dy = tileHeight * (lastMapY - MapPnt.y);
            ScrollWindow(win_hwnd[0], dx, dy, &rect, &rect);
            GetUpdateRgn(win_hwnd[0], region, 0);
            ValidateRgn(win_hwnd[0], region);
            UpdateWindow(win_hwnd[0]);
            InvalidateRgn(win_hwnd[0], region, 0);
            DeleteObject(region);
            ScrollEditArrays(lastMapX - MapPnt.x, lastMapY - MapPnt.y);
        }
    }

    currentTerrain = TERRAINset;
    if (currentTerrain != lastTerrain)
        editForce = 1;
    lastMapX = MapPnt.x;
    lastMapY = MapPnt.y;
    lastMapPlane = MapPlane;
    lastTerrain = currentTerrain;
    UpdateEditIfBufInvalid();
    editForce = 0;
    ResetEditScrollRange(win_hwnd[0]);
    MSClipStart(win_hwnd[0]);
    DrawEditGraphs();
    MSClipEnd();
}
