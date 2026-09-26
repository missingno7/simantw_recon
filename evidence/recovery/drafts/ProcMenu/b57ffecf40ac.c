struct MenuCommand { unsigned char reserved[12]; unsigned int id; };
extern void far AboutDialog(void);
extern void far NewGame(void);
extern void far OpenEditWindow(void);
extern void far OpenMapYard(void);
extern void far OpenModeWindow(void);
extern void far OpenCasteWindow(void);
extern void far OpenHistoryWindow(void);
extern void far OpenInfoWindow(void);
extern void far ScoreDialog(void);
extern void far SetYardMode(int mode);
extern void far SetMapPlane(int plane);
extern void far MapToYard(void);
extern void far MakeEditOpen(void);
extern void far EndTargetMode(void);
extern void far EndLifeTransferMode(void);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far UpdateUserButtons(void);
extern int far win_IsWinOpen(int window);
extern void far win_Swap(int a, int b);
extern void far win_SetObjSelectedState(int object, int state);
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far StopSong(void);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far SetMenuItemState(int item, int state);
extern void far SetMenuOptionText(int item, char far *text);
extern void far WinPrintf(char far *format, ...);
extern int near MapPlane;
extern int near YardMode;
extern int near rootWnd;
extern int far GameSpeed;
extern int far GamePaused;
extern int far CurGameTool;
extern char far WindPromptStrs[];
extern int far Dx8[];
extern int far fileWaitFlag;
extern int far songsOnFlag;
extern int far effectsOnFlag;
extern int far GetWindPrompt(void);
extern int far randomWind;

void far ProcMenu(struct MenuCommand far *command)
{
    volatile int id;
    int i;
    int paused;

    WinPrintf("menu %u", command->id);
    id = (unsigned char)command->id;

    if (id < 1 || id > 70) {
        UpdateUserButtons();
        return;
    }

    switch (id) {
    case 1:
        NewGame();
        break;
    case 2:
        AboutDialog();
        break;
    case 3:
        OpenEditWindow();
        break;
    case 4:
        OpenMapYard();
        break;
    case 5:
        OpenModeWindow();
        break;
    case 6:
        OpenCasteWindow();
        break;
    case 7:
        OpenHistoryWindow();
        break;
    case 8:
        OpenInfoWindow();
        break;
    case 9:
        ScoreDialog();
        break;
    case 10:
        if (GamePaused)
            GamePaused = 0;
        else
            GamePaused = 1;
        break;
    case 11:
        StopSong();
        break;
    case 12:
        if (win_IsWinOpen(0x1900))
            MapToYard();
        else
            SetYardMode(YardMode);
        break;
    case 13:
        SetMapPlane(MapPlane);
        break;
    case 14:
        MakeEditOpen();
        break;
    case 15:
        EndTargetMode();
        EndLifeTransferMode();
        break;
    case 16:
        EditMessage(0L, 0, 0, 1);
        break;
    case 17:
        clip_SetWin(rootWnd);
        clip_Off();
        break;
    case 18:
        win_SetObjSelectedState(0x1900, 1);
        break;
    case 19:
        win_Swap(0x1900, 0x1902);
        break;
    case 20:
    case 21:
    case 22:
    case 23:
        SetYardMode(id - 20);
        break;
    case 24:
    case 25:
    case 26:
    case 27:
        GameSpeed = (int)(id - 24);
        break;
    case 28:
    case 29:
    case 30:
        myBeginSong(id - 28, 0x7e);
        break;
    case 31:
        if (songsOnFlag)
            StopSong();
        else
            myBeginSong(0x2711, 0x7e);
        break;
    case 32:
        SetMenuItemState(id, 1);
        SetMenuOptionText(id, WindPromptStrs);
        break;
    case 33:
        for (i = 0; i < 6; ++i)
            SetMenuItemState(0x31 + i, Dx8[i] == 1 ? 0x20 : 0x10);
        break;
    case 34:
        randomWind = 1;
        break;
    case 35:
        randomWind = 0;
        break;
    case 36:
        if (effectsOnFlag)
            effectsOnFlag = 0;
        else
            effectsOnFlag = 1;
        break;
    case 37:
        fileWaitFlag = id;
        break;
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
        paused = GamePaused;
        if (paused)
            GamePaused = 0;
        if (id >= 40 && id <= 70)
            SetMenuItemState(id, paused ? 0 : 1);
        if (paused)
            GamePaused = 1;
        break;
    }

    UpdateUserButtons();
}


