extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far match_position[];
int far IsNotObstacle(int plane, int x, int y)
{
    int tile = -1;
    int valid;
    int result;
    int map_x;
    if (plane <= 1)
        valid = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
    else
        valid = x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f;
    if (valid == 1) {
        map_x = x;
        switch (plane) {
        case 0: case 1: tile = MapA[map_x][y]; break;
        case 2: tile = MapB[map_x][y]; break;
        case 3: tile = MapR[map_x][y]; break;
        }
    }
    if (tile < 0) return 0;
    if (plane <= 1) {
        if (match_position[0x4db7] == 0) result = tile <= 0x53;
        else if (match_position[0x4db7] != 0) result = tile <= 0x5f;
        else result = tile <= 0x50;
    } else if (tile <= 0x18) result = 1;
    else if (plane <= 2) result = tile >= 0x51 && tile <= 0x53;
    else result = tile >= 0x30 && tile <= 0x31;
    return result;
}
