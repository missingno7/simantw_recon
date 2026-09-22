/*
 * SetMap: write a terrain cell.  Planes 0 and 1 address the 128x64 near
 * MapA; planes 2 and 3 the 64x64 MapB and MapR.  The coordinates are
 * first checked against the plane's extent (x up to 127 for the two wide
 * planes, otherwise up to 63; y always up to 63); for a valid position
 * the cell byte is stored for a known plane and the edit map is zapped at
 * that point.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern void far ZapEuMapAt(int plane, int x, int y);

void far SetMap(int plane, int x, int y, int value)
{
    int ok;

    if (plane <= 1)
        ok = (x >= 0 && x <= 127 && y >= 0 && y <= 63);
    else
        ok = (x >= 0 && x <= 63 && y >= 0 && y <= 63);
    if (ok == 1) {
        switch (plane) {
        case 0:
        case 1:
            MapA[x][y] = value;
            break;
        case 2:
            MapB[x][y] = value;
            break;
        case 3:
            MapR[x][y] = value;
            break;
        }
        ZapEuMapAt(plane, x, y);
    }
}
