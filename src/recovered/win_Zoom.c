extern int near win_hwnd[];
extern void far pascal ShowWindow(int window, int command);

void win_Zoom(int window)
{
    ShowWindow(win_hwnd[window >> 8], 3);
}
