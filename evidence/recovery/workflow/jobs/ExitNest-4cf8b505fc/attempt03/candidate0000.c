/*
 * ExitNest: bring the player's ant back out to the yard surface.  The
 * theme is tried and the nest cell restamped, then MeLocY is folded from
 * MeLocX (mod 0x40) to pick a hole-map row; a missing hole on that row is
 * created with MakeNewHoleB/MakeNewHoleR (by plane) and MeLocX becomes the
 * hole's column.  A queen steps twice as far as a worker (scale).  The
 * initial heading comes from GetDir toward the goal when match_position[0]
 * is 1, a fixed left/right heading when match_position[0] already equals
 * MePlane, or GetMyDir toward the matched target otherwise (falling back
 * to a random SRand8 heading when it fails).  Up to eight absSearchDirs
 * offsets around that heading are tried via IsNotObstacle/Dx8/Dy8 until
 * one lands on open ground; failing all eight instead just nudges MeLocX
 * by scale (wrapped at 0x7f) and keeps the original heading.  Finally the
 * ant is stamped onto plane 1 with SetMyLife.
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern int far match_position[];
extern int far MeGoalX;
extern int far MeGoalY;
extern signed char far absSearchDirs[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];

extern void far TryAntTheme(void);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far MakeNewHoleB(int x);
extern void far MakeNewHoleR(int x);
extern int far GetDir(int x, int y, int tx, int ty);
extern int far GetMyDir(int flag, int x, int y, int midx, int gx, int gy);
extern int far SRand8(void);
extern int far IsNotObstacle(int flag, int x, int y);

void far ExitNest(void)
{
    int scale;
    int dir0;
    int newx, newy;
    int di;
    int si;

    TryAntTheme();
    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0);

    MeLocY = MeLocX & 0x3f;

    if (MePlane == 2) {
        if (HoleMapB[MeLocY] == 0)
            MakeNewHoleB(MeLocX);
        MeLocX = HoleMapB[MeLocY];
    } else {
        if (HoleMapR[MeLocY] == 0)
            MakeNewHoleR(MeLocX);
        MeLocX = HoleMapR[MeLocY];
    }

    scale = (MeType == 0x60) ? 2 : 1;

    if (match_position[0] == 1) {
        dir0 = GetDir(MeLocX, MeLocY, MeGoalX, MeGoalY);
        if (dir0 > 0)
            dir0--;
    } else if (match_position[0] == MePlane) {
        if (MeLocX >= 0x40)
            dir0 = 6;
        else
            dir0 = 2;
    } else {
        dir0 = GetMyDir(1, MeLocX, MeLocY, match_position[0], MeGoalX, MeGoalY);
        if (dir0 < 0)
            dir0 = SRand8();
    }

    for (si = 0; si < 8; si++) {
        di = (dir0 + absSearchDirs[si + 0x6c]) & 7;
        newy = MeLocY + scale * (signed char)Dy8[di];
        newx = MeLocX + scale * (signed char)Dx8[di];
        if (IsNotObstacle(1, newx, newy)) {
            MeLocX = newx;
            MeLocY = newy;
            MeDir = di;
            break;
        }
    }

    if (si == 8) {
        MeDir = dir0;
        MeLocX = (MeLocX + scale) & 0x7f;
    }

    MePlane = 1;
    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
}
