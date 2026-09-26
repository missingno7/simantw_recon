extern int near win_hwnd[];
extern int far pascal IsWindowVisible(int);
int far win_IsWinOpen(int window) {
    register volatile int copy=window;
    int near *slot;
    slot=&win_hwnd[copy >> 8];
    if(*slot != 0) { if(IsWindowVisible(*slot)) return 1; }
    return 0;
}
