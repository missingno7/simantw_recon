/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3e11] -> CurGameTool (one selector word per symbol in the object).
 *
 * StartLifeTransfer toggles the target-selection mode into life-transfer
 * mode 10, using the same MAPSYM-named far int CurGameTool
 * (segment 9, byte offset 0x7c22) that TargetAnt uses for mode 11.  On
 * re-entry (mode already 10) it clears the mode and restores the paused
 * state; otherwise it saves GamePaused, enters mode 10 and pauses.  No
 * explicit pointer local is declared so /Og hoists the far address into a
 * frame-resident CSE temporary reloaded through LES, matching the target.
 */
extern int far match_position[];
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
