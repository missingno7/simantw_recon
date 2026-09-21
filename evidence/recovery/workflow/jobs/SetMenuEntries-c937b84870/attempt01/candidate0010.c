/*
 * SetMenuEntries: refresh the game menu.  Speed items 0x43..0x46 show
 * the one matching GameSpeed checked (state 0x10, others 0x20); the
 * pause item 0x41 reads "Un&pause" or "&Pause" (both Shift+0) according
 * to GamePaused; option items 0x31..0x36 are checked when their far
 * OptionStates word is set; the user buttons are updated and the songs
 * and effects flags (DGROUP words addressed through selector slots) are
 * copied from option states 1 and 2.
 */
extern int far GameSpeed;
extern int far GamePaused;
extern int far OptionStates[];
extern int far songsOnFlag;
extern int far effectsOnFlag;

extern void far SetMenuItemState(int item, int state);
extern void far SetMenuOptionText(int item, char far *text);
extern void far UpdateUserButtons(void);

void far SetMenuEntries(void)
{
    int item;
    

    for (item = 0x43; item <= 0x46; item++)
        SetMenuItemState(item, (item == GameSpeed + 0x43) ? 0x10 : 0x20);
    SetMenuOptionText(0x41, GamePaused ? "Un&pause\tShift+0" : "&Pause\tShift+0");
    for (item = 0x31; item <= 0x36; item++)
        SetMenuItemState(item, OptionStates[item - 0x31] ? 0x10 : 0x20);
    UpdateUserButtons();
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];
}
