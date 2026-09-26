/*
 * IsItDigable: whether the tile at (plane, x, y) can be dug. Requires
 * plane >= 2 (nest planes only) and (x, y) within the shared 64x64 map
 * bound (0<=x<=0x3f, 0<=y<=0x3f); out of either range returns false.
 * A second bounds test selects which per-plane range gates the map
 * lookup (0<=x<=0x3f for plane>1, 0<=x<=0x7f for plane<=1 -- the
 * plane<=1/MapA case is unreachable given the first plane>=2 gate, but
 * the compiled target still carries it, so it is kept here); when in
 * range, the tile byte comes from the named near map for the plane
 * (MapA plane 1, MapB plane 2, MapR plane 3, matching the exact MAPSYM
 * bindings and FixExitMapB/R's MapB/MapR declarations), else the tile
 * stays the -1 sentinel. The tile is digable when IsItDirt (same-segment
 * far call, src/recovered/wf_IsItDirt-30ab0b6cc4.c) accepts it, or when
 * its value falls in [0x1c, 0x1f].
 */
extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far IsItDirt(int value);

int far IsItDigable(int plane, int x, int y)
{
    int tile;
    int inBounds;
    int firstBounds;

    int yCopy;
    yCopy = y;
    if (plane < 2)
        return 0;
    if (x < 0)
        firstBounds = 0;
    else if (x > 0x3f)
        firstBounds = 0;
    else if (yCopy < 0)
        firstBounds = 0;
    else if (yCopy > 0x3f)
        firstBounds = 0;
    else
        firstBounds = 1;
    if (!firstBounds)
        return 0;
    tile = -1;
    if (plane > 1)
        inBounds = (x >= 0 && x <= 0x3f && yCopy >= 0 && yCopy <= 0x3f);
    else
        inBounds = (x >= 0 && x <= 0x7f && yCopy >= 0 && yCopy <= 0x3f);
    if (inBounds) {
        switch (plane) {
        case 1:
            tile = MapA[x][yCopy];
            break;
        case 2:
            tile = MapB[x][yCopy];
            break;
        case 3:
            tile = MapR[x][yCopy];
            break;
        }
    }
    if (IsItDirt(tile))
        return 1;
    return (tile >= 0x1c && tile <= 0x1f);
}
