/*
 * Hypothesis: TargetAnt is the same mode-toggle primitive as
 * StartLifeTransfer, using mode 11.  It saves GamePaused on entry, restores
 * SaveGamePaused on re-entry, and shares the final PauseGame call.  CurGameTool
 * is carried as a far pointer because the target saves its PACK address and
 * selector in the local frame while switching ES for the other globals.
 */
extern int far CurGameTool;
extern int far GamePaused;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);

void TargetAnt(void)
{
    int far *tool;

    tool = &CurGameTool;
    if (*tool == 11) {
        *tool = -1;
        PauseGame(SaveGamePaused);
    } else {
        SaveGamePaused = GamePaused;
        *tool = 11;
        PauseGame(1);
    }
}
