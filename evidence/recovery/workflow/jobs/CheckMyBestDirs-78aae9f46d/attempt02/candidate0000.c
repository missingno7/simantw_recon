/*
 * CheckMyBestDirs: follow the player's best directions from (x, y) on a
 * plane.  The first step's direction moves the point by the far Dx8/Dy8
 * deltas; further steps are taken while a direction exists, up to 64
 * steps, counting every attempt.  The count is returned through the far
 * steps pointer; the result is the failing direction code (negative) or
 * -1 when the walk stopped with a valid direction.
 */
extern char far Dx8[];
extern char far Dy8[];
extern int far GetMyBestDirs(int plane, int x, int y, int a, int b);

int far CheckMyBestDirs(int far *steps, int plane, int x, int y, int a, int b)
{
    int nx;
    int ny;
    int count;
    int dir;

    count = 0;
    dir = GetMyBestDirs(plane, x, y, a, b);
    if (dir >= 0) {
        nx = Dx8[dir] + x;
        ny = Dy8[dir] + y;
    }
    while (dir >= 0 && count < 0x40) {
        dir = GetMyBestDirs(plane, nx, ny, a, b);
        if (dir >= 0) {
            nx += Dx8[dir];
            ny += Dy8[dir];
        }
        count++;
    }
    *steps = count;
    if (dir >= 0)
        dir = -1;
    return dir;
}
