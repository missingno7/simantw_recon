/*
 * IsLiftable: whether whatever is at (plane, x, y) can be lifted.
 * FindEggAt is queried first (far out-parameter gives the ant-list
 * index, the return value is checked at the very end). Bounds
 * (0<=x<=0x7f/0<=y<=0x3f for plane<=1, else 0<=x<=0x3f/0<=y<=0x3f) gate
 * a tile lookup from the named near map for the plane (MapA/MapB/MapR,
 * same as _IsItDigable), defaulting to a -1 sentinel out of range. For
 * plane<=1, IsItFood(tile) (cross-segment call) decides food-likeness;
 * for plane>1, tile in [0x10,0x13] does. Either being true returns
 * liftable. Otherwise a character-range test (tile in [0x51,0x53] for
 * plane<=1, [0x30,0x31] otherwise) can also return liftable. Finally,
 * (eggResult & 0x7f) in [1,7] returns liftable; otherwise not liftable.
 */
extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far FindEggAt(int far *outIndex, int plane, int x, int y);
extern int far IsItFood(int tile);

int far IsLiftable(int plane, int x, int y)
{
    int eggIndex;
    int eggResult;
    int inBounds;
    int tile;
    int foodLike;

    eggResult = FindEggAt(&eggIndex, plane, x, y);
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

    if (plane <= 1)
        foodLike = IsItFood(tile);
    else
        foodLike = (tile >= 0x10 && tile <= 0x13);
    if (foodLike)
        return 1;

    if (plane <= 1) {
        if (tile >= 0x51 && tile <= 0x53)
            return 1;
    } else {
        if (tile >= 0x30 && tile <= 0x31)
            return 1;
    }

    if ((eggResult & 0x7f) >= 1 && (eggResult & 0x7f) <= 7)
        return 1;
    return 0;
}
