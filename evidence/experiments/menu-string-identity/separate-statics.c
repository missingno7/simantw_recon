/* Reviewed menu unit. Target SetMenuEntries, PauseGame, and SetPause all
 * address the same DGROUP strings at 0x900 and 0x911. The remaining bodies
 * come from preserved exact-body sources; ProcMenu is not claimed here. */

extern int far GameSpeed;
extern int far GamePaused;
extern int far OptionStates[];
extern int far songsOnFlag;
extern int far effectsOnFlag;
extern void far SetMenuItemState(int item, int state);
extern void far SetMenuOptionText(int item, char far *text);
extern void far UpdateUserButtons(void);
struct WindPromptTable {
    int header[4];
    char far *yardPrompt;        /* +8 */
    char far *toolTenPrompt;     /* +0xc */
    int filler[26];
    char far *toolElevenPrompt;  /* +0x44 */
};
extern int far CurGameTool;
extern struct WindPromptTable far * far WindPromptStrs;
extern void far EndLifeTransferMode(void);
extern void far EndTargetMode(void);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far win_SetObjSelectedState(int flag, int objectNumber);
extern int near rootWnd;
extern char far helpFile[];
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);
static char near menuUnpause[] = "Un&pause\tShift+0";
static char near menuPause[] = "&Pause\tShift+0";




void far SetMenuEntries(void)
{
    int item;
    

    for (item = 0x43; item <= 0x46; item++)
        SetMenuItemState(item, (item - GameSpeed == 0x43) ? 0x10 : 0x20);
    SetMenuOptionText(0x41, GamePaused ? menuUnpause : menuPause);
    for (item = 0x31; item <= 0x36; item++)
        SetMenuItemState(item, OptionStates[item - 0x31] ? 0x10 : 0x20);
    UpdateUserButtons();
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];
}

void far PauseGame(int mode)
{
    int item;

    if (mode == 0) {
        if (CurGameTool == 0xa)
            EndLifeTransferMode();
        else if (CurGameTool == 0xb)
            EndTargetMode();
    }

    GamePaused = mode;

    if (mode != 0) {
        if (CurGameTool == -1)
            EditMessage((long)WindPromptStrs->yardPrompt, -2, -1, 1);
        else if (CurGameTool == 0xa)
            EditMessage((long)WindPromptStrs->toolTenPrompt, -2, -1, 1);
        else if (CurGameTool == 0xb)
            EditMessage((long)WindPromptStrs->toolElevenPrompt, -2, -1, 1);
    } else {
        EditMessage(0L, -2, -1, 1);
    }

    clip_SetWin(0);
    win_SetObjSelectedState(0xf, mode);
    clip_Off();

    for (item = 0x43; item <= 0x46; item++)
        SetMenuItemState(item, (item - GameSpeed == 0x43) ? 0x10 : 0x20);
    SetMenuOptionText(0x41, GamePaused ? menuUnpause : menuPause);
    for (item = 0x31; item <= 0x36; item++)
        SetMenuItemState(item, OptionStates[item - 0x31] ? 0x10 : 0x20);
    UpdateUserButtons();
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];
}

void far SetPause(int mode)
{
    int item;

    if (mode == 0) {
        if (CurGameTool == 0xa)
            EndLifeTransferMode();
        else if (CurGameTool == 0xb)
            EndTargetMode();
    }

    GamePaused = mode;

    if (mode != 0) {
        if (CurGameTool == -1)
            EditMessage((long)WindPromptStrs->yardPrompt, -2, -1, 1);
        else if (CurGameTool == 0xa)
            EditMessage((long)WindPromptStrs->toolTenPrompt, -2, -1, 1);
        else if (CurGameTool == 0xb)
            EditMessage((long)WindPromptStrs->toolElevenPrompt, -2, -1, 1);
    } else {
        EditMessage(0L, -2, -1, 1);
    }

    clip_SetWin(0);
    win_SetObjSelectedState(0xf, mode);
    clip_Off();

    for (item = 0x43; item <= 0x46; item++)
        SetMenuItemState(item, (item - GameSpeed == 0x43) ? 0x10 : 0x20);
    SetMenuOptionText(0x41, GamePaused ? menuUnpause : menuPause);
    for (item = 0x31; item <= 0x36; item++)
        SetMenuItemState(item, OptionStates[item - 0x31] ? 0x10 : 0x20);
    UpdateUserButtons();
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];
}

void ProcMenuHelp(unsigned int context)
{
    WinHelp(rootWnd, helpFile, 1, (unsigned long)(unsigned int)context);
}

