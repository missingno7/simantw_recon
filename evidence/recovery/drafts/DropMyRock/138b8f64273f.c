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
    volatile int life;
    register int check;
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
    step = 0;
    while (step < 8) {
        direction = (absSearchDirs[step] + startDir) & 7;
        nx = x + Dx8[direction];
        ny = y + Dy8[direction];

        if (plane <= 1) {
            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                check = 1;
            else
                check = 0;
        } else {
            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                check = 1;
            else
                check = 0;
        }
        if (check == 0)
            goto NextDirection;

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
            goto NextDirection;

        if (IsClearTile(plane, nx, ny)) {
            found = 1;
            goto NextDirection;
        }

        /* The map phase validates the chosen position independently. */
        life = 0;
        if (plane <= 1) {
            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                life = 1;
        } else {
            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                life = 1;
        }
        if (life == 0)
            goto NextDirection;

        /* Filter the neighbor by its plane-specific map contents. */
        tile = -1;
        switch (plane) {
        case 0:
        case 1:
            tile = MapA[nx][ny];
            break;
        case 2:
            tile = MapB[nx][ny];
            break;
        case 3:
            tile = MapR[nx][ny];
            break;
        }
        if (plane <= 1) {
            if (IsItFood(tile))
                goto NextDirection;
        } else {
            if (tile >= 0x10 && tile <= 0x13)
                goto NextDirection;
        }

        if (plane <= 1) {
            if (tile >= 0x51 && tile <= 0x53)
                goto NextDirection;
        } else {
            if (tile >= 0x30 && tile <= 0x31)
                goto NextDirection;
        }

        if (plane <= 1) {
            if (IsItHole(nx, ny)) {
                found = 1;
            } else if (tile == 0x38) {
                found = 1;
            }
        } else {
            if (ny <= 0) {
                check = -1;
                if (plane <= 1) {
                    if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                        check = 1;
                } else {
                    if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                        check = 1;
                }
                if (check != 0) {
                    switch (plane) {
                    case 0:
                    case 1:
                        check = MapA[nx][ny];
                        break;
                    case 2:
                        check = MapB[nx][ny];
                        break;
                    case 3:
                        check = MapR[nx][ny];
                        break;
                    }
                    if (check == 0x18)
                        found = 1;
                }
            }
            if (!found && tile == 0x38)
                found = 1;
        }

NextDirection:
        step++;
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
                    life = 0;
                    if (plane <= 1) {
                        if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                            life = 1;
                    } else {
                        if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                            life = 1;
                    }
                    if (life != 0) {
                        tile = -1;
                        switch (plane) {
                        case 0:
                        case 1:
                            tile = MapA[nx][ny];
                            break;
                        case 2:
                            tile = MapB[nx][ny];
                            break;
                        case 3:
                            tile = MapR[nx][ny];
                            break;
                        }
                        if (plane <= 1) {
                            if (!IsItFood(tile)) {
                                if (!(tile >= 0x51 && tile <= 0x53)) {
                                    if (IsItHole(nx, ny)) {
                                        found = 1;
                                    } else if (tile == 0x38) {
                                        found = 1;
                                    }
                                }
                            }
                        } else {
                            if (!(tile >= 0x10 && tile <= 0x13)) {
                                if (!(tile >= 0x30 && tile <= 0x31)) {
                                    if (ny <= 1) {
                                        check = -1;
                                        if (plane <= 1) {
                                            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                                                check = 1;
                                        } else {
                                            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                                                check = 1;
                                        }
                                        if (check != 0) {
                                            switch (plane) {
                                            case 0:
                                            case 1:
                                                check = MapA[nx][ny];
                                                break;
                                            case 2:
                                                check = MapB[nx][ny];
                                                break;
                                            case 3:
                                                check = MapR[nx][ny];
                                                break;
                                            }
                                            if (check == 0x18)
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
