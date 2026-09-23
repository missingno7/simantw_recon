/*
 * DropPebble hypothesis revision 4. The target reads IsItHole twice for
 * surface planes, tests the paired HoleMapB/R entries, and writes reciprocal
 * pebble state before a final bounded map write. Underground planes use tile
 * 0x18 as the entrance condition. This preserves separate map-switch blocks
 * visible in the CFG and uses the verified 128x64 / 64x64 map declarations.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern int far IsItHole(int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);

void far DropPebble(int plane, int x, int y)
{
    int ok;
    register int value;
    register int rx;
    register int ry;

    value = 0x30;
    if (plane <= 1) {
        rx = x;
        ry = y;
        ok = IsItHole(rx, ry);
        if (ok != 0) {
            if (rx >= 0 && rx < 0x40 && HoleMapB[ry] == rx) {
                MapB[rx][ry] = 0x31;
            } else if (HoleMapR[ry] == rx) {
                MapR[rx][ry] = 0x31;
                value = 0x51;
                goto finish;
            }
        }
    }

    if (plane <= 1) {
        rx = x;
        ry = y;
        ok = IsItHole(rx, ry);
    } else if (y > 0) {
        ok = 0;
    } else {
        ok = -1;
        if (plane <= 1)
            ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
        else
            ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
        if (ok == 1) {
            if (plane == 2)
                ok = MapB[x][y];
            else
                ok = MapR[x][y];
            ok = (ok == 0x18);
        }
    }

    if (ok != 0) {
        if (plane == 2) {
            MapA[x][HoleMapB[x]] = 0x51;
        } else {
            MapA[x][HoleMapR[x]] = 0x51;
        }
        value = 0x31;
        goto finish;
    }

    value = 0x30;
finish:
    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok != 0) {
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
