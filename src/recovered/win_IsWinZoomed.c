/* Candidate reconstruction of the zoomed-window predicate. */
extern unsigned int near win_hwnd[];
extern int far pascal IsZoomed(unsigned int window);

int win_IsWinZoomed(unsigned int object)
{
    unsigned int near *address;
    address = &win_hwnd[object >> 8];
    if (*address && IsZoomed(*address)) return 1;
    return 0;
}
