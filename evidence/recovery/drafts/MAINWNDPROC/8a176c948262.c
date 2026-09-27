struct WRect { int left, top, right, bottom; };
struct WPoint { int x, y; };
struct WFarRef { void far *address; };
struct WMouseEvent {
    unsigned message;
    unsigned window;
    unsigned object;
    unsigned flags;
    unsigned x;
    unsigned y;
    unsigned eventCode;
    unsigned eventData;
};
struct WPaintInfo {
    unsigned dc;
    int erase;
    struct WRect paintRect;
    int restore;
    int incremental;
    unsigned char reserved[16];
};

extern int near bHelp;
extern int near activeAppFlag;
extern int near captureWnd;
extern int near rootWnd;
extern int near mainRootWnd;
extern int near ribbonBarWnd;
extern int near screenWidth;
extern int near screenHeight;
extern int near editWidth;
extern int near editHeight;
extern int near paletteFlag;
extern int near paletteH;
extern unsigned long near lpTimerFunc;
extern unsigned near hInst;
extern unsigned near win_hwnd[];
extern unsigned near antCursor, digCursor, dropCursor, foodCursor;
extern unsigned near magCursor, sprayCursor, rockCursor;
extern unsigned far hHelpCursor;
extern char far versionStr[];

extern long far PaintStuff(unsigned, unsigned, unsigned, long, long);
extern void far SoundBlasterMessage(unsigned, unsigned, unsigned);
extern void far UpdateEditIfBufInvalid(unsigned, unsigned);
extern void far UpdateEdit(void);
extern void far UpdateAllWindows(void);
extern void far DrawMapCursor(void);
extern void far DrawYardData(void);
extern void far EraseMapCursor(void);
extern void far MSClipStart(int);
extern void far MSClipEnd(void);
extern void far StopSong(void);
extern void far PopMsg(void);
extern void far DoKeyDown(unsigned, unsigned, unsigned, unsigned);
extern void far HelpKeyDown(unsigned, unsigned, unsigned, unsigned);
extern void far pascal DoMouse(unsigned, unsigned, unsigned, unsigned, unsigned);
extern void far DoMenuEntry(unsigned);
extern void far DoEditScroll(unsigned, unsigned, unsigned, unsigned);
extern int far MenuQuit(void);
extern void far CleanUp(void);
extern void far MciMessage(unsigned, unsigned, unsigned, unsigned);
extern void far SetUpPalette(int);
extern int far win_IsWinOpen(int);
extern int far win_IsWinInFront(int);
extern int far win_IsWinActive(int);
extern void far win_Open(int);
extern void far win_Close(int);
extern void far win_FlushEvents(void);
extern void far win_Recalc(int);
extern int far win_LockWin(int);
extern void far win_UnlockWin(int);
extern void far win_GetObjRect(int, struct WRect far *);
extern void far * far win_WinAddr(int);
extern int far win_FindObject(struct WPoint far *);
extern void far * far win_ObjAddr(int);
extern void far win_ObjInv(int);
extern void far win_SetProxItem(int, int);
extern int far win_GetProxEvent(int);
extern int far win_Swap(int, int);
extern unsigned far MyGetTopWindow(int);
extern void far MyReleaseCapture(void);
extern void far MySetCapture(int);
extern void far YardToMap(void);
extern void far AdjustWndMinMax(unsigned, unsigned);
extern void far MYTIMERFUNC(unsigned, unsigned, unsigned, unsigned);

extern int far pascal BeginPaint(unsigned, struct WPaintInfo far *);
extern int far pascal EndPaint(unsigned, struct WPaintInfo far *);
extern int far pascal GetClientRect(unsigned, struct WRect far *);
extern int far pascal GetStockObject(int);
extern int far pascal FillRect(unsigned, struct WRect far *, unsigned);
extern int far pascal TextOut(unsigned, int, int, char far *, int);
extern int far pascal GetTextExtent(unsigned, char far *, int);
extern int far pascal InvalidateRect(unsigned, struct WRect far *, int);
extern int far pascal UpdateWindow(unsigned);
extern int far pascal SetWindowPos(unsigned, unsigned, int, int, int, int, unsigned);
extern int far pascal GetProp(unsigned, char far *);
extern int far pascal SetProp(unsigned, char far *, unsigned);
extern int far pascal GetCapture(void);
extern int far pascal SetCapture(unsigned);
extern int far pascal ReleaseCapture(void);
extern int far pascal SetFocus(unsigned);
extern int far pascal SendMessage(unsigned, unsigned, unsigned, long);
extern int far pascal BringWindowToTop(unsigned);
extern int far pascal GetWindow(unsigned, unsigned);
extern int far pascal GetNextWindow(unsigned, unsigned);
extern int far pascal IsWindowVisible(unsigned);
extern int far pascal IsZoomed(unsigned);
extern int far pascal IsIconic(unsigned);
extern int far pascal GetAsyncKeyState(int);
extern int far pascal SetTimer(unsigned, unsigned, unsigned, unsigned long);
extern int far pascal KillTimer(unsigned, unsigned);
extern int far pascal GetSystemMetrics(int);
extern int far pascal GetVersion(void);
extern int far pascal GetFreeSpace(unsigned);
extern int far pascal GetClassWord(unsigned, int);
extern int far pascal GetWindowText(unsigned, char far *, int);
extern int far pascal GetWindowTextLength(unsigned);
extern int far pascal ClientToScreen(unsigned, struct WPoint far *);
extern int far pascal ScreenToClient(unsigned, struct WPoint far *);
extern int far pascal WindowFromPoint(struct WPoint);
extern int far pascal GetDC(unsigned);
extern int far pascal ReleaseDC(unsigned, unsigned);
extern int far pascal SelectPalette(unsigned, unsigned, int);
extern int far pascal RealizePalette(unsigned);
extern int far pascal EnumChildWindows(unsigned, unsigned, unsigned long, long);
extern int far pascal MessageBox(unsigned, char far *, char far *, unsigned);
extern int far pascal ShowWindow(unsigned, int);
extern int far pascal DefWindowProc(unsigned, unsigned, unsigned, long);

