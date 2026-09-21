/*
 * win_Close: hide a window object's window.  The window number is the
 * object's high byte; with a live handle in win_hwnd the bucket's open
 * flag (bit 1 of the byte at +0x1d) is cleared and the window hidden.
 * The next visible top-level window of the application (walking from
 * the root's top window, then its owner when it has one) is brought to
 * the top and told it is the active window (WM_NCACTIVATE with the far
 * activeAppFlag).
 */
struct WinBucket {
    unsigned char header[0x1d];
    unsigned char flags;
};

extern int near win_hwnd[];
extern struct WinBucket far * near win_handles[];
extern int near rootWnd;
extern int far activeAppFlag;

extern int far pascal ShowWindow(unsigned int window, int command);
extern unsigned int far pascal GetTopWindow(unsigned int window);
extern int far pascal IsWindowVisible(unsigned int window);
extern unsigned int far pascal GetNextWindow(unsigned int window, int flag);
extern unsigned int far pascal GetWindow(unsigned int window, int flag);
extern void far pascal BringWindowToTop(unsigned int window);
extern int far pascal PostMessage(unsigned int window, unsigned int message, unsigned int wParam, long lParam);

void far win_Close(int objectNumber)
{
    int near *handle;
    unsigned int top;
    unsigned int next;

    handle = &win_hwnd[objectNumber >> 8];
    if (*handle != 0) {
        win_handles[objectNumber >> 8]->flags &= 0xfd;
        ShowWindow(*handle, 0);
        next = GetTopWindow(rootWnd);
        if (next == 0)
            top = 0;
        else {
            while (!IsWindowVisible(next)) {
                next = GetNextWindow(next, 2);
                if (next == 0)
                    break;
            }
            if (next != 0 && GetWindow(next, 4) != 0)
                next = GetWindow(next, 4);
            top = next;
        }
        if (top != 0) {
            BringWindowToTop(top);
            PostMessage(top, 0x86, activeAppFlag, 0L);
        }
    }
}

