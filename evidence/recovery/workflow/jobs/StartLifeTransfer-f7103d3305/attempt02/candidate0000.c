/*
 * Hypothesis: starting life transfer saves the current game-pause state and
 * marks CurGameTool as mode 10.  Re-entering the mode restores the saved pause
 * value and clears CurGameTool instead.  Both paths share the final PauseGame
 * call; the far globals are the PACK words identified by their relocations.
 */
struct LifeTransferState {
    unsigned char beforeCurGameTool[0x7c22];
    int CurGameTool;
    unsigned char beforeGamePaused[0x2004];
    int GamePaused;
    unsigned char beforeSaveGamePaused[0x278];
    int SaveGamePaused;
};

extern struct LifeTransferState far lifeState;
extern void far PauseGame(int paused);

void StartLifeTransfer(void)
{
    if (lifeState.CurGameTool == 10) {
        lifeState.CurGameTool = -1;
        PauseGame(lifeState.SaveGamePaused);
    } else {
        lifeState.SaveGamePaused = lifeState.GamePaused;
        lifeState.CurGameTool = 10;
        PauseGame(1);
    }
}
