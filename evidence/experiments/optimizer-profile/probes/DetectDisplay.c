extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int window);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal ReleaseDC(int window, int dc);

int DetectDisplay(void)
{
    int window;
    int dc;

    window = GetDesktopWindow();
    dc = GetDC(window);
    if (GetDeviceCaps(dc, 12) == 1 && GetDeviceCaps(dc, 14) == 1) {
        ReleaseDC(window, dc);
        return 9;
    }
    ReleaseDC(window, dc);
    return 10;
}
