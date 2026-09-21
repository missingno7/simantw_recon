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
extern int far pascal GetProp(int window, char near *name);

int far win_IsWinInFront(int window)
{
    int hwnd;

    hwnd = GetTopWindow(rootWnd);
    if (hwnd) {
        while (!IsWindowVisible(hwnd)) {
            hwnd = GetNextWindow(hwnd, 2);
            if (!hwnd)
                break;
        }
        if (hwnd) {
            if (GetWindow(hwnd, 4) == 0)
                hwnd = 0;
            else
                hwnd = GetWindow(hwnd, 4);
        }
    }
    if (!hwnd)
        return 0;
    return GetProp(hwnd, "INDEX") == window;
}
