extern unsigned char near MapA[128][64];
extern unsigned char near MapB[128][64];
extern unsigned char near MapR[128][64];

extern int far IsItFood(int tile);

int far IsItFoodAt(int level, int x, int y)
{
    int tile;
    int valid;

    tile = -1;
    if (level <= 1)
        valid = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
    else
        valid = x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f;
    if (valid == 1) {
        switch (level) {
        case 3:
            tile = MapR[x][y];
            break;
        case 2:
            tile = MapB[x][y];
            break;
        case 0:
        case 1:
            tile = MapA[x][y];
            break;
        }
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
