/* Candidate translation unit simtwo_8176_db_Exists_2_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _db_Exists, _db_SetDataBase
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

extern int far sprintf(char far *buffer, char far *format, ...);
extern int far access(char far *path, int mode);
extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
extern void far Punt(char far *message, ...);
extern int far ch_CreateTable(int size);
extern int far OpenDB(char far *name);
static int near db_closed = 1;




int db_Exists(char far *name)
{
    char path[100];

    sprintf(path, "%s.dat", name);
    if (access(path, 0) != -1)
        return 1;
    return 0;
}

int far db_SetDataBase(char far *name)
{
    char path[32];
    int handle;

    sprintf(path, "%s.dat", name);
    if (access(path, 0) == 0) {
        db_closed = 0;
        if (db_cacheTable == 0)
            db_cacheTable = ch_CreateTable(0);
        db_handles[db_numOfHandles] = OpenDB(name);
        handle = db_handles[db_numOfHandles++];
        if (handle < 0)
            Punt("Cannot open database %s", name);
        return handle;
    }
    return -1;
}

