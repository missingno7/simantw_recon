/*
 * MAINWNDPROC is the application's window procedure.  It routes the high
 * frequency paint, keyboard, mouse, activation, and command messages into
 * the simulation and window helpers, while leaving unhandled messages at
 * the default zero result used by this program's private frame.
 */
extern long far PaintStuff(unsigned hwnd, unsigned message,
                           unsigned wParam, long lParam, long extra);
extern void far DoMouse(unsigned hwnd, unsigned message,
                        unsigned wParam, long lParam);
extern void far DoKeyDown(unsigned key);
extern void far HelpKeyDown(unsigned key);
extern void far DoMenuEntry(unsigned menu, unsigned entry);
extern void far MenuQuit(void);
extern void far CleanUp(void);
extern void far UpdateEditIfBufInvalid(unsigned message, unsigned hwnd);
extern void far UpdateAllWindows(void);
extern void far UpdateEdit(void);
extern void far DrawMapCursor(void);
extern void far DrawYardData(void);
extern void far EraseMapCursor(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far win_IsWinOpen(int window);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinActive(int window);
extern void far win_Open(int window);
extern void far win_Close(int window);
extern void far win_FlushEvents(void);
extern void far StopSong(void);
extern void far PopMsg(void);
extern long far DefWindowProc(unsigned hwnd, unsigned message,
                              unsigned wParam, long lParam);
extern int far activeAppFlag;
extern int far captureWnd;
extern int near rootWnd;
extern int near mainRootWnd;
extern int near bHelp;
extern unsigned int near antCursor, digCursor, dropCursor, foodCursor;
extern unsigned int near magCursor, sprayCursor;

long far pascal MAINWNDPROC(unsigned hwnd, unsigned message,
                            unsigned wParam, long lParam)
{
    long result;

    result = 0L;
    switch (message) {
    case 0x000f:                    /* WM_PAINT */
        result = PaintStuff(hwnd, message, wParam, lParam, 0L);
        break;

    case 0x0010:                    /* WM_CLOSE */
        MenuQuit();
        CleanUp();
        break;

    case 0x0011:                    /* WM_QUERYENDSESSION */
        MenuQuit();
        result = 1L;
        break;

    case 0x001c:                    /* WM_TIMECHANGE */
        UpdateEditIfBufInvalid(message, hwnd);
        break;

    case 0x0020:                    /* WM_SETCURSOR */
        if (rootWnd != 0)
            DrawMapCursor();
        break;

    case 0x0024:                    /* WM_GETMINMAXINFO */
        UpdateEditIfBufInvalid(message, hwnd);
        break;

    case 0x0086:                    /* WM_NCACTIVATE */
        if (wParam != 0)
            UpdateAllWindows();
        break;

    case 0x0100:                    /* WM_KEYDOWN */
        if (bHelp)
            HelpKeyDown(wParam);
        else
            DoKeyDown(wParam);
        break;

    case 0x0101:                    /* WM_KEYUP */
        UpdateEdit();
        break;

    case 0x0112:                    /* WM_SYSCOMMAND */
        DoMenuEntry(wParam, (unsigned)lParam);
        break;

    case 0x0200:                    /* WM_MOUSEMOVE */
    case 0x0201:                    /* WM_LBUTTONDOWN */
    case 0x0202:                    /* WM_LBUTTONUP */
    case 0x0203:                    /* WM_LBUTTONDBLCLK */
    case 0x0204:                    /* WM_RBUTTONDOWN */
    case 0x0205:                    /* WM_RBUTTONUP */
        DoMouse(hwnd, message, wParam, lParam);
        break;

    default:
        if (message == 0x00a4)
            StopSong();
        else if (message == 0x0018 && win_IsWinOpen(mainRootWnd))
            UpdateAllWindows();
        else if (message == 0x001d && win_IsWinInFront(mainRootWnd))
            DrawYardData();
        else if (message == 0x001e && activeAppFlag)
            win_FlushEvents();
        else if (message == 0x0022 && captureWnd == hwnd)
            EraseMapCursor();
        else if (message == 0x0084 && win_IsWinActive(mainRootWnd)) {
            MSClipStart(mainRootWnd);
            MSClipEnd();
        } else if (message == 0x0206)
            win_Close(mainRootWnd);
        else if (message == 0x0207)
            win_Open(mainRootWnd);
        else if (message == 0x030f || message == 0x0310)
            PopMsg();
        else if (antCursor == 0xffff || digCursor == 0xffff ||
                 dropCursor == 0xffff || foodCursor == 0xffff ||
                 magCursor == 0xffff || sprayCursor == 0xffff)
            result = DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }
    return result;
}
