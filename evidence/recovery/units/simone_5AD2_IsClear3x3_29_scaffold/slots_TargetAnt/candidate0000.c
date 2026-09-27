/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3e11] -> CurGameTool (one selector word per symbol in the object).
 *
 * TargetAnt toggles the target-selection mode.  It uses the named PACK
 * word CurGameTool, shared with StartLifeTransfer, for mode 11.  On
 * re-entry it clears the mode and restores the paused state; otherwise
 * it saves GamePaused, enters mode 11 and pauses.
 */
extern int far CurGameTool;
extern int far GamePaused;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);

void TargetAnt(void)
{
    if (CurGameTool == 11) {
        CurGameTool = -1;
        PauseGame(SaveGamePaused);
    } else {
        SaveGamePaused = GamePaused;
        CurGameTool = 11;
        PauseGame(1);
    }
}
