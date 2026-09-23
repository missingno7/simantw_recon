/*
 * DropPebble reconstruction, revision 2. Surface points first call IsItHole;
 * a reciprocal HoleMapB[y]/HoleMapR[y] match changes that underground map
 * cell to 0x31, with the red-side branch selecting 0x51 for the target. The
 * second stage also accepts a surface hole or underground tile 0x18, writes
 * the linked MapA cell as 0x51, and selects 0x31 for the target. Otherwise
 * the target gets 0x30. The final bounds-checked switch writes the selected
 * tile and calls ZapEuMapAt. HoleMapB/R are far segment-8 MAPSYM objects.
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
    int value;
    int tile;

    if (plane <= 1) {
        ok = IsItHole(x, y);
        if (ok != 0) {
            if (x < 0x40) {
                if (HoleMapB[y] == x) {
                    MapB[x][y] = 0x31;
                } else if (HoleMapR[y] == x) {
                    MapR[x][y] = 0x31;
                    value = 0x51;
                    goto finish;
                }
            } else if (HoleMapR[y] == x) {
                MapR[x][y] = 0x31;
                value = 0x51;
                goto finish;
            }
        }
    }

    if (plane <= 1) {
        ok = IsItHole(x, y);
    } else {
        ok = 0;
        if (y <= 0 && x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
            if (plane == 2)
                tile = MapB[x][y];
            else if (plane == 3)
                tile = MapR[x][y];
            else
                tile = -1;
            if (tile == 0x18)
                ok = 1;
        }
    }

    if (ok != 0) {
        if (plane == 2)
            tile = HoleMapB[x];
        else
            tile = HoleMapR[x];
        MapA[x][tile] = 0x51;
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
