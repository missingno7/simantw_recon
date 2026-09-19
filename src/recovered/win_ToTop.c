/* Candidate reconstruction of the window z-order wrapper. */
extern unsigned int near win_hwnd[];
extern int far pascal BringWindowToTop(unsigned int window);

int win_ToTop(unsigned int object)
{
    return BringWindowToTop(win_hwnd[object >> 8]);
}
