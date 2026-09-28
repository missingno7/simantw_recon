struct ExpMenuPoint { int x, y; };
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};
struct WinButtonObject {
    unsigned char reserved1[0x1c];
    unsigned char flagsLo;
    unsigned char reserved1d_1f[3];
    union {
        unsigned int group;
        struct {
            unsigned char groupLow;
            unsigned char type;
        } bytes;
    } groupType;
    unsigned char reserved22_23[2];
    unsigned char flags24;
    unsigned char flags25;
};/*
 * Evidence-backed first hypothesis for DoKeyDown.  MAINWNDPROC forwards the
 * window, wParam key, and the low/high lParam words in this order.  The high
 * word contains the WM_KEYDOWN previous-state bit checked below.
 */
struct Point16 { int x; int y; };
struct KeyEvent {
    unsigned char scanCode;
    unsigned char keyCode;
    unsigned int keyState;
    unsigned int reserved4;
    unsigned int state;
    unsigned int x;
    unsigned int y;
    unsigned int object;
    unsigned int reserved14;
};
struct KeyMessage { unsigned int words[8]; };

extern int near rootWnd;
extern int near bHelp;
extern unsigned char near mouse_state;
extern unsigned char far Dx8[];
extern int far MyGetTopWindow(int window);
extern unsigned int far pascal GetProp(int window, char far *name);
extern int far pascal GetCursorPos(void far *point);

extern int far pascal ScreenToClient(int window, struct ExpMenuPoint far *point);

extern int far win_FindObject(int window, struct Point16 far *point);
extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);

extern void far win_SetGroupSelectedObj(int group, int selected, int object);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far WinPrintf(char far *format, ...);
extern void far WaitHundredths(int hundredths);
extern void far DoEvent(struct KeyEvent event);
extern int far HelpKeyDown(int window, int key, unsigned long keyData);
extern int far YellowCommandKey(int key);
extern void far CheatKeys(int index);
extern int far pascal GetKeyState(int key);
extern int far pascal GetAsyncKeyState(int key);
extern unsigned int far pascal MapVirtualKey(unsigned int key,
                                              unsigned int mapType);
extern int far pascal PeekMessage(struct MSG far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, unsigned int remove);

extern int far pascal GetCursorPos(void far *point);

extern int far pascal SetCursorPos(int x, int y);

static unsigned int cheatPosition = 0;
static unsigned int cheatLength = 0;
static char propertyIndex[] = "INDEX";
static char flashStart[] = "DoKeyDown: Flash(start)(%d)\n";
static char flashAlmost[] = "DoKeyDown: Flash(almost done)(%d)\n";
static char flashDone[] = "DoKeyDown: Flash(done)(%d)\n";
static unsigned char cheatBuffer[4];

