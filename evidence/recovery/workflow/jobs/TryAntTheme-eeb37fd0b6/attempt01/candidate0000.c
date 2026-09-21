/*
 * Hypothesis: start the next ant theme only after the historical 0x1c20
 * tick interval.  The timestamp and match-position word are far data in the
 * SIMONE data segment; a third position rolls back to the base theme song.
 */
extern unsigned long far TickCount(void);
extern unsigned long far LastThemeTime;
extern unsigned int far match_position;
extern void far myBeginSong(unsigned int song, unsigned int mode);

void far TryAntTheme(void)
{
    unsigned long now;

    now = TickCount();
    if (now < LastThemeTime + 0x1c20)
        return;
    LastThemeTime = now;
    ++match_position;
    if (match_position > 2) {
        match_position = 0;
        myBeginSong(match_position + 0x2713, 0x7e);
    }
}
