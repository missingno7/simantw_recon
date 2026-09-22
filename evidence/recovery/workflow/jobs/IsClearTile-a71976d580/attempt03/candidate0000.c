/*
 * IsClearTile: whether the map cell (plane, x, y) is walkable terrain and
 * free of a live ant.  Uses the unit's shared bounds-check idiom (surface
 * planes 0/1: 0<=x<=0x7f, 0<=y<=0x3f; underground planes 2/3: 0<=x<=0x3f,
 * 0<=y<=0x3f -- src/recovered/wf_IsLiftable-91a4e99057.c), the GetMap
 * switch (MapA/MapB/MapR) and a parallel occupancy grid (LifeA/LifeB/
 * LifeR) indexed identically to the terrain arrays.  An out-of-range or
 * unknown-plane terrain lookup returns FALSE immediately, before the
 * occupancy grid is even read.  A life-grid byte of 0 is folded back to
 * the -1 "nothing here" sentinel so the following occupancy test treats
 * it the same as out of range: walkable only when clear of anything but
 * the sentinel (-1), a stale corpse marker (0xff) or a trailing queen
 * segment (0xfe), and the terrain tile itself is below the plane's
 * walkable threshold (0x10 on the surface, 8 underground).
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];

#define TRUE 1
#define FALSE 0

int far IsClearTile(int plane, int x, int y)
{
    int result;
    int ok;
    int tile;
    int life;

    result = FALSE;
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
    if (tile == -1)
        return FALSE;

    life = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        switch (plane) {
        case 0:
        case 1:
            life = LifeA[x][y];
            break;
        case 2:
            life = LifeB[x][y];
            break;
        case 3:
            life = LifeR[x][y];
            break;
        }
        if (life == 0)
            life = -1;
    }

    if (life != -1 && life != 0xff && life != 0xfe)
        return FALSE;

    if (plane <= 1)
        ok = (tile < 0x10);
    else
        ok = (tile < 8);
    if (ok == TRUE)
        result = TRUE;

    return result;
}
