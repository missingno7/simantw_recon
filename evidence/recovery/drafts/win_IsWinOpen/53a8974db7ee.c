extern int near win_hwnd[];
extern int far pascal IsWindowVisible(int);
int far win_IsWinOpen(int window) {
    int near * volatile slot;
    slot = &win_hwnd[window >> 8];
    if (*slot == 0) return 0;
    if (IsWindowVisible(*slot)) return 1;
    return 0;
}
