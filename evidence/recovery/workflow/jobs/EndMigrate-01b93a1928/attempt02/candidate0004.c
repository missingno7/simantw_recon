/*
 * EndMigrate: a migrating colony arrives at pixel (x, y).  The departure
 * patch is (MigrateX, MigrateY) in PACK (a negative MigrateX means no
 * migration); the arrival patch is x = (x + y - 238) / 28 and
 * y = (y - 66) / 10 (signed divisions) and must lie inside the 12 x 16
 * patch grid.  Half of the departure patch's B-colony yard population
 * byte (YMapPopB, SIMANT_DATA_GROUP offset 0xa4, 16 bytes per row) is
 * removed from it and added to the arrival patch, capped at 0xfa when the
 * sum reaches 0xfb; the two grid byte offsets are kept in locals.  The
 * segment selectors are loaded as immediates with
 * DS switched for the population bytes, as in the verified Dx8 sources.
 */
extern int far MigrateX;
extern int far MigrateY;
extern unsigned char far Dx8[];

void far EndMigrate(int x, int y)
{
    int from;
    int tx;
    int ty;
    int src;
    int dst;
    int half;

    from = MigrateX;
    if (from < 0)
        return;
    ty = (y - 66) / 10;
    tx = (y + x - 238) / 28;
    if (tx < 0 || ty < 0 || tx > 11 || ty > 15)
        return;
    src = from * 16 + MigrateY;
    half = Dx8[src + 0xa4] >> 1;
    Dx8[src + 0xa4] -= half;
    dst = tx * 16 + ty;
    if (Dx8[dst + 0xa4] + half < 0xfb)
        Dx8[dst + 0xa4] += half;
    else
        Dx8[dst + 0xa4] = 0xfa;
}

