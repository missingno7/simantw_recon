/*
 * ScanForAnts: count live LifeA cells in the 4x4 tile block around the
 * spider.  The spider's pixel position (near words SpidX, SpidY) is scaled
 * to tiles (>> 4); offsets -1..2 in both axes are scanned and a cell counts
 * when it lies inside the 128x64 map and its LifeA byte (verified near map
 * convention, row stride 64) is nonzero.  The original computes the column
 * (tileY + dy) into BX at the top of the inner body, keeps the hoisted row
 * sum in DI, re-evaluates the row sum for its sign test, and carries the
 * count in DX through the inner loop; this batch varies whether the row
 * and column are named variables and how the offset loops are spelled.
 */
extern int near SpidX;
extern int near SpidY;
extern unsigned char near LifeA[];

int far ScanForAnts(void)
{
    int dx;
    int dy;
    int x;
    int y;
    int tileX;
    int count;
    int tileY;

    tileX = SpidX >> 4;
    tileY = SpidY >> 4;
    count = 0;
    for (dx = -1; dx < 3; dx++) {
        for (dy = -1; dy < 3; dy++) {
            y = tileY + dy;
            if (tileX + dx >= 0 && tileX + dx <= 0x7f &&
                y >= 0 && y <= 0x3f &&
                LifeA[(tileX + dx) * 64 + y] != 0)
                count++;
        }
    }

    return count;
}
