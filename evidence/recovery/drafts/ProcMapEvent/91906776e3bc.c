/*
 * ProcMapEvent: dense switch on event->message (0x102-0x118, 23 slots;
 * holes 0x103/0x104 fall to the shared no-op default) for the main map
 * edit screen.  Same lone-far-struct-pointer shape as ProcEditEvent, but
 * message 0x110's handler also reads a second word field at offset 8.
 *   0x102 - forward the event to MapAreaEvent(event).
 *   0x105 - MapToYard().
 *   0x106 - ClearMapScentButtons(); SetMapPlane(1).
 *   0x107 - ClearMapScentButtons(); SetMapPlane(2).
 *   0x108 - ClearMapScentButtons(); SetMapPlane(3); win_ToTop(0x100).
 *   0x109/0x10a - SetMapModeAnt(4 or 5).
 *   0x10b/0x10c/0x10d - SetMapModeAnt(8, 6 or 7).
 *   0x10e - when trails are off and the far match_position flag is
 *       nonzero, clear it, redraw the map and set it back to 1; either
 *       way toggle showTrails (the "== 0" idiom already seen for
 *       GamePaused in ProcEditEvent).
 *   0x10f - OpenModeWindow().
 *   0x110 - only when both GetKeyState(VK_CONTROL) and
 *       GetKeyState(VK_SHIFT) read down: read window object 0x110's rect,
 *       average its left/right edges (signed round-to-zero /2), compare
 *       that to event->value, and AddSomeAnts(1) when the value is less,
 *       else AddSomeAnts(0).  Control not held: GotoMyAnt().  Control
 *       held, shift not: AddFood(0x96, 1).
 *   0x111 - OpenCasteWindow().
 *   0x112..0x115 - MysteryButton/OpenHistoryWindow/ScoreDialog/
 *       OpenInfoWindow, each returning immediately (no common exit).
 *   0x116 - LessonTemp = 1; DoWinHelp(0x103).
 *   0x117 - MapToolsMenu(), returning immediately.
 *   0x118 - DrawCastePopUp(), returning immediately.
 */
struct EditEvent {
    char reserved[8];
    int value;
    char reserved2[2];
    int message;
};

struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near showTrails;
extern int far match_position;
extern int far LessonTemp;

extern void far MapAreaEvent(struct EditEvent far *event);
extern void far MapToYard(void);
extern void far ClearMapScentButtons(void);
extern void far SetMapPlane(int plane);
extern void far win_ToTop(int window);
extern void far SetMapModeAnt(int mode);
extern void far DrawMap(void);
extern void far OpenModeWindow(void);
extern int far pascal GetKeyState(int key);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far AddSomeAnts(int flag);
extern void far AddFood(int a, int b);
extern void far GotoMyAnt(void);
extern void far OpenCasteWindow(void);
extern void far MysteryButton(void);
extern void far OpenHistoryWindow(void);
extern void far ScoreDialog(void);
extern void far OpenInfoWindow(void);
extern void far DoWinHelp(int mode);
extern void far MapToolsMenu(void);
extern void far DrawCastePopUp(void);

void far ProcMapEvent(struct EditEvent far *event)
{
    int far *matchPos;
    struct WinRect rect;
    int val;

    switch (event->message) {
    case 0x102:
        MapAreaEvent(event);
        break;
    case 0x105:
        MapToYard();
        break;
    case 0x106:
        ClearMapScentButtons();
        SetMapPlane(1);
        break;
    case 0x107:
        ClearMapScentButtons();
        SetMapPlane(2);
        break;
    case 0x108:
        ClearMapScentButtons();
        SetMapPlane(3);
        win_ToTop(0x100);
        break;
    case 0x109:
        SetMapModeAnt(4);
        break;
    case 0x10a:
        SetMapModeAnt(5);
        break;
    case 0x10b:
        SetMapModeAnt(8);
        break;
    case 0x10c:
        SetMapModeAnt(6);
        break;
    case 0x10d:
        SetMapModeAnt(7);
        break;
    case 0x10e:
        matchPos = &match_position;
        if (showTrails == 0 && *matchPos != 0) {
            *matchPos = 0;
            DrawMap();
            *matchPos = 1;
        }
        showTrails = (showTrails == 0);
        break;
    case 0x10f:
        OpenModeWindow();
        break;
    case 0x110:
        if (GetKeyState(0x11) & 0x8000) {
            if (GetKeyState(0x10) & 0x8000) {
                win_GetObjRect(0x110, &rect);
                val = (rect.left + rect.right) / 2;
                if (event->value < val)
                    AddSomeAnts(1);
                else
                    AddSomeAnts(0);
            } else {
                AddFood(0x96, 1);
            }
        } else {
            GotoMyAnt();
        }
        break;
    case 0x111:
        OpenCasteWindow();
        break;
    case 0x112:
        MysteryButton();
        return;
    case 0x113:
        OpenHistoryWindow();
        return;
    case 0x114:
        ScoreDialog();
        return;
    case 0x115:
        OpenInfoWindow();
        return;
    case 0x116:
        LessonTemp = 1;
        DoWinHelp(0x103);
        break;
    case 0x117:
        MapToolsMenu();
        return;
    case 0x118:
        DrawCastePopUp();
        return;
    }
}
