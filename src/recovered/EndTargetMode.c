extern int far CurGameTool;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);

void EndTargetMode(void)
{
    CurGameTool = -1;
    PauseGame(SaveGamePaused);
}
