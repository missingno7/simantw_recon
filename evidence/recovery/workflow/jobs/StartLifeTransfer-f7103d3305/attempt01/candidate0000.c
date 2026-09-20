/*
 * Hypothesis: starting life transfer saves the current game-pause state and
 * marks CurGameTool as mode 10.  Re-entering the mode restores the saved pause
 * value and clears CurGameTool instead.  Both paths share the final PauseGame
 * call; the far globals are the PACK words identified by their relocations.
 */
extern int far CurGameTool;
extern int far GamePaused;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);

void StartLifeTransfer(void)
{
    if (CurGameTool == 10) {
        CurGameTool = -1;
        PauseGame(SaveGamePaused);
    } else {
        SaveGamePaused = GamePaused;
        CurGameTool = 10;
        PauseGame(1);
    }
}
