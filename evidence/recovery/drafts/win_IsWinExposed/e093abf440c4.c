/*
 * win_IsWinExposed: report whether an object's window overlaps the root
 * window.  The window handle comes from win_hwnd for the object's window
 * (object >> 8).  Its client rectangle is fetched and both corners are
 * converted to screen coordinates through a point, the root window's
 * screen rectangle is fetched, and the two are intersected; the window is
 * exposed when the intersection equals the whole client rectangle.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Point {
    int x;
    int y;
};

extern int near win_hwnd[];
extern int near rootWnd;

extern void far pascal GetClientRect(unsigned int window, struct Rect far *rect);
extern void far pascal ClientToScreen(unsigned int window, struct Point far *point);
extern void far pascal GetWindowRect(unsigned int window, struct Rect far *rect);
extern int far pascal IntersectRect(struct Rect far *dest, struct Rect far *a, struct Rect far *b);
extern int far pascal EqualRect(struct Rect far *a, struct Rect far *b);

int far win_IsWinExposed(int object)
{
    struct Rect client;
    struct Point point;
    struct Rect root;
    struct Rect overlap;

    GetClientRect(win_hwnd[object >> 8], &client);
    point.x = client.left;
    point.y = client.top;
    ClientToScreen(win_hwnd[object >> 8], &point);
    client.left = point.x;
    client.top = point.y;
    point.x = client.right;
    point.y = client.bottom;
    ClientToScreen(win_hwnd[object >> 8], &point);
    client.right = point.x;
    client.bottom = point.y;
    GetWindowRect(rootWnd, &root);
    IntersectRect(&overlap, &client, &root);
    return EqualRect(&overlap, &client);
}
