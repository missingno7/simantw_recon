/*
 * IsItDigable uses one materialized bounds result before the tile sentinel,
 * then applies the nest-plane lookup and the dirt/range tests.
 */
extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far IsItDirt(int value);

int far IsItDigable(int plane, int x, int y)
{
    int tile;
    int valid;
    int result;

    result = 0;
    if (plane >= 2) {
        if (x < 0)
            valid = 0;
        else if (x > 0x3f)
            valid = 0;
        else if (y < 0)
            valid = 0;
        else if (y > 0x3f)
            valid = 0;
        else
            valid = 1;

        if (valid) {
            tile = -1;
            if (plane > 1) {
                if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f) {
                    switch (plane) {
                    case 1: tile = MapA[x][y]; break;
                    case 2: tile = MapB[x][y]; break;
                    case 3: tile = MapR[x][y]; break;
                    }
                }
            } else if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f) {
                switch (plane) {
                case 1: tile = MapA[x][y]; break;
                case 2: tile = MapB[x][y]; break;
                case 3: tile = MapR[x][y]; break;
                }
            }
            if (IsItDirt(tile))
                result = 1;
            else if (tile >= 0x1c && tile <= 0x1f)
                result = 1;
        }
    }
    return result;
}
