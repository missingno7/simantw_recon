/* Return true only for an existing window that USER reports visible. */
extern int near win_hwnd[];
extern int far pascal IsWindowVisible(int window);
int win_IsWinOpen(int window)
{
    int near *hwnd = &win_hwnd[window >> 8];
    int result = 0;
    if (*hwnd != 0 && IsWindowVisible(*hwnd)) result = 1;
    return result;
}
