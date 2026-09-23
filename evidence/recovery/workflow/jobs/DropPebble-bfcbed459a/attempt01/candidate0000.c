/*
 * DropPebble hypothesis from the target's three phases: surface drops consult
 * IsItHole, underground drops inspect tile 0x18, reciprocal hole maps can
 * place a surface pebble (0x51), and the final selected map is updated before
 * ZapEuMapAt. The two far hole arrays are established MAPSYM names.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern int far IsItHole(int x, int y);
extern void far ZapEuMapAt(int plane, int x, int y);

int far DropPebble(int plane, int x, int y)
{
    int hole;
    int tile;
    int value;
    int row;

    value = 0x30;
    if (plane <= 1) {
        hole = IsItHole(x, y);
        if (hole != 0) {
            if (x < 0x40) {
                if (HoleMapB[y] == x)
                    MapB[x][y] = 0x31;
                else if (HoleMapR[y] == x) {
                    MapR[x][y] = 0x31;
                    value = 0x51;
                }
            } else if (HoleMapR[y] == x) {
                MapR[x][y] = 0x31;
                value = 0x51;
            }
        }
    } else if (y <= 0) {
        if (plane == 2)
            tile = MapB[x][y];
        else
            tile = MapR[x][y];
        if (tile == 0x18) {
            if (plane == 2)
                row = HoleMapB[x];
            else
                row = HoleMapR[x];
            MapA[x][row] = 0x51;
            value = 0x31;
        }
    }
    if (plane <= 1) {
        hole = IsItHole(x, y);
        if (hole != 0) {
            if (plane == 2)
                row = HoleMapB[x];
            else
                row = HoleMapR[x];
            MapA[x][row] = 0x51;
            value = 0x31;
        }
    }
    if (plane == 0 || plane == 1) {
        MapA[x][y] = value;
    } else if (plane == 2) {
        MapB[x][y] = value;
    } else if (plane == 3) {
        MapR[x][y] = value;
    }
    ZapEuMapAt(plane, x, y);
    return 0;
}
