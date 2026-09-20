extern int near win_hwnd[];
extern int far pascal IsZoomed(int window);

int win_IsWinZoomed(int window)
{
    register int near *windowPtr;
    int originalWindow;

    originalWindow = window;
    windowPtr = &win_hwnd[originalWindow >> 8];
    if (*windowPtr == 0)
        return 0;
    return IsZoomed(*windowPtr) != 0;
}
