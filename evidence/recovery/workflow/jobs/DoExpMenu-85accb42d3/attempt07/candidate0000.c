/* Open the expansion menu, track its highlighted item, and return the choice. */
struct ExpMenuEvent {
    unsigned char unused[12];
    int object;
    unsigned char tail[2];
};
struct ExpMenuPoint { int x, y; };

extern int near ribbonBarWnd;
extern int near rootWnd;
extern int near openSub;
extern int near win_hwnd[];
extern int near lastProxObj;
extern int far GamePaused;
extern int far CurExpTool;
extern unsigned char far ExpSubStates[];
extern int far MyGetTopWindow(int window);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far ButtonHeldInit(void);
extern void far ButtonHeldEnd(void);
extern void far SetPause(int pause);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far win_Open(int object, int x, int y);
extern void far win_Close(int object);
extern int far win_IsWinOpen(int object);
extern int far win_GetEvent(struct ExpMenuEvent far *event);
extern unsigned int far win_GetProxEvent(void);
extern void far _win_SetProxItem(int item);
extern int far pascal ClientToScreen(int window, struct ExpMenuPoint far *point);
extern int far pascal ScreenToClient(int window, struct ExpMenuPoint far *point);

int far DoExpMenu(int x, int y)
{
    struct ExpMenuEvent event;
    struct ExpMenuPoint point;
    register int oldPause;
    int choice;
    int prox;

    oldPause = GamePaused;
    choice = -1;
    point.x = x;
    point.y = y;
    if (ribbonBarWnd == 0) {
        ClientToScreen(MyGetTopWindow(rootWnd), &point);
        ScreenToClient(rootWnd, &point);
    }
    win_Open(0x900, point.x, point.y);
    MySetCapture(win_hwnd[9]);
    _win_SetProxItem(CurExpTool + 0x902);
    ButtonHeldInit();
    SetPause(1);

    while (win_IsWinOpen(0x900) && win_GetEvent(&event)) {
        if (openSub != -1) {
            if (event.object != 0) {
                prox = (win_GetProxEvent() & 0xff) - 2;
                ExpSubStates[prox] = (event.object & 0xff) - 2;
                continue;
            }
        } else if (event.object >= 0x902) {
            choice = event.object - 0x902;
        }
        break;
    }

    ButtonHeldEnd();
    SetPause(oldPause);
    EditMessage(0L, -2, -1, 1);
    MyReleaseCapture();
    if (openSub != -1)
        win_Close(openSub);
    win_Close(0x900);
    lastProxObj = -1;
    return choice;
}




