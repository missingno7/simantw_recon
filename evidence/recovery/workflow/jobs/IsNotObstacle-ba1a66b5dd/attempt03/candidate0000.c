/*
 * IsNotObstacle: whether the tile at (plane, x, y) does not block
 * movement. Bounds: 0<=x<=0x7f/0<=y<=0x3f for plane<=1, else
 * 0<=x<=0x3f/0<=y<=0x3f; out of range returns false (0). The tile byte
 * comes from the named near map for the plane (MapA plane<=1, MapB
 * plane==2, MapR otherwise -- same maps/offsets as IsItDigable). For
 * plane<=1 the tile is compared against a threshold selected by a
 * match_position flag (offset 0x9b6e, element 0x4db7) -- the flag's
 * "else" arm re-tests the same flag a second time (an apparent
 * duplicate check in the original, reproduced here since the compiled
 * shape shows both compares), returning false above the threshold else
 * true. For plane>1, a tile <= 0x18 is always clear; otherwise plane==2
 * requires tile in [0x51,0x53] and other planes require tile in
 * [0x30,0x31].
 */
extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far match_position[];

int far IsNotObstacle(int plane, int x, int y)
{
    int tile;
    int inBounds;

    tile = -1;
    if (plane <= 1)
        inBounds = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        inBounds = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);

    if (inBounds) {
        if (plane <= 1)
            tile = MapA[x][y];
        else if (plane == 2)
            tile = MapB[x][y];
        else
            tile = MapR[x][y];
    }

    if (plane <= 1) {
        if (match_position[0x4db7] == 0) {
            if (tile > 0x53)
                return 0;
        } else {
            if (match_position[0x4db7] != 0) {
                if (tile > 0x5f)
                    return 0;
            } else {
                if (tile > 0x50)
                    return 0;
            }
        }
        return 1;
    }
    if (tile <= 0x18)
        return 1;
    if (plane <= 2) {
        if (tile >= 0x51 && tile <= 0x53)
            return 1;
        return 0;
    }
    if (tile >= 0x30 && tile <= 0x31)
        return 1;
    return 0;
}
