/*
 * ScanForAnts: count live LifeA cells in the 4x4 tile block around the
 * spider.  The spider's pixel position (near words SpidX, SpidY) is scaled
 * to tiles (>> 4); offsets -1..2 in both axes are scanned and a cell counts
 * when it lies inside the 128x64 map and its LifeA byte (verified near map
 * convention, row stride 64) is nonzero.  The loop optimizer hoists the
 * row coordinate into DI for the inner loop while the sign test of the row
 * is re-evaluated from the spilled offset.
 */
extern int near SpidX;
extern int near SpidY;
extern unsigned char near LifeA[];

int far ScanForAnts(void)
{
    int dy;
    int dx;
    int tileX;
    int count;
    int tileY;

    tileX = SpidX >> 4;
    tileY = SpidY >> 4;
    count = 0;
    for (dx = -1; dx < 3; dx++) {
        for (dy = -1; dy < 3; dy++) {
            if (tileX + dx >= 0 && tileX + dx <= 0x7f &&
                tileY + dy >= 0 && tileY + dy <= 0x3f &&
                LifeA[(tileX + dx) * 64 + (tileY + dy)] != 0)
                count++;
        }
    }
    return count;
}
