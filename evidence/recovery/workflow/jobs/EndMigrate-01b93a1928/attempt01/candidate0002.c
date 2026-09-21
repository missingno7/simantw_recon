/*
 * EndMigrate: a migrating colony arrives at pixel (x, y).  The departure
 * patch is (MigrateX, MigrateY) in PACK (a negative MigrateX means no
 * migration); the arrival patch is x = (x + y - 238) / 28 and
 * y = (y - 66) / 10 (signed divisions) and must lie inside the 12 x 16
 * patch grid.  Half of the departure patch's B-colony yard population
 * byte (YMapPopB, SIMANT_DATA_GROUP offset 0xa4, 16 bytes per row) is
 * removed from it and added to the arrival patch, capped at 0xfa when the
 * sum reaches 0xfb.  The segment selectors are loaded as immediates with
 * DS switched for the population bytes, as in the verified Dx8 sources.
 */
extern int far MigrateX;
extern int far MigrateY;
extern unsigned char far YMapPopB[12][16];

void far EndMigrate(int x, int y)
{
    int from;
    int tx;
    int ty;
    int half;

    from = MigrateX;
    if (from < 0)
        return;
    ty = (y - 66) / 10;
    tx = (y + x - 238) / 28;
    if (tx < 0 || ty < 0 || tx > 11 || ty > 15)
        return;
    half = YMapPopB[from][MigrateY] >> 1;
    YMapPopB[from][MigrateY] -= half;
    if (YMapPopB[tx][ty] + half < 0xfb)
        YMapPopB[tx][ty] += half;
    else
        YMapPopB[tx][ty] = 0xfa;
}

