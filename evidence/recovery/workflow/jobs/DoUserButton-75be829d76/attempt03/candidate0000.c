/*
 * DoUserButton: ribbon user-button click handler. object identifies which
 * ribbon window's button was hit (a map-window object id has high byte
 * 0x22 and uses mapUserButton[]; a yard-window id uses yardUserButton[],
 * the same DGROUP-adjacent parallel tables UpdateUserButtons walks) and
 * button is the button's index (0..7) within that ribbon.
 *
 * Holding Control (VK_CONTROL, GetAsyncKeyState(0x11)) drags the button
 * into a new programmable action slot: it snapshots GamePaused, opens the
 * drag-feedback window, captures the mouse, marks the affected object
 * with win_SetProxItem, starts the held-button tracker and pauses the
 * game, then blocks on win_GetEvent until an event arrives. It ends the
 * held tracker, restores GamePaused, releases the mouse and reads the
 * final prox event/window rect: if the drop point still falls inside the
 * rect, the new slot value is written back (Shift-held applies it to
 * only the clicked ribbon through SetUserButton; otherwise both parallel
 * tables are updated and the paired map/yard window's matching button --
 * object +/- 0xfb, the constant offset between the map and yard object
 * base ids -- is resynced too).
 *
 * Without Control, the value already stored in mapUserButton[button]/
 * yardUserButton[button] selects one of sixteen ribbon actions through
 * the same dense cs: jump-table idiom as SetUserButton/
 * DoUserButtonUpdate: open the mode/caste/history/info windows, toggle
 * showTrails (guarding a StopSong through match_position), toggle
 * GamePaused, cycle GameSpeed and report it through EditMessage, toggle
 * OptionStates[1..5] (some also stopping the song or refreshing the
 * menu), trigger MysteryButton, flip from yard to map view, save the
 * game, or bring the map to the front and center on the player's ant.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Point {
    int x;
    int y;
};

struct UserEvent {
    unsigned char reserved1[8];
    int x;
    int y;
    unsigned char reserved2[4];
};

extern int near mapUserButton[8];
extern int near yardUserButton[8];
extern int near rootWnd;
extern int near win_hwnd[];
extern void (far *lpTimerFunc)(void);
extern int far GamePaused;
extern int far OptionStates[];
extern int far GameSpeed;
extern int far showTrails;
extern int far match_position;

extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_Open(int flags, int x, int y);
extern void far MySetCapture(int window);
extern void far win_SetProxItem(int item);
extern void far ButtonHeldInit(void);
extern void far SetPause(int pause);
extern int far win_GetEvent(struct UserEvent far *event);
extern void far ButtonHeldEnd(void);
extern void far MyReleaseCapture(void);
extern int far win_GetProxEvent(void);
extern void far win_Close(int window);
extern void far SetUserButton(int object, int button);
extern void far SetMenuEntries(void);
extern void far StopSong(void);
extern void far OpenModeWindow(void);
extern void far OpenCasteWindow(void);
extern void far OpenHistoryWindow(void);
extern void far OpenInfoWindow(void);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far MysteryButton(void);
extern void far YardToMap(void);
extern void far GotoMyAnt(void);
extern void far SaveGame(int flag);
extern int far win_IsWinOpen(int window);

extern int far pascal GetAsyncKeyState(int key);
extern void far pascal GetWindowRect(unsigned int window, struct WinRect far *rect);
extern void far pascal ClientToScreen(unsigned int window, struct Point far *point);
extern int far pascal PtInRect(struct WinRect far *rect, struct Point point);
extern int far pascal KillTimer(int window, unsigned int timer);
extern int far pascal SetTimer(int window, unsigned int timer,
                               unsigned int interval,
                               void (far *timerFunc)(void));
extern void far pascal BringWindowToTop(int window);
extern void far pascal UpdateWindow(int window);

void far DoUserButton(int object, int button)
{
    struct UserEvent event;
    struct WinRect rect;
    struct Point pt;
    int near *tableBase;
    int far *slot;
    int savedGamePaused;
    int savedBase;
    int heldProx;
    int newValue;

    tableBase = (object >> 8) == 0x22 ? mapUserButton : yardUserButton;

    if (GetAsyncKeyState(0x11) & 0x8000) {
        savedGamePaused = GamePaused;
        win_GetObjRect(object, &rect);
        win_Open(0x2400, rect.left, 0);
        MySetCapture(win_hwnd[36]);
        slot = (int far *)(tableBase + button);
        win_SetProxItem(*slot + 0x2402);
        ButtonHeldInit();
        SetPause(1);
        savedBase = button;
        do {
            ;
        } while (!win_GetEvent(&event));
        ButtonHeldEnd();
        SetPause(savedGamePaused);
        MyReleaseCapture();
        heldProx = win_GetProxEvent();
        win_SetProxItem(0x2400);
        GetWindowRect(win_hwnd[36], &rect);
        win_Close(0x2400);
        pt.x = event.x;
        pt.y = event.y;
        ClientToScreen(win_hwnd[36], &pt);
        if (PtInRect(&rect, pt)) {
            newValue = heldProx - 0x2402;
            *slot = newValue;
            if (GetAsyncKeyState(0x10) & 0x8000) {
                SetUserButton(object, *slot);
            } else {
                mapUserButton[button] = newValue;
                yardUserButton[button] = newValue;
                SetUserButton(object, *slot);
                if ((object >> 8) == 0x22)
                    SetUserButton(object + 0xfb, *slot);
                else
                    SetUserButton(object - 0xfb, *slot);
            }
        }
        return;
    }

    switch (*(int far *)(tableBase + button)) {
    case 0:
        OpenModeWindow();
        break;
    case 1:
        OpenCasteWindow();
        break;
    case 2:
        OpenHistoryWindow();
        break;
    case 3:
        OpenInfoWindow();
        break;
    case 4:
        if (!showTrails) {
            if (match_position) {
                match_position = 0;
                StopSong();
                match_position = 1;
            }
        }
        showTrails = (showTrails == 0);
        break;
    case 5:
        GamePaused ^= 1;
        SetPause(GamePaused);
        break;
    case 6:
        if (GameSpeed == 3)
            GameSpeed = 0;
        else
            GameSpeed++;
        SetMenuEntries();
        switch (GameSpeed) {
        case 0:
            EditMessage(0x14bL, 0xb4, 0, 1);
            return;
        case 1:
            EditMessage(0x160L, 0xb4, 0, 1);
            return;
        case 2:
            EditMessage(0x177L, 0xb4, 0, 1);
            return;
        case 3:
            EditMessage(0x18cL, 0xb4, 0, 1);
            return;
        }
        break;
    case 7:
        OptionStates[1] = (OptionStates[1] != 1);
        SetMenuEntries();
        if (OptionStates[1] == 0) {
            StopSong();
            return;
        }
        break;
    case 8:
        MysteryButton();
        return;
    case 9:
        OptionStates[2] = (OptionStates[2] != 1);
        SetMenuEntries();
        return;
    case 10:
        OptionStates[5] = (OptionStates[5] != 1);
        SetMenuEntries();
        return;
    case 11:
        OptionStates[0] = (OptionStates[0] != 1);
        SetMenuEntries();
        return;
    case 12:
        OptionStates[3] = (OptionStates[3] != 1);
        SetMenuEntries();
        return;
    case 13:
        OptionStates[4] = (OptionStates[4] != 1);
        SetMenuEntries();
        return;
    case 14:
        KillTimer(rootWnd, 0);
        SaveGame(1);
        SetTimer(rootWnd, 0, 0x11, lpTimerFunc);
        return;
    case 15:
        if (win_IsWinOpen(0x1900))
            YardToMap();
        if (!win_IsWinOpen(0))
            win_Open(0, 0, 0);
        BringWindowToTop(win_hwnd[0]);
        UpdateWindow(win_hwnd[0]);
        GotoMyAnt();
        break;
    }
}
