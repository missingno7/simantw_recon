/* Keep traversal and result in distinct registers; pass INDEX as DS:offset. */
extern int near rootWnd;
extern int far pascal GetTopWindow(int window);
extern int far pascal IsWindowVisible(int window);
extern int far pascal GetNextWindow(int window, int command);
extern int far pascal GetWindow(int window, int command);
extern int far pascal GetProp(int window, char far *name);
static char near indexName[] = "INDEX";

int far win_IsWinInFront(int window)
{
    int hwnd;
    int propertyWindow;

    hwnd = GetTopWindow(rootWnd);
    if (!hwnd) {
        propertyWindow = 0;
    } else {
        while (!IsWindowVisible(hwnd)) {
            hwnd = GetNextWindow(hwnd, 2);
            if (!hwnd)
                break;
        }
        if (hwnd && GetWindow(hwnd, 4))
            hwnd = GetWindow(hwnd, 4);
        propertyWindow = hwnd;
    }
    if (propertyWindow && GetProp(propertyWindow, indexName) == window)
        return 1;
    return 0;
}
