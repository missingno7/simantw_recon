/* Semantic reconstruction: compute the near HWND slot from the high handle byte;
 * preserve a single result for both the empty-slot and USER-false paths. */
extern int near win_hwnd[];
extern int far pascal IsZoomed(int window);

int win_IsWinZoomed(int window)
{
    int near *windowPtr;
    int originalWindow;
    int result;

    originalWindow = window;
    windowPtr = &win_hwnd[originalWindow >> 8];
    if (*windowPtr == 0)
        result = 0;
    else if (IsZoomed(*windowPtr) == 0)
        result = 0;
    else
        result = 1;
    return result;
}
