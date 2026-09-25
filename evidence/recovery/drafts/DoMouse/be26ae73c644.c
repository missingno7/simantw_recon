/*
 * DoMouse: ribbon/yard mouse handler for WM_LBUTTONDOWN/WM_MOUSEMOVE/
 * WM_LBUTTONUP-style messages (0x201/0x202/0x203) re-dispatched with the
 * key state and x/y already split out by the caller. Rejects clicks
 * outside the active top window (unless it's the ribbon), closes a
 * GetProp(0x240)-tagged owner window whose object has bit 0 of flags+
 * 0x1c set on button-down, otherwise locates the hit object through
 * win_FindObject and (unless bHelp is active with no object) builds an
 * extended-style word from several GetKeyState/toggle-key probes, then
 * on button-down toggles group/object selection state (with WinPrintf
 * debug traces bracketing a WaitHundredths(5) pause) or resyncs the
 * mouse's prox item, records message-specific bits into the global
 * mouse_state byte, and forwards a filled event record to DoEvent
 * (skipping objects of type 5/0x11/0xd entirely).
 */
struct WinButtonObject {
    unsigned char reserved1[0x1c];
    unsigned char flagsLo;
    unsigned char type;
    unsigned char flags24;
    unsigned char flags25;
};

struct Point {
    int x;
    int y;
};

struct DoMouseEvent {
    int reserved0;
    int keyState;
    int reserved4;
    int state;
    int x;
    int y;
    int object;
    int reserved14;
};

extern int near rootWnd;
extern int near ribbonBarWnd;
extern int near bHelp;
extern unsigned char mouse_state;
extern unsigned int near lastProxObj;
extern char near propAtom_0x240;
extern char near msg_0x246;
extern char near msg_0x261;
extern char near msg_0x282;

extern int far pascal MyGetTopWindow(int window);
extern int far pascal GetProp(int window, char far *atom);
extern void far win_Close(int window);
extern struct WinButtonObject far * far win_WinAddr(int window);
extern struct WinButtonObject far * far win_ObjAddr(int object);
extern int far win_FindObject(int window, struct Point far *pt);
extern int far pascal GetKeyState(int key);
extern int far pascal GetAsyncKeyState(int key);
extern void far win_SetGroupSelectedObj(int window, int group);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far WinPrintf(char far *format, ...);
extern void far WaitHundredths(int hundredths);
extern void far win_SetProxItem(int item);
extern void far DoEvent(struct DoMouseEvent event);

void far DoMouse(int window, int message, int keyFlags, int x, int y)
{
    int windowHandle;
    struct WinButtonObject far *obj;
    struct Point pt;
    int object;
    int style;
    int state;
    int capsState, scrollState, numState, shiftState, controlState;
    struct DoMouseEvent event;

    if (window != rootWnd) {
        if (MyGetTopWindow(rootWnd) != window && window != ribbonBarWnd)
            return;
    }

    windowHandle = GetProp(window, &propAtom_0x240);
    if (windowHandle == -1)
        return;

    obj = win_WinAddr(windowHandle);
    if (message == 0x201 && (obj->flagsLo & 1)) {
        win_Close(windowHandle);
        return;
    }

    pt.x = x;
    pt.y = y;
    object = win_FindObject(windowHandle, &pt);
    if (!(object & 0xff) && !bHelp)
        return;

    obj = win_ObjAddr(object);
    style = ((GetKeyState(0x2d) & 1) == 0) ? 0x80 : 0;
    capsState = GetKeyState(0x14);
    scrollState = GetKeyState(0x91);
    numState = GetKeyState(0x90);
    shiftState = GetKeyState(0x10);
    controlState = GetAsyncKeyState(0x11);
    style |= ((capsState & 1) == 0) ? 0x40 : 0;
    style |= ((scrollState & 1) == 0) ? 0x10 : 0;
    style |= ((numState & 1) == 0) ? 0x20 : 0;
    style |= ((shiftState & 0x8000) != 0) ? 3 : 0;
    style |= ((controlState & 0x8000) != 0) ? 4 : 0;
    event.keyState = style;

    if (!bHelp && message == 0x201) {
        if (obj->flags24 & 2) {
            if (obj->flags24 & 8) {
                if (obj->flags24 & 0x20) {
                    win_SetGroupSelectedObj(object, obj->flags25);
                } else {
                    win_SetObjSelectedState(object, (obj->flags24 & 4) != 0);
                }
            } else if (obj->flags25 & 8) {
                WinPrintf(&msg_0x246, (obj->flags24 & 4) >> 2);
                win_SetObjSelectedState(object, (obj->flags24 & 4) != 0);
                WaitHundredths(5);
                WinPrintf(&msg_0x261, (obj->flags24 & 4) >> 2);
                win_SetObjSelectedState(object, (obj->flags24 & 4) != 0);
                WinPrintf(&msg_0x282, (obj->flags24 & 4) >> 2);
            }
            if (obj->flags24 & 0x10) {
                if (((lastProxObj ^ object) & 0xff00) == 0 &&
                    ((lastProxObj ^ object) & 0xff) != 0)
                    win_SetProxItem(object);
            }
        }
    }

    event.object = object;
    event.x = pt.x;
    event.y = pt.y;

    switch (message) {
    case 0x201:
    case 0x204: {
        int leftButton, spaceKey, insertKey, rightButton, deleteKey;
        leftButton = GetKeyState(1);
        spaceKey = GetKeyState(0x20);
        insertKey = GetKeyState(0x2d);
        rightButton = GetKeyState(2);
        deleteKey = GetKeyState(0x2e);
        state = ((leftButton | spaceKey | insertKey) & 0x8000) ? 1 : 0;
        if (((rightButton | deleteKey) & 0x8000) != 0)
            state |= 2;
        if (message == 0x201)
            state |= 0x200;
        else
            state |= 0x800;
        break;
    }
    case 0x202:
    case 0x205: {
        int leftButton, spaceKey, insertKey, rightButton, deleteKey;
        leftButton = GetKeyState(1);
        spaceKey = GetKeyState(0x20);
        insertKey = GetKeyState(0x2d);
        rightButton = GetKeyState(2);
        deleteKey = GetKeyState(0x2e);
        state = ((leftButton | spaceKey | insertKey) & 0x8000) ? 1 : 0;
        if (((rightButton | deleteKey) & 0x8000) != 0)
            state |= 2;
        if (message == 0x202)
            state |= 0x400;
        else
            state |= 0x1000;
        break;
    }
    case 0x203:
    case 0x206: {
        int leftButton, spaceKey, insertKey, rightButton, deleteKey;
        leftButton = GetKeyState(1);
        spaceKey = GetKeyState(0x20);
        insertKey = GetKeyState(0x2d);
        rightButton = GetKeyState(2);
        deleteKey = GetKeyState(0x2e);
        state = ((leftButton | spaceKey | insertKey) & 0x8000) ? 1 : 0;
        if (((rightButton | deleteKey) & 0x8000) != 0)
            state |= 2;
        if (message == 0x203)
            state |= 0x2000;
        else
            state |= 0x4000;
        break;
    }
    default:
        return;
    }
    event.state = state;
    mouse_state = (unsigned char)state;

    if (obj->type == 5 || obj->type == 0x11 || obj->type == 0xd)
        return;

    DoEvent(event);
}
