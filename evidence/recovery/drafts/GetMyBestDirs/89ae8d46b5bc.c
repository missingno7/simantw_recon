/*
 * GetMyBestDirs: pick the best of the 8 Dx8/Dy8 step directions from
 * (x, y) toward (a, b) on the given plane, matching the shape of the
 * already-admitted CheckMyBestDirs caller and GetRedBestDirs sibling.
 * best/fallback start at -1/-2 (best returned unchanged if the starting
 * distance to (a,b) is already <=0). Each direction whose step tile is
 * movable relative to the player's own goal (TileCanBeMovedOn(plane,
 * nx, ny, MeGoalPlane, MeGoalX, MeGoalY, MeCmd==2)) and whose stepped
 * distance improves on the current threshold updates the threshold; if
 * the stepped tile has life or is not clear it only updates the
 * fallback, otherwise it updates best. Returns best if set, else the
 * fallback.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far MeCmd;
extern int far MeGoalPlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far TileCanBeMovedOn(int plane, int nx, int ny, int goalPlane, int goalX, int goalY, int flag);
extern int far GetLife(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);

int far GetMyBestDirs(int plane, int x, int y, int a, int b)
{
    int best;
    int fallback;
    int flag;
    int threshold;
    int dir;
    int nx;
    int ny;
    int dis;

    best = -1;
    threshold = GetDis(x, y, a, b);
    fallback = best;
    if (threshold > 0) {
    fallback = -2;
    flag = (MeCmd == 2) ? 1 : 0;
    for (dir = 0; dir < 8; dir++) {
        ny = Dy8[dir] + y;
        nx = Dx8[dir] + x;
        if (TileCanBeMovedOn(plane, nx, ny, MeGoalPlane, MeGoalX, MeGoalY, flag) != 0) {
            dis = GetDis(nx, ny, a, b);
            if (dis < threshold) {
                if (GetLife(plane, nx, ny) > 0) {
                    fallback = dir;
                } else if (IsClearTile(plane, nx, ny) == 0) {
                    fallback = dir;
                } else {
                    best = dir;
                }
                threshold = dis;
            }
        }
    }
    }
    return best >= 0 ? best : fallback;
}
