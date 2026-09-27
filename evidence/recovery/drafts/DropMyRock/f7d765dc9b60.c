/* Drop a carried rock around the requested cell, then try the cell itself. */
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
extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far myBeginSound(int, int, int);

int far DropMyRock(int plane, int x, int y, int fromX, int fromY)
{
    int tile;
    int life;
    int step;
    int startDir;
    int found;
    int ny;
    int nx;
    int direction;

    if (MeType != 0x28 && MeType != 0x48)
        return 0;

    found = 0;
    startDir = GetDir(x, y, fromX, fromY);
    if (startDir > 0)
        startDir--;
    else
        startDir = MeDir;

    /* Search the eight neighboring positions in the preferred order. */
    for (step = 0; step < 8; step++) {
        direction = (absSearchDirs[step] + startDir) & 7;
        nx = x + Dx8[direction];
        ny = y + Dy8[direction];

        if (plane <= 1) {
            if (nx < 0 || nx > 0x7f || ny < 0 || ny > 0x3f)
                continue;
        } else {
            if (nx < 0 || nx > 0x3f || ny < 0 || ny > 0x3f)
                continue;
        }

        life = -1;
        switch (plane) {
        case 0:
        case 1:
            life = LifeA[nx][ny];
            break;
        case 2:
            life = LifeB[nx][ny];
            break;
        case 3:
            life = LifeR[nx][ny];
            break;
        }
        if (life != 0)
            continue;

        if (IsClearTile(plane, nx, ny)) {
            found = 1;
            break;
        }

        /* Filter the neighbor by its plane-specific map contents. */
        if (plane <= 1) {
            if (plane == 0 || plane == 1)
                tile = MapA[nx][ny];
            else
                tile = -1;
            if (IsItFood(tile))
                continue;
        } else {
            if (plane == 2)
                tile = MapB[nx][ny];
            else if (plane == 3)
                tile = MapR[nx][ny];
            else
                tile = -1;
            if (tile >= 0x10 && tile <= 0x13)
                continue;
        }

        if (plane <= 1) {
            if (tile >= 0x51 && tile <= 0x53)
                continue;
        } else {
            if (tile >= 0x30 && tile <= 0x31)
                continue;
        }

        if (plane <= 1) {
            if (IsItHole(nx, ny)) {
                found = 1;
            } else if (tile == 0x38) {
                found = 1;
            }
        } else {
            if (ny <= 0) {
                if (plane == 2) {
                    if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f &&
                        MapB[nx][ny] == 0x18)
                        found = 1;
                } else if (plane == 3) {
                    if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f &&
                        MapR[nx][ny] == 0x18)
                        found = 1;
                }
            }
            if (!found && tile == 0x38)
                found = 1;
        }

        if (found)
            break;
    }

    /* If no neighboring cell worked, make the same checks at the origin. */
    if (!found) {
        direction = startDir;
        nx = x;
        ny = y;

        if (plane <= 1) {
            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f) {
                if (IsClearTile(plane, nx, ny)) {
                    found = 1;
                } else {
                    tile = MapA[nx][ny];
                    if (!IsItFood(tile)) {
                        if (!(tile >= 0x51 && tile <= 0x53)) {
                            if (IsItHole(nx, ny)) {
                                found = 1;
                            } else if (tile == 0x38) {
                                found = 1;
                            }
                        }
                    }
                }
            }
        } else {
            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f) {
                if (IsClearTile(plane, nx, ny)) {
                    found = 1;
                } else {
                    if (plane == 2)
                        tile = MapB[nx][ny];
                    else if (plane == 3)
                        tile = MapR[nx][ny];
                    else
                        tile = -1;
                    if (!(tile >= 0x10 && tile <= 0x13)) {
                        if (!(tile >= 0x30 && tile <= 0x31)) {
                            if (ny <= 1) {
                                if (plane == 2) {
                                    if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f &&
                                        MapB[nx][ny] == 0x18)
                                        found = 1;
                                } else if (plane == 3) {
                                    if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f &&
                                        MapR[nx][ny] == 0x18)
                                        found = 1;
                                }
                            }
                            if (!found && tile == 0x38)
                                found = 1;
                        }
                    }
                }
            }
        }
    }

    if (found) {
        MeDir = direction;
        DropPebble(plane, nx, ny);
        GetAsyncKeyState(0x10);
        if (MeType == 0x28)
            MeType -= 0x18;
        else if (MeType == 0x48)
            MeType -= 0x18;
        myBeginSound(0x1e, 0, 0x7e);
    }
    return found;
}