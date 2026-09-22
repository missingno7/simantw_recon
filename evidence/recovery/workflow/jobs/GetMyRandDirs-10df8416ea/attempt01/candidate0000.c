/*
 * GetMyRandDirs: pick a movable heading near (a2,a3) toward (a4,a5),
 * writing the chosen heading into *pdir (GetDir()-1) and a rotation sign
 * into *prot.  Bails out immediately (-1, *pdir/*prot untouched) if the
 * two points already coincide (GetDis<=0).  Otherwise it marks each of
 * the 8 Dx8/Dy8-offset cells movable when it is not the ant's last
 * position and TileCanBeMovedOn accepts it (flag set when MeCmd==2);
 * bailing out again if none are movable.  When *prot==0 it alternates
 * outward from *pdir (forward dir1, backward dir2) up to 8 tries,
 * committing the first movable side found with *prot set to +-1
 * accordingly.  Otherwise it searches only the side *prot's sign
 * selects, and once a movable cell is found there it is accepted only if
 * its GetDis to (a4,a5) does not exceed the original distance,
 * committing with *prot reset to 0.
 */
extern int near MeCmd;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far MeLastX;
extern int far MeLastY;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeGoalPlane;

extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetDir(int x, int y, int tx, int ty);
extern int far TileCanBeMovedOn(int a1, int x, int y, int goalPlane, int goalX, int goalY, int flag);

int far GetMyRandDirs(int far *prot, int far *pdir, int a1, int a2, int a3, int a4, int a5)
{
    int initDis;
    int bestDir;
    int flag;
    int candX, candY;
    int si;
    char canMove[8];
    int dir1, dir2;
    int counter;
    int result;

    result = -1;

    initDis = GetDis(a2, a3, a4, a5);
    if (initDis <= 0)
        return result;

    bestDir = -2;
    flag = (MeCmd == 2) ? 1 : 0;

    for (si = 0; si < 8; si++) {
        candY = a3 + (signed char)Dy8[si];
        candX = a2 + (signed char)Dx8[si];

        if (candX == MeLastX && candY == MeLastY) {
            canMove[si] = 0;
            continue;
        }

        if (TileCanBeMovedOn(a1, candX, candY, MeGoalPlane, MeGoalX, MeGoalY, flag)) {
            bestDir = si;
            canMove[si] = 1;
        } else {
            canMove[si] = 0;
        }
    }

    if (bestDir < 0)
        return result;

    dir1 = *pdir;
    dir2 = dir1;

    if (*prot == 0) {
        for (counter = 0; counter < 8; counter++) {
            if (canMove[dir1]) {
                result = dir1;
                *pdir = GetDir(a2, a3, a4, a5) - 1;
                *prot = 1;
                return result;
            }
            if (canMove[dir2]) {
                result = dir2;
                *pdir = GetDir(a2, a3, a4, a5) - 1;
                *prot = -1;
                return result;
            }
            dir1 = (dir1 + 1) & 7;
            dir2 = (dir2 - 1) & 7;
        }
        return result;
    }

    counter = 0;
    for (;;) {
        if (*prot <= 0) {
            if (canMove[dir2]) {
                si = dir2;
                break;
            }
        } else {
            if (canMove[dir1]) {
                si = dir1;
                break;
            }
        }
        dir1 = (dir1 + 1) & 7;
        dir2 = (dir2 - 1) & 7;
        counter++;
        if (counter >= 8)
            return result;
    }

    candY = a3 + (signed char)Dy8[si];
    candX = a2 + (signed char)Dx8[si];
    if (GetDis(candX, candY, a4, a5) > initDis)
        return result;

    *pdir = GetDir(a2, a3, a4, a5) - 1;
    *prot = 0;
    result = si;
    return result;
}
