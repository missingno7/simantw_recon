/* Scan the eight neighbors from the chosen direction, find a food-bearing
 * clear tile, and drop carried food onto the surface or underground map. */
extern int near MeType;
extern int near MeDir;
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far IsItFood(int type);
extern int near IsClearTile(int plane, int x, int y);
extern void near DropFoodA(int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);
extern int far GetAsyncKeyState(int key);
extern void far myBeginSound(int sound, int a, int b);
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far FoodB;
extern int far FoodR;
extern char far absSearchDirs[];
extern char far Dx8[];
extern char far Dy8[];

int far DropMyFood(int plane, int x, int y, int targetX, int targetY)
{
    int result;
    int start;
    int n;
    int dir;
    int nx;
    int ny;
    int type;
    int found;

    result = 0;
    if (MeType != 0x18 && MeType != 0x38)
        return result;

    start = GetDir(x, y, targetX, targetY);
    if (start <= 0)
        start = MeDir;
    else
        --start;

    found = 0;
    for (n = 0; n < 8 && !found; ++n) {
        dir = (absSearchDirs[n] + start) & 7;
        nx = x + Dx8[dir];
        ny = y + Dy8[dir];
        if (nx < 0 || ny < 0 || ny > 63)
            continue;
        if ((plane <= 1 && nx > 127) || (plane > 1 && nx > 63))
            continue;

        if (plane > 1) {
            type = LifeR[nx][ny];
        } else if (plane == 0) {
            type = LifeA[nx][ny];
        } else {
            type = LifeB[nx][ny];
        }
        if (plane > 1) {
            if (!IsItFood(type))
                continue;
        } else if (type < 0x10 || type > 0x13) {
            continue;
        }
        if ((type & 3) != 3)
            ++type;
        if (IsClearTile(plane, nx, ny)) {
            if (type == 0x38) {
                type = 0x10;
                found = 1;
            }
        } else {
            continue;
        }
        if (!found && type != 0x38)
            found = 1;
        if (found) {
            MeDir = dir;
            if (plane <= 1) {
                DropFoodA(nx, ny);
            } else {
                if (plane == 2)
                    MapB[nx][ny] = type;
                else
                    MapR[nx][ny] = type;
                ZapEuMapAt(plane, nx, ny);
                if (plane == 2)
                    ++FoodB;
                else
                    ++FoodR;
            }
            if (GetAsyncKeyState(0x10)) {
                MeType &= 0xf7;
                myBeginSound(0x1d, 0, 0x7e);
            }
            result = 1;
        }
    }
    return result;
}
