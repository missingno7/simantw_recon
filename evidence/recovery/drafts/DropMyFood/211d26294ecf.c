/* Find a neighboring food cell, then fall back to the requested cell. */
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
extern int far IsItFood(int);
extern int far IsClearTile(int, int, int);
extern void far DropFoodA(int, int);
extern void far ZapEuMapAt(int, int, int);
extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far myBeginSound(int, int, int);
extern int far FoodB;
extern int far FoodR;

int far DropMyFood(int plane, int x, int y, int fromX, int fromY)
{
    int tile;
    int life;
    int food;
    int step;
    int startDir;
    int found;
    int nx;
    int ny;
    int direction;

    if (MeType != 0x18 && MeType != 0x38)
        return 0;

    found = 0;
    startDir = GetDir(x, y, fromX, fromY);
    if (startDir > 0)
        startDir--;
    else
        startDir = MeDir;

    /* Visit the eight adjacent cells in the direction table's order. */
    step = 0;
    while (step < 8) {
        direction = (absSearchDirs[step] + startDir) & 7;
        nx = x + Dx8[direction];
        ny = y + Dy8[direction];

        /* First plane-specific coordinate gate. */
        if (plane <= 1) {
            if (nx < 0 || nx > 0x7f || ny < 0 || ny > 0x3f)
                goto NextFoodCell;
        } else {
            if (nx < 0 || nx > 0x3f || ny < 0 || ny > 0x3f)
                goto NextFoodCell;
        }

        /* Recheck before reading the life grid. */
        life = 0;
        if (plane <= 1) {
            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                life = 1;
        } else {
            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                life = 1;
        }
        if (life == 0)
            goto NextFoodCell;

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
            goto NextFoodCell;

        /* Validate again after the clear-tile query before map lookup. */
        if (IsClearTile(plane, nx, ny)) {
            tile = 0x10;
            found = 1;
            goto NextFoodCell;
        }
        food = 0;
        if (plane <= 1) {
            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                food = 1;
        } else {
            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                food = 1;
        }
        if (food == 0)
            goto NextFoodCell;

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

        if (plane <= 1)
            food = IsItFood(tile);
        else if (tile >= 0x10 && tile <= 0x13)
            food = 1;
        else
            food = 0;

        if (food != 0 && (tile & 3) < 3) {
            tile++;
            found = 1;
        } else if (IsClearTile(plane, nx, ny) || tile == 0x38) {
            tile = 0x10;
            found = 1;
        }

NextFoodCell:
        step++;
        if (found)
            break;
    }

    /* With no adjacent destination, apply the same food rules at x,y. */
    if (!found) {
        direction = startDir;
        nx = x;
        ny = y;

        if (plane <= 1) {
            if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f) {
                food = 1;
            } else {
                food = 0;
            }
        } else {
            if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f) {
                food = 1;
            } else {
                food = 0;
            }
        }

        if (food != 0) {
            food = 0;
            if (plane <= 1) {
                if (nx >= 0 && nx <= 0x7f && ny >= 0 && ny <= 0x3f)
                    food = 1;
            } else {
                if (nx >= 0 && nx <= 0x3f && ny >= 0 && ny <= 0x3f)
                    food = 1;
            }

            if (food != 0) {
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

                if (plane <= 1)
                    food = IsItFood(tile);
                else if (tile >= 0x10 && tile <= 0x13)
                    food = 1;
                else
                    food = 0;

                if (food != 0 && (tile & 3) < 3) {
                    tile++;
                    found = 1;
                } else if (IsClearTile(plane, nx, ny) || tile == 0x38) {
                    tile = 0x10;
                    found = 1;
                }
            }
        }
    }

    if (found) {
        MeDir = direction;
        if (plane <= 1) {
            DropFoodA(nx, ny);
        } else {
            if (plane == 2)
                MapB[nx][ny] = tile;
            else
                MapR[nx][ny] = tile;
            ZapEuMapAt(plane, nx, ny);
            if (plane == 2)
                FoodB++;
            else
                FoodR++;
        }
        GetAsyncKeyState(0x10);
        MeType &= 0xf7;
        myBeginSound(0x1d, 0, 0x7e);
    }
    return found;
}