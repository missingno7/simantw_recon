/* Semantic reconstruction: require both a populated HWND slot and a true USER
 * zoom predicate; the short-circuit preserves the empty-slot fast path. */
extern int near win_hwnd[];
extern int far pascal IsZoomed(int window);
int win_IsWinZoomed(int window)
{
    int originalWindow;
    int near *windowPtr;
    originalWindow = window;
    windowPtr = &win_hwnd[originalWindow >> 8];
    if (*windowPtr != 0 && IsZoomed(*windowPtr) != 0)
        return 1;
    return 0;
}
