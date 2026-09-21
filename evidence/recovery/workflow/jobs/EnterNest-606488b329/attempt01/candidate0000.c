/*
 * EnterNest: take the player's ant from the yard into the nest.  The ant
 * theme is tried, an active alarm drop is cancelled quietly, the ant's
 * yard life cell is cleared, and it reappears on nest plane 3 (from the
 * right half of the yard, MeLocX > 0x40) or 2, keeping its former row as
 * its column and starting at row 2 for a yellow queen (MeType 0x60) or 1
 * otherwise, facing direction 4.  Its tile is dug and its life cell set
 * with the entering code 0xff.
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern int far MeDropAlarm;

extern void far TryAntTheme(void);
extern void far SetAlarmDropState(int state, int quiet);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far DigMyTile(int plane, int x, int y);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);

void far EnterNest(void)
{
    TryAntTheme();
    if (MeDropAlarm != 0)
        SetAlarmDropState(0, 1);
    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    MePlane = (MeLocX > 0x40) ? 3 : 2;
    MeLocX = MeLocY;
    MeLocY = (MeType == 0x60) ? 2 : 1;
    MeDir = 4;
    DigMyTile(MePlane, MeLocX, MeLocY);
    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
}
