/* Candidate reconstruction of the window maximize wrapper. */
extern unsigned int near win_hwnd[];
extern int far pascal ShowWindow(unsigned int window, int command);

int win_Zoom(unsigned int object)
{
    return ShowWindow(win_hwnd[object >> 8], 3);
}
