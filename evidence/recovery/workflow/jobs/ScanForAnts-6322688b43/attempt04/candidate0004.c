/*
 * ScanForAnts: count live LifeA cells in the 4x4 tile block around the
 * spider.  The spider's pixel position (near words SpidX, SpidY) is scaled
 * to tiles (>> 4) inline; the optimizer keeps those two loop-invariant
 * values in frame temps ([bp-6], [bp-0xa]) and hoists the row sum through
 * AX into DI.  Offsets -1..2 in both axes are scanned and a cell counts
 * when it lies inside the 128x64 map and its LifeA byte (verified near map
 * convention, row stride 64) is nonzero; the count is carried in DX
 * through the inner loop.
 */
extern int near SpidX;
extern int near SpidY;
extern unsigned char near LifeA[];

int far ScanForAnts(void)
{
    int x;
    int y;
    int dx;
    int dy;
    int count;

    count = 0;
    for (dx = -1; dx < 3; dx++) {
        for (dy = -1; dy < 3; dy++) {
            x = (SpidX >> 4) + dx;
            y = (SpidY >> 4) + dy;
            if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f &&
                LifeA[x * 64 + y] != 0)
                count++;

        }
    }
    return count;
}
