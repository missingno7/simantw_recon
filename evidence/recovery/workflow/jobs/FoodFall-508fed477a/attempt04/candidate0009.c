/*
 * FoodFall: drop a food item from map cell (x, y) in the current DROPdir
 * direction until it lands.  Each step reads the terrain code of the near
 * MapA cell (64 cells per column); a code below 4 is open ground, so the
 * cell becomes the food code (code + 6) << 2, the FoodA count grows and
 * the fall ends.  Otherwise the position advances by the private
 * per-direction column/row deltas (stored as unsigned bytes, 255 meaning
 * -1 before the range test rejects it) and the fall also ends when the
 * column leaves 0..127 or the row leaves 0..63.
 */
extern unsigned char near MapA[];
extern int far DROPdir;
extern int far FoodA;

static unsigned char near dropDirX[4] = {0, 1, 0, 255};
static unsigned char near dropDirY[4] = {255, 0, 1, 0};

void far FoodFall(int x, int y)
{
    int col;
    int row;
    int off;
    int step;
    int cell;
    int falling;
    int dx;
    int dy;

    col = x;
    row = y;
    off = x << 6;
    falling = 1;
    step = dropDirX[DROPdir] << 6;
    do {
        cell = MapA[off + row];
        if (cell < 4) {
            MapA[off + row] = (cell + 6) << 2;
            FoodA++;
            falling = 0;
        }
        off += step;
        dy = dropDirY[DROPdir];
        row += dy;
        dx = dropDirX[DROPdir];
        col += dx;
        if (col < 0 || col > 127)
            falling = 0;
        if (row < 0 || row > 63)
            falling = 0;
    } while (falling);
}
