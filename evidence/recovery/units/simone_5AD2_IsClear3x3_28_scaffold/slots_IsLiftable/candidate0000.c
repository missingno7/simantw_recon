/*
 * IsLiftable: whether whatever is at (plane, x, y) can be lifted.
 *
 * FindEggAt (same-segment far call; its far out-parameter receives the
 * egg's ant-list index) is asked first and its return value is examined
 * last.  The terrain cell is then read exactly as GetMap does it
 * (src/recovered/wf_GetMap-cddf28f960.c): a materialised bounds flag
 * (0<=x<=0x7f, 0<=y<=0x3f on the surface planes 0/1; 0<=x<=0x3f,
 * 0<=y<=0x3f underground) tested with `ok == TRUE`, a switch on the plane
 * reading the named near map (MapA planes 0/1, MapB plane 2, MapR plane
 * 3), and a -1 default kept in the frame slot `map` for an out-of-range
 * position or an unknown plane.  The lookup result is then copied into
 * the working `tile`: the frame word [bp-2] is only ever reloaded on the
 * default path, while every later test runs on a register copy (SI, once
 * y is dead) and x/y both keep DI/SI through the lookup -- a single
 * variable with seven later reads would win the callee-saved register
 * from x instead (probed: with the tests on the frame variable the
 * compiler spills x to memory and keeps the lookup in SI).
 *
 * Tests, each materialised in `ok` and gated by `ok == FALSE` so the
 * three "liftable" exits share the final return TRUE after return FALSE:
 * food (IsItFood, cross-segment far call, on the surface; tiles
 * 0x10..0x13 underground), pebble (plane 1: 0x51..0x53; underground:
 * 0x30..0x31, the ranges of the admitted IsThisPebble) and finally a
 * carried egg class: (eggResult & 0x7f) in 1..7 exactly as the admitted
 * IsThisEgg normalises its value (word compare of a masked int).
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int far FindEggAt(int far *outIndex, int plane, int x, int y);
extern int far IsItFood(int tile);

#define TRUE 1
#define FALSE 0

int far IsLiftable(int plane, int x, int y)
{
    int eggIndex;
    int eggResult;
    int map;
    int ok;
    int tile;

    eggResult = FindEggAt(&eggIndex, plane, x, y);
    map = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == TRUE) {
        switch (plane) {
        case 0:
        case 1:
            map = MapA[x][y];
            break;
        case 2:
            map = MapB[x][y];
            break;
        case 3:
            map = MapR[x][y];
            break;
        }
    }
    tile = map;

    if (plane <= 1)
        ok = IsItFood(tile);
    else
        ok = (tile >= 0x10 && tile <= 0x13);
    if (ok == FALSE) {
        if (plane <= 1)
            ok = (plane == 1 && tile >= 0x51 && tile <= 0x53);
        else
            ok = (tile >= 0x30 && tile <= 0x31);
        if (ok == FALSE) {
            ok = eggResult & 0x7f;
            ok = (ok >= 1 && ok <= 7);
            if (ok == FALSE)
                return FALSE;
        }
    }
    return TRUE;
}
