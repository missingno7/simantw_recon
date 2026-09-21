/*
 * Hypothesis: start the next ant theme only after the historical 0x1c20
 * tick interval.  The timestamp and match-position word are far data in the
 * SIMONE data segment; a third position rolls back to the base theme song.
 */
extern unsigned long far TickCount(void);
extern unsigned long far LastThemeTime;
extern int far match_position;
extern void far myBeginSong(unsigned int song, unsigned int mode);

void far TryAntTheme(void)
{
    int far *position;

    if (TickCount() < LastThemeTime + 0x1c20)
        return;
    LastThemeTime = TickCount();
    position = &match_position;
    ++*position;
    if (*position <= 2)
        return;
    *position = 0;
    myBeginSong(*position + 0x2713, 0x7e);
}
