struct ExpMenuPoint { int x, y; };
union WFreeSpaceWords {
    unsigned long value;
    struct { unsigned low, high; } words;
};
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct WinRect { int left; int top; int right; int bottom; };
struct WRect { int left, top, right, bottom; };
struct WBucket {
    int outerRight, outerBottom, innerRight, innerBottom;
    unsigned char reserved[0x24];
    struct WRect far *rects[256];
};
struct WChangeInfo { struct WRect bounds; int flags; };
struct WSizeUpdate { int width, height, ribbonHeight, flags; };
struct WPoint { int x, y; };
struct MinMaxInfo {
    int reservedX, reservedY;
    int maxSizeX, maxSizeY;
    int maxPositionX, maxPositionY;
    int minTrackSizeX, minTrackSizeY;
    int maxTrackSizeX, maxTrackSizeY;
};
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

static int submenuWindow[8] = { -1, 0x0c, 0x0f, 0x10, 0x11, 0x0d, 0x0e, -1 };

extern int far popUpMenuId;
extern int far editBuf;
extern void far mem_Free(int);
extern int near bHelp;
extern int far activeAppFlag;

extern int far captureWnd;

extern int near rootWnd;
extern int near mainRootWnd;
extern int near ribbonBarWnd;
extern int near screenWidth;
extern int near screenHeight;
extern int near editWidth;
extern int near editHeight;
extern int near paletteFlag;
extern int near paletteH;
extern void (far * near lpTimerFunc)(void);
extern int near hInst;

extern const int near win_hwnd[];
extern int far CurGameType, CurExpTool;
extern unsigned near antCursor, digCursor, dropCursor, foodCursor;
extern unsigned near magCursor, sprayCursor, rockCursor;
extern int far hHelpCursor;

struct MAINWND_VERSION_TABLE {
    char far *initialTargets[120];
    unsigned int header[2];
};
extern struct MAINWND_VERSION_TABLE
    __based(__segname("SIMANT_DATA_GROUP")) versionStr;
extern char near mainWndTitle[];
extern char near mainWndPropertyIndex0[];
extern char near capturePrompt[];
extern char near captureTitle0[];
extern char near captureTitle1[];
extern char near noCaptureMessage[];
extern int far sprintf(char far *, char far *, ...);

typedef void (far *PaintCallback)(void);
extern long far PaintStuff(int window, int message, unsigned int wParam,
                    unsigned long lParam, PaintCallback callback);

extern void far SoundBlasterMessage(unsigned int wMsg, unsigned long dwParam);

extern void far UpdateEditIfBufInvalid(void);
extern void far UpdateEdit(void);
extern void far UpdateAllWindows(void);
extern void far DrawMapCursor(void);
extern void far DrawYardData(void);
extern void far DrawMapData(void);
extern void far UpdateLayQueenModeDisplay(void);
extern void far EraseMapCursor(void);
extern void far MSClipStart(int);
extern void far MSClipEnd(void);
extern void far StopSong(void);
extern void PopMsg(char far *text);

extern void far DoKeyDown(unsigned, unsigned, unsigned, unsigned);
extern int far HelpKeyDown(unsigned int window, int key);

extern void far pascal DoMouse(unsigned, unsigned, unsigned, unsigned, unsigned);
extern void far DoMenuEntry(unsigned);
extern void far DoEditScroll(unsigned, unsigned, unsigned, long);
extern int MenuQuit(void);

extern void far CleanUp(void);
extern void far MciMessage(unsigned, unsigned, unsigned, unsigned);
extern void near SetUpPalette(int);
extern int far win_IsWinOpen(int);
extern int far win_IsWinInFront(int);
extern int far win_IsWinActive(int);
extern void far win_Open(int, int, int);
extern void far win_Close(int);
extern void far win_FlushEvents(void);
extern void far win_Recalc(int);
extern void far win_LockWin(int);

extern void far win_UnlockWin(int);
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern void far *win_WinAddr(int id);

