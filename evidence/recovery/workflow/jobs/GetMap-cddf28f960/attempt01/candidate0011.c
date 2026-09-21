/*
 * GetMap: read a terrain cell.  Planes 0 and 1 address the 128x64 near
 * MapA; planes 2 and 3 the 64x64 MapB and MapR.  The coordinates are
 * first checked against the plane's extent (x up to 127 for the two wide
 * planes, otherwise up to 63; y always up to 63) and -1 is returned for an
 * invalid position or an unknown plane; otherwise the unsigned cell byte.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

#define CASEBODY(v) result = v; break;
int far GetMap(int plane, int x, int y)
{
    int result;
    int ok;

    result = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 127 && y >= 0 && y <= 63);
    else
        ok = (x >= 0 && x <= 63 && y >= 0 && y <= 63) ? 1 : 0;
    if (ok != 0) {
        switch (plane) {
        case 0:
        case 1:
            CASEBODY(MapA[x][y])
        case 2:
            CASEBODY(MapB[x][y])
        case 3:
            CASEBODY(MapR[x][y])
        }
    }
    return result;
}
