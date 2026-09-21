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
    int falling;
    int cell;
    int off;
    int step;

    off = x << 6;
    falling = 1;
    step = dropDirX[DROPdir] << 6;
    do {
        p = MapA + off + y;
        cell = *p;
        if (cell < 4) {
            *p = (cell + 6) << 2;
            FoodA++;
            falling = 0;
        }
        off += step;
        y += dropDirY[DROPdir];
        x += dropDirX[DROPdir];
        if (x < 0 || x > 127)
            falling = 0;
        if (y < 0 || y > 63)
            falling = 0;
    } while (falling);
}
