/* Candidate translation unit simant_4C24_PauseGame_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _PauseGame, _SetPause
 * SCAFFOLDED: unclaimed members _SetMenuEntries are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WindPromptTable {
    int header[4];
    char far *yardPrompt;        /* +8 */
    char far *toolTenPrompt;     /* +0xc */
    int filler[26];
    char far *toolElevenPrompt;  /* +0x44 */
};
extern int far CurGameTool;
extern int far GamePaused;
extern int far GameSpeed;
extern int far OptionStates[];
extern int far songsOnFlag;
extern int far effectsOnFlag;
extern struct WindPromptTable far * far WindPromptStrs;
extern void far EndLifeTransferMode(void);
extern void far EndTargetMode(void);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
extern void far win_SetObjSelectedState(int flag, int objectNumber);
extern void far SetMenuItemState(int item, int state);
extern void far SetMenuOptionText(int item, char far *text);
extern void far UpdateUserButtons(void);


void far pool_stub_SetMenuEntries(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMenuEntries)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMenuEntries.
 * It only reproduces the object's selector-pool allocation order for the
 * words BECA BECC BECE BED0 BED2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMenuEntries(void)
{
    volatile int t;

    t = (int)GameSpeed;
    t = (int)GamePaused;
    t = OptionStates[0];
    t = (int)songsOnFlag;
    t = (int)effectsOnFlag;
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
    SetMenuOptionText(0x41, GamePaused ? "Un&pause\tShift+0" : "&Pause\tShift+0");
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
    SetMenuOptionText(0x41, GamePaused ? "Un&pause\tShift+0" : "&Pause\tShift+0");
    for (item = 0x31; item <= 0x36; item++)
        SetMenuItemState(item, OptionStates[item - 0x31] ? 0x10 : 0x20);
    UpdateUserButtons();
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];
}

