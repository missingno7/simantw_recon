extern int near win_hwnd[];
extern int far pascal IsWindowVisible(int window);

int win_IsWinOpen(int window)
{
    register int near *windowPtr;
    int originalWindow;

    originalWindow = window;
    windowPtr = &win_hwnd[originalWindow >> 8];
    if (*windowPtr == 0)
        return 0;
    return IsWindowVisible(*windowPtr) != 0;
}
