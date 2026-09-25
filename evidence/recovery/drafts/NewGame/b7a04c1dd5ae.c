/* Start or load a game scenario, restore the prior pause state while the
 * scenario dialog runs, then initialize the selected game type and its views. */
extern int far GamePaused;
extern int far CurGameType;
extern int far CurGameTool;
extern int far CurExpTool;
extern int far JustXfered;
extern int far LayDownQueenMode;
extern int far gGameNeedsSaving;
extern int near QueenStorageB;
extern int near MapPlane;
extern int near MePlane;
extern int near YardMode;
extern int near MeLocX;
extern int near MeLocY;
extern int near editForce;
extern int near win_hwnd[];

extern void far SetPause(int paused);
extern int far DoScenario(int scenario);
extern void far EditMessage(long position, int a, int b, int mode);
extern int far LoadGame(int a, int b);
extern void far EndLifeTransferMode(void);
extern void far EndTargetMode(void);
extern void far win_SetButtonBitmaps(int object, unsigned int up,
                                     unsigned int down);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far SetDefaultWindPrompt(int mode);
extern void far SetEditWinTitle(char far *title);
extern void UpdateLayQueenModeDisplay(void);
extern void far RandYard(void);
extern void far win_Open(int window);
extern void OpenCasteWindow(void);
extern void OpenModeWindow(void);
extern void SetMapPlane(int plane);
extern int far win_IsWinOpen(int window);
extern void YardToMap(void);
extern void MapToYard(void);
extern void SetMapTitle(void);
extern void far OpenEditWindow(void);
extern void SetYardMode(int mode);
extern int far win_IsWinZoomed(int window);
extern void far win_Zoom(int window);
extern int far CenterEdit(int x, int y);
extern void far MSClipStart(int window);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);
extern void far MSClipEnd(void);
extern void far UpdateEdit(void);
extern void ClearBookmarks(void);
extern void far ClearLastFileName(void);
extern void far pascal InvalidateRect(int window, void far *rect, int erase);

int far NewGame(int scenario)
{
    int oldPause;
    int choice;
    int tool;
    int far *gameType;

    oldPause = GamePaused;
    gGameNeedsSaving = 0;

    for (;;) {
        SetPause(1);
        choice = DoScenario(scenario);
        SetPause(oldPause);
        EditMessage(0L, -2, -1, 1);

        if (choice == 0x205)
            return -1;
        if (choice == 0x207) {
            if (!LoadGame(0, 0))
                continue;
            choice = 1;
            goto selected;
        }
        choice -= 0x202;
        if (choice == 0)
            choice = 1;
        else if (--choice == 0)
            choice = 2;
        else if (--choice == 0)
            choice = 3;
        else {
            --choice;
            --choice;
            choice = 0;
        }
        break;
    }

selected:
    gameType = &CurGameType;
    *gameType = choice;
    tool = CurGameTool;
    if (tool == 10)
        EndLifeTransferMode();
    else if (tool == 11)
        EndTargetMode();

    if (*gameType == 3)
        CurExpTool = 0;
    if (*gameType == 3)
        win_SetButtonBitmaps(0x220a, 0x38d6, 0x38a4);
    else
        win_SetButtonBitmaps(0x220a, 0x3888, 0x3856);
    win_SetObjSelectedState(0x220a, 0);
    SetDefaultWindPrompt(1);
    SetEditWinTitle((char far *)0);

    QueenStorageB = 0;
    LayDownQueenMode = 1;
    JustXfered = 1;
    UpdateLayQueenModeDisplay();
    RandYard();

    if (*gameType == 0) {
        win_Open(0);
        OpenCasteWindow();
        OpenModeWindow();
        InvalidateRect(win_hwnd[19], 0, 0);
        InvalidateRect(win_hwnd[18], 0, 0);
        SetMapPlane(MapPlane);
        if (MapPlane != 0) {
            if (!win_IsWinOpen(0x100))
                YardToMap();
        } else if (!win_IsWinOpen(0x1900)) {
            MapToYard();
        }
        SetMapTitle();
        OpenEditWindow();
        SetMapPlane(MePlane);
        SetYardMode(YardMode);

        if (!win_IsWinOpen(0x100))
            YardToMap();
        if (!*gameType && !win_IsWinZoomed(0))
            win_Zoom(0);

        if (CenterEdit(MeLocX, MeLocY) && win_IsWinOpen(0x100)) {
            MSClipStart(win_hwnd[17]);
            EraseMapCursor();
            DrawMapCursor();
            MSClipEnd();
            editForce = 1;
            UpdateEdit();
            ClearBookmarks();
            ClearLastFileName();
        }
    }

    gGameNeedsSaving = 0;
    return choice;
}
