/*
 * Hypothesis: walk the root window's visible chain, select its owner/parent
 * through GetWindow(...,4), and identify the front window by the INDEX
 * property.  The packet's DS offset 0xbd0c was independently checked against
 * the original data and contains the literal "INDEX".
 */
extern int near rootWnd;
extern int far pascal GetTopWindow(int window);
extern int far pascal IsWindowVisible(int window);
extern int far pascal GetNextWindow(int window, int command);
extern int far pascal GetWindow(int window, int command);
extern int far pascal GetProp(int window, char far *name);

int far win_IsWinInFront(int window)
{
    int hwnd;
    register int front;

    front = 0;
    hwnd = GetTopWindow(rootWnd);
    if (!hwnd)
        goto done;

visible_loop:
    if (IsWindowVisible(hwnd))
        goto owner_check;
    hwnd = GetNextWindow(hwnd, 2);
    if (hwnd)
        goto visible_loop;

owner_check:
    if (hwnd) {
        if (GetWindow(hwnd, 4))
            hwnd = GetWindow(hwnd, 4);
    }

    front = hwnd;
done:
    if (!front)
        return 0;
    return GetProp(front, "INDEX") == window;
}
