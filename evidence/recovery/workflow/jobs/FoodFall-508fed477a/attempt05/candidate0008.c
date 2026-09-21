/*
 * FoodFall: drop a food item from map cell (x, y) in the current DROPdir
 * direction until it lands.  Each step reads the terrain code of the near
 * 128x64 MapA cell; a code below 4 is open ground, so the cell becomes the
 * food code (code + 6) << 2, the FoodA count grows and the fall ends.
 * Otherwise the position advances by the private per-direction column/row
 * deltas (stored as unsigned bytes, 255 meaning -1 before the range test
 * rejects it) and the fall also ends when the column leaves 0..127 or the
 * row leaves 0..63.
 */
extern unsigned char near MapA[128][64];
extern int far DROPdir;
extern int far FoodA;

static unsigned char near dropDirX[4] = {0, 1, 0, 255};
static unsigned char near dropDirY[4] = {255, 0, 1, 0};

void far FoodFall(int x, int y)
{
    int col;
    int row;
    int falling;
    int cell;
#define COL col
#define ROW row

    falling = 1;
    COL = x;
    ROW = y;
    do {
        cell = MapA[COL][ROW];
        if (cell < 4) {
            MapA[COL][ROW] = (cell + 6) << 2;
            FoodA++;
            falling = 0;
        }
        ROW += dropDirY[DROPdir];
        COL += dropDirX[DROPdir];
        if (COL < 0 || COL > 127)
            falling = 0;
        if (ROW < 0 || ROW > 63)
            falling = 0;
    } while (falling);
}
