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
extern int far match_position[];
extern unsigned char far Dx8[];

void far EndMigrate(int x, int y)
{
    int from;
    int tx;
    int ty;
    int half;

    from = match_position[0x4e77];
    if (from < 0)
        return;
    ty = (y - 66) / 10;
    tx = (y + x - 238) / 28;
    if (tx < 0 || ty < 0 || tx > 11 || ty > 15)
        return;
    half = Dx8[from * 16 + match_position[0x4eb9] + 0xa4] >> 1;
    Dx8[from * 16 + match_position[0x4eb9] + 0xa4] -= half;
    if (Dx8[tx * 16 + ty + 0xa4] + half < 0xfb)
        Dx8[tx * 16 + ty + 0xa4] += half;
    else
        Dx8[tx * 16 + ty + 0xa4] = 0xfa;
}

