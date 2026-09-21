/*
 * GetRedBestDirs: pick the best of the 8 Dx8/Dy8 step directions from
 * (x, y) toward (a, b) on the given plane. best starts at -1 (returned
 * unchanged if the starting distance to (a,b) is already <=0); a -2
 * fallback direction is tracked separately. Each direction whose target
 * tile (a,b) is movable (TileCanBeMovedOn(plane,a,b,0)==1, checked as
 * written, independent of the step) and whose stepped distance improves
 * on the current threshold updates the threshold; if the stepped tile
 * has life or is not clear it only updates the fallback, otherwise it
 * updates best. Returns best if set, else the fallback.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far TileCanBeMovedOn(int plane, int nx, int ny, int plane2, int a, int b, int flag);
extern int far GetLife(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);

int far GetRedBestDirs(int plane, int x, int y, int a, int b)
{
    int p;
    int best;
    int fallback;
    int threshold;
    int dir;
    int nx;
    int ny;
    int dis;

    p = plane;
    best = -1;
    threshold = GetDis(x, y, a, b);
    if (threshold <= 0)
        return best;

    fallback = -2;
    for (dir = 0; dir < 8; dir++) {
        ny = Dy8[dir] + y;
        nx = Dx8[dir] + x;
        if (TileCanBeMovedOn(p, nx, ny, p, a, b, 0) == 1) {
            dis = GetDis(nx, ny, a, b);
            if (dis < threshold) {
                if (GetLife(p, nx, ny) > 0) {
                    fallback = dir;
                } else if (IsClearTile(p, nx, ny) != 1) {
                    fallback = dir;
                } else {
                    best = dir;
                }
                threshold = dis;
            }
        }
    }
    return best >= 0 ? best : fallback;
}
