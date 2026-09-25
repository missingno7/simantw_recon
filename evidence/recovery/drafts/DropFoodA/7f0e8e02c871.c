/*
 * DropFoodA: advance the food/mold growth stage of the A-plane tile at
 * (x, y). Requires TERRAINset (TERRAINset flag, same
 * element used by _IsNotObstacle's threshold selection) == 1, else does
 * nothing (returns 0). The tile byte (MapA[x][y]) is classified: values
 * in [8,0x18) are normalized by repeatedly subtracting 8 and shifting
 * right 2; values under 4 become (value+6)<<2 and increment the far
 * counter FoodA (FoodA), returning true; values in
 * [0x18,0x27) just increment in place and return true. Values >= 0x40
 * and the remaining middle range spread using the far DROPdir table
 * (DROPdir, offsets 0x22be/0x22c2) to pick a neighbour
 * tile and recurse the same classification there; this spread path is
 * reconstructed from the disassembly with lower confidence than the
 * simple classification arms above.
 */
extern int far TERRAINset;
extern int far FoodA;
extern unsigned char near *far DROPdir;
extern unsigned char near MapA[128][64];

int far DropFoodA(int x, int y)
{
    unsigned char near *cell;
    int value;
    unsigned char near *dir;
    int nx, ny;

    cell = &MapA[x][y];
    value = *cell;
    if (TERRAINset != 1)
        return 0;

    for (;;) {
        if (value < 4) {
            *cell = (value + 6) << 2;
            FoodA++;
            return 1;
        }
        if (value >= 4 && value < 8) {
            (*cell)++;
            FoodA++;
            return 1;
        }
        if (value >= 8 && value < 0x18) {
            value = (value - 8) >> 2;
            continue;
        }
        if (value >= 0x18 && value < 0x27) {
            (*cell)++;
            return 1;
        }
        if (value >= 0x40) {
            dir = (unsigned char near *)DROPdir;
            nx = x + dir[0x22be];
            ny = y + dir[0x22c2];
            if (nx < 0 || nx > 0x7f || ny < 0 || ny > 0x3f)
                return 0;
            cell = &MapA[nx][ny];
            value = *cell;
            if (value < 4) {
                *cell = (value + 6) << 2;
                FoodA++;
                return 1;
            }
            return 0;
        }
        if (value >= 0x48 && value < 0x4b) {
            *cell = 0x48;
            continue;
        }
        return 0;
    }
}
