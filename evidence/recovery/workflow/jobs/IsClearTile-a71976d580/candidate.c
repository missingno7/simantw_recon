/*
 * IsClearTile: whether the map cell (plane, x, y) is walkable terrain and
 * free of a live ant.  Uses the unit's shared bounds-check idiom (surface
 * planes 0/1: 0<=x<=0x7f, 0<=y<=0x3f; underground planes 2/3: 0<=x<=0x3f,
 * 0<=y<=0x3f -- src/recovered/wf_IsLiftable-91a4e99057.c), the GetMap
 * switch (MapA/MapB/MapR) and a parallel occupancy grid (LifeA/LifeB/
 * LifeR) indexed identically to the terrain arrays.
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
    int ok;
    int tile;
    int life;
    int result;

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
