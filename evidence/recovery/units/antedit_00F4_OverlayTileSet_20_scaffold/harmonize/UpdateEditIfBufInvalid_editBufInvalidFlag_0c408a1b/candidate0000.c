extern int far editBufInvalidFlag[];
extern int near win_hwnd;
extern int near editForce;

extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal ValidateRgn(int window, int region);
extern int far pascal UpdateWindow(int window);
extern int far pascal DeleteObject(int object);
extern void near DrawEdit(void);

void far UpdateEditIfBufInvalid(void)
{
    int region;

    if (!editBufInvalidFlag)
        return;

    region = CreateRectRgn(0, 0, 10, 10);
    GetUpdateRgn(win_hwnd, region, 0);
    ValidateRgn(win_hwnd, region);
    UpdateWindow(win_hwnd);
    DeleteObject(region);
    editForce = 1;
    DrawEdit();
    editForce = 0;
}