extern int far win_FindObject(int, struct WPoint far *);
extern void far * far win_ObjAddr(int);
extern void win_ObjInv(int objectNumber);

extern void far win_SetProxItem(int);
extern unsigned int far win_GetProxEvent(void);
extern void far win_Swap(int first, int second);

extern int far MyGetTopWindow(int window);

extern void far MyReleaseCapture(void);
extern int far MySetCapture(int window);

extern void far YardToMap(void);
extern void far AdjustWndMinMax(struct MinMaxInfo far *mmi);
extern void far MYTIMERFUNC(unsigned, unsigned, unsigned, unsigned);

extern int far pascal BeginPaint(int window, void far *paint);

extern int far pascal EndPaint(int window, void far *paint);

extern void far pascal GetClientRect(unsigned int window, struct Rect far *rect);

extern unsigned int far pascal GetStockObject(int object);

extern int far pascal FillRect(int dc, struct WinRect far *rect, int brush);

extern int far pascal TextOut(int dc, int x, int y, char far *text, int count);

extern unsigned long far pascal GetTextExtent(int, char far *, int);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

extern void far pascal UpdateWindow(int window);

extern int far pascal SetWindowPos(unsigned, unsigned, int, int, int, int, unsigned);
extern unsigned int far pascal GetProp(int window, char far *name);

extern int far pascal SetProp(int window, char far *name, int data);

extern int far pascal GetCapture(void);
extern int far pascal SetCapture(int window);

extern void far pascal ReleaseCapture(void);

extern int far pascal SetFocus(unsigned);
extern long far pascal SendMessage(int hwnd, unsigned int msg, unsigned int wParam, long lParam);

extern int far pascal BringWindowToTop(int window);

extern int far pascal GetWindow(int window, int command);

extern int far pascal GetNextWindow(int window, int command);

extern int far pascal IsWindowVisible(int window);

extern int far pascal IsZoomed(unsigned);
extern int far pascal IsIconic(int window);

extern int far pascal GetAsyncKeyState(int);
extern int far pascal SetTimer(int window, unsigned int timer,
                               unsigned int interval,
                               void (far *timerFunc)(void));

extern int far pascal KillTimer(int window, unsigned int timer);

extern int far pascal GetSystemMetrics(int);
extern int far pascal GetVersion(void);
extern unsigned long far pascal GetFreeSpace(unsigned int flags);

extern unsigned int far pascal GetClassWord(unsigned int window, int index);

extern int far pascal GetWindowText(unsigned, char far *, int);
extern int far pascal GetWindowTextLength(unsigned);
extern int far pascal ClientToScreen(int window, struct ExpMenuPoint far *point);

extern int far pascal ScreenToClient(int window, struct ExpMenuPoint far *point);

extern int far pascal WindowFromPoint(struct WPoint);
extern int far pascal GetDC(int hwnd);

extern int far pascal ReleaseDC(int hwnd, int hdc);

extern int far pascal SelectPalette(int dc, int palette, int forceBackground);

extern int far pascal RealizePalette(int dc);

typedef int (far pascal *MAINWND_ENUM_PROC)(unsigned, long);
extern MAINWND_ENUM_PROC far pascal MakeProcInstance(MAINWND_ENUM_PROC, unsigned);
extern void far pascal FreeProcInstance(MAINWND_ENUM_PROC);
extern int far pascal EnumChildWindows(unsigned, MAINWND_ENUM_PROC, long);
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);

extern unsigned int far pascal SetCursor(unsigned int cursor);

extern void far WinPrintf(char far *, ...);
extern int far OptionStates[];
extern int __based(__segname("PACK")) openSub;
extern int far lastProxObj;
extern int __based(__segname("PACK")) lastSubState;
extern int far songsOnFlag;
extern int far effectsOnFlag;
extern int near mainWndState0376;
extern int near mainWndState0378;
extern int near mainWndState037A;
extern int near mainWndState038C;
extern char far mainWndPropertyIndex6[];
extern char far activateStart[];
extern char far activateCapture[];
extern char far activateReady[];
extern char far deactivateStart[];
extern char far deactivateRelease[];
extern char far deactivateReady[];
extern int far pascal __export MYENUMFUNC(int target, int unused, int window);