long far pascal MAINWNDPROC(unsigned hwnd, unsigned message,
                            unsigned wParam, long lParam)
{
    struct WPaintInfo paintInfo;
    struct WRect clientRect;
    struct WRect objectRect;
    struct WRect resizeRect;
    struct WPoint point;
    struct WPoint screenPoint;
    struct WFarRef objectReference;
    struct WFarRef windowReference;
    struct WMouseEvent mouseEvent;
    char windowText[128];
    char classText[128];
    char captionText[128];
    unsigned dc;
    unsigned child;
    unsigned topWindow;
    unsigned oldCapture;
    unsigned keyFlags;
    int result;
    int i;
    int stateA;
    int stateB;
    int stateC;
    int stateD;
    int stateE;

    if (message == 0x00a4 || message == 0x0204) {
        if (bHelp == 0) {
            bHelp = 1;
            SetCursor(hHelpCursor);
        } else {
            bHelp = 0;
            SetCursor((unsigned)GetClassWord(hwnd, -12));
        }
        return 0L;
    }

    switch (message) {
    case 0x0003:
    case 0x0005:
        UpdateEditIfBufInvalid(message, hwnd);
        if (hwnd == rootWnd) {
            GetClientRect(hwnd, &clientRect);
            if (message == 0x0005 && activeAppFlag != 0) {
                screenWidth = clientRect.right - clientRect.left;
                screenHeight = clientRect.bottom - clientRect.top;
                SetWindowPos(mainRootWnd, 0, 0, 0, screenWidth,
                             screenHeight, 6);
                InvalidateRect(mainRootWnd, 0, 1);
                UpdateWindow(mainRootWnd);
            }
            if (ribbonBarWnd != 0)
                UpdateWindow(ribbonBarWnd);
        }
        return 0L;

    case 0x000f:
        dc = BeginPaint(hwnd, &paintInfo);
        GetClientRect(hwnd, &clientRect);
        result = GetTextExtent(dc, versionStr, 0x17);
        GetStockObject(2);
        FillRect(dc, &clientRect, GetStockObject(2));
        TextOut(dc, (clientRect.right - result) / 2,
                (clientRect.bottom - editHeight) / 2,
                versionStr, 0x17);
        PaintStuff(hwnd, message, wParam, lParam, dc);
        EndPaint(hwnd, &paintInfo);
        return 0L;

    case 0x0010:
        if (rootWnd != 0) {
            KillTimer(rootWnd, 0x11);
            win_Close(rootWnd);
        }
        MenuQuit();
        CleanUp();
        return 0L;

    case 0x0011:
        if (rootWnd != 0)
            KillTimer(rootWnd, 0x11);
        if (MenuQuit() != 0)
            CleanUp();
        return 1L;

    case 0x001c:
        if (rootWnd != 0) {
            UpdateEditIfBufInvalid(message, hwnd);
            if (activeAppFlag == 0) {
                SetUpPalette(1);
                activeAppFlag = 1;
            }
            GetClientRect(rootWnd, &clientRect);
            SetWindowPos(rootWnd, 0, 0, 0, clientRect.right,
                         clientRect.bottom, 6);
            if (ribbonBarWnd != 0)
                InvalidateRect(ribbonBarWnd, 0, 1);
        }
        return 0L;

    case 0x0020:
        if (rootWnd != 0) {
            if (bHelp != 0)
                SetCursor(hHelpCursor);
            else if (wParam == rootWnd)
                SetCursor(antCursor);
            else
                SetCursor(magCursor);
            DrawMapCursor();
        }
        return 0L;

    case 0x0021:
        if (rootWnd != 0 && win_IsWinInFront(wParam))
            SetFocus(rootWnd);
        if (captureWnd != 0)
            SetCapture(captureWnd);
        return 0L;

    case 0x0022:
        topWindow = MyGetTopWindow(rootWnd);
        if (topWindow != 0 && topWindow != hwnd)
            BringWindowToTop(topWindow);
        return 0L;

    case 0x0024:
        AdjustWndMinMax(hwnd, (unsigned)(lParam >> 16));
        return 0L;

    case 0x001d:
        result = GetFreeSpace(0);
        if (result < 0x4000)
            PopMsg();
        return 0L;

    case 0x0086:
        UpdateEditIfBufInvalid(message, hwnd);
        if (wParam != 0) {
            activeAppFlag = 1;
            UpdateAllWindows();
            DrawMapCursor();
        } else {
            activeAppFlag = 0;
            EraseMapCursor();
            UpdateAllWindows();
        }
        return 0L;

    case 0x0100:
        DoKeyDown(hwnd, message, wParam, (unsigned)(lParam >> 16));
        return 0L;

    case 0x0101:
        UpdateEdit();
        return 0L;

    case 0x0111:
        if ((wParam & 0xff00) == 0xfd00)
            DoMenuEntry(wParam);
        else
            DoMenuEntry(wParam);
        return 0L;

    case 0x0112:
        DoMenuEntry(wParam);
        return 0L;

    case 0x0113:
        if (hwnd == rootWnd)
            MYTIMERFUNC(hwnd, message, wParam, (unsigned)(lParam >> 16));
        else if (wParam == 0xaa)
            StopSong();
        else
            UpdateEditIfBufInvalid(message, hwnd);
        return 0L;

    case 0x0114:
    case 0x0115:
        DoEditScroll(hwnd, message, wParam, (unsigned)(lParam >> 16));
        if (GetAsyncKeyState(0x11) < 0)
            SendMessage(rootWnd, 0x115, wParam, lParam);
        return 0L;

    case 0x0200:
        oldCapture = GetCapture();
        if (oldCapture == 0) {
            point.x = (int)(short)lParam;
            point.y = (int)(short)(lParam >> 16);
            ClientToScreen(hwnd, &point);
            screenPoint = point;
            child = WindowFromPoint(screenPoint);
            if (child != 0 && child != hwnd) {
                GetWindowText(child, windowText, 0x80);
                GetClientRect(child, &resizeRect);
                objectReference.address = win_WinAddr(child);
                windowReference.address = win_WinAddr(hwnd);
                if (objectReference.address != 0 && windowReference.address != 0)
                    win_Recalc(child);
                objectRect = resizeRect;
                GetClassWord(child, 0);
                win_FlushEvents();
            }
        }
        DoMouse(message, hwnd, wParam, (unsigned)lParam, (unsigned)(lParam >> 16));
        return 0L;

    case 0x0201:
    case 0x0202:
    case 0x0203:
    case 0x0205:
        if (captureWnd == 0 && message == 0x0201)
            MySetCapture(hwnd);
        mouseEvent.message = message;
        mouseEvent.window = hwnd;
        mouseEvent.object = wParam;
        mouseEvent.flags = (unsigned)(lParam >> 16);
        mouseEvent.x = (unsigned)(int)(short)lParam;
        mouseEvent.y = (unsigned)(int)(short)(lParam >> 16);
        stateA = (int)mouseEvent.message;
        stateB = (int)mouseEvent.window;
        stateC = (int)mouseEvent.object;
        stateD = (int)mouseEvent.x;
        stateE = (int)mouseEvent.y;
        DoMouse(mouseEvent.message, mouseEvent.window, mouseEvent.object,
                (unsigned)lParam, mouseEvent.flags);
        if (message == 0x0205 && captureWnd != 0)
            MyReleaseCapture();
        return 0L;

    case 0x030f:
        dc = GetDC(hwnd);
        if (paletteH != 0) {
            SelectPalette(dc, paletteH, 0);
            RealizePalette(dc);
            ReleaseDC(hwnd, dc);
        }
        return 0L;

    case 0x0310:
        GetWindowText(hwnd, classText, 0x80);
        return 0L;

    case 0x0311:
        GetWindowText(hwnd, captionText, 0x80);
        GetWindowTextLength(hwnd);
        GetProp(hwnd, versionStr);
        return 0L;

    case 0x03bb:
        MciMessage(hwnd, message, wParam, (unsigned)lParam);
        return 0L;

    default:
        break;
    }

    if (message == 0x0200 && win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }

    if (message == 0x0200 && mainRootWnd != 0)
        win_GetObjRect(mainRootWnd, &objectRect);

    return DefWindowProc(hwnd, message, wParam, lParam);
}
