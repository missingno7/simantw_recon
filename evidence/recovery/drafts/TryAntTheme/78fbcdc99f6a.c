/*
 * Hypothesis: start the next ant theme only after the historical 0x1c20
 * tick interval.  The timestamp and match-position word are far data in the
 * SIMONE data segment; a third position rolls back to the base theme song.
 */
extern long far TickCount(void);
extern long far LastThemeTime;
extern int far match_position;
extern void far myBeginSong(unsigned int song, unsigned int mode);

void far TryAntTheme(void)
{
    int far * volatile position;

    if (TickCount() < LastThemeTime + 0x1c20)
        return;
    LastThemeTime = TickCount();
    position = &match_position;
    *position = *position + 1;
    if (*position <= 2)
        return;
    *position = 0;
    myBeginSong(*position + 0x2713, 0x7e);
}
