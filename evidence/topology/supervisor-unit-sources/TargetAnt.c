/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3e11] -> CurGameTool (one selector word per symbol in the object).
 *
 * TargetAnt toggles the target-selection mode.  The mode/tool cell used
 * here is the MAPSYM-named far int match_position (its exact address,
 * 0x7c22 in segment 9, matches the binding for this instruction; unrelated
 * to the generic "match_position" placeholder name used by other scaffold
 * stand-ins for representative segment-9 offsets).  On re-entry (mode
 * already 11) it clears the mode and restores the paused state; otherwise
 * it saves GamePaused, enters mode 11 and pauses.
 */
extern int far match_position[];
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
