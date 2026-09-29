struct DialogEvent {
    unsigned char unused1[12];
    int object;
    unsigned char unused2[2];
};
struct ExpMenuPoint { int x, y; };
struct Rect { int left, top, right, bottom; };
struct WinRect { int left, top, right, bottom; };
struct WinBucket_2 {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};

extern struct WinBucket_2 far * near win_handles[];
extern int near win_hwnd[];
extern int near rootWnd;
extern int near ribbonBarHeight;
extern unsigned int near lastProxObj;
extern int far activeAppFlag;

extern int far pascal GetTopWindow(int window);
extern int far pascal IsWindowVisible(int window);
extern int far pascal GetNextWindow(int window, int relation);
extern int far pascal GetWindow(int window, int relation);
extern void far pascal GetWindowRect(unsigned int window, struct Rect far *rect);
extern int far pascal ClientToScreen(int window, struct ExpMenuPoint far *point);
extern int far pascal ScreenToClient(int window, struct ExpMenuPoint far *point);
extern void far pascal ShowWindow(int window, int command);
extern void far pascal BringWindowToTop(int window);
extern long far pascal SendMessage(int window, unsigned int message,
                                   unsigned int wParam, long lParam);

extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void GRectInv(struct WinRect *r);
extern void far win_Open(int object, int x, int y);
extern int far win_GetEvent(struct DialogEvent far *event);
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
    struct Rect screenRect;
    struct WinRect objectRect;
    struct ExpMenuPoint point;
    struct DialogEvent event;
    int result;
    int shortArm;
    int activeWindow;
    int windowIndex;
    int near *windowSlot;
    int window;
    int selected;
    int previous;

    result = -1;
    point.x = x;
    point.y = y;

    shortArm = (layer == -2);
    if (!shortArm) {
        GetWindowRect(rootWnd, &screenRect);
        win_LockWin(menu);
        objectRect = *win_handles[menu >> 8]->rects[(unsigned char)menu];
        if (ribbonBarHeight) {
            ++objectRect.right;
            ++objectRect.bottom;
        }
        win_UnlockWin(menu);

        activeWindow = GetTopWindow(rootWnd);
        while (activeWindow != 0 && !IsWindowVisible(activeWindow))
            activeWindow = GetNextWindow(activeWindow, 2);
        if (activeWindow != 0) {
            window = GetWindow(activeWindow, 4);
            if (window != 0)
                activeWindow = window;
            ClientToScreen(activeWindow, &point);
        }

        if (point.y + objectRect.bottom - objectRect.top > screenRect.bottom) {
            point.y += objectRect.top - objectRect.bottom;
            if (point.y < screenRect.top)
                point.y = screenRect.top;
        }
        if (point.x + objectRect.right - objectRect.left > screenRect.right) {
            point.x += objectRect.left - objectRect.right;
            if (point.x < screenRect.left)
                point.x = screenRect.left;
        }
        ScreenToClient(rootWnd, &point);
    }

    win_Open(menu, point.x, point.y);
    windowIndex = menu >> 8;
    windowSlot = &win_hwnd[windowIndex];
    window = *windowSlot;
    MySetCapture(window);

    if (layer == -1) {
        clip_Push();
        MSClipStart(*windowSlot);

        if (lastProxObj != 0xffff && (lastProxObj & 0xff) != 0) {
            previous = lastProxObj;
            win_LockWin(previous);
            GRectInv(win_handles[previous >> 8]->rects[(unsigned char)previous]);
            win_UnlockWin(previous);
        }

        if ((menu & 0xff) != 0) {
            win_LockWin(menu);
            GRectInv(win_handles[menu >> 8]->rects[(unsigned char)menu]);
            win_UnlockWin(menu);
        }

        MSClipEnd();
        lastProxObj = menu;
    } else {
        selected = menu + layer + 2;
        clip_Push();
        MSClipStart(win_hwnd[selected >> 8]);

        if (lastProxObj != 0xffff && (lastProxObj & 0xff) != 0) {
            previous = lastProxObj;
            win_LockWin(previous);
            GRectInv(win_handles[previous >> 8]->rects[(unsigned char)previous]);
            win_UnlockWin(previous);
        }

        if (selected != 0xffff && (selected & 0xff) != 0) {
            win_LockWin(selected);
            GRectInv(win_handles[selected >> 8]->rects[(unsigned char)selected]);
            win_UnlockWin(selected);
        }

        MSClipEnd();
        lastProxObj = selected;
    }
    clip_Pop();

    ButtonHeldInit();
    for (;;) {
        window = win_hwnd[windowIndex];
        if (window == 0 || !IsWindowVisible(window))
            break;

        if (!ButtonHeld())
            previous = lastProxObj;
        if (!win_GetEvent(&event))
            continue;
        if (previous < menu || previous >= menu + 0x100)
            continue;
        if (previous < menu + 2)
            break;
        result = previous - menu - 2;
        break;
    }

    MyReleaseCapture();
    window = *windowSlot;
    if (window != 0) {
        ((unsigned char far *)win_handles[windowIndex])[0x1d] &= 0xfd;
        ShowWindow(window, 0);
    }

    activeWindow = GetTopWindow(rootWnd);
    while (activeWindow != 0 && !IsWindowVisible(activeWindow))
        activeWindow = GetNextWindow(activeWindow, 2);
    if (activeWindow != 0) {
        window = GetWindow(activeWindow, 4);
        if (window != 0)
            activeWindow = window;
        BringWindowToTop(activeWindow);
        SendMessage(-1, 0x86, activeAppFlag, 0L);
    }

    lastProxObj = 0xffff;
    return result;
}

