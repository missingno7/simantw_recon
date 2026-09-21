/*
 * IsLiftable: whether whatever is at (plane, x, y) can be lifted.
 * FindEggAt (same-segment far call, far out-parameter for the egg index)
 * is queried first; its return value is examined at the very end.
 * A materialised bounds flag (0<=x<=0x7f, 0<=y<=0x3f on the surface
 * planes <=1; 0<=x<=0x3f, 0<=y<=0x3f underground) gates a switch on the
 * plane that reads the tile byte from the named near map (MapA for
 * planes 0/1, MapB for plane 2, MapR for plane 3); the tile keeps the
 * -1 sentinel out of range or for an unknown plane.  On the surface
 * IsItFood (cross-segment far call) decides food-likeness; underground
 * tiles 0x10..0x13 are food.  Food is liftable.  Otherwise a pebble test
 * (plane 1: tile 0x51..0x53; underground: 0x30..0x31, the same ranges
 * as the admitted IsThisPebble) makes it liftable, and finally a
 * carried-egg class ((eggResult & 0x7f) in 1..7) is liftable too.
 * Written in the unit's /Og form: the flags are plain locals whose
 * values the optimiser keeps in registers (DX/DI) and the tile lives in
 * SI once x/y are dead.
 */
extern unsigned char near MapA[64][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far FindEggAt(int far *outIndex, int plane, int x, int y);
extern int far IsItFood(int tile);

#define TRUE 1
#define FALSE 0

int far IsLiftable(int plane, int x, int y)
{
    int eggIndex;
    int eggResult;
    int tile;
    int ok;

    eggResult = FindEggAt(&eggIndex, plane, x, y);
    tile = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        switch (plane) {
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

    if (plane <= 1)
        ok = IsItFood(tile);
    else
        ok = (tile >= 0x10 && tile <= 0x13);
    if (ok)
        return TRUE;

    if (plane <= 1)
        ok = (plane == 1 && tile >= 0x51 && tile <= 0x53);
    else
        ok = (tile >= 0x30 && tile <= 0x31);
    if (ok)
        return TRUE;

    ok = ((eggResult & 0x7f) >= 1 && (eggResult & 0x7f) <= 7);
    if (ok)
        return TRUE;
    return FALSE;
}
