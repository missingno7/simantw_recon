extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far match_position[];
int far IsNotObstacle(int plane, int x, int y)
{
    int tile = -1;
    int valid;
    int result;
    if (plane <= 1)
        valid = x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f;
    else
        valid = x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f;
    if (valid == 1) {
        switch (plane) {
        case 0: case 1: tile = MapA[x][y]; break;
        case 2: tile = MapB[x][y]; break;
        case 3: tile = MapR[x][y]; break;
        }
    }
    if (plane <= 1) {
        if (match_position[0x4db7] == 0) result = (unsigned char)tile <= 0x53;
        else if (match_position[0x4db7] != 0) result = (unsigned char)tile <= 0x5f;
        else result = (unsigned char)tile <= 0x50;
    } else if ((unsigned char)tile <= 0x18) result = 1;
    else if (plane <= 2) result = (unsigned char)tile >= 0x51 && (unsigned char)tile <= 0x53;
    else result = (unsigned char)tile >= 0x30 && (unsigned char)tile <= 0x31;
    return result;
}