void far DoKeyDown(int window, int key, unsigned long keyData)
{
    struct KeyEvent event;
    struct WinButtonObject far *objectData;
    struct Point16 point;
    struct Point16 arrowPoint;
    struct MSG queued;
    unsigned int modifiers;
    unsigned int mapped;
    unsigned int count;
    unsigned char reversed[8];
    int top;
    int index;
    int object;
    int match;
    unsigned int queuedState;

    top = MyGetTopWindow(rootWnd);
    if (top != 0 && !(keyData & 0x40000000L) &&
        (key == 0x2d || key == 0x20)) {
        top = MyGetTopWindow(rootWnd);
        if (top == 0)
            return;
        index = GetProp(top, propertyIndex);
        if (index == -1)
            return;
        GetCursorPos(&point);
        ScreenToClient(top, &point);
        object = win_FindObject(index, &point);
        if ((object & 0xff) == 0 && !bHelp)
            return;

        modifiers = 0;
        if (!(GetKeyState(0x2d) & 1)) modifiers |= 0x80;
        if (!(GetKeyState(0x14) & 1)) modifiers |= 0x40;
        if (!(GetKeyState(0x91) & 1)) modifiers |= 0x10;
        if (!(GetKeyState(0x90) & 1)) modifiers |= 0x20;
        if (!(GetKeyState(0x10) & 0x8000)) modifiers |= 3;
        if (!(GetKeyState(0x11) & 0x8000)) modifiers |= 4;
        if (GetKeyState(0x10) & 0x8000) modifiers |= 0x200;
        if (GetKeyState(0x11) & 0x8000) modifiers |= 0x400;
        if (GetKeyState(0x12) & 0x8000) modifiers |= 0x800;
        if (GetKeyState(0x90) & 1) modifiers |= 0x1000;
        if (GetKeyState(0x91) & 1) modifiers |= 0x2000;
        if (GetKeyState(0x14) & 1) modifiers |= 0x4000;
        if (GetAsyncKeyState(0x2d) & 0x8000) modifiers |= 4;
        mouse_state = (unsigned char)modifiers;

        objectData = win_ObjAddr(object);
        if (objectData->flags24 & 2) {
            if (objectData->flags24 & 8) {
                if (objectData->flags24 & 0x20)
                    win_SetGroupSelectedObj(index, objectData->groupType.bytes.groupLow, object);
                else
                    win_SetObjSelectedState(object,
                                            (objectData->flags24 & 4) != 0);
            } else if (objectData->flags25 & 8) {
                WinPrintf(flashStart, (objectData->flags24 & 4) >> 2);
                win_SetObjSelectedState(object,
                                        (objectData->flags24 & 4) != 0);
                WaitHundredths(5);
                WinPrintf(flashAlmost, (objectData->flags24 & 4) >> 2);
                win_SetObjSelectedState(object,
                                        (objectData->flags24 & 4) != 0);
                WinPrintf(flashDone, (objectData->flags24 & 4) >> 2);
                event.keyState = modifiers;

                if (PeekMessage(&queued, 0, 0x100, 0x100, 1)) {
                    if (queued.wParam == 0x2d ||
                        queued.wParam == 0x20 ||
                        queued.wParam == 0x2e) {
                        queuedState = 0;
                        if (queued.wParam == 0x2d || queued.wParam == 0x20)
                            queuedState |= 0x2000;
                        if (queued.wParam == 0x2e)
                            queuedState |= 0x4000;
                        if ((GetKeyState(1) | GetKeyState(0x20) |
                             GetKeyState(0x2d)) & 0x8000)
                            queuedState |= 1;
                        if ((GetKeyState(2) | GetKeyState(0x2e)) & 0x8000)
                            queuedState |= 2;
                        mouse_state = (unsigned char)queuedState;
                        event.scanCode = (unsigned char)MapVirtualKey(key, 2);
                        event.keyCode = (unsigned char)MapVirtualKey(key, 0);
                        event.state = queuedState;
                        event.object = object;
                        event.x = point.x;
                        event.y = point.y;
                        DoEvent(event);
                        return;
                    }
                }
            }
        }

        event.state = 0x100 | modifiers;
        event.object = object;
        event.x = point.x;
        event.y = point.y;
        DoEvent(event);
        return;
    }

    if (HelpKeyDown(window, key, keyData))
        return;
    if (YellowCommandKey(key))
        return;

    if (key >= 0x25 && key <= 0x28) {
        GetCursorPos(&arrowPoint);
        if (key == 0x25) arrowPoint.x -= 8;
        if (key == 0x26) arrowPoint.y -= 8;
        if (key == 0x27) arrowPoint.x += 8;
        if (key == 0x28) arrowPoint.y += 8;
        SetCursorPos(arrowPoint.x, arrowPoint.y);
        return;
    }

    if (key == 0x0d) {
        cheatPosition = 0;
        cheatLength = 0;
        return;
    }
    if (key < 0x41 || key > 0x5a)
        return;

    if (!(GetAsyncKeyState(0x10) & 0x8000))
        return;
    mapped = MapVirtualKey(key, 2);
    if (mapped == 0)
        return;
    cheatBuffer[cheatPosition] = (unsigned char)mapped;
    cheatPosition = (cheatPosition + 1) & 3;
    if (cheatLength < 4)
        ++cheatLength;
    if (cheatLength < 4)
        return;

    for (count = 0; Dx8[0x83bc + count * 4] != 0; ++count) {
        reversed[0] = (unsigned char)~cheatBuffer[cheatPosition & 3];
        reversed[2] = (unsigned char)~cheatBuffer[(cheatPosition + 1) & 3];
        reversed[4] = (unsigned char)~cheatBuffer[(cheatPosition + 2) & 3];
        reversed[6] = (unsigned char)~cheatBuffer[(cheatPosition + 3) & 3];
        match = reversed[0] == (unsigned char)Dx8[0x83bc + count * 4] &&
                reversed[2] == (unsigned char)Dx8[0x83bc + count * 4 + 1] &&
                reversed[4] == (unsigned char)Dx8[0x83bc + count * 4 + 2] &&
                reversed[6] == (unsigned char)Dx8[0x83bc + count * 4 + 3];
        if (match) {
            CheatKeys(count);
            return;
        }
    }
}
