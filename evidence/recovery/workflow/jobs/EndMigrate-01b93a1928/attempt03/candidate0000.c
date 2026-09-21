/*
 * EndMigrate: a migrating colony arrives at pixel (x, y).  The departure
 * patch is (MigrateX, MigrateY) in PACK (a negative MigrateX means no
 * migration); the arrival patch is x = (x + y - 238) / 28 and
 * y = (y - 66) / 10 (signed divisions) and must lie inside the 12 x 16
 * patch grid.  Half of the departure patch's B-colony yard population
 * byte (YMapPopB, SIMANT_DATA_GROUP offset 0xa4, 16 bytes per row) is
 * removed from it and added to the arrival patch, capped at 0xfa when the
 * sum reaches 0xfb; the arrival byte is reached through a far pointer
 * local while the departure byte is indexed.  The segment selectors are loaded as immediates with
 * DS switched for the population bytes, as in the verified Dx8 sources.
 */
extern int far MigrateX;
extern int far MigrateY;
extern unsigned char far Dx8[];

void far EndMigrate(int x, int y)
{
    int half;
    int from;
    unsigned char far *p;
    int tx;
    int ty;

    from = MigrateX;
    if (from < 0)
        return;
    ty = (y - 66) / 10;
    tx = (y + x - 238) / 28;
    if (tx < 0 || ty < 0 || tx > 11 || ty > 15)
        return;
    half = Dx8[from * 16 + MigrateY + 0xa4] >> 1;
    Dx8[from * 16 + MigrateY + 0xa4] -= half;
    p = &Dx8[tx * 16 + ty + 0xa4];
    if (*p + half < 0xfb)
        *p += half;
    else
        *p = 0xfa;
}

