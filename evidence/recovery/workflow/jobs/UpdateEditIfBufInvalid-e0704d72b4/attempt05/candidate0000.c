/* UpdateEditIfBufInvalid: when the far edit-buffer-invalid flag is set,
 * build a 10x10 throwaway update region, validate/flush it against the
 * edit window, force a DrawEdit repaint, then clear the force flag.
 * DrawEdit is defined locally, ahead of UpdateEditIfBufInvalid (its own
 * admitted body is empty, per the antedit:00F4 unit), so the compiler
 * already knows DrawEdit's segment offset when it compiles the call and
 * bakes a literal same-segment relative displacement, matching the
 * target's fixup-free "call 0x238".
 */
extern int far editBufInvalidFlag;
extern int near win_hwnd;
extern int near editForce;

extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal ValidateRgn(int window, int region);
extern int far pascal UpdateWindow(int window);
extern int far pascal DeleteObject(int object);

void near DrawEdit(void) {}

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
