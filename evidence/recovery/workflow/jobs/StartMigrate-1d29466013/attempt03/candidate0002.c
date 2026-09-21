/*
 * StartMigrate: choose the yard patch a migrating colony heads for from
 * the pixel position (x, y).  MigrateY (PACK) becomes (y - 66) / 10 and
 * MigrateX (PACK) becomes (x + y - 238) / 28 (signed divisions); if either
 * lies outside the 12 x 16 patch grid the target is cancelled with
 * MigrateX = -1, and it is also cancelled when the B-colony yard
 * population byte YMapPopB[MigrateX][MigrateY] (SIMANT_DATA_GROUP, 12 rows
 * of 16) is zero.  The compiler caches the far address of MigrateY in a
 * stack temporary and keeps the PACK segment in DS for MigrateX.
 */
extern int far MigrateX;
extern int far MigrateY;
extern unsigned char far YMapPopB[12][16];

void far StartMigrate(int x, int y)
{
    struct { int far *p; } r;

    r.p = &MigrateY;
    *r.p = (y - 66) / 10;
    MigrateX = (y + x - 238) / 28;
    if (MigrateX < 0 || *r.p < 0 || MigrateX > 11 || *r.p > 15)
        MigrateX = -1;
    if (YMapPopB[MigrateX][MigrateY] == 0)
        MigrateX = -1;

}
