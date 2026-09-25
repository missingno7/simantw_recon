/*
 * Save the caller's capture handle.  While the application is active and its
 * main window is not iconic, request capture on the main window; otherwise
 * release capture.  Return the captured handle only when its INDEX property
 * is present.  These near/far declarations follow the admitted capture
 * neighbours and the Win16 USER declarations used elsewhere in the unit.
 */
extern int near mainRootWnd;
extern int far captureWnd;
extern int far activeAppFlag;
extern int far pascal IsIconic(int window);
extern int far pascal SetCapture(int window);
extern void far pascal ReleaseCapture(void);
extern int far pascal GetCapture(void);
extern unsigned int far pascal GetProp(int window, char far *name);

static char near capturePropName[] = "INDEX";

int far MySetCapture(int window)
{
    int captured;

    captureWnd = window;
    if (activeAppFlag && !IsIconic(mainRootWnd))
        SetCapture(mainRootWnd);
    else
        ReleaseCapture();

    captured = GetCapture();
    if (captured != 0 && GetProp(captured, capturePropName) != 0)
        return captured;
    return 0;
}
