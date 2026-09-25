/* Semantic reconstruction: resolve the packed index through the near HWND table;
 * initialize false, and promote to true only when the nonempty HWND is zoomed. */
extern int near win_hwnd[];
extern int far pascal IsZoomed(int window);

int win_IsWinZoomed(int window)
{
    int near *windowPtr;
    int result;
    int originalWindow;

    originalWindow = window;
    windowPtr = &win_hwnd[originalWindow >> 8];
    result = 0;
    if (*windowPtr != 0) {
        if (IsZoomed(*windowPtr) != 0)
            result = 1;
    }
    return result;
}
