extern int far editBufInvalidFlag;
extern int near scrollBarFlag;
extern int near editForce;
extern int near win_hwnd;
extern int far pascal InvalidateRect(int window, struct WinRect far *rect,
                                     int erase);

void InvalidUpdateEdit(void)
{
    if (editBufInvalidFlag && !scrollBarFlag) {
        editForce = 1;
        InvalidateRect(win_hwnd, (void far *)0, 0);
    }
}
