struct ProxRect { int left; int top; int right; int bottom; };
struct ProxPoint { int x; int y; };
struct ProxEvent { int words[8]; };
struct ProxBucket { unsigned char header[0x2c]; struct ProxRect far *rects[256]; };

extern struct ProxBucket far * near win_handles[];
extern int near win_hwnd[];
extern int near rootWnd;
extern int near ribbonBarHeight;
extern unsigned int near lastProxObj;
extern int far activeAppFlag;

extern int far pascal GetTopWindow(int window);
extern int far pascal IsWindowVisible(int window);
extern int far pascal GetNextWindow(int window, int relation);
extern int far pascal GetWindow(int window, int relation);
extern void far pascal GetWindowRect(int window, struct ProxRect far *rect);
extern int far pascal ClientToScreen(int window, struct ProxPoint far *point);
extern int far pascal ScreenToClient(int window, struct ProxPoint far *point);
extern void far pascal ShowWindow(int window, int command);
extern void far pascal BringWindowToTop(int window);
extern long far pascal SendMessage(int window, unsigned int message,
                                   unsigned int wParam, long lParam);

extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far GRectInv(struct ProxRect far *rect);
extern int far win_Open(int objectNumber, int x, int y);
extern int far win_GetEvent(struct ProxEvent far *event);
extern int far ButtonHeld(void);
extern void far ButtonHeldInit(void);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);

int far win_DoProxMenu(int menu, int layer, int x, int y)
{
    struct ProxRect screen;
    struct ProxRect objectRect;
    struct ProxPoint point;
    struct ProxEvent event;
    struct ProxBucket far *bucket;
    int result;
    int active;
    int windowIndex;
    int selected;
    int previous;
    int window;

    result = -1;
    previous = -1;
    if (layer == -2) {
        layer = -1;
    } else {
        GetWindowRect(rootWnd, &screen);
        win_LockWin(menu);
        bucket = win_handles[menu >> 8];
        objectRect = *bucket->rects[(unsigned char)menu];
        if (ribbonBarHeight) {
            ++objectRect.right;
            ++objectRect.bottom;
        }
        win_UnlockWin(menu);

        active = GetTopWindow(rootWnd);
        while (active != 0 && !IsWindowVisible(active))
            active = GetNextWindow(active, 2);
        if (active != 0 && GetWindow(active, 4) != 0)
            active = GetWindow(active, 4);

        point.x = x;
        point.y = y;
        ClientToScreen(active, &point);
        if (point.y + objectRect.bottom - objectRect.top > screen.bottom) {
            point.y += objectRect.top - objectRect.bottom;
            if (point.y < screen.top)
                point.y = screen.top;
        }
        if (point.x + objectRect.right - objectRect.left > screen.right) {
            point.x += objectRect.left - objectRect.right;
            if (point.x < screen.left)
                point.x = screen.left;
        }
        ScreenToClient(rootWnd, &point);
        x = point.x;
        y = point.y;
    }

    win_Open(menu, x, y);
    windowIndex = menu >> 8;
    window = win_hwnd[windowIndex];
    MySetCapture(window);

    selected = menu;
    if (layer != -1)
        selected = menu + layer + 2;
    clip_Push();
    MSClipStart(window);
    if (lastProxObj != -1 && (lastProxObj & 0xff) != 0) {
        previous = lastProxObj;
        win_LockWin(previous);
        bucket = win_handles[previous >> 8];
        GRectInv(bucket->rects[(unsigned char)previous]);
        win_UnlockWin(previous);
    }
    if ((selected & 0xff) != 0) {
        win_LockWin(selected);
        bucket = win_handles[selected >> 8];
        GRectInv(bucket->rects[(unsigned char)selected]);
        win_UnlockWin(selected);
    }
    MSClipEnd();
    lastProxObj = selected;
    clip_Pop();

    ButtonHeldInit();
    for (;;) {
        window = win_hwnd[windowIndex];
        if (window == 0 || GetWindow(window, 0) == 0)
            break;
        if (!ButtonHeld())
            previous = lastProxObj;
        if (!win_GetEvent(&event))
            continue;
        selected = lastProxObj;
        if (selected < menu || selected >= menu + 0x100)
            continue;
        if (selected < menu + 2)
            break;
        result = selected - menu - 2;
        break;
    }

    MyReleaseCapture();
    bucket = win_handles[menu >> 8];
    ((unsigned char far *)bucket)[0x1d] &= 0xfd;
    ShowWindow(win_hwnd[windowIndex], 0);
    active = GetTopWindow(rootWnd);
    if (active == 0)
        selected = 0;
    else {
        while (active != 0 && !IsWindowVisible(active))
            active = GetNextWindow(active, 2);
        if (active != 0 && GetWindow(active, 4) != 0)
            active = GetWindow(active, 4);
        selected = active;
    }
    if (selected != 0) {
        BringWindowToTop(selected);
        SendMessage(-1, 0x86, activeAppFlag, 0L);
    }
    lastProxObj = -1;
    return result;
}
