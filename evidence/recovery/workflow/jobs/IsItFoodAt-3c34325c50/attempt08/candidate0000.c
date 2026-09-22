/*
 * IsItFoodAt validates (level,x,y), looks up the tile through the matching
 * map, and reports edibility.  valid is pre-set to a non-1 sentinel so the
 * bounds-check failure path shares the same "if (valid == 1)" dispatch as
 * success instead of a separate early return.  The tile byte is
 * accumulated in an unsigned char and only widened to int once, after the
 * switch, matching the single shared zero-extension in the target.  The
 * switch cases are written in ascending numeric order (0/1, 2, 3) to match
 * the observed MapA/MapB/MapR block placement order.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];

extern int far IsItFood(int tile);

int far IsItFoodAt(int level, int x, int y)
{
    int tile;
    int valid;
    unsigned char b;

    tile = -1;
    valid = -1;
    if (level <= 1) {
        if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f)
            valid = 1;
    } else {
        if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f)
            valid = 1;
    }
    if (valid == 1) {
        switch (level) {
        case 0:
        case 1:
            b = MapA[x][y];
            break;
        case 2:
            b = MapB[x][y];
            break;
        case 3:
            b = MapR[x][y];
            break;
        }
        tile = b;
    }
    if (tile < 0)
        return 0;
    if (level <= 1)
        return IsItFood(tile);
    if (tile >= 0x10 && tile <= 0x13)
        valid = 1;
    else
        valid = 0;
    return valid;
}
