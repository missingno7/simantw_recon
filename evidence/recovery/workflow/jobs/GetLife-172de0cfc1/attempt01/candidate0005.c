/*
 * GetLife: read a life cell.  Planes 0 and 1 address the 128x64 near
 * LifeA; planes 2 and 3 the 64x64 LifeB and LifeR.  The coordinates are
 * first checked against the plane's extent (x up to 127 for the two wide
 * planes, otherwise up to 63; y always up to 63) and -1 is returned for an
 * invalid position or an unknown plane; an empty cell (0) also reads as
 * -1, otherwise the unsigned cell byte.
 */
extern unsigned char near LifeA[128][64];
extern unsigned char near LifeB[64][64];
extern unsigned char near LifeR[64][64];

#define CASEBODY(v) result = v; break;

int far GetLife(int plane, int x, int y)
{
    int result;
    int ok;

    result = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 127 && y >= 0 && y <= 63);
    else
        ok = (x >= 0 && x <= 63 && y >= 0 && y <= 63);
    if (ok == 1) {
        switch (plane) {
        case 0:
        case 1:
            CASEBODY(LifeA[x][y])
        case 2:
            CASEBODY(LifeB[x][y])
        case 3:
            CASEBODY(LifeR[x][y])
        default:
            goto done;
        }
        if (result == 0)
            result = -1;
    done:
    }
    return result;
}
