/*
 * DropPebble: surface drops first look for an existing hole.  If the hole's
 * reciprocal underground entry points back to this x coordinate, the paired
 * underground cell is changed to 0x31; the red-side case instead selects
 * 0x51 for the surface cell.  On all planes, a hole or underground 0x18
 * location can also place a 0x51 surface pebble.  The final bounded write
 * stores the selected pebble tile and redraws the position.
 *
 * The maps use their MAPSYM names and the far hole arrays follow the segment-8
 * bindings observed at selector slots C4A8/C4AA.  IsLiftable is used only as
 * evidence for the 128x64/64x64 map shapes and coordinate limits.
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

    value = 0x30;
    if (plane <= 1) {
        ok = IsItHole(x, y);
        if (ok != 0) {
            if (x >= 0 && x <= 0x3f) {
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
        if (y <= 0) {
            if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
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
