/*
 * ProcMenu consumes the command id at byte 12 of the window event, executes
 * the selected application or menu action, then refreshes the menu state for
 * option, pause and speed changes. Ordinary actions only reach the final log.
 */
struct MenuCommand {
    unsigned char reserved[12];
    union {
        unsigned int word;
        struct { unsigned char byte; } bytes;
    } id;
};

struct WindPromptTable {
    int header[4];
    long yardPrompt;
    long toolTenPrompt;
    int filler1[20];
    char far *scoreTitlePrompt;
    int filler2[4];
    long toolElevenPrompt;
};

extern int near rootWnd;
extern int near YardMode;
extern int near MapPlane;
extern int near win_hwnd[];
extern int far GameSpeed;
extern int far GamePaused;
extern int far CurGameTool;
extern int far fileWaitFlag;
extern volatile int far OptionStates[];
extern int far songsOnFlag;
extern int far effectsOnFlag;
extern struct WindPromptTable far * far WindPromptStrs;
extern char far helpFile[];

extern void far WinPrintf(char far *format, ...);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far OpenEditWindow(void);
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);
extern void far AboutDialog(void);
extern void far NewGame(int mode);
extern void far OpenMapYard(void);
extern void far OpenModeWindow(void);
extern void far OpenCasteWindow(void);
extern void far OpenHistoryWindow(void);
extern void far OpenInfoWindow(void);
extern void far ScoreDialog(void);
extern void far SetYardMode(int mode);

extern void far SetMapPlane(int plane);

extern int far win_IsWinOpen(int window);
extern void far MapToYard(void);

extern void far win_Swap(int first, int second);
extern void far pascal UpdateWindow(int window);

extern int far pascal BringWindowToTop(int window);

extern void MakeEditOpen(void);

extern void far StopSong(void);
extern void far SetMenuItemState(int item, int state);
extern void far SetMenuOptionText(int item, char far *text);
extern void far EndLifeTransferMode(void);
extern void far EndTargetMode(void);
extern void far EditMessage(long position, int a, int b, int mode);

extern void far clip_SetWin(int window);
extern void far win_SetObjSelectedState(int object, int state);
extern void far clip_Off(void);
extern void far UpdateUserButtons(void);


void far ProcMenu(struct MenuCommand far *command)
{
    volatile int id;
    int item;
    int mode;
    int paused;

    WinPrintf("menu %u", command->id.word);
    switch (id = command->id.bytes.byte) {
    default:
        if (id >= 0x31 && id <= 0x36)
            goto option_handler;
        break;

    case 1:
        AboutDialog();
        break;

    case 3:
        myBeginSong(0x2711, 0x7e);
        NewGame(0);
        break;

    case 4:
    case 5:
    case 6:
    case 8:
        fileWaitFlag = id;
        break;

    case 17:
        OpenEditWindow();
        break;
    case 18:
        OpenMapYard();
        break;
    case 19:
        OpenModeWindow();
        break;
    case 20:
        OpenCasteWindow();
        break;
    case 21:
        OpenHistoryWindow();
        break;
    case 22:
        OpenInfoWindow();
        break;
    case 23:
        ScoreDialog();
        break;

    case 24:
        WinHelp(rootWnd, helpFile, 3, 0L);
        break;

    case 33:
    case 34:
    case 35:
    case 36:
        mode = id - 0x21;
        if (mode != YardMode)
            SetYardMode(mode);
        if (MapPlane != 0)
            SetMapPlane(0);
        if (win_IsWinOpen(0x1900))
            MapToYard();
        if (win_IsWinOpen(0x2200) && win_IsWinOpen(0x2300)) {
            win_Swap(0x2200, 0x2300);
            UpdateWindow(win_hwnd[35]);
            BringWindowToTop(win_hwnd[25]);
        }
        break;

    case 38:
    case 39:
    case 40:
        SetMapPlane(id - 0x25);
        MakeEditOpen();
        break;

    case 50:
        StopSong();
        goto option_handler;

option_handler:
        OptionStates[id - 0x31] = !OptionStates[id - 0x31];

        for (item = 0x43; item <= 0x46; item++)
            SetMenuItemState(item,
                item - GameSpeed == 0x43 ? 0x10 : 0x20);
        if (GamePaused != 0)
            SetMenuOptionText(0x41, "Un&pause\tShift+0");
        else
            SetMenuOptionText(0x41, "&Pause\tShift+0");
        for (item = 0x31; item <= 0x36; item++)
            SetMenuItemState(item,
                OptionStates[item - 0x31] == 1 ? 0x10 : 0x20);
        goto refresh_menu;

    case 65:
        GamePaused = GamePaused ^ 1;
        paused = GamePaused;
        if (paused == 0) {
            if (CurGameTool == 10)
                EndLifeTransferMode();
            else if (CurGameTool == 11)
                EndTargetMode();
        }
        GamePaused = paused;

        if (paused == 0)
            EditMessage(0L, -2, -1, 1);
        else if (CurGameTool == -1)
            EditMessage(WindPromptStrs->yardPrompt, -2, -1, 1);
        else if (CurGameTool == 10)
            EditMessage(WindPromptStrs->toolTenPrompt, -2, -1, 1);
        else if (CurGameTool == 11)
            EditMessage(WindPromptStrs->toolElevenPrompt, -2, -1, 1);
        else
            EditMessage(0L, -2, -1, 1);
        clip_SetWin(0);
        win_SetObjSelectedState(paused, 0x0f);
        clip_Off();

        for (item = 0x43; item <= 0x46; item++)
            SetMenuItemState(item,
                item - GameSpeed == 0x43 ? 0x10 : 0x20);
        if (GamePaused != 0)
            SetMenuOptionText(0x41, "Un&pause\tShift+0");
        else
            SetMenuOptionText(0x41, "&Pause\tShift+0");
        for (item = 0x31; item <= 0x36; item++)
            SetMenuItemState(item,
                OptionStates[item - 0x31] == 1 ? 0x10 : 0x20);
        goto refresh_menu;

    case 67:
    case 68:
    case 69:
    case 70:
        GameSpeed = id - 0x43;
        for (item = 0x43; item <= 0x46; item++)
            SetMenuItemState(item,
                item - GameSpeed == 0x43 ? 0x10 : 0x20);
        if (GamePaused != 0)
            SetMenuOptionText(0x41, "Un&pause\tShift+0");
        else
            SetMenuOptionText(0x41, "&Pause\tShift+0");
        for (item = 0x31; item <= 0x36; item++)
            SetMenuItemState(item,
                OptionStates[item - 0x31] == 1 ? 0x10 : 0x20);
        goto refresh_menu;
    }

    goto log_command;

refresh_menu:
    UpdateUserButtons();
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];

log_command:
    WinPrintf("menu %u", id);
}

