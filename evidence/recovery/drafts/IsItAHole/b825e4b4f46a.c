/*
 * IsItAHole: is the map cell (level, x, y) a nest hole tile (0x18)?  On
 * the yard levels (0 and 1) the answer comes from IsItHole(x, y).  On the
 * nest levels a positive y is never a hole; otherwise the location is
 * validated inline exactly as IsValidLocation does (128x64 for levels
 * up to 1, 64x64 above), the tile is read from MapA, MapB or MapR by
 * level (-1 when invalid or on an unknown level), and 1 is returned when
 * it equals 0x18.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];

extern int far IsItHole(int x, int y);

int far IsItAHole(int level, int x, int y)
{
    int tile;
    int valid;

    if (level <= 1)
        return IsItHole(x, y);
    if (y > 0)
        return 0;
    tile = -1;
    if (level <= 1)
        valid = x >= 0 && x <= 127 && y >= 0 && y <= 63;
    else
        valid = x >= 0 && x <= 63 && y >= 0 && y <= 63;
    if (valid == 1) {
        switch (level) {
        case 0:
        case 1:
            tile = MapA[x][y];
            break;
        case 2:
            tile = MapB[x][y];
            break;
        case 3:
            tile = MapR[x][y];
            break;
        }
    }
    if (tile == 0x18)
        return 1;
    return 0;
}
