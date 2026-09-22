/*
 * TargetAnt toggles the target-selection mode.  The mode/tool cell used
 * here is the MAPSYM-named far int match_position (its exact address,
 * 0x7c22 in segment 9, matches the binding for this instruction; unrelated
 * to the generic "match_position" placeholder name used by other scaffold
 * stand-ins for representative segment-9 offsets).  On re-entry (mode
 * already 11) it clears the mode and restores the paused state; otherwise
 * it saves GamePaused, enters mode 11 and pauses.
 */
extern int far match_position;
extern int far GamePaused;
extern int far SaveGamePaused;
extern void far PauseGame(int paused);

void TargetAnt(void)
{
    if (match_position == 11) {
        match_position = -1;
        PauseGame(SaveGamePaused);
    } else {
        SaveGamePaused = GamePaused;
        match_position = 11;
        PauseGame(1);
    }
}
