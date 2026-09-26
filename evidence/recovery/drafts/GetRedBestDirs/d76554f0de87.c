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
extern int far GetLife(int x, int y, int plane);
extern int far IsClearTile(int x, int y, int plane);

int far GetRedBestDirs(int plane, int x, int y, int a, int b)
{
    int best;
    int fallback;
    int threshold;
    int dir;
    int nx;
    int ny;
    int dis;

    best = -1;
    threshold = GetDis(x, y, a, b);
    if (threshold <= 0)
        goto done;

    fallback = -2;
    for (dir = 0; dir < 8; dir++) {
        ny = Dy8[dir] + y;
        nx = Dx8[dir] + x;
        if (TileCanBeMovedOn(plane, nx, ny, plane, a, b, 0) == 1) {
            dis = GetDis(nx, ny, a, b);
            if (dis < threshold) {
                if (GetLife(nx, ny, plane) > 0 || IsClearTile(nx, ny, plane) != 1)
                    fallback = dir;
                else
                    best = dir;
                threshold = dis;
            }
        }
    }
    if (best >= 0)
        return best;
    return fallback;
done:
    return best;
}
