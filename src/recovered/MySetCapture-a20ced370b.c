/*
 * Save the caller's capture handle.  While the application is active and its
 * main window is not iconic, request capture for the caller's window.  Return
 * the captured handle only when its INDEX property is present.  These
 * near/far declarations follow the admitted capture
 * neighbours and the Win16 USER declarations used elsewhere in the unit.
 */
extern int near mainRootWnd;
extern int far captureWnd;
extern int far activeAppFlag;
extern int far pascal IsIconic(int window);
extern int far pascal SetCapture(int window);
extern int far pascal GetCapture(void);
extern unsigned int far pascal GetProp(int window, char far *name);

int far MySetCapture(int window)
{
    register int captured;

    captureWnd = window;
    captured = (activeAppFlag && !IsIconic(mainRootWnd))
        ? SetCapture(window) : GetCapture();
    if (captured != 0 && GetProp(captured, "INDEX") != 0)
        return captured;
    return 0;
}
