struct WinRect { int left; int top; int right; int bottom; };
struct WinPoint { int x; int y; };
struct MapPoint { int x; int y; };
extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;
extern int near tileWidth;
extern int near tileHeight;
extern int near rootWnd;
extern int near win_hwnd[];
extern void far pascal GetWindowRect(int window, struct WinRect far *rect);
extern int far win_GetObjRect(int object, struct WinRect far *rect);
extern int far pascal ClientToScreen(int window, struct WinPoint far *point);
extern int far pascal ScreenToClient(int window, struct WinPoint far *point);
extern void far win_Open(int object, int x, int y);
extern int far MySetCapture(int window);
extern void far win_FlushEvents(void);
extern void far ButtonHeldInit(void);
extern int far win_IsWinOpen(int window);
extern int far ButtonHeld(void);
extern int far win_IsWinInFront(int window);
extern void far pascal BringWindowToTop(int window);
extern void far MSClipStart(int window);
extern void far win_DrawWindow(int window);
extern void far MSClipEnd(void);
extern void far ButtonHeldEnd(void);
extern void far MyReleaseCapture(void);
extern void far win_Close(int window);
extern void far UpdateAllWindows(void);
static int magnifyX;
static int magnifyY;
static int magnifyPlane;

int far MagnifyMenu(int x, int y, int plane)
{
    int life;
    int px;
    int py;
    int extent;
    struct WinRect screen;
    struct WinRect object;
    struct WinPoint point;

    if (plane <= 1)
        life = LifeA[(x << 6) + y];
    else if (plane == 2)
        life = LifeB[(x << 6) + y];
    else
        life = LifeR[(x << 6) + y];
    if (life == 0)
        return -1;

    px = ((x - MapPnt.x) + 1) * tileWidth + editTileRect.left;
    py = ((y - MapPnt.y) - 1) * tileHeight + editTileRect.top;
    GetWindowRect(rootWnd, &screen);
    win_GetObjRect(0x1d00, &object);
    point.x = px;
    point.y = py;
    ClientToScreen(win_hwnd[0], &point);

    if ((extent = object.bottom,
         extent -= object.top,
         extent += point.y,
         extent) > screen.bottom) {
        point.y += object.top - object.bottom;
        if (point.y < screen.top)
            point.y = screen.top;
    }
    if ((extent = object.right,
         extent -= object.left,
         extent += point.x,
         extent) > screen.right) {
        point.x += object.left - object.right;
        if (point.x < screen.left)
            point.x = screen.left;
    }
    ScreenToClient(rootWnd, &point);

    magnifyX = x;
    magnifyY = y;
    magnifyPlane = plane;
    win_Open(0x1d00, point.x, point.y);
    MySetCapture(win_hwnd[0x1d]);
    win_FlushEvents();
    ButtonHeldInit();
    if (win_IsWinOpen(0x1d00)) {
        do {
            if (!ButtonHeld())
                break;
            if (!win_IsWinInFront(0x1d00)) {
                BringWindowToTop(win_hwnd[0x1d]);
                MSClipStart(win_hwnd[0x1d]);
                win_DrawWindow(0x1d00);
                MSClipEnd();
                MySetCapture(win_hwnd[0x1d]);
            }
        } while (win_IsWinOpen(0x1d00));
    }
    ButtonHeldEnd();
    MyReleaseCapture();
    win_Close(0x1d00);
    UpdateAllWindows();
    return life;
}

