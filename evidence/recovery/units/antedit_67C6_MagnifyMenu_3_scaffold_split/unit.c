/* Candidate translation unit antedit_67C6_MagnifyMenu_3_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _MagnifyMenu, _AntMenu, _SetExpTool
 * SCAFFOLDED: unclaimed members _EditToolsMenu, _win_DrawExamineWindow are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinRect { int left; int top; int right; int bottom; };
struct WinPoint { int x; int y; };
struct MapPoint { int x; int y; };
extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;
extern int near tileWidth;
extern int near tileHeight;
extern int near rootWnd;
extern int near win_hwnd[];
extern void far pascal GetWindowRect(int window, struct WinRect far *rect);
extern int far win_GetObjRect(int object, struct WinRect far *rect);
extern int far pascal ClientToScreen(int window, struct WinPoint far *point);
extern int far pascal ScreenToClient(int window, struct WinPoint far *point);
extern void far win_Open(int object, int x, int y);
extern int far MySetCapture(int window);
extern void far win_FlushEvents(void);
extern void far ButtonHeldInit(void);
extern int far win_IsWinOpen(int window);
extern int far ButtonHeld(void);
extern int far win_IsWinInFront(int window);
extern void far pascal BringWindowToTop(int window);
extern void far MSClipStart(int window);
extern void far win_DrawWindow(int window);
extern void far MSClipEnd(void);
extern void far ButtonHeldEnd(void);
extern void far MyReleaseCapture(void);
extern void far win_Close(int window);
extern void far UpdateAllWindows(void);
struct MouseEvent {
    int pad[4];
    int x;
    int y;
};
extern int far MeMode;
extern int near MeType;
extern int far MeNestStarted;
extern void far WinPrintf(char far *text);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern int far pascal GetAsyncKeyState(int key);
extern void far YellowCommand(int command);
extern int far CurExpTool;
static signed char near cmdB[4] = {0x08, 0x09, 0x00, 0x00};
static signed char near cmdC[6] = {0x01, 0x02, 0x04, 0x05, 0x06, 0x00};
static signed char near cmdA[4] = {0x0a, 0x0b, 0x06, 0x00};
static int magnifyX;
static int magnifyY;
static int magnifyPlane;

extern int far match_position;  /* scaffold reference for pool word C238 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C23E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C240 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C242 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C244 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C246 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_EditToolsMenu(void);
void far pool_stub_win_DrawExamineWindow(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_EditToolsMenu)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawExamineWindow)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _EditToolsMenu.
 * It only reproduces the object's selector-pool allocation order for the
 * words C238 C23A C23C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_EditToolsMenu(void)
{
    volatile int t;

    t = match_position;
    t = (int)MeMode;
    t = (int)CurExpTool;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_DrawExamineWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C23E C240 C242 C244 C246; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_DrawExamineWindow(void)
{
    volatile int t;

    t = match_length;
    t = pack_buf;
    t = Dx8;
    t = Scycle;
    t = EditColumns;
}

int far MagnifyMenu(int x, int y, int plane)
{
    int life;
    int px;
    int py;
    struct WinRect screen;
    struct WinPoint point;
    struct WinRect object;

    if (plane <= 1)
        life = LifeA[(x << 6) + y];
    else if (plane == 2)
        life = LifeB[(x << 6) + y];
    else
        life = LifeR[(x << 6) + y];
    if (life == 0)
        return -1;

    px = ((x - MapPnt.x) + 1) * tileWidth + editTileRect.left;
    py = ((y - MapPnt.y) - 1) * tileHeight + editTileRect.top;
    GetWindowRect(rootWnd, &screen);
    win_GetObjRect(0x1d00, &object);
    point.x = px;
    point.y = py;
    ClientToScreen(win_hwnd[0], &point);

    if (point.y + (object.bottom - object.top) > screen.bottom) {
        point.y += object.top - object.bottom;
        if (point.y < screen.top)
            point.y = screen.top;
    }
    if (point.x + (object.right - object.left) > screen.right) {
        point.x += object.left - object.right;
        if (point.x < screen.left)
            point.x = screen.left;
    }
    ScreenToClient(rootWnd, &point);

    magnifyX = x;
    magnifyY = y;
    magnifyPlane = plane;
    win_Open(0x1d00, point.x, point.y);
    MySetCapture(win_hwnd[0x1d]);
    win_FlushEvents();
    ButtonHeldInit();
    if (win_IsWinOpen(0x1d00)) {
        do {
            if (!ButtonHeld())
                break;
            if (!win_IsWinInFront(0x1d00)) {
                BringWindowToTop(win_hwnd[0x1d]);
                MSClipStart(win_hwnd[0x1d]);
                win_DrawWindow(0x1d00);
                MSClipEnd();
                MySetCapture(win_hwnd[0x1d]);
            }
        } while (win_IsWinOpen(0x1d00));
    }
    ButtonHeldEnd();
    MyReleaseCapture();
    win_Close(0x1d00);
    UpdateAllWindows();
    return life;
}

int far AntMenu(struct MouseEvent far *pt)
{
    int result;
    int selected;
    struct ModeSlot { int far *value; int pad[2]; } mode;

    WinPrintf("ANTMENU");
    mode.value = &MeMode;

    if (**(&mode.value) == 0) {
        if (MeType == 0x40 && MeNestStarted == 0)
            result = win_DoProxMenu(0x800, -1, pt->x, pt->y);
        else
            result = win_DoProxMenu(0x700, -1, pt->x, pt->y);
    } else if (**((int far * volatile near *)&mode.value) == 1) {
        result = win_DoProxMenu(0x2000, -1, pt->x, pt->y);
    } else {
        result = -1;
    }

    if (result < 0)
        return result;

    selected = result;
    if (**(&mode.value) == 1) {
        selected = cmdA[selected];
    } else if (MeType == 0x40 && MeNestStarted == 0) {
        selected = cmdB[selected];
    } else {
        selected = cmdC[selected];
        if (selected == 2 && (GetAsyncKeyState(0x10) & 0x8000))
            selected = 3;
    }
    YellowCommand(selected);
    return result;
}

void SetExpTool(int value)
{
    CurExpTool = value;
}