extern void far StopSimulation(void);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned style);

extern void far pascal ShowWindow(int window, int command);

extern long far pascal DefWindowProc(int window, int message,
                                     unsigned int wParam, unsigned long lParam);


long far pascal __export MAINWNDPROC(unsigned hwnd, unsigned message,
                            unsigned wParam, long lParam)
{
    struct WPaintInfo paintInfo;
    struct WRect clientRect;
    struct WRect objectRect;
    struct WRect resizeRect;
    struct WChangeInfo windowChange;
    struct WSizeUpdate resizeInfo;
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

    {
    register unsigned int dispatchMessage = message;
    if (dispatchMessage == 0x00a4) goto helpToggle;
    switch (dispatchMessage) {
    case 0x0204:
        goto helpToggle;
    case 0x0003:
        UpdateEditIfBufInvalid();
        return 0L;

    case 0x0005:
        UpdateEditIfBufInvalid();
        if (hwnd == win_hwnd[0] && (wParam == 2 || wParam == 0)) {
            result = LoadCursor(0, 0x7f02L);
            SetCursor(result);
            stateA = result;
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                EraseMapCursor();
                MSClipEnd();
            }
            if (editBuf != 0) {
                mem_Free(editBuf);
                editBuf = 0;
            }
            win_LockWin(0);
            objectReference.address = win_WinAddr(0);
            stateB = ((struct WBucket far *)objectReference.address)->outerRight -
                     ((struct WBucket far *)objectReference.address)->innerRight +
                     (int)(short)lParam;
            stateC = ((struct WBucket far *)objectReference.address)->outerBottom -
                     ((struct WBucket far *)objectReference.address)->innerBottom +
                     (int)(short)(lParam >> 16) + 0x12;
            windowReference.address =
                ((struct WBucket far *)objectReference.address)->rects[0];
            ((struct WRect far *)windowReference.address)->right += stateB;
            ((struct WRect far *)windowReference.address)->bottom += stateC;
            ((struct WBucket far *)objectReference.address)->innerRight =
                ((struct WBucket far *)objectReference.address)->outerRight +
                (int)(short)lParam;
            ((struct WBucket far *)objectReference.address)->innerBottom =
                ((struct WBucket far *)objectReference.address)->outerBottom +
                (int)(short)(lParam >> 16) + 0x12;
            win_Recalc(0);
            win_UnlockWin(0);
            UpdateEdit();
            win_GetObjRect(4, &objectRect);
            WinPrintf("WM_SIZE: newWidth(%d) newHeight(%d) editWidth(%d) editHeight(%d) rectWidth(%d) rectHeight(%d)\n", objectRect.right,
                      objectRect.bottom, editHeight, editWidth,
                      ((struct WBucket far *)objectReference.address)->innerRight,
                      ((struct WBucket far *)objectReference.address)->innerBottom);
            if (win_IsWinOpen(0x100)) {
                MSClipStart(win_hwnd[1]);
                DrawMapCursor();
                MSClipEnd();
            }
            SetCursor(stateA);
        }
        if (hwnd == mainRootWnd) {
            if (ribbonBarWnd != 0) {
                GetClientRect(ribbonBarWnd, &objectRect);
                stateA = objectRect.bottom - objectRect.top;
            } else {
                stateA = 0;
            }
            if (rootWnd != 0) {
                resizeInfo.width = (int)(short)lParam;
                resizeInfo.height = (int)(short)(lParam >> 16);
                resizeInfo.ribbonHeight = stateA;
                resizeInfo.flags = 6;
                SetWindowPos(rootWnd, 0, 0, 0, resizeInfo.width,
                             resizeInfo.height - resizeInfo.ribbonHeight,
                             resizeInfo.flags);
                screenWidth = resizeInfo.width;
                screenHeight = resizeInfo.height - resizeInfo.ribbonHeight;
                if (ribbonBarWnd != 0) {
                    SetWindowPos(ribbonBarWnd, 0, 0, 0,
                                 (int)(short)lParam, stateA, 6);
                    InvalidateRect(ribbonBarWnd, 0, 0);
                    UpdateWindow(ribbonBarWnd);
                }
            }
        } else if (hwnd == rootWnd && win_hwnd[0] != 0 &&
                   win_IsWinOpen(win_hwnd[0])) {
            result = GetClassWord(win_hwnd[0], 0);
            if ((result & 0xff) == 0xa3)
                SetCursor(win_hwnd[0]);
            SetWindowPos(win_hwnd[0], 0, 0, 0,
                         GetSystemMetrics(0x20) * 2 + (int)(short)lParam,
                         GetSystemMetrics(0x21) * 2 +
                             (int)(short)(lParam >> 16), 6);
        }
        return 0L;

    case 0x000f:
        if (hwnd == ribbonBarWnd) {
            unsigned long textExtent;
            dc = BeginPaint(hwnd, &paintInfo);
            textExtent = GetTextExtent(dc, "This is the ribbon bar.", 0x17);
            GetClientRect(hwnd, &clientRect);
            FillRect(dc, &clientRect, GetStockObject(2));
            TextOut(dc,
                    (clientRect.right - (int)(textExtent & 0xffff)) / 2,
                    (clientRect.bottom - (int)(textExtent >> 16)) / 2,
                    "This is the ribbon bar.", 0x17);
            EndPaint(hwnd, &paintInfo);
            return 0L;
        }
        if (GetProp(hwnd, "INDEX") == 0xffff || rootWnd == 0)
            return 0L;
        return PaintStuff(hwnd, message, wParam, (unsigned long)lParam, 0L);

    case 0x0010:
        UpdateEditIfBufInvalid();
        if (hwnd == mainRootWnd) {
            if (rootWnd != 0) {
                KillTimer(rootWnd, 0);
                if (MenuQuit() != 0) {
                    CleanUp();
                    return 1L;
                }
                SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
            }
            return 0L;
        }
        if (hwnd != rootWnd && hwnd != ribbonBarWnd &&
            GetProp(hwnd, "INDEX") != 0xffff) {
            result = GetProp(hwnd, "INDEX");
            if (result != 0xffff)
                win_Close(result);
        }
        return 0L;

    case 0x0011:
        if (rootWnd == 0)
            return 0L;
        KillTimer(rootWnd, 0);
        if (MenuQuit() != 0) {
            CleanUp();
            return 1L;
        }
        SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
        return 0L;

    case 0x001c:
        if (rootWnd == 0)
            return 0L;
        if (wParam != 0) {
            WinPrintf("ActivateApplication(START)\n");
            SetUpPalette(1);
            activeAppFlag = 1;
            if (mainWndState0376 == 0)
                mainWndState0376 = MyGetTopWindow(rootWnd);
            if (mainWndState0376 != 0)
                SendMessage(mainWndState0376, 0x0086, 1, 0L);
            OptionStates[2] = mainWndState037A;
            OptionStates[1] = mainWndState0378;
            songsOnFlag = mainWndState0378;
            effectsOnFlag = mainWndState037A;
            if (paletteFlag != 0) {
                objectReference.address =
                    (void far *)MakeProcInstance(
                        (MAINWND_ENUM_PROC)StopSimulation, hInst);
                EnumChildWindows(rootWnd,
                                 (MAINWND_ENUM_PROC)objectReference.address,
                                 0L);
                FreeProcInstance(
                    (MAINWND_ENUM_PROC)objectReference.address);
            }
            if (ribbonBarWnd != 0)
                InvalidateRect(ribbonBarWnd, 0, 0);
            SetFocus(rootWnd);
            if (captureWnd != 0 && mainRootWnd != 0 &&
                IsWindowVisible(captureWnd) && !IsIconic(mainRootWnd)) {
                SetCapture(captureWnd);
                result = GetProp(captureWnd, "INDEX");
                WinPrintf("ActivateApplication(CAPTURE)(%#x)\n", result);
                BringWindowToTop(captureWnd);
                win_FlushEvents();
            }
            KillTimer(rootWnd, 0);
            if (lpTimerFunc != 0L)
                SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
            if (mainWndState038C != 0)
                SetCursor(mainWndState038C);
            WinPrintf("ActivateApplication(READY)\n");
        } else {
            WinPrintf("DeActivateApplication(START)\n");
            result = LoadCursor(0, 0x7f02L);
            SetCursor(result);
            mainWndState038C = result;
            KillTimer(rootWnd, 0);
            if (lpTimerFunc != 0L)
                SetTimer(rootWnd, 0, 0xaa, lpTimerFunc);
            if (captureWnd != 0) {
                ReleaseCapture();
                WinPrintf("DeActivateApplication(RELEASECAPTURE)\n");
            }
            SetUpPalette(0);
            StopSong();
            if (activeAppFlag != 0) {
                mainWndState0378 = OptionStates[1];
                mainWndState037A = OptionStates[2];
                OptionStates[1] = 0;
                songsOnFlag = 0;
                OptionStates[2] = 0;
                effectsOnFlag = 0;
                if (mainWndState0376 != 0)
                    SendMessage(mainWndState0376, 0x0086, 0, 0L);
                activeAppFlag = 0;
                WinPrintf("DeActivateApplication(READY)\n");
            }
        }
        return 0L;

    case 0x0020:
        if (bHelp != 0) {
            SetCursor(hHelpCursor);
            return 1L;
        }
        if (((wParam == win_hwnd[0] && win_IsWinInFront(0)) ||
             (wParam == win_hwnd[1] && win_IsWinInFront(0x100))) &&
            GetAsyncKeyState(0x10) < 0 && (unsigned)lParam == 1 &&
            CurGameType == 3) {
            switch (CurExpTool) {
            case 0:
                SetCursor(magCursor);
                return 1L;
            case 1:
                SetCursor(rockCursor);
                return 1L;
            case 2:
                SetCursor(digCursor);
                return 1L;
            case 3:
                SetCursor(antCursor);
                return 1L;
            case 4:
                SetCursor(foodCursor);
                return 1L;
            case 5:
                SetCursor(dropCursor);
                return 1L;
            case 6:
                SetCursor(sprayCursor);
                return 1L;
            }
        }
        return 0L;

    case 0x0021:
        if (hwnd == rootWnd || hwnd == ribbonBarWnd ||
            hwnd == mainRootWnd || hwnd == mainWndState0376)
            return 0L;
        if ((unsigned)(lParam >> 16) != 0x0201)
            return 0L;
        topWindow = MyGetTopWindow(rootWnd);
        child = GetProp(topWindow, "INDEX");
        if (child != 0xffff) {
            if ((((unsigned char far *)win_WinAddr(child))[0x1c] & 0x40) == 0) {
                BringWindowToTop(hwnd);
                SendMessage(hwnd, 0x86, 1, 0L);
                return 2L;
            }
        }
        return 3L;

    case 0x0022:
        if (hwnd != rootWnd && hwnd != ribbonBarWnd &&
            hwnd != mainRootWnd) {
            if (mainWndState0376 != 0)
                SendMessage(mainWndState0376, 0x0086, 0, 0L);
            SendMessage(hwnd, 0x0086, 1, 0L);
            mainWndState0376 = hwnd;
        }
        return 0L;

    case 0x0024:
        if (hwnd == rootWnd) {
            AdjustWndMinMax((struct MinMaxInfo far *)lParam);
        } else if (hwnd == mainRootWnd) {
            struct MinMaxInfo far *minmax;
            minmax = (struct MinMaxInfo far *)lParam;
            minmax->minTrackSizeY = 100;
            minmax->minTrackSizeX = 100;
        }
        return 0L;

    case 0x001d:
        if ((unsigned)wParam > 0x4000u) {
            union WFreeSpaceWords freeSpace;
            freeSpace.value = GetFreeSpace(0);
            if (freeSpace.words.high == 0 &&
                freeSpace.words.low < 0xc350)
                PopMsg("Memory is very low.");
        }
        return 0L;

    case 0x0086:
        UpdateEditIfBufInvalid();
        if (activeAppFlag != 0 && wParam != 0) {
            if (hwnd == win_hwnd[0]) {
                if (win_IsWinOpen(0x2300)) {
                    win_Swap(0x2200, 0x2300);
                    DrawMapData();
                }
            } else if (hwnd == win_hwnd[25] && win_IsWinOpen(0x2200)) {
                win_Swap(0x2300, 0x2200);
                UpdateLayQueenModeDisplay();
                DrawYardData();
            }
        }
        return 0L;

    case 0x0100:
        DoKeyDown(hwnd, dispatchMessage, wParam, (unsigned)(lParam >> 16));
        return 0L;

    case 0x0101:
        UpdateEdit();
        return 0L;

    case 0x0111:
        if ((wParam & 0xff00) == 0xfd00) {
            if ((wParam & 0x00f0) != 0x00a0) {
                DoMenuEntry(wParam);
            } else {
                topWindow = MyGetTopWindow(rootWnd);
                if (topWindow != 0) {
                    switch (wParam & 0x00ff) {
                    case 0x00a0:
                        SendMessage(topWindow, 0x0010, 0, 0L);
                        break;
                    case 0x00a1:
                        SendMessage(topWindow, 0x0112, 0xf100, 0L);
                        break;
                    case 0x00a2:
                        child = topWindow;
                        while ((topWindow = GetWindow(child, 2)) != 0)
                            child = topWindow;
                        while (GetWindow(child, 4) != 0 ||
                               !IsWindowVisible(child))
                            child = GetNextWindow(child, 3);
                        BringWindowToTop(child);
                        break;
                    case 0x00a3:
                        SendMessage(topWindow, 0x0112, 0xf010, 0L);
                        break;
                    case 0x00a4:
                        if (topWindow == win_hwnd[0])
                            SendMessage(topWindow, 0x0112, 0xf000, 0L);
                        break;
                    case 0x00a5:
                        if (topWindow == win_hwnd[0]) {
                            if (IsZoomed(topWindow))
                                ShowWindow(topWindow, 1);
                            else
                                ShowWindow(topWindow, 3);
                        }
                        break;
                    case 0x00a6:
                        DoEditScroll(win_hwnd[0], 0x0115, 0, 0L);
                        while ((GetAsyncKeyState(0x11) & 0x8000) &&
                               (GetAsyncKeyState(0x26) & 0x8000))
                            DoEditScroll(win_hwnd[0], 0x0115, 0, 0L);
                        break;
                    case 0x00a7:
                        DoEditScroll(win_hwnd[0], 0x0115, 1, 0L);
                        while ((GetAsyncKeyState(0x11) & 0x8000) &&
                               (GetAsyncKeyState(0x28) & 0x8000))
                            DoEditScroll(win_hwnd[0], 0x0115, 1, 0L);
                        break;
                    case 0x00a8:
                        DoEditScroll(win_hwnd[0], 0x0114, 0, 0L);
                        while ((GetAsyncKeyState(0x11) & 0x8000) &&
                               (GetAsyncKeyState(0x25) & 0x8000))
                            DoEditScroll(win_hwnd[0], 0x0114, 0, 0L);
                        break;
                    case 0x00a9:
                        DoEditScroll(win_hwnd[0], 0x0114, 1, 0L);
                        while ((GetAsyncKeyState(0x11) & 0x8000) &&
                               (GetAsyncKeyState(0x27) & 0x8000))
                            DoEditScroll(win_hwnd[0], 0x0114, 1, 0L);
                        break;
                    case 0x00aa:
                        break;
                    case 0x00ab:
                        MessageBox(rootWnd, versionStr.initialTargets[0],
                                   mainWndTitle, 0);
                        break;
                    case 0x00ac:
                        if ((oldCapture = GetCapture()) == 0) {
                            MessageBox(rootWnd, noCaptureMessage,
                                       captureTitle1, 0);
                        } else {
                            oldCapture = GetCapture();
                            result = GetProp(oldCapture,
                                             mainWndPropertyIndex0);
                            sprintf(captionText, capturePrompt, result);
                            if (MessageBox(rootWnd, captionText,
                                           captureTitle0, 0x1024)) {
                                ReleaseCapture();
                                win_Close(result);
                            }
                        }
                        break;
                    }
                }
            }
        }
        return 0L;

    case 0x0112:
        if ((wParam & 0xff00) == 0xf900) {
            popUpMenuId = (unsigned char)wParam;
            return 0L;
        }
        if (hwnd == mainRootWnd && (wParam & 0xfff0) == 0xf020) {
            if (captureWnd != 0)
                ReleaseCapture();
            return 0L;
        }
        if (hwnd == mainRootWnd && (wParam & 0xfff0) == 0xf060) {
            KillTimer(rootWnd, 0);
            if (MenuQuit() != 0) {
                CleanUp();
                return 1L;
            }
            SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
            return 0L;
        }
        if ((wParam & 0xfff0) == 0xf040) {
            child = MyGetTopWindow(rootWnd);
            if (child != 0) {
                topWindow = child;
                for (;;) {
                    child = GetWindow(topWindow, 2);
                    if (child != 0) {
                        topWindow = child;
                    } else if (GetWindow(topWindow, 4) != 0 ||
                               !IsWindowVisible(topWindow)) {
                        topWindow = GetNextWindow(topWindow, 3);
                    } else {
                        break;
                    }
                }
                BringWindowToTop(topWindow);
            }
            return 0L;
        }
        if (hwnd == win_hwnd[25] && (wParam & 0xfff0) == 0xf060) {
            long forwardedResult;
            YardToMap();
            KillTimer(rootWnd, 0);
            forwardedResult = DefWindowProc(hwnd, message, wParam, lParam);
            if (lpTimerFunc != 0L)
                SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
            if (hwnd == mainRootWnd &&
                (wParam & 0xfff0) == 0xf120 && captureWnd != 0) {
                SetCapture(captureWnd);
                GetClientRect(rootWnd, &clientRect);
                GetClientRect(captureWnd, &resizeRect);
                SetWindowPos(captureWnd, 0,
                             (clientRect.right - resizeRect.right) / 2,
                             (clientRect.bottom - resizeRect.bottom) / 2,
                             0, 0, 5);
            }
            return forwardedResult;
        }
        return DefWindowProc(hwnd, message, wParam, lParam);

    case 0x0113:
        if (hwnd == rootWnd)
            MYTIMERFUNC(hwnd, message, wParam, (unsigned)(lParam >> 16));
        else if (wParam == 0xaa)
            StopSong();
        else
            UpdateEditIfBufInvalid();
        return 0L;

    case 0x0114:
    case 0x0115:
        DoEditScroll(hwnd, message, wParam, lParam);
        if (GetAsyncKeyState(0x11) < 0)
            SendMessage(rootWnd, 0x115, wParam, lParam);
        return 0L;

    case 0x0200:
        if (rootWnd == 0 || hwnd == rootWnd)
            return 0L;
        point.x = (int)(short)lParam;
        point.y = (int)(short)(lParam >> 16);
        ClientToScreen(hwnd, &point);
        screenPoint = point;
        child = WindowFromPoint(screenPoint);
        result = GetProp(child, "INDEX");
        ClientToScreen(hwnd, &point);
        ScreenToClient(child, &point);
        result = win_FindObject(result, &point);
        if ((result & 0xff) == 0)
            return 0L;
        objectReference.address = win_ObjAddr(result);
        if (objectReference.address == 0)
            return 0L;
        if (openSub != -1 && win_hwnd[openSub >> 8] != child)
            return 0L;
        if ((((unsigned char far *)objectReference.address)[0x24] & 0x10) == 0)
            return 0L;
        if (lastSubState != result) {
            MSClipStart(win_hwnd[result >> 8]);
            if (lastSubState != -1)
                win_ObjInv(lastSubState);
            if (result != -1)
                win_ObjInv(result);
            MSClipEnd();
            lastSubState = result;
        }
        stateD = lastProxObj ^ result;
        if ((stateD & 0xff00) == 0 && (stateD & 0x00ff) != 0)
            win_SetProxItem(result);
        stateA = win_GetProxEvent();
        stateB = (stateA & 0xff) - 2;
        stateC = submenuWindow[stateB];
        if (stateC == openSub)
            return 0L;
        if (stateB < 0 || stateB > 7)
            return 0L;
        if (openSub != -1) {
            MyReleaseCapture();
            win_Close(openSub);
            openSub = -1;
            UpdateAllWindows();
        }
        if (stateC != -1) {
            win_GetObjRect(0x902 + stateB, &resizeRect);
            point.x = resizeRect.left;
            point.y = resizeRect.top;
            ClientToScreen(win_hwnd[9], &point);
            ScreenToClient(rootWnd, &point);
            openSub = stateC;
            win_Open(openSub, point.x, point.y);
            MySetCapture(win_hwnd[openSub >> 8]);
            lastSubState = -1;
        }
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
    palette_update:
        if (paletteH == 0)
            return 0L;
        dc = GetDC(hwnd);
        SelectPalette(dc, paletteH, 0);
        result = RealizePalette(dc);
        ReleaseDC(hwnd, dc);
        if (result > 0) {
            WinPrintf("WM_PALETTECHANGED/WM_QUERYNEWPALETTE(Invalidate)\n");
            objectReference.address =
                (void far *)MakeProcInstance((MAINWND_ENUM_PROC)StopSimulation,
                                             hInst);
            EnumChildWindows(rootWnd,
                             (MAINWND_ENUM_PROC)objectReference.address, 0L);
            FreeProcInstance((MAINWND_ENUM_PROC)objectReference.address);
            if (ribbonBarWnd != 0)
                InvalidateRect(ribbonBarWnd, 0, 0);
        }
        return (long)(short)result;

    case 0x0311:
        GetWindowText(hwnd, windowText, 0x80);
        WinPrintf("WM_PALETTECHANGED(called)(%s)\n", windowText);
        GetWindowText(wParam, classText, 0x80);
        WinPrintf("WM_PALETTECHANGED(calling)(%s)\n", classText);
        if (hwnd == wParam) {
            WinPrintf("WM_PALETTECHANGED(same window)\n");
            return 0L;
        }
        if (activeAppFlag != 0)
            goto palette_update;
        return 0L;

    case 0x03bb:
        MciMessage(hwnd, message, wParam, (unsigned)lParam);
        return 0L;

    default:
        break;
    }
    }

    goto normal_tail;
helpToggle:
    if (bHelp == 0) {
        bHelp = 1;
        SetCursor(hHelpCursor);
    } else {
        bHelp = 0;
        SetCursor((unsigned)GetClassWord(hwnd, -12));
    }
    return 0L;

normal_tail:

    if (message == 0x0200 && win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        DrawMapCursor();
        MSClipEnd();
    }

    if (message == 0x0200 && mainRootWnd != 0)
        win_GetObjRect(mainRootWnd, &objectRect);

    return DefWindowProc(hwnd, message, wParam, lParam);
}
