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
extern void far SoundBlasterMessage(unsigned wParam, long lParam);
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
    if (message == 0x00a4) {
        SoundBlasterMessage(wParam, lParam);
        return 0L;
    }

    switch (message) {
    case 0x000f:                    /* WM_PAINT */
        return PaintStuff(hwnd, message, wParam, lParam, 0L);

    case 0x0010:                    /* WM_CLOSE */
        MenuQuit();
        CleanUp();
        return 0L;

    case 0x0011:                    /* WM_QUERYENDSESSION */
        MenuQuit();
        return 1L;

    case 0x001c:                    /* WM_TIMECHANGE */
        UpdateEditIfBufInvalid(message, hwnd);
        return 0L;

    case 0x0020:                    /* WM_SETCURSOR */
        if (rootWnd != 0)
            DrawMapCursor();
        return 0L;

    case 0x0024:                    /* WM_GETMINMAXINFO */
        UpdateEditIfBufInvalid(message, hwnd);
        return 0L;

    case 0x0086:                    /* WM_NCACTIVATE */
        if (wParam != 0)
            UpdateAllWindows();
        return 0L;

    case 0x0100:                    /* WM_KEYDOWN */
        if (bHelp)
            HelpKeyDown(wParam);
        else
            DoKeyDown(wParam);
        return 0L;

    case 0x0101:                    /* WM_KEYUP */
        UpdateEdit();
        return 0L;

    case 0x0112:                    /* WM_SYSCOMMAND */
        DoMenuEntry(wParam, (unsigned)lParam);
        return 0L;

    case 0x0200:                    /* WM_MOUSEMOVE */
    case 0x0201:                    /* WM_LBUTTONDOWN */
    case 0x0202:                    /* WM_LBUTTONUP */
    case 0x0203:                    /* WM_LBUTTONDBLCLK */
    case 0x0204:                    /* WM_RBUTTONDOWN */
    case 0x0205:                    /* WM_RBUTTONUP */
        DoMouse(hwnd, message, wParam, lParam);
        return 0L;

    case 0x0003:                    /* WM_MOVE */
    case 0x0005:                    /* WM_SIZE */
    case 0x0021:                    /* WM_MOUSEACTIVATE */
    case 0x0041:
    case 0x0102:                    /* WM_CHAR */
    case 0x0104:                    /* WM_SYSKEYDOWN */
    case 0x0105:                    /* WM_SYSKEYUP */
    case 0x0206:
    case 0x0207:
    case 0x0208:
    case 0x0209:
    case 0x020a:
    case 0x020b:
    case 0x020c:
    case 0x020d:
    case 0x020e:
    case 0x020f:
    case 0x0210:
    case 0x0211:
    case 0x0212:
    case 0x0213:
    case 0x0214:
    case 0x0215:
        DoMouse(hwnd, message, wParam, lParam);
        return 0L;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}
