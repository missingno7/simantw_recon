/*
 * GBoxMove: scroll the box (x1, y1, x2, y2) of the clip window so that its
 * top-left corner lands at (nx, ny), then repaint what the scroll exposed.
 * A scratch region is created (CreateRectRgn, GDI 64), the box and clip
 * rectangles are filled from the four coordinates in the observed store
 * order, ScrollWindow (USER 61) moves the box by (nx - x1, ny - y1) inside
 * itself, GetUpdateRgn (USER 237) collects the exposed area into the
 * region without erasing, ValidateRgn (USER 128) accepts it, UpdateWindow
 * (USER 124) repaints and DeleteObject (GDI 69) frees the region.  All are
 * Pascal imports; clipWind is the near window handle.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near clipWind;
extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern void far pascal ScrollWindow(int window, int dx, int dy,
                                    struct WinRect far *rect,
                                    struct WinRect far *clip);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal ValidateRgn(int window, int region);
extern void far pascal UpdateWindow(int window);
extern int far pascal DeleteObject(int handle);

void far GBoxMove(int x1, int y1, int x2, int y2, int nx, int ny)
{
    struct WinRect box;
    struct WinRect clip;
    int region;

    region = CreateRectRgn(0, 0, 10, 10);
    box.left = x1;
    box.right = x2;
    box.top = y1;
    box.bottom = y2;
    clip.top = y1;
    clip.bottom = y2;
    clip.left = x1;
    clip.right = x2;
    ScrollWindow(clipWind, nx - x1, ny - y1, &box, &clip);
    GetUpdateRgn(clipWind, region, 0);
    ValidateRgn(clipWind, region);
    UpdateWindow(clipWind);
    DeleteObject(region);
}
