/*
 * Hypothesis: only a carried egg (MeType 8) can be dropped. Search eight
 * adjacent cells in the current/requested direction, rotating through the
 * absolute direction stencil. An empty Life cell that is clear and has map
 * tile 0x38 accepts the egg. Otherwise try placing MeEggCarried in the
 * selected cell's colony list, then reinitialize the controlled ant.
 */
extern int near MeType, MePlane, MeLocX, MeLocY, MeDir;
extern int far MeEggCarried;
extern volatile unsigned char far absSearchDirs[];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far ListIndexA, ListIndexB, ListIndexR;
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far IsClearTile(int plane, int x, int y);
extern void far AddAntToAList(int x, int y, int type, int a, int b);
extern void far AddAntToBList(int x, int y, int type, int a, int b);
extern void far AddAntToRList(int x, int y, int type, int a, int b);
extern void far SetLife(int plane, int x, int y, int type);
extern int far pascal GetAsyncKeyState(int key);

extern void far myBeginSound(unsigned int sound, unsigned int a, unsigned int b);

int far DropMyEgg(int plane, int x, int y, int fromX, int fromY)
{
    int result;
    int direction;
    int n;
    int searchDirection;
    int dropX;
    int dropY;
    int life;
    int map;
    int inside;
    int caste;
    int added;
    int newPlane;
    volatile int newType;
    int playerX;
    int playerY;

    if (MeType != 8) return 0;
    result = 0;

    direction = GetDir(x, y, fromX, fromY);
    if (direction > 0)
        --direction;
    else
        direction = MeDir;

    n = 0;
    while (n < 8) {
                searchDirection = (absSearchDirs[n] + direction) & 7;
        dropX = x + Dx8[searchDirection];
        dropY = y + Dy8[searchDirection];

        if (plane <= 1) inside = (dropX >= 0 && dropX <= 0x7f && dropY >= 0 && dropY <= 0x3f) ? 1 : 0;
        else inside = (dropX >= 0 && dropX <= 0x3f && dropY >= 0 && dropY <= 0x3f) ? 1 : 0;
        if (inside == 0) continue;

        switch (plane) {
        case 0:
        case 1:
            life = LifeA[dropX][dropY];
            break;
        case 2:
            life = LifeB[dropX][dropY];
            break;
        case 3:
            life = LifeR[dropX][dropY];
            break;
        default:
            goto next_direction;
        }

        if (life != 0)
            goto next_direction;
        if (IsClearTile(plane, dropX, dropY) != 0) {
            result = 1;
            goto next_direction;
        }

        switch (plane) {
        case 0:
        case 1:
            map = MapA[dropX][dropY];
            break;
        case 2:
            map = MapB[dropX][dropY];
            break;
        case 3:
            map = MapR[dropX][dropY];
            break;
        default:
            goto next_direction;
        }

        if (map == 0x38) result = 1;
next_direction:
        ++n;
        if (result != 0) break;
    }

    if (result == 0) {
        dropX = x;
        dropY = y;
        if (plane <= 1)
            inside = (dropX >= 0 && dropX <= 0x7f && dropY >= 0 && dropY <= 0x3f) ? 1 : 0;
        else
            inside = (dropX >= 0 && dropX <= 0x3f && dropY >= 0 && dropY <= 0x3f) ? 1 : 0;

        if (inside != 0) {
            if (IsClearTile(plane, dropX, dropY) != 0)
                result = 1;
            else {
                switch (plane) {
                case 0:
                case 1:
                    map = MapA[dropX][dropY];
                    break;
                case 2:
                    map = MapB[dropX][dropY];
                    break;
                case 3:
                    map = MapR[dropX][dropY];
                    break;
                default:
                    map = -1;
                    break;
                }
                if (map == 0x38)
                    result = 1;
            }
        }
    }

    if (result == 0) {
        caste = MeEggCarried;
        added = 0;
        if (plane <= 1) {
            if (ListIndexA < 1000) {
                AddAntToAList(dropX, dropY, caste, 8, 0);
                added = 1;
            }
        } else if (plane == 2) {
            if (ListIndexB < 500) {
                AddAntToBList(dropX, dropY, caste, 8, 0);
                added = 1;
            }
        } else if (plane == 3 && ListIndexR < 500) {
            AddAntToRList(dropX, dropY, caste, 8, 0);
            added = 1;
        }
        if (added != 0) {
            result = 1;
            SetLife(plane, dropX, dropY, caste);
        }
    }

    if (result != 0 && plane <= 1)
        caste = 0xff;
    else if (result != 0)
        caste = 0xff;

    if (result != 0) {
        MeDir = searchDirection;
        GetAsyncKeyState(0x10);
        MeType = 0x10;
        newType = 0x10;
        MeEggCarried = 0xfd;
        newPlane = MePlane;
        playerX = MeLocX;
        playerY = MeLocY;
        direction = MeDir;
        if (newPlane <= 1)
            inside = (playerX >= 0 && playerX <= 0x7f && playerY >= 0 && playerY <= 0x3f) ? 1 : 0;
        else
            inside = (playerX >= 0 && playerX <= 0x3f && playerY >= 0 && playerY <= 0x3f) ? 1 : 0;
        if (inside == 1) {
            SetLife(newPlane, playerX, playerY, 0xff);
            if (newType == 0x60)
                SetLife(newPlane, playerX + Dx8[(direction ^ 4) & 7],
                        playerY + Dy8[(direction ^ 4) & 7], 0xfe);
            MeLocX = playerX;
            MeLocY = playerY;
            MeDir = direction;
            MeType = newType;
            MePlane = newPlane;
        }
        myBeginSound(0x1c, 0, 0x7e);
    }
    return result;
}
