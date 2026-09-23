/*
 * DropPebble hypothesis from the target CFG. The entry tests a surface hole;
 * the second redundant plane test leads to the target's separate bounds and
 * tile-0x18 path. A matching reciprocal HoleMapB[y]/HoleMapR[y] updates the
 * corresponding underground cell. The later hole/underground-entrance path
 * writes a 0x51 pebble at MapA[x][HoleMapB/R[x]], then the final checked
 * switch writes 0x30, 0x31, or 0x51 at the requested map cell and redraws it.
 * MAPSYM gives MapA/B/R and segment-8 HoleMapB/R; IsItHole and ZapEuMapAt
 * match the packet's calls.
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
    int row;

    if (plane > 1)
        goto stage_two;
    if (plane > 1)
        goto non_surface_entry;

    ok = IsItHole(x, y);
    goto first_gate;

non_surface_entry:
    if (y <= 0) {
        ok = -1;
        if (plane <= 1) {
            if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f)
                ok = 1;
        } else {
            if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f)
                ok = 1;
        }
        if (ok != 0) {
            if (plane == 0 || plane == 1)
                tile = MapA[x][y];
            else if (plane == 2)
                tile = MapB[x][y];
            else if (plane == 3)
                tile = MapR[x][y];
            else
                tile = -1;
            if (tile == 0x18)
                ok = 1;
        }
    } else {
        ok = 0;
    }

first_gate:
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

stage_two:
    if (plane <= 1) {
        ok = IsItHole(x, y);
    } else if (y > 0) {
        ok = 0;
    } else {
        ok = -1;
        if (plane <= 1) {
            if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f)
                ok = 1;
        } else {
            if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f)
                ok = 1;
        }
        if (ok != 0) {
            if (plane == 2)
                tile = MapB[x][y];
            else if (plane == 3)
                tile = MapR[x][y];
            else
                tile = -1;
            if (tile == 0x18)
                ok = 1;
            else
                ok = 0;
        }
    }

    if (ok != 0) {
        if (plane == 2)
            row = HoleMapB[x];
        else
            row = HoleMapR[x];
        MapA[x][row] = 0x51;
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
