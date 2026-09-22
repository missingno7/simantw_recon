extern int near win_hwnd[];
extern void far pascal BringWindowToTop(int window);

void win_ToTop(int window)
{
    BringWindowToTop(win_hwnd[window >> 8]);
}
