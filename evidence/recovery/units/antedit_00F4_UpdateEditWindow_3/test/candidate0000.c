/* Candidate translation unit antedit_00F4_UpdateEditWindow_3: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _UpdateEditWindow, _UpdateEditIfBufInvalid, _DrawEdit */

extern void far UpdateEdit(void);
extern int far editBufInvalidFlag;
extern int near win_hwnd;
extern int near editForce;
extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal ValidateRgn(int window, int region);
extern int far pascal UpdateWindow(int window);
extern int far pascal DeleteObject(int object);
extern void near DrawEdit(void);

void UpdateEditWindow(void)
{
    UpdateEdit();
}

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

void DrawEdit(void) {}

