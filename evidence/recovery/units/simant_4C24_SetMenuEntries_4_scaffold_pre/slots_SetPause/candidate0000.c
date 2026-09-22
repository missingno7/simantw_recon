/* SetPause: set the pause state.  Unpausing (mode==0) first closes any
 * open tool mode (life-transfer or target mode via CurGameTool 0xa/0xb),
 * then stores GamePaused=mode.  When pausing (mode!=0) it posts a
 * CurGameTool-specific prompt (the yard prompt for -1, tool-ten prompt
 * for 0xa, tool-eleven prompt for 0xb, or nothing for any other tool);
 * unpausing always posts the generic (position 0) message.  It then
 * clips the window off, selects/deselects the pause button (object
 * 0xf) and refreshes the whole menu exactly like SetMenuEntries: speed
 * items 0x43..0x46, the pause item 0x41's text, option items 0x31..0x36,
 * UpdateUserButtons and the songs/effects flag mirrors.
 */

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
