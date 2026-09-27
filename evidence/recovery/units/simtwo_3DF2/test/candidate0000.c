/* Candidate translation unit simtwo_3DF2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _StartMigrate */

extern int far MigrateX;
extern int far MigrateY;
extern unsigned char far YMapPopB[12][16];

void far StartMigrate(int x, int y)
{
    struct { int far *p; } r;
    volatile int near *yHome;

    r.p = &MigrateY;
    yHome = &y;
    *r.p = (y - 66) / 10;
    MigrateX = (*yHome + x - 238) / 28;
    if (MigrateX < 0 || *r.p < 0 || MigrateX > 11 || *r.p > 15)
        MigrateX = -1;
    if (YMapPopB[MigrateX][*r.p] == 0)
        MigrateX = -1;

}

