extern int near win_hwnd[];
extern int far pascal IsWindowVisible(int);
int far win_IsWinOpen(int window) {
    register int copy=window;
    volatile int near *slot=&win_hwnd[copy >> 8];
    if(slot[0] != 0) {
        if(IsWindowVisible(slot[0])) return 1;
    }
    return 0;
}
