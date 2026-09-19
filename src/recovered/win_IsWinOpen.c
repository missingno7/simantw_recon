/* Candidate reconstruction of the visible-window predicate. */
extern unsigned int near win_hwnd[];
extern int far pascal IsWindowVisible(unsigned int window);

int win_IsWinOpen(unsigned int object)
{
    unsigned int near *address;
    address = &win_hwnd[object >> 8];
    if (*address && IsWindowVisible(*address)) return 1;
    return 0;
}
