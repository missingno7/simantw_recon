/* Resolve the packed window number to its HWND; null windows are closed. */
extern int near win_hwnd[];
extern int far pascal IsWindowVisible(int window);
int win_IsWinOpen(int window)
{
    int copy = window;
    int near *hwnd = &win_hwnd[copy >> 8];
    if (*hwnd != 0) {
        if (IsWindowVisible(*hwnd)) return 1;
    }
    return 0;
}
