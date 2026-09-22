/*
 * GetBestDir: pick the best of the 8 Dx8/Dy8 step directions from
 * (x, y) toward (a, b) on the given plane, mirroring the shape of the
 * already-solved GetRedBestDirs/GetMyBestDirs siblings. best/fallback
 * start at -1/-2 (best returned unchanged if the starting distance to
 * (a,b) is already <=0). Each direction whose step tile is not an
 * obstacle (IsNotObstacle(plane,nx,ny)==1) and is not a pebble
 * (IsThisPebble(plane, GetMap(plane,nx,ny))==0) and whose stepped
 * distance improves on the current threshold updates the threshold; if
 * the stepped tile has life or is not clear it only updates the
 * fallback, otherwise it updates best. Returns best if set, else the
 * fallback.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetMap(int plane, int x, int y);
extern int far IsNotObstacle(int plane, int x, int y);
extern int far IsThisPebble(int plane, int tile);
extern int far GetLife(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);

int far GetBestDir(int plane, int x, int y, int a, int b)
{
    int best;
    int fallback;
    int threshold;
    int dir;
    int nx;
    int ny;
    int tile;
    int dis;

    best = -1;
    threshold = GetDis(x, y, a, b);
    if (threshold <= 0)
        return best;

    fallback = -2;
    for (dir = 0; dir < 8; dir++) {
        ny = Dy8[dir] + y;
        nx = Dx8[dir] + x;
        tile = GetMap(plane, nx, ny);
        if (IsNotObstacle(plane, nx, ny) != 1)
            continue;
        if (IsThisPebble(plane, tile) != 0)
            continue;
        dis = GetDis(nx, ny, a, b);
        if (dis >= threshold)
            continue;
        if (GetLife(plane, nx, ny) > 0) {
            fallback = dir;
        } else if (IsClearTile(plane, nx, ny) != 1) {
            fallback = dir;
        } else {
            best = dir;
        }
        threshold = dis;
    }
    return best >= 0 ? best : fallback;
}
