/*
 * GetMyNextRandDirs: chase (a,b) from (x,y) on plane by repeatedly
 * calling GetMyBestDirs and walking along Dx8/Dy8 for the returned
 * direction, up to 64 steps, while GetMyBestDirs keeps succeeding
 * (result >= 0). When the walk stops because the last GetMyBestDirs
 * call itself failed (result < 0) or the step budget was exhausted
 * (forcing a -1 sentinel), any failure code other than -2 falls back to
 * a single direct GetMyBestDirs(plane,x,y,a,b) call from the original
 * position. A -2 failure (no candidate direction at all) instead arms
 * MeCrazyCnt=-1 and defers to GetMyRandDirs, which returns two
 * directions through far out-parameters (hypothesis names/targets;
 * offsets 0xa0d8/0x78a4 in match_position's segment carry no MAPSYM
 * name in the inspection packet). GetMyBestDirs is declared far; LINK
 * rewrites the same-segment far call to nop/push cs/call near.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far MeCrazyCnt;
extern int far match_position[];

extern int far GetMyBestDirs(int plane, int x, int y, int a, int b);
extern void far GetMyRandDirs(int plane, int x, int y, int a, int b,
                               int far *outDirA, int far *outDirB);

int far GetMyNextRandDirs(int plane, int x, int y, int a, int b)
{
    int dir;
    int nx;
    int ny;
    int tries;

    tries = 0;
    dir = GetMyBestDirs(plane, x, y, a, b);
    if (dir >= 0) {
        nx = x + Dx8[dir];
        ny = y + Dy8[dir];
        while (dir >= 0 && tries < 0x40) {
            dir = GetMyBestDirs(plane, nx, ny, a, b);
            if (dir >= 0) {
                nx += Dx8[dir];
                ny += Dy8[dir];
            }
            tries++;
        }
        if (dir >= 0)
            dir = -1;
    }
    if (dir != -2)
        return GetMyBestDirs(plane, x, y, a, b);

    MeCrazyCnt = -1;
    GetMyRandDirs(plane, x, y, a, b,
                  (int far *)&match_position[0x78a4 / 2],
                  (int far *)&match_position[0xa0d8 / 2]);
}
