extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];
extern int far IsItFood(int tile);

/* Select a colony map only after the level-specific coordinate checks.
   Levels 0/1 use MapA's 128-row span; levels 2/3 use the 64-row spans.
   A map byte is meaningful only after a valid map coordinate is selected. */
int far IsItFoodAt(int level, int x, int y)
{
    int tile;
    int valid;
    int result;

    tile = -1;
    if (level <= 1)
        valid = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
    else
        valid = x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f;

    if (valid == 1) {
        if (level <= 1)
            tile = MapA[x][y];
        else if (level == 2)
            tile = MapB[x][y];
        else if (level == 3)
            tile = MapR[x][y];
    }

    if (tile < 0)
        return 0;
    if (level <= 1)
        return IsItFood(tile);
    if (tile >= 0x10 && tile <= 0x13)
        result = 1;
    else
        result = 0;
    return result;
}
