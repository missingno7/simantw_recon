extern int near MeType;
extern int near MeDir;
extern char __based(__segname("SIMANT_DATA_GROUP")) absSearchDirs[];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far GetDir(int, int, int, int);
extern int far IsClearTile(int, int, int);
extern int far IsItFood(int);
extern int far IsItHole(int, int);
extern int far DropPebble(int, int, int);
extern void far myBeginSound(int, int, int);

int far DropMyRock(int plane, int x, int y, int fromX, int fromY)
{
    int startDir;
    int step;
    int direction;
    int nx;
    int ny;
    int life;
    int tile;
    int found;

    if (MeType != 0x28 && MeType != 0x48)
        return 0;

    startDir = GetDir(fromX, fromY, x, y);
    if (startDir > 0)
        startDir--;
    else
        startDir = MeDir;

    found = 0;
    for (step = 0; step < 8; step++) {
        direction = (absSearchDirs[step] + startDir) & 7;
        nx = x + Dx8[direction];
        ny = y + Dy8[direction];

        if (plane <= 1) {
            if (nx < 0 || nx > 127 || ny < 0 || ny > 63)
                continue;
        } else {
            if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
                continue;
        }

        if (plane <= 1)
            life = LifeA[nx][ny];
        else if (plane == 2)
            life = LifeB[nx][ny];
        else
            life = LifeR[nx][ny];
        if (life != 0)
            continue;

        if (IsClearTile(plane, nx, ny)) {
            found = 1;
        } else {
            if (plane <= 1)
                tile = MapA[nx][ny];
            else if (plane == 2)
                tile = MapB[nx][ny];
            else
                tile = MapR[nx][ny];

            if (plane <= 1) {
                if ((tile >= 0x51 && tile <= 0x53) ||
                    (tile >= 0x30 && tile <= 0x31))
                    found = 1;
            } else if ((tile >= 0x30 && tile <= 0x31) || tile == 0x18) {
                found = 1;
            }
            if (IsItFood(tile) || IsItHole(nx, ny) || tile == 0x38)
                found = 1;
        }
        if (found)
            break;
    }

    if (!found)
        return 0;
    MeDir = direction;
    DropPebble(plane, nx, ny);
    if (MeType == 0x48) {
        MeType = 0x30;
        myBeginSound(0x1e, 0, 0x7e);
    }
    return 1;
}
